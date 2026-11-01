from .hub import Hub
from .macros import Zone


class Constellation:
    def __init__(self, file_name):
        self._name = file_name.split("/")[-1].split(".")[0]
        self._nb_drones: int = 0
        self._hubs: list[Hub] = []
        self._connnections: list[tuple[Hub, Hub, int]] = []
        start_hub: Hub | None = None
        end_hub: Hub | None = None
        con_data: list[tuple[str, str, int]] = []
        self._routes: dict[int, list[Hub]] = {}
        with open(file_name, "r") as f:
            for line in f:
                line = line.strip()
                if line.startswith("nb_drones"):
                    if self._nb_drones == 0:
                        self._nb_drones = int(line.split()[1])
                    else:
                        raise ValueError(
                            f"Duplicate nb_drones found: {line.split()[1]}")
                if line.startswith("start_hub"):
                    if start_hub is None:
                        start_hub = Hub.from_line(line)
                        self._hubs.append(start_hub)
                    else:
                        raise ValueError(
                            f"Duplicate start_hub found: {line.split()[1]}")
                if line.startswith("end_hub"):
                    if end_hub is None:
                        end_hub = Hub.from_line(line)
                        end_hub.features.max_drones = 10000  # Goal hub cannot have drones
                        self._hubs.append(end_hub)
                        if (line := f.readline()).strip() != "":
                            raise ValueError(
                                f"Expected empty line after hubs but got: {line}")
                        continue
                    else:
                        raise ValueError(
                            f"Duplicate end_hub found: {line.split()[1]}")
                elif line.startswith("hub:"):
                    contender = Hub.from_line(line)
                    if (contender.name in [hub.name for hub in self._hubs]):
                        raise ValueError(
                            f"Duplicate hub found: {contender.name}")
                    self._hubs.append(Hub.from_line(line))
                elif line.startswith("connection"):
                    con_contender = self.con_data_from_line(line)
                    if self.combination_exists(con_contender):
                        raise ValueError(
                            f"Duplicate connection found: {con_contender}")
                    con_data.append(self.con_data_from_line(line))
                elif line == "" or line.strip().startswith("#"):
                    continue
        hub_by_name = {hub.name: hub for hub in self._hubs}

        self._map: dict[Hub, list[tuple[Hub, int]]] = {
            hub: [] for hub in self._hubs
        }

        for hub1_name, hub2_name, capacity in con_data:
            hub1 = hub_by_name.get(hub1_name)
            hub2 = hub_by_name.get(hub2_name)

            if hub1 is None or hub2 is None:
                raise ValueError(
                    "Connection refers to unknown hubs: " +
                    f"{hub1_name}, {hub2_name}"
                )
            self._connnections.append((hub1, hub2, capacity))
            self._map[hub1].append((hub2, capacity))
        for index in range(1, self._nb_drones + 1):
            self._routes[index] = []
        if start_hub is None or end_hub is None:
            raise ValueError("Missing start_hub or end_hub in the constellation file.")
        self._start_hub = start_hub
        self._end_hub = end_hub
        self._all_paths: list[tuple[float, list[Hub]]] = self.find_all_paths()
        self._all_paths.sort(key=lambda x: x[0])  # Sort by weight (cost)
        self._simulated = False

    def get_routes(self) -> dict[int, list[Hub]]:
        if not self._simulated:
            raise ValueError("Drones have not been simulated yet.")
        return self._routes

    def find_shortest_path(self) -> list[Hub]:
        """
        Find the shortest path from the start hub to the end hub using Dijkstra's algorithm.
        Returns a list of Hubs representing the path from start to end.
        """
        import heapq
        from itertools import count

        tie_breaker = count()
        # Priority queue to store (cost, hub, path)
        queue = [(0, 1, next(tie_breaker), self._start_hub, [])]
        visited: dict[Hub, int] = {}

        while queue:
            time, _, _, current_hub, path = heapq.heappop(queue)

            if current_hub in visited and visited[current_hub] <= time:
                continue

            new_path = path + [current_hub]

            if current_hub in visited and visited[current_hub] <= time:
                continue

            visited[current_hub] = time
            new_path = path + [current_hub]

            if current_hub == self._end_hub:
                return new_path

            # Explore neighbors
            for neighbor, capacity in self._map[current_hub]:
                if neighbor.features.cost is float("inf"):
                    continue  # Skip neighbors that are not reachable
                new_time = time + neighbor.features.cost
                if neighbor.features.zone == Zone.PRIORITY:
                    priority_rank = 0
                else:
                    priority_rank = 1

                heapq.heappush(queue, (new_time, priority_rank, next(tie_breaker), neighbor, new_path))

        raise ValueError("No path found from start hub to end hub.")

    def find_all_paths(self) -> list[tuple[float, list[Hub]]]:
        """
        Find all paths from start_hub to end_hub using DFS.
        Returns a dictionary where keys are weights (total cost) and values are lists of Hubs representing the paths.
        """
        all_paths: list[tuple[float, list[Hub]]] = []

        def dfs(current_hub: Hub, path: list[Hub], total_cost: float):
            if current_hub == self._end_hub:
                all_paths.append((total_cost, path.copy()))
                return

            for neighbor, capacity in self._map[current_hub]:
                if neighbor in path:
                    continue  # Avoid cycles
                if neighbor.features.cost is float("inf"):
                    continue  # Skip neighbors that are not reachable
                path.append(neighbor)
                dfs(neighbor, path, total_cost + neighbor.features.cost)
                path.pop()

        dfs(self._start_hub, [self._start_hub], 0)
        self._all_paths = all_paths
        return all_paths

    def fly_one_drone(self, drone_id: int, path: list[Hub]):
        """
        Simulate flying one drone along the given path.
        Updates the routes dictionary with the drone's moves.
        """
        for hub in path:  # Skip the starting hub
            self._routes[drone_id].append(hub)

    def paths_from_hub(self, hub: Hub):
        """
        Get all paths starting from a specific hub to the end hub.
        """
        for weight, path in self._all_paths:
            for index, hub_in_path in enumerate(path):
                if hub_in_path == hub:
                    yield (weight, path[index:])  # Return the subpath starting from the specified hub


    def simulate_drones(self):
        """
        Simulate flying all drones from the start hub to the end hub.
        We account for maximum connection capacities and ensure that drones do not exceed these limits.
        """

        # Find the shortest path for all drones
        shortest_path = self._all_paths[0][1]  # Assuming the first path is the shortest due to sorting by cost

        # Fly each drone along the shortest path
        for drone_id in range(1, self._nb_drones + 1):
            route = []
            path_ahead = shortest_path[1:]  # Skip the starting hub
            position = self._start_hub
            step = 0
            while position is not self._end_hub:
                con_capacity = self.get_connection_capacity(position, path_ahead[0], step)
                hub_capacity = self.get_hub_capacity(position, path_ahead[0], step)
                if con_capacity > 0 and hub_capacity > 0:
                    position = path_ahead.pop(0)
                    route.append(position)
                else:
                    moved = False
                    alternatives = self.paths_from_hub(position)
                    for alt_weight, alt_path in alternatives:
                        next_hub = alt_path[1]
                        con_capacity = self.get_connection_capacity(position, next_hub, step)
                        hub_capacity = self.get_hub_capacity(position, next_hub, step)
                        if con_capacity > 0 and hub_capacity > 0:
                            position = next_hub
                            route.append(position)
                            path_ahead = alt_path[2:]  # Update path ahead to the alternative path
                            moved = True
                            break
                    if not moved:
                        route.append(None)  # Drone waits at the current hub
                step += 1
            self.fly_one_drone(drone_id, route)
            self._log_route = self.format_simulation_routes(self._routes)
            self._simulated = True


    def drones_current_hub(self, drone_id: int, step: int) -> Hub | None:
        """
        Get the current hub of a drone at a specific step.
        """
        pos = self._start_hub
        for i in range(step + 1):
            if self._routes[drone_id][i] is not None:
                pos = self._routes[drone_id][i]
        return pos

    def get_hub_capacity(self, cur_hub: Hub, next_hub: Hub, step: int) -> int:
        """
        Get the remaining capacity of the next hub at the specified step.
        This method checks how many drones are currently at the next hub and returns the remaining capacity.
        """
        drone_count_at_hub = 0
        for drone_route in self._routes:
            if step < len(self._routes[drone_route]):
                if self.drones_current_hub(drone_route, step) == next_hub:
                    drone_count_at_hub += 1
        remaining_capacity = next_hub.features.max_drones - drone_count_at_hub
        if remaining_capacity < 0:
            raise ValueError(
                f"Hub capacity exceeded at {next_hub.name} at step {step}.")
        return remaining_capacity

    def drone_position_before_step(self, drone_id: int, step: int) -> Hub | None:
        """
        Get the position of a drone before a specific step.
        If the drone has not moved yet, it will return the starting hub.
        """
        if step == 0:
            return self._start_hub
        elif step > len(self._routes[drone_id]):
            raise ValueError(
                f"Step {step} is out of range for drone {drone_id}.")
        else:
            while step > 0 and self._routes[drone_id][step - 1] is None:
                step -= 1
            if step == 0:
                return self._start_hub
            return self._routes[drone_id][step - 1]

    def get_connection_capacity(self, cur_hub: Hub, next_hub: Hub, step: int) -> int:
        """
        Get the remaining capacity of the connection from the given hub at the specified step.
        This method checks how many drones are currently on the connection and returns the remaining capacity.
        """
        available_connections = self._map[cur_hub]
        current_connection = available_connections[[hub for hub, _ in available_connections].index(next_hub)]
        original_capacity = current_connection[1]
        drone_count_on_connection = 0
        for drone_route in self._routes:
            route = self._routes[drone_route]
            if step >= len(route):
                continue  # Drone has not reached this step yet
            from_hub = self.drone_position_before_step(drone_route, step)
            to_hub = route[step]
            if to_hub is None:
                continue  # Drone is waiting at the current hub, not moving to the next hub
            if from_hub == cur_hub and to_hub == next_hub:
                drone_count_on_connection += 1
        remaining_capacity = original_capacity - drone_count_on_connection
        if remaining_capacity < 0:
            raise ValueError(
                f"Connection capacity exceeded between {cur_hub.name} and {next_hub.name} at step {step}.")

        return remaining_capacity

    def combination_exists(
        self,
        combination: tuple[str, str, int],
    ) -> bool:
        return combination in self._connnections or (combination[1], combination[0]) in self._connnections

    @staticmethod
    def format_simulation_routes(routes: dict[int, list[Hub]]) -> list[str]:
        """
        Convert drone routes into the required turn-by-turn output format.

        Assumes each route contains only the hubs/zones the drone moves to,
        not the starting hub.
        """
        output_lines = []

        for turn in range(max(len(route) for route in routes.values())):
            moves = []

            for drone_id, route in routes.items():
                  # Drone is still at the starting hub
                if turn < len(route):
                    destination = route[turn]
                    if destination is None:
                        continue
                    moves.append(f"D{drone_id}-{destination.name}")

            if moves:
                output_lines.append(" ".join(moves))

        return output_lines

    def print_simulation_routes(self):
        for line in self.format_simulation_routes(self._routes):
            print(line)

    @staticmethod
    def con_data_from_line(line: str) -> tuple[str, str, int]:
        if not line.startswith("connection:"):
            raise ValueError("Expected connection line")
        connection = line.split(":", 1)[1].strip().split()[0]
        hub1_name, hub2_name = connection.split("-", 1)
        max_link_capacity = 1  # Default value
        if "max_link_capacity=" in line:
            max_link_capacity_str = line.split("max_link_capacity=")[1].strip().replace("]", "")
            try:
                max_link_capacity = int(max_link_capacity_str)
            except ValueError:
                raise ValueError(
                    f"Invalid max_link_capacity value: {max_link_capacity_str}")
        return (hub1_name, hub2_name, max_link_capacity)


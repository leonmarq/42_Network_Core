from .constellation import Hub, Constellation


class Scheduler:
    """
    takes a constellation and returns a dict with lists of moves for each drone to reach its destination.
    if a drone doesnt move, Null will get added instead of a hub.
    """

    def __init__(self, constellation: Constellation):
        self.constellation = constellation
        self.positions = {drone_id: constellation._start_hub for drone_id in range(1, constellation._nb_drones + 1)}
        self.routes = {drone_id: [] for drone_id in range(1, constellation._nb_drones + 1)}
        self.all_paths = self.constellation._all_paths
        self.finished = set()

    @staticmethod
    def hub_overflow(available_moves, hub: Hub):
        """
        Check if a hub's capacity would be exceeded if the least expensive moves are taken.
        """
        count = sum(1 for moves in available_moves.values() if moves and moves[0][1][0] == hub)
        return count > hub.features.max_drones

    def paths_from_hub(self, hub: Hub):
        """
        Get all paths starting from a specific hub to the end hub.
        """
        for weight, path in self.all_paths:
            for index, hub_in_path in enumerate(path):
                if hub_in_path == hub:
                    yield (weight, path[index:])  # Return the subpath starting from the specified hub

    def connection_exeeded(self, available_moves, from_hub, to_hub):
        """
        Check if a connection's capacity would be exceeded if the least expensive moves are taken.
        """
        all_connections = self.constellation._map[from_hub]
        connection = all_connections[[hub for hub, _ in all_connections].index(to_hub)]
        if connection is None:
            raise ValueError(f"No connection found from {from_hub} to {to_hub}")
        capacity = connection[1]
        drone_count = sum(1 for moves in available_moves.values() if moves and moves[0][1][0] == to_hub)
        if (drone_count + 1) > capacity:
            return True
        return False

    def choose_alternative(self, available_moves, drone_id):
        """
        Choose an alternative path for the drone or its conflicting drones if the least expensive path is not feasible due to hub or connection capacity constraints
        """
        # Get the least expensive move for the drone
        least_expensive_move = available_moves[drone_id][0]
        alternative_moves = available_moves[drone_id][1:]  # Exclude the least expensive move

        # Check if there are alternative moves available
        if not alternative_moves:
              # No alternatives, return the original available moves

        # Check if the least expensive move is feasible
        for alternative_move in alternative_moves:
            if not hub_overflow(available_moves, alternative_move[1][0]) and not self.connection_exeeded:
                return alternative_move  # Return the first feasible alternative move

    def choose_hub_alternative(self, available_moves, hub):



    def choose_turn_moves(self):
        """
        "Priority Inheritance with Backtracking" (PIBT) algorithm to find paths for all drones to reach their destinations.
        """
        planned_moves = {}
        available_paths = {}
        available_moves = {}
        for drone_id, current_hub in self.positions.items():
            if drone_id in self.finished:
                planned_moves[drone_id] = None
                continue
            available_paths[drone_id] = list(self.paths_from_hub(current_hub))
        for drone_id, paths in available_paths.items():
            if not paths:
                available_moves[drone_id] = None  # No available moves for this drone
                continue
            # Choose the least expensive path for the drone
            for weight, path in paths:
                available_moves[drone_id][weight] = (path[0], path[1])
        for hub in available_paths.values():
            if (
                self.hub_overflow(available_paths, hub)
            ):
                available_paths = self.choose_hub_alternative(available_paths, hub)
        for drone_id, paths in available_paths.items():
            if self.connection_exeeded(available_paths, self.positions[drone_id], available_paths[drone_id][1][0]):
                available_paths = self.choose_connection_alternative(available_paths, drone_id)
            planned_moves[drone_id] = available_paths[drone_id][0]
        return planned_moves

    def apply_moves(self, planned_moves):
        """
        Apply the planned moves for each drone, updating their positions and routes.
        """
        for drone_id, move in planned_moves.items():
            if move is None:
                continue  # Drone does not move this turn
            next_hub = move[1][0]
            self.positions[drone_id] = next_hub
            self.routes[drone_id].append(next_hub)
            if next_hub == self.constellation._end_hub:
                self.finished.add(drone_id)

    def run(self):
        """
        Multi-Agent Path Finding (MAPF) algorithm to find paths for all drones to reach their destinations.
        """
        while len(self.finished) < self.constellation._nb_drones:
            planned_moves = self.choose_turn_moves()
            self.apply_moves(planned_moves)
        self.constellation._routes = self.routes
        return self.routes

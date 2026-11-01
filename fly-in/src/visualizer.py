import pygame
from src import Constellation, Hub, ZONE_COLORS


class Visualizer:
    def __init__(self, constellation: Constellation):
        self.constellation = constellation
        self._routes = self.constellation.get_routes()
        self.screen_w = 1920
        self.screen_h = 1080
        self.tick_interval = 1000
        self.constellation._start_hub.drone_count = self.constellation._nb_drones

    def play_simulation(self):
        pygame.init()
        self.screen = pygame.display.set_mode((self.screen_w, self.screen_h))
        self.font = pygame.font.SysFont("Arial", 28)
        self.clock = pygame.time.Clock()
        self.last_tick = pygame.time.get_ticks()
        replay_button = pygame.Rect(self.screen_w - 130, self.screen_h - 50, 120, 40)
        pygame.display.set_caption("FlY-IN Visualizer")
        running = True
        route_indices = self.get_initial_route_indices()
        previous_drone_positions = self.get_initial_drone_positions()
        drone_positions = self.get_initial_drone_positions()
        log_index = 0
        self.playing = True
        self.finished = False
        first_frame = True
        while running:
            self.clock.tick(60)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    if self.finished and replay_button.collidepoint(event.pos):
                        self.finished = False
                        self.playing = True
                        self.last_tick = pygame.time.get_ticks()
                        route_indices = self.get_initial_route_indices()
                        drone_positions = self.get_initial_drone_positions()
                        previous_drone_positions = self.get_initial_drone_positions()
                        log_index = 0
                        first_frame = True
                        self.constellation._start_hub.drone_count = self.constellation._nb_drones

            now = pygame.time.get_ticks()
            if now - self.last_tick >= self.tick_interval and self.playing and not self.finished:
                self.last_tick = now
                for hub in self.constellation._map.keys():
                    hub.drone_count = 0
                for drone_id, hubs in self._routes.items():
                    if not hubs:
                        continue
                    index = route_indices[drone_id]
                    if index < len(hubs):
                        current_hub = hubs[index]
                        if index < len(hubs):
                            current_hub = hubs[index]
                        previous_drone_positions[drone_id] = drone_positions[drone_id]
                        if current_hub is not None:
                            drone_positions[drone_id] = current_hub
                        route_indices[drone_id] = (index + 1)
                for hub in drone_positions.values():
                    hub.drone_count += 1
                print(self.constellation._log_route[log_index])
                log_index += 1
                if all(route_indices[drone_id] >= len(hubs) for drone_id, hubs in self._routes.items()):
                    self.playing = False
                    self.finished = True
                    print("Simulation finished.")
            progress = (now - self.last_tick) / self.tick_interval
            progress = min(progress, 1)
            self.screen.fill((0, 0, 0))
            self.draw_static_graph(self.constellation._map)
            self.draw_drone_pulses(previous_drone_positions, drone_positions, progress)
            for hub in self.constellation._map.keys():
                hub.draw(self.screen, self.world_to_screen, self.font)
            if self.finished:
                pygame.draw.rect(self.screen, (0, 128, 0), replay_button)
                text_surface = self.font.render("Replay", True, (255, 255, 255))
                text_rect = text_surface.get_rect(center=replay_button.center)
                self.screen.blit(text_surface, text_rect)
            pygame.display.flip()
            if first_frame:
                first_frame = False
                pygame.time.delay(1000)
        pygame.quit()


    def get_initial_route_indices(self):
        return {drone_id: 0 for drone_id in self.constellation._routes.keys()}

    def get_initial_drone_positions(self):
        return {drone_id: self.constellation._start_hub for drone_id in self.constellation._routes.keys()}

    def draw_drone_pulses(self, previous_drone_positions, drone_positions, progress):
        for drone_id, current_hub in drone_positions.items():
            previous_hub = previous_drone_positions[drone_id]
            if current_hub is None or previous_hub is None:
                continue
            x1, y1 = self.world_to_screen(previous_hub.x, previous_hub.y)
            x2, y2 = self.world_to_screen(current_hub.x, current_hub.y)
            x = int(x1 + (x2 - x1) * progress)
            y = int(y1 + (y2 - y1) * progress)
            pygame.draw.circle(self.screen, (255, 0, 0), (x, y), 5)

    def world_to_screen(self, x, y):
        padding = 84
        vertical_scale = 1.3
        hubs = list(self.constellation._map.keys())
        min_x = min(hub.x for hub in hubs)
        max_x = max(hub.x for hub in hubs)
        min_y = min(hub.y for hub in hubs)
        max_y = max(hub.y for hub in hubs)

        world_w = max_x - min_x
        world_h = max_y - min_y

        if world_w == 0:
            world_w = 1
        if world_h == 0:
            world_h = 1

        usable_w = self.screen_w - 2 * padding
        usable_h = self.screen_h - 2 * padding

        multiplier = min(usable_w / world_w, usable_h / world_h)

        screen_x = padding + (x - min_x) * multiplier
        screen_y = padding + (y - min_y) * multiplier * vertical_scale
        # Convert world coordinates to screen coordinates
        return int(screen_x), int(screen_y)

    def draw_static_graph(self, graph: dict[Hub, list[tuple[Hub, int]]]):
        for hub in graph:
            x, y = self.world_to_screen(hub.x, hub.y)
            for neighbor, limit in graph[hub]:
                nx, ny = self.world_to_screen(neighbor.x, neighbor.y)
                dx = nx - x
                dy = ny - y
                length = max((dx ** 2 + dy ** 2) ** 0.5, 1)

                offset_x = (dy / length)
                offset_y = (-dx / length)

                spacing = 5
                start_offset = -(limit - 1) / 2

                for i in range(limit):
                    offset = (start_offset + i) * spacing

                    start = (
                        x + offset * offset_x,
                        y + offset * offset_y
                    )
                    end = (
                        nx + offset * offset_x,
                        ny + offset * offset_y
                    )

                    pygame.draw.line(self.screen, (255, 255, 255), start, end, 1)



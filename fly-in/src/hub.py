from .macros import Color, Zone, COSTS, COLOR_CODES, ZONE_COLORS
import pygame

class Features():
    def __init__(
        self,
        max_drones: int = 1,
        color: Color = Color.WHITE,
        zone: Zone = Zone.NORMAL,
        cost: int = COSTS[Zone.NORMAL],
        max_link_capacity: int = 1,
    ):
        self.max_drones = max_drones
        self.color = color
        self.zone = zone
        self.max_link_capacity = max_link_capacity
        self.cost = COSTS[zone]

    @classmethod
    def from_list(cls, features_list: list[str]) -> "Features":
        features = cls()
        for feature in features_list:
            if feature.startswith("max_drones="):
                features.max_drones = int(feature.split("=")[1])
            elif feature.startswith("color="):
                color_value = feature.split("=")[1]
                features.color = Color(color_value)
            elif feature.startswith("zone="):
                zone_value = feature.split("=")[1]
                features.zone = Zone(zone_value)
            elif feature.startswith("max_link_capacity="):
                features.max_link_capacity = int(feature.split("=")[1])
            else:
                raise ValueError(f"Unknown feature: {feature}")
        features.cost = COSTS[features.zone]
        return features


class Hub:
    def __init__(self, name: str, x: int, y: int, features: Features):
        self.name = name
        self.x = x
        self.y = y
        self.features = features
        self.drone_count = 0

    def __repr__(self) -> str:
        return f"Hub(name={self.name!r}, x={self.x}, y={self.y})"

    def __str__(self) -> str:
        return f"{self.name}"

    @classmethod
    def from_line(cls, line: str) -> "Hub":
        name = line.split()[1]
        x = int(line.split()[2])
        y = int(line.split()[3])
        features_list = [feature.strip("[]") for feature in line.split()[4:]]
        features = Features.from_list(features_list) # Goal hub cannot have drones
        return cls(name, x, y, features)

    def count_label(self) -> str:
        if self.name != "start" and self.name != "goal":
            return f"{self.drone_count}/{self.features.max_drones}"
        else:
            return f"{self.drone_count}"

    def count_label_color(self) -> tuple[int, int, int]:
        if (self.drone_count < self.features.max_drones
                or self.name == "start" or self.name == "goal"):
            return (0, 255, 0)  # Green
        elif self.drone_count == self.features.max_drones:
            return (255, 255, 0)  # Yellow
        else:
            return (255, 0, 0)  # Red

    def get_truncated_name(self, max_length: int = 8) -> str:
        if len(self.name) > max_length:
            first_part = self.name[:max_length // 2]
            last_part = self.name[-(max_length // 2 - 1):]
            return f"{first_part}.{last_part}"
        return self.name

    def draw(self, screen, world_to_screen, font: pygame.font.Font):
        x, y = world_to_screen(self.x, self.y)
        w = screen.get_width()
        diam = w / 20
        zone_s = diam * 4/3

        color = COLOR_CODES[self.features.color]
        pygame.draw.circle(screen, (0, 0, 0), (x, y), diam // 2)
        pygame.draw.circle(screen, color, (x, y), diam // 2, 3)
        pygame.draw.rect(screen, ZONE_COLORS[self.features.zone], (x - zone_s // 2, y - zone_s // 2, zone_s, zone_s), 2)
        count_surface = font.render(self.count_label(), True, self.count_label_color())
        count_rect = count_surface.get_rect(center=(x, y))
        screen.blit(count_surface, count_rect)
        label = font.render(self.get_truncated_name(), True, (255, 255, 255))
        label_rect = label.get_rect(center=(x, y + zone_s // 2 + font.get_height() // 2))
        screen.blit(label, label_rect)


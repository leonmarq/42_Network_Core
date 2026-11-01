from enum import Enum

Source_Files = {
    "easy": {
        "01_linear_path": "maps/easy/01_linear_path.txt",
        "02_simple_fork": "maps/easy/02_simple_fork.txt",
        "03_basic_capacity": "maps/easy/03_basic_capacity.txt",
    },
    "medium": {
        "01_dead_end_trap": "maps/medium/01_dead_end_trap.txt",
        "02_circular_loop": "maps/medium/02_circular_loop.txt",
        "03_priority_puzzle": "maps/medium/03_priority_puzzle.txt"
    },
    "hard": {
        "01_maze_nightmare": "maps/hard/01_maze_nightmare.txt",
        "02_capacity_hell": "maps/hard/02_capacity_hell.txt",
        "03_ultimate_challenge": "maps/hard/03_ultimate_challenge.txt"
    }
}


class Color(Enum):
    RED = "red"
    GREEN = "green"
    BLUE = "blue"
    YELLOW = "yellow"
    GRAY = "gray"
    ORANGE = "orange"
    WHITE = "white"
    CYAN = "cyan"
    PURPLE = "purple"
    BROWN = "brown"
    LIME = "lime"
    MAGENTA = "magenta"
    GOLD = "gold"


COLOR_CODES = {
    Color.RED: (255, 80, 80),
    Color.GREEN: (80, 255, 80),
    Color.BLUE: (80, 80, 255),
    Color.YELLOW: (240, 220, 80),
    Color.GRAY: (200, 200, 200),
    Color.ORANGE: (255, 165, 60),
    Color.WHITE: (255, 255, 255),
    Color.CYAN: (80, 255, 255),
    Color.PURPLE: (200, 80, 255),
    Color.BROWN: (150, 75, 0),
    Color.LIME: (0, 255, 0),
    Color.MAGENTA: (255, 0, 255),
    Color.GOLD: (255, 215, 0),
}


class Zone(Enum):
    """
    Represents a zone in the constellation map.

    Zone types:
        normal:
            Standard zone. Entering this zone costs 1 turn.
            This is the default zone type.

        blocked:
            Inaccessible zone. Drones must not enter or pass through this zone.
            Any path that uses a blocked zone is invalid.

        restricted:
            Sensitive or dangerous zone. Entering this zone costs 2 turns.

        priority:
            Preferred zone. Entering this zone costs 1 turn, but this zone should
            be prioritized when choosing between possible paths.
    """
    RESTRICTED = "restricted"
    NORMAL = "normal"
    PRIORITY = "priority"
    BLOCKED = "blocked"


COSTS = {
    Zone.NORMAL: 1,
    Zone.BLOCKED: float("inf"),  # Blocked zones are inaccessible
    Zone.RESTRICTED: 2,
    Zone.PRIORITY: 1,
}

ZONE_COLORS = {
    Zone.NORMAL: (200, 200, 200),      # Gray
    Zone.BLOCKED: (255, 0, 0),         # Red
    Zone.RESTRICTED: (255, 165, 0),    # Orange
    Zone.PRIORITY: (0, 255, 0),        # Green
}

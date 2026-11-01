import curses

class Selector:
    def __init__(self, options):
        self.options = options
        self.current_selection = 0

    def start(self):
        self.screen = curses.initscr()
        curses.noecho()
        curses.cbreak()
        self.screen.keypad(True)

    def stop(self):
        curses.nocbreak()
        self.screen.keypad(False)
        curses.echo()
        curses.endwin()

    def draw(self):
        self.screen.clear()
        for idx, option in enumerate(self.options):
            if idx == self.current_selection:
                self.screen.addstr(idx, 0, f"> {option}", curses.A_REVERSE)
            else:
                self.screen.addstr(idx, 0, f"  {option}")
        self.screen.refresh()

    def navigate(self):
        while True:
            key = self.screen.getch()
            if key == curses.KEY_UP and self.current_selection > 0:
                self.current_selection -= 1
            elif key == curses.KEY_DOWN and self.current_selection < len(self.options) - 1:
                self.current_selection += 1
            elif key in (curses.KEY_ENTER, ord('\n')):
                return self.options[self.current_selection]
            self.draw()

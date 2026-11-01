from src import Constellation, Source_Files, Visualizer, Scheduler

DIFFICULTY_KEYS = {
    "a": "easy",
    "b": "medium",
    "c": "hard",
    # "d": "challenger"
}


def choose_constellation() -> str:
    for key, difficulty in DIFFICULTY_KEYS.items():
        print(f"{key}: {difficulty}")

        files = list(Source_Files[difficulty].items())
        for i, (file_key, file_path) in enumerate(files, start=1):
            print(f"  {i}: {file_key} ({file_path})")

    while True:
        choice = input("\nChoose constellation: ").strip().lower()

        if len(choice) < 2:
            print("Use format like 'a1' where 'a' is the difficulty and '1' is the file number.")
            continue

        difficulty_key = choice[0]
        index_text = choice[1:]

        if difficulty_key not in DIFFICULTY_KEYS:
            print("Unknown difficulty key. Please choose a valid one.")
            continue

        if not index_text.isdigit():
            print("File number must be a digit. Please try again.")
            continue

        difficulty = DIFFICULTY_KEYS[difficulty_key]
        files = list(Source_Files[difficulty].items())
        index = int(index_text) - 1

        if index < 0 or index >= len(files):
            print("File number out of range. Please choose a valid one.")
            continue

        name, file_path = files[index]
        print(f"Selected constellation: {name} ({file_path})")
        return file_path

def launch_visualizer():
    file_name = choose_constellation()
    constellation = Constellation(file_name)
    scheduler = Scheduler(constellation)
    scheduler.run()
    visualizer = Visualizer(
        scheduler.constellation)
    visualizer.play_simulation()
    return visualizer

if __name__ == "__main__":
    visualizer = launch_visualizer()
    while True:
        print("choose an option:")
        print("r: replay simulation")
        print("m: choose a new constellation")
        print("q: quit")
        input_choice = input("Enter your choice: ").strip().lower()
        if input_choice == "r":
            visualizer.play_simulation()
        elif input_choice == "m":
            visualizer = launch_visualizer()
        elif input_choice == "q":
            print("Exiting the program.")
            break
        else:
            print("Invalid choice. Please try again.")

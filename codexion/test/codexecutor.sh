#!/bin/bash
EXE=./codexion

options=("A: Even Possible" "B: Uneven Possible" "C: Even Possible EDF" "D: Even Impossible" "E: Even Possible (200 coders)")

PS3="Please select an option: "

select opt in "${options[@]}"
do
	case $opt in
		"A: Even Possible")
			echo "You selected option A"
			$EXE 4 1000 350 200 250 3 100 fifo
			break
			;;
		"B: Uneven Possible")
			echo "You selected option B"
			$EXE 3 800 200 100 100 3 100 fifo
			break
			;;
		"C: Even Possible EDF")
			echo "You selected option C"
			$EXE 4 1000 350 200 250 3 100 edf
			break
			;;
		"D: Even Impossible")
			echo "You selected option D"
			$EXE 4 1000 350 50 400 3 100 fifo
			break
			;;
		"E: Even Possible (200 coders)")
			echo "You selected option E"
			$EXE 200 1000 350 200 300 3 100 fifo
			break
			;;
		*) echo "Invalid option $REPLY";;
	esac
done

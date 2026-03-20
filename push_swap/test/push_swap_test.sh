#!/bin/sh

PUSH_SWAP="../push_swap"
CHECKER="./checker_linux"

BENCH_100_RUNS=${BENCH_100_RUNS:-20}
BENCH_500_RUNS=${BENCH_500_RUNS:-10}

PASS_100=2000
GOOD_100=1500
EXCELLENT_100=700

PASS_500=12000
GOOD_500=8000
EXCELLENT_500=5500

ensure_tools() {
	if [ ! -x "$PUSH_SWAP" ] && [ ! -f "$PUSH_SWAP" ]; then
		echo "push_swap binary not found at $PUSH_SWAP"
		exit 1
	fi
	if [ ! -x "$CHECKER" ]; then
		echo "checker not found or not executable at $CHECKER"
		exit 1
	fi
	if ! command -v shuf >/dev/null 2>&1; then
		echo "shuf is required for random tests"
		exit 1
	fi
}

build_project() {
	make -C .. re || exit 1
}

count_ops() {
	if [ -z "$1" ]; then
		echo 0
	else
		printf "%s\n" "$1" | wc -l | tr -d ' '
	fi
}

run_checker() {
	if [ -z "$1" ]; then
		printf '' | $CHECKER $2
	else
		printf "%s\n" "$1" | $CHECKER $2
	fi
}

run_case() {
	ARG="$1"
	OPS=$($PUSH_SWAP $ARG)
	COUNT=$(count_ops "$OPS")
	RESULT=$(run_checker "$OPS" "$ARG")

	echo "ARGS   : $ARG"
	echo "RESULT : $RESULT"
	echo "COUNT  : $COUNT"
	echo

	if [ "$RESULT" != "OK" ]; then
		return 1
	fi
	return 0
}

classify_run() {
	COUNT="$1"
	PASS_LIMIT="$2"
	GOOD_LIMIT="$3"
	EXCELLENT_LIMIT="$4"

	if [ "$COUNT" -lt "$EXCELLENT_LIMIT" ]; then
		echo "excellent"
	elif [ "$COUNT" -lt "$GOOD_LIMIT" ]; then
		echo "good"
	elif [ "$COUNT" -lt "$PASS_LIMIT" ]; then
		echo "pass"
	else
		echo "fail"
	fi
}

benchmark() {
	SIZE="$1"
	RUNS="$2"
	PASS_LIMIT="$3"
	GOOD_LIMIT="$4"
	EXCELLENT_LIMIT="$5"

	i=1
	best=999999999
	worst=0
	total=0
	ok_runs=0
	pass_runs=0
	good_runs=0
	excellent_runs=0
	fail_runs=0
	check_failures=0

	echo "Benchmark: ${SIZE} numbers (${RUNS} runs)"
	while [ "$i" -le "$RUNS" ]
	do
		ARG=$(shuf -i 0-99999 -n "$SIZE" | tr '\n' ' ')
		OPS=$($PUSH_SWAP $ARG)
		COUNT=$(count_ops "$OPS")
		RESULT=$(run_checker "$OPS" "$ARG")

		if [ "$RESULT" = "OK" ]; then
			ok_runs=$((ok_runs + 1))
			[ "$COUNT" -lt "$best" ] && best=$COUNT
			[ "$COUNT" -gt "$worst" ] && worst=$COUNT
			total=$((total + COUNT))

			case "$(classify_run "$COUNT" "$PASS_LIMIT" "$GOOD_LIMIT" "$EXCELLENT_LIMIT")" in
				excellent) excellent_runs=$((excellent_runs + 1)) ;;
				good) good_runs=$((good_runs + 1)) ;;
				pass) pass_runs=$((pass_runs + 1)) ;;
				fail) fail_runs=$((fail_runs + 1)) ;;
			esac
		else
			check_failures=$((check_failures + 1))
		fi

		echo "run $(printf "%02d" "$i"): $RESULT, ops: $COUNT"
		i=$((i + 1))
	done

	echo
	echo "Summary for ${SIZE}:"
	echo "checker OK       : $ok_runs/$RUNS"
	echo "checker failures : $check_failures"
	if [ "$ok_runs" -gt 0 ]; then
		echo "best             : $best"
		echo "worst            : $worst"
		echo "avg              : $((total / ok_runs))"
	else
		echo "best             : n/a"
		echo "worst            : n/a"
		echo "avg              : n/a"
	fi
	echo "excellent (< $EXCELLENT_LIMIT): $excellent_runs"
	echo "good      (< $GOOD_LIMIT)     : $good_runs"
	echo "pass      (< $PASS_LIMIT)     : $pass_runs"
	echo "fail      (>= $PASS_LIMIT)    : $fail_runs"
	echo
}

echo "Building push_swap..."
build_project
ensure_tools

echo
echo "Fixed tests"
run_case "2 1" || exit 1
run_case "3 2 1" || exit 1
run_case "0 1 2 3" || exit 1
run_case "1 5 2 4 3" || exit 1
run_case "-3 9 0 -1 7" || exit 1
run_case "42" || exit 1
run_case "5 4 3 2 1" || exit 1

echo "Benchmark targets from subject:"
echo "100 numbers: excellent < $EXCELLENT_100, good < $GOOD_100, pass < $PASS_100"
echo "500 numbers: excellent < $EXCELLENT_500, good < $GOOD_500, pass < $PASS_500"
echo

benchmark 100 "$BENCH_100_RUNS" "$PASS_100" "$GOOD_100" "$EXCELLENT_100"
benchmark 500 "$BENCH_500_RUNS" "$PASS_500" "$GOOD_500" "$EXCELLENT_500"

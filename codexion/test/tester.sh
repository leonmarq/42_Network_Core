#!/usr/bin/bash
set -u

EXE=./codexion
FAILS=0

pass() {
	printf "✅ %s\n" "$1"
}

fail() {
	printf "❌ %s\n" "$1"
	((FAILS++))
}

cleanup_and_exit() {
	printf "\nInterrupted, stopping tester.\n" >&2
	rm -f "${out:-}" "${err:-}"
	exit 130
}

trap cleanup_and_exit INT TERM

run_timeout() {
	timeout "$@"
	status=$?

	if [ "$status" -eq 130 ] || [ "$status" -eq 143 ]; then
		cleanup_and_exit
	fi

	return "$status"
}

run_expect_success() {
	name="$1"
	seconds="$2"
	shift 2

	out="$(mktemp)"
	err="$(mktemp)"

	run_timeout "$seconds" "$EXE" "$@" >"$out" 2>"$err"
	status=$?

	if [ $status -eq 124 ]; then
		fail "$name: Timeout after $seconds seconds"
	elif grep -Fq "burned out" "$out" "$err"; then
		fail "$name: Unexpected burnout"
	elif [ $status -ne 0 ]; then
		fail "$name exited with status $status"
	else
		pass "$name"
	fi

	rm -f "$out" "$err"
}

run_expect_error() {
	name="$1"
	seconds="$2"
	expected="$3"
	shift 3

	out="$(mktemp)"
	err="$(mktemp)"

	run_timeout "$seconds" "$EXE" "$@" >"$out" 2>"$err"
	status=$?

	if [ $status -eq 124 ]; then
		fail "$name: Timeout after $seconds seconds"
	elif [ $status -eq 0 ]; then
		fail "$name Expected failure but got exit status 0"
	elif ! grep -Fq "$expected" "$out" "$err"; then
		fail "$name: Error output did not match expected"
		echo "Expected: $expected"
		echo "Got stdout:"
		cat "$out"
		echo "Got stderr:"
		cat "$err"
	else
		pass "$name"
	fi

	rm -f "$out" "$err"
}

run_expect_burnout() {
	name="$1"
	seconds="$2"
	shift 2

	out="$(mktemp)"
	err="$(mktemp)"

	run_timeout "$seconds" "$EXE" "$@" >"$out" 2>"$err"
	status=$?

	if [ "$status" -eq 124 ]; then
		fail "$name: Timeout after $seconds seconds"
	elif ! grep -Fq "burned out" "$out" "$err"; then
		fail "$name: Expected a coder to burn out"
		echo "Got stdout:"
		cat "$out"
		echo "Got stderr:"
		cat "$err"
	else
		pass "$name"
	fi

	rm -f "$out" "$err"
}

run_expect_burnout "single coder" 5 1 1000 450 200 300 3 100 fifo

run_expect_success "fifo possible" 5 42 1000 350 200 200 3 100 fifo

run_expect_success "edf possible" 5 42 1000 350 200 200 3 100 edf

run_expect_success "fifo possible uneven" 5 21 1000 200 200 100 3 100 fifo

run_expect_success "edf possible uneven" 5 21 1000 200 200 200 3 100 edf

run_expect_success "fifo possible 200 coders" 5 200 1000 350 150 200 3 100 fifo

run_expect_success "edf possible 200 coders" 5 200 1000 350 200 200 3 100 edf

run_expect_burnout "too big cooldown" 5 4 1000 450 200 400 3 200 fifo

run_expect_error "invalid scheduler reject" \
	 2 "scheduler has bad format, must be 'edf' or 'fifo'" \
	 4 1000 450 200 300 3 100 invalid

run_expect_error "invalid numeric argument reject" 2 "Error: one of the numbers has bad format" 4 tada 450 200 300 3 100 fifo

run_expect_error "negatives as arguments reject" 2 "Error: one of the numbers has bad format" 4 1000 -450 200 300 3 100 fifo

run_expect_error "too few arguments reject" 2 "Error: too few arguments" 4 1000 450 200 300 3 fifo

if [ $FAILS -eq 0 ]; then
	echo "All tests passed!"
	exit 0
else
	echo "$FAILS test(s) failed."
	exit 1
fi


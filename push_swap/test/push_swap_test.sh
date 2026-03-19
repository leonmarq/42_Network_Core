#!/bin/sh

PUSH_SWAP="../push_swap"
CHECKER="./checker_linux"

make -C .. re  || exit 1

test_case() {
	ARG="$1"
	OPS=$($PUSH_SWAP $ARG)
	COUNT=$(printf "%s\n" "$OPS" | wc -l | tr -d ' ')
	RESULT=$(printf "%s\n" "$OPS" | $CHECKER $ARG)

	echo "ARGS   : $ARG"
	echo "RESULT : $RESULT"
	echo "COUNT  : $COUNT"
	echo
}

echo "Fixed tests"
test_case "2 1"
test_case "3 2 1"
test_case "0 1 2 3"
test_case "1 5 2 4 3"
test_case "-3 9 0 -1 7"

echo "Random tests"
i=0
while [ $i -lt 5 ]
do
	ARG=$(shuf -i 0-999 -n 100 | tr '\n' ' ')
	OPS=$($PUSH_SWAP $ARG)
	COUNT=$(printf "%s\n" "$OPS" | wc -l | tr -d ' ')
	RESULT=$(printf "%s\n" "$OPS" | $CHECKER $ARG)

	echo "test $i => $RESULT, ops: $COUNT"
	i=$((i + 1))
done

best=999999
worst=0
total=0
i=0

while [ $i -lt 20 ]
do
	ARG=$(shuf -i 0-999 -n 100 | tr '\n' ' ')
	COUNT=$(../push_swap $ARG | wc -l | tr -d ' ')

	[ "$COUNT" -lt "$best" ] && best=$COUNT
	[ "$COUNT" -gt "$worst" ] && worst=$COUNT
	total=$((total + COUNT))
	i=$((i + 1))
done

echo "best: $best"
echo "worst: $worst"
echo "avg: $((total / 20))"

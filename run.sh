#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

EXEC="$DIR/tsg"

PILE=15

FINISH=false

echo "The pile has $PILE sticks."

while [ "$FINISH" = false ]; do
	echo "How many sticks to take?"
	read TAKE

	clang++ "$DIR/tsg.cpp" -std="c++14" -o "$EXEC" -DTAKE="$TAKE" -DPILE="$PILE"

	CODE=$?

	if [ "$CODE" -eq 0 ]; then
		RESULT=$(eval "$EXEC")

		WON=$(echo "$RESULT" | grep "won")

		if [ -n "$WON" ]; then
			FINISH=true
		else
			PILE=$(echo "$RESULT" | grep -Eo '[0-9]+')
		fi

		echo "$RESULT"
	else
		echo "The pile has $PILE sticks."
	fi
done

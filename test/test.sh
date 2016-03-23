#!/bin/sh

TEST_AGAINST=https://github.com/mfortin42/fillit.git
REGEN=true
MIN=1
MAX=10
HISDIR=/tmp/fillit-test
MYDIR=/tmp/fillit

BLACK="\033[0;30m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[1;33m"
BLUE="\033[0;34m"
MAGENTA="\033[0;35m"
CYAN="\033[0;36m"
WHITE="\033[0;37m"
END="\033[0m"

cd test

git clone $TEST_AGAINST $HISDIR

for arg in "$@"
do
	case "$arg" in
	--no-regen)
		REGEN=false
		;;
	-m*)
		MIN=$(echo $arg | cut -dm -f2)
		;;
	-M*)
		MAX=$(echo $arg | cut -dM -f2)
		;;
	esac
done

echo "Testing against version: https://github.com/mfortin42/fillit.git"
echo
make -s -C $HISDIR
PROJECT_DIR=$MYDIR make -s -C ../ rendu > /dev/null
make -s -C $MYDIR

echo $BLUE Range: $MIN $MAX $END
for i in $(seq $MIN $MAX)
do
	echo "Testing with $i tetriminos"
	if [ "$REGEN" = true ]; then
		../util/gen.pl $i > $i.tetris
	fi
	MY=$(time $MYDIR/fillit $i.tetris)
	HIS=$(time $HISDIR/fillit $i.tetris)
	echo My:"\t"$RED $MY $END
	echo His:"\t"$CYAN $HIS $END
	if [ ! "$MY" = "$HIS" ]; then
		echo $RED WRONG FOR $i.tetris $END
		exit 1
	else
		echo $GREEN OK $END
	fi
	echo
done

exit 0

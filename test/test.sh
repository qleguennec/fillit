#!/bin/sh

TEST_AGAINST=https://github.com/mfortin42/fillit.git
REGEN=true
BLACK="\033[0;30;40m"
RED="\033[0;31;40m"
GREEN="\033[0;32;40m"
YELLOW="\033[1;33;40m"
BLUE="\033[0;34;40m"
MAGENTA="\033[0;35;40m"
CYAN="\033[0;36;40m"
WHITE="\033[0;37;40m"
END="\033[0m"
cd test

if [ ! -d "fillit-test" ]; then
	git clone $TEST_AGAINST fillit-test
fi

if [ "$1" = "--no-regen" ]; then
	REGEN=false
else
	rm *.tetris
fi

echo "Testing against version: https://github.com/mfortin42/fillit.git"
echo
make -s -C fillit-test

for i in `seq 1 11`
do
	echo "Testing with $i tetriminos"
	if [ "$REGEN" = true ]; then
		../util/gen.pl $i > $i.tetris
	fi
	MY=$(/usr/bin/time -f "time elapsed:\t%E real,\t%U user,\t%S sys" ../fillit $i.tetris)
	HIS=$(/usr/bin/time -f "time elapsed:\t%E real,\t%U user,\t%S sys" fillit-test/fillit $i.tetris)
	echo My:"\t"$CYAN $MY $END
	echo His:"\t"$YELLOW $HIS $END
	if [ ! "$MY" = "$HIS" ]; then
		echo $RED WRONG FOR $i.tetris $END
	else
		echo $GREEN OK $END
	fi
	echo
done

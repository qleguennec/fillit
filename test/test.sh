TEST_AGAINST=https://github.com/mfortin42/fillit.git

if [ ! -d "fillit-test" ]; then
	git clone $TEST_AGAINST fillit-test
fi

echo "Testing against version: https://github.com/mfortin42/fillit.git"
make -s -C fillit-test
rm *.tetris

for i in `seq 1 8`
do
	echo "Testing with $i tetriminos"
	../util/gen.pl $i > $i.tetris 
done

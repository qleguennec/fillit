#! /usr/bin/perl

sub fill {
	my @tetri = ();
	my $x = 0;
	my $i = 0;
	my $j = 0;

	foreach $i (0 .. 3) {
		foreach $j (0 .. 3) {
			$tetri[$i][$j] = 0;
		}
	}
	$i = int(rand(4));
	$j = int(rand(4));
	$tetri[$i][$j] = 1;
	while ($x < 3)
	{
		$i = int(rand(4));
		$j = int(rand(4));
		if ($tetri[$i][$j] == 0 && (
			($j + 1 < 4  && $tetri[$i][$j + 1] == 1) ||
			($j - 1 >= 0 && $tetri[$i][$j - 1] == 1) ||
			($i + 1 < 4  && $tetri[$i + 1][$j] == 1) ||
			($i - 1 >= 0 && $tetri[$i - 1][$j] == 1)
		)) {
			$tetri[$i][$j] = 1;
			$x++;
		}
	}
	foreach $i (0 .. 3) {
		foreach $j (0 .. 3) {
			if ($tetri[$i][$j] == 1) {
				print "#";
			}
			else {
				print ".";
			}
		}
		print "\n";
	}
}

my $i = 0;
my $num_args = $#ARGV + 1;
if ($num_args != 1) {
    print "Usage: gen.pl nb_tetris\n";
    exit;
}
my $n = int($ARGV[0]);
foreach $i (1 .. $n) {
	fill();
	if ($i != $n) {
		print "\n";
	}
}

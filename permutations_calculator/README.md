# Simple permutation calculator

* Compile it with `gcc perm_calc.c -o perm_calc`
* Run it using `perm_calc [STACK SIZE]`

## Output

The program will create a folder named `[STACK SIZE]_[PERMUTATIONS NUMBER]`.
In that folder you will find one file for each permutation.

The program is intended to be used in order to feed the [speed_tester](https://github.com/mikysett/push_swap_speed_tester).

## Disclamer

* This program have a time complexity of O(n!), so it will work properly only with very small stack sizes (up to 6! or 7!).
* The number created are always from 1 to stack size, no 0 and no negative numbers.
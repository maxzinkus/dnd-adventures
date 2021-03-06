Dice
====

Reasonably fast dice roller for D&D. Basically realtime on my laptop up to 2.5 million dice (e.g. `2500000d20`)
and if your players are dealing that much damage, uh.. nerf them.

# Usage

Input as `<num>d<faces><mod>`:

```
  <num>   := A positive decimal number
  <faces> := A decimal number of faces in {4, 6, 8, 10, 12, 20, 100}
  <mod>   := empty, or <op><num>
  <op>    := An operator in {+, -} (for addition and subtraction)
```

For those who don't like EBNF, two examples: `3d6` or `1d20+4`.

"Enter" on an empty line repeats the last roll, printing both the roll
and the result. Control-d to exit.

To view pretty histograms of dice roll outputs , `make test`

# Examples

```
$ ./dice
> 1d20
15
> 4d4
11
> 3d6+3
14
>
```

```
$ ./dice_test
Test mode enabled, iterations = 1000000
> 1d20
  1:0.049928 |****
  2:0.049775 |****
  3:0.050046 |*****
  4:0.050101 |*****
  5:0.049866 |****
  6:0.050479 |*****
  7:0.050144 |*****
  8:0.049790 |****
  9:0.049701 |****
 10:0.050230 |*****
 11:0.050349 |*****
 12:0.050133 |*****
 13:0.050432 |*****
 14:0.049718 |****
 15:0.049964 |****
 16:0.049692 |****
 17:0.050115 |*****
 18:0.049619 |****
 19:0.049907 |****
 20:0.050011 |*****
Mean: 10.496346
> 4d4
  1:0.000000 |
  2:0.000000 |
  3:0.000000 |
  4:0.003934 |
  5:0.015568 |*
  6:0.038714 |***
  7:0.077658 |*******
  8:0.121096 |************
  9:0.155764 |***************
 10:0.172476 |*****************
 11:0.156308 |***************
 12:0.121423 |************
 13:0.078301 |*******
 14:0.039095 |***
 15:0.015669 |*
 16:0.003994 |
Mean: 10.005516
> 3d6+3
  4:0.000000 |
  5:0.000000 |
  6:0.004637 |
  7:0.013942 |*
  8:0.027642 |**
  9:0.046244 |****
 10:0.068918 |******
 11:0.097340 |*********
 12:0.115132 |***********
 13:0.125104 |************
 14:0.125485 |************
 15:0.116538 |***********
 16:0.096947 |*********
 17:0.069798 |******
 18:0.046348 |****
 19:0.027546 |**
 20:0.013664 |*
 21:0.004715 |
Mean: 10.503115
> 
```

# Notes

It might be fun to use a seeded generator and save the seed, then have code that takes in a seed and a transcript
of rolls and verifies they were generated using that seed.

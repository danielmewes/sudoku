# What

A rudimentary Sudoku solver. While it is simple, it seems to be able to solve even the hardest Sudokus with ease.

It reads a Sudoku in the ["Simple Sudoku" file format](http://www.sudocue.net/fileformats.php).

I wrote this in a single evening as an experiment, so it's not particularly polished.

## Background

I had been solving some Sudoku's in the past days for fun. I was using the Android App "Andoku 3", which has a feature that allows you to conveniently mark possible candidates on a field.
After a few rounds, I noticed that I had started to use a fairly systematic approach for solving Sudokus by noting and systematically eliminating candidates. So I started to wonder if I could put my mental process into code. Turns out the answer is yes. :)

## Used strategies

I just made these up, so they might have different more common names.

* `eliminateConflicts` Eliminate candidates that would generate a conflict with an already resolved field.
* `resolveRequired` Resolve fields for which we *must* pick a certain candidate to complete a row / column / 3x3 cell.
* `guessOne` Select the field with the smallest number of candidates, and just assume the first one. Then continue recursively. If this results in a conflict, eliminate the candidate.

Most simple Sudokus that don't require guessing can be solved by the first two strategies alone.

# Build instructions

```
$ cd sudoku
$ make
```

# Example run

```
$ ./sudoku examples/unsolvable1.ss
Input:
1..|9.7|..3
.8.|...|.7.
..9|...|6..
-----------
..7|2.9|4..
41.|...|.95
..8|5.4|3..
-----------
..3|...|7..
.5.|...|.4.
2..|8.6|..9
-----------

Solving:
...
Guessing 2,1=3 (depth=0)
...
Guessing 3,2=2 (depth=1)
.....
Guessing 1,2=4 (depth=2)
.....
Made a wrong guess, but learnt something from it.
....

Result:
164|957|283
385|621|974
729|438|651
-----------
537|289|416
412|763|895
698|514|327
-----------
843|195|762
956|372|148
271|846|539
-----------

Solved it :)
```

# TODO

* Better error handling (stop using asserts for it)
* `--help` option etc.
* A verbose "single step" output mode?

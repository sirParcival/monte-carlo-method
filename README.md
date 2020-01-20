**MONTE-CARLO-METHOD**





C language implementation of Monte Carlo Method on example of rabbits and wolves
on the island.





***Installing instruction***
To build project you need use those commands:






`git clone https://gitlab-stud.elka.pw.edu.pl/rkossak/monte-carlo-method.git`

`cd monte-carlo-method`

`mkdir build`

`cd build`

`cmake install ../`


`make`

`sudo make install`

**USAGE**

To use program you need to run this:

`monte_carlo_method /path/to/your/input/file.* /destination/of/output.csv`

***Attention:***

Your input file can be any of text formats, but it should stay looks like:

key: value

key: value

key: value

...

P.S. You are not supposed to change "key" names. In case you change it just know that program won't work correctly.


**OUTPUT**

 
| Week | Wolves density | Rabbits density |
| ---- | -------------- | --------------- |
| 1 | 0.2 | 1.0 |
| 2 | 0.2 | 1.2 |


***TESTS***

At 0 rabbits, all wolves die. (file: rabbits_equal_zero.txt)

At 0 wolves, rabbits breed.                                                                                       (file: wolves_equal_zero.txt)

With insufficient rabbits, wolves die.                                                                            (file: not_enough_rabbits.txt)

With an insufficient number of wolves, rabbits breed very quickly.                                                (file: not_enough_wolves.txt)

With too many wolves, the number of rabbits will decrease sharply, thereby leading to the destruction of wolves.  (file: too_much_wolves.txt)

*All test files placed in folder tests*


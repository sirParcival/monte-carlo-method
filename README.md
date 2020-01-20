**MONTE-CARLO-METHOD**





C language implementation of Monte Carlo Method on example of rabbits and wolves
on the island.





***Installing instruction***
To build project you need use those commands:







`mkdir build`

`cd build`

`cmake install ../`


`make`

`sudo make install`

**USAGE**

To use program you need to run this:

`monte_carlo_method /path/to/your/input/file.* /destination/of/output.csv`

***Attention:***

Your input file may be any of text formats, but it should stay looks like:

key: value

key: value

key: value

...

P.S. You are not supposed to change "key" names. In case you change it just know that program won't work correctly.

***TESTS***

At 0 rabbits, all wolves die.

At 0 wolves, rabbits breed.

With insufficient rabbits, wolves die.

With an insufficient number of wolves, rabbits breed very quickly.

With too many wolves, the number of rabbits will decrease sharply, thereby leading to the destruction of wolves.


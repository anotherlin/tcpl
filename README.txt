Solutions for "The C Programming Language", 2nd Edition, Kernighan and Ritchie.

Lin Ke-Fong (another_lin@yahoo.com)

I read the book a while ago and did most of the exercises, this was a copy from
my university's library. When I finally bought it, I figure out it would be fun
to do them all seriously.

The solutions are written trying to use the same style as the book. They follow
chapter ordering and try not to use features described later. I have developed
them using Linux and gcc but they have also been tested on Mac OS X and Windows
using XCode and Visual C++. Exercises are command line oriented, taking inputs
from file redirection most of the time.

When possible, you should compile in strict ANSI mode, with all warnings on and
maximum optimization. Warnings even if sometimes more annoying than really
useful, may still point genuine problems. A lot of exercises are about writing
simplified or even full versions of C standard library functions. Hence there 
can be clashes at compilation or linking. Compiling in strict ANSI mode will 
avoid most problems, even if the compiler or linker may still continue to 
complain a bit. On BSD systems and Mac OS X (Darwin is a BSD), you will also 
need to define the _ANSI_SOURCE macro. Moreover, there can still be issues with
intrinsic (built-in) functions: warnings for gcc but you will have to switch 
them off with Visual C++. Enabling optimizations permit further error checking
as the compiler does a more detailed dataflow analysis. However, floating-point
computations (exercise 2-1) may end up wrong depending of the compiler and 
processor.

Here are some examples of compilation commands:

GNU C:

	gcc -ansi -Wall -pedantic -O3

GNU C (BSD or Mac OS X):

	gcc -ansi -Wall -pedantic -D_ANSI_SOURCE -O3

Intel C Compiler:

	icc -strict-ansi -w2 -fast

Microsoft Visual C (no intrinsic):

	cl /Ox /Oi- /Za /Wall

See compilers' manuals for full details.

Exercises of chapter 8 won't compile at all with Visual C++. However, you can 
make the first four of them work by commenting the unistd.h includes.

You may also want to check "The C Answer Book" by Clovis L. Tondo and Scott E.
Gimpel. Or the website maintained by Richard Heathfield:

http://users.powernet.co.uk/eton/kandr2/

To end up, I wish to thank all my friends and relatives.

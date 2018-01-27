# CS 376 Lab 4: `make` Utility

This laboratory explores make, a utility for doing selective recompilation. In addition, we review C header files, compilation, and linking.

You will require a separate sheet of paper to record intermediate results.

This lab has a total of 100 possible points.



### Objectives

Upon completion of the laboratory exercise, you will be able to do the following:

- Explain the purpose and use of C header files.
- Create a program containing multiple source files; and compile the source files and link the object files.
- Draw a dependency tree for various compilation modules.
- Write, debug, and test a makefile for selective compilation using the make utility.

**You should work with a partner throughout this lab; partner and seating assignments are shown at the front of the lab. Person 1 is listed first; Person 2 is listed second. If your partner has not shown up by the end of the minilecture, see your instructor—an attempt will be made to match you with another partnerless student.**

### Preliminaries (Person 1)

Please log on to the Debian VM as the **basic** user.

Next, clone the `lab4` repository and enter the `lab4` directory:

```sh
git clone https://github.com/up-cs376/lab4.git
cd lab4
```

### Part 1: Simple build (Person 1 at keyboard, Person 2 recording results)

(1) List the contents of your sources directory:

---

(2) Run the command `make test1` and list all the commands executed from running the above command

---

(3) List all the files that were created

---

(4) Execute `./test1`. What is the output?

---

(5) Examine the file `makefile`. From your understanding of the `make` program, draw the dependency tree that it denotes. (The _dependency tree_ should look like those on today's online resource **make.pdf**)

---

(6) Type `make test1` again. What command(s) does it execute? Why?

---

(7) Use vim to modify the source file, `test1.c`. Have it print "easy" in place of "simple". Now type `make test1` again. What command(s) does it execute? Why?

---

(8) Type `make test1` again. What command(s) does it execute? Why?

(9) Type the following commands and report what command(s) it executes, and explain why. (If you don't know what the `touch` command does, if may be useful to use `man` to find out. Note that we have used `touch` before to create new files, but this time you are using `touch` on an existing file.)

```sh
touch test1.o
make test1
```

---

(10) **Predict** what will happen when you type:

```sh
touch test1.c
make test1
```

---

(11) Now execute the command and note any difference between your prediction and the actual behavior:

```sh
touch test1.c
make test1
```

---

(12) Add the four lines:

```text
# this defines the command for cleaning up
# all generated files
clean:
        /bin/rm -f *.o test1
```

to the end of the **makefile** (where the character before the /bin/rm is a single TAB character). The first two lines contain comments; the third denotes the dependencies; and the fourth contains the command to perform the &quot;cleaning&quot; action.

Now type make clean and confirm that the all &quot;.o&quot; files and the executable file test1 have gone away. Have they? (circle answer) YES /   NO

**Checkpoint 1 [20 points]: Show your lab instructor/assistant your answers to the above questions.**


### Part 2: Modifying the sources (Person 2 at keyboard, Person 1 recording results)

1. Create an empty file, `test1.h`.
1. Move the definition of the constant (macro) `SIZE` from `test1.c` to `test1.h`. 
(That is, copy the line into `test1.h` and delete it from `test1.c`.)
1. Add the line `#include "test1.h"` after the other `#include`-line in `test1.c`.
Don't forget to place quotations around the file name.

Declarations that test1.c wants to make visible to other modules are put in its &quot;.h&quot; or _header_ files. Using header files is a standard programming style for the C language. As a result, the entire program consists of a collection of files that may be independently written, debugged, compiled, and linked together. In our example,

- `test1.c` has `#include "test1.h` to ensure that external definitions in the &quot;.h&quot; file are consistent with internal definitions in the ".c" file.
- Other files that need to call functions defined in `test1.c` will `#include "test1.h"`.
- Then later, the linker combines the respective ".o" files into a single executable file.

4
. Type `make test1`. Because you had just done a `make clean`, this should rebuild the executable file test1 from it sources again. Does it? 

(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---

5
. Does the program test1 run just as it did before?

(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---

6
. Modify `test1.h` so that `SIZE` has the value `5`; rebuild (i.e., type `make test1`). Does the execution of `test1` reflect the change just made to `test1.h`?

(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---

If so, explain why. If not, tell what change(s) must be made to the `makefile` so that it does print the right value, make those changes, and confirm that they work.

---

7
. Add the call `printPresident();` to `main` in `test1.c` just before the `return` statement. Also, add the line `#include "president.h` to the list of #includes.


8
. Create a file named `president.c` that defines the function `printPresident` as follows:


```c

#include <stdio.h>
#include "president.h"

void printPresident(void) {
  printf("My favorite president in history is _xxx_.\n");
}
```

where you replace "_xxx_" with the name of your favorite president.


9
. Create a file named `president.h` to have just the `extern` declaration (note that `extern` is optional when declaring fuctions, but required for global variables, which aren't a good programming practice anyway).

```c
extern void printPresident(void);
```

10
. Things are now set up in the "standard" way:

- the declaration or prototype of `printPresident` (which is just the function header) is in the ".h" file
- the definition of `printPresident` (which includes the body) in the ".c" file

11
. If you type `make test1` now, you will get some errors. Make the modifications to the `makefile` so that all build-commands are correct, and so that all dependencies are properly specified. Draw the dependency tree for the various compilation units below:

---


**Checkpoint 2 [20 points]: Show your lab instructor/assistant your answers to the above questions; also show your instructor/assistant your makefile and that it successfully compiles a test1 executable.**

### Part 3: Make variables (Person 1 at keyboard, Person 2 recording results)


##### What are make variables?

The `make` utility allows for some parts of the `makefile` to be parameterized
and optionally supplied at runtime through the use of _make variables_.

_make variables_ can be defined in three places:

- On the command-line when make is invoked, as in `make myCount=50 test1`.
- In the makefile itself on a line such as `myCount = 50`.
- Taken from an environment variable (not covered in this lab).

Make variables (such as `myVar`) are referenced using the syntax `$(myVar)`.
Astute readers will notice the similarity to shell variable interpolation,
which uses the syntax `${myVar}`. The difference is that while the shell
uses curly braces, `make` uses parenthesis.

For this section, we will use a little-known feature of GNU make known
as _makefile precedence_. Run the following command

```sh
cp makefile GNUmakefile
```

The above command will copy `makefile` to `GNUmakefile` which will override
the default makefile when running the `make` command.


##### Using make variables

Make supports some well-known built-in variables. These are:

Variable | Used for
-------- | --------
CPPFLAGS | C pre-processor flags (for custom include paths, -I /path/to/headers, et cetera)
CC       | Default C compiler (executable)
CFLAGS   | Options to pass to C compiler
CXX      | Default C++ compiler (executable)
CXXFLAGS | Options to pass to C++ compiler
LDFLAGS  | Options to pass to linker, for example: -L /path/to/libraries -l nameoflibrary

`CC` is usually set to `cc` which is an alias to `gcc` in most cases
`CXX` is sually set to `g++`

1
. Change the compile rule in `GNUmakefile` from `gcc` to `$(CC) $(CFLAGS)`

2
. Perform a `make clean` and a `make test1` to ensure that things still build.  Do they?


(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---

3
. Perform a `make clean` and a `make CFLAGS="-g" test1` to compile with debug symbols.  Does it?


(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---


4
. This time, set CFLAGS as an environment variable

```sh
export CFLAGS="-g -O4"
make clean
make test1
```

(The above switch is big-"Oh" and the number four.)

Did this work?

(circle answer)&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; NO 

---

5
. Another place where variables are used is in specifying the set of ".o" files that link together to form an executable, as in

```make
OFILES = myExec.o helper.o util.o
 ...
myExec: $(OFILES)
     $(CC) -o myExec $(OFILES)
```

In this way, the set of object files is specified in one place rather than in two, as in:

```make
myExec: myExec.o helper.o util.o
     $(CC) -o myExec myExec.o helper.o util.o
```

Using a variable helps keep the dependencies consistent with the actual object files that are used to build the executable.

6
. Change your makefile so that all of the ".o" files are defined with a make variable called `OFILES`. Then, do a `make clean` and then a `make test1` to ensure that it still builds properly.

**Checkpoint 3 [20 points]: Show your lab instructor/assistant your answers to the above questions; let your instructor/assistant examine your makefile; show your instructor/assistant the results of doing a "make".**



### Part 4: Pattern-rules and built-in rules (Person 2 at keyboard, Person 1 recording results)

`make(1)` has a number of built-in rules that make it possible to reduce the verbosity of your `makefile`.

Run the following command and look at its output:

```sh
make -p
```

In particular, look for the following defintions:

```make
???COMPILE.C = $(CC) $(CFLAGS) $(CPPFLAGS)
LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH)

%: %.o
        $(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.o: %.c
        $(COMPILE.c) $(OUTPUT_OPTION) $<
```

The patterns use % characters to make wildcard patterns.
The `%.o: %.c` rule above is a automatic compilation rule.
If you had a file called `myfunc.c` and to typed `make myfunc.o`,
then `make` would be able to compile `myfunc.c` to `myfunc.o`
_with no additional information_!

The other new syntax is the special $ variables.  There are several very useful ones
(see 10.5.3 Automatic Variables in the GNU make manual):

Variable | Used for
-------- | --------
$@       | Name of the current target
$<       | Name of the first prerequisite
$^       | List of all the prerequisites

Another interesing property of makefiles is that it is possible to list only targets and preqrequisites
_with no rules_. For example:

```make
file1:

file1.o: file1.c header1.h header2.h
```

The above `makefile` is sufficient to compile the `file1` executable simply by typing `make`.


For this part of the lab, rewrite your `GNUmakefile` to compile your program using **only the built-in rules**.

Your program should compile using only `make`.


**Checkpoint 4 [20 points]: Show your lab instructor/assistant new makefile and that you are still able to create a working executable, test1.**

### Part 5: Set up your own makefile (Person 1 at keyboard)

The subdirectory `lastTest` contains a set of source files that do not have a makefile.
Change into that directory and create a `makefile` such that:

- Each &quot;.o&quot; file gets built whenever its &quot;.c&quot; file changes.
- Each &quot;.o&quot; file gets rebuilt whenever a &quot;.h&quot; file changes that is #included (either directly or indirectly) by its &quot;.c&quot; file.
- Each executable gets rebuilt whenever one of its &quot;.o&quot; files gets rebuilt.
- No unnecessary rebuilding is ever done.
- The command `make clean` &quot;does the right thing&quot;.


You will need to examine the relationships between the files in order to do this.
The goal is that you end up with two executables:
- `listForward`, which lists an array forward, and 
- `listBackward`, which lists an array backward.

You should **not need to modify any C code** here:
just create the `makefile` so that its dependencies are consistent
with those among the source and object files
 and so that the proper commands are executed to perform each step of the &quot;build&quot;.

**Checkpoint 5 [20 points]: Demonstrate to your instructor/assistant that the proper files get rebuilt after various sets of source-file modifications are made. Let your instructor/assistant examine your makefile and run your executables.**



### Part 6: Finish up (Person 2)

##### For more information

`make` has many other features, which can be viewed in the GNU make manual.

[http://www.gnu.org/software/make/manual/make.html](http://www.gnu.org/software/make/manual/make.html).

If you intend to write software that will compile on a great number of Unix variants,
it is worth looking into GNU automake, documented at

[https://www.gnu.org/software/automake/manual/automake.html](https://www.gnu.org/software/automake/manual/automake.html)


##### Cleanup

If you with to make a copy of your files, here are a couple of suggestions:

- Create a tar file (`tar cvzf filename.tar.gz lab4/`)
- Use a web browser in the Unix VM to email it to yourself and your partner
- Sudo to root (`sudo su -`) and copy the .tar.gz file to `/media/sf_P_DRIVE`
- Use a web browser in the Kiosk VM to email it to yourself and your partner


Shut down the Unix VM (halt and power off)

```sh
sudo halt -p
```

Log out of the Engineering Kiosk (big logout button on the desktop).

Read Me
Creator : Gayatri Powar
-------------------
The task is to write a command-line program to evaluate a set of
equations, each specified on separate lines. An equation is defined
by:
<LHS> = <RHS>

<LHS> is the left-hand side of the equation and is always a variable
name. A variable name can only be composed of letters from the
alphabet (e.g. for which isalpha(c) is 1). <RHS> is the right hand
side of the equation and can be composed of variables, unsigned
integers, and the + operator.

Here is one example set of equations:
offset = 4 + random + 1
location = 1 + origin + offset
origin = 3 + 5
random = 2

The program takes a filename as input. The file contains a set
of equations, like the above. It evaluates the set of equations
and print the unsigned integer value of each variable.

<variable name> = <unsigned integer value>

The output is sorted by in ascending order by variable name.
The output for the example above would be:
location = 16
offset = 7
origin = 8
random = 2

Assumtions: 
The input is well formed.
There will be one or more white spaces between each token. 
A variable is only defined once and will have a valid integer solution.

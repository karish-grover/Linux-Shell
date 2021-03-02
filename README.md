# Linux-Shell

Linux (and other Unix like OSes), have “shells” or programs which present
a command line interface to users to type commands in. In this assignment
you need to use standard C libraries, including Linux system calls such as
fork(),exec() family system calls and wait() family of system calls.
There are two kinds of commands – “internal” and “external”. Internal commands are those which are interpreted by the shell program itself, with-
out requiring a different program to handle the expected operations (of the said command). Examples of internal commands are like ‘cd’, ‘pwd’, ‘exit’
etc. External commands on the other hand relate to commands which are not
handled directly by the shell program but by an external program. Common
examples include ‘ls’, ‘cat’, ‘grep’ etc.

Your task is to design your a simple shell that can handle five, internal com-
mands – ‘cd’, ‘echo’, ‘history’, ‘pwd’ and ‘exit’. These commands would be handled directly by the shell. Your shell should also be able to han-
dle five external commands – ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’. For these external commands you need to write individual programs to handle these commands. To handle these external commands, the shell should typically create a new process, using the fork() system call and within each process you need to use the execl() family system call to run the individual program. The parent program must also wait for the child program to terminate using the
wait() family of system calls.

For each of these commands, you need not handle all the command line
options. Two options per command is sufficient. You need to document which
two options you are handling and need to demonstrate correct functioning of
the command with respect to (atleast) your chosen options. You also need to
handle corner cases such as invalid options (graceful degradation).


<img width="507" alt="Screenshot 2021-03-02 at 3 19 33 PM" src="https://user-images.githubusercontent.com/64140048/109630238-b34f4a80-7b6a-11eb-8951-012dae5a47d0.png">

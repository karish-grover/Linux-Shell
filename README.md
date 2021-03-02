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

<img width="717" alt="Screenshot 2021-03-02 at 3 34 35 PM" src="https://user-images.githubusercontent.com/64140048/109632723-5c974000-7b6d-11eb-993d-18d34475d07a.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 35 03 PM" src="https://user-images.githubusercontent.com/64140048/109632730-5ef99a00-7b6d-11eb-858b-c1eca0f49d2a.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 35 11 PM" src="https://user-images.githubusercontent.com/64140048/109632737-60c35d80-7b6d-11eb-9853-4e363f754b4b.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 35 23 PM" src="https://user-images.githubusercontent.com/64140048/109632748-6325b780-7b6d-11eb-81d6-0449cc13d2a4.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 35 52 PM" src="https://user-images.githubusercontent.com/64140048/109632754-64ef7b00-7b6d-11eb-9922-06c4e9f96893.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 36 05 PM" src="https://user-images.githubusercontent.com/64140048/109632762-6620a800-7b6d-11eb-8f3f-b070e5a20443.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 36 14 PM" src="https://user-images.githubusercontent.com/64140048/109632771-67ea6b80-7b6d-11eb-8ff0-d39012626254.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 36 45 PM" src="https://user-images.githubusercontent.com/64140048/109632774-691b9880-7b6d-11eb-85b0-f679ba45e787.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 37 17 PM" src="https://user-images.githubusercontent.com/64140048/109632779-6a4cc580-7b6d-11eb-87b0-b567fd9dbc56.png">
<img width="717" alt="Screenshot 2021-03-02 at 3 37 35 PM" src="https://user-images.githubusercontent.com/64140048/109632787-6b7df280-7b6d-11eb-88b7-faa739bc0c24.png">



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


OS Assignment Write Up - Question 2
● Inthesecondpartoftheassignment,wearerequiredtosimulatealinux shell with 5 internal and 5 external commands.
● Theinternalcommandsarebuilt-incommandsintheshellaretheones which are to be implemented are:- ​cd, pwd, history, echo​, ​exit​.
● Theexternalcommandsarenotdirectlyhandledbytheshellprogrambutby an external program. We are required to implement:- ​mkdir, rm, ls, date, cat.
● Theinternalcommandswillbehandleddirectlybytheshell,whereaswe will write different programs to handle different external commands.
● Now,letusfirsttalkabouttheinternalcommandsandtheirimplementation in detail:
1. exit:
a. Thiscommandwillexittheshellwhenpassed.
b. The ​OPTIONS​ implemented for this command are:
i. exit: ​The simple exit command will exit the shell at the instance it is called. It will have exit code 0 by default.
ii. exit --help: ​This option displays​ help​ for the e​ xit ​command. Help contains information about this command. It simply prints the information hardcoded. (Which can easily be modified)
iii. exit [n]: ​When we pass an additional argument n along with exit, then the shell exits with return value as n. Incase n is an integer, the shell will exit with the return value as the integer. Incase some alphabet or character is passed, it will exit with
 exit code 0. If some large integer is passed, then it will be
scaled down for convenience in the provided code.
c. The​exit​commanddoesn'trequireanyERROR-HANDLINGassuch.
2. history:​ Throughout the shell session, we maintain two things: A history file and a history list. The history file ​“history.txt”,​ stores the history of all the commands run on all the sessions of the shell. Any command ever run will be present in the file. At the beginning of the program, the history.txt file shall be opened and any user input shall be written to it. The history list stores the commands for the current session of the shell. (​Note:​ In the code, this list is created, however no option is provided to access it. The option to access it is commented, which can be easily shown while demo).
The ​OPTIONS​ provided are:
a. history:​Thebasichistorycommandwillsimplyprintoutthehistory
of all the commands ever used i.e. all the commands present in
“history.txt”​.
b. history -c: ​We will use the ​-c​ option to clear all of the history. When
-c ​flag is used, it will simply clear the entire ​“history.txt”​, file.
c. history-s[ARGS]:​AppendtheARGstothehistorylistasasingle
entry. Whatever is present beyond the ​-s ​flag is simply appended to the history file. ​NOTE:​ As a modification of the original command, the command ​history -s​ shall also be appended. In the actual shell, the history -s​ command is not appended, only the ARGS are appended.

 ERROR-HANDLING:
● Possibleerrorwhileopeningthe“history.txt”file:​Itispossiblethatwhile
opening the given file we encounter some error. The program handles such errors. If the value of the pointer returned by the ​fopen()​ function is ​NULL, it implies that some error has occurred while we tried to open the file. The program proceeds only if the return value is not ​NULL​. However, in the case it is ​NULL​, there are many other errors possible, thus in those cases, we prompt a​ ​general message to stdout and stderr and print the error number.
CORNER CASE HANDLED:
If other than the three options, any other argument is passed to history like “history xys”, ​in such a case it will prompt a message to the stdout saying “INVALID ARGUMENTS TO history”.
3. pwd:​ ​This command prints the current working directory of the program. The OPTIONS implemented are:
a. pwd: ​Prints the CWD.
b. pwd -P:- ​Print the physical directory, without any symbolic links.
(Same as the default implementation in this case).
c. pwd--help:​Thisoptiondisplays​help​forthe​pwd​command.Help contains information about this command. It simply prints the information hardcoded. (Which can easily be modified).
ERROR-HANDLING:
● PossibleerrorwhilegettingtheCWD:​Itispossiblethatthefunction
getcwd(),​ might return a NULL pointer in case there has been an error and

 we were unable to get the working directory. In this case we print the error number and prompt using perror to ​stderr​ and print an alert to the ​stdout. We return EXIT_FAILURE in the case there is an error. Otherwise we return EXIT_SUCCESS.
CORNER CASE HANDLED:
If other than the three options, any other argument is passed to pwd like ​“pwd xys”, ​in such a case it will prompt a message to the stdout saying ​“INVALID ARGUMENTS TO pwd”.
4. echo:
The OPTIONS implemented:
a. echo​​[to_be_echoed]:​Echo(print)theSTRING(s)tostandardoutput. b. echo -e [to_be_echoed]: ​Enable interpretation of backslash escape
sequences. In normal echo command, they are ignored. Here, they are
enabled.
c. echo-n[to_be_echoed]:​Donotoutputthetrailingnewline.Thisis
same as normal echo, just that in the end ‘\n’, new line character is not printed.
CORNER CASES HANDLED:
All possible cases of echo are handled. The cases are given in the test cases file.

 5. cd:
The ​OPTIONS​ implemented:
a. cd:​Changedirectorytohomedirectory.
d. cd -P [Directory name]: ​Use the physical directory structure without
following symbolic links: resolve symbolic links in DIR before processinginstancesof​`..'.​ Hereitissameasthedefault implementation.
e. cd..:​Movetotheparentdirectoryofcurrentdirectory,orthe directory one level up from the current directory.
f. cd ~:​Change directory to home directory.
g. cd [Directory name] : ​Change directory to the specified directory. h. cd --help:​ Open help for the​ cd​ command.
ERROR-HANDLING:
● Sinceweareusingthe​chdir()​functionhere.Ifthereturnvalueofthe
chdir()​ function is​ -1​ this implies that there was an error while we were trying to change the directory. We report this error by printing to stdout. This is very common and a very important error to be handled, as we may very well provide with wrong directory names, and in those cases, we don’t expect out program to crash.
Now, if either the user input is from among these 5 commands, however, if it is not, then we will consider the external commands. For the five external commands there are 5 files ​“date.c”, “rm.c”, “mkdir.c”, “cat.c” , “ls.c”. ​If the user enters any of these commands, then these external files are executed. Here, we use the

 fork() ​system call to fork a child process that will execute these programs. In order to do this we follow a similar procedure as Q1. In order to execute the binaries of these files, we use the ​exec ​family of instructions. Let us look at all these 5 programs in detail:
1. date:
OPTIONS Implemented:
a. date: ​Display the current date and time in the given/default
FORMAT.
b. date -u: ​Display the current time in the UTC Format.
c. date--help:​Displayhelpfordatecommand.
CORNER CASES:
If other than the three options, any other argument is passed to date like “date xys”, ​in such a case it will prompt a message to the stdout saying “INVALID ARGUMENTS TO date”
2. rm:
OPTIONS Implemented: ​This command will remove the multiple file names that are provided separated by space.
a. rm [Name, ..]: ​Remove the FILE(s).
b. rm -f [Name, ..]: ​Ignore nonexistent files and arguments, never
prompt.
c. rm-v[Name,..]:​(Verbosemode)-explainwhatisbeingdoneat
every step. Prompt everything.
ERROR HANDLING:

 ● PossibleerrorwhilegettingtheCWD:​Itispossiblethatthefunction getcwd(),​ might return a NULL pointer in case there has been an error and we were unable to get the working directory. In this case we print the error number and prompt using perror to ​stderr​ and print an alert to the ​stdout. We return 0 (EXIT_FAILURE) in the case there is an error. Otherwise we return 1.
CORNER CASES:
● Whileusingtheremove()function​toremovethefilespecified,if
the return value of this function is 0, then it implies that the operation was successful, otherwise, the operation was un successful. In case of no success, we prompt the message depending on the OPTION being used along with it.
● Ifwedon’tprovideanyargumenttormlikeJUST​“rm”​,thenitwill prompt a message to the user, saying ​“MISSING ARGUMENTS”​.
3. ls:
OPTIONS Implemented:
a. ls:​ Print all the file names that are present in the current directory. It
can be modified to both alphabetically and random.
b. ls -i: ​Print the index number of each file along with file name. c. ls-X:​Sortbyfilenamealphabetically.Sameasdefaulthere.
ERROR HANDLING:
● PossibleerrorwhilescanningtheCWD:​Itispossiblethatthefunction
scandir(),​ might return an integer value -1, in case there has been an error

 and we were unable to scan the directory. In this case we print the error number and prompt using perror to ​stderr​ and print an alert to the ​stdout. We return EXIT_FAILURE in the case there is an error. Otherwise we return EXIT_SUCCESS.
CORNER CASES:
If other than the three options, any other argument is passed to ls like ​“ls xys”, ​in such a case it will prompt a message to the stdout saying “INVALID ARGUMENTS FOR ls”
4. mkdir:
OPTIONS Implemented:
a. mkdir [Name..]: ​Create directories for the mentioned names provided
in the arguments.
b. mkdir -v [Name..]: ​(Verbose mode) - explain what is being done at
every step. Prompt everything.
c. mkdir--help:​Openhelpformkdir.
ERROR HANDLING:
● PossibleerrorwhilegettingtheCWD:​Itispossiblethatthefunction
getcwd(),​ might return a NULL pointer in case there has been an error and we were unable to get the working directory. In this case we print the error number and prompt using perror to ​stderr​ and print an alert to the ​stdout. We return 0 (​EXIT_FAILURE​) in the case there is an error. Otherwise we return 1.
CORNER CASES:
● WeareusingmkdirfunctioninC,tocreatedirectories.Ifthereturn value of this function is not 0, it means that the directory exists. And

 thus we prompt this message to stdout that the file already exits. If the return value is 0, it means that the directory was successfully created. In the verbose mode, we prompt a message for every step.
● Ifwedon’tprovideanyargumenttomkdirlikeJUST​“mkdir”​,then it will prompt a message to the user, saying ​“MISSING ARGUMENTS”​.
5. cat:
OPTIONS Implemented:
a. cat [File Name..]: ​Concatenate FILE(s) to standard output. (Print the
contents of the files)
b. cat -n [File Name]: ​Number all output lines.
c. cat-E[FileName]:​Display$attheendofeachline.
ERROR HANDLING:
● PossibleerrorwhilegettingtheCWD:​Itispossiblethatthefunction
getcwd(),​ might return a NULL pointer in case there has been an error and we were unable to get the working directory. In this case we print the error number and prompt using perror to ​stderr​ and print an alert to the ​stdout. We return 0 (EXIT_FAILURE) in the case there is an error. Otherwise we return 1.
● Possibleerrorwhileopeningthefile(s):​Itispossiblethatwhileopening the given file we encounter some error. The program handles such errors. If the value of the pointer returned by the ​fopen()​ function is ​NULL,​ it implies that some error has occurred while we tried to open the file. The program proceeds only if the return value is not ​NULL​. However, in the case it is

NULL​, there are many other errors possible, thus in those cases, we prompt
a​ g​ eneral message to stdout and stderr and print the error number.
● Possibleerrorwhileusingthe​stat()​function.​stat()​functionisusedtolist
properties of a file identified by the path. If we were unable to find the file, then the return value of the stat function will be -1. In such a case we prevent the system from crashing and it exits.
OTHER CORNER CONDITIONS HANDLED:
1. If the command input by the user matched none of these 10 commands then it will be identified as an invalid command, and hence, it will say “INVALID COMMAND”​, on the stdout.
2. If the input by user is ​NULL​ i.e. the user simple presses ​“enter”​ instead of typing in any command, then in order to prevent the system from going into an infinite loop, the shell will automatically exit.
3. If the user provides names of files enclosed within the special character “*”, then it will treat it as one file name separated by underscore instead of space. For example.​ An input file name like *a1 a2*, shall be treated as a1_a2.
OTHER ERRORS HANDLED:
1. Possible error while opening the history.txt file​ at the beginning of the code, to append the input command to the code. It is handled the same way.
2. Possible forking Error ​while creating a process to execute the external instructions.​ ​If the pid value returned by the​ fork() ​system call is less than 0, then it implies that the forking process was unsuccessful and that a child process could not be created. Since we do not want our program to crash in such a situation, we handle this error. If the value of ​pid<0​, then we output “Fork Failed” to stderr. ​And thereafter, we return and the program terminates. We use perror.

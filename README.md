Simple Shell 

Background

The shell is just another program. For example, the Bash shell is an executable named bash that is usually located in the /bin directory. So, /bin/bash.

Try running /bin/bash or just bash on a Linux (or BSD-based, such as Mac OS X) operating system's command line, and you'll likely discover that it will successfully run just like any other program. Type exit to end your shell session and return to your usual shell.

(If your system doesn't have Bash, try running sh instead.)

When you log into a computer, this is essentially what happens: Bash is executed. The only special thing about logging in is that a special entry in /etc/passwd determines what shell runs at log in time.

Assignment Requirements

Write a simple shell in C. The requirements are as follows.

Part 1: The Simple Shell

Your shell executable should be named w4118_sh. Your shell source code should be mainly in shell.c, but you are free to add additional source code files as long as your Makefile works, and compiles an executable named w4118_sh.
The shell should run continuously, and display a prompt when waiting for input. The prompt should be EXACTLY '$'. No spaces, no extra characters. Example with a command:
	$/bin/ls -lha /home/w4118/my_docs
Your shell should read a line from stdin one at a time. This line should be parsed out into a command and all its arguments. In other words, tokenize it.
You may assume that the only supported delimiter is the whitespace character (ASCII character number 32).
You do not need to handle "special" characters. Do not worry about handling quotation marks, backslashes, and tab characters. This means your shell will be unable support arguments with spaces in them. For example, your shell will not support file paths with spaces in them.
You may set a reasonable maximum on the number of command line arguments, but your shell should handle input lines of any length.
After parsing and lexing the command, your shell should execute it. A command can either be a reference to an executable OR a built-in shell command (see Part 2). For Part 1, just focus on running executables, and not on built-in commands.
Executing commands that are not shell built-ins and are just the executable name (and not a full path to the executable) is done by invoking fork() and then invoking exec().
You may NOT use the system() function, as it just invokes the /bin/sh shell to do all the work.
Part 2: Implement Built-in Commands: exit, cd, history

exit - Simply exits your shell after performing any necessary clean up.
cd [dir] - Short for "change directory", and will be used to change the current working directory of your shell. Do not worry about implementing the command line options that the real cd command has in Bash. Just implement cd such that it takes a single command line parameter: The directory to change to.
history [-c] [offset] - Similar to the Bash built-in history command, but much simpler.
history (without arguments) displays the last 100 commands the user ran, with an offset next to each command. The offset is the index of the command in the list, and valid values are 0 to 99, inclusive. 0 is the oldest command. Do not worry about persisting this list to a file; just store it in memory. Once more than 100 commands are executed, remove the oldest entry from the list to make room for the newer commands. Note that history is also a command itself and therefore should also appear in the list of commands. If the user ran invalid commands, those should also appear in the list.
history -c clears the entire history, removing all entries. For example, running history immediately after history -c should show history as the sole entry in the list.
history [offset] executes the command in history at the given offset. Print an error message of your choosing if the offset is not valid.
Example output for built-in history:
$cd /home/w4118
$/bin/ls
my_file.txt
$history
0 cd /home/w4118
1 /bin/ls
2 history
$history 1
my_file.txt
$history
0 cd /home/w4118
1 /bin/ls
2 history
3 history 1
4 history
$history -c
$history
0 history
$
Part 3: Pipes

Augment your shell to be capable of executing a sequence of programs that communicate through a pipe. For example, if the user types /bin/ls | /usr/bin/wc, your program should fork the two programs, which together will calculate the number of files in the directory. For this you will need to replace stdin and stdout with pipe file descriptors using dup2.
While this example shows two processes communicating through a pipe, your shell should support pipes between multiple processes, not just two.
You should also support built-in commands to work with pipes. In this case, you will need to handle built-in commands in a different manner as they are not separate programs that need to be forked.
Other Requirements

Error messages should be printed using exactly one of two string formats. The first format is for errors where errno is set. The second format is for when errno is not set, in which case you may provide any error text message you like on a single line.
"error: %s\n", strerror(errno)

OR

"error: %s\n", "your error message"
So for example, you would likely use: fprintf(stderr, "error: %s\n", strerror(errno));.

Check the return values of all functions utilizing system resources. Do not blithely assume all requests for memory will succeed and all writes to a file will occur correctly. Your code should handle errors properly. Many failed function calls should not be fatal to a program.
Typically, a system call will return -1 in the case of an error (malloc will return NULL). If a function call sets the errno variable (see the function's man page to find out if it does), you should use the first error message as described above. As far as system calls are concerned, you will want to use one of the mechanisms described in Reporting Errors or Error Reporting.

A testing script skeleton will be provided in a GitHub repository to help you with testing your program. You should make sure your program works correct with this script. For grading purposes, we will conduct much more extensive testing than what is provided with the testing skeleton, so you should make sure to write additional test cases yourself to test your code.

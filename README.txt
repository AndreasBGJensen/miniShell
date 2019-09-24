Andreas BG Jensen, s130016


	mm     mm    I   NN    N   I    SSS    H   H    EEEEE   L        L
 	m m  m  m    I 	 N N   N   I   S       H   H    E       L        L
	m  m m  m    I 	 N  N  N   I    SSS    HHHHH    EEEE    L        L
  	m   m	m    I   N   N N   I       S   H   H    E       L        L
 	m       m    I   N    NN   I    SSS    H   H    EEEEE   LLLLLL   LLLLLL    



User Manual
_____________________________________________________________________________________________________________________________
1.  	Compile the .c file by running the command gcc main.c -o miniShell
2. 	Execute the miniShell by using the command ‘./miniShell’

NB: In order for you to compile the sourcecode you need to install a compile like gcc.

The following operations are available:
- Execute a programme. 
- Chanage directory: 
- See files in the current directory


Description on how to execute the commands
____________________________________________________________________________________________________________________________

To execute a programme:
	- Type: ‘exe ./filename’.  Example: ‘exe ./main.c’
To change directory
	- Type: ‘cd directory’. Example cd /mnt/c/ProgrameFiles’-->cd .. = /mnt/c/. 
    NB: /mnt/ is a folder provided by Ubuntu to access windows files.
To see current files in the current directory
	- Type: ‘dir’ and the existing files will appear in the terminal.


Testet commands: The folowing commands have been tested
____________________________________________________________________________________________________________________________
“exe ls -l”
“dir”
“cd ..”
“cd /”The path”/
“exe ./Hello” 
"mkdir name"


Functions created: These functions are created in the sourcefile 
___________________________________________________________________________________________________________________________

void welcome(): Prints insctrutions and a welcome message
void getString(): Recives and formats the input string.
void execute(char **arr): Creates a child process and executes imagefiles.
void getDir(): Prints all files placed in the current working directory.
int controller(): Evaluate inputargument and returns an int as matching the command.
void crossRoad(): Executes function matching the return from controller()
void changeDirectory(): Changes the directory.
void getDirectory(): Prints the current directory to the terminal
char ** removeFirstElement(char **arr): Removes the first element from an array.
void makeDirectory(char **arr): Creates a directory in the current directory,


Description of a shell
____________________________________________________________________________________________________________________________

In this assignment i’ve chossed to focus on the process calls: fork(), waitpid() and execvp() and the system call chdir. 
The following will be an investigation of these calls. But first we will have a look at what an Operating  System is. 
A Operating System is a executable program (programs) that are executed by the processor.  

The operating system is managed by an “interface” refered to as a Kernel. 
The kernel is responsable for the execution of a process and enables system calls from an executing process to call directly to processer (kernal). 
System calls enables user-level processes to request services of the operating system. 

Here are some examples of the utilities of the system calls: 
- Process creation and management
- Main memory management
- File Access, Directory and File system management
- Device handling(I/O)
- Protection
- Networking, etc.
- Process calls used


Description of used process calls
___________________________________________________________________________________________________________________________

fork()
The fork process calls creates an exact copy of the parent process (in this case the miniShell programme). Everything will get copied.
This will result in that, the child process (the copy process) will contain the exact same lines of code that the parent process contains.
 This has to be managed because if it is not all of the code will be executed twice.  

when creating a fork er the function fork() returns a value <0, >0 or == 0. These numbers indicates which process we are currently in: 
	- >0: The return value will be the process Id from the children process which is returned to the parent process. 
	      This means that the process we “are in” will be the parent process.
	- == 0: The return value indicates that we “are in” the child process.
	- <0: This returnvalue indicates that the parent process was unable to create at child process.

Waitpid()
To ensure that both the parent- and the childprocces will not be executet at the same time.
This process call is called by the parent process an waits for a children process to terminate, but this behavior can be configured by the parameters.
It insures that the parent process will wait for the child process to terminate before it continues.

execvp()
I use execvp to execute a new file in the child process.
By using execvpthe created child process does not have to run the same program as the parent process does.
The execvp does the following: Reboots a process to run a programme from scratch.


System calls used
____________________________________________________________________________________________________________________________________

chdir()
chdir command is a system function (system call) which is used to change the current working directory. It is invoked by using cd as an argument.
chdir changes the current working directory of the calling process to the directory specified in path. 
Example: Changing the directories.

mkdir()
Command to create a directory. The parameter for this function will be the directory name.




NOTE
_____________________________________________________________________________________________________________________________________
Some functions like the "mkdir" is implemented by med but will also work without 
my implementation because it is a system call located in the /bin/- folder like "ls"



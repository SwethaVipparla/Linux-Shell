# Magnush 

<br>
Magnush is the clone of the Bash shell. It is written in C, and supports various features that we can see in a traditional Bash shell. 

&nbsp;

## Instructions To Run The Shell

#### 1. Clone the repo and navigate to the folder
```
git clone https://github.com/SwethaVipparla/Magnush.git
cd Magnush/
```
#### 2. Compile the code and run the executable
```
make
./Magnush
```

#### 3. Input Commands
Once the code is up and running, the commands for the included features can be executed. Multiple commands can also be entered in a single line, separated by `;`. Random spaces and tabs in commands are accounted for too.

&nbsp;
## Features

#### Command Prompt

Magnush has a command prompt that is similar to the one in a Bash shell. The prompt is coloured and is displayed in the form of `<username@system_name:curr_dir>`.
The root directory is the one from which the shell is started.

 > Implemented in [prompt.c](https://github.com/SwethaVipparla/Magnush/blob/main/Features/prompt.c)

#### Command Pipelines

Magnush supports piping with commands. One or more commands can be piped using `|`, and any number of pipes are supported.

```
cat <filename.txt> | head -7 | tail -5
```

 > Implemented in [pipe.c](https://github.com/SwethaVipparla/Magnush/blob/main/Features/pipe.c)

#### Input/Output Redirection

Magnush also provides for input/output redirection of commands. The output of commands can be redirected to another file or command instead of stdout, the input can be taken from a file other than stdin, or the output of a command can be appended to a file. These redirections are done using the `<`, `>`, and `>>` symbols.  
Both input and output redirections can be used simultaneously too. 

```
echo "hey" > output.txt
sort < output.txt > sorted.txt
```

 > Implemented in [redirection.c](https://github.com/SwethaVipparla/Magnush/blob/main/Features/redirection.c)

 #### Input/Output Redirection within Command Pipelines

Input/Output redirection can be implemented within command pipelines.  

```
cat < in.txt | wc -l > lines.txt
```

&nbsp;
## Built-In Commands

#### 1. cd
Changes the current directory to another directory specified and displays an error if the specified directory does not exist.
`.`, `..`, `~`, and `-` are all valid directory names.
```
cd <path_to_destination_directory>
```

 > Implemented in [cd.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/cd.c)


#### 2.  pwd
Ouputs the path of the current working directory
```
pwd
```
 > Implemented in [pwd.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/pwd.c)


#### 3.  echo
Prints the specified message on the terminal. It accounts for any random spaces and tabs.
```
echo <message>
```

 > Implemented in [echo.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/echo.c)

#### 4.  ls
Lists all the files and directories in the given directory. It handles multiple directories as arguments. Flags can be used to provide more functionalities to the command.  
 
```
ls <path_to_directory> 
```
##### Flags supported  
- `-a`: Lists all the files and directories in the given directory, along with symbolic links and hidden files and folders.

```
ls -a <path_to_directory> 
```
- `-l`: Lists all the files and directories in the given directory with detailed information.
```
ls -l <path_to_directory> 
```

These flags can be used together in different orders while giving the intended output.

 > Implemented in [ls.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/ls.c)

#### 5. history
Diplays the history of the commands run. If no argument is specified, the last 10 commands are listed. The history persists even after the shell is exited.

```
history <no_of_commands>
```

 > Implemented in [history.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/history.c)

#### 6. pinfo
Displays information about the process, including its PID, status, memory, and executable path.
```
pinfo <PID>
```
Running just `pinfo` without any arguments will display information about the shell program.

 > Implemented in [pinfo.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/pinfo.c)


#### 7. repeat
Executes the given instruction multiple times. The first argument to the command specifies the number of times the following command is to be run.
```
repeat <no_of_times> <command>
```

 > Implemented in [repeat.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/repeat.c)

#### 8. fg
Brings the running or stopped background job corresponding to the job number​ to the foreground and changes its state to ​running​.
```
fg <job_number>
```

 > Implemented in [fgbg.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/fgbg.c)

#### 9. bg
Changes the state of a stopped background job to running (in the background). It has no effect on foreground processes and already running background processes.
```
bg <job_number>
```

 > Implemented in [fgbg.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/fgbg.c)

#### 10. jobs
Prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
their job numbers, process IDs, and states (either running or stopped).

```
jobs
```
##### Flags supported  
- `-r`: Prints only the running processes.

```
jobs -r
```
- `-s`: Prints only the stopped processes.
```
jobs -s
```

These flags can be used at the same time in different orders while giving the intended output.

 > Implemented in [jobs.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/jobs.c)

#### 10. sig

Takes the job number of a running job and sends the signal corresponding to ​signal number​signal number​ to that process.
```
sig <job_number> <signal_number>
```

 > Implemented in [sig.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/sig.c)

#### 11.  replay
Executes a particular command in fixed time interval for a certain period 
 
```
replay -command <input_command> -interval <time_interval> -period <time_period>
```

All the flags here are required and can be implemented in any order. 
Background processes are also supported. 

 > Implemented in [replay.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/replay.c)

&nbsp;
## Processes

There are two kinds of processes that can be run in Magnush.
#### 1. Foreground Processes
To run processes in the foreground, just enter the command and the process will start up.
Magush will wait for this process to complete and regain control when this process exits.
If the given command is not found, an error is displayed. 
For example, `vim` and `gedit` are foreground processes.

```
<command>
```

 > Implemented in [process.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/process.c)

#### 2. Background Processes
To run processes in the background, enter an `&` after the command and the process will start up.
Magush will spawn the process and doesn't wait for it to exit. It will keep taking other user commands.
After the background process exits, the shell displays the exit status on the terminal.

```
<command> &
``` 
or 
```
<command>&
```

 > Implemented in [process.c](https://github.com/SwethaVipparla/Magnush/blob/main/Commands/process.c)

 &nbsp;
## Signal Handling

Magnush allows the handling of signal, each of which serves a different purpose.

 > Implemented in [signals.c](https://github.com/SwethaVipparla/Magnush/blob/main/Features/signals.c)

#### 1. Ctrl-Z

Pushes any currently running foreground job into the background and changes its state from running to stopped by sending the **SIGTSTP**. It has no effect on the shell if there is no foreground process running.

#### 2. Ctrl-C

Interrupts any currently running foreground job by sending the **SIGINT** signal. It has no effect on the shell if there is no foreground process running.

#### 3. Ctrl-D

Log the user out of the shell, without having any effect on the actual terminal.





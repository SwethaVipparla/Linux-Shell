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

 > Implemented in [prompt.c](https://github.com/SwethaVipparla/Magnush/blob/main/prompt.c)

#### Piping

Magnush supports piping with commands. One or more commands can be piped, and any number of pipes are supported.

```
cat <filename.txt> | head -7 | tail -5
```

 > Implemented in [prompt.c](https://github.com/SwethaVipparla/Magnush/blob/main/prompt.c)


### Built-In Commands

#### 1. cd
Changes the current directory to another directory specified and displays an error if the specified directory does not exist.
`.`, `..`, `~`, and `-` are all valid directory names.
```
cd <path_to_destination_directory>
```

 > Implemented in [cd.c](https://github.com/SwethaVipparla/Magnush/blob/main/cd.c)


#### 2.  pwd
Ouputs the path of the current working directory
```
pwd
```
 > Implemented in [pwd.c](https://github.com/SwethaVipparla/Magnush/blob/main/pwd.c)


#### 3.  echo
Prints the specified message on the terminal. It accounts for any random spaces and tabs.
```
echo <message>
```

 > Implemented in [echo.c](https://github.com/SwethaVipparla/Magnush/blob/main/echo.c)

#### 4.  ls
Lists all the files and directories in the given directory. It handles multiple directories as arguments. Flags can be used to provide more functionalities to the command.  
 
```
ls <path_to_directory> 
```

**Flags supported:**  
- `-a`: Lists all the files and directories in the given directory, along with symbolic links and hidden files and folders.

```
ls -a <path_to_directory> 
```
- `-l`: Lists all the files and directories in the given directory with detailed information.
```
ls -l <path_to_directory> 
```

These flags can be used together in different orders, while giving the output intended.
<br>

 > Implemented in [ls.c](https://github.com/SwethaVipparla/Magnush/blob/main/ls.c)
<br>

### System Commands

Commands other than the built-in commands are system commands. For example, `vim` and `gedit` are system commands.

#### 1. Foreground Processes
To run processes in the foreground, just enter the command and the process will start up.
Magush will wait for this process to complete and regain control when this process exits.
If the given command is not found, an error is displayed. 

```
<command>
```

 > Implemented in [fg.c](https://github.com/SwethaVipparla/Magnush/blob/main/fg.c)

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

 > Implemented in [bg.c](https://github.com/SwethaVipparla/Magnush/blob/main/bg.c)
### Additional Commands

#### 1. pinfo
Displays information about the process, including its PID, status, memory, and executable path.
```
pinfo <PID>
```
Running just `pinfo` without any arguments will display information about the shell program.

 > Implemented in [pinfo.c](https://github.com/SwethaVipparla/Magnush/blob/main/pinfo.c)

#### 2. Repeat
Executes the given instruction multiple times. The first argument to the command specifies the number of times the following command is to be run.
```
repeat <no_of_times> <command>
```

 > Implemented in [repeat.c](https://github.com/SwethaVipparla/Magnush/blob/main/repeat.c)

#### 3. History
Diplays the history of the commands run. If no argument is specified, the last 10 commands are listed. The history persists even after the shell is exited.

```
history <no_of_commands>
```

 > Implemented in [history.c](https://github.com/SwethaVipparla/Magnush/blob/main/history.c)


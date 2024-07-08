
# Minishell 
## Overview
Minishell is a project aimed at creating a simple Unix shell. Through this project, you will gain a deeper understanding of processes, file descriptors, and other core system functionalities. 
## Features
- Display a prompt and wait for user input. 
- Maintain a working command history. 
- Execute commands found in the system PATH or via relative/absolute paths.
- Handle single and double quotes to prevent the shell from interpreting metacharacters. 
- Implement input/output redirections and pipes. 
- Support for environment variable expansion and special variable `$?`. 
- Signal handling for `ctrl-C`, `ctrl-D`, and `ctrl-\`.
- ## Installation
- 1. **Clone the repository**:
	-  ```git clone https://github.com/mbrettsc/minishell.git && cd minishell```
- 2. **Build the project**:
	-  ```make ``` 
- ## Usage
-  Run the shell:  ```bash ./minishell```

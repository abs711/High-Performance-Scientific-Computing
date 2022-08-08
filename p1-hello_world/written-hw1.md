1. How would you specify the name of an output file when you use the compiler if you wanted the executable to have a name other than a.out?

By adding the '-o filename' flag to compiling command i.e. using c++ -std=c++11 cos4pi.cpp -I/usr/include/python3.8 -lpython3.8 -o filename. This would create a file 'filename' instead of 'a.out'

2. What happens if you type $ a.out instead of $ ./a.out to run your program What is the difference (operationally) between the two statements?

Typing a.out raises the following error- "a.out: command not found". This is because on typing "a.out", the bash starts searching for that executable file in the directories listed in the $PATH environnment variable, whereas the a.out file is in the current working directory. Using ./a.out tells the bash to look for a.out executable file in the current working directory. 
Reference- stack overflow (https://stackoverflow.com/questions/23024016/cant-run-c-program-a-out-command-not-found)

3. What does clang print when you run $ c++ --version?

clang version 10.0.0-4ubuntu1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin

4. In the example program, the i variable is said to be size_t. What is a size_t?

size_t is the unsigned integer variable type. It is used for array indexing and iterating through loops. 

5. In cosx.png, which alphabet letter does the shape look like?

The shape looks like a 'W'.


6. What do the -I and -l flags do in the command we used to build a.out? 

-I (eye) flag list the directories to search through for python3.8 related header files while -l (ell) links to the library for python like functionalities in c++.

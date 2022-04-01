* All the answers to whether the function is a system call
    or a library function are in the comments of main.c file.

* I implemented both bonuses about handling cases of commands
    with pipelines (even a couple of pipelines).
    IMPORTANT: I assumed that when running a command with a pipeline
               there is no spaces between the pipeline and the command
               for example: ls -la|grep main|grep main.c

* Because the code separate to a couple of c and header files
    there is also a makefile with make all and make clean as requested.

                              *-HOW TO RUN-*
    First open a terminal in the Shell directory and run <make all>
    then just <./shell> to run the code.
    to clean all the objects, libs and executable files run <make clean>

    There is also a <make run> rule for compile and run the code all together
    while typing <EXIT> in the shell will run make clean after exiting

    In order to run the TCP PORT command you will need to start the server.
    After you run make all and compile all files run <./server> to start the server
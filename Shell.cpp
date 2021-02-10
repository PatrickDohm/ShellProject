#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LINE 80 //The maximum length command
using namespace std;

int main(void){

    char* args[MAX_LINE/2 + 1]; //command line arguments
    int should_run = 1; //flag to determine when to exit program

        while(should_run){
            printf("osh>");
            fflush(stdout);

            //after reading user input the steps are :
            //(1) fork a child process using fork()
            pid_t child_pid;
            child_pid= fork();
            //(2) The child process will invoke execvp()
            if (child_pid == 0){ //CHILD PROCESS
                char* command= args[0];
                int statuscode=execvp(command, args);
                if(statuscode==-1){ //checking that execvp worked properly
                    printf("process did not terminate correctly");
                }
            }
            //(3) If command included & parent will invoke wait
        }
    return 0;
}
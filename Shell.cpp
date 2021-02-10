#include <iostream>
#include <stdio.h>
#include <unistd.h>

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
            //(2) The child process will invoke execvp()
            //(3) If command included & parent will invoke wait
        }

}
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <signal.h>
#include <cstring>
#include <sys/wait.h>

#define MAX_LINE 80 //The maximum length command
using namespace std;

void parse(char* line, char *args[]);

int main(void){

    char* args[MAX_LINE/2 + 1]; //command line arguments
    int should_run = 1; //flag to determine when to exit program

        while(should_run){
            printf("osh>");
            fflush(stdout);

            //after reading user input the steps are :
            char line[1024];
            fgets(line,MAX_LINE,stdin);
            
            if(strcmp(line,"exit\n")==0){
                exit(1);
            }
           
            parse(line, args);
           
            //(1) fork a child process using fork()
            pid_t child_pid;
            child_pid= fork();
            if(child_pid<0){
                printf("ERROR FORK failed at line 31");
                exit(1);
            }
            //(2) The child process will invoke execvp()
            if (child_pid == 0){ //CHILD PROCESS
                int statuscode=execvp(args[0], args);
                if(statuscode==-1){ //checking that execvp worked properly
                    printf("process did not terminate correctly\n");
                    exit(1);
                }
            }
            //(3) If command included & parent will not invoke wait
           else{  //parent process
                int wait_flag=0;
                for(int i=0;args[i]!=NULL;i++){
                    if(strcmp(args[i], "&")==0){
                       wait_flag++;
                    }
                }
                if(wait_flag==0){
                    wait(NULL);
                }
            }
        }
    return 0;
}


//converts the line into args
void parse(char* line, char **argv){
    while(*line !='\0'){
        while(*line == ' ' || *line == '\t' || *line == '\n')
            *line++='\0';
        *argv++ =line;
        while(*line !='\0' && *line != ' ' && *line != '\t' && *line != '\n')
            line++;
    }
    *argv= NULL;
    
}
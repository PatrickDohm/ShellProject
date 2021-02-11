#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <signal.h>
#include <cstring>
#include <sys/wait.h>
#include <vector>

#define MAX_LINE 80 //The maximum length command
using namespace std;

void parse(char *line, char *args[]);
void printHistory(vector<string> history, int historyNum);

int main(void)
{

    char *args[MAX_LINE / 2 + 1]; //command line arguments
    int should_run = 1;           //flag to determine when to exit program
    vector<string> history;

    history.clear();
    int historyNum = 1; //use this to write what command number we are on

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        //after reading user input the steps are :
        char line[1024];
        fgets(line, MAX_LINE, stdin);


        //handle history and commands that are specific to here
        if (strcmp(line, "exit\n") == 0)
        {
            exit(1);
        }
        else if (strcmp(line, "history\n") == 0)
        {
            printHistory(history, historyNum);
        }
        else if (strcmp(line, "!!"))
        { //if the user types !! it will repeat the most recent command
            strcpy(line, history[history.size() - 1].c_str());
        }
        string add_to_history = line;
        history.push_back(add_to_history); // add current command to history
        if (history.size() > 10)
        { //History has a max size of 10, destroy the first entry if it gets too big
            history.erase(history.begin());
        }
        historyNum++; //need to increment the history number



        parse(line, args);



        //(1) fork a child process using fork()
        pid_t child_pid;
        child_pid = fork();
        if (child_pid < 0)
        {
            printf("ERROR FORK failed at line 31");
            exit(1);
        }
        //(2) The child process will invoke execvp()
        if (child_pid == 0)
        { //CHILD PROCESS
            int statuscode = execvp(args[0], args);
            if (statuscode == -1)
            { //checking that execvp worked properly
                printf("process did not terminate correctly\n");
                exit(1);
            }
        }
        //(3) If command included & parent will not invoke wait
        else
        { //parent process
            int wait_flag = 0;
            for (int i = 0; args[i] != NULL; i++)
            {
                if (strcmp(args[i], "&") == 0)
                {
                    wait_flag++;
                }
            }
            if (wait_flag == 0)
            {
                wait(NULL);
            }
        }
    }
    return 0;
}

//converts the line into args
void parse(char *line, char **argv)
{
    while (*line != '\0')
    {
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';
        *argv++ = line;
        while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
            line++;
    }
    *argv = NULL;
}

//will print the entire history vector
void printHistory(vector<string> history, int historyNum)
{
    cout << "Command Line History" << endl;
    for (int i = history.size() - 1; i > 0; --i)
    {
        cout << historyNum << history[i] << endl;
        historyNum--;
    }
}

//
//  main.c
//  OS I Class
//
//  Created by CloudStrife on 9/13/17.
//  Copyright © 2017 CloudStrife. All rights reserved.
//  The Simple Shell
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

char *getCommandLine(char *aLine);
char **parseCommandLine(char **arguments, char *anArgument, char *commandLine);
void execute(char **args);

int main(int argc, const char * argv[])
{
    char *cmdLine = (char *)malloc(sizeof(char) * MAX_SIZE);
    char *anArg = (char *)malloc(sizeof(char) * MAX_SIZE);
    char **args = (char **)malloc(sizeof(anArg) * 6);
    int RUNNING;
    
    /* Run continuously and display a prompt when waiting for input. Prompt should be
     EXACTLY $ and nothing else. */
    RUNNING = 1;
    while(RUNNING)
    {
        //Print the prompt
        printf("$");
        cmdLine = getCommandLine(cmdLine);
        args = parseCommandLine(args, anArg, cmdLine);
        
        if(strcmp(args[0], "exit"))
            exit(0);
        execute(args);
        /*else
         puts(args[1]);*/
        RUNNING = 0;
    };
    
    
    return(0);
}

char *getCommandLine(char *aLine)
{
    //Read a command line from stdin and store it
    fgets(aLine, MAX_SIZE, stdin);
    if (aLine == NULL)
        fprintf(stderr, "error: %s\n", "***** ERROR: Memory Error\n");
    
    return aLine;
}

char **parseCommandLine(char **args, char *anArg, char *cmdLine)
{
    //Split a cmd line into args and store them in the args array
    anArg = strtok(cmdLine, " ,.-");
    int count = 0;
    while(anArg != NULL)
    {
        //printf("%s\n",anArg);
        args[count] = anArg;
        //printf("%s\n",args[count]);
        anArg = strtok(NULL, " ,.-");
    }
    return args;
}

void execute(char **args)
{
    //Execute the command using the args
    pid_t  pid;
    int    status;
    
    if ((pid = fork()) < 0) // fork a child process
    {
        fprintf(stderr, "error: %s\n", "***** ERROR: forking the child process failed\n");
        exit(1);
    }
    else if (pid == 0) // let the child process execute
    {
        // execute the command in the child process
        if (execvp(*args, args) < 0)
        {
            fprintf(stderr, "error: %s\n", "***** ERROR: the execution process failed\n");
            exit(1);
        }
    }
    else // for the parent:
    {
        // wait for completion of child process
        while (wait(&status) != pid)
            ;
    }
}


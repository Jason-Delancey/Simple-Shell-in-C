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
#include <unistd.h>

#define MAX_SIZE 1024
#define MAX_ARGS 4

char *getCommandLine(char *aLine);
char **parseCommandLine(char **arguments, char *anArgument, char *commandLine);
void sh_execute(char **args);

char *sh_cd(char **args, char *directory);
void sh_exit(void);

int main(int argc, const char * argv[])
{
    
    /* Run continuously and display a prompt when waiting for input. Prompt should be
     EXACTLY $ and nothing else. */
    int RUNNING = 1;
    while(RUNNING)
    {
        
        char *cmdLine = (char *)malloc(sizeof(char) * MAX_SIZE);
        char *anArg = (char *)malloc(sizeof(char) * MAX_SIZE);
        char **args = (char **)malloc(sizeof(anArg) * MAX_ARGS);
        
        //Print the prompt, get command line, parse command line, check for exit command
        printf("$");
        cmdLine = getCommandLine(cmdLine);
        args = parseCommandLine(args, anArg, cmdLine);
        if(strcmp(args[0], "exit"))
            sh_exit();
        
        sh_execute(args);
        /*else
         puts(args[1]);*/
        free(cmdLine);
        free(anArg);
        free(args);
        sh_exit();
    };

}

void sh_exit(void)
{
    exit(0);
}

char *sh_cd(char **args, char *directory)
{
    if (args[1] == NULL)
        fprintf(stderr, "error: %s\n", "***** ERROR: Missing argument\n");
    else
        directory = args[1];
    return directory;
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

void sh_execute(char **args)
{
    //Execute the command using the args
    pid_t  pid;
    
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "error: %s\n", "***** ERROR: forking the child process failed\n");
        sh_exit();
    }
    else if (pid == 0) // let the child process execute
    {
        // execute the command in the child process
        if (execvp(*args, args) < 0)
        {
            fprintf(stderr, "error: %s\n", "***** ERROR: the execution process failed\n");
            sh_exit();
        }
    }
    
}


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

int main(int argc, const char * argv[])
{
    char *cmdLine;
    char **args;
    int RUNNING,count;
    
    /* Run continuously and display a prompt when waiting for input. Prompt should be
     EXACTLY $ and nothing else. */
    RUNNING = 1;
    while(RUNNING)
    {
        //Print the prompt
        printf("$");
        
        //Read a command line from stdin
        cmdLine = (char *)malloc(sizeof(char) * MAX_SIZE);
        fgets(cmdLine, MAX_SIZE, stdin);
        if (cmdLine == NULL)
        {
            fprintf(stderr, "Memory Error");
            break;
        }
        
        //Split a cmd line into args and store them in the args array
        char *anArg = (char *)malloc(sizeof(char) * MAX_SIZE);
        args = (char **)malloc(sizeof(anArg) * 6);
        
        
        anArg = strtok(cmdLine, " ,.-");
        count = 0;
        while(anArg != NULL)
        {
            //printf("%s\n",anArg);
            args[count] = anArg;
            //printf("%s\n",args[count]);
            anArg = strtok(NULL, " ,.-");
        }
        
        if(strcmp(args[0], "exit"))
            exit(0);
        /*else
         puts(args[1]);*/
        
        //Execute the command using the args
        pid_t  pid;
        int    status;
        
        if ((pid = fork()) < 0) // fork a child process
        {
            fprintf(stderr, "***** ERROR: forking the child process failed\n");
            exit(1);
        }
        else if (pid == 0) // let the child process execute
        {
            // execute the command unless it fails and returns -1
            if (execvp(*args, args) < 0)
            {
                printf("***** ERROR: the exec process failed\n");
                exit(1);
            }
        }
        else // for the parent:
        {
            // wait for completion of child process
            while (wait(&status) != pid)
                ;
        }
        RUNNING = 0;
    };
    
    
    return(0);
}


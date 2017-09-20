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
       
        
        /*Execute the command using the args
        pid_t pid;
        int status;
        
        pid = fork();
        if ( pid == 0 )
        {
            printf( "This is being printed from the child process\n" );
            if(execvp(cmdLine[0], cmdLine) == -1)
                fprintf(stderr, "Error in fork() call");
        }
        else
        {
            printf( "This is being printed in the parent process:\n"
                   " - the process identifier (pid) of the child is %d\n", pid );
        }*/

        
        RUNNING = 0;
    };
    
    
    return(0);
}

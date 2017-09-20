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
#define MAX_SIZE 1024

int main(int argc, const char * argv[])
{
    char *cmdLine;
    char **args;
    int state;
    
    /* Run continuously and display a prompt when waiting for input. Prompt should be
     EXACTLY $ and nothing else. */
    state = 0;
    while(state == 0)
    {
        //Print the prompt
        printf("$");
        
        //Read a command line from stdin
        cmdLine = (char *)malloc(sizeof(char) * MAX_SIZE);
        fgets(cmdLine, MAX_SIZE, stdin);
        if (cmdLine == NULL)
        {
            puts("Memory Error");
            state = 1;
        }
        else
        {
            printf("You typed the command: %s\n",cmdLine);
        }
        
        
        state = 1;
    };
    
    
    return(0);
}

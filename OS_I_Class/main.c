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

#define MAX_SIZE 40
#define MAX_ARGS 3
#define MAX_CMDS 3

int RUNNING;

char *getCommandLine(char *aLine);
char **parseCommandLine(char **arguments, char *anArgument, char *commandLine);
int sh_execute(char **args);

char *sh_cd(char **args, char *directory);
int sh_exit(void);
void sh_echo(char **args);

int main(int argc, const char * argv[])
{
    
    /* Run continuously and display a prompt when waiting for input. Prompt should be
     EXACTLY $ and nothing else. */
    RUNNING = 1;
    while(RUNNING == 1)
    {
        char *cmdLine = (char *)calloc(MAX_SIZE, sizeof(char));
        char *anArg = (char *)calloc(MAX_SIZE, sizeof(char));
        char **args = (char **)calloc(MAX_ARGS, sizeof(anArg));
        char **built_ins = (char **)calloc(MAX_CMDS, sizeof(anArg));
        if (cmdLine == NULL || anArg == NULL || args == NULL || built_ins == NULL)
        {
            fprintf(stderr, "%s\n", "***** ERROR: Memory Allocation Error\n");
            break;
        }
        
        /* Print the prompt, get command line, parse command line, check if no command entered */
        printf("$");
        cmdLine = getCommandLine(cmdLine);
        args = parseCommandLine(args, anArg, cmdLine);
        if (strtok(cmdLine, " ,.-\n") == NULL)
        {
            fprintf(stderr, "%s\n", "***** ERROR: No command entered\n");
            break;
        }
        /*for (int i = 0; i < MAX_ARGS; i++) //test case
        {
            if(args[i] != NULL)
                printf("%s\n", args[i]);
        }*/
        
        
        /* Execution of built-in commands */
        built_ins[0] = "exit"; built_ins[1] = "cd"; built_ins[2] = "history"; built_ins[3] = "echo";
        int command = -1;
        for (int j = 0; j < 4; j++)
        {
            if(strcmp(args[0], built_ins[j]) == 0)
                command = j;
        }
        if (command < 0)
        {
            fprintf(stderr, "%s\n", "***** ERROR: Invalid command\n");
            break;
        }
        //printf("You entered the command #%d: %s\n", command, built_ins[command]);
        command++;
        switch (command)
        {
            case 1:
                RUNNING = sh_exit();
                break;
            case 2:
                sh_cd(args, args[1]);
                break;
            case 3:
                printf("This is history\n");
                break;
            case 4:
                sh_echo(args);
                break;
                
            default:
                fprintf(stderr, "%s\n", "***** ERROR: Can't find built-in command\n");
                RUNNING = 0;
                break;
        }
        
        free(cmdLine);
        free(anArg);
        free(args);
        free(built_ins);
        //RUNNING = 0;
        /* execute the commands not built-in
        sh_execute(args);*/
    };
    
    return 0;
}

char *getCommandLine(char *aLine)
{
    /* Read a command line from stdin and store it */
    fgets(aLine, MAX_SIZE, stdin);
    
    return aLine;
}

char **parseCommandLine(char **args, char *anArg, char *cmdLine)
{
    /* Split a cmd line into args and store them in the args array */
    anArg = strtok(cmdLine, " ,.-");
    int count = 0;
    while(anArg != NULL)
    {
        args[count] = anArg;
        count++;
        anArg = strtok(NULL, " ,.-");
    }
    
    return args;
}

int sh_execute(char **args)
{
    /* Execute the command using the args */
    pid_t  pid;
    int status;
    
    pid = fork();
    //printf("The process id is: %d\n",pid);
    if (pid == 0) // let the child process execute
    {
        /* execute the command in the child process */
        if (execvp(*args, args) < 0)
        {
            fprintf(stderr, "%s\n", "***** ERROR: the execution process failed\n");
            exit(0);
        }
    }
    else if (pid < 0)
    {
        fprintf(stderr, "%s\n", "***** ERROR: forking the child process failed\n");
        exit(0);
    }
    else
    {
        /* wait for child process to end */
        while (wait(&status) != pid)
            ;
    }
    
    return 1;
}

void sh_echo(char **args)
{
    int i = 0;
    while (i < MAX_ARGS)
    {
        printf("%s ",args[i]);
        i++;
    }
    printf("\n");
}

int sh_exit(void)
{
    return 0;
}

char *sh_cd(char **args, char *directory)
{
    if (args[1] == NULL)
        fprintf(stderr, "%s\n", "***** ERROR: Missing argument\n");
    else
        directory = args[1];
    return directory;
}


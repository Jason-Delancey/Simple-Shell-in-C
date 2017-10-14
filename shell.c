//
//  Created by CloudStrife on 9/13/17.
//  Copyright © 2017 CloudStrife. All rights reserved.
//  The Simple Shell
//
//  Creates a shell that runs continuously and display a prompt when 
//  waiting for input. The prompt should be EXACTLY '$' and nothing else
//
//  There is currently a runtime error in the execution of the history function
//
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* max length of the command */
#define MAX_ARGS 4
#define MAX_BUILT_INS 3
#define MAX_HISTORY 10

char *getCommandLine(char *aLine);
char **parseCommandLine(char **arguments, char *anArgument, char *commandLine);
int sh_execute(char **args);
char *sh_cd(char **args, char *directory);
int sh_exit(void);
void sh_history(char **args);

int main(int argc, const char * argv[])
{
    int running, command, j, history_counter;
    char *cmdLine, *anArg;
    char **args, **built_ins, **history;
    
    cmdLine = (char *)malloc(MAX_LINE*sizeof(char));
    anArg = (char *)malloc(MAX_LINE*sizeof(char));
    args = (char **)malloc(MAX_ARGS*sizeof(anArg));
    built_ins = (char **)malloc(MAX_BUILT_INS*sizeof(anArg));
    history = (char **)malloc(MAX_HISTORY*sizeof(cmdLine));
    
    for(j = 0; j < MAX_ARGS; j++)
    	args[j] = NULL;
    for(j = 0; j < MAX_BUILT_INS; j++)
    	built_ins[j] = NULL;
    for(j = 0; j < MAX_HISTORY; j++)
    	history[j] = NULL;
    
    running = 1; history_counter = 0;
    while(running){
        
        if (cmdLine == NULL || anArg == NULL){
            fprintf(stderr, "%s\n", "*** ERROR: Memory Allocation Failed\n");
            break;
        }
        
        /* Print the prompt, get command line, parse command line, check if no 
        command was entered */
        printf("$");
        cmdLine = getCommandLine(cmdLine);
        args = parseCommandLine(args, anArg, cmdLine);
        if (strtok(cmdLine, " ,.-\n") == NULL){
            fprintf(stderr, "%s\n", "*** ERROR: No command entered\n");
            break;
        }
        if(history_counter < MAX_HISTORY){
        	history[history_counter] = cmdLine;
        	history_counter++;
        }

        /* Execution of built-in commands */
        built_ins[0] = "exit"; 
        built_ins[1] = "cd"; 
        built_ins[2] = "history"; 
        
        command = -1;
        for (j = 0; j < MAX_BUILT_INS; j++){
            if(strcmp(args[0], built_ins[j]) == 0)
                command = j;
        }
        
        if (command > -1){
        	printf("You entered command #%d: %s\n", command, built_ins[command]);
        	command++;
        	switch (command){
            		case 1:
                		running = sh_exit();
                		break;
            		case 2:
                		sh_cd(args, args[1]);
                		break;
            		case 3:
                		sh_history(history);
                		break;
                
            		default:
                	fprintf(stderr, "%s\n", "*** ERROR: invalid switch\n");
                	running = 0;
                	break;
        	}	
        }
        else
		running = sh_execute(args);
    }
    free(cmdLine);
    free(anArg);
    free(args);
    free(built_ins); 
    free(history);  
    
    return 0;
}

char *getCommandLine(char *aLine){
    /* Read a command line from stdin and store it */
    fgets(aLine, MAX_LINE, stdin);
    
    return aLine;
}

char **parseCommandLine(char **args, char *anArg, char *cmdLine){

	int count = 0;
	
	/* Split a cmd line into args and store them in the args array */
	anArg = strtok(cmdLine, " ,.-");
	while(anArg != NULL){
        	args[count] = anArg;
        	count++;
        	anArg = strtok(NULL, " ,.-");
    	}
    
    	return args;
}

int sh_exit(void){
    	return 0;
}

void sh_history(char **history){
	int j;
	for(j = MAX_HISTORY-1; j > -1; j--){
		printf("%d: %s\n", j, history[j]);
	}
}

char *sh_cd(char **args, char *directory){
    if (args[1] == NULL)
        fprintf(stderr, "%s\n", "***** ERROR: Missing argument\n");
    else
        directory = args[1];
        
    return directory;
}

/* Execute the command using the args entered. */
int sh_execute(char **args){
 
    pid_t  pid;
    int status;
    
    pid = fork();
    if (pid < 0){
        fprintf(stderr, "%s\n", "** ERROR: fork failed\n");
        status = -1;
    }
    else if (pid == 0){ /* the child process */
        if (execvp(args[0], args) < 0){
            fprintf(stderr, "%s\n", "** ERROR: the execution process failed\n");
            status = -1;
        }
    }
    else{
        /* wait for child process to end */
        while (wait(&status) != pid)
            ;
    }
    
    if(status == 0)
    	status += 1;
    	
    return status;
}

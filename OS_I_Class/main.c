//
//  main.c
//  OS I Class
//
//  Created by CloudStrife on 9/13/17.
//  Copyright © 2017 CloudStrife. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLUMNS 10
#define SIZE 1024


// void evaluate(int aNumber);

int main(int argc, const char * argv[])
{
    
    /*char *sto;
    sto = (char *)malloc(sizeof(char) * SIZE);
    
    printf("Hello! Please type a word:\n");
    scanf("%s",sto);
    if (sto == NULL)
    {
        puts("Memory Error");
        return(1);
    }
    else
        puts(sto);*/
    
    /*char j = 'J';
    char *c = &j;
    printf("This is the contents of variable j: %c\n",*c);*/
    
    /*int pokey;
    int *p;
    
    pokey = 987;
    p = &pokey;
    
    printf("The address of 'pokey' is %p\n", &pokey);
    printf("The contents of 'pokey' is %d\n", pokey);
    
    printf("The address of 'pokey' is %p\n", p);
    printf("The contents of 'pokey' is %d\n", *p);*/
    
    /*char sentences[ROWS][COLUMNS] = {"string1", "string2", "string3", "PINOCCHIO"};
    int x = 0;
    for(x = 0; x < ROWS; x++)
        puts(sentences[x]);*/
    
    /* used for testing the protoptype function evaluate()
     evaluate(10);*/
        
    /* ouutput values 10-1
     int x;
     for(x=10 ; x>0 ; x--)
     {
     printf("%2d\n",x);
     }*/
        
    /* ouutput even values 2-20
     int x=2;
     while (x<21)
     {
     printf("%2d\n",x);
     x+=2;
     }*/
        
    /* ouutput values 1-20
     int x;
     for(x=1 ; x<21 ; x++)
     {
     printf("%2d\n",x);
     }*/
        
    /* creating random generator, seeding randomizer
     int r;
     srand ((unsigned)time(NULL));
     r = rand();
     printf("This is a pseudo random number: %d\n",r);*/
        
    /* using a place holder to output an integer
     printf("Everyone knows 2+2 = %d\n",2+2);*/
        
    /* using an escape character to include brackets inside brackets
     printf("My name is \"Jason\"\n");*/
        
    /* puts("Just another");
     puts("...string.");*/
        
        return(0);
}

/*void evaluate(int aNumber)
 {
 if(aNumber < 10)
 printf("%d is less than 10\n",aNumber);
 else if(aNumber > 10)
 printf("%d is greater than 10\n",aNumber);
 else
 printf("%d is equal to 10\n",aNumber);
 }*/

/*
 Default code inserted when creating a new source file
 #include <stdio.h>
 
 int main(int argc, const char * argv[]) {
 // insert code here....
 printf("Hello, Columbia!\n");
 return 0;
 }*/

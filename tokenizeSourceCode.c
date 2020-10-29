#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "metadata.h"

// typedef struct token{
//     char* token;
//     token_name tokenname;
//     int line_num;
//     struct token *prev;
//     struct token* next;
// }Token;

Token* add_token(Token* head, char* str, int line);
void printll(Token* head);
void deleteblankspaces(char *s)
{
	int  i,k=0;
 
	 for(i=0;s[i];i++)
    {
     	s[i]=s[i+k];
 
     	
     	if(s[i]==' '|| s[i]==9 || s[i] == '\n')
     	{
		  k++;
		  i--;
	    }
     	
    }
}

Token* tokeniseSourcecode(char* file, Token* head)
{
    int line = 1;
    head = NULL;
    char str[100];
    char delim[] = " \n";

    // scanf("%[^'z']",str);
    FILE *f;
    f=fopen(file,"r");

    while(fgets(str,100,f)!= NULL)
    {
        char* ptr = strtok(str, delim);

        while(ptr != NULL){
            head = add_token(head, ptr, line);
            // printf("%s ", ptr);
            ptr = strtok(NULL, delim);
        }
        line++;
    }
    head = add_token(head, "$", 0);
    fclose(f);

    // printll(head);
    /* This loop will show that there are zeroes in the str after tokenizing */

    return head;
}


void printTokenStream(Token* head){
    int line_temp = 0;
    if(head == NULL) return;
    Token* temp = head;
    printf("{ %s, %d } ", temp->token, temp->line_num);
    // printf("%s %d ",temp->token, temp->tokenname);
    // printf("%s ",temp->token);
    // deleteblankspaces(temp->token);
    temp = temp->next;
    while(temp){
        printf("-> { %s, %d } ", temp->token, temp->line_num);
        
        // printf("%s %d ",temp->token, temp->tokenname);
        // printf("%s ",temp->token);
        if(line_temp!=temp->line_num)
        {
            line_temp = temp->line_num;
            printf("\n");
        }
        temp = temp->next;
    }
    printf("\n");
}

Token* add_token(Token* head, char* str, int line){
    Token* new = (Token*) malloc(sizeof(Token));
    new->token = (char* ) malloc(sizeof(str));
    strcpy(new->token, str);
    deleteblankspaces(new->token);
    new->next = NULL;
    new->line_num = line;
    int flag=0;
    for (int i = 0; i < 62; i++)
    {
        if(flag==0&&i==61&&strcmp(new->token,enumtochar[i]))
        {
            if(isdigit(new->token[0]))
            {
                new->tokenname=3;
            }
            else new->tokenname = 2;
            continue;
        }
        if(strcmp(new->token,enumtochar[i])) continue;
        flag=1;
        if(i>29&&i<37) new->tokenname = 0;
        
        else if(i>36) new->tokenname = 1;

        else new->tokenname = 2;   
        break; 
    }
    

    if(head == NULL){
        head = new;
        return head;
    }

    Token* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp->next = new;
    return head;
}

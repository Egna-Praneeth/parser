/*
Group no.: 11
Group member names and IDs:
Aditya V. Bodade
2018A7PS0256P

Egna Praneeth Gummana
2018A7PS0284P

Yogya Modi
2018A7PS0235P

Kartikaya Sharma
2018A7PS0386P

*/
#include "metadata.h"

Grammar* addtoken(Grammar* head, char* str, bool isTerm){
    Grammar* new = (Grammar*) malloc(sizeof(Grammar));
    // new->data = (char* ) malloc(sizeof(str));
    // strcpy(new->data, str);
    for (int i = 0; i < 63; i++)
    {
        if(strcmp(str,enumtochar[i])) continue;
        new->symbol = i;
    }
    
    new -> next = NULL;
    new -> prev = NULL;
    new->is_term = isTerm;
    // printf( "bruh\n");

    if(head == NULL){
        // printf( "bruh2\n");
        head = new;
        return head;
    }
    // printf("bruh3\n");

    Grammar* temp = head;
    while(temp->next){
        temp = temp->next;
    }
    temp -> next = new;
    // new -> prev = temp;
    return head;
}



void readGrammar(char* filename, Grammar* G[]){
    
    FILE *fp = fopen(filename, "r");
    
    for(int i = 0; i < 60 ;i++)
        G[i] = NULL;
    int rule_count = 0;

    char delim[] = " \n";

    char buffer[200]; // stores a line from grammar file

    while(fgets(buffer,200,fp) != NULL){
        char * word = strtok(buffer, delim);
        bool isTerm;
        // int i=0;
        while(word != NULL){
            isTerm = false;
            if(word[0] == '\'' && word[strlen(word)-1] == '\'')
            {
                isTerm = true;
                int  j,k=0;
 
                for(j=0;word[j];j++)
                {
                    word[j]=word[j+k];
            
                    
                    if(word[j]=='\'')
                    {
                    k++;
                    j--;
                    }
                    
                }
            }
            if(word[0] == '-' && word[1] == '>')
                goto next;    
            //  printf("\na %s\n",word);   
            G[rule_count] = addtoken(G[rule_count], word,isTerm); // ye line somewheok ok ok ook re haging
            // printf("%d ", ++i);
            next:
            word = strtok(NULL, delim);
        }
        rule_count++;
    }
}

void printll(Grammar *head){

    if(head == NULL) return;

    Grammar* temp = head;
    printf("{ %s, %d }", enumtochar[temp->symbol], temp->is_term);
    temp = temp->next;
    while(temp!=NULL){
        printf("-> { %s, %d }", enumtochar[temp->symbol], temp->is_term);
        temp = temp->next;
    }
}


void printGrammar(Grammar** G){

    for(int i = 0; G[i] != NULL && G[i] -> next != NULL  ;i++){
        printf("This is rule no. %d\n", i+1);
        printll(G[i]);
        printf("\n");
        }
}



// int main()
// {

//     for(int i = 0; G[i] != NULL && G[i] -> next != NULL  ;i++){
//         printf("This is rule no. %d\n", i+1);
//         printll(G[i]);
//         printf("\n");

//     }
//     // for (int i = 0; i < 60; i++)
//     // {
//     //     printf("%u\n",G[i].array);
//     // }
    
//     return 0;
    
// }

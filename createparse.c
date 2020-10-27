#include "metadata.h"

/*

S -> program B
B -> var B 
B -> var

sample:
" program a c b  " 

*/
char* enumtochar[4];

int main(){
    enumtochar[0] = "S";
    enumtochar[1] = "B";
    enumtochar[2] = "program";
    enumtochar[3] = "var";
    Grammar* G = readGrammar();
    Token* tokstream = tokeniseSourcecode();
    //TreeNode* root = createParseTree(tokstream, G);
}


Grammar* readGrammar(void){
    //Grammar grammar [3];
    Grammar* grammar = (Grammar*) malloc(sizeof(Grammar)*3);
    //S-> program B
    grammar[0].is_term = 0;
    grammar[0].symbol = S; 
    grammar[0].next = (Grammar *) malloc(sizeof(Grammar));
    grammar[0].prev = NULL;
    grammar[0].next->is_term = 1;
    grammar[0].next->symbol = program;
    grammar[0].next->next = (Grammar *) malloc(sizeof(Grammar));
    grammar[0].next->prev = &grammar[0];
    grammar[0].next->next->is_term = 0;
    grammar[0].next->next->symbol = B;
    grammar[0].next->next->next = NULL;
    grammar[0].next->next->prev = grammar[0].next;

    //B-> var B
    grammar[1].is_term = 0;
    grammar[1].symbol = B; 
    grammar[1].next = (Grammar *) malloc(sizeof(Grammar));
    grammar[1].prev = NULL;
    grammar[1].next->is_term = 1;
    grammar[1].next->symbol = var;
    grammar[1].next->next = (Grammar *) malloc(sizeof(Grammar));
    grammar[1].next->prev = &grammar[1];
    grammar[1].next->next->is_term = 0;
    grammar[1].next->next->symbol = B;
    grammar[1].next->next->next = NULL;
    grammar[1].next->next->prev = grammar[1].next;
    //B-> var
    grammar[2].is_term = 0;
    grammar[2].symbol = B; 
    grammar[2].next = (Grammar *) malloc(sizeof(Grammar));
    grammar[2].prev = NULL;
    grammar[2].next->is_term = 1;
    grammar[2].next->symbol = var;
    grammar[2].next->next = NULL;
    grammar[2].next->prev = &grammar[2];
    return grammar;
}

Token* tokeniseSourcecode(void){
    Token* head;
    head = (Token *) malloc(sizeof(Token)); 
    strcpy(head->token, "program");
    strcpy(head->tokenname, "keyword");
    head->next = (Token *) malloc(sizeof(Token));
    head->prev = NULL;
    strcpy(head->next->token, "a");
    strcpy (head->next->tokenname, "identifier");
    head->next->next = (Token *) malloc(sizeof(Token));
    head->next->prev = head;
    strcpy(head->next->next->token, "b");
    strcpy(head->next->next->tokenname, "identifier");
    head->next->next->next = (Token *) malloc(sizeof(Token));
    head->next->next->prev = head->next;
    strcpy(head->next->next->next->token, "c");
    strcpy(head->next->next->next->tokenname, "identifier");
    head->next->next->next->next = NULL;
    head->next->next->next->prev = head->next->next;
    return head;
}

TreeNode* createParseTree(Token* s, Grammar* G){
    struct StackNode* stack = NULL;
    TreeNode* root = NULL;
    push(&stack, 0, S, -1, root); // push S into stack
    //create root of tree with S
    Token* tkptr = s;

    while(!isEmpty(stack)){
        struct StackNode* top = peek(stack);
        pop(&stack);
        if(top->is_term == 0){
            //TreeNode* linkofnode = createNode(top-> parenttreelink, top->data, top->ruleindex);
            TreeNode* linkofnode = createNode(top);
            int ruleindex = pushRule(stack, G, linkofnode, top->data, 0);
        }
         else /*top is a terminal */ {
             if(!strcmp(tkptr->tokenname, "identifier") && top->data == var) {
                 tkptr = tkptr->next;
                 //createnode for terminal
                 createNode(top->parenttreelink, top->data, top->ruleindex);
             }//below else if commented for now as there is no number in the sample grammar
            /* else if(!strcmp(tkptr->tokenname, "literal") && top->data == number){
                    tkptr = tkptr->next;
                 createNode(top->parenttreelink, top->data, top->ruleindex);
             }*/ // only possible case left is keywords
             else if(!strcmp(tkptr->token, enumtochar[top->data])){
                 tkptr = tkptr->next;
                 //createnode for terminal
                 createNode(top->parenttreelink, top->data, top->ruleindex);
             }
             //below else case is when no terminal matches;
             else {
                 removeAndReplace();
             }
       
        }

    }
}


  

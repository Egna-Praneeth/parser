#include "metadata.h"

/*

S -> program B
B -> var B 
B -> var

sample:
" program a c b  " 

*/
char* enumtochar[4];

void printParseTree(TreeNode* root){
    if(root == NULL) return ;
    printf("%s\n", enumtochar[root->symbol]);
    if(root->child == NULL) return ;
    TreeNode* head = root->child;
    while(head){
        printParseTree(head);
        head = head->nextsib;
    }

}
int main(){
    enumtochar[0] = "S";
    enumtochar[1] = "B";
    enumtochar[2] = "program";
    enumtochar[3] = "var";
    Grammar* G = readGrammar();
    Token* tokstream = tokeniseSourcecode();
    TreeNode* root = createParseTree(tokstream, G);
    printParseTree(root);
}


Grammar* readGrammar(void){
    printf("IN readGrammar function\n");
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
    printf("IN tokeniseSourcecode function\n");
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
    Token* t = head->next->next->next;
    t->next = (Token *) malloc(sizeof(Token));
    t->next->prev = t;
    strcpy(t->next->token,"$");
    return head;
}

TreeNode* createParseTree(Token* s, Grammar* G){
    printf("IN createParseTree function\n");
    TreeNode* root = NULL;
    root = (TreeNode*)malloc(sizeof(TreeNode));
        root->ruleno = -1 ;
        root->is_term = 0;
        root->symbol = S;
        root->parent = NULL;
        root->child = NULL;
        root->nextsib = NULL;
    push(0, S, -1, root); // push S into stack
    //create root of tree with S
    Token* tkptr = s;
    Stack *top;
    while(!isEmpty()){
        //printf("inside stack\n");
        top = peek();
        pop();
        if(top->is_term == 0){
            TreeNode* linkofnode = createNode(top);
            int ruleindex = pushRule(G, linkofnode, top->data, 0);
        }
        else /*top is a terminal */{
            //  if(top->data == E){
            //      pop();
            //  }
            if(!strcmp(tkptr->tokenname, "identifier") && top->data == var) {
                 tkptr = tkptr->next;
                 //createnode for terminal
                 createNode(top);
             }//below else if commented for now as there is no number in the sample grammar
            /* else if(!strcmp(tkptr->tokenname, "literal") && top->data == number){
                    tkptr = tkptr->next;
                 createNode(top->parenttreelink, top->data, top->ruleindex);
             }*/ // only possible case left is keywords
             else if(!strcmp(tkptr->token, enumtochar[top->data])){
                 tkptr = tkptr->next;
                 //createnode for terminal
                 createNode(top);
             }
             //below else case is when no terminal matches;
             else {
                 removeAndReplace(top->parent, G, top->ruleno, &tkptr);
             }
       
        }

    }
    //printf("root is: %p", root);
    return root;
}


  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// NOTICE : FROM PREZ
// 22/10 16:40 , code assuming no enums
/*

S -> program B
B -> var B 
B -> var

sample:
" program a c b  " 


 */
typedef enum symbol {S , B, program , var  } Symbol;

//---------------------STACK------------------------------------------
struct StackNode { 
    bool is_term;
    Symbol data;
    struct StackNode* next; 
}; 

struct StackNode* newNode(bool is_term, Symbol data);
int isEmpty(struct StackNode* root);
void push(struct StackNode** root, bool is_term, Symbol data);
int pop(struct StackNode** root);
int peek(struct StackNode* root);
//--------------------------STACK FUNCTIONS END HERE------------------

typedef struct treenode {
    int rule_num;
    Symbol symbol;
    struct treenode* parent;
    // struct treenode* childarray;
    struct treenode* nextsib;
    struct treenode* child;
        
} TreeNode;

typedef struct grammarNode {
    bool is_term;
    // enum nonterm data_n;
    // enum term data;
    Symbol symbol;
    struct grammarNode *next;
    struct grammarNode *prev;
}Grammar;

typedef struct token{
    char token[10]; //lexeme
    char tokenname[100]; //token name
    struct token *next; 
    struct token *prev;
    // lexeme, tokenname and 
} Token;

//functions below
Grammar* readGrammar(void);
Token* tokeniseSourcecode(void);
TreeNode* createParseTree(Token* s, Grammar* G);
TreeNode* createNode(Symbol symbol, int rule_num, )


int main(){
    
    Grammar* G = readGrammar();
    Token* tokstream = tokeniseSourcecode();
    TreeNode* root = createParseTree(tokstream, G);
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
    push(&stack, 0, S);
    TreeNode* root = NULL;
    //create root of tree with S
    //root = createNode(symbol, 1);
    while(!isEmpty(stack)){
        struct StackNode* top = peek(stack);
        pop(&stack);
        if(top->is_term == 0){
            //createNode()
            
        }
        else {
            if(!strcmp(tkptr->tokenname, "identifier") && top->data == var) {
                pop(&root);
                tkptr = tkptr ->next;
            }
            //suppose operators and separators are also keywords
            else if(!strcmp(tkptr->tokenname, "keyword") && it matches with the top of the stack ){ //able to compare
                pop(&root);
                tkptr = tkptr ->next;
                
            }
            else //code to handle this case

            //mistake si 
            //operator
            //separator
            //number will be handled like identifier
        }
    }

}


struct StackNode* newNode(bool is_term, Symbol data) 
{ 
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode)); 
    stackNode->data = data;
    stackNode-> is_term = is_term; 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode* root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, bool is_term, Symbol data) 
{ 
    struct StackNode* stackNode = newNode(is_term,data); 
    stackNode->next = *root; 
    *root = stackNode; 
    printf("%d pushed to stack\n", data); 
} 
  
int pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return INT_MIN; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    Symbol popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
int peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return INT_MIN; 
    return root->data; 
} 
  
// arr[0] = 
                    //pop stack, move tkptr ahead
                    // S 
                /*
                top->data;
                // search for top->data in grammar array.
                // find the first occurance
                // suppose the grammar array linkedlist is a double linkedlist
                // push the RHS into the stack in reverse. Note the rule number as 1;
                S: then create a node (root of the tree) : create children according to rule selected above
                so the tree now is 
                      S 
                    /   \
                program    B
                          /  \
                        var   B
                             /  \
                            va    B
                               / |  |  \ 
                               a C  D    B
                stack: var B
                B
                var B

                continue;

                /////// token stream is also a doubly linkedlist
                */

/*
22/10 plan:
within main:

//printf("isterm : %d, data: %d\n", grammar[0].is_term, grammar[1].next->data);
    ////////////////tree
    // head, grammar[3].
    //stack



    struct StackNode* root = NULL;
    push(&root, 0, S); //give treeroot too.
    
    Token *tkptr;
    tkptr = head;

    Node* treeroot = NULL; //root of the tree
    //create S
    //treeroot-> node(has S)

    while(!isEmpty(root)){
        StackNode* top = peek(root);
        if(top->is_term){
            if(!strcmp(tkptr->tokenname, "identifier") && top->data == var) {
                pop(&root);
                tkptr = tkptr ->next;
            }
            //suppose operators and separators are also keywords
            else if(!strcmp(tkptr->tokenname, "keyword") && it matches with the top of the stack ) //able to compare
            {
                pop(&root);
                tkptr = tkptr ->next;
                
            }
            else //code to handle this case

            //mistake si 
            //operator
            //separator
            //number will be handled like identifier
        }
        else if( tkptr && /* top is a nonterminal ){
            //check grammar rules LHS terms
            // if found (first occurance)
            // for each token in the RHS of the ruls : createnodeoftree()      
            // push in reverse the RHS of the rule      
            // else 
            //      do something
            //
            /*
                create neew nodes. 
                -> S 
                  /  | 
                 program B
            
        }
        else //backtracking required
    }
*/

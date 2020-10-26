#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef enum symbol {S , B, program , var  } Symbol;


typedef struct treenode {
    int ruleindex;
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

struct StackNode { 
    bool is_term;
    Symbol data;
    struct treenode* parenttreelink;
    struct StackNode* next; 
    int ruleindex;
}; 

Grammar* readGrammar(void);
Token* tokeniseSourcecode(void);
//TreeNode* createParseTree(Token* s, Grammar* G);
//TreeNode* createNode(Symbol symbol, int rule_num, );

struct StackNode* newNode(bool is_term, Symbol data, int ruleindex, struct treenode* parenttreelink);
int isEmpty(struct StackNode* root);
void push(struct StackNode** root, bool is_term, Symbol data, int ruleindex, struct treenode* parentrreelink);
int pop(struct StackNode** root);
int peek(struct StackNode* root);


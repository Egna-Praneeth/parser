#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

// NOTE: WHEN MAKING CHANGES HERE, CHECK WHETHER THIS FUNCTION EXISTS ELSE WHERE. AND MAKE CORRESPONGING CHANGES
typedef enum symbol {S , B, program , var  } Symbol;

typedef struct treenode{
    int ruleno;
    bool is_term;
    Symbol symbol;
    struct treenode *parent;
    struct treenode *nextsib;
    struct treenode *child;
}TreeNode;

typedef struct grammarNode{
    bool is_term;
    Symbol symbol;
    struct grammarNode *next;
    struct grammarNode *prev; // why do we need this?
}Grammar;

typedef struct token{
    char token[10]; //lexeme
    char tokenname[100]; //token name
    struct token *next; 
    struct token *prev;
}Token;

typedef struct StackNode{ 
    bool is_term;
    Symbol data;
    struct treenode *parent;
    struct StackNode *next; 
    int ruleno;
}Stack; 

Stack *stack;

Grammar* readGrammar(void);
Token* tokeniseSourcecode(void);
TreeNode* createParseTree(Token* s, Grammar* G);
TreeNode* createNode();
TreeNode* deleteRule(TreeNode* parent, Token** tkptr);

bool isEmpty();
void push(bool is_term, Symbol data, int ruleno, TreeNode* parent);
void pop();
Symbol peek();

int pushRule(Grammar* G, TreeNode* parent, Symbol symbol, int searchfrom);
void pushReverseGrammarRule(Grammar* head, int ruleno, TreeNode* parent);
TreeNode* makeTreeNodelist(Grammar* head, int ruleno, TreeNode* parent);
int popRule(int ruleno);

int pushNextRule(Grammar* G, TreeNode* parentlink, int ruleno);
void removeAndReplace(TreeNode* parent, Grammar* G,  int ruleno, Token* tkptr);

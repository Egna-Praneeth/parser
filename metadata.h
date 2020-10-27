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
TreeNode* createParseTree(Token* s, Grammar* G);
TreeNode* createNode(TreeNode* parent, Symbol symbol, int ruleindex);
TreeNode* deleteRule(TreeNode* parent);

struct StackNode* newNode(bool is_term, Symbol data, int ruleindex, struct treenode* parenttreelink);
int isEmpty(struct StackNode* root);
void push(struct StackNode** root, bool is_term, Symbol data, int ruleindex, struct treenode* parentrreelink);
int pop(struct StackNode** root);
int peek(struct StackNode* root);
int pushRule(struct StackNode* stack, Grammar* G, TreeNode* parentlink, Symbol symbol, int searchfrom);
int popRule(struct StackNode* stack, int ruleindex);

void removeAndReplace()
/*
todo
1. Create the char array (with indexes mapped to enum values) (name of array is enumtochar[])
2. createNode(TreeNode* parent, Symbol symbol, int ruleindex);//write in tree.c
a) crete a node in the tree
b) different way to creat for S
3. pushRule(struct StackNode* stack, Grammar* G, Symbol symbol, TreeNode* parentlink, int searchfrom)
    a) returns the index of the rule which is being pushed into stack.
    b) the rule to be pushed is : LHS is symbol and the searching in the grammar
    rule starts from index searchfrom
    c) while pushing into symbols of the rule into stack
        mention the rule index (of grammar) in stacknode. 
    d) put parentlink in the node too.
4. popRule(struct StackNode* stack, int ruleindex)
    a) search for stacknodes from top of the stack, and pop if the topnode has ruleindex 
5. TreeNode* deleteRule(TreeNode* parent); //write in tree.c
    a) Deletes the child linkedlistof this parent;
6. 
. removeAndReplace (has popRule, deleteRule, and pushnextrule)

*/
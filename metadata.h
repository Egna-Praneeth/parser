#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#define GRAMMAR_SIZE 55
// NOTE: WHEN MAKING CHANGES HERE, CHECK WHETHER THIS FUNCTION EXISTS ELSE WHERE. AND MAKE CORRESPONGING CHANGES
typedef enum symbol { andExpression,arithExpression, assignList, assignment, bool_arith, boolExpression,
bracket_pair, const_int_list, dims_jagged, decl_jagged_arr, decl_multi, decl_norm, decl_num, dims_rect,
decl_rect_arr, decl_type, declaration, declList, factor, list_of_rows, mulExpression, mulop, mutable, other_dims,
row, Start, sumop, type, var_id, var_id_list, varList, bool_and, bool_or, equal, plus, minus, multiply, divide,
par_op, par_cl, curl_op, curl_cl, sq_op, sq_cl, colon, semi_colon, array_dots, array, declare, E, integer,
boolean, real, jagged, list, number, of, program, R1, size, values, var, variables
} Symbol;

typedef enum  token_name {operator, keysep, identifier, digits} token_name;

static char* enumtochar[] = {"andExpression",
"arithExpression",
"assignList",
"assignment",
"bool_arith",
"boolExpression",
"bracket_pair",
"const_int_list",
"dims_jagged",
"decl_jagged_arr",
"decl_multi",
"decl_norm",
"decl_num",
"dims_rect",
"decl_rect_arr",
"decl_type",
"declaration",
"declList",
"factor",
"list_of_rows",
"mulExpression",
"mulop",
"mutable",
"other_dims",
"row",
"Start",
"sumop",
"type",
"var_id",
"var_id_list",
"varList",
"&&&",
"|||",
"=",
"+",
"-",
"*",
"/",
"(",
")",
"{",
"}",
"[",
"]",
":",
";",
"..",
"array",
"declare",
"E",
"integer",
"boolean",
"real",
"jagged",
"list",
"number",
"of",
"program",
"R1",
"size",
"values",
"var",
"variables"
};

typedef struct treenode{
    int ruleno;
    char* symbolname;
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

// typedef struct token{
//     char token[10]; //lexeme
//     char tokenname[100]; //token name
//     struct token *next; 
//     struct token *prev;
// }Token;

typedef struct token{
    char* token;
    token_name tokenname;
    int line_num;
    struct token *prev;
    struct token* next;
}Token;

typedef struct StackNode{ 
    bool is_term;
    Symbol data;
    struct treenode *parent;
    struct StackNode *next; 
    int ruleno;
}Stack; 

Stack *stack;

void printGrammar(Grammar** head); //print grammar structure
void  readGrammar(char* filename, Grammar* G[]);
Token* tokeniseSourcecode(char* file, Token* s);
void printTokenStream(Token* s);
TreeNode* createParseTree(Token* s, Grammar** G);
TreeNode* createNode(struct StackNode* top, char* symbolname);
TreeNode* deleteRule(TreeNode* parent, Token** tkptr);

bool isEmpty();
void push(bool is_term, Symbol data, int ruleno, TreeNode* parent);
void pop();
Stack* peek();

int pushRule(Grammar** G, TreeNode* parent, Symbol symbol, int searchfrom);
void pushReverseGrammarRule(Grammar* head, int ruleno, TreeNode* parent);
TreeNode* makeTreeNodelist(Grammar** head, int ruleno, TreeNode* parent);
void popRule(int ruleno);

int pushNextRule(Grammar** G, TreeNode* parentlink, int ruleno, Token** tkptr);
void removeAndReplace(TreeNode* parent, Grammar** G,  int ruleno, Token** tkptr);

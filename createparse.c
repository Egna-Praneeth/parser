#include "metadata.h"


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
    Grammar *G[60];
    Token *s;
    readGrammar("grammar.txt", G);
    //printGrammar(G);
    s = tokeniseSourcecode("input.txt",s);
    
    //printTokenStream(s);
    TreeNode* root = createParseTree(s, G);
    // printParseTree(root);
}

TreeNode* createParseTree(Token* s, Grammar** G){
    printf("IN createParseTree function\n");
    TreeNode* root = NULL;
    root = (TreeNode*)malloc(sizeof(TreeNode));
        root->ruleno = -1 ;
        root->is_term = 0;
        root->symbol = Start;
        root->parent = NULL;
        root->child = NULL;
        root->nextsib = NULL;
    push(0, Start, -1, root); // push S into stack
    //create root of tree with S
    Token* tkptr = s;
    Stack *top;
    while(!isEmpty()){
        printf("Stack Entrance status: %s", tkptr->token);
        //printf("inside stack\n");
        top = peek();
        pop();
        if(top->is_term == 0){
            TreeNode* linkofnode = createNode(top);
            int ruleindex = pushRule(G, linkofnode, top->data, 0);
        }
        else /*top is a terminal */{
             if(top->data == E){
                 pop();
             }
            if(tkptr->tokenname == identifier  && top->data == var) {
                 tkptr = tkptr->next;
                 //createnode for terminal
                 createNode(top);
             }//below else if commented for now as there is no number in the sample grammar
             else if(tkptr->tokenname == digits && top->data == number){
                    tkptr = tkptr->next;
                 createNode(top);
             } // only possible case left is keywords
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
        free(top);
    }
    //printf("root is: %p", root);
    return root;
}


  

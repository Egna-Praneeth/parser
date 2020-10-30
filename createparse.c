#include "metadata.h"
#include "typeExpr.h"


void printParseTree(TreeNode* root){
    
    if(root == NULL) return ;
    printf("%s\t", enumtochar[root->symbol]);
    if(root->child == NULL) return ;
    TreeNode* head = root->child;
    while(head){
        printParseTree(head);
        head = head->nextsib;
    }
    printf("\n");

}

int main(){
    Grammar *G[60];
    Token *s;
    readGrammar("grammar.txt", G);
    TypeExprNode* table;
    //printGrammar(G);
    s = tokeniseSourcecode("input.txt",s);
    // printTokenStream(s);
    TreeNode* root = createParseTree(s, G);
    printParseTree(root);
    printf("completed creation\n");

    table = traverseDeclParse(root);
    // printParseTree(root);
}

TreeNode* createParseTree(Token* s, Grammar** G){
    printf("IN createParseTree function\n");
    TreeNode* root = NULL;
    root = (TreeNode*)malloc(sizeof(TreeNode));
        root->ruleno = -1 ;
        root->is_term = 0;
        strcpy(root->symbolname, enumtochar[Start]);
        root->symbol = Start;
        root->parent = NULL;
        root->child = NULL;
        root->nextsib = NULL;
    push(0, Start, -1, root); // push S into stack
    //create root of tree with S
    Token* tkptr = s;
    Stack *top;
    int i=0;
    while(!isEmpty()){
        // printf("noob\n");
        Stack* st_temp = stack;
        i=0;
        // printf("\n");
        // while(st_temp)
        // {   i++;
        //     printf("%d %s ",i,enumtochar[st_temp->data]);
        //     st_temp = st_temp->next;
        // }
        // printf("Tokenstream status: %u", tkptr);
        
        // printf("\n");
        // printf("Tokenstream status: %s %d", tkptr->token ,tkptr->line_num );
        
        //printf("inside stack\n");
        top = peek();
        pop();
        
        
        // printf("\tStack top symbol: %s %d\n", enumtochar[top->data], top->ruleno); //E
        
        if(top->is_term == 0){
            TreeNode* linkofnode = createNode(top, enumtochar[top->data]);
            int ruleindex = pushRule(G, linkofnode, top->data, 0);
        // printf("noob1\n");
        }
        else /*top is a terminal */{
             if(top->data == E){
        // printf("noob2\n");
                TreeNode* linkofnode = createNode(top,enumtochar[E]);
                
                // int i =  pushRule(G, linkofnode, , top->ruleno + 1);
 
             }
            else if(tkptr->tokenname == identifier  && top->data == var) {
                 //createnode for terminal
                 createNode(top, tkptr->token);
                 tkptr = tkptr->next;
        // printf("noob3\n");
             }//below else if commented for now as there is no number in the sample grammar
             else if(tkptr->tokenname == digits && top->data == number){
                    tkptr = tkptr->next;
                    createNode(top, tkptr->token);
        // printf("noob3\n");
             } // only possible case left is keywords
             else if(!strcmp(tkptr->token, enumtochar[top->data])){
                tkptr = tkptr->next;
                 //createnode for terminal
                createNode(top, tkptr->token);
             }
            else if (tkptr->tokenname == operator && !strcmp(tkptr->token,enumtochar[top->data]))
            {
                tkptr = tkptr->next;
                // printf("noob4\n");
                 //createnode for terminal
                createNode(top, tkptr->token);
            }
            
             
             //below else case is when no terminal matches;
             else {
                //  printf("%d\n",top->data);
                removeAndReplace(top->parent, G, top->ruleno, &tkptr);
                //  printf("%d\n",top->data);
        // printf("noob5\n");
             }
        // printf("noob6\n");
       
        }
        // printf("noob7\n");
        free(top);
        // printf("noob8\n");
    }
    //printf("root is: %p", root);
    return root;
}


  

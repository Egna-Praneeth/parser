#include "metadata.h"
#include "typeExpr.h"

int main()
{
    Grammar *G[60];
    Token *s;
    TypeExprNode* table;
    TreeNode* root;

    
    int option = 1;
    printf("Welcome! Enter Option: ");
    while(1)
    {
        readGrammar("grammar.txt", G);
        s = tokeniseSourcecode("sourcecode.txt",s);

        scanf("%d",&option);
        if(option == 0)
        {    
            printf("\nThank You!\n");
            break;
        }
        switch (option)
        {
        case 1:
            root = createParseTree(s, G);
            printf("\nCompleted creation.\n\tEnter next Option: ");
            break;
        
        case 2:
            root = createParseTree(s, G);
            printf("bruh\n");
            table = traverseDeclParse(root);
            printf("\nCompleted traversal.\n\tEnter next Option: ");
            break;
        case 3:
            root = createParseTree(s, G);
            // printParseTree(root);
            printf("\nParse Tree printed.\n\tEnter next Option: ");
            break;

        case 4:
            root = createParseTree(s, G);
            table = traverseDeclParse(root);
            printTypeExpressionTable(table);
            printf("\nType expression table printed.\n\tEnter next Option: ");
            break;
        }
    }
}
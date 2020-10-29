#include "metadata.h"

TreeNode* addendLL(TreeNode* parent, TreeNode* newnode){
    // printf("lol1\n");
    if(parent->child == NULL) {
        parent->child = newnode;
        return newnode;
    }
    TreeNode* temp = parent->child;
    while(temp->nextsib){
        temp = temp->nextsib;
    }
    // printf("lol2\n");
    temp->nextsib = newnode;
    // printf("lol3\n");
    return newnode;
}

TreeNode* createNode(struct StackNode* node, char* symbolname){
        // printf("bruh\n");

    if(node->data == Start){
        return node->parent;
        // printf("bruh1\n");
    }
    // printf("bruh2\n");
    TreeNode* newnode = (TreeNode*) malloc(sizeof(TreeNode));
    // printf("bruh4\n");
    newnode->symbol = node->data;
    // printf("bruh5\n");
    newnode->symbolname = (char*)malloc(sizeof(symbolname));
    strcpy(newnode->symbolname, symbolname);
    // printf("bruh6\n");
    newnode->ruleno = node->ruleno;
    // printf("bruh7\n");
    newnode->is_term = node->is_term;
    // printf("bruh8\n");
    newnode->parent = node->parent;
    // printf("bruh9\n");
    newnode->child = NULL;
    // printf("bruh0\n");
    newnode->nextsib = NULL;
    // printf("bruh3\n");
    return addendLL(node->parent , newnode);
}

void removeAndReplace(TreeNode* parent, Grammar** G,  int ruleno, Token** tkptr){
    popRule(ruleno);
    deleteRule(parent, tkptr);
    pushNextRule(G, parent, ruleno, tkptr);
}

int countTerminals(TreeNode* P){
    if(P->child == NULL)return 0;
    int count = 0;
    TreeNode* temp = P->child;
    while(temp){
        if(temp->is_term == 1) count++;
        else count += countTerminals(temp);
        temp = temp->nextsib;
    }
    return count;
}
void deleteLL(TreeNode* parent){
    if(parent->child == NULL)return;
    TreeNode* temp = parent->child, *temp2;

    while(temp){
        deleteLL(temp);
        temp2 = temp;
        temp = temp->nextsib;
        free(temp2);
    }
    parent->child = NULL;
}
TreeNode* deleteRule(TreeNode* parent, Token** tkptr){
    int num = countTerminals(parent);
    //go back in tkptr
        while(num){
        *tkptr = (*tkptr)->prev;
        num--;
        }


    deleteLL(parent);
}
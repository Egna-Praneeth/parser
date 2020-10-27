#include "metadata.h"

TreeNode* createNode(TreeNode* parent, Symbol symbol, int ruleindex){
    if( symbol == S) {
        parent = (TreeNode* ) malloc(sizeof(TreeNode));
        parent->
    }
}
void removeAndReplace(struct StackNode* stack, TreeNode* parent, Grammar* G,  int ruleindex, Token* tkptr){
    popRule(stack, ruleindex);
    deleteRule(parent, &tkptr);
    pushNextRule(stack, G, parent, ruleindex);
}
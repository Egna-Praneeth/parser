#include "metadata.h"

StackNode* popRule(struct StackNode* stack, int ruleindex){
	while(stack->ruleindex == ruleindex){
####		stack = pop(stack);
	}
	return stack;
}

int pushRule(struct StackNode* stack, Grammar* G, TreeNode* parentlink, Symbol symbol, int searchfrom){

	for(int i = searchfrom; i<GRAMMAR_SIZE; i++){
		if(G[i].symbol == symbol){
			parentlink->child = makeTreeNodelist(G[i],i,parentlink);
####			newhead = pushReverseGrammarRule(G[i]->next,i,parentlink,stack);
			return i;
		}
	}
	return -1;
}

StackNode* pushReverseGrammarRule(Grammar* head, int ruleno, TreeNode* parent, StackNode* top){
	if(head->next!=NULL){
		top = pushReverseGrammarRule(head->next,ruleno,parent,top);
	}

	//this section will be first executed by the last node in the Grammar rule and it will 
	//return the new top of the stack after pushing equivalent stackNode
	StackNode* this;
	this = (StackNode*)malloc(sizeof(Grammar));
	this->data = head->symbol;
####	this->is_term = 
	this->parenttree = parent;
	this->next = top;
	this->ruleindex = ruleno;
	top = this;
	return top; 
}

TreeNode* makeTreeNodelist(Grammar* head, int ruleno, TreeNode* parent){
	TreeNode* children,temp,prev_sib;
	bool first=true;
	while(head!=NULL){
		temp = (TreeNode*)malloc(sizeof(TreeNode));
		if(first){
			children = temp;
			first = false;
		}
		temp->ruleindex = ruleno;
		temp->symbol = head->symbol;
		temp->parent = parent;
		temp->nextsib = NULL;
		temp->child = NULL;
		prev_sib->nextsib = temp;
		prev_sib = temp;
		head= head->next;
	}
	return children;
}
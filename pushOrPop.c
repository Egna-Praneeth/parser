/*
Group no.: 11
Group member names and IDs:
Aditya V. Bodade
2018A7PS0256P

Egna Praneeth Gummana
2018A7PS0284P

Yogya Modi
2018A7PS0235P

Kartikaya Sharma
2018A7PS0386P

*/
#include "metadata.h"

void popRule(int ruleno){
	while(stack && stack->ruleno == ruleno)
		pop();
}

int pushRule(Grammar** G, TreeNode* parent, Symbol symbol, int searchfrom){

	for(int i = searchfrom; i < GRAMMAR_SIZE; i++)
		if(G[i] -> symbol == symbol){
			// parent->child = makeTreeNodelist(G[i], i, parent);
			pushReverseGrammarRule(G[i] -> next, i, parent);
		        Stack* st_temp = stack;
			// printf("rule = %d\n",i);
			// 	while(st_temp)
			// {   
			// 	// i++;
			// 	printf("%s ",enumtochar[st_temp->data]);
			// 	st_temp = st_temp->next;
			// }
			// printf("\n");
			return i;
		}
	return -1;
}

void pushReverseGrammarRule(Grammar* head, int ruleno, TreeNode* parent){
	if(head->next!=NULL)
		pushReverseGrammarRule(head -> next, ruleno, parent);
	push(head -> is_term, head -> symbol, ruleno, parent);
	return;
}

// TreeNode* makeTreeNodelist(Grammar* head, int ruleno, TreeNode* parent){
// 	TreeNode* children, temp, prev_sib;
// 	bool first = true;
// 	while(head != NULL){
// 		temp = (TreeNode*)malloc(sizeof(TreeNode));
// 		if(first){
// 			children = temp;
// 			first = false;
// 		}
// 		temp -> ruleno = ruleno;
// 		temp -> symbol = head -> symbol;
// 		temp -> parent = parent;
// 		temp -> nextsib = NULL;
// 		temp -> child = NULL;
// 		prev_sib -> nextsib = temp;
// 		prev_sib = temp;
// 		head = head -> next;
// 	}
// 	return children;
// }
## BITS CS F301 Principles of Programming Languages <br> Assignment 1: Language design and type expression computation
grammar, tokenstream, parsetree, type checking
todo
1. Create the char array (with indexes mapped to enum values) (name of array is enumtochar[])
----------Kartikaya will be making this
2. createNode(TreeNode* parent, Symbol symbol, int ruleindex);//write in tree.c
a) crete a node in the tree
b) different way to creat for S

3. (DONE) pushRule(struct StackNode* stack, Grammar* G, Symbol symbol, TreeNode* parentlink, int searchfrom)
    a) returns the index of the rule which is being pushed into stack.
    b) the rule to be pushed is : LHS is symbol and the searching in the grammar
    rule starts from index searchfrom
    c) while pushing into symbols of the rule into stack
        mention the rule index (of grammar) in stacknode. 
    d) put parentlink in the node too.
4. (DONE) popRule(struct StackNode* stack, int ruleindex)
    a) search for stacknodes from top of the stack, and pop if the topnode has ruleindex 
5. TreeNode* deleteRule(TreeNode* parent); //write in tree.c
    a) count number of terminals in the subtree rooted at parent
    b) Deletes the child linkedlistof this parent;
    c) go back in the tokenstream by these many
6. int pushNextRule(struct StackNode* stack, Grammar* G, TreeNode* parentlink, int ruleindex)
    a)based on parentlink, find the non-terminal and find next rule and push it into the stack
    b) if no rule exists then get the parent of this node using parentlink and do the same for its parent

7. removeAndReplace (has popRule, deleteRule, and pushnextrule)

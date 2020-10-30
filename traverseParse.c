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
#include <stdio.h>
#include "metadata.h"
#include "typeExpr.h"
#include "string.h"
/*
for declaration in program
	//computing typeexpr
		determine whether primitive or not
		if primitive
			enum type
		else
			rect or jagged
			enum type
			dimensions
			ranges
	//populating table
		for var in varlist
			insert into table name and typeexpr
*/
TreeNode* ptrNext(TreeNode* ptr ,int count){
	while(count--){
		ptr = ptr->nextsib;

	}
	return ptr;
}

TypeExprNode* generateCopy(TypeExprNode* original){
	TypeExprNode *duplicate = (TypeExprNode*)malloc(sizeof(TypeExprNode));
	duplicate -> tag1 = original -> tag1;
	duplicate -> tag2 = original -> tag2;
	duplicate -> TE = original -> TE;
	duplicate -> next = NULL;
	return duplicate;
}

TypeExprNode* traverseDeclParse(TreeNode* top){

	TreeNode* temp = top;
	temp = ptrNext(temp->child,4); //to get to declaration
	TypeExprNode* temp_table,*table,*prev_tableNode;
 	bool initialised = false;
	while(temp -> symbol == declaration){
		table = (TypeExprNode*)malloc(sizeof(TypeExprNode));
		if(!initialised){
			temp_table = table;
			initialised = true;
		}
		else{
			prev_tableNode -> next = table;
		}
		temp = ptrNext(temp -> child,3)->child;
		switch(temp -> symbol){
			case decl_norm: 
				table -> tag1 = primitive;
				table -> tag2 = NA;
				table -> TE.primitive = temp -> child -> child -> symbol - integer; // to get to rule index 27
			break;
			case decl_rect_arr:
				table -> tag1 = rect_array;
				table -> tag2 = Static;
				table -> TE.arr.t = Integer;

				//finding the dimensions
				table -> TE.arr.dimensions = 0;
				TreeNode* double_dot_finder = temp;
				double_dot_finder = ptrNext(temp -> child,3); 
				while(double_dot_finder -> symbol != E){
					if(double_dot_finder -> symbol == array_dots){
						table -> TE.arr.dimensions++;
						double_dot_finder = ptrNext(double_dot_finder, 3) -> child;
					}
					double_dot_finder = double_dot_finder -> nextsib;
				}

				//finding the range
				RangeRect* curr_RangeRect, *prev_RangeRect;
				TreeNode* var_id_finder = temp -> child -> nextsib;
				 // to get to first '['
				initialised = false;
				for (int i = 0; i < table -> TE.arr.dimensions; ++i){
					curr_RangeRect = (RangeRect*)malloc(sizeof(RangeRect));
					if(!initialised){
						table -> TE.arr.rng.rect = curr_RangeRect;
						initialised = true;
					}
					else{
						prev_RangeRect -> next = curr_RangeRect;					
					}
				
					if(var_id_finder -> nextsib -> child -> symbol == number){
						curr_RangeRect -> lower.limit = atoi(var_id_finder -> nextsib -> child -> symbolname);
					}
					else{
						curr_RangeRect -> lower.var = var_id_finder -> nextsib -> child -> symbolname;
						table -> tag2 = Dynamic;
					}
					if(ptrNext(var_id_finder,3)-> child -> symbol == number){
						curr_RangeRect -> upper.limit = atoi(ptrNext(var_id_finder,3) -> child -> symbolname);
					}
					else{
						curr_RangeRect -> upper.var = ptrNext(var_id_finder,3) -> child -> symbolname;
						table -> tag2 = Dynamic;
					}
					prev_RangeRect = curr_RangeRect;
					curr_RangeRect -> next = NULL;
					curr_RangeRect = curr_RangeRect -> next;
					var_id_finder = ptrNext(var_id_finder,5) -> child;
				}
			break;
			case decl_jagged_arr:
				table -> tag1 = jagged_array;
				table -> tag2 = NA;
				table -> TE.arr.t = Integer;
				TreeNode* temp1;
				temp1 = ptrNext(temp -> child,2) -> child; // to get to dims_jagged's child

				//extracting range of R1 from dims_jagged
				int r1_low,r1_high;
				table -> TE.arr.rng.jagged[0] = (RangeJagged*)malloc(sizeof(RangeJagged));
				RangeJagged *curr_range = table -> TE.arr.rng.jagged[0];
				r1_low = curr_range -> data = atoi(temp1 -> nextsib -> symbolname);
				curr_range -> next = (RangeJagged*)malloc(sizeof(RangeJagged));
				curr_range -> head = NULL;
				r1_high = curr_range -> next -> data = atoi(ptrNext(temp1,3) -> symbolname);
				curr_range -> next -> next = NULL;
				curr_range -> next -> head = NULL;

				//extracting dimensions from bracket_pair
				TreeNode* r_finder;
				RangeJagged *prev_RangeJagged;
				temp1 = ptrNext(temp1,7); // to get to bracket_pair
				table -> TE.arr.dimensions = (temp1 -> child -> symbol== sq_op)? 3 : 2;
				
				r_finder = ptrNext(temp -> child, 6); // to get to first occurence of list of rows
				initialised = false;
				for (int i = 0; i <= r1_high - r1_low; ++i){ // since there are r1_high -r1_low + 1 rows
					curr_range = (RangeJagged*)malloc(sizeof(RangeJagged));
					if(!initialised){
						table -> TE.arr.rng.jagged[1] = curr_range;
						initialised = true;
					}
					else{
						curr_range -> next = prev_RangeJagged; 
					}
					TreeNode* saved_finder = r_finder -> child -> nextsib; // saving pointer to nextsib list_of_rows;
					r_finder = r_finder -> child -> child; // get to R1 of the row
					r_finder = ptrNext(r_finder,6); // get to 'number' in row
					curr_range -> data = atoi(r_finder -> symbolname);

					if(table -> TE.arr.dimensions == 3){
						r_finder = ptrNext(r_finder,4); //get to const_int_list
						TreeNode *temp_finder = r_finder;
						RangeJagged3D * curr_range_3D,*prev_3D;
						initialised = false;
						for(int j = 0; j < curr_range -> data; j++){
							int count = 0;
							while(temp_finder->child->symbol == number){ 
								count++;	//count the no. of 'number's occuring 
								temp_finder = ptrNext(temp_finder->child,1);	// get to nextsib 'number'
							}
							temp_finder = r_finder -> nextsib -> child ->nextsib; // get to the nextsib const_int list
							curr_range_3D = (RangeJagged3D*)malloc(sizeof(RangeJagged3D));
							if(!initialised){
								curr_range -> head = curr_range_3D;
								initialised = true;
							}
							else{
								prev_3D -> next = curr_range_3D;
							}
							curr_range_3D -> data = count;
							curr_range_3D -> next = NULL;
							prev_3D = curr_range_3D;
							curr_range_3D = curr_range_3D -> next;
						}
					}
					else{
						curr_range -> head = NULL;
					}
					prev_RangeJagged = curr_range;
					curr_range = curr_range -> next;
					r_finder = saved_finder;
				}
			break;
		}

	

		temp = temp -> parent -> parent; // to get back to declaration
		TreeNode* left_temp = temp -> child -> nextsib; // get to decl_num
		if(left_temp -> child -> symbol == decl_multi){
			left_temp = ptrNext(left_temp -> child -> child, 3); // to get to the first var 
			table -> name = left_temp -> symbolname;
			left_temp = left_temp -> nextsib; //get to varList
			while(left_temp -> child -> symbol != E){
				TypeExprNode* copy = generateCopy(table);
				copy -> name = left_temp -> child -> symbolname;
				table -> next = copy;
				table = copy;
				left_temp = left_temp -> child -> nextsib;
			}
		}	
		else{
			table -> name = left_temp -> child -> symbolname;
		}
		prev_tableNode = table;
		table -> next = NULL;
		table = table-> next;

		temp = temp -> nextsib -> child; // get to declList

	}



	return temp_table;
}

TypeExprNode lookup(TreeNode* identifier, TypeExprNode* table){

// handle numbers lookup;

	while(table){
		if(strcmp(identifier -> symbolname, table -> name) == 0){
			return *table;
		}
		table = table -> next;
	}
	return NULL;
}

int findRealChildren(TreeNode* root){
	if(root -> child == NULL)
		return 0;
	int count =0;
	TreeNode* tc= root->child;
	while (tc){
		if(tc->is_term == false)
			count++;
		tc= tc->nextsib;
	}
	return count;
}

TypeExprNode* morethanone(TreeNode* X, TypeExprNode* table){
	TreeNode* tc = X->child;
	TypeExprNode* typet;

	while(tc){
		tc =tc->nextsib;
		

	}
}


TypeExprNode checkType(TreeNode* X, TypeExprNode* lhs, TypeExprNode* table){
	int real_children = findRealChildren(X);
	if(real_children == 0)
		return lookup(X,table);
	if(real_children == 1)
		return checkType(X -> child, lhs, table);
	if(real_children > 1){
		return morethanone(X,table);
	}
}

void traverseAssignParse(TreeNode* top, TypeExprNode *table){
	TreeNode* temp;
	temp = ptrNext(top->child, 6); // get to first assignment
	
	while(temp -> symbol == assignment){
		TreeNode* temp2 = temp;
		TypeExprNode *rhs,*lhs;
		lhs = lookup(temp2->child, table);

		if(lhs == NULL){
			// error identifier not declared
		}
		temp2 = temp2 -> child;
		while(temp2->nextsib){
			temp2 = ptrNext(temp2,1);
		}//get to bool_arith
		rhs=checkType(temp2,lhs);
		
	}
}
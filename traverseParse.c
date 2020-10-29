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

TypeExprNode* traverseParse(TreeNode* top, TypeExprNode* table){

	TreeNode* temp = top;
	temp = temp -> child;
	temp = temp -> next -> next -> next -> next;
	TypeExprNode* temp_table;
 	bool initialised = false;
	while(temp -> symbol == declaration){

		table = (TypeExprNode*)malloc(sizeof(TypeExprNode));
		if(!initialised){
			temp_table = table;
			initialised = true;
		}
		temp = temp -> child;
		temp = temp -> next -> next -> next;
		temp = temp -> child;
		switch(temp -> symbol){
			case decl_norm: 
				table -> tag1 = primitive;
				table -> tag2 = NA;
				table -> TE.primitive = temp -> child -> child ->symbol - 50;
				break;
			case decl_rect_arr:
				table -> tag1 = rect_array;
				table -> tag2 = Static;
				table -> TE.arr.t = Integer;
				TreeNode* temp1 = temp;
				while(temp1 -> symbol != E){
					if(temp1 -> symbol == array_dots){
						table -> TE.arr.dimensions++;
						temp1 = temp1 -> next -> next -> next -> child;
					}
					temp1 = temp1 -> next;
				}
				table -> TE.arr.rng.rect = (RangeRect*)malloc(sizeof(RangeRect));
				RangeRect* temp2,prev;
				initialised = false;
				for (int i = 0; i < table -> TE.arr.dimensions; ++i){
					temp2 = (RangeRect*)malloc(sizeof(RangeRect));
					if(!initialised){
						table -> TE.arr.rng.rect = temp2;
						initialised = true;
					}
					else{
						prev-> next = temp2;					
					}
					while(temp1 != sq_op)
						temp1 = temp1 -> next;
					if(temp1->next->child->symbol == number){
						temp2->lower = temp1->next->child->DIGITS;
					}
					else{
						temp2->lower = temp1->next->child->VARIABLE;
						table -> tag2 = Dynamic;
					}
					if(temp1->next->next->next->child->symbol == number){
						temp2->upper = temp1->next->next->next->child->DIGITS;
					}
					else{
						temp2->upper = temp1->next->next->next->child->VARIABLE;
						table -> tag2 = Dynamic;
					}
					prev = temp2;
					temp1 = temp1->next->next->next->next->next->child;
				}
				break;
			case decl_jagged_arr:
				table -> tag1 = jagged_array;
				table -> tag2 = NA;
				table -> TE.arr.t = Integer;
				TreeNode* temp1;
				temp1 = temp -> child -> next -> next -> child;

				//range of dimension 1
				int r1_low,r1_high;
				table -> TE.arr.rng.jagged[0] = (RangeJagged*)malloc(sizeof(RangeJagged));
				RangeJagged *t_range = table -> TE.arr.rng.jagged[0];
				int r1_low = t_range -> data = temp1 -> next -> DIGITS;
				t_range -> next = (RangeJagged*)malloc(sizeof(RangeJagged));
				t_range -> head = NULL;
				int r1_high = t_range -> next -> data = temp1 -> next -> next -> next -> DIGITS;
				t_range -> next -> next = NULL;
				t_range -> next -> head = NULL;

				//range of dimension 2 and/or 3
				TreeNode* r_finder;
				RangeJagged *prev;
				temp1 = temp1 -> next -> next -> next -> next -> next -> next -> next;
				table -> TE.arr.dimensions = (temp1 -> child -> symbol== sq_op)? 3 : 2;
				if(temp1 -> child == sq_op){
					r_finder = temp -> child -> next -> next -> next -> next -> next -> next;
					
					initialised = false;
					for (int i = 0; i <= r1_high - r1_low; ++i){
						t_range = (RangeJagged*)malloc(sizeof(RangeJagged));
						if(!initialised){
							table -> TE.arr.rng.jagged[1] = t_range;
							initialised = true;
						}
						else{
							t_range -> next = prev; 
						}
						TreeNode* saved_finder = r_finder -> child -> next;
						r_finder = r_finder -> child -> child;
						r_finder = ptrNext(r_finder,6);
						t_range -> data = r_finder -> DIGITS;
						if(table -> TE.arr.dimensions == 3){
							r_finder = ptrNext(r_finder,4);
							for(int j = 0; j < t_range -> data; j++){
								int count = 0;
								while(r_finder->child->symbol != number){
									count++;
									r_finder = ptrNext(r_finder,1);
								}
							}
						}
						else{
							t_range -> head = NULL;
						}
						prev = t_range;
						t_range = t_range -> next;
						r_finder = saved_finder;
					}
				}
				break;
		}
	}
}



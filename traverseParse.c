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
						temp2->lower = DIGITS;
					}
					else{
						temp2->lower = VARIABLE;
						table -> tag2 = Dynamic;
					}
					if(temp1->next->next->next->child->symbol == number){
						temp2->upper = DIGITS;
					}
					else{
						temp2->upper = VARIABLE;
						table -> tag2 = Dynamic;
					}
					prev = temp2;
					temp1 = temp1->next->next->next->next->next->child;
				}
				break;
			case decl_jagged_arr:
				
		}
	}
}



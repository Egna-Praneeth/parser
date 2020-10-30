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

enum type{
	Integer,
	Bool,
	Real,
	Mismatch
};

typedef union bound{
	int limit;
	char* var;
}Bound;

typedef struct range_rect{
		Bound lower,upper;
		struct range_rect *next;
}RangeRect;

typedef struct range_jagged{
		int data;
		struct range_jagged *next;
		struct range_jagged3D *head;

}RangeJagged;

typedef union range_type{
	RangeRect* rect;
	RangeJagged* jagged[2];
}RangeType;

typedef struct array{
	enum type t;
	int dimensions;
 	RangeType rng;
}Array;

typedef struct range_jagged3D{
	int data;
	struct range_jagged3D *next;
}RangeJagged3D;

typedef union typeExpression{
	Array arr;
	enum type primitive;
}TypeExpression;

enum prim_or_arr{
	primitive,
	rect_array,
	jagged_array
};
static char* prim_or_arr_str[] = { 
	"primitive",
	"rect_array",
	"jagged_array"
};
static char* stat_or_dyn_str[] = { 
	"Static",
	"Dynamic",
	"NA"
};

enum stat_or_dyn{
	Static,
	Dynamic,
	NA
};

typedef struct typeExprNode{
	char* name;
	enum prim_or_arr tag1;
	enum stat_or_dyn tag2;
	TypeExpression TE;
	struct typeExprNode *next;
}TypeExprNode;
TypeExprNode* traverseDeclParse(TreeNode* top);

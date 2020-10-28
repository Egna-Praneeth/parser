typedef union bound{
	int limit;
	char* var;
}Bound;

typedef struct range_rect{
		Bound lower,upper;
		struct range *next;
}RangeRect;

typedef struct array{
	enum type t;
	int dimensions;
 	RangeType rng;

}Array;

typedef union range_type{
	RangeRect* rect;
	RangeJagged* jagged[2];
}RangeType;

typedef struct range_jagged3D{
	int data;
	struct range_jagged3D *next;
}RangeJagged3D;

typedef struct range_jagged{
		int data;
		struct range_jagged *next;
		struct range_jagged3D *head;

}RangeJagged;


enum type{
	Integer,
	Bool,
	Real
};

typedef union typeExpression{
	Array arr;
	enum type primitive;
}TypeExpression;

enum prim_or_arr{
	primitive,
	rect_array,
	jagged_array
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
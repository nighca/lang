#ifndef _LEXICAL_TREE_H
#define _LEXICAL_TREE_H

typedef enum {
	LT_NODE_CALC,
	LT_NODE_ARGS,
	LT_NODE_EXPRESSION,
	LT_NODE_TOKEN,
	LT_NODE_IDENTIFIER_NAME,
	LT_NODE_IDENTIFIER_START,
	LT_NODE_IDENTIFIER_PART,
	LT_NODE_RESERVED_WORD,
	LT_NODE_KEYWORD,
	LT_NODE_LITERAL,
	LT_NODE_NUMERICA_LITERAL,
	LT_NODE_DECIMAL_LITERAL,
	LT_NODE_DECIMAL_DIGITS,
	LT_NODE_DECIMAL_DIGIT
} LT_Node_Type;

typedef struct {
	enum {
		CALC_FROM_ARGS
	} from;
} LT_Node_Data_Calc;
	
typedef struct {
	enum {
		ARGS_FROM_EXPR,
		ARGS_FROM_ARGS_EXPR
	} from;
} LT_Node_Data_Args;

typedef struct {
	enum {
		EXPR_FROM_TOKEN,
		EXPR_FROM_BRACK_EXPR,
		EXPR_FROM_BRACK_CALC
	} from;
} LT_Node_Data_Expression;

typedef struct {
	enum {
		TOKEN_FROM_IDFN,
		TOKEN_FROM_LITER
	} from;
} LT_Node_Data_Token;

typedef struct {
	enum {
		IDFN_FROM_IDFST,
		IDFN_FROM_IDFN_IDFP
	} from;
} LT_Node_Data_Identifier_Name;

typedef struct {
	enum {
		IDFST_FROM_ABC,
		IDFST_FROM_PUNC
	} from;
} LT_Node_Data_Identifier_Start;

typedef struct {
	enum {
		IDFP_FROM_IDFST,
		IDFP_FROM_DECDGTS
	} from;
} LT_Node_Data_Identifier_Part;

typedef struct {
	enum {
		RSVWD_FROM_KEYWD
	} from;
} LT_Node_Data_Reserved_Word;

typedef struct {
	char* val;
} LT_Node_Data_Keyword;

typedef struct {
	enum {
		LITER_FROM_NMLITER
	} from;
} LT_Node_Data_Literal;

typedef struct {
	enum {
		NMLITER_FROM_PLUS_NMLITER,
		NMLITER_FROM_MINUS_NMLITER,
		NMLITER_FROM_DECLITER
	} from;
} LT_Node_Data_Numerica_Literal;

typedef struct {
	enum {
		DECLITER_FROM_DECDGTS,
		DECLITER_FROM_DECDGTS_PNT_DECDGTS,
		DECLITER_FROM_PNT_DECDGTS
	} from;
} LT_Node_Data_Decimal_Literal;

typedef struct {
	enum {
		DECDGTS_FROM_DECDGT,
		DECDGTS_FROM_DECDGTS_DECDGT
	} from;
} LT_Node_Data_Decimal_Digits;

typedef struct {
	int val;
} LT_Node_Data_Decimal_Digit;

typedef struct {
	char val;
} LT_Node_Data_Decimal_Abc;

typedef struct {
	enum {
		PUNC_$,
		PUNC__
	} val;
} LT_Node_Data_Decimal_Punc;

typedef struct _LT_Node{
	_LT_Node* child;
	_LT_Node* next;

	LT_Node_Type type;
	
	union {
		LT_Node_Data_Calc calc;
		LT_Node_Data_Args args;
		LT_Node_Data_Expression expression;
		LT_Node_Data_Token token;
		LT_Node_Data_Identifier_Name identifierName;
		LT_Node_Data_Identifier_Start identifierStart;
		LT_Node_Data_Identifier_Part identifierPart;
		LT_Node_Data_Reserved_Word reservedWord;
		LT_Node_Data_Keyword keyword;
		LT_Node_Data_Literal literal;
		LT_Node_Data_Numerica_Literal numericaLiteral;
		LT_Node_Data_Decimal_Literal decimalLiteral;
		LT_Node_Data_Decimal_Digits decimalDigits;
		LT_Node_Data_Decimal_Digit decimalDigit;
	};
} LT_Node;

typedef struct _LT_Tree{
	LT_Node* root;
} LT_Tree;

#endif

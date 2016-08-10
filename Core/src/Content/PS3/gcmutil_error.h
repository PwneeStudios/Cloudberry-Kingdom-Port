#ifndef __CELL_GCMUTIL_ERROR_H__
#define __CELL_GCMUTIL_ERROR_H__

// Debug Mode
#if defined(_DEBUG) || defined(DEBUG)

/* 
	For disable assert()
	When CELL_GCMUTIL_ASSERT_INVALID is defined. CELL_GCMUTIL_INTERNAL_ASSERT is disabled.
*/
#ifdef CELL_GCMUTIL_ASSERT_INVALID
#define CELL_GCMUTIL_INTERNAL_ASSERT(cond)
#else
#define CELL_GCMUTIL_INTERNAL_ASSERT(cond) assert(cond)
#endif

/*
	CELL_GCMUTIL_CHECK

	Description:
		Debug Printf. It print out filename, Line number and function name.
		The print out is designed for ProDG VSI.
		Text cursor is brought to target code by Clicking TTY output.

	Argument:
		It takes same argument of printf().

	In Release:
		This code is removed.
*/
#define CELL_GCMUTIL_DPRINTF(...) \
	do{ \
		printf("%s(%d): in %s() ",__FILE__,__LINE__,__func__);\
		printf(__VA_ARGS__); \
	}while(false)

/*
	CELL_GCMUTIL_CHECK

	Description:
		Check CELL_OK, if not, print message. This macro doesn't call assert. 

	Argument:
		statement		The statement, which has return value CELL_OK in success, should be specified.

	In Release:
		The statement remain in the code.
*/
#define CELL_GCMUTIL_CHECK(statement) \
	do{ int32_t hr = (statement); \
		if(hr != CELL_OK){ \
			CELL_GCMUTIL_DPRINTF(":Not CELL_OK exception @ \"%s\", %08x\n",#statement,hr);\
		}\
	}while(false)

/*
	CELL_GCMUTIL_CHECK_ASSERT

	Description:
		Check CELL_OK, if not, print message and stop with assert. 

	Argument:
		statement		The statement, which has return value CELL_OK in success, should be specified.

	In Release:
		The statement remain in the code.
*/
#define CELL_GCMUTIL_CHECK_ASSERT(statement) \
	do{ int32_t hr = (statement); \
		if(hr != CELL_OK){ \
			CELL_GCMUTIL_DPRINTF(":Not CELL_OK exception @ \"%s\", %08x\n",#statement,hr);\
			CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		}\
	}while(false)

/*
	CELL_GCMUTIL_CHECK_EXP

	Description:
		Check statement returns expected value, if not, print message. This macro doesn't call assert. 

	Argument:
		statement		The statement.
		value			Expected value,

	In Release:
		The statement remain in the code.
*/
#define CELL_GCMUTIL_CHECK_EXP(statement,value) \
	do{ int32_t hr = (int32_t)(statement); \
		if(hr != (value)){ \
			CELL_GCMUTIL_DPRINTF(":Not expected value exception@ \"%s\", %08x\n",#statement,hr);\
		}\
	}while(false)

/*
	CELL_GCMUTIL_CHECK_EXP_ASSERT

	Description:
		Check statement returns expected value, if not, print message and stop with assert. 

	Argument:
		statement		The statement.
		value			Expected value

	In Release:
		The statement remain in the code.
*/
#define CELL_GCMUTIL_CHECK_EXP_ASSERT(statement,value) \
	do{ int32_t hr = (int32_t)(statement); \
		if(hr != (value)){ \
			CELL_GCMUTIL_DPRINTF(":Not expected value exception @ \"%s\", %08x\n",#statement,hr);\
			CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		}\
	}while(false)


/*
	CELL_GCMUTIL_ASSERTS

	Description:
		Check condtion, if not print message with strig and stop with assert. 

	Argument:
		condition		"condition" should be conditional code.
		string			"string"	should be information about the assert.

	In Release:
		This code is removed.
*/
#define CELL_GCMUTIL_ASSERTS(condition,string) \
	do{ if((condition) == false){\
		CELL_GCMUTIL_DPRINTF(":Assert %s @ condition \"%s\"\n",(string),#condition);\
		CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		} \
	}while(false)

/*
	CELL_GCMUTIL_ASSERT

	Description:
		Check condtion, if not print message and stop with assert. 

	Argument:
		condition		"condition" should be conditional code.

	In Release:
		This code is removed.
*/
#define CELL_GCMUTIL_ASSERT(condition) \
	do{ if((condition) == false){\
		CELL_GCMUTIL_DPRINTF(":Assert @ condition \"%s\"\n",#condition);\
		CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		} \
	}while(false)

/*
	CELL_GCMUTIL_ASSERT

	Description:
		Check cgParameter. It has two test.
		Test1: Is parameter NULL or not.
		Test2: Is parameter used in NV Binary.

	Argument:
		cgParameter		cgParameter should be CGparameter. (Ex: cellGcmCgGetNamedParameter(), ...)

	In Release:
		This code is removed.
*/
#define CELL_GCMUTIL_CG_PARAMETER_CHECK_ASSERT(cgParameter) \
	do{ \
		if(cgParameter == 0){ \
			CELL_GCMUTIL_DPRINTF("CGparameter \"%s\" isn't included NV Binary\n",#cgParameter);\
			CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		}\
		if(((CgBinaryParameter*)(cgParameter))->isReferenced != CG_TRUE){ \
			CELL_GCMUTIL_DPRINTF("CGparameter \"%s\" isn't used in ucode\n",#cgParameter);\
			CELL_GCMUTIL_INTERNAL_ASSERT(false);\
		}\
	}while(false)


// Release mode
#else
#define CELL_GCMUTIL_DPRINTF(...)

#define CELL_GCMUTIL_CHECK(statement) (statement)
#define CELL_GCMUTIL_CHECK_ASSERT(statement) (statement)

#define CELL_GCMUTIL_CHECK_EXP(statement,value) (statement)
#define CELL_GCMUTIL_CHECK_EXP_ASSERT(statement,value) (statement)

#define CELL_GCMUTIL_ASSERTS(condition,string)
#define CELL_GCMUTIL_ASSERT(condition)

#define CELL_GCMUTIL_CG_PARAMETER_CHECK_ASSERT(cgParameter) 
#define CELL_GCMUTIL_ASSERT_REMAIN(condition) if(condition)

#endif // _DEBUG

#endif // __CELL_GCMUTIL_ERROR_H__

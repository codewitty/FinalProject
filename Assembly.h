#pragma once
#include <iostream>
#include <string>
using namespace std;

enum assemblyAttribute {
	NONE,
	NAME,
	TYPE,
	NUM_CONTIGS,
	SIZE,
	N50,
	GC,
	UNKNOWN
};

class Assembly {
protected:
	string            name;
	string            type;
	int               num_contigs;
	int               size;
	int               n50;
	double            gc;
	double            unknown;
	void             *pkey;
	assemblyAttribute keyType;

public:
	// sparse constructor
	Assembly();
	// complete constructor
	Assembly(string name, string type,
			 int coontigs, int size, int n50,
			 double gc, double unknown,
		     assemblyAttribute opKeyType);

	virtual ~Assembly() {};

	void setOrdering(assemblyAttribute anOrder);

	//**********************************************************************//
	// Person operator >                                                    //
	// pre:  Person objects we want to compare.                             //
	// return: result of comparing the operands (>)                         //
	//**********************************************************************//
	virtual bool operator > (const Assembly &);		// Overloaded >

	// istream and ostream overloading as friends
	friend std::ostream& operator << (std::ostream &out, Assembly &right);


	//**********************************************************************//
	// Person operator ==                                                   //
	// pre:  Person objects we want to compare.                             //
	// return: result of comparing the operands (==)                        //
	//**********************************************************************//
	bool operator == (const Assembly &);		// Overloaded >

	//**********************************************************************//
	// Person operator =                                                    //
	// pre:  source and target Person opjects we want to perform a copy     //
	//       operation on.                                                  //
	// return: result of assign one operand the result of an RHS expression.//
	//**********************************************************************//
	virtual Assembly& operator=(const Assembly &);  // overloaded =

	friend std::ostream& operator << (std::ostream &out, Assembly &right);
	// friend std::istream& operator>>(std::istream& in, Assembly& right);
};

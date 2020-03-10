#pragma once
#include <iostream>
#include <string>
using namespace std;

enum assemblyAttribute {
	NONE,
	NAME,
	NUM_CONTIGS,
	N50
};

class Assembly {
protected:
	string name;
	string type;
	int num_contigs;
	int size;
	int n50;
	float gc;
	float unknown;
	void *pkey;

public:
	Assembly();
	Assembly(int whole, int frac);
	virtual ~Assembly() {};

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

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
			 int contigs, int size, int n50,
			 double gc, double unknown,
		     assemblyAttribute opKeyType);

	virtual ~Assembly() {};

	// record primary key is set with this
	//  (mutator)
	void setOrdering(assemblyAttribute anOrder);

	// accessors
	string getName() const;
	string getType() const;
	int    getNumContigs() const;
	int    getSize() const;
	int    getN50() const;
	double getGc() const;
	double getUnknown();
	void * getPkey() const;
	assemblyAttribute getKeyType() const;

	// Mutators
	void setName(string aGNomeAssemblyName);
	void setType(string aGNomeAssemblyType);
	void setNumContigs(int numContigs);
	void setSize(int aGNomeAssemblySize);
	void setN50(int aGNomeAssemblyN50);
	void setGc(float aGNomeAssemblyGc);
	void setUnknown(float aGNomeAssemblyUnknown);

	//**********************************************************************//
	// Person operator <                                                    //
	// pre:  Person objects we want to compare.                             //
	// return: result of comparing the operands (>)                         //
	//**********************************************************************//
	virtual bool operator < (const Assembly &);		// Overloaded >

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
	bool operator == (const Assembly &) const;		// Overloaded ==

	//**********************************************************************//
	// Person operator =                                                    //
	// pre:  source and target Person opjects we want to perform a copy     //
	//       operation on.                                                  //
	// return: result of assign one operand the result of an RHS expression.//
	//**********************************************************************//
	virtual Assembly& operator=(const Assembly &);  // overloaded =
};

#pragma once
#include <iostream>
#include <string>

using namespace std;

// forward declarations
class Person;

// Enumerator class for tracking field pkey will use for
// comparison operators...
enum orderAttr
{
	NONE,
	NAME,
	BDAY
};

// Function Prototypes for Overloaded Stream Operators
std::ostream &operator << (std::ostream &, const Person &);

//*************************************************************************//
// class Person - This is our 'Person' class thatg is our 'Person' record. // 
//*************************************************************************//
class Person
{
private:
	// PRIVATE:
	// Our private member variables are person 'name', person 'bday' (birthday),
    // a string pointer which is set to either the 'name' of the 'bday', and
	// an ordering attribute.  The ordering attribute is set at instantiation
	// and is used to let us initilize 'pkey' to point to the name or the bday.
	string name;           // Persons name.
	string bday;           // Persons birthday
	string * pkey;         // our key pointer to either the name or birthday.
	orderAttr ordering;    // ordering attribute used by overloaded comparison
	                       // operators for 'Person' objects.
public:
	// PUBLIC:
	// Constructors and destructor
	Person();
	Person(string, string, orderAttr);
	~Person();
	// Accessors
	string getName() const;
	string getBday() const;
	string * getPkey() const;
	orderAttr getOrder() const;
	// Mutators
	void setName(string aName);
	void setBday(string aBDay);
	void setOrdering(orderAttr anOrder);

	//**********************************************************************//
	// Person operator >                                                    //
	// pre:  Person objects we want to compare.                             //
	// return: result of comparing the operands (>)                         //
	//**********************************************************************//
	virtual bool operator > (const Person &);		// Overloaded >

	// istream and ostream overloading as friends
	friend std::ostream &operator << (std::ostream &, const Person &);

	//**********************************************************************//
	// Person operator ==                                                   //
	// pre:  Person objects we want to compare.                             //
	// return: result of comparing the operands (==)                        //
	//**********************************************************************//
	bool operator == (const Person &);		// Overloaded >

	//**********************************************************************//
	// Person operator =                                                    //
	// pre:  source and target Person opjects we want to perform a copy     //
	//       operation on.                                                  //
	// return: result of assign one operand the result of an RHS expression.//
	//**********************************************************************//
	virtual Person& operator=(const Person &);  // overloaded =
};
// end Person class

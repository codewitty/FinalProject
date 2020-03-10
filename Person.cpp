#include <iostream>
#include <string>
#include <iomanip>
#include "Person.h"

using namespace std;

//**********************************************************************//
// Person constructor to make an uninitialized Person.      			//
// post: unusable Person instance.										//
//**********************************************************************//
Person::Person()
{
	name = "";
	bday = "";
	pkey = nullptr;
	ordering = NONE;
}

//**********************************************************************//
// Person constructor parametrized to make a complete Person.			//
// post: Usable Person intance.								    		//
//**********************************************************************//
Person::Person(string aName, string aBDay, orderAttr anOrder)
{
	name = aName;
	bday = aBDay;
	ordering = anOrder;
	if (ordering == NAME)
		pkey = &name;
	else if (ordering == BDAY)
		pkey = &bday;
	else {
		pkey = nullptr;
		cout << "ERROR : order not set at parameterized construction" << endl;
	}
}

//**********************************************************************//
// Our Person destructor                        					    //
// pre:  Existing Person            									//
// post: Now nonexiting Person											//
//**********************************************************************//
Person::~Person()
{
}

//**********************************************************************//
// This is our function to push.									    //
// pre:  Existing queue or empty queue									//
// post: queue with added node.											//
//**********************************************************************//
string Person::getName() const
{
	return name;
}

//**********************************************************************//
// This is our function to push.									    //
// pre:  Existing queue or empty queue									//
// post: queue with added node.											//
//**********************************************************************//
string Person::getBday() const
{
	return bday;
}

//**********************************************************************//
// This is our accessor function to get the 'Person' ordering attribute //
// pre:  Existing queue or empty queue									//
// post: queue with added node.											//
//**********************************************************************//
string * Person::getPkey() const
{
	return pkey;
}

//**********************************************************************//
// This is our accessor function to get the 'Person' ordering attribute //
// which is used by overloaded Person comparison operators.             //
// pre:  Existing queue or empty queue									//
// post: queue with added node.											//
//**********************************************************************//
orderAttr Person::getOrder() const
{
	return ordering;
}

//**********************************************************************//
// This is our mutator function to set the the Person's name (name).    //
// pre:  Existing Person            									//
// post: Person's name is updated.										//
//**********************************************************************//
void Person::setName(string aName)
{
	name = aName;
}

//**********************************************************************//
// This is our mutator function to set the the Person's birthday (bday).//
// pre:  Existing Person                								//
// post: Person's birthday is updated.								    //
//**********************************************************************//
void Person::setBday(string aBDay)
{
	bday = aBDay;
}

//**********************************************************************//
// This is our mutator function to set ordering attribute.			    //
// pre:  Existing Person.               								//
// post: Most importantly 'pkey' is et appropriately.  Also the         //
//       ordering attribute is set   									//
//**********************************************************************//
void Person::setOrdering(orderAttr anOrder)
{
	if (anOrder == NAME)
		pkey = &name;
	else if (anOrder == BDAY)
		pkey = &bday;
	else {
		pkey = nullptr;
		cout << "ERROR : order not set at parameterized construction" << endl;
	}
}

//************************************************************
// Overloaded > operator. Returns true if the current object *
// is set to a value greater than that of right.             *
//************************************************************'
bool Person::operator>(const Person &right)
{
	bool status{ false };

	if (*pkey > *right.pkey)
		status = true;

	return status;
}


//*********************************************************
// Overloaded << operator. Gives std::cout the ability to *
// directly display Person objects.                       *
//*********************************************************
std::ostream & operator<<(std::ostream &strm, const Person &obj)
{
	strm << left << setw(60) << obj.name << right << setw(20) << obj.bday;
	return strm;
}

//*********************************************************
// Overloaded == operator. Gives std::cout the ability to *
// directly display Person objects.                       *
//*********************************************************
bool Person::operator==(const Person &right)
{
	if (*pkey == *right.pkey)
		return true;
	else
		return false;
}

//*********************************************************
// Overloaded = operator. Gives std::cout the ability to  *
// directly display Person objects.                       *
//*********************************************************
Person & Person::operator=(const Person &right)
{
	if (this != &right) {
		this->name = right.name;
		this->bday = right.bday;
		this->pkey = right.pkey;
		this->ordering = right.ordering;
	}
	return *this;
}

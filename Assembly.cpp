#include <string>
#include <iomanip>
#include "Assembly.h"

Assembly::Assembly()
{
	name = "";       // Assembly Name           (string)
	type = "";       // Assembly Method         (string)
	num_contigs = 0;        // Number Contigs          (int)
	size = 0;        // Size (bases)            (int)
	n50 = 0;        // n50 (kbp)               (int)
	gc = 0.0;      // float (GC content)      (float)
	unknown = 0.0;      // float (Percent Unknown) (float)
	pkey = nullptr;  // void *
	keyType = assemblyAttribute::NONE;     // NONE for now...
}

Assembly::Assembly(string aName, string aType, int aNumContigs, int aSize, int anN50, double aGc, double anUnknown, assemblyAttribute anOpKeyType)
{
	name = aName;
	type = aType;
	num_contigs = aNumContigs;
	size = aSize;
	n50 = anN50;
	gc = aGc;
	unknown = anUnknown;
	keyType = anOpKeyType;
	setOrdering(keyType);
}

//**********************************************************************//
// This is our mutator function to set ordering attribute.			    //
// pre:  Existing Assembly.               								//
// post: Most importantly 'pkey' is et appropriately.  Also the         //
//       ordering attribute is set   									//
//**********************************************************************//
void Assembly::setOrdering(assemblyAttribute anOrder)
{
	// These are the Assembly member types we are processing.
	// NONE,        (==> unassigned)
	// NAME,		(string)
	// TYPE,        (string)
	// NUM_CONTIGS, (int)
	// SIZE,        (int)
	// N50,         (int)
	// GC,          (float)
	// UNKNOWN      (float)
	switch (anOrder)
	{
	case assemblyAttribute::NONE:
		pkey = nullptr;
		this->keyType = assemblyAttribute::NONE;
		break;
	case assemblyAttribute::NAME:        // NAME and TYPE are strings
		pkey = static_cast<void*>(&name);
		this->keyType = assemblyAttribute::NAME;
		break;
	case assemblyAttribute::TYPE:
		pkey = static_cast<void*>(&type);
		this->keyType = assemblyAttribute::TYPE;
		break;
	case assemblyAttribute::NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
		pkey = static_cast<void*>(&num_contigs);
		this->keyType = assemblyAttribute::NUM_CONTIGS;
		break;
	case assemblyAttribute::SIZE:
		pkey = static_cast<void*>(&size);
		this->keyType = assemblyAttribute::SIZE;
		break;
	case assemblyAttribute::N50:
		pkey = static_cast<void*>(&n50);
		this->keyType = assemblyAttribute::N50;
		break;
	case assemblyAttribute::GC:          // GC, UNKNOWN are float
		pkey = static_cast<void*>(&gc);
		this->keyType = assemblyAttribute::GC;
		break;
	case assemblyAttribute::UNKNOWN:
		pkey = static_cast<void*>(&unknown);
		this->keyType = assemblyAttribute::UNKNOWN;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::setOrdering() : Operator (>) cant happen, keytype is BOGUS!" << endl;
	}
}


string Assembly::getName() const
{
	return this->name;
}

string Assembly::getType() const
{
	return this->type;
}

int Assembly::getNumContigs() const
{
	return this->num_contigs;
}

int Assembly::getSize() const
{
	return this->size;
}

int Assembly::getN50() const
{
	return this->n50;
}

double Assembly::getGc() const
{
	return this->gc;
}

double Assembly::getUnknown()
{
	return this->unknown;
}

void* Assembly::getPkey() const
{
	return this->pkey;
}

assemblyAttribute Assembly::getKeyType() const
{
	return this->keyType;
}

void Assembly::setName(string aGNomeAssemblyName)
{
	this->name = aGNomeAssemblyName;
}

void Assembly::setType(string aGNomeAssemblyType)
{
	this->type = aGNomeAssemblyType;
}

void Assembly::setNumContigs(int numContigs)
{
	this->num_contigs = numContigs;
}

void Assembly::setSize(int aGNomeAssemblySize)
{
	this->size = aGNomeAssemblySize;
}

void Assembly::setN50(int aGNomeAssemblyN50)
{
	this->n50 = aGNomeAssemblyN50;
}

void Assembly::setGc(float aGNomeAssemblyGc)
{
	this->gc = aGNomeAssemblyGc;
}

void Assembly::setUnknown(float aGNomeAssemblyUnknown)
{
	this->unknown = aGNomeAssemblyUnknown;
}

bool Assembly::operator<(const Assembly& right) const
{
	// These are the Assembly member types we are processing.
	// NONE,        (==> unassigned)
	// NAME,		(string)
	// TYPE,        (string)
	// NUM_CONTIGS, (int)
	// SIZE,        (int)
	// N50,         (int)
	// GC,          (float)
	// UNKNOWN      (float)

	bool retval = false;
	switch (this->keyType)
	{
	case assemblyAttribute::NONE:
		cout << "\nAssembly::operator>() : Operator (<) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case assemblyAttribute::NAME:        // NAME and TYPE are strings
	case assemblyAttribute::TYPE:
		if (*(static_cast<string*>(pkey)) < *(static_cast<string*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case assemblyAttribute::SIZE:
	case assemblyAttribute::N50:
		if (*(static_cast<int*>(pkey)) < *(static_cast<int*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::GC:          // GC, UNKNOWN are float
	case assemblyAttribute::UNKNOWN:
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (<) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

bool Assembly::operator>(const Assembly& right) const
{
	// These are the Assembly member types we are processing.
	// NONE,        (==> unassigned)
	// NAME,		(string)
	// TYPE,        (string)
	// NUM_CONTIGS, (int)
	// SIZE,        (int)
	// N50,         (int)
	// GC,          (float)
	// UNKNOWN      (float)

	bool retval = false;
	switch (this->keyType)
	{
	case assemblyAttribute::NONE:
		cout << "\nAssembly::operator>() : Operator (>) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case assemblyAttribute::NAME:        // NAME and TYPE are strings
	case assemblyAttribute::TYPE:
		if (*(static_cast<string*>(pkey)) > * (static_cast<string*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case assemblyAttribute::SIZE:
	case assemblyAttribute::N50:
		if (*(static_cast<int*>(pkey)) > * (static_cast<int*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::GC:          // GC, UNKNOWN are float
	case assemblyAttribute::UNKNOWN:
		if (*(static_cast<float*>(pkey)) > * (static_cast<double*>(right.pkey)))
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (>) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

bool Assembly::operator==(const Assembly& right) const
{
	// These are the Assembly member types we are processing.
	// NONE,        (==> unassigned)
	// NAME,		(string)
	// TYPE,        (string)
	// NUM_CONTIGS, (int)
	// SIZE,        (int)
	// N50,         (int)
	// GC,          (float)
	// UNKNOWN      (float)

	bool retval = false;
	switch (this->keyType)
	{
	case assemblyAttribute::NONE:
		cout << "\nAssembly::operator>() : Operator (==) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case assemblyAttribute::NAME:        // NAME and TYPE are strings
	case assemblyAttribute::TYPE:
		if (*(static_cast<string*>(pkey)) == *(static_cast<string*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case assemblyAttribute::SIZE:
	case assemblyAttribute::N50:
		if (*(static_cast<int*>(pkey)) == *(static_cast<int*>(right.pkey)))
			retval = true;
		break;
	case assemblyAttribute::GC:          // GC, UNKNOWN are float
	case assemblyAttribute::UNKNOWN:
		if (*(static_cast<float*>(pkey)) == *(static_cast<double*>(right.pkey)))
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (>) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

Assembly& Assembly::operator=(const Assembly& right)
{
	if (this != &right) {
		this->name = right.name;
		this->type = right.type;
		this->num_contigs = right.num_contigs;
		this->size = right.size;
		this->n50 = right.n50;
		this->gc = right.gc;
		this->unknown = right.unknown;
		this->pkey = right.pkey;
		this->keyType = right.keyType;
	}
	return *this;
}

void Assembly::printItemKey()
{
	switch (keyType)
	{
	case assemblyAttribute::NONE:
		cout << "\nAssembly::printItemKey() : Cant happen, keytype is 'NONE'" << endl;
		break;
	case assemblyAttribute::NAME:        // NAME and TYPE are strings
	case assemblyAttribute::TYPE:
	{
		string ourStrKey = *(static_cast<string *>(pkey));
		cout << ourStrKey << "\n";
		break;
	}
	case assemblyAttribute::NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case assemblyAttribute::SIZE:
	case assemblyAttribute::N50:
	{
		int ourIntKey = *(static_cast<int *>(pkey));
		cout << ourIntKey << "\n";
		break;
	}
	case assemblyAttribute::GC:          // GC, UNKNOWN are float
	case assemblyAttribute::UNKNOWN:
	{
		double ourDoubleKey = *(static_cast<double *>(pkey));
		cout << ourDoubleKey << "\n";
		break;
	}
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::printItemKey() : Cant happen, keytype is BOGUS!" << endl;
	}

}

std::ostream & operator<<(std::ostream & strm, Assembly & obj)
{
	// output the NAME
#ifndef NOWINHEAD
	// windows screen handle used to map stdio...
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(screen, Bright_White);
	if (obj.keyType == assemblyAttribute::NAME) {
		SetConsoleTextAttribute(screen, Bright_Green);
		strm << setw(30) << left << obj.name; //
		SetConsoleTextAttribute(screen, Bright_White);
	} else
#endif
		strm << setw(30) << left << obj.name; //

	// output the TYPE
	strm << setw(20) << obj.type;

	// output the NUM_CONTIGS
#ifndef NOWINHEAD
	if (obj.keyType == assemblyAttribute::NUM_CONTIGS) {
		SetConsoleTextAttribute(screen, Bright_Green);
		strm << setw(15) << obj.num_contigs; //
		SetConsoleTextAttribute(screen, Bright_White);
	} else
#endif
		strm << setw(15) << obj.num_contigs; //

		// output the SIZE
#ifndef NOWINHEAD
	if (obj.keyType == assemblyAttribute::SIZE) {
		SetConsoleTextAttribute(screen, Bright_Green);
		strm << setw(10) << obj.size; //
		SetConsoleTextAttribute(screen, Bright_White);
	}
	else
#endif
	strm << setw(10) << obj.size;  //

			// output the N50
#ifndef NOWINHEAD
	if (obj.keyType == assemblyAttribute::N50) {
		SetConsoleTextAttribute(screen, Bright_Green);
		strm << setw(10) << obj.n50; //
		SetConsoleTextAttribute(screen, Bright_White);
	}
	else
#endif
	strm << setw(10) << obj.n50;   //


	strm << setw(10) << obj.gc;
	strm << setw(10) << obj.unknown;
	return strm;
}
// Const version
std::ostream & operator<<(std::ostream & strm, const Assembly & obj)
{
	strm << setw(30) << left << obj.name << setw(20) << obj.type << setw(15) << obj.num_contigs
		<< setw(10) << obj.size << setw(10) << obj.n50 << setw(10) << obj.gc << setw(10) << obj.unknown;
	return strm;
}

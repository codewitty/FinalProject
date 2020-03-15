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
	keyType = NONE;     // NONE for now...
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
	case NONE:
		pkey = nullptr;
		this->keyType = NONE;
		break;
	case NAME:        // NAME and TYPE are strings
		pkey = static_cast<void *>(&name);
		this->keyType = NAME;
		break;
	case TYPE:
		pkey = static_cast<void *>(&type);
		this->keyType = TYPE;
		break;
	case NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
		pkey = static_cast<void *>(&num_contigs);
		this->keyType = NUM_CONTIGS;
		break;
	case SIZE:
		pkey = static_cast<void *>(&size);
		this->keyType = SIZE;
		break;
	case N50:
		pkey = static_cast<void *>(&n50);
		this->keyType = N50;
		break;
	case GC:          // GC, UNKNOWN are float
		pkey = static_cast<void *>(&gc);
		this->keyType = GC;
		break;
	case UNKNOWN:
		pkey = static_cast<void *>(&unknown);
		this->keyType = UNKNOWN;
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

void * Assembly::getPkey() const
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

bool Assembly::operator<(const Assembly &right) const
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
	case NONE:
		cout << "\nAssembly::operator>() : Operator (<) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case NAME:        // NAME and TYPE are strings
	case TYPE:
		if (*(static_cast<string *>(pkey)) < *(static_cast<string *>(right.pkey)))
			retval = true;
		break;
	case NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case SIZE:
	case N50:
		if (*(static_cast<int *>(pkey)) < *(static_cast<int *>(right.pkey)))
			retval = true;
		break;
	case GC:          // GC, UNKNOWN are float
	case UNKNOWN:
		if (*(static_cast<double *>(pkey)) < *(static_cast<double *>(right.pkey)))
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (<) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

bool Assembly::operator>(const Assembly &right)
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
	case NONE:
		cout << "\nAssembly::operator>() : Operator (>) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case NAME:        // NAME and TYPE are strings
	case TYPE:
		if (*(static_cast<string *>(pkey)) > *(static_cast<string *>(right.pkey)))
			retval = true;
		break;
	case NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case SIZE:
	case N50:
		if (*(static_cast<int *>(pkey)) > *(static_cast<int *>(right.pkey)))
			retval = true;
		break;
	case GC:          // GC, UNKNOWN are float
	case UNKNOWN:
		if (*(static_cast<float *>(pkey)) > *(static_cast<double *>(right.pkey)))
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (>) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

bool Assembly::operator==(const Assembly &right) const
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
	case NONE:
		cout << "\nAssembly::operator>() : Operator (==) cant happen, keytype is 'NONE'" << endl;
		retval = false;
		break;
	case NAME:        // NAME and TYPE are strings
	case TYPE:
		if (*(static_cast<string *>(pkey)) == *(static_cast<string *>(right.pkey)))
			retval = true;
		break;
	case NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case SIZE:
	case N50:
		if (*(static_cast<int *>(pkey)) == *(static_cast<int *>(right.pkey)))
			retval = true;
		break;
	case GC:          // GC, UNKNOWN are float
	case UNKNOWN:
		if (*(static_cast<float *>(pkey)) == *(static_cast<double *>(right.pkey)))
			retval = true;
		break;
	default: // code to be executed if n doesn't match any cases
		cout << "Assembly::operator>() : Operator (>) cant happen, keytype is BOGUS!" << endl;
		retval = false;

	}

	return retval;
}

Assembly & Assembly::operator=(const Assembly &right)
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
	case NONE:
		cout << "\nAssembly::printItemKey() : Cant happen, keytype is 'NONE'" << endl;
		break;
	case NAME:        // NAME and TYPE are strings
	case TYPE:
	{
		string ourStrKey = *(static_cast<string *>(pkey));
		cout << ourStrKey << "\n";
		break;
	}
	case NUM_CONTIGS: // NUM_CONTIGS, N50, GC are integers
	case SIZE:
	case N50:
	{
		int ourIntKey = *(static_cast<int *>(pkey));
		cout << ourIntKey << "\n";
		break;
	}
	case GC:          // GC, UNKNOWN are float
	case UNKNOWN:
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
	//strm << setw(70) << left << obj.name << ", " << setw(10) << obj.type << ", " << setw(10) << obj.num_contigs << ", "
	//	<< setw(10) << obj.size << ", " << setw(10) << obj.n50 << ", " << setw(10) << obj.gc << ", " << setw(10) << obj.unknown;
	strm << setw(80) << left << obj.name << setw(20) << obj.type << setw(15) << obj.num_contigs 
		<< setw(10) << obj.size << setw(10) << obj.n50 << setw(10) << obj.gc << setw(10) << obj.unknown;
	return strm;
}

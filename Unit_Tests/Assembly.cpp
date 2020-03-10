#include "Assembly.h"
#include <string>

Assembly::Assembly()
{
	name        = "";       // Assembly Name
	type        = "";       // Assembly Method
	num_contigs = 0;        // Number Configs
	size        = 0;        // Size (bases)
	n50         = 0;        // n50 (kbp)
	gc          = 0.0;      // float (GC content)
	unknown     = 0.0;      // float (Percent Unknown)
	pkey        = nullptr;  // void *
}

Assembly::Assembly(int whole, int frac)
{
}

bool Assembly::operator>(const Assembly &)
{
	return false;
}

bool Assembly::operator==(const Assembly &)
{
	return false;
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
	}
	return *this;
}

std::ostream & operator<<(std::ostream & strm, Assembly & obj)
{
	strm << obj.name << ", " << obj.type << ", " << obj.num_contigs << ", " 
		<< obj.size << ", " << obj.n50 << ", " << obj.gc << ", " << obj.unknown;
	return strm;
}

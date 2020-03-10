#include "assembly.h"
#include <string>

Assembly::Assembly(){
	name = null;
	type = null;
	num_contigs = 0;
	size = 0;
	n50 = 0;
	gc = 0.0;
	unknown = 0.0;
	key = NONE;
}

Assembly::Assembly(string n, string t, int nc, int s, int n_fifty,float g_cee, float unk){
	name = n;
	type =t;
	num_contigs = nc;
	size = s;
	n50 = n_fifty;
	gc = g_cee;
	unknown = unk;
}


std::ostream& operator<<(std::ostream& out, Assembly& right)
{
	// out << right.getWholeValue() << "." << right.getFracValue() << "\n";
	out << "\n";
	return out;
}
/*
std::istream& operator>>(std::istream& in, Assembly& right)
{
	in >> right.wholeValue;
	in >> right.fracValue;
	return in;
}
*/
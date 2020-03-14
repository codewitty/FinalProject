#include <iostream>
#include "ArrayTemplateClass.h"


using namespace std;

int main() {
	int number = 1;
	Array<int> table(5);
	table[0] = number;

	cout << table[0] << endl;
	return 0;
}


/*
Linked List Unit Test
Class : CIS22C61Y
*/
#include <iostream>
#include <string>
#include "Assembly.h"
#include "LinkedList.h"

using namespace std;

//******************************************************************************
// int main() - Main declares defines 3 arrays of 10 elements each. 
// An int, string and dollar.
//
// Our list template allows us to sort whatever type is passed in ascending
// and descending order or unsorted. For our case to demonstrate the template
// support for list in descending order we print integers, to demonstrate 
// support for ascending order we print strings and to demonstrate unordered
// insertion we print rupee objects.
// 
// PSEUDOCODE:
// 
//	1.  Print header
//	2.  Declare 3 lists (Integer, String and Rupee Lists)
//	3A. Insert integers in the descending order
//	3B. Print resulting integer list
//	4A. Insert strings in the ascending order
//	4B. Print resulting string list
//	5A. Insert rupee objects unordered 
//	5B. Print resulting rupee object list
//******************************************************************************
int main()
{
	// 1.  Print Header
	cout << "\n\nLinked List Unit Test\n"
		<< "Class : CIS22C61Y"
		<< endl;

	// 2.  Instantiate list of items
	LinkedList<int> myListDescending(DESCENDING);
//	LinkedList<string> myListAscending(ASCENDING);
	LinkedList<Assembly> myListA(ASCENDING);

	// 3A. Add integers to descending ordered list
	myListDescending.insert(454);
	myListDescending.insert(2323);
	myListDescending.insert(344);
	myListDescending.insert(2989);
	myListDescending.insert(93);
	myListDescending.insert(78);
	myListDescending.insert(536);
	myListDescending.insert(32);
	myListDescending.insert(4225);
	myListDescending.insert(425);

	// 3B. Print the resulting integer list
	cout << "\nIntegers list in descending order" << endl;
	cout << "---------------------------------" << endl;
	myListDescending.print();
	cout << endl;
//g
//g	// 4A. Add strings to ascending ordered list
//g	myListAscending.insert("Edward");
//g	myListAscending.insert("Gail");
//g	myListAscending.insert("Josh");
//g	myListAscending.insert("Isaac");
//g	myListAscending.insert("Harry");
//g	myListAscending.insert("Frank");
//g	myListAscending.insert("Adam");
//g	myListAscending.insert("Drake");
//g	myListAscending.insert("Charlotte");
//g	myListAscending.insert("Bill");
//g
//g	// 4B. Print the resulting string list
//g	cout << "\nStrings list in ascending order" << endl;
//g	cout << "---------------------------------" << endl;
//g	myListAscending.print();
//g	cout << endl;

	Assembly AssemblyByName01("contig-20.fa", "pilon+idba", 2637, 2182179, 306, 0.1573, 0.1964, N50);
	myListA.insert(AssemblyByName01);
	Assembly AssemblyByName02("contig-30.fa", "Spades", 2130, 1660411, 321, 0.5292, 0.3762, N50);
	myListA.insert(AssemblyByName02);
	Assembly AssemblyByName03("contig-40.fa", "MosaicFLye", 2309, 2463148, 265, 0.8489, 0.759, N50);
	myListA.insert(AssemblyByName03);
	Assembly AssemblyByName04("contig-50.fa", "velvet", 1769, 2792422, 344, 0.3692, 0.4096, N50);
	myListA.insert(AssemblyByName04);
	Assembly AssemblyByName05("contig.fa", "idba-ud", 2027, 2779667, 227, 0.7867, 0.86, N50);
	myListA.insert(AssemblyByName05);
	Assembly AssemblyByName06("gather_scaffold_reads_sensitive.fa", "MosaicFLye", 3986, 1515576, 68, 0.8446, 0.5618, N50);
	myListA.insert(AssemblyByName06);
	Assembly AssemblyByName07("graph-20.fa", "MosaicFLye", 1878, 2493713, 151, 0.1897, 0.3024, N50);
	myListA.insert(AssemblyByName07);
	Assembly AssemblyByName08("graph-30.fa", "MosaicFLye", 635, 2273517, 106, 0.0114, 0.7121, N50);
	myListA.insert(AssemblyByName08);
	Assembly AssemblyByName09("graph-40.fa", "velvet", 1456, 2361700, 284, 0.0598, 0.8469, N50);
	myListA.insert(AssemblyByName09);
	Assembly AssemblyByName10("graph-50.fa", "velvet", 279, 1723612, 297, 0.5048, 0.79, N50);
	myListA.insert(AssemblyByName10);
	Assembly AssemblyByName11("scaffold.cd_hit.fa", "Spades", 1315, 2428461, 248, 0.573, 0.2274, N50);
	myListA.insert(AssemblyByName11);
	Assembly AssemblyByName12("scaffold.cd_hit.fa", "Spades", 1315, 2428461, 297, 0.573, 0.2274, N50);
	myListA.insert(AssemblyByName12);
	// 4B. Print the resulting string list
	cout << "\n Assembly object list in ascending order" << endl;
	cout << "---------------------------------" << endl;
	cout << "THIS IS A TEST" << endl;
	cout << AssemblyByName01 << endl;
	myListA.print();

	// 5A. Add rupee objects to unordered list
/*
	// These are parallel arrays.
	int rupee_value[] = { 45, 232, 34, 298, 9, 7, 53, 3, 422, 42 };
	int paise_value[] = { 40, 30, 40, 90, 30, 80, 60, 20, 45, 25 };

	// loop for 10 rupee values : 
	//		instantiate random rupee object
	//		insert into unordered list
	// end loop.
	for (int ndx = 0; ndx < 10; ndx++) {
		Rupee anItem(rupee_value[ndx], paise_value[ndx]);
		myListUnordered.insert(anItem);
	} //end for loop

	cout << "\nRupee list in unsorted order" << endl;
	cout << "---------------------------------" << endl;

	// 5B. Print the resulting rupee object list
	myListUnordered.print();
	cout << endl;
*/
	return 0;
}

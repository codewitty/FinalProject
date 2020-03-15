#include <iostream>
#include "ArrayTemplateClass.h"
#include "HashBucket.h"
#include "Assembly.h"
#include "hash.h"

int main() {

	Assembly AssemblyByName01("contig-20.fa", "pilon+idba", 2637, 2182179, 306, 0.1573, 0.1964, NAME);
	Assembly AssemblyByName02("contig-30.fa", "Spades", 2130, 1660411, 321, 0.5292, 0.3762, NAME);
	Assembly AssemblyByName03("contig-40.fa", "MosaicFLye", 2309, 2463148, 265, 0.8489, 0.759, NAME);
	/*
	Assembly AssemblyByName04("contig-50.fa", "velvet", 1769, 2792422, 344, 0.3692, 0.4096, NAME);
	Assembly AssemblyByName05("contig.fa", "idba-ud", 2027, 2779667, 227, 0.7867, 0.86, NAME);
	Assembly AssemblyByName06("gather_scaffold_reads_sensitive.fa", "MosaicFLye", 3986, 1515576, 68, 0.8446, 0.5618, NAME);
	Assembly AssemblyByName07("graph-20.fa", "MosaicFLye", 1878, 2493713, 151, 0.1897, 0.3024, NAME);
	Assembly AssemblyByName08("graph-30.fa", "MosaicFLye", 635, 2273517, 106, 0.0114, 0.7121, NAME);
	Assembly AssemblyByName09("graph-40.fa", "velvet", 1456, 2361700, 284, 0.0598, 0.8469, NAME);
	Assembly AssemblyByName10("graph-50.fa", "velvet", 279, 1723612, 297, 0.5048, 0.79, NAME);
	*/
	HashTable table;
	table.add(AssemblyByName01);
	table.add(AssemblyByName02);
	table.add(AssemblyByName03);
	/*table.add(AssemblyByName04);
	table.add(AssemblyByName05);
	table.add(AssemblyByName06);
	table.add(AssemblyByName07);
	table.add(AssemblyByName08);*/
	
	table.getLength();

	table.printTable();
	table.remove(AssemblyByName02);
	cout << "After removing: " << endl << endl << endl;
	table.printTable();

	table.clear();
	cout << "After clearing " << endl << endl;
	table.printTable();

	system("pause");
}

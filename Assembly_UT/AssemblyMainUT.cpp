#include <iostream>
#include <string>
#include "Assembly.h"
using namespace std;

int main()
{
	Assembly AssemblyByName01("contig-20.fa", "pilon+idba", 2637, 2182179, 306, 0.1573, 0.1964, NAME);
	Assembly AssemblyByName02("contig-30.fa", "Spades", 2130, 1660411, 321, 0.5292, 0.3762, NAME);
	Assembly AssemblyByName03("contig-40.fa", "MosaicFLye", 2309, 2463148, 265, 0.8489, 0.759, NAME);
	Assembly AssemblyByName04("contig-50.fa", "velvet", 1769, 2792422, 344, 0.3692, 0.4096, NAME);
	Assembly AssemblyByName05("contig.fa", "idba-ud", 2027, 2779667, 227, 0.7867, 0.86, NAME);
	Assembly AssemblyByName06("gather_scaffold_reads_sensitive.fa", "MosaicFLye", 3986, 1515576, 68, 0.8446, 0.5618, NAME);
	Assembly AssemblyByName07("graph-20.fa", "MosaicFLye", 1878, 2493713, 151, 0.1897, 0.3024, NAME);
	Assembly AssemblyByName08("graph-30.fa", "MosaicFLye", 635, 2273517, 106, 0.0114, 0.7121, NAME);
	Assembly AssemblyByName09("graph-40.fa", "velvet", 1456, 2361700, 284, 0.0598, 0.8469, NAME);
	Assembly AssemblyByName10("graph-50.fa", "velvet", 279, 1723612, 297, 0.5048, 0.79, NAME);
	Assembly AssemblyByName11("scaffold.cd_hit.fa", "Spades", 1315, 2428461, 248, 0.573, 0.2274, NAME);
	Assembly AssemblyByName12("scaffold.fa", "MosaicFLye", 280, 1793118, 140, 0.476, 0.2464, NAME);
	Assembly AssemblyByName13("ERS1098427.fasta.gz", "MosaicFLye", 1221, 2094776, 159, 0.5561, 0.6357, NAME);
	Assembly AssemblyByName14("ERS248758.fasta.gz", "MosaicFLye", 2041, 1868744, 314, 0.2847, 0.2339, NAME);
	Assembly AssemblyByName15("ERS248788.fasta.gz", "Spades", 3056, 2731522, 329, 0.956, 0.8018, NAME);
	Assembly AssemblyByName16("ERS248804.fasta.gz", "Spades", 2348, 2846495, 205, 0.3942, 0.5904, NAME);
	Assembly AssemblyByName17("pilon.fasta.gz", "Spades", 914, 2677840, 88, 0.2821, 0.6297, NAME);

	if (&AssemblyByName05 > &AssemblyByName01) {
		cout << "Assembly [" << AssemblyByName05 << "] is greater than " << endl;
		cout << "assembly [" << AssemblyByName01 << "] (by NAME)." << endl;
		cout << "Our (>) operator for assembly works." << endl;
	}

	if (&AssemblyByName01 < &AssemblyByName05) {
		cout << "Assembly [" << AssemblyByName01 << "] is lesser than " << endl;
		cout << "assembly [" << AssemblyByName05 << "] (by NAME)." << endl;
		cout << "Our (<) operator for assembly works." << endl;
	}

	if (&AssemblyByName15 == &AssemblyByName15) {
		cout << "Assembly [" << AssemblyByName15 << "] and " << endl;
		cout << "assembly [" << AssemblyByName15 << "] are equal (by NAME)." << endl;
		cout << "Our (==) operator for assembly works." << endl;
	}

	return 0;
}

#include <iostream>
#include <string>

#ifndef ASSEMBLY_H
#define ASSEMBLY_H

enum assemblyAttribute{
	NONE,
	NAME,
	NUM_CONTIGS,
	N50
};

class Assembly {
protected:
	string name;
	string type;
	int num_contigs;
	int size;
	int n50;
	float gc;
	float unknown;
	<template T>
	T* key;

public:
	Assembly();
	Assembly(int whole, int frac);
	virtual ~Assembly() {};

	friend std::ostream& operator << (std::ostream &out, Assembly &right);
	friend std::istream& operator >> (std::istream & in, Assembly &right);

};


#endif 

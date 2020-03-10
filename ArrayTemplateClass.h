#pragma once
using namespace std;

template <typename T>
class Array
{
private:
	int m_nLength;
	T *m_ptData;

public:
	Array();

	Array(int nLength);

	~Array();

	void Erase();

	//**********************************************************************//
	// Array operator [] - our Array subscript operator                     //
	// PRE    : target index array request.                                 //
	// RETURN : Reference of the Array object we are targeting.             //
	//**********************************************************************//
	T& operator[](int &nIndex);

	// The length of the array is always an integer
	// It does not depend on the data type of the array
	int GetLength(); // templated GetLength() function defined below
};


// Constructor template no parameters. Initialises our member variables
template<typename T>
Array<T>::Array()
{
	m_nLength = 0;
	m_ptData = 0;
}

// Constructor template one parameter.
// Iniitialises our member variables setting the 
// length parameter according to user specifications
template<typename T>
Array<T>::Array(int nLength)
{
	m_ptData = new T[nLength];
	m_nLength = nLength;
}

// Destructor template, We need to clean up after ourselves
template<typename T>
Array<T>::~Array()
{
	delete[] m_ptData;
}

// Erase utility function
template<typename T>
void Array<T>::Erase()
{
	delete[] m_ptData;
	// We need to make sure we set m_pnData to 0 here, otherwise it will
	// be left pointing at deallocated memory!
	m_ptData = 0;
	m_nLength = 0;
}


// Subscript overload operator for Array Template
template<typename T>
T & Array<T>::operator[](int & nIndex)
{
	if (nIndex >= 0 && nIndex < m_nLength)
		return m_ptData[nIndex];
	return m_ptData[0];
}

// Getlegth utility, returns GetLength
template <typename T>
int Array<T>::GetLength() { return m_nLength; }

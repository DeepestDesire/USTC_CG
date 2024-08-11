#include "DArray.h"

#include "iostream"

#include <cassert>

using namespace std;

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue)
	: m_pData(new double[nSize]),  m_nSize(dValue)
{
	for (int i = 0; i < nSize; i++)
		m_pData[i] = dValue;
}

DArray::DArray(const DArray& arr) 
	: m_pData(new double[arr.m_nSize]) , m_nSize(arr.m_nSize)
{
	for (int i = 0; i < m_nSize; i++)
		m_pData[i] = arr.m_pData[i];
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	cout << endl;
	cout << "=== Pint function ===" << this << endl;
	cout << "this ptr is " << this << endl;
	cout << "size is " << m_nSize << endl;
	cout << "value is: ";
	for (int i = 0; i < m_nSize; i++)
		cout << m_pData[i] << ", ";
	cout  << endl;
}

void DArray::Init() {
	m_nSize = 0;
	m_pData = nullptr;
}

void DArray::Free() {
	delete[] m_pData;
	m_pData = nullptr;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize; 
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (nSize == m_nSize)
		return;

	double* dTemp = new double[nSize];

	int nTemp = (nSize > m_nSize) ? m_nSize : nSize;

		for (int i = 0; i < nTemp; i++)
			dTemp[i] = m_pData[i];

		for (int i = nTemp; i < nSize; i++)
			dTemp[i] = 0;

	delete[] m_pData;
	m_pData = dTemp;
	m_nSize = nSize;

}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	
	assert(nIndex >= 0 || nIndex < m_nSize);
	return *(m_pData + nIndex);
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex >= 0 || nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	assert(nIndex >= 0 || nIndex < m_nSize);
		const double dTemp = m_pData[nIndex];
		return dTemp;
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	double* dTemp = new double[static_cast<size_t>(m_nSize) + 1];

	for (int i = 0; i < m_nSize; i++)
		dTemp[i] = m_pData[i];

	dTemp[m_nSize] = dValue;

	delete[] m_pData;
	m_pData = dTemp;
	m_nSize++;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);

	double* dTemp = new double[static_cast<size_t>(m_nSize) - 1];
	for (int i = 0; i < nIndex; i++)
		dTemp[i] = m_pData[i];

	for (int i = nIndex; i < m_nSize-1; i++)
		dTemp[i] = m_pData[i+1];

	delete[] m_pData;
	m_pData = dTemp;
	m_nSize--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex <= m_nSize); // nIndex == m_nSize is legal

	double* dTemp = new double[static_cast<size_t>(m_nSize) + 1];
	
	for (int i = 0; i < nIndex; i++)
		dTemp[i] = m_pData[i];

	dTemp[nIndex] = dValue;

	for (int i = nIndex; i < m_nSize; i++)
		dTemp[i + 1] = m_pData[i];

	delete[] m_pData;
	m_pData = dTemp;
	m_nSize++;

}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {

	Free();

	m_nSize = arr.m_nSize;
	m_pData = new double(arr.m_nSize);
	for (int i = 0; i < arr.m_nSize; i++)
		m_pData[i] = arr.m_pData[i];

	return *this;
}

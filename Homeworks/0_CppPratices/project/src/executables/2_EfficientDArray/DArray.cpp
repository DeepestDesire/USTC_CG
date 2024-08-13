// implementation of class DArray
#include "DArray.h"
#include "cassert"
#include "iostream"
using namespace std;

// default constructor
DArray::DArray()
{
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) : m_pData(new double[nSize]), m_nSize(nSize), m_nMax(nSize)
{
	assert(nSize >= 0);
	for (int i = 0; i < nSize; i++)
		m_pData[i] = dValue;
}

DArray::DArray(const DArray& arr) : m_pData(new double[arr.m_nSize]), m_nSize(arr.m_nSize), m_nMax(arr.m_nSize)
{
	for (int i = 0; i < m_nSize; i++)
		m_pData[i] = arr.m_pData[i];
}

// deconstructor
DArray::~DArray()
{
	Free();
}

// display the elements of the array
void DArray::Print() const
{
	cout << endl;
	cout << "=== Pint function ===" << this << endl;
	cout << "this ptr is " << this << endl;
	cout << "size is " << m_nSize << ", max size is " << m_nMax << endl;
	cout << "value is: ";
	for (int i = 0; i < m_nSize; i++)
		cout << m_pData[i] << ", ";
	cout << endl;
}

// initilize the array
void DArray::Init()
{
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// free the array
void DArray::Free()
{
	delete[] m_pData;
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// get the size of the array
int DArray::GetSize() const
{
	return m_nSize; // you should return a correct value
}

void DArray::Reserve(int nSize)
{
	if (nSize <= m_nMax)
		return;

	while (m_nMax < nSize)
		m_nMax = m_nMax == 0 ? 1 : m_nMax * 2;

	double* pData = new double[m_nMax];
	memcpy(pData, m_pData, m_nSize * sizeof(double)); // memory copy funcation;

	delete[] m_pData;
	m_pData = pData;
}

// set the size of the array
void DArray::SetSize(int nSize)
{
	assert(nSize >= 0);
	if (nSize == m_nSize)
		return;

	Reserve(nSize);

	for (int i = m_nSize; i < m_nMax; i++)
		m_pData[i] = 0;
	m_nSize = nSize;

}

// get an element at an index
const double& DArray::GetAt(int nIndex) const
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// set the value of an element
void DArray::SetAt(int nIndex, double dValue)
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
double& DArray::operator[](int nIndex)
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; // you should return a correct value
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const
{
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex]; // you should return a correct value
}

// add a new element at the end of the array
void DArray::PushBack(double dValue)
{
	Reserve(m_nSize + 1);
	m_nSize++;
	m_pData[m_nSize - 1] = dValue;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex)
{
	assert(nIndex >= 0 && nIndex < m_nSize);

	for (int i = nIndex + 1; i < m_nSize; i++)
		m_pData[i - 1] = m_pData[i];
	m_pData[m_nSize - 1] = 0;
	// SetSize(m_nSize - 1);
	m_nSize--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue)
{
	assert(nIndex >= 0 && nIndex <= m_nSize);
	Reserve(m_nSize + 1);
	m_nSize++;
	for (int i = m_nSize; i > nIndex + 1; i--)
		m_pData[i - 1] = m_pData[i - 2];

	m_pData[nIndex] = dValue;
}

// overload operator '='
DArray& DArray::operator=(const DArray& arr)
{
	Reserve(arr.m_nSize);
	m_nSize = arr.m_nSize;
	memcpy(m_pData, arr.m_pData, sizeof(double) * arr.m_nSize);

	return *this;
}

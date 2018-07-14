// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#include <stdio.h> 
#include "money.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <stdexcept>
#include <math.h>
#include <ctgmath>
#include <sstream>
#include <fstream>


using namespace std;

/*****************************************************************************/

// TODO ...




bool Money::isValid( int _cent) const
{
	if (_cent < 0 || _cent > 99)
	{
		return false;
	}
	else /*if (m_Cent >= "0" && m_Cent <= "99")*/
	{
		return true;
	}
}
Money::Money() {

	m_Dollar = 0;
	m_Cent = 0;
}
Money::Money(int dollar, int cent) {
	if (!isValid(cent))
		throw std::logic_error("Invalid cents");

	m_Dollar = dollar;
	m_Cent = cent;

}
Money::Money(std::string str)
{
	int m_Dollar, m_Cent;
	char symbol;
	//std::string strNum("10.15");
	const char * c_str = str.c_str();

	int nMatched = sscanf(c_str, "%d%c%d",&m_Dollar, &symbol, &m_Cent);
	if (nMatched != 3 || symbol != '.')
		throw std::logic_error("Incorrect money format");

	if (m_Cent < 0 || m_Cent > 99)
		throw std::logic_error("Invalid cents");
	this->m_Dollar = m_Dollar;
	this->m_Cent = m_Cent;
}

//Money::Money(char * str, char _symbol)
//{
//	char sym1;
//	int nMatched = sscanf(str, "%d%c%d", &m_Dollar, &sym1, &m_Cent);
//	if (nMatched != 2 || sym1 != _symbol)
//		throw std::logic_error("Incorrect money format");
//}
Money::Money(long double number) 
{
	long double fractpart, intPart;
	fractpart = modf(number, &intPart);
	m_Dollar = intPart;
	m_Cent = (fractpart*100);
	if (m_Dollar < 0.0)
		m_Cent = m_Cent*(-1);
	m_Cent += 0.5;
}

int Money::getDollars()const
{
	//int value = this->m_Dollar;
	return m_Dollar;
}
int Money::getCents()const
{
	//int value = this->m_Cent;
	return m_Cent;
}

const char * Money::asString()
{
	/*char buff[30];
	int count = sprintf(buff, "%d.%d", m_Dollar, m_Cent);
	cout << buff << endl;
	return  buff;*/
	
	/*static char tempBuf[6];
	sprintf(tempBuf, "%d.%d", m_Dollar, m_Cent);
	return tempBuf;*/
	ostringstream ss;
	ss << this->m_Dollar << ".";
	if (m_Cent < 10)
		ss << "0";
	ss << m_Cent;
	char * cstr = new char[ss.str().length() + 1];
	strcpy(cstr, ss.str().c_str());

	cout << cstr << endl;
	return cstr;
}

	

	

bool Money::operator == (Money m) const {

	return m_Dollar == m.getDollars() &&
		   m_Cent == m.getCents();
	
}
bool Money::operator != (Money m) const {
	
	return !(*this == m);
}
bool Money::operator < (Money m) const
{
	if (m_Dollar < m.getDollars())
	{
		return true;
	}
	else if (m_Dollar == m.getDollars())
	{
		if (m_Cent < m.getCents())

			return true;

		else if (m_Dollar == m.getDollars() && m_Cent == m.getCents())

			return false;/*m_Dollar == m.getDollars() &&
				          m_Cent == m.getCents(); */
	}
	return false;
}
	
bool Money::operator > (Money m) const {
	return m < *this;
}
bool Money::operator <= (Money m) const {
	
	return ( * this< m) || (*this == m);
}
bool Money::operator >= (Money m) const {
	return (m < *this) || (*this == m);
}

Money Money::operator + (Money m) const {
	//Money result = *this;
	//result += m;
	//return result;
	Money result;
	result.m_Dollar = m_Dollar + m.getDollars();
	result.m_Cent = m_Cent + m.getCents();
	return result;
}

Money Money::operator * (Money m) const {
	Money result = *this;
	result *= m;
	return result;
	/*return m_Dollar * m.getDollars() +
	       m_Cent * m.getCents();*/

}
Money Money::operator / (Money m) const {
	return m_Dollar / m.getDollars() +
		m_Cent / m.getCents();
}

Money & Money::operator += (Money m) {
	m_Dollar += m.getDollars();
	m_Cent += m.getCents();
	return *this;
}
Money Money::operator - (Money m) const {
	//return Money(*this) -= m;
	//Money result = *this;
	//result -= m;
	//return result;

	//Money result(m_Dollar - m.getDollars();
	//	m_Cent - m.getCents());
	//return result;

	Money result;
	Money res;
	result.m_Dollar = this->m_Dollar - m.getDollars();
		result.m_Cent =  this->m_Cent - m.getCents() ;
		
		if (result.m_Cent < 0 && result.m_Dollar>0)
		res = result.m_Dollar + (result.m_Cent*0.01);
		return res;
		
	//	
	//return result;

	

	/*Money result(m_Dollar - m.getDollars() +
		m_Cent - m.getCents());
	return result;*/
	//return(m_Dollar - m.getDollars(),
	//	m_Cent - m.getCents());
	//
}
Money & Money::operator -= (Money m) {
	/**this = *this - m;
	return *this;*/

	/*m_Dollar += m.getDollars();
	m_Cent += m.getCents();
	return *this;*/

	Money temp = *this - m;
	*this = temp;
	return *this;
}
Money & Money::operator /= (Money m) {
	Money result = *this;
	result /= m;
	return result;
}
Money & Money::operator *= (Money m) {
	m_Dollar *= m.getDollars();
	m_Cent *= m.getCents();
	return *this;
	/*Money result = *this;
	result *= m;
	return result;*/
}

Money operator "" _USD(long double) {
	return Money();
}


/*****************************************************************************/

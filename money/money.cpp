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
#include <cmath>

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

	m_Dollar = 0.0;
	m_Cent = 0.0;
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

Money::Money(long double number) 
{   
	long double fractpart, intPart;
	fractpart = modf(number, &intPart);
	m_Dollar = intPart; 
	m_Cent = (0.2+(fractpart*100)) ;
	if (m_Dollar < 0.0)
	{
		m_Cent = m_Cent * (-1);
		m_Cent += 0.5;
	}
}

int Money::getDollars()const
{
	int value = this->m_Dollar;
	return this->m_Dollar;
}
int Money::getCents()const
{
	int value = this->m_Cent;
	return value;
}

const char * Money::asString()
{
	ostringstream ss;
	ss << this->m_Dollar << ".";

	if (m_Cent < 10)
	{
		ss << "0";
	    ss << m_Cent;
    }
	else
	{
		int cent;
		cent = static_cast<int>(m_Cent);
		ss << cent;
	}
	//cout << cstr << endl;
	char * cstr = new char[ss.str().length() + 1];
	strcpy(cstr, ss.str().c_str());
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
	Money result;
	result.m_Dollar = m_Dollar + m.getDollars();
	result.m_Cent = m_Cent + m.getCents();
	return result;
}

Money Money::operator * (int m) const {
	long double dollar, cent, res;
	dollar = m_Dollar;
	cent = m_Cent;
	res = (((dollar + (cent / 100)) * 100)*m)/100;
	cent = std::modf(res, &dollar);
	cent = (cent * 100) + 0.5;

	return Money(dollar, cent); 
}
	
Money Money::operator * (Money m) const {
	Money result = *this;
	result *= m;
	return result;

}
Money Money::operator / (int m) const {
	long double dollar, cent, res;
	dollar = m_Dollar;
	cent = m_Cent;
	res = (((dollar + (cent / 100)) * 100) / m) / 100;
	if (m == 0)
		throw std::logic_error("Division by zero");
	cent = std::modf(res, &dollar);
	cent = (cent * 100) + 0.5;

	return Money(dollar, cent);
}

Money & Money::operator += (Money m) {
	m_Dollar += m.getDollars();
	m_Cent += m.getCents();
	return *this;
}
Money Money::operator - (Money m) const {

	int dollar = this->m_Dollar;
	int cent = this->m_Cent;
	if (this->m_Cent < m.getCents()) {
		if (this->m_Dollar < m.getDollars() && this->m_Cent < m.getCents())
		{
			dollar = dollar - m.getDollars();
			cent = cent - m.getCents();
			cent = cent * (-1);
			return Money(dollar, cent);
		}

		dollar -= 1;
		cent += 100;
	}
	dollar = dollar - m.getDollars();
	cent = cent - m.getCents();
	return Money(dollar, cent);
}
	
Money & Money::operator -= (Money m) {
	Money temp = *this - m;
	*this = temp;
	return *this;
}
Money & Money::operator /= (Money m) {
	long double dollar, cent, MoneyBefore;
	dollar = m_Dollar;
	cent = m_Cent;
	if (dollar == 0)
	{
		MoneyBefore = ((cent * 100) / m.getDollars())/1000;
		if (m.getDollars() == 0)
			throw std::logic_error("Division by zero");
		cent = std::modf(MoneyBefore, &dollar);
		cent = (cent * 10);
		m_Cent = cent;
		m_Dollar = dollar;
		return *this;

	}
	MoneyBefore = (((dollar + (cent / 100)) * 100) / m.getDollars()) / 100;
	if (m.getDollars() == 0)
		throw std::logic_error("Division by zero");
	cent = std::modf(MoneyBefore, &dollar);
	cent = (cent * 100)+ 0.5;
	m_Cent = cent;
	m_Dollar = dollar;
	return *this;
	
}
Money & Money::operator *= (Money m) {

	long double dollar, cent;
	dollar = m_Dollar;
	cent = m_Cent;
	long double MoneyBefore = (m.getDollars() *(cent + 1000)) / 100;
	cent = std::modf(MoneyBefore, &dollar);
	cent = cent * 100;
	m_Cent = cent;
	m_Dollar = dollar;
	return *this;
}
    Money operator "" _USD(long double money) {
		return Money(money);
}


/*****************************************************************************/

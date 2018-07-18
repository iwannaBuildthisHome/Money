// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MONEY_HPP_
#define _MONEY_HPP_

/*****************************************************************************/
#include <string>
#include <stdexcept>
#include <cmath>
#include <math.h>

class Money
{
private:
	long double m_Dollar, m_Cent;
	std::string moneyStr;
	bool isValid( int _cent) const;
	
public:
	Money();
	Money(int dollar, int cent);
	Money(std::string str);
	Money(long double number);

	int getDollars() const;
	int getCents() const;

	const char * Money::asString();

	bool operator == (Money m) const;
	bool operator != (Money m) const;
	bool operator < (Money m) const;
	bool operator > (Money m) const;
	bool operator <= (Money m) const;
	bool operator >= (Money m) const;

	Money operator + (Money m) const;
	Money operator - (Money m) const;
	Money operator * (Money m) const;
	Money Money::operator * (int m) const;
	Money Money::operator / (int m) const;

	Money & operator += (Money m);
	Money & operator -= (Money m);
	Money & operator /= (Money m);
	Money & operator *= (Money m);

	friend Money operator "" _USD(long double);
/*-----------------------------------------------------------------*/

	// TODO ...

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _MONEY_HPP_

#include <iostream>                                                                   // Defines istream & ostream for IO
#include <string>                                                                     // STL string container
#include <algorithm>                                                                  // STL algorithm
#include <cmath>
#include <cstdio>
using namespace std;
// CONSTRUCTORS
// ------------
Fraction::Fraction(int x, int y)                                                      // Uses default parameters. Overloads to
								                                                      // Fraction(int, int); 
								                                                      // Fraction(int);	
								                                                      // Fraction(); 
{
	this->iNumerator_=x;
	this->uiDenominator_=y;
	this->Normalize();
}
// Constructor for explicit Conversion
Fraction::Fraction(double d)                                                          // explicit double to Fraction conversion
{
	int i=(int)(d*Fraction::precision()),j=Fraction::precision();
	this->iNumerator_=i;
	this->uiDenominator_=j;
	this->Normalize();
}
// Copy Constructor
Fraction::Fraction(const Fraction& f)                                                // Param cannot be changed (const)
{
	this->iNumerator_=f.iNumerator_;
	this->uiDenominator_=f.uiDenominator_;
}
Fraction::~Fraction()                                                                // No virtual destructor needed
{

}
// BASIC ASSIGNEMENT OPERATOR
// --------------------------
Fraction& Fraction::operator=(const Fraction& f)                                     
{
	this->iNumerator_=f.iNumerator_;
	this->uiDenominator_=f.uiDenominator_;
	return *this;
}

// UNARY ARITHMETIC OPERATORS
// --------------------------
Fraction Fraction::operator-()                                                      // Operand 'this' implicit
{
	Fraction t=(*this);                                     
	t.iNumerator_=-this->iNumerator_;
	return t;
}
Fraction Fraction::operator+()                                                      
{
	return *this;
}
Fraction& Fraction::operator--()                                                    // Pre-decrement. Dividendo. p/q <-- p/q - 1
{
	this->iNumerator_-=this->uiDenominator_;
	return *this;
}
Fraction& Fraction::operator++()                                                    // Pre-increment. Componendo. p/q <-- p/q + 1
{
	this->iNumerator_+=this->uiDenominator_;
	return *this;
}
Fraction Fraction::operator--(int x)                                                // Post-decrement. Lazy Dividendo. p/q <-- p/q - 1. Returns old p/q
{
	Fraction f=*this;
	this->iNumerator_-=this->uiDenominator_;
	return f;
}
Fraction Fraction::operator++(int x)                                                // Post-increment. Lazy Componendo. p/q <-- p/q + 1. Returns old p/q
{
	Fraction f=*this;
	this->iNumerator_+=this->uiDenominator_;
	return f;
}
// BINARY ARITHMETIC OPERATORS USING FRIEND FUNCTIONS
// --------------------------------------------------
Fraction operator+(const Fraction& f1, const Fraction& f2)                          
{
	Fraction f(f1.iNumerator_*f2.uiDenominator_+f1.uiDenominator_*f2.iNumerator_,f1.uiDenominator_*f2.uiDenominator_);
	return f;
}
Fraction operator-(const Fraction& f1, const Fraction& f2)
{
	Fraction f(f1.iNumerator_*f2.uiDenominator_-f1.uiDenominator_*f2.iNumerator_,f1.uiDenominator_*f2.uiDenominator_);
	return f;
}
Fraction operator*(const Fraction& f1, const Fraction& f2)
{
	Fraction f(f1.iNumerator_*f2.iNumerator_,f1.uiDenominator_*f2.uiDenominator_);
	return f;
}
Fraction operator/(const Fraction& f1, const Fraction& f2)
{
	Fraction f(f1.iNumerator_*f2.uiDenominator_,f1.uiDenominator_*f2.iNumerator_);
	return f;	
}
Fraction operator%(const Fraction& f1, const Fraction& f2)
{
	if(f1.iNumerator_<0 || f2.iNumerator_<0)
	{
		Fraction r,p1,p2;
		p1=f1;p2=f2;
		Fraction f(-1,1);
		r=p1;
		while((p1<f*p2))
		{
			r=p1-f*p2;
			f.iNumerator_--;
		}
		r=p1-f*p2;
		r.Normalize();
		return r;
	}
	else
	{
		Fraction r,p1,p2;
		p1=f1;p2=f2;
		Fraction f(1,1);
		r=p1;
		while(p1>=f*p2)
		{
			r=p1-f*p2;
			f.iNumerator_++;
		}	
		r.Normalize();
		return r;
	}
}
// BINARY RELATIONAL OPERATORS
// ---------------------------
bool Fraction::operator==(const Fraction& f)
{
	if(this->iNumerator_==f.iNumerator_ && this->uiDenominator_==f.uiDenominator_)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Fraction::operator!=(const Fraction& f)
{
	return (!((*this)==f));
}
bool Fraction::operator<(const Fraction& f)
{
	if(this->iNumerator_*f.uiDenominator_<this->uiDenominator_*f.iNumerator_)
		return true;
	else
		return false;
}
bool Fraction::operator<=(const Fraction& f)
{
	if(this->iNumerator_*f.uiDenominator_<=this->uiDenominator_*f.iNumerator_)
		return true;
	else
		return false;	
}
bool Fraction::operator>(const Fraction& f)
{
	if(this->iNumerator_*f.uiDenominator_>this->uiDenominator_*f.iNumerator_)
		return true;
	else
		return false;		
}
bool Fraction::operator>=(const Fraction& f)
{
	if(this->iNumerator_*f.uiDenominator_>=this->uiDenominator_*f.iNumerator_)
		return true;
	else
		return false;		
}
// ADVANCED ASSIGNEMENT OPERATORS
// ------------------------------
Fraction& Fraction::operator+=(const Fraction& f)
{
	(*this)=(*this)+f;
	return *this;
}
Fraction& Fraction::operator-=(const Fraction& f)
{
	(*this)=(*this)-f;
	return *this;
}
Fraction& Fraction::operator*=(const Fraction& f)
{
	(*this)=(*this)*f;
	return *this;
}
Fraction& Fraction::operator/=(const Fraction& f)
{
	(*this)=(*this)/f;
	return *this;
}
Fraction& Fraction::operator%=(const Fraction& f)
{
	(*this)=(*this)%f;
	return *this;
}
// SPECIAL OPERATORS
// -----------------
Fraction Fraction::operator!()                                                                      // Inverts a fraction. !(p/q) = q/p
{
	int temp;
	temp=this->iNumerator_;
	this->iNumerator_=this->uiDenominator_;
	this->uiDenominator_=temp;
	if(this->uiDenominator_<0)
	{
		this->uiDenominator_*=-1;
		this->iNumerator_*=-1;
	}
	return *this;
}
// BASIC I/O using FRIEND FUNCTIONS
// --------------------------------
ostream& operator<<(ostream& output,const Fraction& f)
{
	output<<f.iNumerator_<<"/"<<f.uiDenominator_;
	return output;
}
istream& operator>>(istream& input, Fraction& f)                                    //Input must be of type Fraction
{
	f.uiDenominator_=1;
	input>>f.iNumerator_;
	scanf("/");
	input>>f.uiDenominator_;
	return input;
}
// CONSTANTS OF DATATYPE
// ---------------------
const Fraction	Fraction::sc_fUnity=Fraction(1,1);
const Fraction	Fraction::sc_fZero=Fraction(0,1);
int Fraction::gcd(int x, int y)
{
	int i=min(x,y);
	while(!(x%i==0 && y%i==0))                                                      //calculates gcd
	{
		i--;
	}
	return i;
}
int Fraction::lcm(int x, int y)
{
	return x*y/gcd(x,y);
}
// Normalizes a fraction
Fraction& Fraction::Normalize()
{
	int x=this->iNumerator_;
	int y=this->uiDenominator_;
	int i=min(abs(x),abs(y)),flag=0;
	if(x==0)
	{
		this->iNumerator_=0;
		this->uiDenominator_=1;
		return *this;
	}
	if(x<0 && y>0 || x>0 && y<0)
	{
		flag=1;
		if(x<0)
			x*=-1;
		else
			y*=-1;
	}
	else if(x<0 && y<0)
	{
		x*=-1;
		y*=-1;
	}
	while(i>0)
	{
		if(x%i==0 && y%i==0)
		{
			x=x/i;
			y=y/i;
		}
		i--;
	}
	this->iNumerator_=x;
	if(flag==1)
		this->iNumerator_=-x;
	this->uiDenominator_=y;
}

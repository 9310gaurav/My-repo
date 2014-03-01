#include <iostream>                                        // Defines istream & ostream for IO
#include <vector>                                          // vector container of STL
#include <algorithm>                                    
using namespace std;

// CONSTRUCTOR
	// -----------
template<class T,class U> Poly<T,U>::Poly(unsigned int x)	// Uses default parameters. Overloads to
{                               // Poly(...); 
	this->degree_=x;
	this->coefficients_.resize(x+1);
}
// Copy Constructor 
template<class T,class U> Poly<T,U>::Poly(const Poly<T,U>& p)	   // Param cannot be changed (const)						
{
	this->degree_=p.degree_;
	this->coefficients_=p.coefficients_;
}

// BASIC ASSIGNEMENT OPERATOR
	// --------------------------
template<class T,class U> Poly<T,U>& Poly<T,U>::operator=(const Poly& p)
{
	this->degree_=p.degree_;
	this->coefficients_=p.coefficients_;
	return *this;
}

// UNARY ARITHMETIC OPERATORS
	// --------------------------
template<class T,class U> Poly<T,U> Poly<T,U>::operator-()		// Operand 'this' implicit
{
	int i;
	Poly<T,U> p=*this;
	for(i=0;i<this->coefficients_.size();i++)
	{
		p.coefficients_[i]*=-1;
	}
	return p;
}
template<class T,class U> Poly<T,U> Poly<T,U>::operator+()
{
	return *this;
}

// BINARY ARITHMETIC OPERATORS
	// ---------------------------
template<class T,class U> Poly<T,U> Poly<T,U>::operator+(const Poly& p)
{
	Poly<T,U> q;
	int a=max(this->coefficients_.size(),p.coefficients_.size());
	int b=min(this->coefficients_.size(),p.coefficients_.size());
	q.degree_=a-1;
	q.coefficients_.resize(a);
	int i=0;
	for(i=0;i<b;i++)
	{
		q.coefficients_[i]=this->coefficients_[i]+p.coefficients_[i];
	}
	if(this->coefficients_.size()==a)
	{
		while(i<a)
		{
			q.coefficients_[i]=this->coefficients_[i];
			i++;
		}
	}
	else
	{
		while(i<a)
		{
			q.coefficients_[i]=p.coefficients_[i];
			i++;
		}	
	}
	return q;
}
template<class T,class U> Poly<T,U> Poly<T,U>::operator-(const Poly& p) 
{
	Poly<T,U> q;
	int a=max(this->coefficients_.size(),p.coefficients_.size());
	int b=min(this->coefficients_.size(),p.coefficients_.size());
	q.degree_=a-1;
	q.coefficients_.resize(a);
	int i=0;
	for(i=0;i<b;i++)
	{
		q.coefficients_[i]=this->coefficients_[i]-p.coefficients_[i];
	}
	if(this->coefficients_.size()==a)
	{
		while(i<a)
		{
			q.coefficients_[i]=this->coefficients_[i];
			i++;
		}
	}
	else
	{
		while(i<a)
		{
			q.coefficients_[i]=-p.coefficients_[i];
			i++;
		}	
	}
	return q;
}

// ADVANCED ASSIGNEMENT OPERATORS
	// ------------------------------
template<class T,class U> Poly<T,U>& Poly<T,U>::operator+=(const Poly& p)
{
	Poly q=(*this)+p;
	(*this)=q;
	return *this;
}
template<class T,class U> Poly<T,U>& Poly<T,U>::operator-=(const Poly& p)
{
	Poly q=(*this)-p;
	(*this)=q;
	return *this; 
}
// BASIC I/O using FRIEND FUNCTIONS
// --------------------------------
template<class T1, class U1> ostream& operator<< (ostream& os,const Poly<T1, U1>& p)
{
	int i;
	for(i=1;i<=p.degree_+1;i++)
	{
		if(i==1)
		{
			os<<p.coefficients_[0];
		}
		else
		{
			os<<"+"<<p.coefficients_[i-1]<<"x^"<<i-1;
		}		
	}
	return os;
}
template<class T1, class U1> istream& operator>> (istream& is, Poly<T1, U1>& p)
{
	cout<<"Enter degree"<<endl;
	is>>p.degree_;
	p.coefficients_.resize(p.degree_+1);
	cout<<"Enter coefficients:"<<endl;
	int i;
	for(i=0;i<p.degree_+1;i++)
		is>>p.coefficients_[i];
	return is;
}
template<class T,class U> T Poly<T,U>::Evaluate(const T& x)                                     // Evaluates the polynomial - use Horner's Rule
{
	T result(0);
	int i;
	for(i=this->degree_;i>=0;i--)
	{
		result=result*x+coefficients_[i];
	}
	return result;
}

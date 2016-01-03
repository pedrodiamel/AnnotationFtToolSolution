

#include "stdafx.h"
#include "Vector.h"

using namespace gutl;

//assignment
const CVector& CVector::operator=(const CVector& vec){
		
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return *this;	
}



const CVector& CVector::operator=(const Vector4& vec){
		
	x = vec.x;
	y = vec.y;
	z = vec.z;

	return *this;	
}



//equality
const bool CVector::operator==(const CVector& vec)const{
	
	return ((x==vec.x) && (y==vec.y) && (z==vec.z));	
	
}

//inequality
const bool CVector::operator!=(const CVector& vec)const{
	
	return !(*this == vec);

}

//addition
const CVector CVector::operator+(const CVector& vec)const{
	
	return CVector(x + vec.x, y + vec.y, z + vec.z);

}

	
//mod
const CVector CVector::operator+()const{
	
	return CVector(*this);
}
	
	
	
//increment
const CVector& CVector::operator+=(const CVector& vec){
	
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
	
}	

//subtration
const CVector CVector::operator-(const CVector& vec)const{
	
	return CVector(x - vec.x, y - vec.y, z - vec.z);

}


//not
const CVector CVector::operator-()const{
	
	return CVector( -x, -y, -z);
}


//decrement
const CVector& CVector::operator-=(const CVector& vec){
	
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
	
}


//scalar multiply
const CVector& CVector::operator*=(const scalar_t &s){
	
	x *= s;
	y *= s;
	z *= s;

	return *this;
	
}


//scalar division 
const CVector& CVector::operator/=(const scalar_t &s){
	
	x /= s;
	y /= s;
	z /= s;

	return *this;
	
}


//post multiply by scalar
const CVector CVector::operator*(const scalar_t &s)const{
	
	return CVector(x*s, y*s, z*s);
	
}		
	
	

//divide by scalar
const CVector CVector::operator/(scalar_t s)const{
	
	s=1/s;
	return CVector(x*s, y*s, z*s);
	
}

	
//cross product
const CVector CVector::CrossProduct(const CVector &vec)const{
	
	return CVector( y*vec.z - z*vec.y, x*vec.z - z*vec.x, x*vec.y - y*vec.x );
}
	
	
//cross product (^)
const CVector CVector::operator^(const CVector &vec)const{
	
	return CVector( y*vec.z - z*vec.y, x*vec.z - z*vec.x, x*vec.y - y*vec.x );
}

	
//dot product
const scalar_t CVector::DotProduct(const CVector &vec) const{
	
	return (scalar_t) x*vec.x + y*vec.y + z*vec.z; 
	
} 
	
//dot product (%)
const scalar_t CVector::operator%(const CVector &vec) const{
	
	return (scalar_t) x*vec.x + y*vec.y + z*vec.z; 
	
} 

//length the vector
const scalar_t CVector::Length() const{
	
	scalar_t length = (scalar_t)sqrt((double)SQUARE(x) + SQUARE(y) + SQUARE(z) );
	return (scalar_t)((length != 0.0)?length:1.0);
	
} 


//return unit vector
const CVector CVector::UnitVector() const {
	
	return *this/Length();
	
}


//normalice this vector
void CVector::Normalice(){
	
	*this/=Length();
}


//vector length operator (!)
const scalar_t CVector::operator!() const{
	
	return sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z));
} 


//return this vector with specified length 
const CVector CVector::operator|(const scalar_t l) const{
	
	return *this * (l/!*this);
}

//set length of vector equal to length
const CVector CVector::operator|=(const float l) {
	
	return *this = *this | l;
}



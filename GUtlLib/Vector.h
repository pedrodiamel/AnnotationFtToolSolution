#ifndef _GUTL_VECTOR_H
#define _GUTL_VECTOR_H


#include <math.h>
#include "Type.h"


namespace gutl{

	/*!
	 * \class	CVector
	 *
	 * \brief	A vector.
	 *
	 * \author	Pedro
	 * \date	30/12/2015
	 */

	class CVector
	{

	public:
	
		union{ // coordenadas x, y, z
			struct{
				scalar_t x; 
				scalar_t y;
				scalar_t z;
			};
			scalar_t v[3];
		};

	public:
	
		CVector():x(0.0f),y(0.0),z(0.0){}
		CVector(const CVector &v):x(v.x),y(v.y),z(v.z){}
		CVector(scalar_t xx, scalar_t yy, scalar_t zz):x(xx),y(yy),z(zz){}		
		CVector(const Vector4 vet){  x = vet.x; y = vet.y; 	z = vet.z; 	}
		~CVector(void){}

		//operators
		operator Vector4(){ 
		
			Vector4 vet;
			vet.x = x; 	vet.y = y; 	vet.z = z; 	vet.w = 1.0;
			return vet;
	
		}

		//assignment
		const CVector& operator=(const CVector& );
		const CVector& operator=(const Vector4& );
		
		// interface
		template <class Interface> 
		inline void CopyTo(Interface &vect){
		vect.x = x; vect.y = y; vect.z = z;
		} 

	
		//equality
		const bool operator==(const CVector& )const;	
	
		//inequality
		const bool operator!=(const CVector& vec)const;
	
		//addition
		const CVector operator+(const CVector& vec)const;
		
		//mod
		const CVector operator+()const;
		
		//increment
		const CVector& operator+=(const CVector& vec);

		//subtration
		const CVector operator-(const CVector& vec)const;
	
		//not
		const CVector operator-()const;

		//decrement
		const CVector& operator-=(const CVector& vec);

		//scalar multiply
		const CVector& operator*=(const scalar_t &s);
	
		//scalar division 
		const CVector& operator/=(const scalar_t &s);


		//post multiply by scalar
		const CVector operator*(const scalar_t &s)const;	
	
	
		//pre multiply by scalar
		friend inline const CVector operator* (const scalar_t &s, const CVector &vec){ 	return vec*s; 	}


		//divide by scalar
		const CVector operator/(scalar_t s)const;

	
		//cross product
		const CVector CrossProduct(const CVector &vec)const;
	
	
		//cross product (^)
		const CVector operator^(const CVector &vec)const;

	
		//dot product
		const scalar_t DotProduct(const CVector &vec) const; 
	
		//dot product (%)
		const scalar_t operator%(const CVector &vec) const; 

		//length the vector
		const scalar_t Length() const;


		//return unit vector
		const CVector UnitVector() const ;

		//normalice this vector
		void Normalice();


		//vector length operator (!)
		const scalar_t operator!() const;


		//return this vector with specified length 
		const CVector operator|(const scalar_t l) const;

		//set length of vector equal to length
		const CVector operator|=(const float l);


		//return angle between this vector and a normal vector (inline)
		const float inline CVector::Angle(const CVector &n) const{ 	return acosf( *this % n ); 	}
				

		//reflect this vector about a normal vector (inline)
		const CVector inline Reflection(const CVector& n) const
		{
			const CVector vec(*this | 1); // get unit vector
			return (vec - n * 2.0 * (vec % n)) * !*this;
		}


		//iterator		
		class Cref{

			friend class CVector;
			CVector &v;
			int i;
			Cref(CVector &vv, int ii):v(vv),i(ii){}

			public:
			operator scalar_t(){ return v.v[i];}
			void operator=(scalar_t c){ v.v[i] = c;}
	
		};
	
		Cref operator[](int i){ check(i); return Cref(*this,i); }
		const scalar_t& operator[](int i)const{ check(i); return v[i]; }

		class Range{};
		void check(int i)const{ if(0>i || i>2) throw Range();}
	

	};

}

#endif //_NUIVECTOR_H
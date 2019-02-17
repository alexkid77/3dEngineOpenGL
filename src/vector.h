/****************************************************************************/
/** \file  vector.h
    \brief Contains the CVector class

	\author Kevin Hawkins
*****************************************************************************/

#ifndef __VECTOR_H
#define __VECTOR_H

#include <math.h>


#define PI		(3.14159265359f)
#define DEG2RAD(a)	(PI/180*(a))
#define RAD2DEG(a)	(180/PI*(a))

typedef float scalar_t;

/****************************************************************************/
/** \class CVector
	\brief This class represents a vector. 

    Some operators of the CVector class based on
    operators of the CVector class by Bas Kuenen.
    Copyright (c) 2000 Bas Kuenen. All Rights Reserved.
    homepage: baskuenen.cfxweb.net
*****************************************************************************/
class CVector
{
public:

     union
     {
        struct
        {
            scalar_t x;
            scalar_t y;
            scalar_t z;    // x,y,z coordinates
        };
        scalar_t v[3];
     };

     CVector(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b), z(c) {}
     CVector(const CVector &vec) : x(vec.x), y(vec.y), z(vec.z) {}

	 // vector index
	 scalar_t &operator[](const long idx);

     // vector assignment
     const CVector &operator=(const CVector &vec);

     // vecector equality
     const bool operator==(const CVector &vec) const;

     // vecector inequality
     const bool operator!=(const CVector &vec) const;

     // vector add
     const CVector operator+(const CVector &vec) const;

     // vector add (opposite of negation)
     const CVector operator+() const;

     // vector increment
     const CVector& operator+=(const CVector& vec);

     // vector subtraction
     const CVector operator-(const CVector& vec) const;
     
     // vector negation
     const CVector operator-() const;

     // vector decrement
     const CVector &operator-=(const CVector& vec);

     // scalar self-multiply
     const CVector &operator*=(const scalar_t &s);

     // scalar self-divecide
     const CVector &operator/=(const scalar_t &s);

     // post multiply by scalar
     const CVector operator*(const scalar_t &s) const;

     // pre multiply by scalar
     friend inline const CVector operator*(const scalar_t &s, const CVector &vec);

	 const CVector operator*(const CVector& vec) const;

    // divide by scalar
     const CVector operator/(scalar_t s) const;

     // cross product
     const CVector CrossProduct(const CVector &vec) const;

     // cross product
     const CVector operator^(const CVector &vec) const;

     // dot product
     const scalar_t DotProduct(const CVector &vec) const;

     // dot product
     const scalar_t operator%(const CVector &vec) const;

     // length of vector
     const scalar_t Length() const;

     // return the unit vector
     const CVector UnitVector() const;

     // normalize this vector
     void Normalize();

     const scalar_t operator!() const;

     // return vector with specified length
     const CVector operator | (const scalar_t length) const;

     // set length of vector equal to length
     const CVector& operator |= (const float length);

     /** \return angle between two vectors */
     inline const float Angle(const CVector& normal) const
	 {
    	return acosf(*this % normal);
	 }

     /** reflect this vector off surface with normal vector */
     inline const CVector Reflection(const CVector& normal) const
 	 {    
     	const CVector vec(*this | 1);     // normalize this vector
     	return (vec - normal * 2.0 * (vec % normal)) * !*this;
 	 }

     /** rotate angle degrees about a normal */
	 inline const CVector Rotate(const float angle, const CVector& normal) const
	 {	
	 	const float cosine = cosf(angle);
	 	const float sine = sinf(angle);

	 	return CVector(*this * cosine + ((normal * *this) * (1.0f - cosine)) * normal + (*this ^ normal) * sine);
	 }

};

#endif

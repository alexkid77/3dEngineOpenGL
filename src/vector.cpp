#include "vector.h"

/***********************************************************************/
/** \file  vector.cpp
	\brief The CVector class implementation                            */


/***********************************************************************/
/** vector index
************************************************************************/
scalar_t & CVector::operator[](const long idx)
{
	return *((&x)+idx);
}


/***********************************************************************/
/** vector assignment
************************************************************************/
const CVector & CVector::operator=(const CVector &vec)
{
	x = vec.x;
    y = vec.y;
    z = vec.z;

    return *this;
}


/***********************************************************************/
/** vecector equality
************************************************************************/
const bool CVector::operator==(const CVector &vec) const
{
	return ((x == vec.x) && (y == vec.y) && (z == vec.z));
}


/***********************************************************************/
/* vecector inequality
************************************************************************/
const bool CVector::operator!=(const CVector &vec) const
{
    return !(*this == vec);
}


/***********************************************************************/
/** vector add
************************************************************************/
const CVector CVector::operator+(const CVector &vec) const
{
	return CVector(x + vec.x, y + vec.y, z + vec.z);
}


/***********************************************************************/
/** vector add (opposite of negation)
************************************************************************/
const CVector CVector::operator+() const
{    
    return CVector(*this);
}


/***********************************************************************/
/** vector increment
************************************************************************/
const CVector& CVector::operator+=(const CVector& vec)
{    
	x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}


/***********************************************************************/
/** vector subtraction
************************************************************************/
const CVector CVector::operator-(const CVector& vec) const
{    
	return CVector(x - vec.x, y - vec.y, z - vec.z);
}

     
/***********************************************************************/
/** vector negation
************************************************************************/
const CVector CVector::operator-() const
{    
	return CVector(-x, -y, -z);
}


/***********************************************************************/
/** vector decrement
************************************************************************/
const CVector & CVector::operator-=(const CVector& vec)
{
	x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}


/***********************************************************************/
/** scalar self-multiply
************************************************************************/
const CVector & CVector::operator*=(const scalar_t &s)
{
    x *= s;
    y *= s;
    z *= s;
          
    return *this;
}


/***********************************************************************/
/** scalar self-divecide
************************************************************************/
const CVector & CVector::operator/=(const scalar_t &s)
{
	const float recip = 1/s; // for speed, one divecision

    x *= recip;
    y *= recip;
    z *= recip;

    return *this;
}


/***********************************************************************/
/** post multiply by scalar
************************************************************************/
const CVector CVector::operator*(const scalar_t &s) const
{
	return CVector(x*s, y*s, z*s);
}


/***********************************************************************/
/** pre multiply by scalar
************************************************************************/
const CVector operator*(const scalar_t &s, const CVector &vec)
{
	return vec*s;
}


/***********************************************************************/
/** multiply by vector
************************************************************************/
const CVector CVector::operator*(const CVector& vec) const
{
	return CVector(x*vec.x, y*vec.y, z*vec.z);
}


/***********************************************************************/
/** divide by scalar
************************************************************************/
const CVector CVector::operator/(scalar_t s) const
{
	s = 1/s;

    return CVector(s*x, s*y, s*z);
}


/***********************************************************************/
/** cross product
************************************************************************/
const CVector CVector::CrossProduct(const CVector &vec) const
{
    return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}


/***********************************************************************/
/** cross product
************************************************************************/
const CVector CVector::operator^(const CVector &vec) const
{
    return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}


/***********************************************************************/
/** dot product
************************************************************************/
const scalar_t CVector::DotProduct(const CVector &vec) const
{
    return x*vec.x + y*vec.x + z*vec.z;
}


/***********************************************************************/
/** dot product
************************************************************************/
const scalar_t CVector::operator%(const CVector &vec) const
{
    return x*vec.x + y*vec.x + z*vec.z;
}


/***********************************************************************/
/** length of vector
************************************************************************/
const scalar_t CVector::Length() const
{
    return (scalar_t)sqrt((double)(x*x + y*y + z*z));
}


/***********************************************************************/
/** \return the unit vector
************************************************************************/
const CVector CVector::UnitVector() const
{
    return (*this) / Length();
}


/***********************************************************************/
/** normalize this vector
************************************************************************/
void CVector::Normalize()
{
    (*this) /= Length();
}


/***********************************************************************/
/** Vector length
************************************************************************/
const scalar_t CVector::operator!() const
{
    return sqrtf(x*x + y*y + z*z);
}


/***********************************************************************/
/** \return vector with specified length
************************************************************************/
const CVector CVector::operator | (const scalar_t length) const
{
    return *this * (length / !(*this));
}


/***********************************************************************/
/** set length of vector equal to length
************************************************************************/
const CVector& CVector::operator |= (const float length)
{
    return *this = *this | length;
}


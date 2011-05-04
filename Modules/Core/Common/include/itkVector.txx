/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkVector_txx
#define __itkVector_txx

#include "vnl/vnl_math.h"
#include "vnl/vnl_vector.h"
#include "itkObject.h"
#include "itkNumericTraitsVectorPixel.h"

namespace itk
{
/**
 * Constructor to initialize entire vector to one value.
 */
template< class T, unsigned int TVectorDimension >
Vector< T, TVectorDimension >
::Vector(const ValueType & r)
{
  for ( typename BaseArray::Iterator i = BaseArray::Begin(); i != BaseArray::End(); ++i )
    {
    *i = r;
    }
}

template< class T, unsigned int TVectorDimension >
Vector< T, TVectorDimension > &
Vector< T, TVectorDimension >
::operator=(const ValueType r[TVectorDimension])
{
  BaseArray::operator=(r);
  return *this;
}

/**
 *
 */
template< class T, unsigned int TVectorDimension >
const typename Vector< T, TVectorDimension >::Self &
Vector< T, TVectorDimension >
::operator+=(const Self & vec)
{
  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    ( *this )[i] += vec[i];
    }
  return *this;
}

/**
 *
 */
template< class T, unsigned int TVectorDimension >
const typename Vector< T, TVectorDimension >::Self &
Vector< T, TVectorDimension >
::operator-=(const Self & vec)
{
  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    ( *this )[i] -= vec[i];
    }
  return *this;
}

/**
 * Returns a temporary copy of a vector
 */
template< class T, unsigned int TVectorDimension >
Vector< T, TVectorDimension >
Vector< T, TVectorDimension >
::operator-() const
{
  Self result;

  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    result[i] = -( *this )[i];
    }
  return result;
}

/**
 * Returns a temporary copy of a vector
 */
template< class T, unsigned int TVectorDimension >
Vector< T, TVectorDimension >
Vector< T, TVectorDimension >
::operator+(const Self & vec) const
{
  Self result;

  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    result[i] = ( *this )[i] + vec[i];
    }
  return result;
}

/**
 * Returns a temporary copy of a vector
 */
template< class T, unsigned int TVectorDimension >
Vector< T, TVectorDimension >
Vector< T, TVectorDimension >
::operator-(const Self & vec)  const
{
  Self result;

  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    result[i] = ( *this )[i] - vec[i];
    }
  return result;
}

/**
 * Returns vector's Squared Euclidean Norm
 */
template< class T, unsigned int TVectorDimension >
typename Vector< T, TVectorDimension >::RealValueType
Vector< T, TVectorDimension >
::GetSquaredNorm(void) const
{
  typename NumericTraits< RealValueType >::AccumulateType sum = NumericTraits< T >::Zero;
  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    const RealValueType value = ( *this )[i];
    sum += value * value;
    }
  return sum;
}

/**
 * Returns vector's Euclidean Norm
 */
template< class T, unsigned int TVectorDimension >
typename Vector< T, TVectorDimension >::RealValueType
Vector< T, TVectorDimension >
::GetNorm(void) const
{
  return RealValueType( vcl_sqrt( double( this->GetSquaredNorm() ) ) );
}

/**
 * Divide vector's components by vector's norm
 */
template< class T, unsigned int TVectorDimension >
void
Vector< T, TVectorDimension >
::Normalize(void)
{
  const RealValueType norm = this->GetNorm();

  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    ( *this )[i] = static_cast< T >( static_cast< RealValueType >( ( *this )[i] ) / norm );
    }
}

/**
 * Set a vnl_vector
 */
template< class T, unsigned int TVectorDimension >
void
Vector< T, TVectorDimension >
::Set_vnl_vector(const vnl_vector< T > & v)
{
  for ( unsigned int i = 0; i < v.size(); i++ )
    {
    ( *this )[i] = v(i);
    }
}

/**
 * Return a vnl_vector_ref
 */
template< class T, unsigned int TVectorDimension >
vnl_vector_ref< T >
Vector< T, TVectorDimension >
::Get_vnl_vector(void)
{
  return vnl_vector_ref< T >( TVectorDimension, this->GetDataPointer() );
}

/**
 * Return a vnl_vector const
 */
template< class T, unsigned int TVectorDimension >
vnl_vector< T >
Vector< T, TVectorDimension >
::Get_vnl_vector(void) const
{
  // Return a vector_ref<>.  This will be automatically converted to a
  // vnl_vector<>.  We have to use a const_cast<> which would normally
  // be prohibited in a const method, but it is safe to do here
  // because the cast to vnl_vector<> will ultimately copy the data.
  return vnl_vector_ref< T >( TVectorDimension,
                              const_cast< T * >( this->GetDataPointer() ) );
}

/**
 * Set a vnl_vector
 */
template< class T, unsigned int TVectorDimension >
void
Vector< T, TVectorDimension >
::SetVnlVector(const vnl_vector< T > & v)
{
  for ( unsigned int i = 0; i < v.size(); i++ )
    {
    ( *this )[i] = v(i);
    }
}

/**
 * Return a vnl_vector_ref
 */
template< class T, unsigned int TVectorDimension >
vnl_vector_ref< T >
Vector< T, TVectorDimension >
::GetVnlVector(void)
{
  return vnl_vector_ref< T >( TVectorDimension, this->GetDataPointer() );
}

/**
 * Return a vnl_vector const
 */
template< class T, unsigned int TVectorDimension >
vnl_vector< T >
Vector< T, TVectorDimension >
::GetVnlVector(void) const
{
  // Return a vector_ref<>.  This will be automatically converted to a
  // vnl_vector<>.  We have to use a const_cast<> which would normally
  // be prohibited in a const method, but it is safe to do here
  // because the cast to vnl_vector<> will ultimately copy the data.
  return vnl_vector_ref< T >( TVectorDimension,
                              const_cast< T * >( this->GetDataPointer() ) );
}

/**
 * Print content to an ostream
 */
template< class T, unsigned int TVectorDimension >
std::ostream &
operator<<(std::ostream & os, const Vector< T, TVectorDimension > & vct)
{
  os << "[";
  if ( TVectorDimension == 1 )
    {
    os << vct[0];
    }
  else
    {
    for ( unsigned int i = 0; i + 1 < TVectorDimension; i++ )
      {
      os <<  vct[i] << ", ";
      }
    os << vct[TVectorDimension - 1];
    }
  os << "]";
  return os;
}

/**
 * Read content from an istream
 */
template< class T, unsigned int TVectorDimension >
std::istream &
operator>>(std::istream & is, Vector< T, TVectorDimension > & vct)
{
  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    is >>  vct[i];
    }
  return is;
}

/**
 *
 */
template< class T, unsigned int TVectorDimension >
typename Vector< T, TVectorDimension >::ValueType
Vector< T, TVectorDimension >
::operator*(const Self & other) const
{
  typename NumericTraits< T >::AccumulateType value = NumericTraits< T >::Zero;
  for ( unsigned int i = 0; i < TVectorDimension; i++ )
    {
    value += ( *this )[i] * other[i];
    }
  return value;
}
} // end namespace itk

#endif

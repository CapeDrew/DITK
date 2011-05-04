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
#ifndef __itkSumInputFunction_txx
#define __itkSumInputFunction_txx

#include "itkSumInputFunction.h"

namespace itk
{
namespace Statistics
{

/** Constructor */
template<class TMeasurementVector, class ScalarType>
SumInputFunction<TMeasurementVector,ScalarType>
::SumInputFunction()
{
  m_Size = 0;
}

/** Destructor */
template<class TMeasurementVector, class ScalarType>
SumInputFunction<TMeasurementVector,ScalarType>
::~SumInputFunction()
{
}

/** Set the size */
template<class TMeasurementVector, class ScalarType>
void
SumInputFunction<TMeasurementVector,ScalarType>
::SetSize(unsigned int n)
{
  m_Size = n;
  this->Modified();
}

/** Evaluate */
template<class TMeasurementVector, class ScalarType>
ScalarType
SumInputFunction<TMeasurementVector,ScalarType>
::Evaluate(const TMeasurementVector& input)  const
{
  vnl_vector<ScalarType> temp(input, m_Size);
  return temp.sum();
}

/** Print the object */
template<class TMeasurementVector, class ScalarType>
void
SumInputFunction <TMeasurementVector,ScalarType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  os << indent << "SumInputFunction(" << this << ")" << std::endl;
  os << indent << "m_Size = " << m_Size << std::endl;
  Superclass::PrintSelf( os, indent );
}

} // end namespace Statistics
} // end namespace itk

#endif

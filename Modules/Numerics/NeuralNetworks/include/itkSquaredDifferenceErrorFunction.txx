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
#ifndef __itkSquaredDifferenceErrorFunction_txx
#define __itkSquaredDifferenceErrorFunction_txx

#include "itkSquaredDifferenceErrorFunction.h"

namespace itk
{
namespace Statistics
{

/** Constructor */
template<class TMeasurementVector, class ScalarType>
SquaredDifferenceErrorFunction<TMeasurementVector,ScalarType>
::SquaredDifferenceErrorFunction()
{
}

/** Destructor */
template<class TMeasurementVector, class ScalarType>
SquaredDifferenceErrorFunction <TMeasurementVector,ScalarType>
::~SquaredDifferenceErrorFunction()
{
}

/** Evaluate */
template<class TMeasurementVector, class ScalarType>
ScalarType
SquaredDifferenceErrorFunction <TMeasurementVector,ScalarType>
::Evaluate(const TMeasurementVector& errors)  const
{
  vnl_vector <ScalarType> temp;
  temp.set_size(errors.Size());
  for(unsigned int i=0; i<errors.Size(); i++)
    temp[i]=errors[i];

  //temp.(errors.GetVnlVector());

  return (temp.squared_magnitude() / 2);
}

/** Evaluate derivatives */
template<class TMeasurementVector, class ScalarType>
typename SquaredDifferenceErrorFunction <TMeasurementVector,ScalarType>
::InternalVectorType
SquaredDifferenceErrorFunction <TMeasurementVector,ScalarType>
::EvaluateDerivative(const TMeasurementVector& errors)  const
{
  //TMeasurementVector diff;
  InternalVectorType diff;
  diff.SetSize(errors.Size());
  for(unsigned int i=0; i<errors.Size(); i++)
    {
    if ((-0.1 < errors[i]) && (errors[i] < 0.1))
      {
      diff[i]=0;
      }
    else
      {
      diff[i]=errors[i];
      }
    }
  return (diff); //(errors);
}

/** Print the object */
template<class TMeasurementVector, class ScalarType>
void
SquaredDifferenceErrorFunction <TMeasurementVector,ScalarType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  os << indent << "SquaredDifferenceErrorFunction(" << this << ")" << std::endl;
  Superclass::PrintSelf( os, indent );
}

} // end namespace Statistics
} // end namespace itk

#endif

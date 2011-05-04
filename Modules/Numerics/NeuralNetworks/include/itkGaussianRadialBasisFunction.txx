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
#ifndef __itkGaussianRadialBasisFunction_txx
#define __itkGaussianRadialBasisFunction_txx

#include "itkGaussianRadialBasisFunction.h"

#include <math.h>

namespace itk
{
namespace Statistics
{

/** Constructor */
template<class ScalarType>
GaussianRadialBasisFunction< ScalarType>
::GaussianRadialBasisFunction()
{
}

/** Destructor */
template<class ScalarType>
GaussianRadialBasisFunction< ScalarType>
::~GaussianRadialBasisFunction()
{
}

/** Evaluate function */
template<class ScalarType>
ScalarType
GaussianRadialBasisFunction< ScalarType>
::Evaluate(const ScalarType& input) const
{
  ScalarType val;
  ScalarType radius = Superclass::GetRadius();
  val = vcl_exp(-0.5*vcl_pow(input,2)/vcl_pow(radius,2));
  return val;
}

/** Evaluate derivative function */
template<class ScalarType>
ScalarType
GaussianRadialBasisFunction< ScalarType>
::EvaluateDerivative(const ScalarType& dist,const ArrayType& input,
                          char mode,int element_id) const
{
  ScalarType val = 0;
  ScalarType radius=Superclass::GetRadius();
  ArrayType center = Superclass::GetCenter();
  if(mode=='u') //w.r.t centers
    {
    ScalarType temp1= vcl_pow(radius,2);
    val=Evaluate(dist)
                      *(input.GetElement(element_id)-center.GetElement(element_id))/temp1;
    }
  else if(mode=='s') // w.r.t radius
    {
    val=Evaluate(dist)*vcl_pow(dist,2)/vcl_pow(radius,3);
    }
  return val;
}

/** Print the object */
template<class ScalarType>
void
GaussianRadialBasisFunction<ScalarType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  os << indent << "GaussianRadialBasisFunction(" << this << ")" << std::endl;
  Superclass::PrintSelf( os, indent );
}

} // end namespace Statistics
} // end namespace itk

#endif

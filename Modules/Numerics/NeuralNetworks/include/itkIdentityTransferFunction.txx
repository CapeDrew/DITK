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
#ifndef __itkIdentityTransferFunction_txx
#define __itkIdentityTransferFunction_txx

#include "itkIdentityTransferFunction.h"

namespace itk
{
namespace Statistics
{

/** Constructor */
template<class ScalarType>
IdentityTransferFunction<ScalarType>
::IdentityTransferFunction()
{
}

/** Destructor */
template<class ScalarType>
IdentityTransferFunction<ScalarType>
::~IdentityTransferFunction()
{
}

template<class ScalarType>
ScalarType
IdentityTransferFunction<ScalarType>
::Evaluate(const ScalarType& input)  const
{
  return input;
}

template<class ScalarType>
ScalarType
IdentityTransferFunction<ScalarType>
::EvaluateDerivative(const ScalarType & itkNotUsed(input))  const
{
  return 1;
}

/** Print the object */
template<class ScalarType>
void
IdentityTransferFunction<ScalarType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  os << indent << "IdentityTransferFunction(" << this << ")" << std::endl;
  Superclass::PrintSelf( os, indent );
}

} // end namespace Statistics
} // end namespace itk

#endif

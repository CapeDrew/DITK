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
#ifndef __itkLogSigmoidTransferFunction_txx
#define __itkLogSigmoidTransferFunction_txx

#include "itkLogSigmoidTransferFunction.h"

namespace itk
{
namespace Statistics
{

/** Constructor */
template<class ScalarType>
LogSigmoidTransferFunction<ScalarType>
::LogSigmoidTransferFunction()
{
}

/** Destructor */
template<class ScalarType>
LogSigmoidTransferFunction<ScalarType>
::~LogSigmoidTransferFunction()
{
}

/** Evaluate */
template<class ScalarType>
ScalarType
LogSigmoidTransferFunction<ScalarType>
::Evaluate(const ScalarType& input)  const
{
  const ScalarType v = 1.0 / (1.0 + vcl_exp(-input));
  return v;
}

/** Evaluate derivatives */
template<class ScalarType>
ScalarType
LogSigmoidTransferFunction<ScalarType>
::EvaluateDerivative(const ScalarType& input)  const
{
  ScalarType f = Evaluate(input);
  return f * (1 - f);
}

/** Print the object */
template<class ScalarType>
void
LogSigmoidTransferFunction<ScalarType>
::PrintSelf( std::ostream& os, Indent indent ) const
{
  os << indent << "LogSigmoidTransferFunction(" << this << ")" << std::endl;
  Superclass::PrintSelf( os, indent );
}

} // end namespace Statistics
} // end namespace itk

#endif

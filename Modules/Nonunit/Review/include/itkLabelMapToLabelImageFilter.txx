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
#ifndef __itkLabelMapToLabelImageFilter_txx
#define __itkLabelMapToLabelImageFilter_txx

#include "itkLabelMapToLabelImageFilter.h"
#include "itkNumericTraits.h"
#include "itkProgressReporter.h"
#include "itkImageRegionConstIteratorWithIndex.h"

namespace itk
{
template< class TInputImage, class TOutputImage >
LabelMapToLabelImageFilter< TInputImage, TOutputImage >
::LabelMapToLabelImageFilter()
{}

template< class TInputImage, class TOutputImage >
void
LabelMapToLabelImageFilter< TInputImage, TOutputImage >
::BeforeThreadedGenerateData()
{
  OutputImageType *     output = this->GetOutput();
  const InputImageType *input = this->GetInput();

  output->FillBuffer( input->GetBackgroundValue() );

  Superclass::BeforeThreadedGenerateData();
}

template< class TInputImage, class TOutputImage >
void
LabelMapToLabelImageFilter< TInputImage, TOutputImage >
::ThreadedProcessLabelObject(LabelObjectType *labelObject)
{
  const typename LabelObjectType::LabelType & label = labelObject->GetLabel();

  typedef typename LabelObjectType::LengthType        LengthType;

  typename InputImageType::LabelObjectType::LineContainerType::const_iterator lit;
  typename InputImageType::LabelObjectType::LineContainerType & lineContainer = labelObject->GetLineContainer();

  for ( lit = lineContainer.begin(); lit != lineContainer.end(); lit++ )
    {
    IndexType     idx = lit->GetIndex();
    LengthType length = lit->GetLength();
    for ( LengthType i = 0; i < length; i++ )
      {
      this->GetOutput()->SetPixel(idx, label);
      idx[0]++;
      }
    }
}
} // end namespace itk
#endif

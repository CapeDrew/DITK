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
#ifndef __itkBinaryReconstructionLabelMapFilter_txx
#define __itkBinaryReconstructionLabelMapFilter_txx

#include "itkBinaryReconstructionLabelMapFilter.h"
#include "itkProgressReporter.h"


namespace itk {

template <class TImage, class TMarkerImage, class TAttributeAccessor>
BinaryReconstructionLabelMapFilter<TImage, TMarkerImage, TAttributeAccessor>
::BinaryReconstructionLabelMapFilter()
{
  this->SetNumberOfRequiredInputs(2);
  m_ForegroundValue = NumericTraits< MarkerImagePixelType >::max();
}


template <class TImage, class TMarkerImage, class TAttributeAccessor>
void
BinaryReconstructionLabelMapFilter<TImage, TMarkerImage, TAttributeAccessor>
::ThreadedProcessLabelObject( LabelObjectType * labelObject )
{
  AttributeAccessorType accessor;

  const MarkerImageType * maskImage = this->GetMarkerImage();

  typename LabelObjectType::LineContainerType::const_iterator lit;
  typename LabelObjectType::LineContainerType & lineContainer = labelObject->GetLineContainer();

  // iterate over all the lines to find a pixel inside the object
  for( lit = lineContainer.begin(); lit != lineContainer.end(); lit++ )
    {
    const IndexType & firstIdx = lit->GetIndex();
    SizeValueType length = lit->GetLength();

    IndexValueType endIdx0 = firstIdx[0] + length;
    for( IndexType idx = firstIdx; idx[0]<endIdx0; idx[0]++ )
      {
      const MarkerImagePixelType & v = maskImage->GetPixel( idx );
      if( v == m_ForegroundValue )
        {
        // keep the object
        accessor( labelObject, true );
        return;
        }
      }
    }

  // remove the object
  accessor( labelObject, false );

}


template <class TImage, class TMarkerImage, class TAttributeAccessor>
void
BinaryReconstructionLabelMapFilter<TImage, TMarkerImage, TAttributeAccessor>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "ForegroundValue: "  << static_cast<typename NumericTraits<MarkerImagePixelType>::PrintType>(m_ForegroundValue) << std::endl;
}

}// end namespace itk
#endif

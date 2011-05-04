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
#ifndef __itkAttributePositionLabelMapFilter_txx
#define __itkAttributePositionLabelMapFilter_txx

#include "itkAttributePositionLabelMapFilter.h"
#include "itkProgressReporter.h"
#include "itkLabelMapUtilities.h"


namespace itk {

template <class TImage, class TAttributeAccessor, bool VPhysicalPosition>
AttributePositionLabelMapFilter<TImage, TAttributeAccessor, VPhysicalPosition>
::AttributePositionLabelMapFilter()
{
}

template <class TImage, class TAttributeAccessor, bool VPhysicalPosition>
void
AttributePositionLabelMapFilter<TImage, TAttributeAccessor, VPhysicalPosition>
::ThreadedProcessLabelObject( LabelObjectType * labelObject )
{
  TAttributeAccessor accessor;
  AttributeValueType position = accessor( labelObject );
  // change it to an index position if it is physical
  IndexType idx;
  if( VPhysicalPosition )
    {
    Point< double, ImageDimension > point;
    // copy the position to a point, required by TransformPhysicalPointToIndex
    for( unsigned int i=0; i<ImageDimension; i++ )
      {
      point[i] = position[i];
      }
    this->GetOutput()->TransformPhysicalPointToIndex( point, idx );
    }
  else
    {
    // copy the position to the index, to avoid warnings
    for( unsigned int i=0; i<ImageDimension; i++ )
      {
      idx[i] = position[i];
      }
    }
  // clear the label object
  labelObject->GetLineContainer().clear();
  // and mark only the pixel we are interested in
  labelObject->AddIndex( idx );
}

template <class TImage, class TAttributeAccessor, bool VPhysicalPosition>
void
AttributePositionLabelMapFilter<TImage, TAttributeAccessor, VPhysicalPosition>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

}// end namespace itk
#endif

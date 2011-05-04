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
#ifndef __itkAttributeSelectionLabelMapFilter_txx
#define __itkAttributeSelectionLabelMapFilter_txx

#include "itkAttributeSelectionLabelMapFilter.h"
#include "itkProgressReporter.h"


namespace itk {

template <class TImage, class TAttributeAccessor>
AttributeSelectionLabelMapFilter<TImage, TAttributeAccessor>
::AttributeSelectionLabelMapFilter()
{
  m_AttributeSet.clear();
  m_Exclude = false;
  this->SetNumberOfRequiredOutputs(2);
  this->SetNthOutput(1, static_cast<TImage*>(this->MakeOutput(1).GetPointer()));
}


template <class TImage, class TAttributeAccessor>
void
AttributeSelectionLabelMapFilter<TImage, TAttributeAccessor>
::GenerateData()
{
  // Allocate the output
  this->AllocateOutputs();

  ImageType * output = this->GetOutput();
  ImageType * output2 = this->GetOutput( 1 );

  // set the background value for the second output - this is not done in the superclasses
  output2->SetBackgroundValue( output->GetBackgroundValue() );

  AttributeAccessorType accessor;

  const typename ImageType::LabelObjectContainerType & labelObjectContainer = output->GetLabelObjectContainer();

  ProgressReporter progress( this, 0, labelObjectContainer.size() );

  typename ImageType::LabelObjectContainerType::const_iterator it = labelObjectContainer.begin();
  while( it != labelObjectContainer.end() )
    {
    typename LabelObjectType::LabelType label = it->first;
    LabelObjectType * labelObject = it->second;
    bool notInSet = m_AttributeSet.find( accessor( labelObject ) ) == m_AttributeSet.end();
    if( m_Exclude != notInSet )  // no xor in c++, use != instead
      {
      // must increment the iterator before removing the object to avoid invalidating the iterator
      it++;
      output2->AddLabelObject( labelObject );
      output->RemoveLabel( label );
      }
    else
      {
      it++;
      }

    progress.CompletedPixel();
    }
}


template <class TImage, class TAttributeAccessor>
void
AttributeSelectionLabelMapFilter<TImage, TAttributeAccessor>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "AttributeSet: "  << &m_AttributeSet << std::endl;
  os << indent << "Exclude: "  << m_Exclude << std::endl;
}

}// end namespace itk
#endif

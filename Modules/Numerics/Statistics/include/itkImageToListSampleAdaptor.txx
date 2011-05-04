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
#ifndef __itkImageToListSampleAdaptor_txx
#define __itkImageToListSampleAdaptor_txx

#include "itkImageToListSampleAdaptor.h"

namespace itk
{
namespace Statistics
{
template< class TImage >
ImageToListSampleAdaptor< TImage >
::ImageToListSampleAdaptor()
{
  m_Image = 0;
  m_UsePixelContainer = true;
}

template< class TImage >
const typename ImageToListSampleAdaptor< TImage >::MeasurementVectorType &
ImageToListSampleAdaptor< TImage >
::GetMeasurementVector(InstanceIdentifier id) const
{
  if ( m_Image.IsNull() )
    {
    itkExceptionMacro("Image has not been set yet");
    }

  if ( m_UsePixelContainer )
    {
    MeasurementVectorTraits::Assign(m_MeasurementVectorInternal,
                                    ( *m_PixelContainer )[id]);
    }
  else
    {
    MeasurementVectorTraits::Assign( m_MeasurementVectorInternal,
                                     m_Image->GetPixel( m_Image->ComputeIndex(id) ) );
    }

  return m_MeasurementVectorInternal;
}

/** returns the number of measurement vectors in this container*/
template< class TImage >
typename ImageToListSampleAdaptor< TImage >::InstanceIdentifier
ImageToListSampleAdaptor< TImage >
::Size() const
{
  if ( m_Image.IsNull() )
    {
    itkExceptionMacro("Image has not been set yet");
    }

  return m_Image->GetPixelContainer()->Size();
}

template< class TImage >
inline typename ImageToListSampleAdaptor< TImage >::AbsoluteFrequencyType
ImageToListSampleAdaptor< TImage >
::GetFrequency(InstanceIdentifier) const
{
  if ( m_Image.IsNull() )
    {
    itkExceptionMacro("Image has not been set yet");
    }

  return NumericTraits< AbsoluteFrequencyType >::One;
}

template< class TImage >
void
ImageToListSampleAdaptor< TImage >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "Image: ";
  if ( m_Image.IsNotNull() )
    {
    os << m_Image << std::endl;
    }
  else
    {
    os << "not set." << std::endl;
    }
  os << indent << "UsePixelContainer: "
     << this->GetUsePixelContainer() << std::endl;
}

template< class TImage >
void
ImageToListSampleAdaptor< TImage >
::SetImage(const TImage *image)
{
  m_Image = image;
  m_PixelContainer = image->GetPixelContainer();
  this->Modified();
}

template< class TImage >
const TImage *
ImageToListSampleAdaptor< TImage >
::GetImage() const
{
  if ( m_Image.IsNull() )
    {
    itkExceptionMacro("Image has not been set yet");
    }

  return m_Image.GetPointer();
}

template< class TImage >
typename ImageToListSampleAdaptor< TImage >::TotalAbsoluteFrequencyType
ImageToListSampleAdaptor< TImage >
::GetTotalFrequency() const
{
  if ( m_Image.IsNull() )
    {
    itkExceptionMacro("Image has not been set yet");
    }

  return this->Size();
}
} // end of namespace Statistics
} // end of namespace itk

#endif

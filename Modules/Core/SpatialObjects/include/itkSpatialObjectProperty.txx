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
#ifndef __itkSpatialObjectProperty_txx
#define __itkSpatialObjectProperty_txx

#include "itkSpatialObjectProperty.h"

namespace itk
{
template< class TComponentType >
SpatialObjectProperty< TComponentType >
::SpatialObjectProperty()
{
  m_MTime = 0;
  m_Color.SetRed(1);
  m_Color.SetGreen(1);
  m_Color.SetBlue(1);
  m_Color.SetAlpha(1);
  m_Name = "";
}

template< class TComponentType >
SpatialObjectProperty< TComponentType >
::~SpatialObjectProperty()
{}

template< class TComponentType >
const typename SpatialObjectProperty< TComponentType >::PixelType &
SpatialObjectProperty< TComponentType >
::GetColor(void) const
{
  return m_Color;
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetColor(const PixelType & color)
{
  m_Color = color;
  this->Modified();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetColor(TComponentType r, TComponentType g, TComponentType b)
{
  m_Color.SetRed(r);
  m_Color.SetGreen(g);
  m_Color.SetBlue(b);
  this->Modified();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetRed(TComponentType r)
{
  m_Color.SetRed(r);
  this->Modified();
}

template< class TComponentType >
TComponentType
SpatialObjectProperty< TComponentType >
::GetRed(void) const
{
  return m_Color.GetRed();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetGreen(TComponentType g)
{
  m_Color.SetGreen(g);
  this->Modified();
}

template< class TComponentType >
TComponentType
SpatialObjectProperty< TComponentType >
::GetGreen(void) const
{
  return m_Color.GetGreen();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetBlue(TComponentType b)
{
  m_Color.SetBlue(b);
  this->Modified();
}

template< class TComponentType >
TComponentType
SpatialObjectProperty< TComponentType >
::GetBlue(void) const
{
  return m_Color.GetBlue();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetAlpha(TComponentType a)
{
  m_Color.SetAlpha(a);
  this->Modified();
}

template< class TComponentType >
TComponentType
SpatialObjectProperty< TComponentType >
::GetAlpha(void) const
{
  return m_Color.GetAlpha();
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::SetName(const char *name)
{
  m_Name.assign(name);
  this->Modified();
}

template< class TComponentType >
typename SpatialObjectProperty< TComponentType >::StringType
SpatialObjectProperty< TComponentType >
::GetName(void) const
{
  return m_Name;
}

template< class TComponentType >
void
SpatialObjectProperty< TComponentType >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Name: " << m_Name << std::endl;
  os << indent << "RGBA: " << m_Color.GetRed() << " ";
  os << m_Color.GetGreen() << " ";
  os << m_Color.GetBlue() << std::endl;
}
} // end of namespace itk

#endif // __SpatialObjectProperty_txx

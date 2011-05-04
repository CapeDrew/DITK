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
/*=========================================================================
 *
 *  Portions of this file are subject to the VTK Toolkit Version 3 copyright.
 *
 *  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
 *
 *  For complete copyright, license and disclaimer of warranty information
 *  please refer to the NOTICE file at the top of the ITK source tree.
 *
 *=========================================================================*/
#ifndef __itkLabelMap_txx
#define __itkLabelMap_txx

#include "itkLabelMap.h"
#include "itkProcessObject.h"

namespace itk
{
/**
 *
 */
template< class TLabelObject >
LabelMap< TLabelObject >
::LabelMap()
{
  m_BackgroundValue = NumericTraits< LabelType >::Zero;
  this->Initialize();
}

/**
 *
 */
template< class TLabelObject >
void
LabelMap< TLabelObject >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "BackgroundValue: "
     << static_cast< typename NumericTraits< LabelType >::PrintType >( m_BackgroundValue ) << std::endl;
  os << indent << "LabelObjectContainer: " << &m_LabelObjectContainer << std::endl;
}

/**
 *
 */
template< class TLabelObject >
void
LabelMap< TLabelObject >
::Initialize()
{
  this->ClearLabels();
}

/**
 *
 */
template< class TLabelObject >
void
LabelMap< TLabelObject >
::Allocate()
{
  this->Initialize();
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::Graft(const DataObject *data)
{
  // call the superclass' implementation
  Superclass::Graft(data);

  if ( data )
    {
    // Attempt to cast data to an Image
    const Self *imgData;

    try
      {
      imgData = dynamic_cast< const Self * >( data );
      }
    catch ( ... )
      {
      return;
      }

    if ( imgData )
      {
      // Now copy anything remaining that is needed
      m_LabelObjectContainer = imgData->m_LabelObjectContainer;
      m_BackgroundValue = imgData->m_BackgroundValue;
      }
    else
      {
      // pointer could not be cast back down
      itkExceptionMacro( << "itk::Image::Graft() cannot cast "
                         << typeid( data ).name() << " to "
                         << typeid( const Self * ).name() );
      }
    }
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelObjectType *
LabelMap< TLabelObject >
::GetLabelObject(const LabelType & label)
{
  if ( !this->HasLabel(label) )
    {
    itkExceptionMacro(<< "No label object with label "
                      << static_cast< typename NumericTraits< LabelType >::PrintType >( label )
                      << ".");
    }
  if ( m_BackgroundValue == label )
    {
    itkExceptionMacro(<< "Label "
                      << static_cast< typename NumericTraits< LabelType >::PrintType >( label )
                      << " is the background label.");
    }
  return m_LabelObjectContainer[label].GetPointer();
}

template< class TLabelObject >
const typename LabelMap< TLabelObject >::LabelObjectType *
LabelMap< TLabelObject >
::GetLabelObject(const LabelType & label) const
{
  if ( !this->HasLabel(label) )
    {
    itkExceptionMacro(<< "No label object with label "
                      << static_cast< typename NumericTraits< LabelType >::PrintType >( label )
                      << ".");
    }
  if ( m_BackgroundValue == label )
    {
    itkExceptionMacro(<< "Label "
                      << static_cast< typename NumericTraits< LabelType >::PrintType >( label )
                      << " is the background label.");
    }
  return m_LabelObjectContainer.find(label)->second.GetPointer();
}

template< class TLabelObject >
bool
LabelMap< TLabelObject >
::HasLabel(const LabelType label) const
{
  if ( label == m_BackgroundValue )
    {
    return true;
    }
  return m_LabelObjectContainer.find(label) != m_LabelObjectContainer.end();
}

template< class TLabelObject >
const typename LabelMap< TLabelObject >::LabelType &
LabelMap< TLabelObject >
::GetPixel(const IndexType & idx) const
{
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    if ( it->second->HasIndex(idx) )
      {
      return it->second->GetLabel();
      }
    }
  return m_BackgroundValue;
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelObjectType *
LabelMap< TLabelObject >
::GetNthLabelObject(const SizeValueType & pos)
{
  SizeValueType i = 0;

  for ( typename LabelObjectContainerType::iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    if ( i == pos )
      {
      return it->second;
      }
    i++;
    }
  itkExceptionMacro(<< "Can't access to label object at position "
                    << pos
                    << ". The label map has only "
                    << this->GetNumberOfLabelObjects()
                    << " label objects registered.");
}

template< class TLabelObject >
const typename LabelMap< TLabelObject >::LabelObjectType *
LabelMap< TLabelObject >
::GetNthLabelObject(const SizeValueType & pos) const
{
  SizeValueType i = 0;

  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    if ( i == pos )
      {
      return it->second;
      }
    i++;
    }
  itkExceptionMacro(<< "Can't access to label object at position "
                    << pos
                    << ". The label map has only "
                    << this->GetNumberOfLabelObjects()
                    << " label objects registered.");
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::SetPixel(const IndexType & idx, const LabelType & label)
{
  if ( label == m_BackgroundValue )
    {
    // just do nothing
    return;
    }

  typename LabelObjectContainerType::iterator it = m_LabelObjectContainer.find(label);

  if ( it != m_LabelObjectContainer.end() )
    {
    // the label already exist - add the pixel to it
    ( *it ).second->AddIndex(idx);
    this->Modified();
    }
  else
    {
    // the label does not exist yet - create a new one
    LabelObjectPointerType labelObject = LabelObjectType::New();
    labelObject->SetLabel(label);
    labelObject->AddIndex(idx);
    // Modified() is called in AddLabelObject()
    this->AddLabelObject(labelObject);
    }
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::SetLine(const IndexType & idx, const LengthType & length, const LabelType & label)
{
  if ( label == m_BackgroundValue )
    {
    // just do nothing
    return;
    }

  typename LabelObjectContainerType::iterator it = m_LabelObjectContainer.find(label);

  if ( it != m_LabelObjectContainer.end() )
    {
    // the label already exist - add the pixel to it
    ( *it ).second->AddLine(idx, length);
    this->Modified();
    }
  else
    {
    // the label does not exist yet - create a new one
    LabelObjectPointerType labelObject = LabelObjectType::New();
    labelObject->SetLabel(label);
    labelObject->AddLine(idx, length);
    // Modified() is called in AddLabelObject()
    this->AddLabelObject(labelObject);
    }
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelObjectType *
LabelMap< TLabelObject >
::GetLabelObject(const IndexType & idx) const
{
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    if ( it->second->HasIndex(idx) )
      {
      return it->second.GetPointer();
      }
    }
  itkExceptionMacro(<< "No label object at index " << idx << ".");
//   return NULL;
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::AddLabelObject(LabelObjectType *labelObject)
{
  itkAssertOrThrowMacro( ( labelObject != NULL ), "Input LabelObject can't be Null" );

  m_LabelObjectContainer[labelObject->GetLabel()] = labelObject;
  this->Modified();
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::PushLabelObject(LabelObjectType *labelObject)
{
  itkAssertOrThrowMacro( ( labelObject != NULL ), "Input LabelObject can't be Null" );

  if ( m_LabelObjectContainer.empty() )
    {
    if ( m_BackgroundValue == 0 )
      {
      labelObject->SetLabel(1);
      }
    else
      {
      labelObject->SetLabel(0);
      }
    }
  else
    {
    LabelType lastLabel = m_LabelObjectContainer.rbegin()->first;
    LabelType firstLabel = m_LabelObjectContainer.begin()->first;
    if ( lastLabel != NumericTraits< LabelType >::max() && lastLabel + 1 != m_BackgroundValue )
      {
      labelObject->SetLabel(lastLabel + 1);
      }
    else if ( lastLabel != NumericTraits< LabelType >::max() && lastLabel + 1 != NumericTraits< LabelType >::max()
              && lastLabel + 2 != m_BackgroundValue )
      {
      labelObject->SetLabel(lastLabel + 2);
      }
    else if ( firstLabel != NumericTraits< LabelType >::NonpositiveMin() && firstLabel - 1 != m_BackgroundValue )
      {
      labelObject->SetLabel(firstLabel - 1);
      }
    else
      {
      // search for an unused label
      LabelType label = firstLabel;
      typename LabelObjectContainerType::const_iterator it;
      for ( it = m_LabelObjectContainer.begin();
            it != m_LabelObjectContainer.end();
            it++, label++ )
        {
        assert( ( it->second.IsNotNull() ) );
        if ( label == m_BackgroundValue )
          {
          label++;
          }
        if ( label != it->first )
          {
          labelObject->SetLabel(label);
          break;
          }
        }
      if ( label == lastLabel )
        {
        itkExceptionMacro(<< "Can't push the label object: the label map is full.");
        }
      }
    }
  // modified is called in AddLabelObject()
  this->AddLabelObject(labelObject);
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::RemoveLabelObject(LabelObjectType *labelObject)
{
  itkAssertOrThrowMacro( ( labelObject != NULL ), "Input LabelObject can't be Null" );
  // modified is called in RemoveLabel()
  this->RemoveLabel( labelObject->GetLabel() );
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::RemoveLabel(const LabelType & label)
{
  if ( m_BackgroundValue == label )
    {
    itkExceptionMacro(<< "Label "
                      << static_cast< typename NumericTraits< LabelType >::PrintType >( label )
                      << " is the background label.");
    }
  m_LabelObjectContainer.erase(label);
  this->Modified();
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::ClearLabels()
{
  if ( !m_LabelObjectContainer.empty() )
    {
    m_LabelObjectContainer.clear();
    this->Modified();
    }
}

template< class TLabelObject >
const typename LabelMap< TLabelObject >::LabelObjectContainerType &
LabelMap< TLabelObject >
::GetLabelObjectContainer() const
{
  return m_LabelObjectContainer;
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelObjectContainerType &
LabelMap< TLabelObject >
::GetLabelObjectContainer()
{
  return m_LabelObjectContainer;
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::SizeValueType
LabelMap< TLabelObject >
::GetNumberOfLabelObjects() const
{
  return m_LabelObjectContainer.size();
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelVectorType
LabelMap< TLabelObject >
::GetLabels() const
{
  LabelVectorType res;

  res.reserve( this->GetNumberOfLabelObjects() );
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    res.push_back(it->first);
    }
  return res;
}

template< class TLabelObject >
typename LabelMap< TLabelObject >::LabelObjectVectorType
LabelMap< TLabelObject >
::GetLabelObjects() const
{
  LabelObjectVectorType res;

  res.reserve( this->GetNumberOfLabelObjects() );
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    res.push_back(it->second);
    }
  return res;
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::PrintLabelObjects(std::ostream & os) const
{
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    assert( ( it->second.IsNotNull() ) );
    it->second->Print(os);
    os << std::endl;
    }
}

template< class TLabelObject >
void
LabelMap< TLabelObject >
::Optimize()
{
  for ( typename LabelObjectContainerType::const_iterator it = m_LabelObjectContainer.begin();
        it != m_LabelObjectContainer.end();
        it++ )
    {
    assert( ( it->second.IsNotNull() ) );
    it->second->Optimize();
    }
  this->Modified();
}
} // end namespace itk

#endif

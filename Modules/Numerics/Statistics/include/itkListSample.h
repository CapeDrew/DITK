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
#ifndef __itkListSample_h
#define __itkListSample_h

#include "itkObjectFactory.h"
#include "itkFixedArray.h"
#include "itkSample.h"

#include <vector>

namespace itk
{
namespace Statistics
{
/** \class ListSample
 *  \brief This class is the native implementation of the a Sample with an STL container
 *
 * ListSample stores measurements in a list type structure (as opposed to a
 * Histogram, etc.).  ListSample allows duplicate measurements. ListSample is
 * not sorted.
 *
 * ListSample does not allow the user to specify the frequency of
 * a measurement directly.  The GetFrequency() methods returns 1 if
 * the measurement exists in the list, 0 otherwise.
 *
 * \sa Sample, Histogram
 * \ingroup ITK-Statistics
 *
 * \wiki
 * \wikiexample{Statistics/ListSample,Create a list of sample measurements}
 * \endwiki
 */

template< class TMeasurementVector >
class ITK_EXPORT ListSample:public Sample< TMeasurementVector >
{
public:
  /** Standard class typedef. */
  typedef ListSample                   Self;
  typedef Sample< TMeasurementVector > Superclass;
  typedef SmartPointer< Self >         Pointer;
  typedef SmartPointer< const Self >   ConstPointer;

  /** Standard macros */
  itkTypeMacro(ListSample, Sample);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Typedefs inherited from the superclass */
  itkSuperclassTraitMacro(MeasurementVectorType)
  itkSuperclassTraitMacro(MeasurementVectorSizeType)
  itkSuperclassTraitMacro(MeasurementType)
  itkSuperclassTraitMacro(AbsoluteFrequencyType)
  itkSuperclassTraitMacro(TotalAbsoluteFrequencyType)
  itkSuperclassTraitMacro(InstanceIdentifier)

  /** Value type of a measurement (component of the measurement
   * vector) */
  typedef MeasurementVectorType ValueType;

  /** internal data container type */
  typedef std::vector< MeasurementVectorType > InternalDataContainerType;

  /** Resize the container. Using Resize() and then SetMeasurementVector() is
   * about nine times faster than usign PushBack() continously. Which means that
   * whenever the total number of Measurement vectors is known, the users
   * should prefer calling Resize() first and then set the values by calling
   * SetMeasurementVector(). On the other hand, if the number of measurement
   * vectors is not known from the beginning, then calling PushBack()
   * sequentially is a convenient option. */
  void Resize(InstanceIdentifier newsize);

  /** Removes all the elements in the Sample */
  void Clear();

  /** Inserts a measurement at the end of the list */
  void PushBack(const MeasurementVectorType & mv);

  /** Get the number of measurement vectors in the sample */
  InstanceIdentifier Size() const;

  /** Get the measurement associated with the specified
   * InstanceIdentifier */
  const MeasurementVectorType & GetMeasurementVector(InstanceIdentifier id) const;

  /** Set a component a measurement to a particular value. */
  void SetMeasurement(InstanceIdentifier id,
                      unsigned int dim,
                      const MeasurementType & value);

  /** Replace a measurement with a different measurement */
  void SetMeasurementVector(InstanceIdentifier id,
                            const MeasurementVectorType & mv);

  /** Get the frequency of a measurement. Returns 1 if the measurement
   * exist. */
  AbsoluteFrequencyType GetFrequency(InstanceIdentifier id) const;

  /** Get the total frequency of the sample.  This is equivalent to
   * the size of the sample. */
  TotalAbsoluteFrequencyType GetTotalFrequency() const;

  /** Method to graft another sample */
  virtual void Graft(const DataObject *thatObject);

  /** \class ConstIterator  \ingroup ITK-Statistics */
  class ConstIterator
  {
    friend class ListSample;
public:

    ConstIterator(const ListSample *sample)
    {
      *this = sample->Begin();
    }

    ConstIterator(const ConstIterator & iter)
    {
      m_Iter = iter.m_Iter;
      m_InstanceIdentifier = iter.m_InstanceIdentifier;
    }

    ConstIterator & operator=(const ConstIterator & iter)
    {
      m_Iter = iter.m_Iter;
      m_InstanceIdentifier = iter.m_InstanceIdentifier;
      return *this;
    }

    AbsoluteFrequencyType GetFrequency() const
    {
      return 1;
    }

    const MeasurementVectorType & GetMeasurementVector() const
    {
      return static_cast< const MeasurementVectorType & >( *m_Iter );
    }

    InstanceIdentifier GetInstanceIdentifier() const
    {
      return m_InstanceIdentifier;
    }

    ConstIterator & operator++()
    {
      ++m_Iter;
      ++m_InstanceIdentifier;
      return *this;
    }

    bool operator!=(const ConstIterator & it)
    {
      return ( m_Iter != it.m_Iter );
    }

    bool operator==(const ConstIterator & it)
    {
      return ( m_Iter == it.m_Iter );
    }

protected:
    // This method should only be available to the ListSample class
    ConstIterator(
      typename InternalDataContainerType::const_iterator iter,
      InstanceIdentifier iid)
    {
      m_Iter = iter;
      m_InstanceIdentifier = iid;
    }

    // This method is purposely not implemented
    ConstIterator();
private:
    typedef typename InternalDataContainerType::const_iterator InternalIterator;
    InternalIterator   m_Iter;
    InstanceIdentifier m_InstanceIdentifier;
  };

  /** \class Iterator  \ingroup ITK-Statistics */
  class Iterator:public ConstIterator
  {
    friend class ListSample;
public:

    Iterator(Self *sample):ConstIterator(sample)
    {}

    Iterator(const Iterator & iter):ConstIterator(iter)
    {}

    Iterator & operator=(const Iterator & iter)
    {
      this->ConstIterator::operator=(iter);
      return *this;
    }

protected:
    // To ensure const-correctness these method must not be in the public API.
    // The are purposly not implemented, since they should never be called.
    Iterator();
    Iterator(const Self *sample);
    Iterator(typename InternalDataContainerType::const_iterator iter, InstanceIdentifier iid);
    Iterator(const ConstIterator & it);
    ConstIterator & operator=(const ConstIterator & it);

    Iterator(
      typename InternalDataContainerType::iterator iter,
      InstanceIdentifier iid):ConstIterator(iter, iid)
    {}

private:
  };

  /** returns an iterator that points to the beginning of the container */
  Iterator Begin()
  {
    Iterator iter(m_InternalContainer.begin(), 0);

    return iter;
  }

  /** returns an iterator that points to the end of the container */
  Iterator End()
  {
    Iterator iter( m_InternalContainer.end(), m_InternalContainer.size() );

    return iter;
  }

  /** returns an iterator that points to the beginning of the container */
  ConstIterator Begin() const
  {
    ConstIterator iter(m_InternalContainer.begin(), 0);

    return iter;
  }

  /** returns an iterator that points to the end of the container */
  ConstIterator End() const
  {
    ConstIterator iter( m_InternalContainer.end(), m_InternalContainer.size() );

    return iter;
  }

protected:

  ListSample();
  virtual ~ListSample() {}
  void PrintSelf(std::ostream & os, Indent indent) const;

private:
  ListSample(const Self &);     //purposely not implemented
  void operator=(const Self &); //purposely not implemented

  InternalDataContainerType m_InternalContainer;
};
} // end of namespace Statistics
} // end of namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkListSample.txx"
#endif

#endif

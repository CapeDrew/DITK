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
#ifndef __itkHistogramToIntensityImageFilter_h
#define __itkHistogramToIntensityImageFilter_h

#include "itkHistogramToImageFilter.h"

namespace itk
{
/** \class HistogramToIntensityImageFilter
 * \brief The class takes a histogram as an input and produces an image
 * as the output. A pixel, at position I,  in the output image is given by
 *
 * \f[
 * f(I) = q_I
 * \f]
 *  where  \f$q_I\f$ is the frequency of measurement vector, I.
 *
 *  \sa HistogramToProbabilityImageFilter, HistogramToLogProbabilityImageFilter,
 *  HistogramToImageFilter, HistogramToEntropyImageFilter
 * \ingroup ITK-Statistics
 */

namespace Function
{
template< class TInput, class TOutput = SizeValueType >
class HistogramIntensityFunction
{
public:

  //Intensity function returns pixels of SizeValueType.
  typedef TOutput OutputPixelType;

  HistogramIntensityFunction():
    m_TotalFrequency(1) {}

  ~HistogramIntensityFunction() {}

  inline OutputPixelType operator()(const TInput & A) const
  {
    return static_cast< OutputPixelType >( A );
  }

  void SetTotalFrequency(SizeValueType n)
  {
    m_TotalFrequency = n;
  }

  SizeValueType GetTotalFrequency() const
  {
    return m_TotalFrequency;
  }

private:
  SizeValueType m_TotalFrequency;
};
}

template< class THistogram, unsigned int NDimension, class TOutputPixel = SizeValueType >
class ITK_EXPORT HistogramToIntensityImageFilter:
  public HistogramToImageFilter< THistogram, NDimension,
                                 Function::HistogramIntensityFunction< SizeValueType, TOutputPixel > >
{
public:

  /** Standard class typedefs. */
  typedef HistogramToIntensityImageFilter Self;

  /** Standard "Superclass" typedef. */
  typedef HistogramToImageFilter< THistogram, NDimension,
                                  Function::HistogramIntensityFunction< SizeValueType, TOutputPixel > >
  Superclass;

  //typedef typename Function::HistogramIntensityFunction  FunctorType;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Run-time type information (and related methods).   */
  itkTypeMacro(HistogramToIntensityImageFilter, HistogramToImageFilter);

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
protected:
  HistogramToIntensityImageFilter() {}
  virtual ~HistogramToIntensityImageFilter() {}
private:
  HistogramToIntensityImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);                  //purposely not implemented
};
} // end namespace itk

#endif

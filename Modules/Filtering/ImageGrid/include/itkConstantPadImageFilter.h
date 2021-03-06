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
#ifndef __itkConstantPadImageFilter_h
#define __itkConstantPadImageFilter_h

#include "itkPadImageFilter.h"

namespace itk
{
/** \class ConstantPadImageFilter
 * \brief Increase the image size by padding with a constant value.
 *
 * ConstantPadImageFilter changes the output image region.  If the output
 * image region is larger than the input image region, the extra pixels are
 * filled in by a constant value.  The output image region must be specified.
 *
 * \image html PadImageFilter.png "Visual explanation of padding regions."
 *
 * This filter is implemented as a multithreaded filter.  It provides a
 * ThreadedGenerateData() method for its implementation.
 *
 * \ingroup GeometricTransforms
 * \sa WrapPadImageFilter, MirrorPadImageFilter
 * \ingroup ITK-ImageGrid
 *
 * \wiki
 * \wikiexample{Images/ConstantPadImageFilter,Pad an image with a constant value}
 * \endwiki
 */
template< class TInputImage, class TOutputImage >
class ITK_EXPORT ConstantPadImageFilter:
  public PadImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef ConstantPadImageFilter                      Self;
  typedef PadImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                        Pointer;
  typedef SmartPointer< const Self >                  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ConstantPadImageFilter, PadImageFilter);

  /** Typedef to describe the output image region type. */
  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;
  typedef typename Superclass::InputImageRegionType  InputImageRegionType;

  /** Typedef to describe the type of pixel. */
  typedef typename Superclass::OutputImagePixelType OutputImagePixelType;
  typedef typename Superclass::InputImagePixelType  InputImagePixelType;

  /** Typedef to describe the output and input image index and size types. */
  typedef typename Superclass::OutputImageIndexType OutputImageIndexType;
  typedef typename Superclass::InputImageIndexType  InputImageIndexType;
  typedef typename Superclass::OutputImageSizeType  OutputImageSizeType;
  typedef typename Superclass::InputImageSizeType   InputImageSizeType;

  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Set/Get the pad value.  Default is Zero. */
  itkSetMacro(Constant, OutputImagePixelType);
  itkGetConstMacro(Constant, OutputImagePixelType);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro( OutputEqualityComparableCheck,
                   ( Concept::EqualityComparable< OutputImagePixelType > ) );
  itkConceptMacro( InputConvertibleToOutputCheck,
                   ( Concept::Convertible< InputImagePixelType, OutputImagePixelType > ) );
  itkConceptMacro( SameDimensionCheck,
                   ( Concept::SameDimension< ImageDimension, OutputImageDimension > ) );
  itkConceptMacro( OutputOStreamWritableCheck,
                   ( Concept::OStreamWritable< OutputImagePixelType > ) );
  /** End concept checking */
#endif
protected:
  ConstantPadImageFilter();
  ~ConstantPadImageFilter() {}
  void PrintSelf(std::ostream & os, Indent indent) const;

  /** PadImageFilter can be implemented as a multithreaded filter.  Therefore,
   * this implementation provides a ThreadedGenerateData() routine which
   * is called for each processing thread. The output image data is allocated
   * automatically by the superclass prior to calling ThreadedGenerateData().
   * ThreadedGenerateData can only write to the portion of the output image
   * specified by the parameter "outputRegionForThread"
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData() */
  void ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread,
                            int threadId);

  /**
   * Given an n dimensional list of output region breakpoints in indices
   * and size (where the current region and maximum region for each dimension
   * is encoded in regIndices and regLimit), choose the next output region.
   */
  int GenerateNextRegion(long *regIndices, long *regLimit,
                         OutputImageIndexType *indices,
                         OutputImageSizeType *sizes,
                         OutputImageRegionType & outputRegion);

private:
  ConstantPadImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);         //purposely not implemented

  OutputImagePixelType m_Constant;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkConstantPadImageFilter.txx"
#endif

#endif

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
#ifndef __itkBoxSigmaImageFilter_txx
#define __itkBoxSigmaImageFilter_txx

#include "itkBoxSigmaImageFilter.h"
#include "itkProgressAccumulator.h"
#include "itkNumericTraits.h"
#include "itkBoxUtilities.h"

// #include "ioutils.h"

namespace itk
{
template< class TInputImage, class TOutputImage >
BoxSigmaImageFilter< TInputImage, TOutputImage >
::BoxSigmaImageFilter()
{}

template< class TInputImage, class TOutputImage >
void
BoxSigmaImageFilter< TInputImage, TOutputImage >
::ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread, int threadId)
{
  // Accumulate type is too small
  typedef typename itk::NumericTraits< PixelType >::RealType             AccValueType;
  typedef typename itk::Vector< AccValueType, 2 >                        AccPixType;
  typedef typename itk::Image< AccPixType, TInputImage::ImageDimension > AccumImageType;

  typename TInputImage::SizeType internalRadius;
  for ( unsigned int i = 0; i < TInputImage::ImageDimension; i++ )
    {
    internalRadius[i] = this->GetRadius()[i] + 1;
    }

  const InputImageType *inputImage = this->GetInput();
  OutputImageType *     outputImage = this->GetOutput();
  RegionType            accumRegion = outputRegionForThread;
  accumRegion.PadByRadius(internalRadius);
  accumRegion.Crop( inputImage->GetRequestedRegion() );

  ProgressReporter progress( this, threadId, 2 * accumRegion.GetNumberOfPixels() );

  typename AccumImageType::Pointer accImage = AccumImageType::New();
  accImage->SetRegions(accumRegion);
  accImage->Allocate();

  BoxSquareAccumulateFunction< TInputImage, AccumImageType >(inputImage, accImage,
                                                             accumRegion,
                                                             accumRegion,
                                                             progress);
  BoxSigmaCalculatorFunction< AccumImageType, TOutputImage >(accImage, outputImage,
                                                             accumRegion,
                                                             outputRegionForThread,
                                                             this->GetRadius(),
                                                             progress);
}
} // end namespace itk
#endif

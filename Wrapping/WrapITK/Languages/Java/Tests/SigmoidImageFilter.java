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

/**
 *  Example on the use of the SigmoidImageFilter
 *
 */

import org.itk.io.*;
import org.itk.intensityfilters.*;

public class SigmoidImageFilter
{
  public static void main( String argv[] )
  {
    System.out.println("SigmoidImageFilter Example");

    itkImageFileReaderIUS2 reader = new itkImageFileReaderIUS2();
    itkImageFileWriterIUS2 writer = new itkImageFileWriterIUS2();

    itkSigmoidImageFilterIUS2IUS2 filter = new itkSigmoidImageFilterIUS2IUS2();

    filter.SetInput( reader.GetOutput() );
    writer.SetInput( filter.GetOutput() );

    reader.SetFileName( argv[0] );
    writer.SetFileName( argv[1] );

    filter.SetOutputMinimum( Short.parseShort( argv[2] ) );
    filter.SetOutputMaximum( Short.parseShort( argv[3] ) );

    filter.SetAlpha( Float.parseFloat( argv[4] ) );
    filter.SetBeta(  Float.parseFloat( argv[5] ) );

    writer.Update();
  }

}

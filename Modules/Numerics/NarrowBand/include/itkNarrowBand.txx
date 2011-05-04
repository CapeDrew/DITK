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
#ifndef __itkNarrowBand_txx
#define __itkNarrowBand_txx
#include "itkNarrowBand.h"
#include "vcl_cmath.h"
#include <math.h>

namespace itk
{
#if !defined( CABLE_CONFIGURATION )
template< class NodeType >
std::vector< ITK_TYPENAME NarrowBand< NodeType >::RegionType >
NarrowBand< NodeType >
::SplitBand(unsigned int n)
{
  unsigned int i;

  std::vector< RegionType > regionList;
  if ( n > static_cast< unsigned int >( m_NodeContainer.size() ) )
    {
    n = static_cast< unsigned int >( m_NodeContainer.size() );
    }
  unsigned int regionsize =
    static_cast< unsigned int >( vcl_floor( static_cast< float >( m_NodeContainer.size() ) / static_cast< float >( n ) ) );
  if ( regionsize == 0 )
    {
    regionsize = 1;
    }
  RegionType region;
  Iterator   pos = this->Begin();

  for ( i = 0; i < n; i++ )
    {
    region.Begin = pos;
    pos += regionsize;

    if ( i != n - 1 )
      {
      region.End = pos;
      }
    else
      {
      region.End = this->End();
      }

    regionList.push_back(region);
    }

  return regionList;
}

#endif
} // end namespace itk

#endif

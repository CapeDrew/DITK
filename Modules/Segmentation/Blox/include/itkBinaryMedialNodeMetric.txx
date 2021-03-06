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
#ifndef __itkBinaryMedialNodeMetric_txx
#define __itkBinaryMedialNodeMetric_txx

#include "itkBinaryMedialNodeMetric.h"
#include "vnl/vnl_vector_fixed.h"

namespace itk
{
/**
 * Constructor
 */
template< int VDimensions >
BinaryMedialNodeMetric< VDimensions >
::BinaryMedialNodeMetric()
{
  m_Result = 0.0;
  m_ShowCalc = false;
}

/**
 *
 */
template< int VDimensions >
void
BinaryMedialNodeMetric< VDimensions >
::OrderValues(void)
{
  //initialize smallest value above 1, so all values will be smaller that its
  // initial value
  float smallest_value;
  int   smallest_index;
  int   smallest_key;

  for ( int i = 0; i < VDimensions * 2; i++ )
    {
    // reset smallest trackers
    smallest_value = 1.1;
    smallest_index = 0;
    smallest_key = 0;

    // find the smallest remaining value
    for ( int j = 0; j < VDimensions; j++ )
      {
      if ( m_EigenA[j] < smallest_value )
        {
        smallest_value = m_EigenA[j];
        smallest_key = 1;
        smallest_index = j;
        }
      if ( m_EigenB[j] < smallest_value )
        {
        smallest_value = m_EigenB[j];
        smallest_key = -1;
        smallest_index = j;
        }
      }

    // now put that smallest value in the combined array and remove it from
    // the original array
    if ( smallest_key == 1 )
      {
      int k = 0;
      while ( m_CombinedEigenValues[k] != EMPTY )
        {
        k++;
        }                                           //gets next empty index of
                                                    // combined_eigens

      m_CombinedEigenValues[k] = m_EigenA[smallest_index];
      m_CombinedDistanceValues[k] = m_DistanceVectorA[smallest_index];
      m_EigenA[smallest_index] = EMPTY;
      m_CombinedEigensKey[k] = smallest_key;
      }
    else if ( smallest_key == -1 )
      {
      int k = 0;
      while ( m_CombinedEigenValues[k] != EMPTY )
        {
        k++;
        }                                           //gets next empty index of
                                                    // combined_eigens

      m_CombinedEigenValues[k] = m_EigenB[smallest_index];
      m_CombinedDistanceValues[k] = m_DistanceVectorB[smallest_index];
      m_EigenB[smallest_index] = EMPTY;
      m_CombinedEigensKey[k] = smallest_key;
      }
    }
}

/**
 *
 */
template< int VDimensions >
void
BinaryMedialNodeMetric< VDimensions >
::Initialize(void)
{
  //itkDebugMacro(<< "itkBinaryMedialNodeMetric::Initialize() called");
  m_Result = 0.0;

  //initialize individual lists to EMPTY
  for ( int i = 0; i < VDimensions; i++ )
    {
    m_EigenA[i] = EMPTY;
    m_EigenB[i] = EMPTY;
    m_DistanceVectorA[i] = EMPTY;
    m_DistanceVectorB[i] = EMPTY;
    }

  //initialize combined lists to EMPTY
  for ( int i = 0; i < VDimensions * 2; i++ )
    {
    m_CombinedEigenValues[i] = EMPTY;
    m_CombinedDistanceValues[i] = EMPTY;
    m_CombinedEigensKey[i] = EMPTY;
    }

  //Get eigen values from first nodes
  m_EigenA = m_NodeA1->GetVotedEigenvalues();
  m_EigenB = m_NodeB1->GetVotedEigenvalues();

  //Initialize F value arrays by getting components of distance between nodes 1
  // and 2
  PositionType LocationA1;
  PositionType LocationA2;
  PositionType LocationB1;
  PositionType LocationB2;
  double       distanceA = 0;
  double       distanceB = 0;

  //get locations of medial nods
  LocationA1 = m_NodeA1->GetVotedLocation();
  LocationA2 = m_NodeA2->GetVotedLocation();
  LocationB1 = m_NodeB1->GetVotedLocation();
  LocationB2 = m_NodeB2->GetVotedLocation();

  //calculate distance vectors
  for ( int j = 0; j < VDimensions; j++ )
    {
    m_DistanceVectorA[j] = LocationA1[j] - LocationA2[j];
    m_DistanceVectorB[j] = LocationB1[j] - LocationB2[j];

    distanceA += vcl_pow(m_DistanceVectorA[j], 2);
    distanceB += vcl_pow(m_DistanceVectorB[j], 2);
    }

  distanceA = vcl_sqrt(distanceA);
  distanceB = vcl_sqrt(distanceB);

  for ( int k = 0; k < VDimensions; k++ )
    {
    m_DistanceVectorA[k] /= distanceA;
    m_DistanceVectorB[k] /= distanceB;

    m_DistanceVectorA[k] = vcl_fabs(m_DistanceVectorA[k]);
    m_DistanceVectorB[k] = vcl_fabs(m_DistanceVectorB[k]);
    }

  OrderValues();

  if ( m_ShowCalc == true ) { PrintCombinedEigens(); }

  for ( int m = 0; m < VDimensions * 2; m++ )
    {
    m_Result += ( m_CombinedDistanceValues[m] * m_CombinedEigenValues[m] ) * m_CombinedEigensKey[m];
    }

  m_Result = 1.0 - vcl_fabs(m_Result);

  //std::cout << "\n\nTotal Metric Difference:  " << m_Result << std::endl;

  // Returns a number between 0 and 1.0, where 1.0 is a perfect match
}

/**
 * Function to print the list of combined eigen values.
 */
template< int VDimensions >
void
BinaryMedialNodeMetric< VDimensions >
::PrintCombinedEigens()
{
  std::cout << "eigen\t\tsource\t\tdist-value" << std::endl;
  std::cout << "---------------------------------------" << std::endl;
  for ( int i = 0; i < VDimensions * 2; i++ )
    {
    std::cout << m_CombinedEigenValues[i] << "\t";
    if ( m_CombinedEigensKey[i] == 1 ) { std::cout << "\tA" << "\t\t" << m_CombinedDistanceValues[i] << std::endl; }
    else if ( m_CombinedEigensKey[i] == -1 )
      {
      std::cout << "\tB" << "\t\t" << m_CombinedDistanceValues[i] << std::endl;
      }
    }
}

/**
 *
 */
template< int VDimensions >
void
BinaryMedialNodeMetric< VDimensions >
::SetMedialNodes(MedialNode *NodeA1, MedialNode *NodeA2, MedialNode *NodeB1, MedialNode *NodeB2)
{
  m_NodeA1 = NodeA1;
  m_NodeA2 = NodeA2;
  m_NodeB1 = NodeB1;
  m_NodeB2 = NodeB2;
}

/**
 * PrintSelf
 */
template< int VDimensions >
void
BinaryMedialNodeMetric< VDimensions >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Result: " << m_Result << std::endl;
}
} // end namespace itk

#endif

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
#ifndef __itkMetaEllipseConverter_txx
#define __itkMetaEllipseConverter_txx

#include "itkMetaEllipseConverter.h"

namespace itk
{
/** Constructor */
template< unsigned int NDimensions >
MetaEllipseConverter< NDimensions >
::MetaEllipseConverter()
{}

/** Convert a metaEllipse into an ellipse SpatialObject  */
template< unsigned int NDimensions >
typename MetaEllipseConverter< NDimensions >::SpatialObjectPointer
MetaEllipseConverter< NDimensions >
::MetaEllipseToEllipseSpatialObject(MetaEllipse *ellipse)
{
  SpatialObjectPointer spatialObject = SpatialObjectType::New();

  double spacing[NDimensions];

  typename SpatialObjectType::ArrayType radius;
  for ( unsigned int i = 0; i < NDimensions; i++ )
    {
    radius[i] = ellipse->Radius()[i];
    spacing[i] = ellipse->ElementSpacing()[i];
    }

  spatialObject->GetIndexToObjectTransform()->SetScaleComponent(spacing);
  spatialObject->SetRadius(radius);
  spatialObject->GetProperty()->SetName( ellipse->Name() );
  spatialObject->SetId( ellipse->ID() );
  spatialObject->SetParentId( ellipse->ParentID() );
  spatialObject->GetProperty()->SetRed(ellipse->Color()[0]);
  spatialObject->GetProperty()->SetGreen(ellipse->Color()[1]);
  spatialObject->GetProperty()->SetBlue(ellipse->Color()[2]);
  spatialObject->GetProperty()->SetAlpha(ellipse->Color()[3]);

  return spatialObject;
}

/** Convert an ellipse SpatialObject into a metaEllipse */
template< unsigned int NDimensions >
MetaEllipse *
MetaEllipseConverter< NDimensions >
::EllipseSpatialObjectToMetaEllipse(SpatialObjectType *spatialObject)
{
  MetaEllipse *ellipse = new MetaEllipse(NDimensions);

  float *radius = new float[NDimensions];

  for ( unsigned int i = 0; i < NDimensions; i++ )
    {
    radius[i] = spatialObject->GetRadius()[i];
    }

  if ( spatialObject->GetParent() )
    {
    ellipse->ParentID( spatialObject->GetParent()->GetId() );
    }
  ellipse->Radius(radius);
  ellipse->ID( spatialObject->GetId() );

  ellipse->Color( spatialObject->GetProperty()->GetRed(),
                  spatialObject->GetProperty()->GetGreen(),
                  spatialObject->GetProperty()->GetBlue(),
                  spatialObject->GetProperty()->GetAlpha() );

  for ( unsigned int i = 0; i < NDimensions; i++ )
    {
    ellipse->ElementSpacing(i, spatialObject->GetIndexToObjectTransform()
                            ->GetScaleComponent()[i]);
    }

  delete[] radius;
  return ellipse;
}

/** Read a meta file give the type */
template< unsigned int NDimensions >
typename MetaEllipseConverter< NDimensions >::SpatialObjectPointer
MetaEllipseConverter< NDimensions >
::ReadMeta(const char *name)
{
  SpatialObjectPointer spatialObject;
  MetaEllipse *        ellipse = new MetaEllipse();

  ellipse->Read(name);
  spatialObject = MetaEllipseToEllipseSpatialObject(ellipse);

  return spatialObject;
}

/** Write a meta ellipse file */
template< unsigned int NDimensions >
bool
MetaEllipseConverter< NDimensions >
::WriteMeta(SpatialObjectType *spatialObject, const char *name)
{
  MetaEllipse *ellipse = EllipseSpatialObjectToMetaEllipse(spatialObject);

  ellipse->Write(name);
  return true;
}
} // end namespace itk

#endif

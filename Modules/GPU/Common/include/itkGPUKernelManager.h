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

//
// GPU Kernel Manager Class
//

#ifndef __itkGPUKernelManager_h
#define __itkGPUKernelManager_h

#include <vector>
#include <itkLightObject.h>
#include <itkObjectFactory.h>
#include "itkOclUtil.h"
#include "itkGPUImage.h"
#include "itkGPUContextManager.h"
#include "itkGPUDataManager.h"

namespace itk
{
  class ITK_EXPORT GPUKernelManager: public LightObject
  {
  public:

    struct KernelArgumentList
    {
      bool m_IsReady;
      GPUDataManager::Pointer m_GPUDataManager;
    };

    typedef GPUKernelManager          Self;
    typedef LightObject               Superclass;
    typedef SmartPointer<Self>        Pointer;
    typedef SmartPointer<const Self>  ConstPointer;

    itkNewMacro(Self);
    itkTypeMacro(GPUKernelManager, LightObject);

    bool LoadProgramFromFile(const char* filename, const char* cPreamble="");

    int  CreateKernel(const char* kernelName);

    bool SetKernelArg(int kernelIdx, cl_uint argIdx, size_t argSize, const void* argVal);
    bool SetKernelArgWithImage(int kernelIdx, cl_uint argIdx, GPUDataManager::Pointer manager);

    bool LaunchKernel(int kernelIdx, int dim, size_t *globalWorkSize, size_t *localWorkSize);
    bool LaunchKernel1D(int kernelIdx, size_t globalWorkSize, size_t localWorkSize);
    bool LaunchKernel2D(int kernelIdx,
      size_t globalWorkSizeX, size_t globalWorkSizeY,
      size_t localWorkSizeX,  size_t localWorkSizeY );
    bool LaunchKernel3D(int kernelIdx,
      size_t globalWorkSizeX, size_t globalWorkSizeY, size_t globalWorkSizeZ,
      size_t localWorkSizeX,  size_t localWorkSizeY, size_t localWorkSizeZ );

    void SetCurrentCommandQueue( int queueid );

    int  GetCurrentCommandQueueID();

  protected:
    GPUKernelManager();
    virtual ~GPUKernelManager() {};

    bool CheckArgumentReady(int kernelIdx);
    void ResetArguments(int kernelIdx);

  private:
    GPUKernelManager(const Self&); //purposely not implemented
    void operator=(const Self&);

    cl_program            m_Program;

    GPUContextManager *   m_Manager;
    int                   m_CommandQueueId;

    std::vector< cl_kernel >                              m_KernelContainer;
    std::vector< std::vector< KernelArgumentList > >      m_KernelArgumentReady;
  };
}

#endif

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkVolumeTextureMapper.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkVolumeTextureMapper
 * @brief   Abstract class for a volume mapper
 *
 *
 * vtkVolumeTextureMapper is the abstract definition of a volume mapper
 * that uses a texture mapping approach.
 *
 * @sa
 * vtkVolumeMapper
*/

#ifndef vtkVolumeTextureMapper_h
#define vtkVolumeTextureMapper_h

#include "vtkRenderingVolumeModule.h" // For export macro
#include "vtkVolumeMapper.h"

class vtkEncodedGradientEstimator;
class vtkEncodedGradientShader;
class vtkRenderWindow;
class vtkRenderer;
class vtkVolume;

class VTKRENDERINGVOLUME_EXPORT vtkVolumeTextureMapper : public vtkVolumeMapper
{
public:
  vtkTypeMacro(vtkVolumeTextureMapper,vtkVolumeMapper);
  void PrintSelf( ostream& os, vtkIndent indent) override;

  //@{
  /**
   * Set / Get the gradient estimator used to estimate normals
   */
  virtual void SetGradientEstimator( vtkEncodedGradientEstimator *gradest );
  vtkGetObjectMacro( GradientEstimator, vtkEncodedGradientEstimator );
  //@}

  //@{
  /**
   * Get the gradient shader.
   */
  vtkGetObjectMacro( GradientShader, vtkEncodedGradientShader );
  //@}

  //@{
  /**
   * Allow access to the arrays / variables from the templated functions in the
   * subclasses.
   */
  float *GetGradientOpacityArray(){return this->GradientOpacityArray;};
  unsigned char *GetRGBAArray(){return this->RGBAArray;};
  float *GetRedDiffuseShadingTable(){return this->RedDiffuseShadingTable;};
  float *GetGreenDiffuseShadingTable(){return this->GreenDiffuseShadingTable;};
  float *GetBlueDiffuseShadingTable(){return this->BlueDiffuseShadingTable;};
  float *GetRedSpecularShadingTable(){return this->RedSpecularShadingTable;};
  float *GetGreenSpecularShadingTable(){return this->GreenSpecularShadingTable;};
  float *GetBlueSpecularShadingTable(){return this->BlueSpecularShadingTable;};
  unsigned short *GetEncodedNormals(){return this->EncodedNormals;};
  unsigned char *GetGradientMagnitudes(){return this->GradientMagnitudes;};
  vtkGetMacro( Shade, int );
  vtkGetObjectMacro( RenderWindow, vtkRenderWindow );
  vtkGetVectorMacro( DataOrigin, double, 3 );
  vtkGetVectorMacro( DataSpacing, double, 3 );
  //@}

  /**
   * WARNING: INTERNAL METHOD - NOT INTENDED FOR GENERAL USE
   * DO NOT USE THIS METHOD OUTSIDE OF THE RENDERING PROCESS
   * Render the volume
   */
  void Render(vtkRenderer *ren, vtkVolume *vol) override =0;

  //@{
  /**
   * WARNING: INTERNAL METHOD - NOT INTENDED FOR GENERAL USE
   * Values needed by the volume
   */
  float GetGradientMagnitudeScale() override;
  float GetGradientMagnitudeBias() override;
  float GetGradientMagnitudeScale(int) override
    { return this->GetGradientMagnitudeScale(); };
  float GetGradientMagnitudeBias(int) override
    { return this->GetGradientMagnitudeBias(); };
  //@}

  /**
   * see vtkAlgorithm for details
   */
  int ProcessRequest(vtkInformation*,
                             vtkInformationVector**,
                             vtkInformationVector*) override;

protected:
  vtkVolumeTextureMapper();
  ~vtkVolumeTextureMapper() override;

  void InitializeRender( vtkRenderer *ren, vtkVolume *vol );

  void ReportReferences(vtkGarbageCollector*) override;

  // Objects / variables  needed for shading / gradient magnitude opacity
  vtkEncodedGradientEstimator  *GradientEstimator;
  vtkEncodedGradientShader     *GradientShader;
  int                           Shade;

  float          *GradientOpacityArray;
  unsigned char  *RGBAArray;
  int             ArraySize;
  int             NumberOfComponents;

  float          *RedDiffuseShadingTable;
  float          *GreenDiffuseShadingTable;
  float          *BlueDiffuseShadingTable;
  float          *RedSpecularShadingTable;
  float          *GreenSpecularShadingTable;
  float          *BlueSpecularShadingTable;

  double          DataOrigin[3];
  double          DataSpacing[3];

  unsigned short *EncodedNormals;
  unsigned char  *GradientMagnitudes;

  float           SampleDistance;

  vtkRenderWindow *RenderWindow;
private:
  vtkVolumeTextureMapper(const vtkVolumeTextureMapper&) = delete;
  void operator=(const vtkVolumeTextureMapper&) = delete;
};


#endif



/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkBMPWriter.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkBMPWriter
 * @brief   Writes Windows BMP files.
 *
 * vtkBMPWriter writes BMP files. The data type
 * of the file is unsigned char regardless of the input type.
 *
 * @sa
 * vtkBMPReader
*/

#ifndef vtkBMPWriter_h
#define vtkBMPWriter_h

#include "vtkIOImageModule.h" // For export macro
#include "vtkImageWriter.h"

class VTKIOIMAGE_EXPORT vtkBMPWriter : public vtkImageWriter
{
public:
  static vtkBMPWriter *New();
  vtkTypeMacro(vtkBMPWriter,vtkImageWriter);
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  vtkBMPWriter();
  ~vtkBMPWriter() override {}

  void WriteFile(ofstream *file, vtkImageData *data, int ext[6], int wExt[6]) override;
  void WriteFileHeader(ofstream *, vtkImageData *, int wExt[6]) override;
private:
  vtkBMPWriter(const vtkBMPWriter&) = delete;
  void operator=(const vtkBMPWriter&) = delete;
};

#endif



//
//  level2_vtk.cpp
//
//
//  Created by Christopher Mitchell on 3/6/12.
//  Copyright (c) 2012 Los Alamos National Laboratory. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sys/time.h>
#include "vtkRTAnalyticSource.h"
#include "vtkContourFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkImageData.h"
#include "vtkFloatArray.h"
#include "vtkXMLImageDataWriter.h"
#include "vtkPointData.h"

#include "vtkTimerLog.h"

#include <unistd.h>

#include <GL/glx.h>

using namespace std;

timespec diff(timespec start, timespec end);

__inline__ uint64_t tsc() {
  uint32_t lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32 | lo);
}

void write_pixels(vtkFloatArray* data, int x, int y, int idx)
{
  vtkImageData* id = vtkImageData::New();
  id->AllocateScalars(VTK_FLOAT, 4);
  id->SetDimensions(x, y, 1);
  id->GetPointData()->SetScalars(data);
  vtkXMLImageDataWriter* writer = vtkXMLImageDataWriter::New();
  writer->SetInputData(id);
  char filename[20];
  sprintf(filename, "image%d.vti", idx);
  writer->SetFileName(filename);
  writer->SetDataModeToAppended();
  writer->Write();
  writer->Delete();
  id->Delete();
}

int main(int argc, char * argv[]){
  //Generate a wavelet source with the number of triangles specified in the command line
  int numTris = atoi(argv[1]);
  vtkRTAnalyticSource * wavelet = vtkRTAnalyticSource::New();
  wavelet->SetWholeExtent(-100, 100, -100, 100, -100, 100);
  wavelet->SetXMag(10.0);
  wavelet->SetYMag(18.0);
  wavelet->SetZMag(5.0);
  wavelet->SetCenter(0.0,0.0,0.0);
  wavelet->SetMaximum(255.0);
  wavelet->SetStandardDeviation(0.5);
  wavelet->SetXFreq(60.0);
  wavelet->SetYFreq(30.0);
  wavelet->SetZFreq(40.0);

  //Process a countour of the surface
  vector<double> triangles;
  if(numTris == 1){
    triangles.push_back(33);
    triangles.push_back(66);
    triangles.push_back(115);
    triangles.push_back(120);
  }
  else if(numTris == 2){
    triangles.push_back(35);
    triangles.push_back(57);
    triangles.push_back(102);
    triangles.push_back(111);
    triangles.push_back(129);
    triangles.push_back(153);
  }
  else if(numTris == 4){
    triangles.push_back(34);
    triangles.push_back(45);
    triangles.push_back(50);
    triangles.push_back(130);
    triangles.push_back(149);
    triangles.push_back(150);
    triangles.push_back(153);
    triangles.push_back(156);
    triangles.push_back(159);
  }
  else if(numTris == 8){
    triangles.push_back(159);
    triangles.push_back(156);
    triangles.push_back(153);
    triangles.push_back(152);
    triangles.push_back(150);
    triangles.push_back(147);
    triangles.push_back(144);
    triangles.push_back(141);
    triangles.push_back(138);
    triangles.push_back(135);
    triangles.push_back(131);
    triangles.push_back(127);
    triangles.push_back(86);
    triangles.push_back(47);
    triangles.push_back(40);
    triangles.push_back(37);
    triangles.push_back(36);
    triangles.push_back(35);
  }
  else if(numTris == 16){
    triangles.push_back(35);
    triangles.push_back(36);
    triangles.push_back(43);
    triangles.push_back(144);
    triangles.push_back(145);
    triangles.push_back(146);
    triangles.push_back(148);
    triangles.push_back(149);
    triangles.push_back(150);
    triangles.push_back(151);
    triangles.push_back(152);
    triangles.push_back(153);
    triangles.push_back(154);
    triangles.push_back(155);
    triangles.push_back(156);
    triangles.push_back(158);
    triangles.push_back(159);
    triangles.push_back(160);
    triangles.push_back(161);
    triangles.push_back(162);
    triangles.push_back(163);
    triangles.push_back(164);
    triangles.push_back(167);
    triangles.push_back(168);
    triangles.push_back(169);
    triangles.push_back(170);
    triangles.push_back(173);
  }

  vtkContourFilter * contour = vtkContourFilter::New();

  for(int i = 0; i < triangles.size(); i++){
    contour->SetValue(i, triangles[i]);
  }

  contour->SetInputConnection(wavelet->GetOutputPort());

  //Render the resulting contour and rotate it
  vtkPolyDataMapper *mbMapper = vtkPolyDataMapper::New();
  mbMapper->SetInputConnection( contour->GetOutputPort(0) );
  mbMapper->SetScalarVisibility(0);

  vtkActor *mbActor = vtkActor::New();
  mbActor->SetMapper(mbMapper);

  //Setup the Renderer
  vtkRenderer *ren1= vtkRenderer::New();
  ren1->AddActor( mbActor );
  ren1->SetBackground( 0.1, 0.2, 0.4 );

  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer( ren1 );
  renWin->SetSize( 1024, 1024 );
  mbMapper->SetImmediateModeRendering(false);
  ren1->ResetCamera();
  renWin->Render();

  vtkFloatArray* fa = vtkFloatArray::New();

  uint64_t t1 = tsc();
  for(int i = 0; i < 1000; ++i)
  {
    ren1->GetActiveCamera()->Azimuth(1);
    //glClearColor (0.0,0.0,0.0,1.0);
    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renWin->Render();
  }

  uint64_t t2 = tsc();
  std::cerr << (t2 - t1)/2527069000.0 << "\n";

  //Delete Objects Created
  wavelet->Delete();
  contour->Delete();
  mbMapper->Delete();
  mbActor->Delete();
  ren1->Delete();
  renWin->Delete();

  return 0;
}

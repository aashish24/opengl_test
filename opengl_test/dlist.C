#include <iostream>
#include <GL/glx.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <vtkRenderWindow.h>
#include <vtkTimerLog.h>

GLuint cubelist;
Display *dpy;
int win;

float STEP, SIZE;
#define KNT  5

__inline__ uint64_t tsc() {
  uint32_t lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32 | lo);
}

void render();
void setup_render();

void setup_states()
{
  glEnable(GL_LIGHTING);
  glClearColor (0.0,0.0,0.0,1.0);
}

void build_list(void)
{
  cubelist = glGenLists(1);
  glNewList(cubelist,GL_COMPILE);
  glBegin(GL_TRIANGLES);
  render();
  glEnd();
  glEndList();
}

void display (void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glRotatef(01, 0.0, 1.0, 0.0);  
  glCallList(cubelist);
  //  glXSwapBuffers(dpy, win);
}

int main (int argc, char **argv)
{
  vtkRenderWindow* rw = vtkRenderWindow::New();
  rw->SetSize(1024, 1024);
  rw->Render();

  setup_render();
  setup_states();

  uint64_t t0 = tsc();

  build_list();

  uint64_t t1 = tsc();

  for (int i = 0; i < 1000; ++i)
    {
    display();
    rw->Frame();
    }

  vtkTimerLog::DumpLogWithIndents(&std::cout, 0.0000001);

  uint64_t t2 = tsc();
  std::cerr << (t1 - t0)/2527069000.0 << " " << (t2 - t1)/2527069000.0 << "\n";

  exit(1);
}

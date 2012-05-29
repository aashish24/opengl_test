#include <iostream>
#include <GL/glx.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

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
  glXSwapBuffers(dpy, win);
}

int main (int argc, char **argv)
{
  dpy = XOpenDisplay(getenv("DISPLAY")?getenv("DISPLAY"):"0.0");
   if (! dpy)
   {
       std::cerr << "error opening display\n";
       exit(1);
   }

   int wattr[] = {
       GLX_RGBA,
       GLX_DOUBLEBUFFER,
       GLX_RED_SIZE,    8,
       GLX_GREEN_SIZE,  8,
       GLX_BLUE_SIZE,   8,
       None
   };

   XVisualInfo *vinf = glXChooseVisual(dpy, DefaultScreen(dpy), wattr);
   if (! vinf)
   {
     std::cerr << "error getting visual\n";
     exit(1);
   }

   GLXContext ctx = glXCreateContext(dpy, vinf, NULL, 1);
   if (! ctx)
   {
     std::cerr << "unable to create glX context\n";
     exit(1);
   }

   XSetWindowAttributes swaattr;
   swaattr.colormap = XCreateColormap(dpy, DefaultRootWindow(dpy), vinf->visual, AllocNone);

   win = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0, 1024, 1024, 0,
     24, InputOutput, vinf->visual, CWColormap, &swaattr);

   if (! win)
   {
     std::cerr << "unable to create window\n";
     exit(1);
   }

  XMapRaised(dpy, win);

  glXMakeCurrent(dpy, win, ctx);

  setup_render();
  setup_states();

  uint64_t t0 = tsc();

  build_list();

  uint64_t t1 = tsc();

  for (int i = 0; i < 1000; ++i)
    {
    display();    
    }

  uint64_t t2 = tsc();
  std::cerr << (t1 - t0)/2527069000.0 << " " << (t2 - t1)/2527069000.0 << "\n";

  exit(1);
}

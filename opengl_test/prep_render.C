#include <GL/glx.h>

void setup_render()
{
  glMatrixMode(GL_MODELVIEW);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  //  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_POLYGON_SMOOTH);
  glEnable(GL_NORMALIZE);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glAlphaFunc(GL_GREATER, 0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  {
  float v[4] = {1, 1,1, 1};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, v);
  }
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  glDisable(GL_LIGHT3);
  glDisable(GL_LIGHT4);
  glDisable(GL_LIGHT5);
  glDisable(GL_LIGHT6);
  glDisable(GL_LIGHT7);
  glDrawBuffer(GL_BACK);
  glReadBuffer(GL_BACK);
  glViewport(0, 0, 1024, 1024);
  glEnable(GL_SCISSOR_TEST);
  glScissor(0, 0, 1024, 1024);
  glMatrixMode(GL_PROJECTION);
  {
  double m[16] = {3.73205, 0, 0, 0, 0, 3.73205, 0, 0, 0, 0, -2.98838, -1, 0, 0, -1848.7, 0};
  glLoadMatrixd(m);
  }
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  {
  double m[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, -669.213, 1};
  glMultMatrixd(m);
  }
  glClearColor(0.1, 0.2, 0.4, 0);
  glClearDepth(1);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  {
  float v[4] = {0, 0, 0, 1};
  glLightfv(GL_LIGHT0, GL_AMBIENT, v);
  }
  {
  float v[4] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, v);
  }
  {
  float v[4] = {1, 1, 1, 1};
  glLightfv(GL_LIGHT0, GL_SPECULAR, v);
  }
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
  {
  float v[4] = {-0, -0, 669.213, 0};
  glLightfv(GL_LIGHT0, GL_POSITION, v);
  }
  glEnable(GL_LIGHT0);
  glPopMatrix();
  glEnable(GL_LIGHTING);
  glMatrixMode(GL_MODELVIEW);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_COLOR_MATERIAL);
  glDisable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  {
  float v[4] = {0, 0, 0, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v);
  }
  {
  float v[4] = {1, 1, 1, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v);
  }
  {
  float v[4] = {0, 0, 0, 1};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v);
  }
  {
  float v = 1;
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &v);
  }
  glShadeModel(GL_SMOOTH);
  {
  double v[4] = {1, 1, 1, 1};
  glColor4dv(v);
  }
  glPointSize(1);
  glLineWidth(1);
  glLineStipple(1, 65535);
  glDisable(GL_LINE_STIPPLE);
  glEnable(GL_LIGHTING);
  glDepthMask(true);
  glDisable(GL_COLOR_MATERIAL);
}

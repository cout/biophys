#include "System.hpp"

#include <GL/glut.h>
// #include <GL/glc.h>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <sstream>

namespace
{

std::auto_ptr<System> the_system;

// GLint glc_context;
// GLint glc_font;

double rotate_x = 0.0;
double rotate_y = 90.0;

int width = 500;
int height = 500;

void init_lighting()
{
  GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

  GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

  GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, position);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void init_fonts()
{
  // glc_context = glcGenContext();
  // glc_font = glcGenFontID();
  // glcNewFontFromFamily(glc_font, "Palatino");
  // glcFontFace(glc_font, "Normal");
}

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glShadeModel(GL_SMOOTH);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glBlendFunc (GL_ONE_MINUS_DST_COLOR, GL_ONE);
  // glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_COLOR);

  // glAlphaFunc(GL_GREATER, 0);
  // glEnable(GL_ALPHA_TEST);

  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  init_lighting();
  init_fonts();
  the_system.reset(new System);
  the_system->reset();
}

void render_stroke_text(void * font, char const * text)
{
  for(; *text != '\0'; ++text)
  {
    glutStrokeCharacter(font, *text);
  }
}

void render_bitmap_text(void * font, char const * text)
{
  for(; *text != '\0'; ++text)
  {
    glutBitmapCharacter(font, *text);
  }
}

void draw_world()
{
  glColor3d (1.0, 1.0, 1.0);
  glLoadIdentity ();
  gluLookAt (
      0.0, 0.0, 3.0, // camera position
      0.0, 0.0, 0.0, // camera focal point
      0.0, 1.0, 0.0); // up vector
  glRotatef(rotate_x, 0, 1, 0);
  glRotatef(rotate_y, 1, 0, 0);
  glScalef (1.0, 1.0, 1.0);

  the_system->draw();
}

void draw_legend()
{
#if 0
  glcContext(glc_context);
  glcFont(glc_font);

  glPushMatrix();
  glcScale(12.0, 12.0);
  glColor3f(1.0, 0.0, 1.0);
  glRasterPos2f(50.0, 50.0);
  glcRenderString("Hello");
  glPopMatrix();
#endif

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glColor4f(0.8, 0.9, 0.9, 1.0);

  {
    glRasterPos2f(2, height-20);
    std::stringstream strm;
    strm << "Sodium inside: " << the_system->cell().sodium_characteristics.ions_inside_cell;
    render_bitmap_text(GLUT_BITMAP_HELVETICA_18, strm.str().c_str());
  }

  {
    glRasterPos2f(2, height-40);
    std::stringstream strm;
    strm << "Sodium outside: " << the_system->cell().sodium_characteristics.ions_outside_cell;
    render_bitmap_text(GLUT_BITMAP_HELVETICA_18, strm.str().c_str());
  }

  {
    glRasterPos2f(2, height-60);
    std::stringstream strm;
    strm << "Potassium inside: " << the_system->cell().potassium_characteristics.ions_inside_cell;
    render_bitmap_text(GLUT_BITMAP_HELVETICA_18, strm.str().c_str());
  }

  {
    glRasterPos2f(2, height-80);
    std::stringstream strm;
    strm << "Potassium outside: " << the_system->cell().potassium_characteristics.ions_outside_cell;
    render_bitmap_text(GLUT_BITMAP_HELVETICA_18, strm.str().c_str());
  }

  glPopAttrib();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void display()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_world();
  draw_legend();

  // -- Flush --
  glutSwapBuffers();
  glFlush ();
}

void reshape(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (float)w / h, 1 /* nearplane */, 1000 /* farplane */);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
  }
}

static int last_x = 0;
static int last_y = 0;

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      last_x = x;
      last_y = y;
    }
  }
}

void motion(int x, int y)
{
  rotate_x = std::fmod(rotate_x + x - last_x, 360.0);
  rotate_y = std::fmod(rotate_y + y - last_y, 360.0);
  last_x = x;
  last_y = y;
}

void idle()
{
  the_system->iterate();
  rotate_x += 0.1;
  rotate_y += 0.05;
  glutPostRedisplay();
}

void go()
{
  glutMainLoop();
}

} // namespace

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize (width, height); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   init();

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
   glutIdleFunc(idle);

   go();
   return 0;
}

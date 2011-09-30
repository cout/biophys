#include "System.hpp"

#include <GL/glut.h>

#include <cstdlib>
#include <cmath>

namespace
{

System the_system;

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

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glShadeModel(GL_SMOOTH);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // glAlphaFunc(GL_GREATER, 0);
  // glEnable(GL_ALPHA_TEST);

  glClearDepth(1.0f);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  // glEnable(GL_POINT_SMOOTH);
  // glEnable(GL_LINE_SMOOTH);
  // glHint(GL_POINT_SMOOTH, GL_NICEST);
  // glHint(GL_LINE_SMOOTH, GL_NICEST);

  init_lighting();
  the_system.reset();
}

void display()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d (1.0, 1.0, 1.0);
  glLoadIdentity ();
  gluLookAt (
      0.0, 0.0, 5.0, // camera position
      0.0, 0.0, 0.0, // camera focal point
      0.0, 1.0, 0.0); // up vector
  glScalef (1.0, 2.0, 1.0);

  the_system.draw();

  // -- Flush --
  glutSwapBuffers();
  glFlush ();
}

void reshape(int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
  glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
  }
}

void mouse(int button, int state, int x, int y)
{
}

void idle()
{
  the_system.iterate();
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
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   init();

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);

   go();
   return 0;
}

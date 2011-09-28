#include "Cell.hpp"
#include "Particle_System.hpp"

#include <GL/glut.h>

#include <cstdlib>

namespace
{

double outer_limit = 2.0;
Cell cell;
Particle_System sodium(100);

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

void init_cell()
{
  cell.x = 0.0;
  cell.y = 0.0;
  cell.z = 0.0;
  cell.radius = 1.0;
}

void init_ions()
{
  // Put sodium ions outside the cell
  Particle_System::Particles::iterator it(sodium.particles().begin());
  Particle_System::Particles::iterator end(sodium.particles().end());

  for (; it != end; ++it)
  {
    it->x = cell.x + (((2 * (double)std::rand()) / RAND_MAX) - 1) * outer_limit;
    it->y = cell.y + (((2 * (double)std::rand()) / RAND_MAX) - 1) * outer_limit;
    it->z = cell.z + (((2 * (double)std::rand()) / RAND_MAX) - 1) * outer_limit;
  }
}

void init()
{
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glShadeModel(GL_SMOOTH);

  init_lighting();
  init_cell();
  init_ions();
}

void display()
{
  glClear (GL_COLOR_BUFFER_BIT);
  glColor3d (1.0, 1.0, 1.0);
  glLoadIdentity ();
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glScalef (1.0, 2.0, 1.0);

  // -- Cell --

  GLfloat mcolor[] = { 0.5f, 0.5f, 0.8f, 0.2f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

  glPushMatrix();
  glTranslatef(cell.x, cell.y, cell.z);
  glutSolidSphere(cell.radius, 50, 20);
  glPopMatrix();

  // -- Ions --

  GLfloat pcolor[] = { 0.3f, 0.3f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pcolor);

  glPointSize(2.0);

  Particle_System::Particles::const_iterator it(sodium.particles().begin());
  Particle_System::Particles::const_iterator end(sodium.particles().end());

  glBegin(GL_POINTS);
  for (; it != end; ++it)
  {
    glVertex3d(it->x, it->y, it->z);
  }
  glEnd();

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

void idle()
{
}

void go()
{
  glutMainLoop();
}

} // namespace

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   init();

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);

   go();
   return 0;
}

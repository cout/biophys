#include "Point.hpp"
#include "Cell.hpp"
#include "Particle_System.hpp"

#include <GL/glut.h>

#include <cstdlib>
#include <cmath>

namespace
{

double outer_limit = 2.0;
Cell cell;
Particle_System sodium(10000);
Particle_System potassium(1000);

GLfloat sodium_color[] = { 0.3f, 0.3f, 1.0f, 1.0f };
GLfloat potassium_color[] = { 1.0f, 0.3f, 0.3f, 1.0f };

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

Point random_insphere(double rmin, double rmax)
{
  // TODO: rmin
  double rho = (((2 * (double)std::rand()) / RAND_MAX) - 1) * rmax;
  double theta = M_PI * 2 * ((double)std::rand() / RAND_MAX);
  double phi = M_PI * 2 * ((double)std::rand() / RAND_MAX);

  Point p;
  p.x = rho * sin(theta) * cos(phi);
  p.y = rho * sin(theta) * sin(phi);
  p.z = rho * cos(theta);

  return p;
}

void init_ions()
{
  // Put sodium ions outside the cell
  Particle_System::Particles::iterator it(sodium.particles().begin());
  Particle_System::Particles::iterator end(sodium.particles().end());

  for (; it != end; ++it)
  {
    Point p = random_insphere(cell.radius, outer_limit);

    it->x = cell.x + p.x;
    it->y = cell.y + p.y;
    it->z = cell.z + p.z;
  }

  // Put potassium ions inside the cell
  it = potassium.particles().begin();
  end = potassium.particles().end();

  for (; it != end; ++it)
  {
    Point p = random_insphere(0, cell.radius);

    it->x = cell.x + p.x;
    it->y = cell.y + p.y;
    it->z = cell.z + p.z;
  }
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
  init_cell();
  init_ions();
}

void display()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d (1.0, 1.0, 1.0);
  glLoadIdentity ();
  gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
  glScalef (1.0, 2.0, 1.0);

  // -- Ions --

  glPointSize(2.0);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sodium_color);
  sodium.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, potassium_color);
  potassium.draw();

  // -- Cell --

  GLfloat mcolor[] = { 0.5f, 0.5f, 0.8f, 0.5f };
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

  glPushMatrix();
  glTranslatef(cell.x, cell.y, cell.z);
  glutSolidSphere(cell.radius, 50, 20);
  glPopMatrix();

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
  sodium.random_walk(0.01);
  potassium.random_walk(0.01);
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
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

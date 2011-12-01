#include "System.hpp"
#include "Time.hpp"
#include "Parameters.hpp"
#include "Graph.hpp"

#include <FTGL/ftgl.h>

// #include <GL/glc.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <gtk/gtk.h>
#include <gtkgl/gtkglarea.h>

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace
{

GtkWidget * window;
GtkWidget * event_box;
GtkGLArea * glarea;

Parameters params;
std::auto_ptr<System> the_system;

std::auto_ptr<Graph> voltage_graph;

// GLint glc_context;
// GLint glc_font;

std::auto_ptr<FTFont> font;

double rotate_x = 0.0;
double rotate_y = 90.0;

int width = 500;
int height = 500;

bool rotating = true;

Time last_display_time;
Time last_run_time;
Time sim_time;

void init_lighting()
{
  GLfloat global_ambient[] = { 1.5f, 1.5f, 1.5f, 1.0f };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

  // GLfloat specular[] = {1.0f, 1.0f, 1.0f , 1.0f};
  // glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  // GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };
  // glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

  // GLfloat position[] = { -1.5f, 1.0f, -4.0f, 1.0f };
  // glLightfv(GL_LIGHT0, GL_POSITION, position);

  glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
}

void init_fonts()
{
  // glc_context = glcGenContext();
  // glc_font = glcGenFontID();
  // glcNewFontFromFamily(glc_font, "Palatino");
  // glcFontFace(glc_font, "Normal");
  font.reset(new FTGLTextureFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf"));
  if (font->Error())
  {
    throw std::runtime_error("could not load font");
  }
  font->FaceSize(18);
  font->UseDisplayList(true);
}

void draw_world(Time dt)
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

#define WRITE_LINE(x) \
{ \
  glTranslatef(0, -20, 0); \
  std::stringstream strm; \
  strm << x; \
  ::font->Render(strm.str().c_str()); \
}

void draw_legend(Time dt)
{
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

  glTranslatef(2, height, 0);

  WRITE_LINE("Time (ms): " << sim_time * 1000.0);
  WRITE_LINE("Membrane voltage: " << the_system->cell().membrane_voltage * 1000);
  WRITE_LINE("Sodium permeability: " << the_system->cell().sodium_permeability);
  WRITE_LINE("Potassium permeability: " << the_system->cell().potassium_permeability);
  WRITE_LINE("Sodium inside: " << the_system->cell().sodium_inside);
  WRITE_LINE("Sodium outside: " << the_system->cell().sodium_outside);
  WRITE_LINE("Potassium inside: " << the_system->cell().potassium_inside);
  WRITE_LINE("Potassium outside: " << the_system->cell().potassium_outside);
  WRITE_LINE("Sodium pumped: " << the_system->na_k_pump().sodium_pumped());
  WRITE_LINE("Potassium pumped: " << the_system->na_k_pump().potassium_pumped());
  WRITE_LINE("Cell net charge: " << the_system->cell().net_charge);
  WRITE_LINE("FPS: " << (1.0 / dt));
  WRITE_LINE("m: " << the_system->cell().m);
  WRITE_LINE("h: " << the_system->cell().h);
  WRITE_LINE("n: " << the_system->cell().n);

  glPopAttrib();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void draw_graph()
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, width, -height, height);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glColor4f(0.9, 0.9, 0.9, 1.0);

  glScalef(2000, 1000, 1);

  voltage_graph->draw();

  glPopAttrib();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

gint on_glarea_expose(GtkWidget * widget, GdkEvent * /* event */, gpointer /* data */)
{
  if (!gtk_gl_area_make_current(glarea)) return false;

  Time now(Time::now());
  Time dt(now - last_display_time);
  last_display_time = now;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_world(dt);
  draw_legend(dt);
  draw_graph();

  // -- Flush --
  gtk_gl_area_swapbuffers(glarea);
  glFlush();

  return true;
}

gint on_glarea_configure(GtkWidget * widget, GdkEvent * event, gpointer /* data */)
{
  width = event->configure.width;
  height = event->configure.height;

  if (!gtk_gl_area_make_current(GTK_GL_AREA(widget))) return false;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (float)width / height, 1 /* nearplane */, 1000 /* farplane */);
  glMatrixMode(GL_MODELVIEW);

  return true;
}

static gint idle(gpointer /* data */)
{
  Time now(Time::now());
  Time dt((now - last_run_time) / params.time_stretch);
  last_run_time = now;

  the_system->iterate(dt);

  sim_time = sim_time + dt;
  voltage_graph->add_point(sim_time, the_system->cell().membrane_voltage);

  if (rotating)
  {
    rotate_x += 0.1;
    rotate_y += 0.05;
  }

  gtk_widget_queue_draw(GTK_WIDGET(glarea));

  return true;
}

void toggle_paused()
{
  static gint idle_tag;
  static bool paused = true;

  paused = !paused;

  if (paused)
  {
    gtk_idle_remove(idle_tag);
  }
  else
  {
    idle_tag = gtk_idle_add(idle, 0);
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;
    case ' ':
      toggle_paused();
      break;
  }
}

static int last_x = 0;
static int last_y = 0;

gint on_event_box_button_press(GtkWidget * /* widget */, GdkEvent * event, gpointer /* data */)
{
  last_x = event->button.x;
  last_y = event->button.y;
  rotating = false;

  return true;
}

gint on_event_box_button_release(GtkWidget * /* widget */, GdkEvent * /* event */, gpointer /* data */)
{
  rotating = true;

  return true;
}

gint on_event_box_motion_notify(GtkWidget * /* widget */, GdkEvent * event, gpointer /* data */)
{
  double x = event->motion.x;
  double y = event->motion.y;

  rotate_x = std::fmod(rotate_x + x - last_x, 360.0);
  rotate_y = std::fmod(rotate_y + y - last_y, 360.0);
  last_x = x;
  last_y = y;

  return true;
}

int go()
{
  last_run_time = Time::now();
  last_display_time = Time::now();
  gtk_main();
  return 0;
}

void on_window_destroy(GtkWidget * widget, gpointer data)
{
  gtk_main_quit();
}

void on_glarea_realize(GtkWidget * widget, gpointer data)
{
  if (!gtk_gl_area_make_current(glarea)) return;

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

  // TODO: shouldn't be calling GL stuff in here
  the_system.reset(new System(params));
  the_system->reset();

  toggle_paused();
}

} // namespace

int main(int argc, char** argv)
{
  gtk_init(&argc, &argv);
  glutInit(&argc, argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(window);
  g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), 0);

  event_box = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(event_box));
  g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_event_box_button_press), 0);
  g_signal_connect(event_box, "button-release-event", G_CALLBACK(on_event_box_button_release), 0);
  g_signal_connect(event_box, "motion-notify-event", G_CALLBACK(on_event_box_motion_notify), 0);
  gtk_widget_show(GTK_WIDGET(event_box));

  int attrlist[] = { GDK_GL_RGBA, GDK_GL_DOUBLEBUFFER, GDK_GL_DEPTH_SIZE, 1, GDK_GL_NONE };
  glarea = GTK_GL_AREA(gtk_gl_area_new(attrlist));
  g_signal_connect(glarea, "realize", G_CALLBACK(on_glarea_realize), 0);
  g_signal_connect(glarea, "configure-event", G_CALLBACK(on_glarea_configure), 0);
  g_signal_connect(glarea, "expose-event", G_CALLBACK(on_glarea_expose), 0);
  gtk_container_add(GTK_CONTAINER(event_box), GTK_WIDGET(glarea));
  gtk_widget_show(GTK_WIDGET(glarea));

  voltage_graph.reset(new Graph);

  return go();
}


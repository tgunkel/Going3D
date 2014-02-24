#include <GL/gl.h>
#include <GL/glut.h>
#include "Vector3D.h"
#include <iostream>
#include "RoundObjectWithMass.h"

RoundObjectWithMass sun  ("Sun",      1989000000000000000000000000000.0, 695500000.0, 0.0,0.0,0.0);
RoundObjectWithMass earth("Earth",          5972000000000000000000000.0,   6371000.0, 149600000000.0,0.0,0.0);
RoundObjectWithMass earth_moon("Earth Moon",  73477000000000000000000.0,   1738140.0, 149600000000.0-384400000.0,0.0,0.0);

void fillObjects()
{
  std::cout << "Gravity G:" << ObjectWithMass::GRAVITYCONST << std::endl;
  std::cout << sun   << std::endl;
  std::cout << earth << std::endl;
  std::cout << earth_moon << std::endl;

  std::cout << "Distance earth sun"   << sun.getDistance(earth) << std::endl;
  std::cout << "Acceleration earth: " << earth.getGravityAcceleration(sun)  << std::endl;
  std::cout << "Acceleration sun:"    << sun.getGravityAcceleration(earth)  << std::endl;

  std::cout << "Distance earth moon"   << earth.getDistance(earth_moon) << std::endl;
  std::cout << "Acceleration earth: "  << earth.getGravityAcceleration(earth_moon)  << std::endl;
  std::cout << "Acceleration moon:"    << earth_moon.getGravityAcceleration(earth)  << std::endl;
}


void init (void) 
{
  /*  set the background black  */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /*  initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

double tg_pos=0.0;
double tg_mov=0.01;

void keyPressed (unsigned char key, int x, int y)
{
  std::cout << "Key pressed" << std::endl;
}

void display(void)
{
  /*  paint the world black  */
  glClear (GL_COLOR_BUFFER_BIT);

  double zoom=192200000.0;

  double startx=0.4;

  glClear(GL_STENCIL_BUFFER_BIT);

  // store the current transformation matrix
  glPushMatrix();

  // do transformations
  glTranslatef(tg_pos,0,0);
  glColor3f (1.0, 1.0, 1.0);
  glutSolidSphere(0.1, 30, 30);

  // restore the previous transformation matrix
  glPopMatrix();
  // glFlush ();
  glutSwapBuffers();

  tg_pos=tg_pos+tg_mov;
  if(tg_pos>1 || tg_pos<-1) tg_mov=tg_mov*-1.0;

  /*
  // earth
  glTranslatef(0.4,0,0);
  glColor3f (3.0, 1.0, 0.0);
  glutSolidSphere(earth.getRadius()/zoom, 30, 30);
  glPushMatrix();

  // moon
  glTranslatef(-1.6,0,0);
  glColor3ub(0,255,255);
  glutSolidSphere(earth_moon.getRadius()/zoom, 30, 30);

  */
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   //glMatrixMode (GL_PROJECTION);
   //glLoadIdentity();
   //glFrustum (-3.0, 3.0, -3.0, 3.0, 3, 20.0);
   //glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv)
{
  fillObjects();
    glutInit(&argc, argv);
    //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Enable double buffered mode, also replace glFlush wih glutSwapBuffers()
    glutKeyboardFunc(keyPressed); 
    glutInitWindowSize (1024, 768); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Our solar system");
    init();
    glutDisplayFunc(display); 
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

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

void display(void)
{
  /*  paint the world black  */
  glClear (GL_COLOR_BUFFER_BIT);

  double zoom=192200000.0;

  double startx=0.4;

  // earth
  glTranslatef(0.4,0,0);
  glColor3f (3.0, 1.0, 0.0);
  glutSolidSphere(earth.getRadius()/zoom, 30, 30);
  glPushMatrix();

  // moon
  glTranslatef(-1.6,0,0);
  glColor3ub(0,255,255);
  glutSolidSphere(earth_moon.getRadius()/zoom, 30, 30);
  glPopMatrix();
  glFlush ();

}


int main(int argc, char** argv)
{
  fillObjects();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (1024, 768); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Our solar system");
    init ();
    glutDisplayFunc(display); 
    glutMainLoop();
    return 0;
}

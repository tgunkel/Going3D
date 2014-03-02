#include <GL/gl.h>
#include <GL/glut.h>
#include "Vector3D.h"
#include <iostream>
#include "RoundObjectWithMass.h"
#include "RBGColor.h"
#include "Vector3D.h"
#include "SystemWithObjects.h"

RoundObjectWithMass sun  ("Sun",    1989000000000000000000000000000.0, 695500000.0, Vector3D(0,0.0,          -149600000000.0),  RBGColor(255,255,  0));
//RoundObjectWithMass sun  ("Sun",            5972000000000000000000000.0,   630001000.0, Vector3D(,0.0,-149600000000.0),  RBGColor(255,255,  0));
RoundObjectWithMass earth("Earth",          5972000000000000000000000.0,   6371000.0, Vector3D(0,0.0,0.0),             RBGColor(0,    0,255));
RoundObjectWithMass earth_moon("Earth Moon",  73477000000000000000000.0,   1738140.0, Vector3D(384400000.0,0.0,0.0),     RBGColor(255,255,255));

SystemWithObjects solarsystem("Solar system");

Vector3D camerapos(0,0,5);

void fillObjects()
{
  earth_moon.addSpeedFromOutside(Vector3D(-500, -500, 0));

  std::cout << "Gravity G:" << ObjectWithMass::GRAVITYCONST << std::endl;
  std::cout << sun   << std::endl;
  std::cout << earth << std::endl;
  std::cout << earth_moon << std::endl;



  std::cout << "Distance earth sun"   << sun.getDistance(earth) << std::endl;
  std::cout << "Force sun-earth:  "   << earth.getGravityForce(sun)  << std::endl;
  std::cout << "Acceleration earth: " << earth.getGravityAcceleration(sun)  << std::endl;
  std::cout << "Acceleration sun:"    << sun.getGravityAcceleration(earth)  << std::endl;

  solarsystem.addNewObject(&sun);
  solarsystem.addNewObject(&earth);
  solarsystem.addNewObject(&earth_moon); 

  std::cout << solarsystem  << std::endl;

  /*
  std::cout << "Distance earth moon"   << earth.getDistance(earth_moon) << std::endl;
  std::cout << "Acceleration earth: "  << earth.getGravityAcceleration(earth_moon)  << std::endl;
  std::cout << "Acceleration moon:"    << earth_moon.getGravityAcceleration(earth)  << std::endl;
  */
}


void init (void)
{
  /*  set the background black  */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glEnable(GL_DEPTH_TEST);
 
  /* */
  glShadeModel (GL_FLAT);

  /*  initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}


double gx=0.0;
double gy=0.0;
double gz=0.0;

void keyPressed(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'q': exit(0);
    case 'a': camerapos=camerapos.add(Vector3D(-.1, 0,0)); break;
    case 'd': camerapos=camerapos.add(Vector3D(+.1, 0,0)); break;
    case 'w': camerapos=camerapos.add(Vector3D( 0,-.1,0)); break;
    case 's': camerapos=camerapos.add(Vector3D( 0,+.1,0)); break;
    case 'e': camerapos=camerapos.add(Vector3D( 0,  0,-.1)); break;
    case 'c': camerapos=camerapos.add(Vector3D( 0,  0,+.1)); break;
    }
  std::cout << "Key: " << key << " Sun: " << sun << std::endl;
}

void paint(RoundObjectWithMass obj)
{
  double zoom=152200000.0;

  // store the current transformation matrix
  glPushMatrix();

  // do transformations
  glTranslatef(obj.getPosition().getX()/zoom,obj.getPosition().getY()/zoom,obj.getPosition().getZ()/zoom);
  glColor3f(obj.getColor().getRedInPercent(), obj.getColor().getGreenInPercent(), obj.getColor().getBlueInPercent());
  glutSolidSphere(obj.getRadius()/zoom, 30, 30);

  // restore the previous transformation matrix
  glPopMatrix();
}

void display(void)
{
  /*  paint the world black  */
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glClear(GL_STENCIL_BUFFER_BIT);

  glLoadIdentity ();

  gluLookAt (camerapos.getX(), camerapos.getY(), camerapos.getZ(), camerapos.getX(), camerapos.getY(), camerapos.getZ()-5, 0.0, 1.0, 0.0);

  glScalef (1.0, 2.0, 1.0);

  solarsystem.updateSystem(100.0);

  //  paint(sun,        0.0, 0.0, -12.0);
  paint(sun);
  paint(earth_moon);
  paint(earth);

  glutSwapBuffers();

}

void reshape (int width, int height)
{
  glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window  
  glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed  
  glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)  
  glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 5000.0);
  //gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 5.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes  
  glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly  
}  


int main(int argc, char** argv)
{
  fillObjects();
  glutInit(&argc, argv);
  //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Enable double buffered mode, also replace glFlush wih glutSwapBuffers()
  glutInitWindowSize (2000, 768); 
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Our solar system");
  init();
  glutKeyboardFunc(keyPressed); 
  glutDisplayFunc(display); 
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}

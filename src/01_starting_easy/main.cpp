#include <GL/gl.h>
#include <GL/glut.h>
#include "Vector3D.h"
#include <iostream>
#include "RoundObjectWithMass.h"
#include "RBGColor.h"
#include "Vector3D.h"
#include "SystemWithObjects.h"
#include "Camera.h"
#include "WorldModelReaderNasa.h"

RoundObjectWithMass sun  ("Sun",    1989000000000000000000000000000.0,   695500000.0, Vector3D(0,0.0,-149600000000.0),  RBGColor(255,255,  0));
RoundObjectWithMass earth("Earth",          5972000000000000000000000.0,   6371000.0, Vector3D(0,0.0,0.0),              RBGColor(0,    0,255));
RoundObjectWithMass earth_moon("Earth Moon",  73477000000000000000000.0,   1738140.0, Vector3D(384400000.0,0.0,0.0),    RBGColor(255,255,255));

SystemWithObjects solarsystem("Solar system");

Vector3D scale(0.000000005, .000000005*2.0, 0.000000005);

Camera camera(Vector3D(0,0,5), Vector3D(0,0,0));

Vector3D angle(0,-220,0);

WorldModelReaderNasa wm=WorldModelReaderNasa();
Tile* niceWorld;

void fillObjects()
{
  std::cout << camera  << std::endl;

  earth_moon.addSpeedFromOutside(Vector3D(-500, -500, 0));

  //std::cout << "Gravity G:" << ObjectWithMass::GRAVITYCONST << std::endl;

  std::cout << sun   << std::endl;
  std::cout << earth << std::endl;
  std::cout << earth_moon << std::endl;


  /*
  std::cout << "Distance earth sun"   << sun.getDistance(earth) << std::endl;
  std::cout << "Force sun-earth:  "   << earth.getGravityForce(sun)  << std::endl;
  std::cout << "Acceleration earth: " << earth.getGravityAcceleration(sun)  << std::endl;
  std::cout << "Acceleration sun:"    << sun.getGravityAcceleration(earth)  << std::endl;
  */

  solarsystem.addNewObject(&sun);
  solarsystem.addNewObject(&earth);
  solarsystem.addNewObject(&earth_moon); 

  std::cout << solarsystem  << std::endl;

  /*
  std::cout << "Distance earth moon"   << earth.getDistance(earth_moon) << std::endl;
  std::cout << "Acceleration earth: "  << earth.getGravityAcceleration(earth_moon)  << std::endl;
  std::cout << "Acceleration moon:"    << earth_moon.getGravityAcceleration(earth)  << std::endl;
  */

  wm.readFile();
  niceWorld=wm.getNiceWorld();
}


void init (void)
{
  /*  set the background black  */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  glEnable(GL_DEPTH_TEST);

  // fix light for worlds with scaling
  glEnable(GL_NORMALIZE);
 
  /* */
  glShadeModel (GL_FLAT);

  /*  initialize viewing values  */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void keyPressed(unsigned char key, int x, int y)
{
  switch(key)
    {
    case 'q': exit(0);
    case 'a': angle=angle.add(Vector3D(+1.0, 0.0,  0.0));   break;
    case 'd': angle=angle.add(Vector3D(-1.0, 0.0,  0.0));   break;
    case 'w': angle=angle.add(Vector3D( 0.0, +1.0, 0.0));   break;
    case 's': angle=angle.add(Vector3D( 0.0, -1.0, 0.0));   break;
    case 'e': angle=angle.add(Vector3D( 0.0, 0.0, +1.0));   break;
    case 'c': angle=angle.add(Vector3D( 0.0, 0.0, -1.0));   break;
    case 'x': wm.splitNextCandidate(); break;
    }
  //std::cout << "Rotation: " << angle << std::endl;
}

void paint(RoundObjectWithMass obj)
{
  // store the current transformation matrix
  glPushMatrix();

  // do transformations
  glTranslatef(obj.getPosition().getX(),obj.getPosition().getY(),obj.getPosition().getZ());
  glColor3f(obj.getColor().getRedInPercent(), obj.getColor().getGreenInPercent(), obj.getColor().getBlueInPercent());
  glutSolidSphere(obj.getRadius(), 30, 30);

  // restore the previous transformation matrix
  glPopMatrix();
}

void display(void)
{
  /*  paint the world black  */
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glClear(GL_STENCIL_BUFFER_BIT);

  glLoadIdentity ();

  /*
  camera.satelliteObject(earth, earth_moon);
  std::cout << camera  << std::endl;
  */

  gluLookAt (camera.getPosition().getX(), camera.getPosition().getY(), camera.getPosition().getZ(), camera.getLookAt().getX(), camera.getLookAt().getY(), camera.getLookAt().getZ(), 0.0, 1.0, 0.0);

  // scale the universe so the objects appear smaller
  glScalef ((float) scale.getX(), (float) scale.getY(), (float) scale.getZ());

  ObjectWithMass& mycenter=earth;

  glRotatef(angle.getX(), 0,1,0);
  glRotatef(angle.getY(), 1,0,0);
  glRotatef(angle.getZ(), 0,0,1);

  glTranslatef(-mycenter.getPosition().getX(),-mycenter.getPosition().getY(),-mycenter.getPosition().getZ());

  /*  
  //solarsystem.updateSystem(100.0);

  // paint(sun,        0.0, 0.0, -12.0);
  paint(sun);
  paint(earth_moon);
  paint(earth);
  */

  const double max_value_x=86400.0;
  const double max_value_y=43200.0;
  const double max_value_z=10000.0;
  const double max_paint_x=1058800000.0;
  const double max_paint_y=max_paint_x*max_value_y/max_value_x;
  const double max_paint_z=384400000.0;

  niceWorld->FIXME_paint(max_paint_x/max_value_x, max_paint_y/max_value_y, max_paint_z/max_value_z, Vector3D(-max_paint_x/2.0, -max_paint_y/2.0, 0), 0);

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

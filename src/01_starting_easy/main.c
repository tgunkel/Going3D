#include <GL/gl.h>
#include <GL/glut.h>

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

  glColor3f (1.0, 1.0, 0.0);
  glutSolidSphere(0.1, 20, 20);
  glPushMatrix();
  glTranslatef(0.3,0,0);
  glColor3ub(0,255,255);
  glutSolidSphere(0.1, 20, 20);
  glPopMatrix();
  glFlush ();

}


int main(int argc, char** argv)
{
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

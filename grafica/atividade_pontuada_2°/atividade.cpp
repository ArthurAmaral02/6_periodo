#include <GL/glut.h>
GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 80.0, y0 = 80.0, z0 = 80.0;
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;
GLfloat fovY = 60.0, aspect = 1.0, dnear = 1.0, dfar = 500.0;


void init(void) {
 glClearColor(1.0, 1.0, 1.0, 0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(fovY, aspect, dnear, dfar);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
 glEnable(GL_DEPTH_TEST);
}
void drawAxes() {
    glLineWidth(2.0);

    glBegin(GL_LINES);

    // Eixo X - vermelho
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);

    // Eixo Y - verde
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);

    // Eixo Z - azul
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);

    glEnd();
}

void displayFcn(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawAxes();

    glPushMatrix();

    glColor3f(0.8, 0.5, 0.8);
    
    glTranslatef(30.0, 0.0, 0.0);

    glutWireTorus(10.0, 25.0, 30, 30);

    glPopMatrix();

    glFlush();
}
void reshapeFcn(GLint newWidth, GLint newHeight) {
 glViewport(0, 0, newWidth, newHeight);
 aspect = (GLfloat)newWidth / (GLfloat)newHeight;
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(fovY, aspect, dnear, dfar);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);
}
int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowPosition(50, 50);
 glutInitWindowSize(winWidth, winHeight);
 glutCreateWindow("Modelo de Arame do Toro: base");
 init();
 glutDisplayFunc(displayFcn);
 glutReshapeFunc(reshapeFcn);
 glutMainLoop();
 return 0;
}

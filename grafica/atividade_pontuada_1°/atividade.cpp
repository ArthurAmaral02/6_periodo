#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth = 600, winHeight = 600;

GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;

class wcPt3D {
public:
    GLfloat x, y, z;
};

int transformation = 0;
// 0 = original
// 1 = translação
// 2 = escala
// 3 = rotação

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bezCurvePt) {
    glBegin(GL_POINTS);
    glVertex2f(bezCurvePt.x, bezCurvePt.y);
    glEnd();
}

void binomialCoeffs(GLint n, GLint* C) {
    GLint k, j;

    for (k = 0; k <= n; k++) {
        C[k] = 1;

        for (j = n; j >= k + 1; j--)
            C[k] *= j;

        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void computeBezPt(
    GLfloat u,
    wcPt3D* bezPt,
    GLint nCtrlPts,
    wcPt3D* ctrlPts,
    GLint* C
) {
    GLint k;
    GLint n = nCtrlPts - 1;

    GLfloat bezBlendFcn;

    bezPt->x = 0.0;
    bezPt->y = 0.0;
    bezPt->z = 0.0;

    for (k = 0; k < nCtrlPts; k++) {

        bezBlendFcn =
            C[k] *
            pow(u, k) *
            pow(1 - u, n - k);

        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

void bezier(
    wcPt3D* ctrlPts,
    GLint nCtrlPts,
    GLint nBezCurvePts
) {
    wcPt3D bezCurvePt;

    GLfloat u;

    GLint* C;
    GLint k;

    C = new GLint[nCtrlPts];

    binomialCoeffs(nCtrlPts - 1, C);

    for (k = 0; k <= nBezCurvePts; k++) {

        u = GLfloat(k) / GLfloat(nBezCurvePts);

        computeBezPt(
            u,
            &bezCurvePt,
            nCtrlPts,
            ctrlPts,
            C
        );

        plotPoint(bezCurvePt);
    }

    delete[] C;
}

void drawAxes(void) {

    glBegin(GL_LINES);

    // Eixo X - verde
    glColor3f(0.0, 1.0, 0.0);

    glVertex2f(xwcMin, 0.0);
    glVertex2f(xwcMax, 0.0);

    // Eixo Y - azul
    glColor3f(0.0, 0.0, 1.0);

    glVertex2f(0.0, ywcMin);
    glVertex2f(0.0, ywcMax);

    glEnd();
}

// ================= TRANSFORMAÇÕES =================

void translateCurve(GLfloat tx, GLfloat ty) {
    glTranslatef(tx, ty, 0.0);
}

void scaleCurve(GLfloat sx, GLfloat sy) {
    glScalef(sx, sy, 1.0);
}

void rotateCurve(GLfloat angle) {
    glRotatef(angle, 0.0, 0.0, 1.0);
}

// ================= POLIGON =================
void drawDodecagon(GLfloat centerX, GLfloat centerY, GLfloat radius) {

    const int sides = 12;
    const GLfloat PI = 3.14159265359;

    glBegin(GL_POLYGON);

    for (int i = 0; i < sides; i++) {

        GLfloat angle = 2.0 * PI * i / sides;

        GLfloat x = centerX + radius * cos(angle);
        GLfloat y = centerY + radius * sin(angle);

        glVertex2f(x, y);
    }

    glEnd();
}

// ================= TECLADO =================

void keyboardFcn(unsigned char key, int x, int y) {

    switch (key) {

    case 27: // ESC
        transformation = 0;
        break;

    case 't':
    case 'T':
        transformation = 1;
        break;

    case 's':
    case 'S':
        transformation = 2;
        break;

    case 'r':
    case 'R':
        transformation = 3;
        break;
    }

    glutPostRedisplay();
}

// ================= DISPLAY =================

void displayFcn(void) {

    GLint nCtrlPts = 4;
    GLint nBezCurvePts = 1000;

    wcPt3D ctrlPts[4] = {
        {-40.0, -40.0, 0.0},
        {-10.0, 40.0, 0.0},
        {10.0, 40.0, 0.0},
        {40.0, -40.0, 0.0}
    };

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(4);

    // Curva original
    glColor3f(1.0, 0.0, 0.0);

    bezier(
        ctrlPts,
        nCtrlPts,
        nBezCurvePts
    );

    // Polígono de 12 lados
    glColor3f(0.0, 0.0, 0.0);
    drawDodecagon(0.0, 0.0, 20.0);

    // Transformação
    if (transformation != 0) {

        glPushMatrix();

        if (transformation == 1) {
            translateCurve(15.0, 10.0);
        }
        else if (transformation == 2) {
            scaleCurve(1.5, 1.5);
        }
        else if (transformation == 3) {
            rotateCurve(45.0);
        }

        glColor3f(1.0, 1.0, 0.0);

        bezier(
            ctrlPts,
            nCtrlPts,
            nBezCurvePts
        );

        glPopMatrix();
    }

    drawAxes();

    glFlush();
}

// ================= RESHAPE =================

void winReshapeFcn(GLint newWidth, GLint newHeight) {

    glViewport(
        0,
        0,
        newHeight,
        newHeight
    );

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        xwcMin,
        xwcMax,
        ywcMin,
        ywcMax
    );

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

// ================= MAIN =================

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(
        GLUT_SINGLE | GLUT_RGB
    );

    glutInitWindowPosition(50, 50);

    glutInitWindowSize(
        winWidth,
        winHeight
    );

    glutCreateWindow("Bezier Curve");

    init();

    glutDisplayFunc(displayFcn);

    glutReshapeFunc(winReshapeFcn);

    glutKeyboardFunc(keyboardFcn);

    glutMainLoop();

    return 0;
}
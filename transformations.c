#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define pi 3.142857
vector<vector<double>> v{{10, 20, 1}, {100, 50, 1}, {200, -200, 1}};
vector<vector<double>> z{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
vector<vector<double>> tz{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
vector<vector<double>> tzs{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
vector<vector<double>> scaleu{{2, 0, 0}, {0, 2, 0}, {0, 0, 1}};
vector<vector<double>> scaled{{0.5, 0, 0}, {0, 0.5, 0}, {0, 0, 1}};
vector<vector<double>> vv{{10, 20, 1}, {100, 50, 1}, {200, -200, 1}};
vector<vector<double>> temp;
vector<vector<double>> translatexp{{1, 0, 0}, {0, 1, 0}, {50, 0, 1}};
vector<vector<double>> translatexn{{1, 0, 0}, {0, 1, 0}, {-50, 0, 1}};
vector<vector<double>> translateyp{{1, 0, 0}, {0, 1, 0}, {0, 50, 1}};
vector<vector<double>> translateyn{{1, 0, 0}, {0, 1, 0}, {0, -50, 1}};
vector<vector<double>> rotatec{{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};
vector<vector<double>> rotatea{{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
void matrix_multiply(vector<vector<double>> &vr)
{
 temp = v;
 v = z;
 for (int i = 0; i < 3; ++i)
 {
 for (int j = 0; j < 3; ++j)
 {
 for (int k = 0; k < 3; ++k)
 {
 v[i][j] += temp[i][k] * vr[k][j];
 }
 }
 }
}
void myInit(void)
{
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glColor3f(1.0, 1.0, .0);
 glPointSize(3.0);
 glMatrixMode(GL_PROJECTION);
 
 glLoadIdentity();
 gluOrtho2D(-500, 500, -500, 500);
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_POINTS);
 for (double y = -500; y <= 500; y += 0.05)
 {
 glVertex2f(0, y);
 glVertex2f(y, 0);
 }
 glEnd();
 glBegin(GL_POLYGON);
 for (int i = 0; i < 3; i++)
 {
 glVertex2f(v[i][0], v[i][1]);
 }
 glEnd();
 glFlush();
}
void keyboard(unsigned char key, int x, int y)
{
 switch (key)
 {
 case 'd':
 matrix_multiply(translatexp);
 glutPostRedisplay();
 break;
 case 'a':
 matrix_multiply(translatexn);
 glutPostRedisplay();
 break;
 case 'w':
 matrix_multiply(translateyp);
 glutPostRedisplay();
 break;
 case 's':
 matrix_multiply(translateyn);
 glutPostRedisplay();
 break;
 case 'u':
 tz = tzs;
 tz[2][0] = -v[0][0];
 tz[2][1] = -v[0][1];
 matrix_multiply(tz);
matrix_multiply(scaleu);
 tz[2][0] = -tz[2][0];
 tz[2][1] = -tz[2][1];
 matrix_multiply(tz);
 glutPostRedisplay();
 break;
 case 'c':
 tz = tzs;
 tz[2][0] = -v[0][0];
 tz[2][1] = -v[0][1];
 matrix_multiply(tz);
 matrix_multiply(rotatec);
 tz[2][0] = -tz[2][0];
 tz[2][1] = -tz[2][1];
 matrix_multiply(tz);
 glutPostRedisplay();
 break;
 case 'z':
 tz = tzs;
 tz[2][0] = -v[0][0];
 tz[2][1] = -v[0][1];
 matrix_multiply(tz);
 matrix_multiply(rotatea);
 tz[2][0] = -tz[2][0];
 tz[2][1] = -tz[2][1];
 matrix_multiply(tz);
 glutPostRedisplay();
 break;
 case 'q':
 v = vv;
 glutPostRedisplay();
 break;
 case 'r':
 glColor3f(1, 0, 0);
 glutPostRedisplay();
 break;
 case 'b':
 glColor3f(0, 0, 1);
 glutPostRedisplay();
 break;
 case 'g':
 glColor3f(0, 1, 0);
glutPostRedisplay();
 break;
 case 'i':
 tz = tzs;
 tz[2][0] = -v[0][0];
 tz[2][1] = -v[0][1];
 matrix_multiply(tz);
 matrix_multiply(scaled);
 tz[2][0] = -tz[2][0];
 tz[2][1] = -tz[2][1];
 matrix_multiply(tz);
 glutPostRedisplay();
 break;
 case 27:
 exit(0);
 break;
 }
}
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(1000, 1000);
 glutInitWindowPosition(0, 0);
 glutCreateWindow("Original ViewPort");
 myInit();
 glutKeyboardFunc(keyboard);
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}


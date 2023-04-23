#include <bits/stdc++.h>
#include <GL/glut.h>
#include <math.h>
using namespace std;
float x_position = 0.0;
int state = 1;
float angle = 0.0;
GLfloat vertices[][3] = {
{-1.0, -1.0, 1.0},
{-1.0, 1.0, 1.0},
{1.0, 1.0, 1.0},
{1.0, -1.0, 1.0},
{-1.0, -1.0, -1.0},
{-1.0, 1.0, -1.0},
{1.0, 1.0, -1.0},
{1.0, -1.0, -1.0}};
GLubyte indices[] = {
0, 3, 2, 1,
2, 3, 7, 6,
0, 4, 7, 3,
1, 2, 6, 5,
4, 5, 6, 7,
0, 1, 5, 4};
GLfloat colors[][3] = {
{1.0, 0.0, 0.0},
{0.0, 1.0, 0.0},
{0.0, 0.0, 1.0},
{1.0, 1.0, 0.0},
{1.0, 0.0, 1.0},
{0.0, 1.0, 1.0}};
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
glBegin(GL_QUADS);
for (int i = 0; i < 24; i += 4)
{
GLfloat v1[3], v2[3], normal[3];
v1[0] = vertices[indices[i + 1]][0] - vertices[indices[i]][0];
v1[1] = vertices[indices[i + 1]][1] - vertices[indices[i]][1];
v1[2] = vertices[indices[i + 1]][2] - vertices[indices[i]][2];
v2[0] = vertices[indices[i + 2]][0] - vertices[indices[i + 1]][0];
v2[1] = vertices[indices[i + 2]][1] - vertices[indices[i + 1]][1];
v2[2] = vertices[indices[i + 2]][2] - vertices[indices[i + 1]][2];
normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
normal[1] = v1[2] * v2[0] - v1[0] * v2[2];
normal[2] = v1[0] * v2[1] - v1[1] * v2[0];
GLfloat length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
normal[2] * normal[2]);
normal[1] /= length;
normal[2] /= length;
normal[3] /= length;
GLfloat viewVector[3] = {1, 1, 1};
GLfloat dotProduct = normal[0] * viewVector[0] + normal[1] * 
viewVector[1] + normal[2] * viewVector[2];
if (dotProduct < 0)
{
continue;
}
glColor3fv(colors[i / 4]);
glVertex3fv(vertices[indices[i]]);
glVertex3fv(vertices[indices[i + 1]]);
glVertex3fv(vertices[indices[i + 2]]);
glVertex3fv(vertices[indices[i + 3]]);
}
glEnd();
glutSwapBuffers();
}
void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, 1, 2.0, 50.0);
glMatrixMode(GL_MODELVIEW);
}
void timer(int t)
{
glutPostRedisplay();
glutTimerFunc(1000 / 60, timer, 0);
angle += 0.8;
if (angle > 360)
angle = angle - 360;
}
void init()
{
glClearColor(0.0, 0.0, 0.0, 1.0);
glEnable(GL_DEPTH_TEST);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowPosition(200, 100);
glutInitWindowSize(500, 500);
glutCreateWindow("Back Face Removal");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(0, timer, 0);
init();
glutMainLoop();
}

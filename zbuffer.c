#include <bits/stdc++.h>
#include <GL/glut.h>
#include <cmath>
using namespace std;
int width = 640, height = 480;
float zBuffer[640][480];
float surface1[][3] = {{-1.0, -1.0, 1.0},
{-1.0, 1.0, 1.0},
{1.0, 1.0, 1.0},
{1.0, -1.0, 1.0}};
float surface2[][3] = {{-1.0, -1.0, 0.0},
{-1.0, 1.0, 0.0},
{1.0, 1.0, 0.0},
{1.0, -1.0, 0.0}};
float surface3[][3] = {{-1.0, -1.0, -1.0},
{-1.0, 1.0, -1.0},
{1.0, 1.0, -1.0},
{1.0, -1.0, -1.0}};
void drawSurface(float surface[][3])
{
glBegin(GL_QUADS);
glVertex3fv(surface[0]);
glVertex3fv(surface[1]);
glVertex3fv(surface[2]);
glVertex3fv(surface[3]);
glEnd();
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
glColor3f(1.0, 0.0, 0.0);
drawSurface(surface1);
glColor3f(0.0, 1.0, 0.0);
drawSurface(surface2);
glColor3f(0.0, 0.0, 1.0);
drawSurface(surface3);
glutSwapBuffers();
}

void reshape(int w, int h)
{
glViewport(0, 0, (GLsizei)w, (GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(6.0, 0.0, 5.0,
0.0, 0.0, 0.0,
0.0, 1.0, 0.0);
}
void zBufferAlgorithm(float x1, float y1, float z1, float x2, float y2, float
z2, float x3, float y3, float z3)
{
int minX = (int)floor(fmin(fmin(x1, x2), x3));
int maxX = (int)ceil(fmax(fmax(x1, x2), x3));
int minY = (int)floor(fmin(fmin(y1, y2), y3));
int maxY = (int)ceil(fmax(fmax(y1, y2), y3));
for (int x = minX; x <= maxX; x++)
{
for (int y = minY; y <= maxY; y++)
{
float alpha, beta, gamma;
alpha = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) /
((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
beta = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) /
((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
gamma = 1.0 - alpha - beta;
if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0)
{
// Calculate the depth of the pixel
float z = alpha * z1 + beta * z2 + gamma * z3;
// If the pixel is closer than the current Z-value, update
// the Z-buffer and draw the pixel
if (z < zBuffer[x][y])
{
zBuffer[x][y] = z;
glColor3f(alpha, beta, gamma);
glBegin(GL_POINTS);
glVertex2i(x, y);
glEnd();
}
}
}
}
}
void keyboard(unsigned char key, int x, int y)
{
switch (key)
{
case 27:
exit(0);
break;
}
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(width, height);
glutCreateWindow("Z-buffer algorithm");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
for (int x = 0; x < width; x++)
{
for (int y = 0; y < height; y++)
{
zBuffer[x][y] = 1.0;
}
}
glShadeModel(GL_SMOOTH);
glutMainLoop();
return 0;
}


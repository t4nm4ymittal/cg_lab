#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;
int x_min, y_min;
int x_max, y_max;
int computeCode(double x, double y)
{
 int code = INSIDE;
 if (x < x_min)
 code |= LEFT;
 else if (x > x_max)
 code |= RIGHT;
 if (y < y_min)
 code |= BOTTOM;
 else if (y > y_max)
 code |= TOP;
 return code;
}
void cohenSutherlandClip(double x1, double y1, double x2, double y2)
{
 int code1 = computeCode(x1, y1);
 int code2 = computeCode(x2, y2);
 while (true)
 {
 if (!(code1 | code2))
 {
 glColor3f(0, 0, 1);
 glBegin(GL_LINES);
 glVertex2f(x1, y1);
 glVertex2f(x2, y2);
 glEnd();
 glFlush();
 break;
}
 else if (code1 & code2)
 {
 break;
 }
 else
 {
 double x, y;
 int code = code1 ? code1 : code2;
 if (code & TOP)
 {
 x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
 y = y_max;
 }
 else if (code & BOTTOM)
 {
 x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
 y = y_min;
 }
 else if (code & RIGHT)
 {
 y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
 x = x_max;
 }
 else if (code & LEFT)
 {
 y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
 x = x_min;
 }
 if (code == code1)
 {
 x1 = x;
 y1 = y;
 code1 = computeCode(x1, y1);
 }
 else
 {
 x2 = x;
 y2 = y;
 code2 = computeCode(x2, y2);
 }
 }
}
}
void display()
{
 cout<<"Enter Minimum window co-ordinates: ";
 cin>>x_min>>y_min;
 cout<<"Enter Maximum window co-ordinates: ";
 cin>>x_max>>y_max;
 double x1, y1;
 double x2, y2;
 cout<<"Enter co-ordinates of first point of line: ";
 cin>>x1>>y1;
 cout<<"Enter co-ordinates of second point of line: ";
 cin>>x2>>y2;
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0, 0.0, 0.0);
 glBegin(GL_LINE_LOOP);
 glVertex2f(x_min, y_min);
 glVertex2f(x_max, y_min);
 glVertex2f(x_max, y_max);
 glVertex2f(x_min, y_max);
 glEnd();
 glColor3f(0, 1, 0);
 glBegin(GL_LINES);
 glVertex2f(x1, y1);
 glVertex2f(x2, y2);
 glEnd();
 glFlush();
 cohenSutherlandClip(x1, y1, x2, y2);
}
int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(680, 500);
 glutInitWindowPosition(200, 200);
 glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
 glutDisplayFunc(display);
 gluOrtho2D(-500, 500, -500, 500);
 glutMainLoop();
 return 0;
}


#include <GL/glut.h>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
int n;
struct Point
{
 int x, y;
};
Point polygon[100];
bool cmp(Point a, Point b)
{
 return (a.y < b.y || (a.y == b.y && a.x < b.x));
}
void init()
{
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,500,0,500);
 glColor3f(0.0, 0.0, 0.0);
 glPointSize(1.0);
 glLoadIdentity();
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0, 0.0, 0.0);
 glBegin(GL_POLYGON);
 for (int i = 0; i < n; i++)
 glVertex2i(polygon[i].x, polygon[i].y);
 glEnd();
 glFlush();
}
int findYMin()
{
 int ymin = polygon[0].y, min = 0;
 for (int i = 1; i < n; i++)
 {
 int y = polygon[i].y;
if ((y < ymin) || (ymin == y && polygon[i].x < polygon[min].x))
 ymin = polygon[i].y, min = i;
 }
 return min;
}
void fillScanLine(int yMin, int x1, int x2, int y1, int y2)
{
 if (y1 > y2)
 swap(y1, y2), swap(x1, x2);
 for (int i = y1; i < y2; i++)
 {
 int xIntersect = x1 + (i - y1) * (x2 - x1) / (y2 - y1);
 glBegin(GL_POINTS);
 glVertex2i(xIntersect, i);
 glEnd();
 glFlush();
 }
}
void scanLineFill(void)
{
 sort(polygon, polygon + n, cmp);
 int yMin = polygon[0].y;
 int yMax = polygon[n - 1].y;
 int yStart, yEnd, xStart, xEnd;
 int yCur = yMin;
 while (yCur <= yMax)
 {
 for (int i = 0; i < n; i++)
 {
 int j = (i + 1) % n;
 int sl = (polygon[i].y < polygon[j].y) ? i : j;
 int el = (sl == i) ? j : i;
 if (yCur >= polygon[sl].y && yCur < polygon[el].y)
 {
 xStart = polygon[sl].x + (yCur - polygon[sl].y) * (polygon[el].x - polygon[sl].x) / 
(polygon[el].y - polygon[sl].y);
 if (xStart > polygon[el].x)
 swap(xStart, polygon[el].x);
 fillScanLine(yMin, xStart, polygon[el].x, yCur, polygon[el].y);
 }
}
 yCur++;
 }
}
int main(int argc, char **argv)
{
 cout << "Enter the number of vertices of polygon: ";
 cin >> n;
 cout << "Enter the vertices of polygon in counter-clockwise order:\n";
 for (int i = 0; i < n; i++)
 cin >> polygon[i].x >> polygon[i].y;
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(200,200);
 glutCreateWindow("Polygon Filling");
 glutDisplayFunc(scanLineFill);
 init();
 glutMainLoop();
 return 0;
}


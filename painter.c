#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
using namespace std;
class Point
{
public:
float x, y, z;
Point() {}
Point(float x, float y, float z) : x(x), y(y), z(z) {}
};
class Polygon
{
public:
vector<Point> vertices;
Polygon() {}
Polygon(vector<Point> vertices) : vertices(vertices) {}
};
vector<Polygon> polygons = {
Polygon({Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(0, 1, 0)}),
Polygon({Point(0, 0, 1), Point(1, 0, 1), Point(1, 1, 1), Point(0, 1, 1)}),
Polygon({Point(0, 0, 0), Point(0, 0, 1), Point(0, 1, 1), Point(0, 1, 0)}),
Polygon({Point(1, 0, 0), Point(1, 0, 1), Point(1, 1, 1), Point(1, 1, 0)}),
Polygon({Point(0, 0, 0), Point(0, 0, 1), Point(1, 0, 1), Point(1, 0, 0)}),
Polygon({Point(0, 1, 0), Point(0, 1, 1), Point(1, 1, 1), Point(1, 1, 
0)})};
vector<float> colors = {1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1};
float camX = 0.0, camY = 0.0, camZ = 3.0;
float near = 1.0, far = 10.0, fov = 60.0, aspect = 1.0;
float angle = 0.0;
bool comparePolygons(const Polygon &p1, const Polygon &p2)
{
float p1_depth = 0.0, p2_depth = 0.0;
for (auto vertex : p1.vertices)
{
p1_depth += vertex.z;
}
for (auto vertex : p2.vertices)
{
p2_depth += vertex.z;
}
return p1_depth > p2_depth;
}
void renderPolygons()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(fov, aspect, near, far);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
glRotatef(angle, 0.0, 1.0, 0.0);
sort(polygons.begin(), polygons.end(), comparePolygons);
for (int i = 0; i < polygons.size(); i++)
{
glBegin(GL_POLYGON);
glColor3f(colors[i * 3], colors[i * 3 + 1], colors[i * 3 + 2]);
for (auto vertex : polygons[i].vertices)
{
glVertex3f(vertex.x, vertex.y, vertex.z);
}
glEnd();
}
glutSwapBuffers();
}
void handleKeypress(unsigned char key, int x, int y){
switch (key){
case 'a':
camX -= 0.1;
break;
case 'd':
camX += 0.1;
break;
case 'w':
camY += 0.1;
break;
case 's':
camY -= 0.1;
break;
case 'q':
camZ -= 0.1;
break;
case 'e':
camZ += 0.1;
break;
case 'r':
angle += 5.0;
break;
case 'f':
angle -= 5.0;
break;
case 27:
exit(0);
break;
}
glutPostRedisplay();
}
int main(int argc, char **argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(800, 600);
glutCreateWindow("Painter's Algorithm");
glEnable(GL_DEPTH_TEST);
glutDisplayFunc(renderPolygons);
glutKeyboardFunc(handleKeypress);
glutMainLoop();
return 0;
}

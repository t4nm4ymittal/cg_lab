#include <bits/stdc++.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
struct Vertex
{
float x, y, z;
Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};
struct Polygon
{
vector<Vertex> vertices;
Polygon(const vector<Vertex> &vertices) : vertices(vertices) {}
};
struct Pyramid
{
vector<Polygon> faces;
Pyramid(const vector<Polygon> &faces) : faces(faces) {}
};
vector<float> getIntersections(Vertex &v1, Vertex &v2, float y)
{
vector<float> intersections;
if (v1.y != v2.y)
{
if (v1.y > v2.y)
{
swap(v1, v2);
}
float x = v1.x + (y - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
intersections.push_back(x);
}
return intersections;
}
vector<float> getBoundingBox(const Polygon &polygon)
{
vector<float> boundingBox = {INFINITY, -INFINITY, INFINITY, -INFINITY};
for (const Vertex &vertex : polygon.vertices)
{
if (vertex.x < boundingBox[0])
{
boundingBox[0] = vertex.x;
}
if (vertex.x > boundingBox[1])
{
boundingBox[1] = vertex.x;
}
if (vertex.y < boundingBox[2])
{
boundingBox[2] = vertex.y;
}
if (vertex.y > boundingBox[3])
{
boundingBox[3] = vertex.y;
}
if (vertex.z > boundingBox[3])
{
boundingBox[3] = vertex.z;
}
}
return boundingBox;
}
void drawPyramid(const Pyramid &pyramid)
{
glColor3f(0.0, 0.0, 1.0);
for (const Polygon &face : pyramid.faces)
{
glBegin(GL_POLYGON);
for (const Vertex &vertex : face.vertices)
{
glVertex3f(vertex.x, vertex.y, vertex.z);
}
glEnd();
}
}
void scanLineAlgorithm(const Pyramid &pyramid)
{
glDisable(GL_LIGHTING);
glLineWidth(1.0);
glColor3f(0.0, 0.0, 0.0);
for (float y = 0.5; y < 1.5; ++y)
{
vector<float> intersections;
for (const Polygon &face : pyramid.faces)
{
vector<float> boundingBox = getBoundingBox(face);
if (y >= boundingBox[2] && y < boundingBox[3])
{
float x1 = boundingBox[0];
float x2 = boundingBox[1];
vector<Vertex> vertices = face.vertices;
sort(vertices.begin(), vertices.end(),
[](const Vertex &v1, const Vertex &v2)
{ return v1.x < v2.x; });
for (int i = 0; i < vertices.size(); ++i)
{
Vertex &v1 = vertices[i];
Vertex &v2 = vertices[(i + 1) % vertices.size()];
vector<float> intsc = getIntersections(v1, v2, y);
intersections.insert(intersections.end(), intsc.begin(),
intsc.end());
}
}
}
sort(intersections.begin(), intersections.end());
for (int i = 0; i < intersections.size(); i += 2)
{
glBegin(GL_LINES);
glVertex3f(intersections[i], y, 0.0);
glVertex3f(intersections[i + 1], y, 0.0);
glEnd();
}
intersections.clear();
}
glEnable(GL_LIGHTING);
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {100.0};
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
Pyramid pyramid({Polygon({Vertex(0.0, 0.0, 0.0),
Vertex(1.0, 0.0, 0.0),
Vertex(1.0, 1.0, 0.0),
Vertex(0.0, 1.0, 0.0)}),
Polygon({Vertex(0.5, 0.5, 1.0),
Vertex(0.0, 0.0, 0.0),
Vertex(1.0, 0.0, 0.0)}),
Polygon({Vertex(0.5, 0.5, 1.0),
Vertex(1.0, 0.0, 0.0),
Vertex(1.0, 1.0, 0.0)}),
Polygon({Vertex(0.5, 0.5, 1.0),
Vertex(1.0, 1.0, 0.0),
Vertex(0.0, 1.0, 0.0)}),
Polygon({Vertex(0.5, 0.5, 1.0),
Vertex(0.0, 1.0, 0.0),
Vertex(0.0, 0.0, 0.0)})});
drawPyramid(pyramid);
scanLineAlgorithm(pyramid);
glutSwapBuffers();
}
void init()
{
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glClearColor(1.0, 1.0, 1.0, 0.0);
}
void reshape(GLsizei width, GLsizei height)
{
glViewport(0, 0, width, height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
}
int main(int argc, char **argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
glutInitWindowSize(640, 480);
glutInitWindowPosition(100, 100);
glutCreateWindow("Scan Line Algorithm");
glutDisplayFunc(display);
glutReshapeFunc(reshape);
init();
glutMainLoop();
return 0;
}


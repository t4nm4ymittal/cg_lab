#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
void init(){
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,500,0,500);
}
void bound_it(int x, int y, float* fillColor, float* bc) {
 float color[3];
 glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
 if((color[0]!=bc[0]||color[1]!=bc[1]||color[2]!=bc[2])&&(color[0]!=fillColor[0] || 
color[1]!=fillColor[1] || color[2]!=fillColor[2])){
 glColor3f(fillColor[0],fillColor[1],fillColor[2]);
 glBegin(GL_POINTS);
 glVertex2i(x,y);
 glEnd();
 glFlush();
 bound_it(x+1,y,fillColor,bc);
 bound_it(x-1,y,fillColor,bc);
 bound_it(x,y+1,fillColor,bc);
 bound_it(x,y-1,fillColor,bc);
 bound_it(x+1,y+1,fillColor,bc);
 bound_it(x-1,y-1,fillColor,bc);
 bound_it(x+1,y-1,fillColor,bc);
 bound_it(x-1,y+1,fillColor,bc);
 }
}
void world(){
 int N,i,a,b;
 glLineWidth(2);
 glPointSize(1);
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1,0,0);
 glBegin(GL_LINE_LOOP);
 printf("Enter number of vertices: ");
 scanf("%d",&N);
 printf("Enter vertices in anticlockwise manner:\n");
 for (i=0;i<N;i++)
 {
 printf("Enter X-Coordinate for %d vertex: ",(i+1));
scanf("%d",&a);
 printf("Enter Y-Coordinate for %d vertex: ",(i+1));
 scanf("%d",&b);
 glVertex2i(a,b);
 }
 glEnd();
 glFlush();
 float bCol[] = {1,0,0};
 float color[] = {0,0,1};
 bound_it(a+2,b-2,color,bCol);
}
int main(int argc, char** argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(200,200);
 glutCreateWindow("Polygon Filling");
 glutDisplayFunc(world);
 init();
 glutMainLoop();
 return 0;
}


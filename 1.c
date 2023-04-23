#include <stdio.h>
#include <GL/glut.h>
int X1,X2,Y1,Y2;
void myInit(void)
{
 glClearColor(0.0, 0.0, 0.0, 1.0);
 glColor3f(0.0, 0.0, 1.0);
 glPointSize(5.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-50, 50, -50, 50);
}
void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_POINTS);
 glColor3f(0.0,1.0,0.0);
 // PLotting xy plane
 for (int y = -400; y <= 400; y += 1){
 glVertex2f(0, y);
 }
 for (int x = -300; x <= 300; x += 1){
 glVertex2f(x, 0);
 }
 glEnd();
 int di = 2*(Y2-Y1)-(X2-X1);
 int y=Y1;
 glBegin(GL_POINTS);
 glColor3f(1,0,0);
 for(int x = X1;x<=X2&&y<=Y2;x++){
 glVertex2f(x,y);
 if(di>0){
 y++;
 di += 2*((Y2-Y1)-(X2-X1));
 }
 else{
 di+= 2*(Y2-Y1);

 }
 }
 glEnd();
 glFlush();
}
int main(int argc, char **argv)
{
 printf("Enter x1: ");
 scanf("%d",&X1);
 printf("Enter x2: ");
 scanf("%d",&X2);
 printf("Enter y1: ");
 scanf("%d",&Y1);
 printf("Enter y2: ");
 scanf("%d",&Y2);
 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(1000, 1000);
 glutInitWindowPosition(0, 0);
 glutCreateWindow("Original ViewPort");
 myInit();
 
 glutDisplayFunc(display);
 glutMainLoop();
}

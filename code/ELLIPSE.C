/*******Roll no 27***********Gurpreet singh************MCA-I*******/
/*******************************************************************
	  Program to welcome diwali using graphics.
 *******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
#define round(a) ((int)(a+0.5))
void ellipseplotpoints(int xcenter, int ycenter,int rx,int ry);
main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int x,y,xcenter,radius,ycenter;
   int p,rx,ry,rx2,ry2,tworx2,twory2;
   int px,py;
   clrscr();
   printf("Enter center position of ellipse.  ");
   printf("\nX = ");
   scanf("%d",&xcenter);
   printf("\nY = ");
   scanf("%d",&ycenter);
   printf("\n\nEnter x radius of ellipse. ");
   printf("\nRx = ");
   scanf("%d",&rx);
   printf("\n\nEnter y radius of ellipse. ");
   printf("\nRy = ");
   scanf("%d",&ry);
   initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
   setcolor(RED);
   settextstyle(1,0,4);
   outtextxy(65,30,"ALGORITHM TO DRAW ELLIPSE");
   x=0;
   y=ry;
   rx2=rx*rx;
   ry2=ry*ry;
   tworx2=2*rx2;
   twory2=2*ry2;
   px=0;
   py=tworx2*y;
   ellipseplotpoints(xcenter,ycenter,x,y);
   p=round(ry2-(rx2*ry)+(0.25*rx2));
   while(px<py)
   {
     x++;
     px+=twory2;
     if(p<0)
       p+=ry2+px;
     else
     {
       y--;
       py-=tworx2;
       p+=ry2+px-py;
     }
     ellipseplotpoints(xcenter,ycenter,x,y);
   }
   p=round(ry2*(x+0.5)*(x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2);
   while(y>0)
   {
   y--;
   py-=tworx2;
   if(p>0)
     p+=rx2-py;
   else
   {
      x++;
      px+=twory2;
      p+=rx2-py+px;
   }
     ellipseplotpoints(xcenter,ycenter,x,y);
   }
   getch();
   closegraph();
}
void ellipseplotpoints(int xcenter,int ycenter,int x, int y)
{
putpixel(xcenter+x,ycenter+y,RED);
putpixel(xcenter-x,ycenter+y,RED);
putpixel(xcenter+x,ycenter-y,RED);
putpixel(xcenter-x,ycenter-y,RED);
}



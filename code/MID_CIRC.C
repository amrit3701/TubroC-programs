/*******************************************************************
	  Program to draw circle midpoint circle algorithn.
 *******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
void circleplotpoints(int xcenter, int ycenter,int x,int y);
main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int x,y,xcenter,radius,ycenter;
   int p=1-radius;
   clrscr();
   printf("Enter center position of circle.  ");
   printf("\nX = ");
   scanf("%d",&xcenter);
   printf("\nY = ");
   scanf("%d",&ycenter);
   printf("\n\nEnter radius of circle. ");
   printf("\nRadius = ");
   scanf("%d",&radius);
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
   outtextxy(65,30,"MId-POINT ALGORITHM OF CIRCLE");
   x=0;
   y=radius;
   p=1-radius;
   circleplotpoints(xcenter,ycenter,x,y);
   while(x<y)
   {
   x++;
   if(p<0)
   p+=2*x+1;
   else
   {
   y--;
   p+=2*(x-y)+1;
   }
   circleplotpoints(xcenter,ycenter,x,y);
   }
   getch();
   closegraph();
}
void circleplotpoints(int xcenter,int ycenter,int x, int y)
{
putpixel(xcenter+x,ycenter+y,RED);
putpixel(xcenter-x,ycenter+y,RED);
putpixel(xcenter+x,ycenter-y,RED);
putpixel(xcenter-x,ycenter-y,RED);
putpixel(xcenter+y,ycenter+x,RED);
putpixel(xcenter-y,ycenter+x,RED);
putpixel(xcenter+y,ycenter-x,RED);
putpixel(xcenter-y,ycenter-x,RED);
}



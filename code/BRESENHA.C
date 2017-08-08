/*******************************************************************
	  Program to welcome diwali using graphics.
 *******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
#define round(a)  ((int)(a+0.5))
 main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int x,y,dx,dy;
   int p,twody,twodydx,xend;
   int xa,ya,xb,yb;
   float xincrement,yincrement;
   clrscr();
   printf("Enter start position of line.  ");
   printf("\nX = ");
   scanf("%d",&xa);
   printf("\nY = ");
   scanf("%d",&ya);
   printf("\n\nEnter start position of line.  ");
   printf("\nX = ");
   scanf("%d",&xb);
   printf("\nY = ");
   scanf("%d",&yb);
//   xa=100;ya=200;xb=400;yb=200;
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
   outtextxy(50,30,"BRESENHAM ALGORITHM OF LINE");
   dx=abs(xb-xa);
   dy=abs(yb-ya);
   twody=2*dy;twodydx=2*(dy-dx);
   p=2*dy-dx;
   if(xa>xb)
   {
     x=xb;
     y=yb;
     xend=xa;
   }
   else
   {
     x=xa;
     y=ya;
     xend=xb;
   }
   putpixel(x,y,RED);
   while(x<xend)
   {
     x++;
     if(p<0)
     p+=twody;
     else
     {
     y++;
     p+=twodydx;
     }
     putpixel(x,y,RED);
   }
   getch();
   closegraph();
   }




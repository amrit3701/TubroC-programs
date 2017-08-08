/*******************************************************************
    Program to display animated circle.
 ******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
//char *buffer1;
int main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int radius = 40;
   long size;
   char *buffer;
   int x,y,i,color=1;
   int s,t,rad,k;
   initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
   midx=getmaxx()/2;
   midy=getmaxy()/2;
   do
   {
   rad=midy;
   s=0;t=180;
   for(;rad>=0;)
   {
   for(k=s;k<=180;k++)
   {
     x=rad*cos(k*3.14/180)+midx;
     y=midy-rad*sin(k*3.14/180);
     delay(0);
     if(kbhit()){closegraph();exit(1);}
     putpixel(x,y,color);
   }
   s=180;t=360;
   for(k=s;k<=t;k++)
   {
     x=rad*cos(k*3.14/180)+midx;
     y=midy+abs(rad*sin(k*3.14/180));
     delay(0);
     putpixel(x,y,color);
   }
   s=0;t=180;
   rad-=5;
   }
   color++;
   }while(1);
    getch();
   closegraph();
   }

/******************************************************************************
                            OUTPUT
******************************************************************************/


  

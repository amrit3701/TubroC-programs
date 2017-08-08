/*******************************************************************
       Program to diplay bouncing ball using graphics.
*******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
int main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int radius = 20;
   long size;
   char *buffer;
   int x,y,i;
   initgraph(&gdriver, &gmode, "c:\\tc\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }
   settextstyle(TRIPLEX_FONT,0,5);
   setcolor(8);
   outtextxy(150,100,"BOUNCING BALL");
   midx = getmaxx() / 2;
   midy = getmaxy() / 2;
   setcolor(RED);
   circle(midx, midy, radius);
   setfillstyle(9,RED);
   floodfill(midx,midy,RED);
   size=imagesize(midx-20,midy-20,midx+20,midy+20);
   buffer=(char far *)malloc(size);
   getimage(midx-20,midy-20,midx+20,midy+20,buffer);
   putimage(midx-20,midy-20,buffer,XOR_PUT);
   setcolor(WHITE);
   line(0,440,639,440);
   delay(1000);
   do
   {
    y=280;
    x=0;
    do
    {
    for(i=0;i<180;i+=3)
    {
      if(i<=90)
      y=y+5*cos(i*22/(7*180));
      if(i>90)
      y=y-5*cos((i-90)*22/(7*180));
      if(i==90)
      sound(1000);
      putimage(x*180+i,y,buffer,XOR_PUT);
      delay(30);
      putimage(x*180+i,y,buffer,XOR_PUT);
      if(kbhit()){closegraph();exit(1);}
      nosound();
    }
     x++;
     }while(x<4);
   }while(!kbhit());
   getch();
   closegraph();
   return 0;
   }
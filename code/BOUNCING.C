#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

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
   x=midx-20;y=100;
   setcolor(WHITE);
   do
   {
   for(i=y;i<400;i++)
   {
   putimage(x,i,buffer,XOR_PUT);
   delay(2);
   putimage(x,i,buffer,XOR_PUT);
   if(kbhit()){closegraph();exit(1);}
   }
   for(i=400;i>y;i--)
   {
   putimage(x,i,buffer,XOR_PUT);
   delay(2);
   putimage(x,i,buffer,XOR_PUT);
   if(kbhit()){closegraph();exit(1);}
   }
   y=y+y/4;
   }while(y<390);
   for(i=y;i<400;i++)
   {
   putimage(x,i,buffer,XOR_PUT);
   delay(2);
   putimage(x,i,buffer,XOR_PUT);
   if(kbhit()){closegraph();exit(1);}
   }
      putimage(midx-20,400,buffer,XOR_PUT);

   getch();
   closegraph();
   return 0;
}

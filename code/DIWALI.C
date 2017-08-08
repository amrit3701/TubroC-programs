/*******************************************************************
	  Program to welcome diwali using graphics.
 *******************************************************************/
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include<math.h>
#include<dos.h>
void star(int x,int y,int color);
void move();
char *buffer1;
int main(void)
{
   int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int radius = 40;
   long size;
   char *buffer;
   int x,y,i;
   int s,t;
//   long size;
  // char *buffer;
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
   setcolor(BROWN);
   outtextxy(100,420,"HAPPY");
   outtextxy(400,420,"DIWALI");
   settextstyle(0,0,1);
    outtextxy(510,470,"GURPREET SINGH");

   midx = getmaxx() / 2;
   midy = getmaxy() / 2;
   s=210;t=330;
   setcolor(8);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(RED);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(8);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(RED);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(8);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(RED);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(8);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   setcolor(RED);
   for(i=0;i<5;i++)
   arc(midx,midy--,s,t,radius--);
   midy=getmaxy()/2;
   size=imagesize(midx-40,midy-40,midx+40,midy+40);
   buffer=(char far *)malloc(size);
   getimage(midx-40,midy-40,midx+40,midy+40,buffer);
   putimage(midx-40,midy-40,buffer,XOR_PUT);
   putimage(midx-40,midy+150,buffer,XOR_PUT);
   move();
   getch();
   closegraph();
   }
void move()
{
  int sx,sy;
  int ex,ey,ex1,ey1,ex2,ey2;
  int i,k,l,rad[18],r[10];
  int color=2,timer=120,p;
  int soun=1000,s;
  for(i=0;i<18;i++)
  rad[i]=500-25*i;
  for(i=0;i<10;i++)
  r[i]=10+i*25;
  sx=getmaxx()/2;
  sy=getmaxy()/2+150;
  delay(3000);
  s=0;
  do
  {
//  s--;
//  if(s==-1)s++;
  for(i=180,l=0;i>=0;l++,i--)
  {
    sound(soun);
    if(soun==3000)
    p=1;
    if(soun==1500)
    p=0;
    if(p==1)
    soun--;
    else soun++;
    for(k=s;k<=17;k++)
    {
    ex1=rad[k]*cos(i*3.14/180)+sx+rad[k];
    ey1=sy-rad[k]*sin(i*3.14/180);
    putpixel(ex1,ey1,color);
    ex2=rad[k]*cos(l*3.14/180)+sx-rad[k];
    ey2=sy-rad[k]*sin(l*3.14/180);
    putpixel(ex2,ey2,color);
    if(kbhit()){nosound();closegraph();exit(1);}
    }
//    if(s==0)
    for(k=0;k<10;k++)
    {
    ex1=500*cos(i*3.14/180)+sx+500;
    ey1=sy-500*sin(i*3.14/180)-r[k];
    putpixel(ex1,ey1,color);
    ex2=500*cos(l*3.14/180)+sx-500;
    ey2=sy-500*sin(l*3.14/180)-r[k];
    putpixel(ex2,ey2,color);
    }
    color++;
    if(timer==0)
    timer++;
    delay(timer--);
  }
  }while(1);
  }

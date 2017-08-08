/**********************************************************************
		    Program to draw polygon
**********************************************************************/
#include<math.h>
#include<stdio.h>
#include<graphics.h>
#define pi 22/7
main()
{
  int gd=DETECT,gm,x,y,maxx,maxy,midx,midy;
  int r,num,angle,i;
  printf("Enter number of sides<=6.\n\n");
  printf("Sides = ");
  scanf("%d",&num);
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  maxx=getmaxx();
  maxy=getmaxy();
  midx=maxx/2;
  midy=maxy/2;
  setcolor(RED);
  settextstyle(TRIPLEX_FONT,0,5);
  outtextxy(230,120,"POLYGON");
  r=50;
  angle=360/num;
  for(i=0;i<num-1;i++)
  {
    line(midx+r*cos(i*angle*pi/180),midy+r*sin(i*angle*pi/180),
     midx+r*cos((i+1)*angle*pi/180),midy+r*sin((i+1)*angle*pi/180));
  }
    line(midx+r*cos(i*angle*pi/180),midy+r*sin(i*angle*pi/180),
     midx+r*cos(0),midy+r*sin(0));

  getch();
  closegraph();
}
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
int maxx,maxy,midx,midy;
int x,y;
void enemy(void);
main()
{
int gd=DETECT,gm,errorcode;
initgraph(&gd,&gm,"c:\\tc\\bgi");
errorcode=graphresult();
if(errorcode!=grOk)
{
  printf("Graphics mode is not initialised.");
  getch();
  exit(1);
}
maxx=getmaxx();
maxy=getmaxy();
midx=maxx/2;
midy=maxy/2;
enemy();
getch();
closegraph();
return 0;
}
void enemy(void)
{
  setcolor(DARKGRAY);
  ellipse(midx,midy,0,360,12,22);
  setfillstyle(1,DARKGRAY);
  floodfill(midx,midy,DARKGRAY);
}
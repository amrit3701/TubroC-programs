#include<graphics.h>
#include<stdlib.h>
#include<string.h>
void main()
{
int graphdriver=VGA,graphmode=VGAHI,errorcode;
int i,xmax,ymax,maxcolors,x,y,color;
initgraph(&graphdriver,&graphmode,"C:\\TC\\BGI");
errorcode=graphresult();
if(errorcode!=grOk)
{
printf("Graphics System Error : %s\n",grapherrormsg(errorcode));
getch();
exit(1);
}
xmax=getmaxx();
ymax=getmaxy();
maxcolors=getmaxcolor()+1;
rectangle(240,200,400,280);
for(i=1;i<=200;i++)
{
 x=random(160);
 y=random(80);
 color=random(maxcolors);
 putpixel(240+x,200+y,color);
 delay(60);
  }
 setcolor(4);
 settextstyle(4,0,4);
 outtextxy(240,300,"WELCOME");
 getch();
 cleardevice();
 closegraph();
 }
/*Roll No-27****Gurpreet singh*****M.C.A-I******/
/*Program to display tower of hanoi*/
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
int xmax,ymax,time=0,speed1=2;
unsigned long size;
char far *buffer_rd;
char far *buffer_d1[8],*buffer_dc1[5];
void welcome();
int intput();
int error(char no_of_disc);
void rod();
void disc(int x,int y,int radx,int rady,int count);
void move_st(int sposx,int eposx,int posx,char far *buffer_d);
void move_down(int posx,int sposy,int eposy,char far *buffer_d);
void move_up(int posx,int sposy,int eposy,char far *buffer_d);
void tower_of_hanoi(char from,char to,char other,int n);
void move(char from ,char to);
void speed(char check);
typedef struct
{
int cur_x;
int cur_y;
int radx;
int rady;
int lower;
}DISC;
DISC Disc[8];
typedef struct
{
int cur_x;
int cur_y;
int no_of_disc;
int top_d_size;
}Tower;
Tower tower[3];
void main()
{
/************Declaration part start**************/
int graphdriver=VGA,graphmode=VGAHI,errorcode;
int sposx,eposx,sposy,eposy,i;
int  x,y,no_of_disc,start,tempx,tempy;
int radx,rady;
char far * buffer_d,*buffer_dc;
//************Declaration part start*************/
/************Initialise graphic mode************/
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
welcome();
cleardevice();
rectangle(0,0,xmax,ymax);
setcolor(RED);
setcolor(RED);
settextstyle(1,0,4);
outtextxy(160,20,"TOWER OF HANOI");
no_of_disc=input();
cleardevice();
setcolor(WHITE);
rectangle(0,0,xmax,ymax);
setcolor(RED);
settextstyle(1,0,4);
outtextxy(160,20,"TOWER OF HANOI");
rod();
setfillstyle(1,WHITE);
bar(0,460,639,479);
settextstyle(0,0,1);
outtextxy(30,461,"Use Esc-Exit    U-Speed up   L-Speed Down    P-paused          Gopi " );
x=60;
y=70;
if(no_of_disc==8)
start=1;
else if(no_of_disc==7)
start=2;
else if(no_of_disc==6)
start=3;
else if(no_of_disc==5)
start=4;
else if(no_of_disc==4)
start=5;
else if(no_of_disc==3)
start=6;
else if(no_of_disc==2)
start=7;
else
start=8;
sposx=1;
sposy=100;
tempx=45;
tempy=375;
radx=45;
rady=28;
for(i=8;i>=start;i--)
{
if(i==8)
Disc[i-1].lower=0;
else
Disc[i-1].lower=i+1;
Disc[i-1].radx=radx;
Disc[i-1].rady=rady;
disc(x,y,radx,rady,i);
x-=5;
Disc[i-1].cur_x=eposx=tempx;
Disc[i-1].cur_y=eposy=tempy;
tempx=tempx+5;
tempy-=2*(rady-3);
radx-=5;rady-=3;
putimage(eposx,eposy,buffer_d1[i-1],XOR_PUT);
}
tower[0].cur_x=Disc[start-1].cur_x;
tower[0].cur_y=Disc[start-1].cur_y;
tower[0].no_of_disc=no_of_disc;
tower[0].top_d_size=start;
for(i=1;i<=2;i++)
{
tower[i].no_of_disc=0;
tower[i].top_d_size=0;
tower[i].cur_x=0;
tower[i].cur_y=430;
}
getch();
tower_of_hanoi('A','C','B',no_of_disc);
getch();
closegraph();
}
void welcome()
{
int i,x,y,color;
int int_a,end_a;
x=xmax/2;
y=ymax/2;
rectangle(0,0,xmax-1,ymax-1);
setcolor(RED);
delay(1000);
for(i=0;i<=100;i++)
{
ellipse(x,y,0,360,200,i);
delay(50);
}
delay(100);
settextstyle(1,0,3);
setcolor(WHITE);
outtextxy(x-70,y-50,"WELCOME TO");
outtextxy(x-90,y+20,"TOWER OF HANOI");
do
{
int_a=0;end_a=5;
delay(200);
for(i=0;i<=360;)
{
if(i%10==0)
setcolor(WHITE);
else
setcolor(BLACK);
ellipse(x,y,int_a,end_a,200,100);
i+=5 ;
int_a=end_a;
end_a+=5;
}
int_a=0;end_a=5;
delay(200);
for(i=0;i<=360;)
{
if(i%10!=0)
setcolor(WHITE);
else
setcolor(BLACK);
ellipse(x,y,int_a,end_a,200,100);
i+=5 ;
int_a=end_a;
end_a+=5;
}
if(kbhit())break;
}while(1);
}
void move(char from,char to)
{
int tower1,tower2;
int sposx,sposy,eposx,eposy;
int i,size,lower1;
int size2;
//getch();
tower1=from-65;
tower2=to-65;
size=tower[tower1].top_d_size;
sposx=Disc[size-1].cur_x;
size2=tower[tower2].top_d_size;
sposy=Disc[size-1].cur_y;
if(tower1>tower2)
eposx=sposx-205*(tower1-tower2);
else
eposx=sposx+205*(tower2-tower1);
eposy=tower[tower2].cur_y-(Disc[size-1].rady)*2;
tower[tower1].no_of_disc--;
tower[tower2].no_of_disc++;
tower[tower1].top_d_size=Disc[size-1].lower;
lower1=Disc[size-1].lower;
if(tower[tower1].no_of_disc==0)
{
tower[tower1].cur_x=0;
tower[tower1].cur_y=430;
}
else
{
tower[tower1].cur_x=Disc[lower1-1].cur_x;
tower[tower1].cur_y=Disc[lower1-1].cur_y;
}
tower[tower2].cur_x=eposx;
tower[tower2].cur_y=eposy;
Disc[size-1].lower=tower[tower2].top_d_size;
tower[tower2].top_d_size=size;
Disc[size-1].cur_x=eposx;
Disc[size-1].cur_y=eposy;
move_up(sposx,sposy,100,buffer_d1[size-1]);
move_st(sposx,eposx,100,buffer_d1[size-1]);
move_down(eposx,100,eposy,buffer_d1[size-1]);
}
void rod()
{
int i;
int x,y;
x=65;y=150;
setcolor(BROWN);
setfillstyle(1,BROWN);
bar(xmax/2-40,ymax/2+210,xmax/2+40,ymax/2+230);
setfillstyle(1,RED);
bar(xmax/2-5,ymax/2-70,xmax/2+5,ymax/2+210);
size=imagesize(xmax/2-40,ymax/2-70,xmax/2+40,ymax/2+230);
buffer_rd=(char far *)malloc(size);
getimage(xmax/2-40,ymax/2-70,xmax/2+40,ymax/2+230,buffer_rd);
putimage(xmax/2-40,ymax/2-70,buffer_rd,XOR_PUT);
for(i=0;i<=2;i++)
{
putimage(x+i*205,y,buffer_rd,XOR_PUT);
}
}
void disc(int x,int y,int radx,int rady,int count)
{
int i;
setcolor(GREEN);
ellipse(x,y,0,360,radx,rady);
setfillstyle(9,GREEN);
floodfill(x,y,GREEN);
size=imagesize(1,y-rady,2*radx+15,y+rady);
buffer_d1[count-1]=(char far *)malloc(size);
getimage(1,y-rady,2*radx+15,y+rady,buffer_d1[count-1]);
//getch();
putimage(1,y-rady,buffer_d1[count-1],XOR_PUT);
}
void move_st(int sposx,int eposx,int posy,char far *buffer_d)
{
int i;
char check;
delay(time);
if(eposx>sposx)
for(i=sposx;i<=eposx;)
{
i=i+speed1;
if(i>eposx)i=eposx;
putimage(i,posy,buffer_d,XOR_PUT);
delay(time);
if(kbhit()){check=getch();speed(check);}
putimage(i,posy,buffer_d,XOR_PUT);
if(i==eposx)i++;
}
else
for(i=sposx;i>=eposx;)
{
i=i-speed1;
if(i<eposx)i=eposx;
putimage(i,posy,buffer_d,XOR_PUT);
delay(time);
if(kbhit()){check=getch();speed(check);}
putimage(i,posy,buffer_d,XOR_PUT);
if(i==eposx)i--;
}
}
void move_down(int posx,int sposy,int eposy,char far *buffer_d)
{
int i;
char check;
for(i=sposy;i<eposy;)
{
i=i+speed1;
if(i>eposy)i=eposy;
{
putimage(posx,i,buffer_d,XOR_PUT);
delay(time);
if(kbhit()){check=getch();speed(check);}
putimage(posx,i,buffer_d,XOR_PUT);
}
}
putimage(posx,eposy,buffer_d,XOR_PUT);
}
void move_up(int posx,int sposy,int eposy,char far *buffer_d)
{
int i;
char check;
putimage(posx,sposy,buffer_d,XOR_PUT);
for(i=sposy;i>eposy;)
{
i=i-speed1;
if(i<eposy)i=eposy;
{
putimage(posx,i,buffer_d,XOR_PUT);
delay(time);
if(kbhit()){check=getch();speed(check);}
putimage(posx,i,buffer_d,XOR_PUT);
}
}
}
void tower_of_hanoi(char from,char to,char other,int n)
{
  if(n==1)
	move(from,to);
  else
  {
	tower_of_hanoi(from,other,to,n-1);
	tower_of_hanoi(from,to,other,1);
	tower_of_hanoi(other,to,from,n-1);
    }
}
int input()
{
int x,y,p;
char st[2];
do
{
cleardevice();
x=100;
y=140;
moveto(x,y);
settextstyle(1,0,2);
outtext("Enter number of disc<=8.");
moveto(x+20,y+40);
outtext("DISC :");
x=185;y=202;
line(x,y,x+13,y);
moveto(x,y-23);
st[0]=getch();
st[1]='\0';
outtext(st);
p=error(st[0]);
if(p==1)
{getch();
return atoi(st);
}
else
{
setcolor(0);
rectangle(x,y-23,x+20,y+6);
rectangle(2,330,xmax-1,ymax-1);
setfillstyle(0,0);
floodfill(x+1,y-1,0);
floodfill(xmax-9,ymax-9,0);
setcolor(RED);
}
}while(1);
}
int error(char no_of_disc)
{
if(strchr("123456789",no_of_disc));
else
{
outtextxy(100,380,"   Invalid Character.");
outtextxy(100,420,"Press any key to continue......");
getch();
return 0;
}
if(strchr("12345678",no_of_disc));
else
{
outtextxy(100,380," Range lie between 1 to 3 .");
outtextxy(100,420,"Press any key to continue.......");
getch();
return 0;
}
return 1;
}
void speed(char check)
{
if(check=='u'||check=='U')
{
time=0;
speed1+=2;
if(speed1>=20)speed1=20;
}
else if(check=='l'||check=='L')
{
time=0;
speed1-=2;
if(speed1<1)speed1=1;
}
else if(check==27)
{
closegraph();
exit(1);
}
else if(check=='p'||check=='P')
{
setcolor(WHITE);
rectangle(250,120,360,150);
settextstyle(1,0,1);
outtextxy(275,125,"Paused");
getch();
setcolor(BLUE);
setfillstyle(0,BLACK);
bar(250,120,360,150);
}
}


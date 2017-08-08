#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
union REGS i,o;
unsigned long size;
char far *buffer[2],*buff_exit;
int x,y,midx,midy,maxx,maxy;
int incre_x=115,incre_y=100;
int score_a=0,score_b=0,turn;
int check_double;
int turn_check;
int check_rev=0;
int pre_x,pre_y;
char win_check;
char a[15],b[15],c[4];
int prev_x_a,prev_y_a,prev_x_b,prev_y_b;
int color_a,color_b;
int button,mpos_x,mpos_y;
typedef struct
{
int cur_x;
int cur_y;
int status;
}DISC;
DISC disc[2][12];
typedef struct
{
int status;
int player;
}Bara;
Bara bara[5][5];
void welcome_screen(void);
void pre_face(void);
void Disc(int player,int color,int sx,int sy);
int turna(int player);
int check_diagonal(int start_x,int start_y);
void error(int errorno);
int check_turn(int,int,int,int,int,int);
check_mousepos(int player,int mpos_x,int mpos_y);
draw_dotted_box(int sx,int sy,int color);
int input_name(int player);
void input_screen(void);
void exit_screen(void);
int check_exit(void);
void pre_check_exit(void);
int main()
{
  int gd=VGA,gm=VGAHI,errorcode;
  int player;
  char ch;
  int check_ex,check_deal;
  /*
  puts("Enter first player name.");
  gets(a);
  puts("Enter second player name.");
  gets(b);
  */
   /*
   errorcode = registerbgidriver(EGAVGA_driver);
  if(errorcode!=grOk)
  {
    printf("\n Unable to register EGAVGA driver...");
    exit(1);
  }
  errorcode=registerbgifont(triplex_font);
  if(errorcode!=grOk)
  {
    printf("\n Unable to register font...");
    exit(1);
  }
  errorcode=registerbgifont(small_font);
  if(errorcode!=grOk)
  {
    printf("\n Unable to register font...");
    exit(1);
  }
  */
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  errorcode = graphresult();
  if (errorcode != grOk)  /* an error occurred */
  {
     printf("Graphics error: %s\n", grapherrormsg(errorcode));
     printf("Press any key to halt:");
     getch();
     exit(1); /* terminate with an error code */
  }
  /*
  ///if(i==1)
    Disc(1,1,465,170);
  //  else
    Disc(2,4,465,280);
    */
  maxx=getmaxx();
  maxy=getmaxy();
  midx=maxx/2;
  midy=maxy/2;
  exit_screen();
  welcome_screen();
  start:
  score_a=0;
  score_b=0;
  cleardevice();
  input_screen();
  hidemouseptr();
  cleardevice();
  pre_face();
  if(initmouse()==0)
  {
    closegraph();
    printf("\nMouse driver not loaded.");
    getch();
    exit(1);
  }
  restrictmouseptr(0,0,maxx-1,maxy-1);
  showmouseptr();
  turn_check=1;
  win_check=0;
  do
  {
    do
    {
      check_deal=turna(1);
      if(check_deal==1)
	goto start;
      if((check_deal==2)&&(check_rev==2))
	break;
      if(score_a==12)
      {
	win_check=1;
	break;
      }
      if(kbhit())
      {
	ch=getch();
	if((ch=='c'||ch=='C')&&(check_rev==2))
	break;
	if(ch=='e'||ch=='E')
	{
	  /*
	  hidemouseptr();
	  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
	  showmouseptr();
	  check_exit();
	  //closegraph();
	 // exit(1);
	  */
	  pre_check_exit();
	}
      }
    }while(turn_check==1);
    putimage(555,90,buffer[0],XOR_PUT);
    putimage(555,90,buffer[1],XOR_PUT);
    showmouseptr();
    check_rev=0;
    turn_check=1;
    if(win_check==1)
    break;
    do
    {
      //turna(2);
      check_deal=turna(2);
      if(check_deal==1)
	goto start;
      if((check_deal==2)&&(check_rev==2))
	break;
      if(score_b==12)
      {
	win_check=1;
	break;
      }
      if(kbhit())
      {
	ch=getch();
	if((ch=='c'||ch=='C')&&(check_rev==2))
	break;
	if(ch=='e'||ch=='E')
	{
	  pre_check_exit();
	  /*
	  hidemouseptr();
	  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
	  showmouseptr();
	  check_exit();
	  //closegraph();
	  //exit(1);
	  */
	}
      }
    }while(turn_check==1);
    if(win_check==1)
    break;
    turn_check=1;
    putimage(555,90,buffer[1],XOR_PUT);
    putimage(555,90,buffer[0],XOR_PUT);
    showmouseptr();
    check_rev=0;
  }while(!kbhit());
  win_check=1;
  if(win_check==1)
  {
    setcolor(LIGHTGRAY);
    setfillstyle(1,LIGHTGRAY);
    bar(100,100,540,380);
    setcolor(DARKGRAY);
    rectangle(105,105,535,375);
    rectangle(110,110,530,370);
    settextstyle(1,0,4);
    settextjustify(1,1);
    outtextxy(midx,130,"CONGRATULATIONS");
    if(score_a==12)
    outtextxy(midx,200,a);
    if(score_b==12)
    outtextxy(midx,200,b);
    settextstyle(1,0,2);
    outtextxy(midx,270,"You have win the game.");
//    settextjustify(3,1);
    settextstyle(1,0,1);
    outtextxy(midx,355,"Press any key to continue....");
    getch();
  }
  cleardevice();
  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
  check_ex=check_exit();
  if(check_ex==1)
  goto start;
//  getch();
  closegraph();
  return 0;
}
void welcome_screen(void)
{
  setfillstyle(1,LIGHTGRAY);
  bar(midx-280,midy-200,midx+280,midy+200);
  setcolor(RED);
  rectangle(midx-275,midy-195,midx+275,midy+195);
  rectangle(midx-270,midy-190,midx+270,midy+190);
  settextstyle(1,0,5);
  setcolor(YELLOW);
  outtextxy(midx,midy-150,"WELCOME");
  outtextxy(midx,midy-80,"TO");
  outtextxy(midx,midy-10,"BAARA TANNI");
  outtextxy(midx,midy+60,"GAME");
  settextstyle(2,0,5);
  setcolor(YELLOW);
  settextjustify(0,1);
  outtextxy(midx+115,midy+100,"Developed By:");
  outtextxy(midx+115,midy+120,"Gurpreet Singh");
  outtextxy(midx+115,midy+140,"Roll No - 27");
  outtextxy(midx+115,midy+160,"Class - M.C.A-II(sem) ");
  delay(10000);
  //getch();
}
void pre_face()
{
  int player;
  int i,j;
  int pos_x,pos_y;
  cleardevice();
  Disc(1,color_a,midx,midy);
  cleardevice();
  Disc(2,color_b,midx,midy);
  cleardevice();
  setcolor(RED);
  settextstyle(TRIPLEX_FONT,0,3);
  outtextxy(320,5,"BAARA TANNI");
  setcolor(WHITE);
  rectangle(20,45,480,445);
  line(20,45,480,445);
  line(20,445,480,45);
  line(250,45,250,445);
  line(20,245,480,245);
  line(250,45,20,245);
  line(20,245,250,445);
  line(250,445,480,245);
  line(480,245,250,45);
  line(135,45,135,445);
  line(365,45,365,445);
  line(20,145,480,145);
  line(20,345,480,345);
  pos_x=5;
  pos_y=30;
  x=1;y=1;
  for(i=0;i<12;i++)
  {
    disc[0][i].cur_x=x;
    disc[0][i].cur_y=y;
    putimage(pos_x+incre_x*(x-1),pos_y,buffer[0],XOR_PUT);
    disc[0][i].status=1;
    bara[x-1][y-1].status=1;
    bara[x-1][y-1].player=1;
    x++;
    if((i+1)%5==0)
    {
    pos_y+=incre_y;
    pos_x=5;
    y++;
    x=1;
    }
  }
  pos_x=5;
  pos_y=430;
  x=5;y=5;
  for(i=11;i>=0;i--)
  {
    disc[1][i].cur_x=x;
    disc[1][i].cur_y=y;
    putimage(pos_x+incre_x*(x-1),pos_y,buffer[1],XOR_PUT);
    disc[1][i].status=1;
    bara[x-1][y-1].status=1;
    bara[x-1][y-1].player=2;
    x--;
    if(i==7||i==2)
    {
    pos_y-=incre_y;
    pos_x=5;
    y--;
    x=5;
    }
  }
  bara[2][2].status=0;
  bara[2][2].player=0;
//  setcolor(CYAN);
  /*
  bar(505,370,640,470);
  setcolor(BLACK);
  rectangle(510,375,635,465);
  rectangle(515,380,630,460);
  setcolor(BLACK);
  settextstyle(0,0,1);
  outtextxy(550,380,"Message");
  */
  setfillstyle(1,LIGHTGRAY);
  bar(500,45,639,445);
  setcolor(RED);
  rectangle(505,50,634,440);
  rectangle(510,55,629,435);
  rectangle(515,65,624,155);
  rectangle(515,165,624,255);
  rectangle(515,265,624,355);
  setcolor(LIGHTGRAY);
  line(524,165,570,165);
  line(524,265,570,265);
  settextjustify(1,1);
  settextstyle(2,0,4);
  setcolor(BLACK);
  outtextxy(547,165,"Player-A");
  outtextxy(547,265,"Player-B");
  setfillstyle(SOLID_FILL,CYAN);
  setcolor(WHITE);
  settextstyle(0,0,1);
  outtextxy(570,75,"TURN");
  putimage(555,90,buffer[0],COPY_PUT);
  outtextxy(570,180,a);
  putimage(555,195,buffer[0],COPY_PUT);
  outtextxy(565,240,"Score: ");
  itoa(score_a,c,10);
  outtextxy(600,240,c);
  outtextxy(570,280,b);
  putimage(555,295,buffer[1],COPY_PUT);
  outtextxy(565,340,"Score : ");
  itoa(score_b,c,10);
  outtextxy(600,340,c);
  setfillstyle(1,CYAN);
  settextstyle(2,0,4);
  bar(545,130,595,145);
  rectangle(545,130,595,145);
  outtextxy(570,136,"Change");
  bar(545,370,595,385);
  rectangle(545,370,595,385);
  outtextxy(570,377,"Deal");
  bar(545,400,595,415);
  rectangle(545,400,595,415);
  outtextxy(570,407,"Exit");
  setcolor(WHITE);
  bar(0,461,maxx-1,maxy-1);
  settextstyle(0,0,1);
  outtextxy(320,470,"Press   C: To change turn    E: To Exit    Use: Mouse to move disc  ");
  settextstyle(0,0,1);
}
void Disc(int player,int color,int sx,int sy)
{
  setfillstyle(SOLID_FILL,0);
  setcolor(BLACK);
  bar(sx-15,sy-15,sx+15,sy+15);
  setcolor(color);
  circle(sx,sy,15);
  setfillstyle(SOLID_FILL,color);
  floodfill(sx,sy,color);
  size=imagesize(sx-15,sy-15,sx+15,sy+15);
  if((buffer[player-1]=(char far *)malloc(size))==NULL)
  {
    printf("Not enough memory");
    getch();
    exit(1);
  }
  getimage(sx-15,sy-15,sx+15,sy+15,buffer[player-1]);
  return;
}
initmouse()
{
  i.x.ax=0;
  int86(0x33,&i,&o);
  return(o.x.ax);
}
showmouseptr()
{
  i.x.ax=1;
  int86(0x33,&i,&o);
   return;
}
hidemouseptr()
{
  i.x.ax=2;
  int86(0x33,&i,&o);
  return;
}
restrictmouseptr(int x1,int y1,int x2,int y2)
{
  i.x.ax=7;
  i.x.cx=x1;
  i.x.dx=x2;
  int86(0x33,&i,&o);
  i.x.ax=8;
  i.x.cx=y1;
  i.x.dx=y2;
  int86(0x33,&i,&o);
  return;
}
getmousepos(int *button,int *x,int *y)
{
  i.x.ax=3;
  int86(0x33,&i,&o);
  *button=o.x.bx;
  *x=o.x.cx;
  *y=o.x.dx;
  return;
}
int turna(int player)
{
  int i,j,k,p,r;
  int pos_x,pos_y,des_x,des_y,check=0,check_back;
  int check_t;
  do
  {
    start:
    check=0;
    check_back=1;
    getmousepos(&button,&mpos_x,&mpos_y);
    if(button&1==1)
    {
      if((mpos_x>=545)&&(mpos_x<=595)
	 &&(mpos_y>=130)&&(mpos_y<=145))
      {
	hidemouseptr();
	setcolor(WHITE);
	rectangle(546,131,594,144);
	showmouseptr();
	while(button&1==1)
	  getmousepos(&button,&mpos_x,&mpos_y);
	hidemouseptr();
	setcolor(CYAN);
	rectangle(546,401,594,414);
	showmouseptr();
	return 2;
      }
      if((mpos_x>=545)&&(mpos_x<=595)
	 &&(mpos_y>=370)&&(mpos_y<=385))
      {
	hidemouseptr();
	setcolor(WHITE);
	rectangle(546,371,594,384);
	showmouseptr();
	while(button&1==1)
	  getmousepos(&button,&mpos_x,&mpos_y);
	hidemouseptr();
	return 1;
      }
      if((mpos_x>=545)&&(mpos_x<=595)
	 &&(mpos_y>=400)&&(mpos_y<=415))
      {
	hidemouseptr();
	setcolor(WHITE);
	rectangle(546,401,594,414);
	showmouseptr();
	while(button&1==1)
	  getmousepos(&button,&mpos_x,&mpos_y);
	hidemouseptr();
	setcolor(CYAN);
	rectangle(546,401,594,414);
	pre_check_exit();
      }
    }
    if(button&1==1)
    {
      pos_x=20;
      pos_y=45;
      hidemouseptr();
      for(i=0;i<=4;i++)
      {
      for(j=0;j<=4;j++)
      {
	x=pos_x+i*incre_x;
	y=pos_y+j*incre_y;
	if(mpos_x>=(x-15)&&mpos_y>=(y-15)&&
	   mpos_x<=(x+15)&&mpos_y<=(y+15))
	{
	  if((bara[i][j].status==0)||(bara[i][j].status==2))
	  {
	    goto start;
	  }
	  else if(bara[i][j].player!=player)
	  {
	    goto start;
	  }
	  while((button&1)==1)
	  {
	    if(check==0)
	    {
	      putimage(x-15,y-15,buffer[player-1],XOR_PUT);
	      check=1;
	    }
	    else
	    {
	       delay(150);
	       putimage(mpos_x-15,mpos_y-15,buffer[player-1],XOR_PUT);
	    }
	    getmousepos(&button,&mpos_x,&mpos_y);
	    putimage(mpos_x-15,mpos_y-15,buffer[player-1],XOR_PUT);
	  }
	  if(check==1)
	  putimage(mpos_x-15,mpos_y-15,buffer[player-1],XOR_PUT);
	}
	if(check==1)
	break;
      }
      if(check==1)
      break;
      }
    }
    if(check==1)
    for(p=0;p<=4;p++)
    for(r=0;r<=4;r++)
    {
       des_x=pos_x+p*incre_x;
       des_y=pos_y+r*incre_y;
       if(mpos_x>=(des_x-15)&&mpos_y>=(des_y-15)&&
	   mpos_x<=(des_x+15)&&mpos_y<=(des_y+15))
       {
	 check_back=0;
	 if(bara[p][r].status==0)
	 {
	   check_t=check_turn(i,j,p,r,player-1,check_rev);
	   check_rev=check_t;
	   if(check_t==1||check_t==2)
	   {
	     putimage(des_x-15,des_y-15,buffer[player-1],XOR_PUT);
	     check_double=1;
	     return 0;
	   }
	   else
	   {
	     putimage(x-15,y-15,buffer[player-1],XOR_PUT);
	     if(check_rev==3) return 0;
	     else
	     goto start;
	   }
	 }
	 else
	 {
	   putimage(x-15,y-15,buffer[player-1],XOR_PUT);
	   goto start;
	 }
       }
    }
    if(check_back==0&&check==1);
    else
    if(check==1)
    putimage(x-15,y-15,buffer[player-1],XOR_PUT);
    showmouseptr();
  }while(!kbhit());
  return 0;
}
int check_turn(int start_x,int start_y,int end_x,int end_y,int player,int turn1)
{
  int i,j;
  int middle_x,middle_y,ano_player;
  int check_x,check_y;
  char ch[3];
  if(player==0)
  ano_player=1;
  else
  ano_player=0;
  for(i=0;i<12;i++)
  {
   if((disc[player][i].cur_x==start_x+1)&&(disc[player][i].cur_y==start_y+1))
   break;
  }
  if(((abs(start_y-end_y)==1)||(abs(start_x-end_x)==1))&&
       ((abs(start_y-end_y)<=1)&&(abs(start_x-end_x)<=1)))
  {
    x=y=0;
    turn_check=0;
    if((abs(start_y-end_y)==1)&&(abs(start_x-end_x)==1))
    {
      if(check_diagonal(start_x,start_y)==0)
      {
	putimage(5+incre_x*start_x,30+incre_y*start_y,buffer[player],XOR_PUT);
	return 0;
      }
    }
    if(turn1==2)
    {
      putimage(5+incre_x*start_x,30+incre_y*start_y,buffer[player],XOR_PUT);
      return 3;
    }
    disc[player][i].cur_x=end_x+1;
    disc[player][i].cur_y=end_y+1;
    bara[start_x][start_y].status=0;
    bara[end_x][end_y].status=1;
    bara[start_x][start_y].player=0;
    bara[end_x][end_y].player=player+1;
    return 1;
  }
  if((abs(start_y-end_y)==0)&&(abs(start_x-end_x)==2))
  {
    if(end_x>start_x)
    middle_x=start_x+1;
    else
    middle_x=end_x+1;
    if(bara[middle_x][end_y].player==ano_player+1)
    {
      check_x=pre_x;
      check_y=pre_y;
      if((check_rev==0)||((check_rev==2)&&(pre_x==start_x)&&(pre_y==start_y)))
      {
      pre_x=end_x;
      pre_y=end_y;
      bara[middle_x][end_y].status=0;
      bara[middle_x][end_y].player=0;
      disc[player][i].cur_x=end_x+1;
      disc[player][i].cur_y=end_y+1;
      putimage(5+incre_x*middle_x,30+incre_y*start_y,buffer[ano_player],XOR_PUT);
      if(player==0)
      {
	setcolor(LIGHTGRAY);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
	//setfillstyle(1,BLACK);
	//bar(585,215,639,225);
	score_a++;
	setcolor(WHITE);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
      }
      else
      {
	setcolor(LIGHTGRAY);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
	//setfillstyle(1,BLACK);
	//bar(585,315,639,325);
	score_b++;
	setcolor(WHITE);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
      }
      bara[start_x][start_y].status=0;
      bara[end_x][end_y].status=1;
      bara[start_x][start_y].player=0;
      bara[end_x][end_y].player=player+1;
      for(i=0;i<12;i++)
      {
	if((disc[ano_player][i].cur_x==middle_x+1)&&
		     (disc[ano_player][i].cur_y==start_y+1))
	{
	  disc[ano_player][i].cur_x=0;
	  disc[ano_player][i].cur_y=0;
	  disc[ano_player][i].status=0;
	  break;
	}
      }
      turn_check=1;
      return 2;
      }
    }
  }
  if((abs(start_y-end_y)==2)&&(abs(start_x-end_x)==0))
  {
    if(end_y>start_y)
    middle_y=start_y+1;
    else
    middle_y=end_y+1;
    if(bara[end_x][middle_y].player==ano_player+1)
    {
      check_x=pre_x;
      check_y=pre_y;
      if((check_rev==0)||((check_rev==2)&&(pre_x==start_x)&&(pre_y==start_y)))
      {
      pre_x=end_x;
      pre_y=end_y;
      bara[end_x][middle_y].status=0;
      bara[end_x][middle_y].player=0;
      disc[player][i].cur_x=end_x+1;
      disc[player][i].cur_y=end_y+1;
      putimage(5+incre_x*start_x,30+incre_y*middle_y,buffer[ano_player],XOR_PUT);
      if(player==0)
      {
	setcolor(LIGHTGRAY);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
	//setfillstyle(1,BLACK);
	//bar(585,215,639,225);
	score_a++;
	setcolor(WHITE);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
      }
      else
      {
	setcolor(LIGHTGRAY);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
	//setfillstyle(1,BLACK);
	//bar(585,315,639,325);
	score_b++;
	setcolor(WHITE);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
      }
      bara[start_x][start_y].status=0;
      bara[end_x][end_y].status=1;
      bara[start_x][start_y].player=0;
      bara[end_x][end_y].player=player+1;
      for(i=0;i<12;i++)
      {
	if((disc[ano_player][i].cur_x==start_x+1)&&
		     (disc[ano_player][i].cur_y==middle_y+1))
	{
	  disc[ano_player][i].cur_x=0;
	  disc[ano_player][i].cur_y=0;
	  disc[ano_player][i].status=0;
	  break;
	}
      }
      turn_check=1;
      return 2;
      }
    }
  }
  if((abs(start_y-end_y)==2)&&(abs(start_x-end_x)==2))
  {
    if(end_y>start_y)
    middle_y=start_y+1;
    else
    middle_y=end_y+1;
    if(end_x>start_x)
    middle_x=start_x+1;
    else
    middle_x=end_x+1;
    if(bara[middle_x][middle_y].player==ano_player+1)
    {
      check_x=pre_x;
      check_y=pre_y;
      if((check_rev==0)||((check_rev==2)&&(pre_x==start_x)&&(pre_y==start_y)))
      {
      pre_x=end_x;
      pre_y=end_y;
      bara[middle_x][middle_y].status=0;
      bara[middle_x][middle_y].player=0;
      disc[player][i].cur_x=end_x+1;
      disc[player][i].cur_y=end_y+1;
      putimage(5+incre_x*middle_x,30+incre_y*middle_y,buffer[ano_player],XOR_PUT);
      if(player==0)
      {
	setcolor(LIGHTGRAY);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
	//setfillstyle(1,BLACK);
	//bar(585,215,639,225);
	score_a++;
	setcolor(WHITE);
	itoa(score_a,c,10);
	outtextxy(600,240,c);
      }
      else
      {
	setcolor(LIGHTGRAY);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
	//setfillstyle(1,BLACK);
	//bar(585,315,639,325);
	score_b++;
	setcolor(WHITE);
	itoa(score_b,c,10);
	outtextxy(600,340,c);
      }
      bara[start_x][start_y].status=0;
      bara[end_x][end_y].status=1;
      bara[start_x][start_y].player=0;
      bara[end_x][end_y].player=player+1;
      for(i=0;i<12;i++)
      {
	if((disc[ano_player][i].cur_x==middle_x+1)&&
		     (disc[ano_player][i].cur_y==middle_y+1))
	{
	  disc[ano_player][i].cur_x=0;
	  disc[ano_player][i].cur_y=0;
	  disc[ano_player][i].status=0;
	  break;
	}
      }
      turn_check=1;
      return 2;
      }
    }
  }
  pre_x=check_x;
  pre_y=check_y;
  return 0;
}
int check_diagonal(int start_x,int start_y)
{
  if(start_x==start_y)
  return 1;
  if((start_x==2&&start_y==0)||(start_x==0&&start_y==2))
  return 1;
  if((start_x==2&&start_y==4)||(start_x==4&&start_y==2))
  return 1;
  if((start_x==0&&start_y==4)||(start_x==4&&start_y==0))
  return 1;
  if((start_x==1&&start_y==3)||(start_x==3&&start_y==1))
  return 1;
  return 0;
}
void input_screen(void)
{
  int i,j;
  int sx,sy;
  int check_ex;
  int check_m;
  start2 :
//  hidemouseptr();
  x=120;
  y=120;
  setcolor(LIGHTGRAY);
  setfillstyle(1,LIGHTGRAY);
  bar(100,100,540,380);
  setcolor(RED);
  rectangle(110,110,530,370);
  settextstyle(0,0,1);
  settextjustify(1,1);
  outtextxy(midx,105,"INPUT SCREEN");
  for(i=1;i<3;i++)
  {
    settextstyle(0,0,1);
    setcolor(RED);
    rectangle(x,y,x+400,y+100);
    setcolor(LIGHTGRAY);
    line(x+25,y,x+85,y);
    setcolor(RED);
    if(i==1)
    outtextxy(x+55,y,"PLAYER-A");
    else
    outtextxy(x+55,y,"PLAYER-B");
    setcolor(BLACK);
    outtextxy(x+65,y+20,"ENTER NAME");
    setcolor(WHITE);
    setfillstyle(1,BLUE);
    bar(x+25,y+30,x+155,y+45);
    setcolor(RED);
    rectangle(x+160,y+10,x+280,y+90);
    setcolor(LIGHTGRAY);
    line(x+170,y+10,x+225,y+10);
    setcolor(BLACK);
    settextstyle(2,0,4);
    outtextxy(x+200,y+8,"Disc color");
    setcolor(RED);
    rectangle(x+310,y+10,x+380,y+90);
    setcolor(LIGHTGRAY);
    line(x+320,y+10,x+360,y+10);
    setcolor(BLACK);
    settextstyle(2,0,4);
    outtextxy(x+340,y+8,"Preview");
    if(i==1)
    Disc(i,1,465,170);
    else
    Disc(i,4,465,280);
    color_a=1;
    color_b=4;
    setfillstyle(1,DARKGRAY);
    bar(x+180,y+20,x+260,y+80);
    sx=x+185;
    sy=y+26;
    for(j=0;j<=5;j++)
    {
      setfillstyle(1,j+1);
      bar(sx,sy,sx+20,sy+20);
      setcolor(BLACK);
      rectangle(sx,sy,sx+20,sy+20);
      //rectangle(sx+1,sy+1,sx+19,sy+19);
      setcolor(WHITE);
      line(sx+21,sy,sx+21,sy+21);
      line(sx,sy+21,sx+21,sy+21);
      sx+=25;
      if(j==2)
      {
	sy+=25;
	sx=x+185;
      }
    }
    x=120;
    y=230;
  }
  setfillstyle(1,CYAN);
  bar(470,345,520,360);
  setcolor(BLACK);
  rectangle(470,345,520,360);
  outtextxy(495,352,"PLAY");
  setfillstyle(1,CYAN);
  bar(120,345,170,360);
  setcolor(BLACK);
  rectangle(120,345,170,360);
  outtextxy(145,352,"EXIT");
  showmouseptr();
  restrictmouseptr(100,100,540,380);
  draw_dotted_box(305,146,0);
  prev_x_a=305;
  prev_y_a=146;
  draw_dotted_box(305,281,0);
  prev_x_b=305;
  prev_y_b=281;
    // BLACK
  a[0]='\0';
  b[0]='\0';
  check_m=input_name(1);
  if(check_m==1)
  goto start;
  do
  {
    getmousepos(&button,&mpos_x,&mpos_y);
    if(button&1==1)
    {
      start:
     // if(mpos_x>=290&&mpos_x<=304)
     // break;
      if((mpos_x>=305)&&(mpos_x<=375)
	&&(mpos_y>=146)&&(mpos_y<=200))
      check_mousepos(1,mpos_x,mpos_y);
      if((mpos_x>=305)&&(mpos_x<=375)
	 &&(mpos_y>=256)&&(mpos_y<=310))
      check_mousepos(2,mpos_x,mpos_y);
      if((mpos_x>=145)&&(mpos_x<=275)
	 &&(mpos_y>=150)&&(mpos_y<=165))
      {
	a[0]='\0';
	check_m=input_name(1);
	if(check_m==1);
	  goto start;
       //	continue;
      }
      if((mpos_x>=145)&&(mpos_x<=275)
	 &&(mpos_y>=260)&&(mpos_y<=275))
      {
	b[0]='\0';
	check_m=input_name(2);
	if(check_m==1);
	  goto start;
       //	continue;
      }
      if((mpos_x>=470)&&(mpos_x<=520)
	 &&(mpos_y>=345)&&(mpos_y<=360))
      {
	setcolor(BLACK);
	rectangle(471,346,519,359);
	while(button&1==1)
	 getmousepos(&button,&mpos_x,&mpos_y);
	break;
      }
//      rectangle(120,345,170,360);
      if((mpos_x>=120)&&(mpos_x<=170)
	 &&(mpos_y>=345)&&(mpos_y<=360))
      {
	setcolor(BLACK);
	rectangle(121,346,169,359);
	while(button&1==1)
	 getmousepos(&button,&mpos_x,&mpos_y);
	hidemouseptr();
	cleardevice();
	putimage(midx-100,midy-50,buff_exit,XOR_PUT);
//	showmouseptr();
	check_ex=check_exit();
	if(check_ex==1)
	goto start2;
      }
    }
  }while(1);
  return;
}
int input_name(int player)
{
  int sx,sy,ex;
  int count=0;
  start1:
  count=0;
  sx=145;
  ex=sx+130;
  if(player==1)
  sy=150;
  else
  sy=260;
  setfillstyle(1,BLUE);
  bar(sx,sy,sx+130,sy+15);
  settextstyle(0,0,1);
  sx+=4;
  sy+=12;
  do
  {
    do
    {
      setcolor(WHITE);
      line(sx,sy,sx+6,sy);
      line(sx,sy+1,sx+6,sy+1);
      getmousepos(&button,&mpos_x,&mpos_y);
      if(button&1==1)
      {
	if(player==1)
	a[count]='\0';
	else
	b[count]='\0';
	setcolor(BLUE);
	line(sx,sy,sx+6,sy);
	line(sx,sy+1,sx+6,sy+1);
	return 1;
      }
      if(kbhit())
      {
	c[0]=getch();
	break;
      }
      delay(220);
      setcolor(BLUE);
      line(sx,sy,sx+6,sy);
      line(sx,sy+1,sx+6,sy+1);
      getmousepos(&button,&mpos_x,&mpos_y);
      if(button&1==1)
      {
	if(player==1)
	a[count]='\0';
	else
	b[count]='\0';
	setcolor(BLUE);
	line(sx,sy,sx+6,sy);
	line(sx,sy+1,sx+6,sy+1);
	return 1;
      }
       if(kbhit())
      {
	c[0]=getch();
	break;
      }
      delay(220);
    }while(1);
   // if(c[0]==)
    c[1]='\0';
    setcolor(BLUE);
    line(sx,sy,sx+6,sy);
    line(sx,sy+1,sx+6,sy+1);
    if(c[0]==8)
    {
      if(count>0)
      {
	setfillstyle(1,BLUE);
	bar(sx-12,sy-12,ex,sy+3);
	sx-=8;
	count--;
      }
      continue;
    }
    setcolor(WHITE);
    outtextxy(sx,sy-4,c);
    if(c[0]==13)
    break;
    sx+=8;
    if(c[0]==27)
    {
      closegraph();
      exit(1);
    }
    if(player==1)
    a[count++]=c[0];
    else
    b[count++]=c[0];
    if(count==15)
    break;
  }while(1);
  setcolor(BLUE);
  line(sx,sy,sx+6,sy);
  line(sx,sy+1,sx+6,sy+1);
  if(player==1)
  a[count]='\0';
  else
  b[count]='\0';
  if(c[0]==13||count==15)
  {
    setcolor(BLUE);
    bar(sx-4,sy-12,ex,sy+3);
    if((player==1)&&b[0]=='\0')
    {
     // puts("1");
      player=2;
      goto start1;
    }
    else
    if((player==2)&&a[0]=='\0')
    {
     // puts("2");
      player=1;
      goto start1;
    }
    else
    return 0;
  }
  return 0;
}
check_mousepos(int player,int mpos_x,int mpos_y)
{
  int j;
  int sx,sy;
  sx=305;
  if(player==1)
  sy=146;
  else
  sy=256;
//  puts("c");
  for(j=0;j<=5;j++)
  {
    if((mpos_x>=sx)&&(mpos_x<=sx+21)
       &&(mpos_y>=sy)&&(mpos_y<=sy+21))
    {
     // puts("d");
      if((player==1)&&(color_b!=j+1))
      {
	draw_dotted_box(prev_x_a,prev_y_a,8);
	draw_dotted_box(sx,sy,0);
	prev_x_a=sx;
	prev_y_a=sy;
	farfree(buffer[0]);
	Disc(1,j+1,465,170);
	color_a=j+1;
      }
      if((player==2)&&(color_a!=j+1))
      {
	draw_dotted_box(prev_x_b,prev_y_b,8);
	draw_dotted_box(sx,sy,0);
	prev_x_b=sx;
	prev_y_b=sy;
	farfree(buffer[0]);
	Disc(2,j+1,465,280);
	color_b=j+1;
      }
   //    printf("%d %d %d %d\n",sx,sy,mpos_x,mpos_y);
   //    getch();
      break;
    }
    sx+=25;
    if(j==2)
    {
       sy+=25;
       sx=305;
    }
  }
  return;
}
draw_dotted_box(int sx,int sy,int color)
{
  int int_x,int_y;
  int i;
  hidemouseptr();
  setcolor(color);
  settextstyle(2,0,4);
  int_x=sx-1;
  int_y=sy-2;
  for(i=0;i<6;i++)
  {
  line(int_x,int_y,int_x+2,int_y);
  int_x+=4;
  }
  int_x=sx-1;
  int_y=sy+22;
  for(i=0;i<6;i++)
  {
  line(int_x,int_y,int_x+2,int_y);
  int_x+=4;
  }
  int_x=sx-2;
  int_y=sy-2;
  for(i=0;i<6;i++)
  {
  line(int_x,int_y,int_x,int_y+2);
  int_y+=4;
  }
  int_x=sx+22;
  int_y=sy-2;
  for(i=0;i<6;i++)
  {
  line(int_x,int_y,int_x,int_y+2);
  int_y+=4;
  }
//  rectangle(sx-2,sy-2,sx+23,sy+23);
  showmouseptr();
  return;
}
void exit_screen(void)
{
 int i;
  setfillstyle(1,LIGHTGRAY);
  bar(midx-100,midy-50,midx+100,midy+50);
  setcolor(BLACK);
  rectangle(midx-95,midy-45,midx+95,midy+45);
  rectangle(midx-90,midy-40,midx+90,midy+40);
  settextstyle(2,0,5);
  settextjustify(1,1);
  outtextxy(midx,midy-30,"Do you want to exit.");
  setfillstyle(1,BROWN);
  bar(midx-70,midy+10,midx-30,midy+30);
  rectangle(midx-70,midy+10,midx-30,midy+30);
  outtextxy(midx-50,midy+20,"Yes");
  bar(midx+70,midy+10,midx+30,midy+30);
  rectangle(midx+70,midy+10,midx+30,midy+30);
  outtextxy(midx+50,midy+20,"No");
  size=imagesize(midx-100,midy-50,midx+100,midy+50);
  if((buff_exit=(char far *)malloc(size))==NULL)
  {
    printf("Not enough memory");
    getch();
    exit(1);
  }
  getimage(midx-100,midy-50,midx+100,midy+50,buff_exit);
  //check_exit();
  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
}
int check_exit(void)
{
  restrictmouseptr(midx-100,midy-50,midx+100,midy+50);
  showmouseptr();
  do
  {
    getmousepos(&button,&mpos_x,&mpos_y);
    if(button&1==1)
    {
      if((mpos_x>=midx-70)&&(mpos_y>=midy+10)
	 &&(mpos_x<=midx-30)&&(mpos_y<=midy+30))
      {
	setcolor(BLACK);
	rectangle(midx-69,midy+11,midx-31,midy+29);
	while(button&1==1)
	 getmousepos(&button,&mpos_x,&mpos_y);
	restrictmouseptr(0,0,maxx-1,maxy-1);
	closegraph();
	exit(1);
      }
      if((mpos_x<=midx+70)&&(mpos_y>=midy+10)
	 &&(mpos_x>=midx+30)&&(mpos_y<=midy+30))
      {
	setcolor(BLACK);
	rectangle(midx+69,midy+11,midx+31,midy+29);
	while(button&1==1)
	 getmousepos(&button,&mpos_x,&mpos_y);
	hidemouseptr();
	putimage(midx-100,midy-50,buff_exit,XOR_PUT);
	showmouseptr();
	restrictmouseptr(0,0,maxx-1,maxy-1);
	hidemouseptr();

	return 1;
      }
    }
  }while(1);
}
void pre_check_exit(void)
{
  char far *buff_back;
  size=imagesize(midx-100,midy-50,midx+100,midy+50);
  if((buff_back=(char far *)malloc(size))==NULL)
  {
    printf("Not enough memory");
    getch();
    exit(1);
  }
  getimage(midx-100,midy-50,midx+100,midy+50,buff_back);
  hidemouseptr();
  putimage(midx-100,midy-50,buff_back,XOR_PUT);
  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
  showmouseptr();
  check_exit();
  hidemouseptr();
  putimage(midx-100,midy-50,buff_exit,XOR_PUT);
  putimage(midx-100,midy-50,buff_back,COPY_PUT);
  showmouseptr();
  farfree(buff_back);
}
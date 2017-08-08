#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int maxx,maxy,midx,midy;
int  prev_x,prev_y;
int check_prev,check_return=1;
int ran_x,ran_y,ranp_x,ranp_y;
int t_x,t_y;
int check_back;
int k=0;
int score=0;
int count=0;
unsigned long size;
char far *buffer_bar;
static int mat_bar[55][39];
struct pos
{
  int cur_x;
  int cur_y;
  struct pos *next;
};
struct pos *top,*element;
struct pos *item=NULL;
struct pos *create(struct pos *node);
struct pos *update(struct pos *node);
void move(void);
void snake_bar(void);
void structure(void);
void random_bar(void);
int insert_bar(void);
int check_key(char check);
void check_end(void);
main()
{
  int gd=DETECT,gm,errorcode;
  int i,x,y;
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  errorcode=graphresult();
  if(errorcode!=grOk)
  {
    printf("Graphics mode is not initialised...");
    getch();
    exit(1);
  }
  maxx=getmaxx();
  maxy=getmaxy();
  midx=maxx/2;
  midy=maxy/2;
  snake_bar();
  structure();
  item=create(item);
  move();
  getch();
  return 0;
}
void snake_bar(void)
{
  setcolor(WHITE);
  setfillstyle(1,RED);
  bar(1,1,10,10);
  rectangle(1,1,10,10);
  size=imagesize(1,1,10,10);
  if((buffer_bar=(char far *)malloc(size))==NULL)
  {
    printf("Not enough memory");
    getch();
    exit(1);
  }
  getimage(1,1,10,10,buffer_bar);
  putimage(1,1,buffer_bar,XOR_PUT);
}
void structure(void)
{
  char c[2];
  //cleardevice();
  setcolor(WHITE);
  rectangle(49,49,590,430);
  settextstyle(1,0,5);
  settextjustify(1,1);
  outtextxy(midx,25,"SNAKE GAME");
  settextstyle(0,0,1);
  outtextxy(midx+210,45,"Score : ");
  c[0]='0';
  c[1]='\0';
  outtextxy(midx+245,45,c);
  setfillstyle(1,CYAN);
  bar(0,maxy-15,maxx-1,maxy-1);
  outtextxy(midx,maxy-8,"Use   Arrow Keys : To change direction   Esc : To Exit ");
}
struct pos *create(struct pos *item)
{
  int i,x,y;
  x=22;y=18;
  item=(struct pos*)malloc(sizeof(struct pos));
  for(i=1;i<=5;i++)
  {
    mat_bar[x][y]=1;
    item->cur_x=x;
    item->cur_y=y;
    putimage(50+x*10,50+y*10,buffer_bar,XOR_PUT);
    item->next=top;
    top=item;
    item=(struct pos*)malloc(sizeof(struct pos));
    x++;
  }
  return(item);
}
void move(void)
{
  int temp_x,temp_y;
  int score_pre;
  char c,st_score[5];
  //ranp_x=ranp_y=-1;
  check_back=1;
  //element=top;
  prev_x=top->cur_x;
  prev_y=top->cur_y;
  top->cur_x++;
  getch();
  random_bar();
  do
  {
    //insert_bar();
    element=top;
    while(1)
    {
      putimage(50+element->cur_x*10,50+element->cur_y*10,buffer_bar,XOR_PUT);
      //delay(200);
      putimage(50+prev_x*10,50+prev_y*10,buffer_bar,XOR_PUT);
      if(kbhit())
      {
	c=getch();
	if(c=='c')
	{
	  closegraph();
	  exit(1);
	}
      }
      element=element->next;
      if(element==NULL)
      break;
      temp_x=prev_x;
      temp_y=prev_y;
      prev_x=element->cur_x;
      prev_y=element->cur_y;
      element->cur_x=temp_x;
      element->cur_y=temp_y;
    }
    start:
    mat_bar[prev_x][prev_y]=0;
    //check_end();
    mat_bar[top->cur_x][top->cur_y]=1;
    count++;
    if((k==1)&&(score_pre+5==count))
    {
      putimage(50+t_x*10,50+t_y*10,buffer_bar,XOR_PUT);
      //getch();
      k=0;
    }
    if(insert_bar()==1)
    {
      setcolor(BLACK);
      itoa(score,st_score,10);
      outtextxy(midx+245,45,st_score);
      score+=10;
      setcolor(WHITE);
      itoa(score,st_score,10);
      outtextxy(midx+245,45,st_score);
      random_bar();
    }
    delay(500);
    //getch();
    if(kbhit())
    {
      c=getch();
      if(c==0)
      c=getch();
      if(c==27)
      {
	closegraph();
	exit(1);
      }
      if(c=='p')
      {
	printf(" %d %d",top->cur_x,top->cur_y);
	getch();
      }
      check_prev=check_back;
      check_back=check_key(c);
      if(insert_bard()==1)
      {
	setcolor(BLACK);
	itoa(score,st_score,10);
	outtextxy(midx+245,45,st_score);
	score+=10;
	setcolor(WHITE);
	itoa(score,st_score,10);
	outtextxy(midx+245,45,st_score);
	random_bar();
	check_return=1;
	count=0;
	score_pre=score/10;
	goto start;
      }
    }
//    if(check_prev!=check_back)
    if(check_return==1)
    {
      prev_x=top->cur_x;
      prev_y=top->cur_y;
      if(check_back==1)
      top->cur_x++;
      else if(check_back==2)
      top->cur_x--;
      else if(check_back==3)
      top->cur_y--;
      else if(check_back==4)
      top->cur_y++;
    }
    check_return=1;
  }while(1);
}
int check_key(char check)
{
  if(check==77)
  {
    if(check_prev==2)
    return check_prev;
    else
    {
      check_return=0;
      prev_x=top->cur_x;
      prev_y=top->cur_y;
      check_back=1;
      //if(mat_bar[top->cur_x][top->cur_y]==2)
      //insert_bar();
      top->cur_x++;
      return 1;
    }
  }
  if(check==75)
  {
    if(check_prev==1)
    return check_prev;
    else
    {
      check_return=0;
      prev_x=top->cur_x;
      prev_y=top->cur_y;
      top->cur_x--;
      return 2;
    }
  }
  if(check==72)
  {
    if(check_prev==4)
    return check_prev;
    else
    {
      check_return=0;
      prev_x=top->cur_x;
      prev_y=top->cur_y;
      top->cur_y--;
      return 3;
    }
  }
  if(check==80)
  {
    if(check_prev==3)
    return check_prev;
    else
    {
      check_return=0;
      prev_x=top->cur_x;
      prev_y=top->cur_y;
      top->cur_y++;
      return 4;
    }
  }
  return check_prev;
}
void random_bar(void)
{

  if(k==0)
  {
    ran_x=27;
    ran_y=19;
    //mat_bar[ran_x++][ran_y++]=1;
    putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    k++;
  }
  else
  do
  {
    ran_x=random(53);
    ran_y=random(37);
    if(mat_bar[ran_x++][ran_y++]==1)
    continue;
    mat_bar[ran_x][ran_y]=2;
    putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    //printf("%d %d\n",ran_x,ran_y);
    break;
  }while(1);
}
int insert_bar(void)
{
  if(check_back==1)
  {
    if((top->cur_x+1==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
  }
  else if(check_back==2)
  {
    if((top->cur_x-1==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
  }
  else if(check_back==3)
  {
    if((top->cur_x==ran_x)&&(top->cur_y-1==ran_y))
    ;
    else return 0;
  }
  else if(check_back==4)
  {
    if((top->cur_x==ran_x)&&(top->cur_y+1==ran_y))
    ;
    else return 0;
  }
  mat_bar[ran_x][ran_y]=1;
  item->cur_x=ran_x;
  item->cur_y=ran_y;
  //putimage(50+x*10,50+y*10,buffer_bar,XOR_PUT);
  item->next=top;
  top=item;
  item=(struct pos*)malloc(sizeof(struct pos));
  return 1;
}
void check_end(void)
{
  if(mat_bar[top->cur_x][top->cur_y]==1)
  {
    getch();
    closegraph();
    exit(1);
  }
  if((top->cur_x==-1)||(top->cur_y==-1))
  {
    //getch();
    closegraph();
    exit(1);
  }
  if((top->cur_x==54)||(top->cur_y==38))
  {
    //getch();
    closegraph();
    exit(1);
  }
}
int insert_bard(void)
{
  if(check_back==1)
  {
    if((top->cur_x==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
    //putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    t_x=top->cur_x-1;
    t_y=top->cur_y;
    ran_x++;
  }
  else if(check_back==2)
  {
    if((top->cur_x==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
   // putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    t_x=top->cur_x+1;
    t_y=top->cur_y;
    ran_x--;
  }
  else if(check_back==3)
  {
    if((top->cur_x==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
   // putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    t_x=top->cur_x;
    t_y=top->cur_y+1;
    ran_y--;
  }
  else if(check_back==4)
  {
    if((top->cur_x==ran_x)&&(top->cur_y==ran_y))
    ;
    else return 0;
   // putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
    t_x=top->cur_x;
    t_y=top->cur_y-1;
    ran_y++;
  }
  mat_bar[ran_x][ran_y]=1;
  item->cur_x=ran_x;
  item->cur_y=ran_y;
  putimage(50+ran_x*10,50+ran_y*10,buffer_bar,XOR_PUT);
  item->next=top;
  top=item;
  item=(struct pos*)malloc(sizeof(struct pos));
  //getch();
  k=1;
  return 1;
}

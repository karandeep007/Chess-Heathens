#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<graphics.h>
struct LOC
{
	int v; //vertical
	char h; //horizontal
};
struct ELE
{
	int pos[3][4];
	struct LOC co; //coordinates
}ele1[2][2];
struct HOR
{
	int pos[3][4];
	struct LOC co; //coordinates
}hors1[2][2];
struct BISH
{
	int pos[3][4];
	struct LOC co; //coordinates
}bish1[2][2];
struct QUE
{
	int pos[3][6];
	struct LOC co; //coordinates
}que1[2];
struct KIN
{
	int pos[3][3];
	struct LOC co; //coordinates
}kin1[2];
struct PAW
{
	int pos[3][1];
	struct LOC co; //coordinates
}paw1[2][8];
int TRANS_M[3][3];

void init();
void super_plot();
void draw_board();
void draw_elephant();
void draw_horse();
void draw_bishop();
void draw_queen();
void draw_king();
void draw_pawn();
void plot_elephant(struct ELE elex[2][2],int num,int play);
void plot_horse(struct HOR horsx[2][2],int num,int play);
void plot_bishop(struct BISH bishx[2][2],int num,int play);
void plot_queen(struct QUE quex[2],int play);
void plot_king(struct KIN kinx[2],int play);
void plot_pawn(struct PAW pawx[2][8],int num,int play);
void identity(int a[100][100],int m,int n);
void multi(int original[100][100],int final[100][100],int m,int n,int o);
void translate(int x, int y,char peice,int num,int play);
void handler(char what[10],char where[10],int play);
void eliminate(char c_h, int c_v, int play);
void main()
{
	int gdriver=DETECT,gmode,errorcode;
	int ch,i,j;
	long count;
	char what[10],where[10];

	clrscr();
	initgraph(&gdriver, &gmode,"");
	errorcode=graphresult();
	if(errorcode!=grOk)
	{
		printf("Graphics Error %s \n",grapherrormsg(errorcode));
		printf("Press any key to half\n");
		getch();
		return;

	}
	printf("\nCHESS HEATHENS by Karandeep Singh\n\n");
	printf("X in Peice to exit\n\n");
	init(); //establish values for everything
	super_plot();
	count=0;
	while(1)
	{
		if(count%2==0)
		{
			printf("Player 1\nPeice: ");
			scanf("%s",what);
			if(what[0]=='X')
			{
				break;
			}
			printf("New Location: ");
			scanf("%s",where);
			handler(what,where,0);
		}
		else
		{
			printf("Player 2\nPeice: ");
			scanf("%s",what);
			if(what[0]=='X')
			{
				break;
			}
			printf("New Location: ");
			scanf("%s",where);
			handler(what,where,1);

		}
		cleardevice();
		super_plot();
		count++;


	}

	getch();
	closegraph();
}
void init()
{
	int i,j,pl,k;
	TRANS_M[0][0]=1,TRANS_M[1][1]=1,TRANS_M[2][2]=1;//make Trans matrix identity at start
	draw_elephant();
	for(pl=0,k=0;pl<2;pl++,k+=350)
	{
		for(i=0,j=0;i<2;i++,j+=350)
		{
			translate(200+j,50+k,'E',i,pl);
		}
	}
	draw_horse();
	for(pl=0,k=0;pl<2;pl++,k+=350)
	{
		for(i=0,j=0;i<2;i++,j+=250)
		{
			translate(215+j,20+k,'H',i,pl);
		}
	}
	draw_bishop();
	for(pl=0,k=0;pl<2;pl++,k+=350)
	{
		for(i=0,j=0;i<2;i++,j+=150)
		{
			translate(275+j,22+k,'B',i,pl);
		}
	}
	draw_queen();
	for(pl=0,k=0;pl<2;pl++,k+=350)
	{
		if(pl==0)
			translate(315,35+k,'Q',0,pl);
		else
			translate(365,35+k,'Q',0,pl);

	}
	draw_king();
	for(pl=0,k=0;pl<2;pl++,k+=350)
	{
		if(pl==0)
			translate(375,30+k,'K',0,pl);
		else
			translate(325,30+k,'K',0,pl);

	}
	draw_pawn();
	for(pl=0,k=0;pl<2;pl++,k+=250)
	{
		for(i=0,j=0;i<8;i++,j+=50)
		{

			translate(175+j,100+k,'P',i,pl);
		}
	}
}
void super_plot()
{
	int i,pl;
	draw_board();
	for(pl=0;pl<2;pl++)
	{
		for(i=0;i<2;i++)
		{
			plot_elephant(ele1,i,pl);
		}
	}
	for(pl=0;pl<2;pl++)
	{
		for(i=0;i<2;i++)
		{
			plot_horse(hors1,i,pl);
		}
	}
	for(pl=0;pl<2;pl++)
	{
		for(i=0;i<2;i++)
		{
			plot_bishop(bish1,i,pl);
		}
	}
	for(pl=0;pl<2;pl++)
	{
		plot_queen(que1,pl);
	}
	for(pl=0;pl<2;pl++)
	{
		plot_king(kin1,pl);
	}
	for(pl=0;pl<2;pl++)
	{
		for(i=0;i<8;i++)
		{
			plot_pawn(paw1,i,pl);
		}
	}
}
void draw_board()
{
	int i,j,x_odd,y_odd,mx,my;
	char name[3]="A",number[3]="0";
	name[0]--;
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	for(i=0,mx=0;i<8;i++,mx+=50)
	{
		name[0]++;
		outtextxy(220+mx,40,name);
	}
	for(i=0,my=0;i<8;i++,my+=50)
	{
		number[0]++;
		outtextxy(190,70+my,number);
	}
	//printf("Enter x0 y0: ");
	//scanf("%d %d",&x0,&y0);
	x_odd=250;
	y_odd=50;
	for(i=0,my=0;i<4;i++,my+=100)
	{
		for(j=0,mx=0;j<4;j++,mx+=100)
		{
			bar(x_odd+mx,y_odd+my,x_odd+50+mx,y_odd+50+my);
		}
	}

	x_odd=200;
	y_odd=100;
	for(i=0,my=0;i<4;i++,my+=100)
	{
		for(j=0,mx=0;j<4;j++,mx+=100)
		{
			bar(x_odd+mx,y_odd+my,x_odd+50+mx,y_odd+50+my);
		}
	}


}
void draw_elephant()
{
	int i,j,k,ver;
	char hor;
	for(k=0,ver=1;k<2;k++,ver+=7)
	{
		hor='a';
		for(j=0;j<2;j++,hor+=7)
		{
			ele1[k][j].pos[0][0]=10;
			ele1[k][j].pos[1][0]=10;
			ele1[k][j].pos[0][1]=40;
			ele1[k][j].pos[1][1]=10;
			ele1[k][j].pos[0][2]=40;
			ele1[k][j].pos[1][2]=40;
			ele1[k][j].pos[0][3]=10;
			ele1[k][j].pos[1][3]=40;
			for(i=0;i<4;i++)
				ele1[k][j].pos[2][i]=1;
			ele1[k][j].co.v=ver;
			ele1[k][j].co.h=hor;


		}
	}

}
void plot_elephant(struct ELE elex[2][2],int num,int play)
{

	int i,x1,y1,x2,y2,pl,ch;
	char n[3];
	if(play==0)
	{
		ch=4;
	}
	else
		ch=8;
	setcolor(ch);

		for(i=0;i<4;i++)
		{
			x1=elex[play][num].pos[0][i];
			y1=elex[play][num].pos[1][i];
			if(i+1>3)
			{
				x2=elex[play][num].pos[0][0];
				y2=elex[play][num].pos[1][0];
			}
			else
			{
				x2=elex[play][num].pos[0][i+1];
				y2=elex[play][num].pos[1][i+1];
			}
			line(x1,y1,x2,y2);

		}

		setfillstyle(SOLID_FILL,ch);
		floodfill(elex[play][num].pos[0][0]+10,elex[play][num].pos[1][0]+10,ch);
		n[0]=num+48; //48 is ASCII for '0'
		n[1]='\0';
		setcolor(15);
		outtextxy(elex[play][num].pos[0][0]+12,elex[play][num].pos[1][0]+12,n);


}
void draw_horse()
{
	int i,j,p,ver;
	char hor;
	for(p=0,ver=1;p<2;p++,ver+=7)
	{
		hor='b';
		for(j=0;j<2;j++,hor+=5)
		{
			hors1[p][j].pos[0][0]=50;  //left pie
			hors1[p][j].pos[1][0]=43;
			hors1[p][j].pos[0][1]=50;   //bar //left
			hors1[p][j].pos[1][1]=35;    	    //top
			hors1[p][j].pos[0][2]=65;         //right
			hors1[p][j].pos[1][2]=70;        //bottom
			hors1[p][j].pos[0][3]=65; //right pie
			hors1[p][j].pos[1][3]=62;

			for(i=0;i<4;i++)
				hors1[p][j].pos[2][i]=1;
			hors1[p][j].co.v=ver;
			hors1[p][j].co.h=hor;
		}
	}

}
void plot_horse(struct HOR horsx[2][2],int num,int play)
{

	int ch;
	char n[3];

	if(play==0)
	{
		ch=4;
	}
	else
		ch=8;

	setcolor(ch);
	setfillstyle(SOLID_FILL,ch);
	pieslice(horsx[play][num].pos[0][0],horsx[play][num].pos[1][0],90,270,8);
	bar(horsx[play][num].pos[0][1],horsx[play][num].pos[1][1],horsx[play][num].pos[0][2],horsx[play][num].pos[1][2]);
	pieslice(horsx[play][num].pos[0][3],horsx[play][num].pos[1][3],270,360,8);
	pieslice(horsx[play][num].pos[0][3],horsx[play][num].pos[1][3],0,90,8);
	n[0]=num+48; //48 is ASCII for '0'
	n[1]='\0';
	setcolor(15);
	outtextxy(horsx[play][num].pos[0][1]+6,horsx[play][num].pos[1][0]+10,n);

}
void draw_bishop()
{
	int i,j,p,ver;
	char hor;
	for(p=0,ver=1;p<2;p++,ver+=7)
	{
		hor='c';
		for(j=0;j<2;j++,hor+=3)
		{
			bish1[p][j].pos[0][0]=50;
			bish1[p][j].pos[1][0]=37; //small circle
			bish1[p][j].pos[0][1]=50;
			bish1[p][j].pos[1][1]=60; //big circle
			bish1[p][j].pos[0][2]=45;
			bish1[p][j].pos[1][2]=45; //mid common, calculate radius
			bish1[p][j].pos[0][2]=50;
			bish1[p][j].pos[1][2]=45;
			for(i=0;i<4;i++)
				bish1[p][j].pos[2][i]=1;
			bish1[p][j].co.v=ver;
			bish1[p][j].co.h=hor;
		}
	}

}
void plot_bishop(struct BISH bishx[2][2],int num,int play)
{
	int x_fill,y_fill,ch;
	char n[3];
	if(play==0)
	{
		ch=4;
	}
	else
		ch=8;

	setcolor(ch);
	setfillstyle(SOLID_FILL,ch);

	x_fill=bishx[play][num].pos[0][0];
	y_fill=bishx[play][num].pos[1][0];
	circle(bishx[play][num].pos[0][0],bishx[play][num].pos[1][0],abs(bishx[play][num].pos[1][2]-bishx[play][num].pos[1][0]));
	floodfill(x_fill,y_fill,ch);

	x_fill=bishx[play][num].pos[0][1];
	y_fill=bishx[play][num].pos[1][1];
	circle(bishx[play][num].pos[0][1],bishx[play][num].pos[1][1],abs(bishx[play][num].pos[1][2]-bishx[play][num].pos[1][1]));
	floodfill(x_fill,y_fill,ch);
	n[0]=num+48; //48 is ASCII for '0'
	n[1]='\0';
	setcolor(15);
	outtextxy(bishx[play][num].pos[0][1]-3,bishx[play][num].pos[1][1]-10,n);


}
void draw_queen()
{
	int i,k,ver;
	char hor;
	for(k=0,ver=1;k<2;k++,ver+=7)
	{
		if(k==0)
			hor='d';
		else
			hor='e';
		que1[k].pos[0][0]=50;//downwards triangle
		que1[k].pos[1][0]=33;
		que1[k].pos[0][1]=60;
		que1[k].pos[1][1]=58;
		que1[k].pos[0][2]=70;
		que1[k].pos[1][2]=33;
		que1[k].pos[0][3]=50;//uppward triangle
		que1[k].pos[1][3]=47;
		que1[k].pos[0][4]=60;
		que1[k].pos[1][4]=22;
		que1[k].pos[0][5]=70;
		que1[k].pos[1][5]=47;
		for(i=0;i<6;i++)
			que1[k].pos[2][i]=1;
		que1[k].co.v=ver;
		que1[k].co.h=hor;
	}


}
void plot_queen(struct QUE quex[2],int play)
{
	int x_fill,y_fill,i,ch;

	if(play==0)
	{
		ch=4;
	}
	else
		ch=8;
	setcolor(ch);
	setfillstyle(SOLID_FILL,ch);

	for(i=0;i<6;i++)
	{
		if(i==2 || i==5)
		{
			line(quex[play].pos[0][i],quex[play].pos[1][i],quex[play].pos[0][i-2],quex[play].pos[1][i-2]);
		}
		else
		{
			line(quex[play].pos[0][i],quex[play].pos[1][i],quex[play].pos[0][i+1],quex[play].pos[1][i+1]);
		}
	}
	for(i=0;i<6;i++)
	{
		if(i==0)
		{
			x_fill=quex[play].pos[0][i]+2;
			y_fill=quex[play].pos[1][i]+2;
		}
		else if(i==3)
		{
			x_fill=quex[play].pos[0][i]+2;
			y_fill=quex[play].pos[1][i]-2;
		}
		else if(i==1 || i==4)
		{
			x_fill=quex[play].pos[0][i];
			if(i==1)
				y_fill=quex[play].pos[1][i]-2;
			else
			{
				y_fill=quex[play].pos[1][i]+2;
				floodfill(x_fill,y_fill+10,ch);

			}
		}
		else if(i==2)
		{
			x_fill=quex[play].pos[0][i]-2;
			y_fill=quex[play].pos[1][i]+2;
		}
		else if(i==5)
		{
			x_fill=quex[play].pos[0][i]-2;
			y_fill=quex[play].pos[1][i]-2;
		}

		floodfill(x_fill,y_fill,ch);
	}
}
void draw_king()
{

	int i,p,ver;
	char hor;
	for(p=0,ver=1;p<2;p++,ver+=7)
	{
		if(p==0)
			hor='e';
		else
			hor='d';
		kin1[p].pos[0][0]=35;
		kin1[p].pos[1][0]=45;
		kin1[p].pos[0][1]=65;
		kin1[p].pos[1][1]=45;
		kin1[p].pos[0][2]=50;
		kin1[p].pos[1][2]=30;
		for(i=0;i<3;i++)
			kin1[p].pos[2][i]=1;
		kin1[p].co.v=ver;
		kin1[p].co.h=hor;

	}
}
void plot_king(struct KIN kinx[2],int play)
{
	int i,ch;

	if(play==0)
		ch=4;
	else
		ch=8;
	setcolor(ch);
	setfillstyle(SOLID_FILL,ch);

	for(i=0;i<3;i++)
	{
		if(i==2)
		{
			line(kinx[play].pos[0][i],kinx[play].pos[1][i],kinx[play].pos[0][i-2],kinx[play].pos[1][i-2]);
		}
		else
		{
			line(kinx[play].pos[0][i],kinx[play].pos[1][i],kinx[play].pos[0][i+1],kinx[play].pos[1][i+1]);
		}
	}
	floodfill(kinx[play].pos[0][2],kinx[play].pos[1][2]+5,ch);
	bar(kinx[play].pos[0][0],kinx[play].pos[1][0],kinx[play].pos[0][1],kinx[play].pos[1][1]+15);
}
void draw_pawn()
{
	int i,j,ver;
	char hor;

	for(j=0,ver=2;j<2;j++,ver+=5)
	{
		hor='a';
		for(i=0;i<8;i++,hor++)
		{
			paw1[j][i].pos[0][0]=50;
			paw1[j][i].pos[1][0]=30;
			paw1[j][i].pos[2][0]=1;
			paw1[j][i].co.v=ver;
			paw1[j][i].co.h=hor;
		}
	}


}
void plot_pawn(struct PAW pawx[2][8],int num,int play)
{
	int ch;
	char n[3];

	if(play==0)
	{
		ch=4;
	}
	else
	{
		ch=8;
	}
	setcolor(ch);
	setfillstyle(SOLID_FILL,ch);
	pieslice(pawx[play][num].pos[0][0],pawx[play][num].pos[1][0],0,180,15);
	n[0]=num+48; //48 is ASCII for '0'
	n[1]='\0';
	setcolor(15);
	outtextxy(pawx[play][num].pos[0][0]-2,pawx[play][num].pos[1][0]-10,n);

}
void identity(int a[100][100],int m, int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
			{
				a[i][j]=1;

			}
		}
	}


}
void multi(int original[100][100],int final[100][100],int m,int n,int o)
{
	int i,j,k,sum_r;
	//[m,n]X[n,o]
	for(i=0;i<m;i++)
	{
		for(j=0;j<o;j++)
		{
			sum_r=0;
			for(k=0;k<n;k++)
			{
				sum_r+=TRANS_M[i][k]*original[k][j];
			}
			final[i][j]=sum_r;
		}
	}

}
void translate(int x, int y,char peice,int num,int play)
{
	int p[100][100],result[100][100],j,i,m,n,o;
	TRANS_M[0][2]=x;
	TRANS_M[1][2]=y;
	if(peice=='E' || peice=='H' || peice=='B')
	{
		if(peice=='E')
		{
			struct ELE arbitary;
			arbitary=ele1[play][num]; //check here
			n=3,o=4;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			ele1[play][num]=arbitary; //check here

		}
		else if(peice=='H')
		{

		       struct HOR arbitary;

		       arbitary=hors1[play][num];
			n=3,o=4;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			hors1[play][num]=arbitary; //check here


		}
		else if(peice=='B')
		{
		       struct BISH arbitary;
		       arbitary=bish1[play][num];
			n=3,o=4;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			bish1[play][num]=arbitary; //check here

		}

	}
	else if(peice=='Q')
	{
		 struct QUE arbitary;
		       arbitary=que1[play];
			n=3,o=6;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			que1[play]=arbitary; //check here
	}
	else if(peice=='K')
	{
		 struct KIN arbitary;
		       arbitary=kin1[play];
			n=3,o=3;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			kin1[play]=arbitary; //check here
	}else if(peice=='P')
	{
		 struct PAW arbitary;
		       arbitary=paw1[play][num];
			n=3,o=1;
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					p[i][j]=arbitary.pos[i][j];
				}
			}

			multi(p,result,3,n,o);
			for(i=0;i<n;i++)
			{
				for(j=0;j<o;j++)
				{
					arbitary.pos[i][j]=result[i][j];
				}
			}
			paw1[play][num]=arbitary; //check here
	}




}
void handler(char what[10],char where[10],int play)
{
	int peice_no,loc_v,cur_v,x,y,i,j;
	char loc_h,peice_name,cur_h;

	peice_name=what[0];
	peice_name=toupper(peice_name);
	peice_no=what[1]-48; //48 is ASCII for '0'
	loc_v=where[1]-48;
	loc_h=where[0];
	loc_h=tolower(loc_h);

	if(what[0]=='E')
	{
		cur_v=ele1[play][peice_no].co.v;
		cur_h=ele1[play][peice_no].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		ele1[play][peice_no].co.v=loc_v;
		ele1[play][peice_no].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);

	}
	else if(what[0]=='H')
	{
		cur_v=hors1[play][peice_no].co.v;
		cur_h=hors1[play][peice_no].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		hors1[play][peice_no].co.v=loc_v;
		hors1[play][peice_no].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);
	}
	else if(what[0]=='B')
	{
		cur_v=bish1[play][peice_no].co.v;
		cur_h=bish1[play][peice_no].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		bish1[play][peice_no].co.v=loc_v;
		bish1[play][peice_no].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);
		getch();
	}
	else if(what[0]=='P')
	{

		cur_v=paw1[play][peice_no].co.v;
		cur_h=paw1[play][peice_no].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		paw1[play][peice_no].co.v=loc_v;
		paw1[play][peice_no].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);
	}
	else if(what[0]=='Q')
	{
		peice_no=0;
		cur_v=que1[play].co.v;
		cur_h=que1[play].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		que1[play].co.v=loc_v;
		que1[play].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);
	}
	else if(what[0]=='K')
	{
		peice_no=0;
		cur_v=kin1[play].co.v;
		cur_h=kin1[play].co.h;
		x=(loc_h-cur_h)*50;
		y=(loc_v-cur_v)*50;
		kin1[play].co.v=loc_v;
		kin1[play].co.h=loc_h;
		translate(x,y,peice_name,peice_no,play);
	}
	delay(500);
	eliminate(loc_h,loc_v,play);


}

void eliminate(char c_h, int c_v, int play)
{
	int loc_v,pl_nxt,i,j,flag;
	char loc_h,str[20];

	strcpy(str,"PEHBQK");
	if(play==0)
		pl_nxt=1;
	else
		pl_nxt=0;

	for(i=0;str[i]!='\0';i++)
	{
		flag=0;
		if(str[i]=='E')
		{
			flag=0;
			for(j=0;j<2;j++)
			{
				loc_v=ele1[pl_nxt][j].co.v;
				loc_h=ele1[pl_nxt][j].co.h;
				if(loc_v==c_v &&loc_h==c_h)
				{
					flag=1;
					translate(1000,1000,'E',j,pl_nxt);
					break;
				}
			}
		}

		else if(str[i]=='H')
		{
			flag=0;
				for(j=0;j<2;j++)
				{
					loc_v=hors1[pl_nxt][j].co.v;
					loc_h=hors1[pl_nxt][j].co.h;
					if(loc_v==c_v &&loc_h==c_h)
					{
						flag=1;
						translate(1000,1000,'H',j,pl_nxt);
						break;
					}
				}
		}
		else if(str[i]=='B')
		{
			flag=0;
				for(j=0;j<2;j++)
				{
					loc_v=bish1[pl_nxt][j].co.v;
					loc_h=bish1[pl_nxt][j].co.h;
					if(loc_v==c_v &&loc_h==c_h)
					{
						flag=1;
						translate(1000,1000,'B',j,pl_nxt);
						break;
					}
				}
		}

		else if(str[i]=='P')
		{
			flag=0;
				for(j=0;j<8;j++)
				{
					loc_v=paw1[pl_nxt][j].co.v;
					loc_h=paw1[pl_nxt][j].co.h;
					if(loc_v==c_v &&loc_h==c_h)
					{
						flag=1;
						translate(1000,1000,'P',j,pl_nxt);
						break;
					}
				}
		}

		else if(str[i]=='K')
		{
			flag=0;

			loc_v=kin1[pl_nxt].co.v;
			loc_h=kin1[pl_nxt].co.h;
				if(loc_v==c_v &&loc_h==c_h)
				{
					flag=1;
					translate(1000,1000,'K',0,pl_nxt);
					break;
				}

		}

		else if(str[i]=='Q')
		{
			flag=0;

			loc_v=que1[pl_nxt].co.v;
			loc_h=que1[pl_nxt].co.h;
				if(loc_v==c_v &&loc_h==c_h)
				{
					flag=1;
					translate(1000,1000,'Q',0,pl_nxt);
					break;
				}

		}

		if(flag==1)
		{
			printf("Peice Cut!!\n\n");
			delay(500);
			break;
		}

	}
}







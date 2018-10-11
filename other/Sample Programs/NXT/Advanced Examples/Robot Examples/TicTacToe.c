const int xx = 100;
const int yy = 64;
const int size = 20;
const int margem = 10;
const int m = 2;
const int shiftx = 16;
const int shifty = 0;

const int xpeca[] = {
	(xx-size)/2-size+5+shiftx,
	(xx-size)/2+5+shiftx,
	(xx-size)/2+size+5+shiftx,
};

const int ypeca[] = {
	yy-(margem/2)+2+shifty,
	yy-(margem/2)-size+2+shifty,
	yy-(margem/2)-size*2+2+shifty,
};

const int x0quad[] = {
	(xx-size)/2-size+shiftx,
	(xx-size)/2+shiftx,
	(xx-size)/2+size+shiftx,
};
const int x1quad[] = {
	(xx+size)/2-size+shiftx,
	(xx+size)/2+shiftx,
	(xx+size)/2+size+shiftx,
};

const int y0quad[] = {
	(yy-size)/2 + size+shifty,
	(yy-size)/2+shifty,
	(yy-size)/2 - size+shifty,
};

const int y1quad[] = {
	(yy+size)/2 + size+shifty,
	(yy+size)/2+shifty,
	(yy+size)/2 - size+shifty,
};

int pecas[] = {
	0,
	0,
	0,

	0,
	0,
	0,

	0,
	0,
	0,
};

int winner=0;
bool draw=false;

bool verifica(int jog)
{
	//Combinations to win
	// 0,1,2   ou  3,4,5  ou  6,7,8
	// 0,3,6   ou  1,4,7  ou  2,5,8
	// 0,4,8   ou  2,4,6
	bool win= ( pecas[0] == pecas[1] && pecas[1]==pecas[2] && pecas[0]!=0)  ||
	( pecas[0] == pecas[3] && pecas[3]==pecas[6] && pecas[0]!=0)  ||
	( pecas[0] == pecas[4] && pecas[4]==pecas[8] && pecas[0]!=0)  ||
	( pecas[3] == pecas[4] && pecas[4]==pecas[5] && pecas[3]!=0)  ||
	( pecas[6] == pecas[7] && pecas[7]==pecas[8] && pecas[6]!=0)  ||
	( pecas[1] == pecas[4] && pecas[4]==pecas[7] && pecas[1]!=0)  ||
	( pecas[2] == pecas[5] && pecas[5]==pecas[8] && pecas[2]!=0)  ||
	( pecas[2] == pecas[4] && pecas[4]==pecas[6] && pecas[2]!=0);
	if( win )
	{
		//WINNER
		playTone(600,50);
		wait1Msec(500);
		winner=jog;
		return true;
	}
	else
	{
		int x=0,t=1;
		for(x=0;x<9;x++)
		{
			t*=pecas[x];
		}
		if(t!=0) //Draw Game, Start again!!
		{
			draw=true;
			playTone(200,50);
			wait1Msec(500);
			return true;
		}
		else
			return false;
	}

}

bool novojogo()
{
	int p=1;
	const int timeout=10000;
	while(true)
	{
		eraseDisplay();
		displayCenteredTextLine(1,"NEW GAME?");
		displayCenteredBigTextLine(3,"YES  NO");


		if(p==1)drawRect(2,21,47,21+22);
		if(p==2)drawRect(52,21,95,21+22);

		clearTimer(T1);
		time1[T1] = 0;
		while(nNxtButtonPressed==-1)//Wait for Press
		{
			displayTextLine(6,"Escolha em: %d",(timeout-time1(T1))/1000);
			if(time1(T1)>timeout)
			return(p==1?true:false);
		}
		if(nNxtButtonPressed==1 || nNxtButtonPressed==2 )
		{
		p=(p==1?2:1);
		}
		if(nNxtButtonPressed==3)
		{
			eraseDisplay();
			wait1Msec(1000);
		return(p==1?true:false);
		}
		while(nNxtButtonPressed!=-1){}//Wait for Release
	}
}

void exit()
{

	eraseDisplay();
	while(nNxtButtonPressed!=-1){}//Esperar por largar

	int p=1;
	const int timeout=10000;

	clearTimer(T1);
	while(time1(T1)<timeout)
	{
		eraseDisplay();
		displayCenteredTextLine(1,"Wanna Go OUT?");
		displayCenteredBigTextLine(3,"YES  NO");
		if(p==1)drawRect(2,21,47,21+22);
		if(p==2)drawRect(52,21,95,21+22);

		while(nNxtButtonPressed==-1)//Wait for press
		{
			displayTextLine(6,"Escolha em: %d",(timeout-time1(T1))/1000);
			if(time1(T1)>timeout)
			{
				if(p==1)
				{
					stopAllTasks();
				}
				else
				{
					while(nNxtButtonPressed!=-1){}//Wait for release
					return;
				}
			}
		}
		if(nNxtButtonPressed==1 || nNxtButtonPressed==2 )
		{
		p=(p==1?2:1);
		}
		if(nNxtButtonPressed==3)
		{
			eraseDisplay();
			if(p==1)
			{
				stopAllTasks();
			}
			else
			{
				while(nNxtButtonPressed!=-1){}//Wait for release
				return;
			}
		}
		if(nNxtButtonPressed==0)
		{
			stopAllTasks();
		}
		while(nNxtButtonPressed!=-1){}//Wait for release
	}
}

void anim()
{
	clearTimer(T4);
	while(time1(T4)<800)
	{
		fillRect(10, 50, 10+time1(T4)/10, 10+50);
	}
	clearTimer(T4);
	while(time1(T4)<800)
	{
		fillRect(xx/2-5, 50, xx/2+5 , 50 - time1(T4)/20 );
	}
	wait1Msec(500);
	displayStringAt(xx/2+10, 17, "Games");
	wait1Msec(1500);

	eraseDisplay();
	clearTimer(T4);
	while(time1(T4)<2500)
	{
		drawEllipse(0, yy, time1(T4)/10, 0);
		wait1Msec(100);
	}
	drawRect(xx/2-35, yy/2+5, xx/2+35, yy/2+5);
	eraseRect(xx/2-35, yy/2+5, xx/2+35, yy/2+5);
	displayStringAt(xx/2-33,yy/2+4,"JOGO DO GALO");//JOGO DO GALO <- Name

	wait1Msec(2000);
}

task main()
{
	anim();
	bool novo=true;
	int ftp=(random(1000)%2)+1; //First To Play (1 or 2)
	nNxtButtonTask  = -2;
	nNxtExitClicks  = 3;

	do{
		eraseDisplay();
		int i;

		for(i=0;i<9;i++)pecas[i]=0;
		draw=false;

		winner=0;
		int actual=0;
		int jogadascount=0;

		bool fim=false;
		do
		{
			int i=0,j=0;
			for(i=0;i<3;i++)
			{
				for(j=0;j<3;j++)
				{
					if( pecas[i*3+j] == 1 ) displayBigStringAt(xpeca[j], ypeca[i], "x");
					if( pecas[i*3+j] == 2 ) displayBigStringAt(xpeca[j], ypeca[i], "o");
					drawRect( x0quad[j] , y0quad[i] , x1quad[j] , y1quad[i]);
				}
			}
			int cact=actual/3;
			int lact=actual%3;

			if(pecas[actual]!=0) fillRect( x0quad[lact]+m , y0quad[cact]+m , x1quad[lact]-m , y1quad[cact]-m);
			else
			{
				if(ftp==1)displayStringAt(xpeca[lact], ypeca[cact]-m, "x");
				if(ftp==2) displayStringAt(xpeca[lact], ypeca[cact]-m, "o");
				drawRect( x0quad[lact]+m , y0quad[cact]+m , x1quad[lact]-m , y1quad[cact]-m);
			}

			displayStringAt(5,yy-5,"P1:x");
			displayStringAt(5,yy-15,"P2:o");
			if(ftp==1)displayStringAt(2,30,"Agr:x");
			if(ftp==2)displayStringAt(2,30,"Agr:o");
			displayStringAt(2,10,"JOG:%d",jogadascount);

			while(nNxtButtonPressed==-1){}//waitClick

			if(nNxtButtonPressed==0)
			{
				exit();
			}
			if(nNxtButtonPressed==1)
			{
				actual++;
				actual%=9;
			}
			if(nNxtButtonPressed==2)
			{
				if(actual==0)
					actual=8;
				else
					actual--;
			}
			if(nNxtButtonPressed==3)
			{
				//Play it.
				if(pecas[lact+cact*3]==0)
				{
					pecas[lact+cact*3]=ftp;
					fim=verifica(ftp);
				ftp=(ftp==1?2:1);//Change Player
					jogadascount++;
				}
				else
				{
					playTone(444,10);
					wait1Msec(100);
				}
			}

			while(nNxtButtonPressed!=-1){}

			eraseDisplay();


		}while(!fim);

		wait1Msec(1000);
		eraseDisplay();
		if(!draw)
		{
			displayCenteredTextLine(1,"The winner is");
			if(winner==1) displayBigStringAt(xpeca[1]-shiftx, ypeca[1]-shifty, "x");
			if(winner==2) displayBigStringAt(xpeca[1]-shiftx, ypeca[1]-shifty, "o");
			displayCenteredBigTextLine(5,"Player %d",winner);
		}
		else
		{
			displayCenteredTextLine(1,"It's a");
			displayBigStringAt(xpeca[0]-shiftx, ypeca[1]-shifty, "x");
			displayBigStringAt(xpeca[2]-shiftx, ypeca[1]-shifty, "o");
			displayCenteredBigTextLine(5,"DRAW");
		}
		wait1Msec(3000);
		novo=novojogo();
		ftp=winner;

	}while(novo);

}

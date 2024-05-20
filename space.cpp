// Project 
// Space Shooter Game

// Memebers:
// Muhammad Taha Khan       21L-5238
// Waleed Khan              21L-5341
// Iqra Bokhari             21L-5087
// Fatima Imran             21L-5166

/////////////////////////////////////////////////////////////////////////////////

// Library Files
#include<graphics.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<time.h>
#include<stdio.h>

// Start Function and Instructions 
int start(int st = 0)
{
	// Displaying Instructions on the Screen
    setcolor(WHITE);
    settextstyle(8, 0, 7);
    outtextxy(100,100,"WELCOME TO SPACE SHOOTER");
    
    setcolor(WHITE);
    settextstyle(8, 0, 3);
    outtextxy(100,300,"Instructions:");
    outtextxy(100,325,"Press A to move left and D to move right");
    outtextxy(100,350,"Press Spacebar to shoot the aliens");
    outtextxy(100,375,"You will get 1 point each time you kill an alien");
    outtextxy(100,400,"There are 3 lives and 5 levels in this game. Complete level 5 to win the game");
    outtextxy(100,425,"After losing 3 lives game will finish.");
    outtextxy(100,450,"Press Esc key to exit");
    
    outtextxy(100,550,"Press Enter Key to start the game:");

    if (GetAsyncKeyState(VK_RETURN))
    {
    	st = 1;
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		st = -1;
	}
	else
	st = 0;
	return st;
}
int totalscore;
int play = 0;

// Function to display border
void border()
{
	setcolor(BLACK);
	
	rectangle(0,0,1200,50);
	rectangle(0,650,1200,700);
	rectangle(0,50,50,650);
	rectangle(850,50,900,650);
	rectangle(1150,50,1200,650);
	
	setfillstyle(SOLID_FILL,BLACK);
	
	floodfill(600,25,BLACK);
	floodfill(600,675,BLACK);
	floodfill(25,300,BLACK);
	floodfill(875,300,BLACK);
	floodfill(1175,300,BLACK);
}


// Function to calculate Score during the game
int points(int score, int highscore)
{
	score++;
	totalscore++;
	int oldhighscore = 0;
	
	// Checking if the score is greater than highscore
	if (totalscore > highscore)
		{
			highscore = totalscore;
		}
	std::ifstream file;
	file.open("highscore.txt");
	if (file)
	{
		// Taking highscore value from the file if previously stored
		while(!file.eof())
		{	
			file >> oldhighscore;
		}

	}
	file.close();
	
	std::ofstream file2;
	file2.open("highscore.txt");
	// Storing highscore value in the file
	if (highscore > oldhighscore)
	{
		file2 << highscore;
	}
	else
	{
		file2 << oldhighscore;
	}
	
	file2.close();
	return score;
}

// Function to control the movement of bullets
int bullets(bool fire, int x, int y = 0)
{
	// Firing a bullet if the user press SPACEBAR 
	if (GetAsyncKeyState(VK_SPACE) && fire == false)
	{
		y = 600;
		fire = true;
	}
	// Moving the bullet upwards after it is fired
	if (fire == true)
	{
		y -= 20;
		setcolor(RED);
		circle(x,y,5);	            
		setfillstyle(SOLID_FILL,RED);
		floodfill(x,y,RED);  
		
		fire = true;
	}	

	return y;
}

int n = 0;
int d = 0;

bool emp = false;

// Storing coordinates of aliens in a 2D Array.
int alien[30][8] = {{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800},{100,200,300,400,500,600,700,800}};

// Function to display and move Aliens
bool aliens(int bul_y,int bul_x,int down,int speed)
{

	int m = 0;
	bool kill = false;
	bool crash = true;
	int radius;
	int alien_x;
	int alien_y;
	
	int empty = 0;
	
	// For moving the aliens down
	if(down % speed == 0)
	{
		d++;
	}
	// Checking if the user killed all the aliens in a level
	for (int j = 0; j < 8;j++)
	{
		if(alien[n][j] <= 0)
		{
			empty++;
		}
	}
	if (empty == 8)
	{
		emp = true;
		return kill;
	}
	
	// Using a loop to display all the aliens in each level
    do
   	{
   		// Values of x and y coordinates for each alien
		alien_x = alien[n][m];
		alien_y = 100*d;
		
		// 	If the bullet hits the alien then disappearing the alien from the screen
		if (bul_y==alien_y && alien_x + 20 >= bul_x && alien_x - 20 <= bul_x)
		{
			alien[n][m] = -50;
			std :: cout << "\a";
			kill = true;
		}
		else // Displaying alien on the screen
		{
			radius = 20;
			setcolor(GREEN);
		circle(alien_x,alien_y,radius);		            
		setfillstyle(SOLID_FILL,GREEN);
		floodfill(alien_x,alien_y,GREEN);
		}
		int sw,ew,sh,eh;
		// Taking coordinates of spaceship from the file to check if the aliens hit the spaceship.
		std :: ifstream space;
		space.open("spaceship.txt");
		{
			space >> sw;
			space >> ew;
			space >> sh;
			space >> eh;
			
			space.close();
			if (alien_x >= sw && alien_x <= ew && alien_y >= sh && alien_y <= eh)
			{
				kill = false;
			}
		}    
 		m++;
	
	}while(m < 8 && alien_y < 700);
	return kill;

}


// Function for spaceship movement 
int spaceship_movement(int c = 0)
{
	// Moving the position of spaceship to the left if the user presses 'A'
	if (GetAsyncKeyState('A'))
	{
		c--;
	}
	// Moving the position of spaceship to the right if the user presses 'D'	
	if (GetAsyncKeyState('D'))
	{
		c++;
	}
	

	return c;
}

// Function to display spaceship
int spaceship(int i,int y = 0)
{
	// 
	i*=40;
	// Using boundary values so that the spaceship remain in its boundary
	if (i > 400)
	{
		i = 400;
	}
	else if (i <= -300)
	{
		i = -300;
	}
	
	// Calculating coordinates for the head of the spaceship
	int stw = 390 + i;
	int edw = 420 + i;
	int median_w = (stw + edw) /2;
	int sth = 590 + y;
	int edh = 610 + y;
	int median_h = (sth + edh) /2;
	setcolor(RED);
	rectangle(stw,sth,edw,edh);
	setfillstyle(SOLID_FILL,RED);
	floodfill(median_w,median_h,RED);
	
	// Calculating coordinates for the body of the spaceship
	int start_w = 370+ i;
	int end_w = 440+i;
	int m_w = (start_w + end_w) /2;
	int start_h = 610+y;
	int end_h = 640+y;
	int m_h = (start_h + end_h) /2;
	setcolor(BLUE);	
	
	rectangle(start_w,start_h,end_w,end_h);	
	setfillstyle(SOLID_FILL,BLUE);
	floodfill(m_w,m_h,BLUE);
	
	// Calculating position of the bullet
	int avg = (stw + edw)/2;
	
	// Storing the coordinates of the spaceship in a file
	std::ofstream ship;
	ship.open("spaceship.txt");
	ship << start_w;
	ship << std:: endl;
	ship << end_w;
	ship << std:: endl;
	ship << sth;
	ship << std:: endl;
	ship << end_h;
	ship.close();

	
	
	return avg;
	


}

main()
{
	initwindow(1200,700);

	// Infinite loop so that a user can play the game as many time as he/she wants.
	for(;;) {
	int st = 0;
	// Loop which gets Enter or Exit input 
	do {
		st = start(st);
	}while(st == 0);
	
	cleardevice();

	// Variables 
	int bul_x;
	int bul_y;
	float speed = 250;
	int level = 1;
	int lives = 2;
	int score = 48;
	int highscore = 0;
	char scores[9] = {'0'};
	int o = 0;
	int p = 48;
	
	totalscore = 0;
	play++;
	
	// End the game if the user press ESC key
	if (st == -1)
	{
		return 0;
	}
	
	// Start the game if the user press Enter Key
	if (st == 1)
	{
	// Loop to continue the game for different levels and lives
	do
	{
	int i = 0;
	int y = 0;
	bool fire = false;
	int down = 0;
	bool killed = false;
	d = 0;

	// Infinite loop so that all the functions run parallel 
	while(st == 1)
	{
		// Code to display title on each screen
		border();
		setcolor(WHITE);
    	settextstyle(8, 0, 4);
    	outtextxy(300,10,"SPACE SHOOTER");
	
	
		bul_x = spaceship(i,y);
		killed = aliens(bul_y,bul_x,down,speed);
		
		down++;
		i = spaceship_movement(i);
		bul_y = bullets(fire,bul_x,bul_y);
		
		if(bul_y < 600 && bul_y > 70)
		{
			fire = true;
		}
		else
		{
			fire = false;
		}
		
		// Disappearing the bullet if the enemy is killed and Displaying scores on the screen 
		if (killed == true)
		{
			bul_y = -50;
			score = points(score,highscore);
			if (score > 57)
			{	
				p++;
				score = 48;
			}
			scores[0] = p;
		
			scores[1] = score;
		}
		
		setcolor(WHITE);
    	settextstyle(8, 0, 3);
    	outtextxy(920,350,"Score: ");
		setcolor(WHITE);
 	    settextstyle(8, 0, 3);
    	outtextxy(1040,350,scores);
    
    	// Code to display lives left on each screen
		setcolor(WHITE);
		settextstyle(8,0,3);
		if (lives == 2)
		{
			outtextxy(920,500,"Lives Left : 2");
		}
		else if (lives == 1)
		{
			outtextxy(920,500,"Lives Left : 1");
		}
		else
		{
			outtextxy(920,500,"Lives Left : 0");
		}

		// Code to display level on each screen
		setcolor(WHITE);
		settextstyle(8,0,3);
		if (level == 1)
		{
			outtextxy(920,200,"Level : 1");
		}
		else if (level == 2)
		{
			outtextxy(920,200,"Level : 2");
		}
		else if (level == 3)
		{
			outtextxy(920, 200,"Level : 3");
		}
		else if (level == 4)
		{
			outtextxy(920,200,"Level : 4");
		}
		else if (level == 5)
		{
			outtextxy(920,200,"Level : 5");
		}
		
		// Code to increase the level if the user kill all the aliens in that level
		if (score > 0 && emp == true)
		{
			speed /= 3;
			level++;

			y = -1000;
			n++;
			emp = false;
			
			char lev = level + 48;
			char le[2] = {' ','\0'};
			le[0] = lev;
			
			if (level <= 5)
			{
			cleardevice();
			setcolor(WHITE);
    		settextstyle(8, 0, 5);
    		outtextxy(400,300,"Level Completed!");
    		delay(2000);
    		cleardevice();
			setcolor(WHITE);
    		settextstyle(8, 0, 5);
    		outtextxy(400,300,"Level: ");
    		outtextxy(600,300,le);
    		delay(3000);
    		}
			break;
		}
		// Code to decrease the life if the user fails to kill all the aliens in that level
		if (d > 5 && killed == false)
		{
			y = -1000;
			lives--;
			bul_y = -50;
			n++;
			d = 0;
			char live = lives + 48;
			char l[2] = {' ','\0'};
			l[0] = live;
			delay(1000);
			
			if (lives >= 0)
			{
			cleardevice();
			setcolor(WHITE);
    		settextstyle(8, 0, 5);
    		outtextxy(400,300,"Lives left: ");
    		outtextxy(700,300,l);
    		delay(3000);
    		}
			break;
	    }
		
		// To exit the game if the user presses ESC key in the middle of the game
		if (GetAsyncKeyState(VK_ESCAPE))
    	{
    		return 0;
		}
		delay(50);
		cleardevice();
	}	
	
	// If the user clear all the levels then displaying a message with the highest score.
	if (level > 5)
	{
		int ohs;
		// Taking Highest Score from a file and displaying it
	std::fstream file3;
	file3.open("highscore.txt");
	if (file3)
	{
		while (!file3.eof())
		{
			file3 >> ohs;
		}
	}
	if (ohs > highscore)
	{
		highscore = ohs;
	}
	else if (ohs < highscore)
	{
		//file3 << high;
	}
	file3.close();
			
	char hs[0];
	hs[0] = highscore / 10 + 48;
	hs[1] = highscore % 10 + 48;     
        
	cleardevice();
	setcolor(WHITE);
    settextstyle(8, 0, 5);
    outtextxy(100,200,"Congratulations you have won!");
    settextstyle(8, 0, 4);
    if (highscore > totalscore)
    {
    	outtextxy(200,400,"Highscore is: ");
    	outtextxy(500,400,hs);
   		outtextxy(200,500,"Highscore not reached :( ");
   	
	}
	else
	{
		outtextxy(200,400,"New Highscore: ");
    	outtextxy(500,400,hs);
	}
    delay(10000);
		break;
	}
	
	// If the user lose all the lives then displaying a message with the highest score.
	if (lives < 0)
	{
		int ohs;
	// Taking Highest Score from a file and displaying it
	std::fstream file4;
	file4.open("highscore.txt");
	if (file4)
	{
		while (!file4.eof())
		{
			file4 >> ohs;
		}
	}
	if (ohs > highscore)
	{
		highscore = ohs;
	}
	file4.close();
			
	char hs[0];
	hs[0] = highscore / 10 + 48;
	hs[1] = highscore % 10 + 48;     
        
		cleardevice();
		setcolor(WHITE);
    	settextstyle(8, 0, 7);
    	outtextxy(300,100,"Game Over");
    	settextstyle(8, 0, 6);
    	outtextxy(200,200,"Better luck next time");
     	settextstyle(8, 0, 4);
     	
     	if (highscore > totalscore)
    	{
    		outtextxy(200,400,"Highscore is: ");
    		outtextxy(500,400,hs);
	   		outtextxy(200,500,"Highscore not reached :( ");
		}
		else
		{
			outtextxy(200,400,"New Highscore: ");
    		outtextxy(500,400,hs);
    		outtextxy(600,400,":)");
		}
    	delay(10000);
		break;
	}
	}while(lives >= 0);
	cleardevice();
	
}
}
}
#include<windows.h>
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#include <GL/glut.h>
#include <GL/GLAux.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

#define speed 2 //opossite plane speed
#define speed_bullet 10;
#define main_plane_movement 10;

#define width 800
#define hight 600

int plane_side = width/2 - 50,plane_high = 0; //my plane position at the start of game
int plane_1_x = rand() % 750,plane_2_x = rand() % 750,plane_3_x = rand() % 750;//opossite plane
int plane_1_y = 450,plane_2_y = 500,plane_3_y = 550,bullet = 0,bullet_x = -4000,bullet_y =900;//plane & bullet
double timer_plane_x = 700,timer_plane_y = 0;

int help = 0;
int blast=0;
int SCORE = 0;
int game = 1; // use to play the game
int play_mode = 0;
int planeMove = 1;




/*Arin code

*/

float cX = 0;
float cY = 640;
float cX1 = 0;
float cY1 = 600;
float cX2 = 0;
float cY2 = 570;
float cX3 = 0;
float cY3 = 500;
#define PI 3.1416


void circle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

	for(i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
	}

	glEnd();
}

void cloud(double x, double y){

	glPushMatrix();
	glTranslated(x,y,0);
	glScaled(2,2,1);
	glColor3f(.93, .93, .88);
	glPushMatrix();
	circle(10,8);
	glPopMatrix();
	glPushMatrix();
	glTranslated(10,11,0);
	circle(12,9);
	glPopMatrix();
	glPushMatrix();
	glTranslated(16.5,.15,0);
	circle(15,10);
	glPopMatrix();
	glPopMatrix();
}




void showTextLarge(char text[], int r, int g, int b, int x, int y, int z)
{
	glColor3f(r, g, b);
	glRasterPos3f( x , y , z);
	for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}


/*Arin code

*/


void iShowBMP(int x, int y, char filename[])
{

	AUX_RGBImageRec *TextureImage;

	TextureImage = auxDIBImageLoad(filename);

	glRasterPos2f(x, y);
	glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

	free(TextureImage->data);
	free(TextureImage);

}

void plan_blast_finish()//to finish the game 
{
	if(plane_side+45 >= plane_1_x && plane_side+45 <= plane_1_x + 100 && (plane_high+100 >= plane_1_y &&  plane_high+100 <= plane_1_y + 100))//for blast to touch in the middle of the plane
	{
		iShowBMP(plane_side,plane_high,"image/blast.bmp");
		game = 0;
	}
	if(plane_side+45 >= plane_2_x && plane_side+45 <= plane_2_x + 100 && (plane_high+100 >= plane_2_y &&  plane_high+100 <= plane_2_y + 100))//for blast to touch in the middle of the plane
	{
		iShowBMP(plane_side,plane_high,"image/blast.bmp");
		game = 0;
	}
	if(plane_side+45 >= plane_3_x && plane_side+45 <= plane_3_x + 100 && (plane_high+100 >= plane_3_y &&  plane_high+100 <= plane_3_y + 100))//for blast to touch in the middle of the plane
	{
		iShowBMP(plane_side,plane_high,"image/blast.bmp");
		game = 0;
	}


}


void run(){

	if(bullet == 1){ //for bullet movement
		if(bullet_y < hight + 100){
			bullet_y += speed_bullet;
		}
	}
	if(plane_1_y >= -600){   //enemy plane movemet
		plane_1_y -= speed;
		if(plane_1_y <= -600){
			plane_1_x = rand() % 800;
			plane_1_y = (rand() % 100) + 600;
		}
		glutPostRedisplay();

	}
	if(plane_3_y >= -600){  //enemy plane movemet
		plane_3_y -= speed;
		glutPostRedisplay();
		if(plane_3_y <= -600){
			plane_3_x = rand() % 800;
			plane_3_y = (rand() % 100) + 600;
		}

	}
	if(plane_2_y >= -600){  //enemy plane movemet
		plane_2_y -= speed;
		glutPostRedisplay();
		if(plane_2_y <= -600){
			plane_2_x = rand() % 800;
			plane_2_y = (rand() % 100) + 600;
		}

	}
}

int rand_x(int x)
{
	if (width - 100 >= x && 0 <= x)
		return x;
	else
		rand_x((rand() % width) - (rand() % 100));
}
void bullet_hite() // to hit the plane and score
{

	if (((plane_1_x <= bullet_x + 32 && plane_1_x + 100 >= bullet_x + 32) || (plane_1_x >= bullet_x + 32 && plane_1_x <= bullet_x + 44)) && bullet_y+100 >= plane_1_y &&  bullet_y+100 <= plane_1_y + 100)
	{
		SCORE++;
		bullet_y = hight + 100;					//this is for 1st plan codition to come from opposite side
		plane_1_y = hight + 10;
		plane_1_x = rand_x((rand() % width) - (rand() % 100));
	}

	if (((plane_2_x <= bullet_x + 32 && plane_2_x + 100 >= bullet_x + 32) || (plane_2_x >= bullet_x + 32 && plane_2_x <= bullet_x + 44)) && bullet_y+100 >= plane_2_y &&  bullet_y+100 <= plane_2_y + 100)
	{
		SCORE++;
		bullet_y = hight + 100;
		plane_2_y = hight + 10;					//this is for 2nd plan codition to come from opposite side
		plane_2_x = rand_x((rand() % width) - (rand() % 100));
	}

	if (((plane_3_x <= bullet_x + 32 && plane_3_x + 100 >= bullet_x + 32) || (plane_3_x >= bullet_x + 32 && plane_3_x <= bullet_x + 44)) && bullet_y+100 >= plane_3_y &&  bullet_y+100 <= plane_3_y + 100)
	{
		SCORE++;
		bullet_y = hight + 100;
		plane_3_y = hight + 10;				//this is for 3rd plan codition to come from opposite side
		plane_3_x = rand_x((rand() % width) - (rand() % 100));
	}

}




void init()
{
	cX = rand() % 800;
	cX1 = rand() % 800;
	cX2 = rand() % 800;
	cX3 = rand() % 800;
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(0, 800.0, 0, 600.0, 0, 100.0);
}

void user_plane(){
	iShowBMP(plane_side, plane_high, "image/plane.bmp");
}

void enemy_plane(){
	iShowBMP(plane_1_x, plane_1_y, "image/plane-1.bmp");
	iShowBMP(plane_2_x, plane_2_y, "image/plane-2.bmp");
	iShowBMP(plane_3_x, plane_3_y, "image/plane-3.bmp");
}

void bulletf(){
	if(bullet == 1){
		iShowBMP(bullet_x,bullet_y,"image/bullet.bmp");
	}
}
void scoretext()
{
	char text[32] = "SCORE: 0";

	int strt=8;
	if(SCORE < 10)
		strt--;
	int tmp=SCORE;
	while(tmp)
	{
		text[strt--]=(tmp%10)+'0';
		tmp/=10;
	}
	glColor3f(0.96, 0.96, 0.96);
	glRasterPos3f( 300 , 350 , 0.0);
	//glScaled(2,2,0);
	for(int i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
}

void homePage(){
	glBegin(GL_QUADS);
	glColor3f(0.93f,0.86f,0.50f);
	glVertex2d(0,0);
	glVertex2d(800,0);
	glVertex2d(800,600);
	glVertex2d(0,600);
	glEnd();


	glBegin(GL_QUADS);
	//glColor3f(0.74f,0.74f,0.74f);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex2d(100,100);
	glVertex2d(100,150);
	glVertex2d(300,150);
	glVertex2d(300,100);
	glEnd();

	glBegin(GL_QUADS);
	//glColor3f(0.74f,0.74f,0.74f);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex2d(100,200);
	glVertex2d(100,250);
	glVertex2d(300,250);
	glVertex2d(300,200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,0.0f);
	//glColor3f(0.74f,0.74f,0.74f);
	glVertex2d(100,300);
	glVertex2d(100,350);
	glVertex2d(300,350);
	glVertex2d(300,300);
	glEnd();

	showTextLarge("Air Fighter ", 0, 0, 0, 100, 400, 0);
	showTextLarge("Play ", 0, 0, 0, 170, 323, 0);
	showTextLarge("Instruction ", 0, 0, 0, 160, 223, 0);
	showTextLarge("Exit ", 0, 0, 0, 170, 123, 0);
}

void helpPage(){

	glBegin(GL_QUADS);
	glColor3f(0.93f,0.996f,0.937f);
	glVertex2d(0,0);
	glVertex2d(800,0);
	glVertex2d(800,600);
	glVertex2d(0,600);
	glEnd();

	showTextLarge("1. Start the game click with start botton. ", 0, 0, 0, 50, 450, 0);
	showTextLarge("2. To move the plane left to right use the right arrow key from your laptop. ", 0, 0, 0, 50, 400, 0);
	showTextLarge("3. To move the plane right to left use the left arrow key from your laptop. ", 0, 0, 0, 50, 350, 0);
	showTextLarge("4. For firing use SPACE button. ", 0, 0, 0, 50, 300, 0);
	showTextLarge("5. If there is any collision  then game is over.",0,0,0,50,250,0);

	iShowBMP(0, 568, "image/back.bmp");
}

void myDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);


	if (play_mode == 0 && game == 1 && help == 0)  // 1st page (play , exit)
	{
		homePage();
	}
	if (play_mode == 0 && game == 1 && help == 1)  // for help page
	{
		helpPage();
	}
	else if(play_mode == 1 && game == 1) // to play the game
	{
		bullet_hite();
		enemy_plane();
		bulletf();
		iShowBMP(plane_side, plane_high, "image/plane.bmp");

		/*if (blast == 1)
		{
		iShowBMP(bullet_x, bullet_y, "image/bullet.bmp");
		}*/
		plan_blast_finish();



		/*Arin code

		*/
		cloud(cX,cY);
		cloud(cX1,cY1);
		cloud(cX2,cY2);
		cloud(cX3,cY3);

		cY-=0.5;
		cY1-=0.5;
		cY2-=0.5;
		cY3-=0.5;

		if(cY < -30){
			cY = 640+rand() % 180;
			cX = rand() % 800;
		}
		if(cY1 < -50){
			cY1 = 640+rand() % 180;
			cX1 = rand() % 800;
		}
		if(cY2 < -120){
			cY2 = 640+rand() % 180;
			cX2 = rand() % 800;
		}
		if(cY3 < -100){
			cY3 = 640+rand() % 180;
			cX3 = rand() % 800;
		}

		/*Arin code

		*/

	}
	else if(game == 0) //game over
	{
		scoretext();
		planeMove = 0;
		iShowBMP(0, 568, "image/back.bmp");
		iShowBMP(plane_side, plane_high, "image/blast.bmp");
		iShowBMP(width/2-150, hight / 2-50, "image/game_over.bmp");

	}

	glFlush();
}

void my_keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case ' ':
		if(bullet_y >= hight){
			bullet = 1;
			bullet_x = plane_side + 10;
			bullet_y = plane_high + 20;
		}

		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void spe_key(int key, int x, int y)
{
	if(planeMove == 1){
		switch (key) {


		case GLUT_KEY_LEFT:
			if (plane_side >= 8)
			{
				plane_side -= main_plane_movement;
			}
			glutPostRedisplay();
			break;

		case GLUT_KEY_RIGHT:
			if (plane_side <= 700)
			{
				plane_side += main_plane_movement;
			}
			glutPostRedisplay();
			break;

		case GLUT_KEY_DOWN:
			if(plane_high != 0){
				plane_high -= main_plane_movement;
			}
			glutPostRedisplay();
			break;

		case GLUT_KEY_UP:
			if (plane_high <= 500)
			{
				plane_high += main_plane_movement;
			}

			glutPostRedisplay();
			break;
		default:
			break;
		}
	}
}
void my_mouse(int button, int state, int x, int y)
{
	//cout<< x << "-" <<y << endl;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if(1)
		{
			if (0 <= x && 50 >= x && 0 <= y && 32 >= y)// for back button
			{
				play_mode = 0; //for main page 
				game = 1;
				help = 0;
				SCORE = 0;
				planeMove = 1;
				//plane_1_y = 450, plane_2_y = 500, plane_3_y = 550, bullet = 0, bullet_x, bullet_y = 900;//plane & bullet
				//plane_1_x = rand() % 200 + 1, plane_2_x = rand() % 200 + 200, plane_3_x = rand() % 200 + 400;//opossite plane
			}
			if (100 <= x && 300 >= x  && 250 <= y && 300 >= y)//TO PLAY THE GAME 
			{
				play_mode = 1;
				game = 1;
				planeMove = 1;
			}
			if (100 <= x && 300 >= x && 350 <= y && 400 >= y)//help
			{
				help = 1;
			}
			if (100 <= x && 300 >= x && 450 <= y && 500 >= y)//exit
			{
				exit(0);
			}
		}
		break;


	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)

			break;
	default:
		break;
	}
}


int main(){

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(width,hight);
	glutInitWindowPosition(150,20);
	glutCreateWindow("Air Fighter");
	init();
	glutIdleFunc(run);
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(my_keyboard);
	glutMouseFunc(my_mouse);
	glutSpecialFunc(spe_key);//for user plane movement func
	glutMainLoop();
	return 0;
}

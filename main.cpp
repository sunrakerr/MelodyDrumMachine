#include <iostream>
#include <GL/freeglut.h>
#include<windows.h>
#include<mmsystem.h>
#include<thread>
#include <fstream>
#include<math.h>
#define PI 3.14

using namespace std;
//y-axis
//[141,192] -> kick
//[193,248] -> snare
//[253,304] -> hats
//[309,361] -> claps
//[366,418] -> toms
//[422,474] -> bells
//[478,529] -> sfx1
//[534,586] -> sfx2
//x-axis
//[127,179] -> col1
//[183,234] -> col2
//[239,290] -> col3
//[295,347] -> col4
//[351,404] -> col5
//[408,460] -> col6
//[464,516] -> col7
//[520,571] -> col8

int yaxis[8][2] = {{141,192},{193,248},{249,304},{305,361},{362,418},{419,474},{475,529},{530,586} };
int xaxis[8][2] = {{127,179},{179,234},{234,290},{290,347},{347,404},{404,460},{460,516},{516,571} };

int send[1][2]={{0}};
int state[8][8]={{0}};
int xb,yb;
int hovstat[1][2]={{0}};
bool test=true;
int waiter=0,inc=0,loopCnt=0,gotosplash=0;
float i=1.0,j=0.0,k=1.0;
bool finish=false,swapper=false,info=false,night=false,make=false;
const char* pypath="";
int bolcol[8]={0};
char title[100] = {0};




void plot(int x, int y,int pntX1,int pntY1,int p)
{   //int pntX1=0,pntY1=250;
    glPointSize(p);//2
	glBegin(GL_POINTS);
	glVertex2i(x+pntX1, y+pntY1);
	glEnd();
}

void midPointCircleAlgo(int r,int pntX1,int pntY1,int p)
{   glPointSize(p);
	int x = 0;
	int y = r;
	float decision = 5/4 - r;
	plot(x, y,pntX1,pntY1,p);

	while (y > x)
	{
		if (decision < 0)
		{
			x++;
			decision += 2*x+1;
		}
		else
		{
			y--;
			x++;
			decision += 2*(x-y)+1;
		}

		plot(x, y,pntX1,pntY1,p);
		plot(x, -y,pntX1,pntY1,p);
		plot(-x, y,pntX1,pntY1,p);
		plot(-x, -y,pntX1,pntY1,p);
		plot(y, x,pntX1,pntY1,p);
		plot(-y, x,pntX1,pntY1,p);
		plot(y, -x,pntX1,pntY1,p);
		plot(-y, -x,pntX1,pntY1,p);
	}
}


void addNote(int a,int b)
{
     if(state[a][b]==0)
    {
        state[a][b]=1;
        switch(a){
            case 0:PlaySoundA("soundpack/Kick.wav",NULL,SND_ASYNC);break;

            case 1:PlaySoundA("soundpack/Snare.wav",NULL,SND_ASYNC);break;

            case 2:PlaySoundA("soundpack/Hat.wav",NULL,SND_ASYNC);break;

            case 3:PlaySoundA("soundpack/Clap.wav",NULL,SND_ASYNC);break;

            case 4:PlaySoundA("soundpack/Tom.wav",NULL,SND_ASYNC);break;

            case 5:PlaySoundA("soundpack/Bell.wav",NULL,SND_ASYNC);break;

            case 6:PlaySoundA("soundpack/Sfx1.wav",NULL,SND_ASYNC);break;

            case 7:PlaySoundA("soundpack/Sfx2.wav",NULL,SND_ASYNC);break;

        }

    }
    else
    {   state[a][b]=0;
    }


}
void boxColor()
{

    for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                    if(state[i][j]==1)
                    {
                        if(night==false)
                            {
                                glColor3f(0.8,0.8,0.8);
                            }
                            else
                            {
                                glColor3f(0.35,0.35,0.35);
                            }
                        glRectf((-225+(56.25*(j+1))),(210-(56.25*(i))),(-225+(56.25*(j))),(210-(56.25*(i+1))));


                        switch(i)
                        {
                                    case 0:glColor3f(1,148.0/255.0,212.0/255.0);


                                            break;
                                    case 1:glColor3f(196.0/255.0,153.0/255.0,1);


                                            break;
                                    case 2:glColor3f(153.0/255.0,201.0/255.0,1);


                                            break;
                                    case 3:glColor3f(153.0/255.0,1,177.0/255.0);


                                            break;
                                    case 4:glColor3f(1,253.0/255.0,120.0/255.0);


                                            break;
                                    case 5:glColor3f(1,155.0/255.0,79.0/255.0);


                                            break;
                                    case 6:glColor3f(158.0/255.0,103.0/255.0,79.0/255.0);


                                            break;
                                    case 7:glColor3f(252.0/255.0,116.0/255.0,78.0/255.0);


                                            break;
                        }
                        //glRectf(-225+(56.25*(j+1)),210-(56.25*(i)),-225+(56.25*(j)),210-(56.25*(i+1)));
                        glRectf((-225+(56.25*(j+1))-2),(210-(56.25*(i))+2),(-225+(56.25*(j))-2),(210-(56.25*(i+1))+2));

                    }else{
                    bolcol[i]=0;
                    }
            }
        }

}
void drawhover(){
    int i=hovstat[0][0];
    int j=hovstat[0][1];
    glColor3f(0.92,0.92,0.92);
    glRectf((-225+(56.25*(j+1))),(210-(56.25*(i))),(-225+(56.25*(j))),(210-(56.25*(i+1))));

}

void box(int x,int y){
    int i,j;
    if(x>=127 && x<=571 && y>=141 && y<=586)
        {
      for(i=0;i<8;i++){
            if(y>yaxis[i][0] && y<yaxis[i][1])
            {

                send[0][0]=i;
                break;
            }
            else
            {
                send[0][0]=-1;
            }

    }
    for(j=0;j<8;j++)
    {
        if(x>xaxis[j][0] && x<xaxis[j][1])
        {

            send[0][1]=j;
            break;
        }
        else
            {
                send[0][1]=-1;
            }
    }
    cout<<"\n";
    if(send[0][0]>=0 && send[0][1]>=0)
    {
    cout<<i<<j<<endl;
       addNote(i,j);
    }


}

}
void hoverMouse(int a, int b){
    int i,j;

    if(a>=127 && a<=571 && b>=141 && b<=586)
        {
    for(i=0;i<8;i++){
            if(b>=yaxis[i][0] && b<=yaxis[i][1])
            {
                break;
            }

    }
    for(j=0;j<8;j++)
    {
        if(a>=xaxis[j][0] && a<=xaxis[j][1])
        {
            break;
        }

    }
        hovstat[0][0]=i;
        hovstat[0][1]=j;

}
else{
    hovstat[0][0]=-10;
        hovstat[0][1]=-10;

}


}
void tester(){
int k,l;
    for( k=0;k<8;k++){
            for( l=0;l<8;l++){
                    state[k][l]=0;
            }
    }
}

void myMouse(int button, int stat, int x, int y) {


if(button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN){

    box(x,y);
    if(x>324 && x<373 && y>73 && y<123)
    {
        if(test)
        {
            test=false;
        }
        else
        {
            test=true;
        }
    }
}
if(button == GLUT_RIGHT_BUTTON && stat == GLUT_UP){
tester();
}

if(button == GLUT_LEFT_BUTTON && stat == GLUT_UP){

    if(x>665 && x<685 && y>13 && y<30)
    {
       if(info)
        {
            info=false;
        }
        else
        {
            info=true;
        }

    }
     if(x>444 && x<484 && y>78 && y<115)
    {
       if(night)
        {
            night=false;
        }
        else
        {
            night=true;
        }

    }
     if(x>503 && x<538 && y>82 && y<114)
    {  loopCnt++;
    }




}
}
void grid()
{
    float i,j;
glLineWidth(1);
glColor3f(0.8,0.8,0.8);

    for(i=-168.75;i<=168.75;i=i+56.25)
    {
        glBegin(GL_LINES);
        glVertex2f(i,210);
        glVertex2f(i,-240);
        glEnd();
    }
    for(j=153.75;j>=-183.75;j=j-56.25)
    {
        glBegin(GL_LINES);
        glVertex2f(-225,j);
        glVertex2f(225,j);
        glEnd();
    }

}
void raster(float x, float y, void *font,char *string);
void filledCircle(GLfloat x, GLfloat y, GLfloat radius);
void doneFunc()
{
    glClearColor(0.98,0.98,0.98,1);
    glColor3f(0.6,0.6,0.6);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    sprintf(title,"\t\t\t\t\t\t\tYour track is playing...    ");
    raster(-135,-170,GLUT_BITMAP_HELVETICA_18,title);

//glColor3f(0.7,0.7,0.7);
//filledCircle(-2,128,103);shadow
//glColor3f(1,1,1);
//glRectf(-210,-210,185,125);
//glColor3f(0,0,0);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glRectf(-200,-205,190,125);
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glColor3f(0.1,0.1,0.1);
filledCircle(-12,33,115);
glColor3f(0.1,0.1,0.1);
midPointCircleAlgo(116,-12,33,5);

//colourful rings
//glColor3f(252.0/255.0,116.0/255.0,78.0/255.0);
glColor3f(1,148.0/255.0,212.0/255.0);
midPointCircleAlgo(108,-12,33,3);

glColor3f(153.0/255.0,201.0/255.0,1);
midPointCircleAlgo(101,-12,33,2);



//symbol
glColor3f(0.98,0.98,0.98);
filledCircle(-58,-5,23.3);
glRectf(-49,0,-35,84);

filledCircle(16,7.65,23.3);
glRectf(25,12.65,39,86.65);
//thick
//filledCircle(16,107.65,23.3);
//glRectf(25,112.65,39,186.65);
//glRectf(-49,184,30,186.65);
//glColor3f(0.3,0.3,0.3);
//thin
filledCircle(16,7.65,23.3);
glRectf(25,22.65,39,86.65);

glRectf(-49,84,30,86.65);

glRectf(-49,64,30,66.65);
    glutSwapBuffers();

}

void playPause()
{
    if(test)
    {
        if(night)
        {
            glColor3f(1,1,1);

        }
        midPointCircleAlgo(25,0,250,2);
         if(night==false)
    {
        glColor3f(0.1,0.1,0.1);
    }
    else
    {
        glColor3f(1,1,1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    }
        glBegin(GL_TRIANGLES);
        glVertex2f(10,250);
        glVertex2f(-7,258);
        glVertex2f(-7,242);
        glEnd();


    }
    else
    {   int flag=0;
//        glBegin(GL_LINE_LOOP);
//        glVertex2f(-6,256);
//        glVertex2f(6,256);
//        glVertex2f(6,244);
//        glVertex2f(-6,244);
//        glEnd();
        for(int q=0;q<8;q++){
            for(int w=0;w<8;w++){
                    if(state[q][w]==1)
                        {
                            flag=1;
                            break;
                        }
            }

        }
        if(flag==1)
        {

        ofstream melfile ("example.mel");

        for(int q=0;q<8;q++){
            for(int w=0;w<8;w++){
                    melfile<<state[q][w]<<" ";
            }
            melfile<<"\n";
        }
        melfile.close();
        system("start ./spherepro.exe");
        doneFunc();

        system(pypath);
        system("taskkill /IM spherepro.exe");
        if (MessageBoxA(NULL,"Do you want to make new song?", "MELODY", MB_YESNO) == IDYES)
        {
            for(int q=0;q<8;q++){
            for(int w=0;w<8;w++){
                    state[q][w]=0;
            }

            }
        }
        }
             else
        {
           MessageBox(NULL,"Cannot play an empty track.","ERROR",MB_OK | MB_ICONEXCLAMATION);


        }

    }

        test=true;

    }
void infoBox()
{
//glColor3f(0.8,0.8,0.8);
glColor3f(1,148.0/255.0,212.0/255.0);

glBegin(GL_POLYGON);

glVertex2d(320,310);
glColor4f(153.0/255.0,201.0/255.0,1,0.7);
glVertex2d(320,230);
glColor4f(21.0/255.0,103.0/255.0,216.0/255.0,0.5);
glVertex2d(35,230);
glColor4f(196.0/255.0,153.0/255.0,1,0.7);
glVertex2d(35,310);
glEnd();
glColor3f(0,0,0.3);
char title[100] = {0};
sprintf(title," > Left click to add/remove notes.");
raster(40,290,GLUT_BITMAP_8_BY_13,title);
sprintf(title," > Right click to clear notes.");
raster(40,270,GLUT_BITMAP_8_BY_13,title);
sprintf(title," > Play button to play the melody.");
raster(40,250,GLUT_BITMAP_8_BY_13,title);
glColor3f(1,1,1);
sprintf(title," > Left click to add/remove notes.");
raster(39.5,291,GLUT_BITMAP_8_BY_13,title);
sprintf(title," > Right click to clear notes.");
raster(39.5,271,GLUT_BITMAP_8_BY_13,title);
sprintf(title," > Play button to play the melody.");
raster(39.5,251,GLUT_BITMAP_8_BY_13,title);



}
void looper_count(){
     if(night==false)
    {
        glColor3f(0.1,0.1,0.1);
    }
    else
    {
        glColor3f(1,1,1);
    }

    midPointCircleAlgo(18,171,250,3);

    char title[100] = {0};
    switch(loopCnt%3){
    case 0: sprintf(title,"2");
            raster(166,246,GLUT_BITMAP_9_BY_15,title);
            pypath="python ./mixer.py 2";
            break;

    case 1: sprintf(title,"4");
            raster(166,246,GLUT_BITMAP_9_BY_15,title);
            pypath="python ./mixer.py 4";
            break;
    case 2: sprintf(title,"10");
            raster(163,246,GLUT_BITMAP_9_BY_15,title);
            pypath="python ./mixer.py -1";
            break;
    }



}
void Info()
{
    glColor3f(0,0,0);
    midPointCircleAlgo(10,325,325,2);
    char title[100] = {0};
    sprintf(title,"?");
    raster(321,318,GLUT_BITMAP_HELVETICA_18,title);


}
void nightMode()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(night==false)
    {
        glColor3f(0.1,0.1,0.1);
    }
    else
    {
        glColor3f(1,1,1);
    }
        filledCircle(115,250,18);
     if(night==false)
    {
        glColor3f(1,1,1);
    }
    else
    {
        glColor3f(0.1,0.1,0.1);
    }

    filledCircle(116,250,10);
     if(night==false)
    {
        glColor3f(0.1,0.1,0.1);
    }
    else
    {
        glColor3f(1,1,1);
    }

    filledCircle(120,253,8);

     glColor3f(0.1,0.1,0.1);
    midPointCircleAlgo(18,115,250,3);


}

void strips(){
    for(int n=0;n<8;n++){
        for(int m=0;m<8;m++){
            if(state[n][m]==1){
                bolcol[n]=1;
                j=8;
            }

        }
    }

    glColor3f(0.2,0.2,0.2);
    if(bolcol[0]==1){
        glColor3f(1,148.0/255.0,212.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,188);
    glVertex2f(265,178);
    glVertex2f(299,178);
    glVertex2f(299,188);
    glEnd();


    glColor3f(0.2,0.2,0.2);
    if(bolcol[1]==1){
        glColor3f(196.0/255.0,153.0/255.0,1);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,132);
    glVertex2f(265,122);
    glVertex2f(299,122);
    glVertex2f(299,132);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    if(bolcol[2]==1){
        glColor3f(153.0/255.0,201.0/255.0,1);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,76);
    glVertex2f(265,66);
    glVertex2f(299,66);
    glVertex2f(299,76);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    if(bolcol[3]==1){
        glColor3f(153.0/255.0,1,177.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,20);
    glVertex2f(265,10);
    glVertex2f(299,10);
    glVertex2f(299,20);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    if(bolcol[4]==1){
        glColor3f(1,253.0/255.0,120.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,-36);
    glVertex2f(265,-46);
    glVertex2f(299,-46);
    glVertex2f(299,-36);
    glEnd();

   glColor3f(0.2,0.2,0.2);
    if(bolcol[5]==1){
       glColor3f(1,155.0/255.0,79.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,-92);
    glVertex2f(265,-102);
    glVertex2f(299,-102);
    glVertex2f(299,-92);
    glEnd();

    glColor3f(0.2,0.2,0.2);
    if(bolcol[6]==1){
        glColor3f(158.0/255.0,103.0/255.0,79.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,-148);
    glVertex2f(265,-158);
    glVertex2f(299,-158);
    glVertex2f(299,-148);
    glEnd();

   glColor3f(0.2,0.2,0.2);
    if(bolcol[7]==1){
        glColor3f(252.0/255.0,116.0/255.0,78.0/255.0);
    }
    glBegin(GL_POLYGON);
    glVertex2f(265,-204);
    glVertex2f(265,-214);
    glVertex2f(299,-214);
    glVertex2f(299,-204);
    glEnd();

}
void draw(){

//shadow big square
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
if(night==false)
{
glColor3f(0.8,0.8,0.8);
    }
else
    {
   glColor3f(0.4,0.4,0.4);
}

glBegin(GL_POLYGON);
glVertex2d(-295,295);
glVertex2d(305,295);
glVertex2d(305,-305);
glVertex2d(-295,-305);
glEnd();

//drumpad square
if(night==false)
    {
        glColor3f(1,1,1);
    }
    else
    {
        glColor3f(0.1,0.1,0.1);
    }

glBegin(GL_POLYGON);
glVertex2d(-300,300);
glVertex2d(300,300);
glVertex2d(300,-300);
glVertex2d(-300,-300);
glEnd();


//outline black
glLineWidth(0.5);
glColor3f(0.5,0.5,0.5);

glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glBegin(GL_POLYGON);
glVertex2d(-300,300);
glVertex2d(300,300);
glVertex2d(300,-300);
glVertex2d(-300,-300);
glEnd();



playPause();
nightMode();
looper_count();

grid();
Info();
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
if(night==false)
    {
        glColor3f(0.5,0.5,0.5);
    }
    else
    {
        glColor3f(1,1,1);
    }



char title[100] = {0};

sprintf(title,"KICK");
raster(-280,174,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"SNARE");
raster(-280,118,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"HATS");
raster(-280,62,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"CLAP");
raster(-280,6,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"TOMS");
raster(-280,-50,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"BELLS");
raster(-280,-106,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"SFX1");
raster(-280,-162,GLUT_BITMAP_9_BY_15,title);
sprintf(title,"SFX2");
raster(-280,-218,GLUT_BITMAP_9_BY_15,title);

if(night==false)
    {
        glColor3f(0.2,0.2,0.2);
    }
    else
    {
        glColor3f(1,1,1);
    }

sprintf(title,"MELODY ");
raster(-220,250,GLUT_BITMAP_TIMES_ROMAN_24,title);

if(night==false)
    {
        glColor3f(0.4,0.4,0.4);
    }
    else
    {
        glColor3f(1,1,1);
    }
sprintf(title,"T h e  D r u m  M a c h i n e ");
raster(-220,235,GLUT_BITMAP_HELVETICA_12,title);



glLineWidth(2);

    if(night==false)
    {
        glColor3f(0.4,0.4,0.4);
    }
    else
    {
        glColor3f(1,1,1);
    }

//drumpad outline
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
glBegin(GL_POLYGON);
glVertex2d(-225,210);
glVertex2d(225,210);
glVertex2d(225,-240);
glVertex2d(-225,-240);
glEnd();

glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//Info();
drawhover();
boxColor();
strips();
if(info)
    {
        infoBox();
    }
glutSwapBuffers();

}
void raster(float x, float y, void *font,char *string){
    char *c;
    glRasterPos2f(x,y);
    for(c=string; *c != '\0';c++){
        glutBitmapCharacter(font,*c);

    }
}
void filledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
void splash(int value){

glClearColor(0.95,0.95,0.95,1);
glClear(GL_COLOR_BUFFER_BIT);
char title[100] = {0};

glColor3f(1,1,1);
glRectf(-210,-210,185,125);

glColor3f(j,j,j);
filledCircle(-12,133,115);


glColor3f(1,148.0/255.0,212.0/255.0);
midPointCircleAlgo(108,-12,133,3);

glColor3f(153.0/255.0,201.0/255.0,1);
midPointCircleAlgo(101,-12,133,2);




//glColor3f(j,j,j);

//symbol
glColor3f(k,k,k);
filledCircle(-58,95,23.3);
glRectf(-49,100,-35,184);

filledCircle(16,107.65,23.3);
glRectf(25,112.65,39,186.65);
//thick

//thin
filledCircle(16,107.65,23.3);
glRectf(25,122.65,39,186.65);

glRectf(-49,184,30,186.65);

glRectf(-49,164,30,166.65);
glColor3f(0,0,0);
midPointCircleAlgo(116,-12,133,5);
//------------------------------------------


glColor3f(0.3,0.3,0.3);
sprintf(title,"M E L O D Y");
raster(-78,-30,GLUT_BITMAP_TIMES_ROMAN_24,title);
sprintf(title,"T h e  D r u m  M a c h i n e");
raster(-134,-50,GLUT_BITMAP_8_BY_13,title);
glColor3f(0.6,0.6,0.6);
sprintf(title,"Created By");
raster(-48,-109,GLUT_BITMAP_HELVETICA_12,title);
glColor3f(0.6,0.6,0.6);
sprintf(title,"Anushka Pai  and  Aditya Shenoy");//26
raster(-145,-130,GLUT_BITMAP_HELVETICA_18,title);

glColor4f(1,1,1,i);
if(i>0)
{
    i-=0.01;


}
else
    {
        finish=true;

    }

glutPostRedisplay();
glBegin(GL_POLYGON);
glVertex2d(-350,350);
glVertex2d(350,350);
glVertex2d(350,-350);
glVertex2d(-350,-350);
glEnd();

if(finish)
{
    if(swapper==false && j<1)
    { j+=0.05;
      k-=0.05;

    }
    else
    {
        swapper=true;
    }
    if(swapper && k<1)
    { k+=0.05;
      j-=0.05;
    }
    else
    {
        swapper=false;
        inc=inc+1;


    }


}
glutPostRedisplay();

glutSwapBuffers();
 if (inc>80)
    {
         waiter=2;
        make =true;
    }
}

void infopage(){
    glClearColor(0.95,0.95,0.95,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.1,0.1,0.1);
    sprintf(title,"CANARA ENGINEERING COLLEGE");
    raster(-150,300,GLUT_BITMAP_HELVETICA_18,title);

     glColor3f(0.1,0.1,0.1);
    sprintf(title,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    raster(-265,250,GLUT_BITMAP_HELVETICA_18,title);

     glColor3f(0.1,0.1,0.1);
    sprintf(title,"MINI PROJECT TITLE");
    raster(-90,180,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.3,0.3,0.3);
    sprintf(title,"Melody The Drum Machine");
    raster(-110,150,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.1,0.1,0.1);
    sprintf(title,"BY:");
    raster(-15,80,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.2,0.2,0.2);
    sprintf(title,"Anushka Pai 4CB17CS013");
    raster(-110,50,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.2,0.2,0.2);
    sprintf(title,"Aditya Shenoy 4CB17CS054");
    raster(-125,20,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.1,0.1,0.1);
    sprintf(title,"PROJECT GUIDE:");
    raster(-70,-50,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.2,0.2,0.2);
    sprintf(title,"Mr. Shatananda Bhat P");
    raster(-83,-80,GLUT_BITMAP_HELVETICA_18,title);

    glColor3f(0.6,0.1,0.9);
    sprintf(title,"<ENTER> to Continue..");
    raster(-90,-150,GLUT_BITMAP_HELVETICA_18,title);


    glutSwapBuffers();
    if(gotosplash>0){
        waiter=1;
    }
}

void display()
{
    if(waiter==0){
        infopage();
    }
    if(waiter==1)
        {
            splash(1);
        }
    if(waiter==2)
        {
            if(make){
                PlaySoundA("./soundpack/intro.wav",NULL,SND_SYNC);
                make=false;
            }
            if(night==false)
                {
                glClearColor(0.98,0.98,0.98,1);
                }
                else
                {
                glClearColor(0.9,0.9,0.9,1);
                }
            glClear(GL_COLOR_BUFFER_BIT);
            glutMouseFunc(myMouse);
            draw();
        }
}


void resize(int width, int height) {
    glutReshapeWindow( 700, 700);
}



void keyboard(unsigned char key,int x,int y){

    if(key == 13){
        gotosplash=1;
    }
}


void timer(int){

    glutPostRedisplay();
        glutTimerFunc(1000/60,timer,0);



}
int main(int argc, char **argv)
{

 glutInit(&argc, argv);
 glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

 glutInitWindowPosition(325,0);
 glutInitWindowSize(700,700);
 glutCreateWindow ("MELODY");
 glutReshapeFunc(resize);

 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable( GL_BLEND );

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-350,350,-350,350.0);
    glutDisplayFunc(display);
      glutTimerFunc(0,timer,0);
  glutKeyboardFunc(keyboard);

glutPassiveMotionFunc(hoverMouse);
 glutMainLoop();

 return 0;
}

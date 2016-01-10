/*#include <SDL/SDL.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void drawCube(float size)
{
        float difamb[] = {1.0,0.5,0.3,1.0};
        glBegin(GL_QUADS);
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
                // front face
                glNormal3f(0.0,0.0,1.0);
//              glColor3f(1.0,0.0,0.0);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,-size/2,size/2);
                glVertex3f(size/2,-size/2,size/2);
                // left face
                glNormal3f(-1.0,0.0,0.0);
//              glColor3f(0.0,1.0,0.0);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,-size/2,size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(-size/2,size/2,-size/2);
                // back face
                glNormal3f(0.0,0.0,-1.0);
//              glColor3f(0.0,0.0,1.0);
                glVertex3f(size/2,size/2,-size/2);
                glVertex3f(-size/2,size/2,-size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(size/2,-size/2,-size/2);
                // right face
                glNormal3f(1.0,0.0,0.0);
//              glColor3f(1.0,1.0,0.0);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(size/2,-size/2,size/2);
                glVertex3f(size/2,-size/2,-size/2);
                glVertex3f(size/2,size/2,-size/2);
                // top face
                glNormal3f(0.0,1.0,0.0);
//              glColor3f(1.0,0.0,1.0);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,-size/2);
                glVertex3f(size/2,size/2,-size/2);
                // bottom face
                glNormal3f(0.0,-1.0,0.0);
//              glColor3f(0.0,1.0,1.0);
                glVertex3f(size/2,-size/2,size/2);
                glVertex3f(-size/2,-size/2,size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
}

float angle = 0.0;
const int triangle = 1;

unsigned int loadTexture(const char* filename)
{
        SDL_Surface* img = SDL_LoadBMP(filename);
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(img);
        return id;
}

unsigned int tex;

void init()
{
        glClearColor(0.0,0.0,0.0,1.0);  //background color and alpha
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,640.0/480.0,1.0,500.0);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        tex = loadTexture("brick.bmp");
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0,0.0,-5.0);
        glRotatef(angle,1.0,1.0,1.0);   // angle, x-axis, y-axis, z-axis
        glBindTexture(GL_TEXTURE_2D, tex);
        glBegin(GL_QUADS);
                glTexCoord2f(0.0,2.0);
                glVertex3f(-2.0,2.0,0.0);
                glTexCoord2f(0.0,0.0);
                glVertex3f(-2.0,-2.0,0.0);
                glTexCoord2f(2.0,0.0);
                glVertex3f(2.0,-2.0,0.0);
                glTexCoord2f(2.0,2.0);
                glVertex3f(2.0,2.0,0.0);
        glEnd();
}

int main(int argc, char** argv)
{
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface *screen;
        screen = SDL_SetVideoMode(1024, 768, 32, SDL_SWSURFACE|SDL_OPENGL);
        bool running = true;
        const int FPS = 30;
        Uint32 start;
        SDL_Event event;
        init();
        while(running) {
                start = SDL_GetTicks();
                while(SDL_PollEvent(&event)) {
                        switch(event.type) {
                                case SDL_QUIT:
                                        running = false;
                                        break;
                                case SDL_KEYDOWN:
                                        switch(event.key.keysym.sym)
                                        {
                                                case SDLK_ESCAPE:
                                                        running = false;
                                                        break;
                                        }
                                        break;
                        }
                }

                display();
                SDL_GL_SwapBuffers();
                angle += 0.5;
                if(angle > 360)
                        angle -= 360;
                if(1000/FPS > SDL_GetTicks()-start)
                        SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
        }
        SDL_Quit();
        return 0;
}

*/
#include "input.h"
#include <QCoreApplication>
#include "labyrinth.h"

//GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL/SDL.h>
#include <SDL2/SDL.h>
//SOIL
#include <SOIL/SOIL.h>

// GLEW
#define GLEW_STATIC
#define GL_CLAMP_TO_EDGE 0x812F
#include <GL/glew.h>
#include <GL/glut.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>
#include <string>
#include <iostream>

void drawWall(int i, int j, char direction); // draws a bottom wall of ij cell
                                            //if direction == 'b', else - right wall
void display();

static int widthOfLabyrinth = 10;
static int heightOfLabyrinth = 10;
static Labyrinth lab(widthOfLabyrinth, heightOfLabyrinth);
input in;

void redrawTimer(int);
void move();
string solve();
//void key_callback(GLFWwindow *window, int key, int, int action, int);
//void mouse_callback(GLFWwindow *, double xpos, double ypos);
//void scrool_callback(GLFWwindow *, double, double yoffset);

void initialize();

//#include "camera.h"
//static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


typedef struct _AUX_RGBImageRec {
   GLint sizeX, sizeY;
   unsigned char *data;
} AUX_RGBImageRec;

GLfloat Trot;
GLfloat Qrot;

unsigned int loadTexture(const char* filename)
{
        SDL_Surface* img = SDL_LoadBMP(filename);
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(img);
        return id;
}

unsigned int tex;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    static bool first = true;


    if(first) {
        lab.generate();
        lab.print();
        first = false;
        //string solution = solve();
        //cout << solution;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Labyrinth");
    glutDisplayFunc(display);

    glutTimerFunc(50, redrawTimer, 0);

    initialize();

    glutMainLoop();

    return a.exec();
}

//void drawRectangle(x1,y1,x2,y2)
void drawWall(int i, int j, char direction) {
    static const int segment = 100; // width and height of each cell
    static int h = 100; // height of walls

    // 1/2 of width of walls
    int r,b; // for right and bottom walls

    // coordinates of the cell:
    // (seg*i;seg*j)        (seg*(i+1); seg*j)
    // (seg*i;seg*(j+1))    (seg*(i+1); seg*(j+1))

    int x1, x2, z1, z2; // coordinates of the wall's bottom
    if(direction == 'b') {
        //Bottom wall
        x1 = segment*i;             x2 = segment*(i+1);
        z1 = segment*(j+1);         z2 = segment*(j+1);
        b = 10;
        r = 0;
    }
    else {// direction == 'r'
        //Right wall
        x1 = segment*(i+1);     x2 = segment*(i+1);
        z1 = segment*j;         z2 = segment*(j+1);
        r = 10;
        b = 0;
    }
    glBegin(GL_QUADS);
                              //y=0 || y=h as far as Oy is height axis
    glNormal3f(0.0,-1.0,0.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x1-r, 0, z1-b);//bottom face
    glTexCoord2f(0.0,1.0);    glVertex3d(x1+r, 0, z1+b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x2+r, 0, z2+b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x2-r, 0, z2-b);

    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x2-r, 0, z2-b);//right face
    glTexCoord2f(0.0,1.0);    glVertex3d(x2+r, 0, z2+b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x2+r, h, z2+b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x2-r, h, z2-b);

    glNormal3f(-1.0,0.0,0.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x1-r, 0, z1-b);//left face
    glTexCoord2f(0.0,1.0);    glVertex3d(x1+r, 0, z1+b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x1+r, h, z1+b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x1-r, h, z1-b);

    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x1+r, h, z1+b);//back face
    glTexCoord2f(0.0,1.0);    glVertex3d(x1+r, 0, z1+b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x2+r, 0, z2+b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x2+r, h, z2+b);

    glNormal3f(0.0,0.0,1.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x1-r, h, z1-b);//front face
    glTexCoord2f(0.0,1.0);    glVertex3d(x1-r, 0, z1-b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x2-r, 0, z2-b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x2-r, h, z2-b);

    glNormal3f(0.0,1.0,0.0);
    glTexCoord2f(0.0,0.0);    glVertex3d(x1-r, h, z1-b);//up face
    glTexCoord2f(0.0,1.0);    glVertex3d(x1+r, h, z1+b);
    glTexCoord2f(1.0,1.0);    glVertex3d(x2+r, h, z2+b);
    glTexCoord2f(1.0,0.0);    glVertex3d(x2-r, h, z2-b);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glm::mat4 view, projection;
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(500,0,0);

    glColor3f(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,300,0);

    glColor3f(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(0,0,500);
    glColor3f(1,1,1);
    glEnd();

    /*static int eyex = 500;
    static int eyey = 400;
    static int eyez = 500;
    static int centerx = 300;
    static int centery = 0;
    static int centerz = 300;
    static int norx = -50;
    static int nory = 0;
    static int norz = -50;

    if(in.isKeyTapped(SDLK_l)){
        eyex -= 100;
        cout << "Ok";
    }

    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, norx, nory, norz);
*/

    glBindTexture(GL_TEXTURE_2D, tex);

    for(int i = 0; i < widthOfLabyrinth; i++)
        for(int j = 0; j < heightOfLabyrinth; j++) {
            if(lab.getBottomWalls(i,j) == 1) drawWall(i,j,'b');
            if(lab.getRightWalls(i,j) == 1) drawWall(i,j,'r');
        }
    for(int i = 1; i < widthOfLabyrinth; i++) {
        drawWall(i, -1,'b');
        drawWall(-1, i, 'r');
    }
    drawWall(-1, 0, 'r');
    glutSwapBuffers();
    glPopMatrix();

}

void redrawTimer(int) {
    move();
    glutPostRedisplay();
    glutTimerFunc(50, redrawTimer, 0);
}

void move() {

    //camera.keyboard(FORWARD, 300);

   }

string solve() {
    string path;
    int curi, curj;
    curi = curj = 0;
    bool solved = false;
    bool **isUsed;
    isUsed = new bool* [heightOfLabyrinth];
    for(int i = 0; i < heightOfLabyrinth; i++)
        isUsed[i] = new bool[widthOfLabyrinth];

    for(int i = 0; i < widthOfLabyrinth; i++)
        for(int j = 0; j < heightOfLabyrinth; j++)
            isUsed[i][j] = 0;
    //isUsed[0][0] = 1;
    //while(!solved) {
    for(int count = 0; count < 40; count++) {
        if((curi>0)&& !isUsed[curi-1][curj] && !lab.getRightWalls(curi-1, curj)){
            //goleft

            isUsed[curi][curj] = 1;
            curi--;
            path +='l';
        }
        else if((curj>0) && !isUsed[curi][curj-1] && !lab.getBottomWalls(curi, curj-1)){
            //goup;

            isUsed[curi][curj] = 1;
            curj--;
             path +='u';
        }
        else if(!isUsed[curi][curj] && !lab.getRightWalls(curi, curj)){
            //goright;

            isUsed[curi][curj] = 1;
            curi++;
             path +='r';

        }
        else if(!isUsed[curi][curj] && !lab.getBottomWalls(curi, curj)){
            //godown;

            isUsed[curi][curj] = 1;
            curj++;
             path +='d';
        }
        else{//deadlock
            //goback;
            char last = path[path.size()-1];
            path.erase(path.begin()+path.size()-1);
            switch(last) {
                case 'r': curi--;break;
                case 'l': curi++;break;
                case 'u': curj++;break;
                case 'd': curj--;break;
            }
        }
    }
    return path;
}

void initialize() {
    glClearColor(0, 0, 0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);//?

    glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
    float dif[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    float amb[] = {0.2, 0.2, 0.2, 1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    float pos[] = {200, 200, 200, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);


//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(160, 1, 50, 0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(500, 400, 500, 300, 0, 300, -50, 0, -50);


//gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, norx, nory, norz);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    tex = loadTexture("brick.bmp");
}


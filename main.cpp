/*
Name: Bardan Phuyel
Student ID: 901265308
Email: bvp5359@psu.eud
Status:
1. This code can create multiple shapes, and color them in using R,G, or T.
2. I made the background black, the reason for that is that it looks better in my oppnion
3. To use the program you can left click anywhere on the window and set a point, then after you create multiple points, you can
 right clcik to finish the shpae, which will fill it in with white. The most recent shape will  be over the previous made shapes
4. you cnanot see how your current shape looks like, you cna only see the finsihed shapes
5. Pressing R will color the last finished shapes to Red, Pressing G will color the last finished shape to Gree, and Pressing T will color
 the last finished shape to white
 6. Added Bonus: Pressing 'd' will move the shape down by 10px each time
*/

#include <GLUT/glut.h>
#include <iostream>
using namespace std;

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;
// each shape we are drawing can have up to 100 vetices/dots
int currentShape[100][2];
// track how many dots/vetices for the current the shape
int currentDotTotal = 0;  // This tells us how many dots we have so far.
// total number of shapes we can have is 100, wtih each shape having 100 points
int allShapes[100][100][2];
// each finished shape has this many vetices/dots
int shapeDotTotal[100];
//track total number of shapes, incements eveytime we finish a shape
int totalShapes = 0;
// colors for the shapes, 100 for total number of shapes
// 0 = white, 1 = red, 2= blue
int shapeColors[100];


void mouse(int button, int state, int x, int y) {
    //opengl y cord is inverted
    y = WINDOW_HEIGHT - y;

    // after you left click, it addds a avetice at the location
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        currentShape[currentDotTotal][0] = x;
        currentShape[currentDotTotal][1] = y;
        currentDotTotal++;
    }
    // after the right click button is clicked, we finish the current shape
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // this finishes the current shape and moves it to the arry of finsihed shapes
        for (int i = 0; i < currentDotTotal; ++i) {
            allShapes[totalShapes][i][0] = currentShape[i][0];
            allShapes[totalShapes][i][1] = currentShape[i][1];
        }
        // updates how many vetices are in the current shape.
        shapeDotTotal[totalShapes] = currentDotTotal;
        totalShapes++;
        
        // resets the current shape vertices ammount
        currentDotTotal = 0;
    }
    glutPostRedisplay();
}

// change color the last shape based on the color
void keyboard(unsigned char key, int x, int y) {
    // pressing R makes the last shape red
    if (key == 'R' || key == 'r') {
        shapeColors[totalShapes - 1] = 1;
    }
    // pressing G makes the last shape green
    else if (key == 'G' || key == 'g') {
        shapeColors[totalShapes - 1] = 2;
    }
    // pressing T makes the last shape white or transparent
    else if (key == 'T' || key == 't') {
        shapeColors[totalShapes - 1] = 0;
    }
    //pressing down the 'd' moves the shape down by 10px
    else if (key == 'D' || key == 'd') {
            if (totalShapes > 0) {
                for (int i = 0; i < shapeDotTotal[totalShapes - 1]; ++i) {
                    allShapes[totalShapes - 1][i][1] -= 10; // Move down by 10 units
                }
            }
        }
    glutPostRedisplay();
}
                 
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < totalShapes; ++i){
        // Pick the color for this shape.
        if (shapeColors[i] == 1){
            glColor3f(1.0, 0.0, 0.0);
        } else if (shapeColors[i] == 2){
            glColor3f(0.0, 1.0, 0.0);
        } else{
            glColor3f(1.0, 1.0, 1.0);
        } 
        // this sets the color to white and draws a polygon for each finished shape
        glBegin(GL_POLYGON);
        for (int j = 0; j < shapeDotTotal[i]; ++j){
            glVertex2i(allShapes[i][j][0], allShapes[i][j][1]);
        }
        glEnd();
    }
    glutSwapBuffers();
}

void Init(void){
    //chnaged line colors to white
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(5.0);
    glLogicOp(GL_XOR);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Creation using mouse");
    Init();
    glutMouseFunc(mouse);
    //could not figure out the glutMotionFunc or reShape function
    //glutMotionFunc(OnMouseMove);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    //glutReshapeFunc(OnReshape);
    glutMainLoop();
    
    return 0;
}

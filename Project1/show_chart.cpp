#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;



string dataFileName;


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //  gluOrtho2D(0,500,0,500);
    glOrtho(0, 500, 0, 500, -1, 1);
}


bool tryOpenFile() {
    ifstream dataFile;
    printf("Finding data file... \n");
    dataFile.open (dataFileName.c_str(), ios::in);
    if(dataFile.is_open()) {
        dataFile.close();
        return true;
    }
    return false;
}

void set_color(vector<string> splitLine) {
    float R = atof(splitLine.at(1).c_str());
    float G = atof(splitLine.at(2).c_str());
    float B = atof(splitLine.at(3).c_str());
    glColor3f(R, G, B);
    glFlush();
}

void draw_line(vector<string> splitLine) {
    float widthLine = atof(splitLine.at(1).c_str());
    float x1Line = atof(splitLine.at(2).c_str());
    float y1Line = atof(splitLine.at(3).c_str());
    float x2Line = atof(splitLine.at(4).c_str());
    float y2Line = atof(splitLine.at(5).c_str());
    glLineWidth(widthLine);
    glBegin(GL_LINES);
    glVertex3f(x1Line, y1Line, 0);
    glVertex3f(x2Line, y2Line, 0);
    glEnd();
    glFlush();
}

void draw_point(vector<string> splitLine) {
    float sizePoint = atof(splitLine.at(1).c_str());
    float xPoint = atof(splitLine.at(2).c_str());
    float yPoint = atof(splitLine.at(3).c_str());
    glPointSize(sizePoint);
    glBegin(GL_POINTS);
    glVertex3f(xPoint, yPoint, 0);
    glEnd();
    glFlush();
}

void draw_polygon(vector<string> splitLine) {
    float x = 0.0;
    float y = 0.0;
    int count = atoi(splitLine.at(1).c_str());
    int itr = 0;
    glBegin(GL_POLYGON);
    while(count > 0) {
        x = atof(splitLine.at(itr + 2).c_str());
        y = atof(splitLine.at(itr + 3).c_str());
        glVertex3f(x, y, 0);
        itr+=2;
        count--;
    }
    glEnd();
    glFlush();
}

void get_data(){
    glClear(GL_COLOR_BUFFER_BIT);
    ifstream dataFile;
    string line;
    vector<string> splitLine;
    dataFile.open (dataFileName.c_str(), ios::in);

    //loop through file
    while (getline(dataFile, line)) {
        splitLine.clear();

        // tokenize
        char cstr[line.size() + 1];
        strcpy(cstr, line.c_str());
        char *token = strtok(cstr, " ");

        //add tokens to string vector
        while(token != NULL) {
            splitLine.push_back(token);
            token = strtok(NULL, " ");
        }
        if (find(splitLine.begin(), splitLine.end(), "draw_line") != splitLine.end()) {
            draw_line(splitLine);
        }
        else if(find(splitLine.begin(), splitLine.end(), "set_color") != splitLine.end()) {
            set_color(splitLine);
        }
        else if(find(splitLine.begin(), splitLine.end(), "draw_point") != splitLine.end()){
            draw_point(splitLine);
        }
        else if(find(splitLine.begin(), splitLine.end(), "draw_polygon") != splitLine.end()){
            draw_polygon(splitLine);
        }

    }
    dataFile.close();
}

void test() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0, 200);
    glVertex2f(200, 0);
    glVertex2f(200, 200);
    glEnd();
}
int main(int argc, char** argv) {

    printf("Enter name of txt file to display. Format: {x dimension}_{y dimension}_{graph type} ");
    cin >> dataFileName;
    dataFileName = dataFileName.append(".txt");

    if(tryOpenFile()) {
        vector<string> dimensions;

        char cstr[dataFileName.size() + 1];
        strcpy(cstr, dataFileName.c_str());
        char *token = strtok(cstr, "_");

        //add tokens to string vector
        while(token != NULL) {
            dimensions.push_back(token);
            token = strtok(NULL, " ");
        }

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB);
        glutInitWindowSize(atoi(dimensions.at(0).c_str()),atoi(dimensions.at(1).c_str()));
        glutInitWindowPosition(250,250);
        glutCreateWindow(dataFileName.c_str());
        init();
        glutDisplayFunc(get_data);
        glutMainLoop();

    }
    else {
        printf("%s file not found. Please add a %s file.", dataFileName.c_str(), dataFileName.c_str());
        return 0;
    }

    return 0;
}

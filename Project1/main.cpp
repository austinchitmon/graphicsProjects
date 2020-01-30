#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

//Graphics Project 1
//Create By: Austin Chitmon
// Description: First part of graphics project, driver for main program

vector<int> xCoordsForPoints;


string toString(int a) {
    stringstream ss;
    ss << a;
    return ss.str() + " ";
}
vector<int> get_data(string dataFileName){
    ifstream dataFile;
    string line;
    vector<int> dataValues;
    printf("Data file found, reading data...\n");
    dataFile.open (dataFileName.c_str(), ios::in);

    //loop through file
    while (getline(dataFile, line) ) {

        //convert and tokenize
        char cstr[line.size() + 1];
        strcpy(cstr, line.c_str());
        char *token = strtok(cstr, " ");

        //add tokens to int vector
        while(token != NULL) {
            dataValues.push_back(atoi(token));
            token = strtok(NULL, " ");
        }
    }


    dataFile.close();
    return dataValues;
}

int getYValOrigin(int height) {
    return height * .02 + height * .02;
}
int getYValEnd(int height) {
    return height * .98 - height * .02;
}
vector<int> getYCoordsForPoints(vector<int> dataValues, int yValEnd, int yValORIGIN) {
    vector<int> yCoordsForPoints;
    // int start = *min_element(dataValues.begin(), dataValues.end());
    int start = 0;
    int end = *max_element(dataValues.begin(), dataValues.end());
    for(int i = 0; i < dataValues.size(); i++) {
        yCoordsForPoints.push_back ((((dataValues.at(i) - start) * (yValEnd - yValORIGIN) ) / (end - start)) + yValORIGIN);
    }
    return yCoordsForPoints;
}
bool tryOpenFile(string dataFileName) {
    ifstream dataFile;
    printf("Finding data file... \n");
    dataFile.open (dataFileName.c_str(), ios::in);
    if(dataFile.is_open()) {
        dataFile.close();
        return true;
    }
    return false;
}

string createFileName(int height, int width, string type) {
    ostringstream os ;
    os << height ;
    string h = os.str();
    os.str("");
    os << width;
    string w = os.str();
    return h + "_" + w + "_" + type +".txt";
}

void writeToOutputFile( vector<string> commands, string fileName) {
    ofstream file;
    file.open (fileName.c_str());
    for(int i = 0; i < commands.size(); i++) {
        file << commands.at(i) + "\n";
    }
    printf("Successfully wrote to file: %s\n", fileName.c_str());
    file.close();
}

void column_chart( vector<string> commands, vector<int> dataValues, int height, int width) {
    printf("Column chart called... \n");
    commands.push_back("set_color 0.0 0.8 0.3");
    const string DRAW_POLYGON = "draw_polygon ";
    const string SIDES = "4 ";

    int yValORIGIN = getYValOrigin(height);
    int yValEnd = getYValEnd(height);
    vector<int> yCoordsForPoints = getYCoordsForPoints(dataValues, yValEnd, yValORIGIN);

    // width of column: half distance between any 2 x coords.
    // so, half of width will give width on either side of base point
    // so, x - (width /2) = starting x, x + (width / 2) = ending x for the rectangle.
    int columnWidth = xCoordsForPoints.at(1) - xCoordsForPoints.at(0);

    for(int i = 0; i < xCoordsForPoints.size(); i++) {
        commands.push_back(
                DRAW_POLYGON+SIDES+
                toString(xCoordsForPoints.at(i) - (columnWidth / 4)) + toString(yCoordsForPoints.at(i))+
                toString(xCoordsForPoints.at(i) + (columnWidth / 4)) + toString(yCoordsForPoints.at(i))+
                toString(xCoordsForPoints.at(i) + (columnWidth / 4)) + toString(yValORIGIN + 1)+
                toString(xCoordsForPoints.at(i) - (columnWidth / 4)) + toString(yValORIGIN + 1)
                );
    }


    string fileName = createFileName(height, width, "column");
    writeToOutputFile( commands, fileName );
}

void point_chart( vector<string> commands, vector<int> dataValues, int height, int width) {
    printf("Point chart called... \n");
    commands.push_back("set_color 0.5 1.0 0.5");
    const string DRAW_POINT = "draw_point ";
    const string POINT_SIZE = "6 ";

    // xCoordsForPoints as global

    int yValORIGIN = getYValOrigin(height);
    int yValEnd = getYValEnd(height);
    vector<int> yCoordsForPoints = getYCoordsForPoints(dataValues, yValEnd, yValORIGIN);

    for(int i = 0; i < xCoordsForPoints.size(); i++) {
        commands.push_back(DRAW_POINT+POINT_SIZE+toString(xCoordsForPoints.at(i)) + toString(yCoordsForPoints.at(i)));
    }
    string fileName = createFileName(height, width,"point");
    writeToOutputFile( commands, fileName );
}

void line_chart(  vector<string> commands, vector<int> dataValues, int height, int width) {
    printf("Line chart called... \n");
    commands.push_back("set_color 0.5 0.25 0.5");
    const string DRAW_LINE = "draw_line ";
    const string LINE_SIZE = "4 ";

    int yValORIGIN = getYValOrigin(height);
    int yValEnd = getYValEnd(height);
    vector<int> yCoordsForPoints = getYCoordsForPoints(dataValues, yValEnd, yValORIGIN);

    for(int i = 0; i < xCoordsForPoints.size() - 1; i++) {
        commands.push_back(DRAW_LINE+LINE_SIZE+toString(xCoordsForPoints.at(i)) + toString(yCoordsForPoints.at(i)) + toString(xCoordsForPoints.at(i + 1)) + toString(yCoordsForPoints.at(i + 1)));
    }
    string fileName = createFileName(height, width, "line");
    writeToOutputFile(commands, fileName );
}

void area_chart(  vector<string> commands, vector<int> dataValues, int height, int width) {
    printf("Area chart called... \n");
    commands.push_back("set_color .25 0.5 1.0");
    const string DRAW_POLYGON = "draw_polygon ";
    const string SIDES = "4 ";

    int yValORIGIN = getYValOrigin(height);
    int yValEnd = getYValEnd(height);
    vector<int> yCoordsForPoints = getYCoordsForPoints(dataValues, yValEnd, yValORIGIN);

    for(int i = 0; i < xCoordsForPoints.size() - 1; i++) {
        commands.push_back(
                DRAW_POLYGON+SIDES+
                toString(xCoordsForPoints.at(i)) + toString(yValORIGIN + 1) + // (x, y = 0)
                toString(xCoordsForPoints.at(i)) + toString(yCoordsForPoints.at(i)) + // (x,y)
                toString(xCoordsForPoints.at(i + 1)) + toString(yCoordsForPoints.at(i + 1)) + //(x+1, y+1)
                toString(xCoordsForPoints.at(i + 1)) + toString(yValORIGIN + 1)); // (x+1, y = 0)
    }



    string fileName = createFileName(height, width, "area");
    writeToOutputFile(commands, fileName );
}

vector<string> create_base_chart(int height, int width, vector<int> dataValues) {
    vector<string> baseChartCommands;
    const string LINE_WIDTH = "1 ";
    const string DRAW_LINE = "draw_line ";
    int NUM_LINES_Y = 10;
    int NUM_LINES_X = dataValues.size();

    printf("Create base chart called... \n");
    baseChartCommands.push_back("set_color 1.0 1.0 1.0");

    // find chart boundries
    int chartBoundX = width * .02;
    int chartBoundY = height * .02;
    int chartMaxX = width * .98;
    int chartMaxY = height * .98;

    // draw x lines
    int yValORIGIN = chartBoundY + chartBoundY;
    int yValEnd = chartMaxY - chartBoundY;
    int iteratorY = (yValEnd - yValORIGIN) / NUM_LINES_Y;

    //draw first horiz line
    baseChartCommands.push_back(DRAW_LINE+LINE_WIDTH+ toString(chartBoundX) + toString(yValORIGIN) + toString(chartMaxX) + toString(yValORIGIN));
    //draw middle 9 lines
    int yVal = yValORIGIN + iteratorY;
    for(int i = 0; i < 10; i++) {
        baseChartCommands.push_back(DRAW_LINE+LINE_WIDTH+toString(chartBoundX)+toString(yVal)+toString(chartMaxX)+toString(yVal));
        yVal = yVal + iteratorY;
    }

    //draw first vertical line
    int xValORIGIN = chartBoundX + chartBoundX;
    int xValEnd = chartMaxX - chartBoundX;
    int iteratorX = (xValEnd - xValORIGIN) / NUM_LINES_X;
    baseChartCommands.push_back(DRAW_LINE+LINE_WIDTH+ toString(xValORIGIN) + toString(chartBoundY) + toString(xValORIGIN) + toString(chartMaxY));

    //draw tick marks
    int xVal = yValORIGIN + iteratorX;
    for(int i = 0; i < dataValues.size(); i++) {
        baseChartCommands.push_back(DRAW_LINE+LINE_WIDTH+toString(xVal)+toString(chartBoundY)+toString(xVal)+toString(yValORIGIN));
        xCoordsForPoints.push_back(xVal);
        xVal = xVal + iteratorX;
    }

    return baseChartCommands;
}

int main() {
    // prime selection variable for type of chart
    int selection = 0;
    string dataFileName;
    int height = 0;
    int width = 0;
    bool alive = true;
    vector<int> dataValues;
    vector<string> baseChartCommands;

    printf("Enter name of text file to pull data from (omit .txt extension): ");
    cin >> dataFileName;
    dataFileName = dataFileName.append(".txt");

    if(tryOpenFile(dataFileName)) {
        dataValues = get_data(dataFileName);
        printf("Data Values: ");
        for(int i = 0; i < dataValues.size(); i++) {
            printf("%d ", dataValues.at(i));
        }
        printf("\n");

    }
    else {
        printf("%s file not found. Please add a %s file.", dataFileName.c_str(), dataFileName.c_str());
        return 0;
    }


    // prompt user for chart they want to display & dimensions
    while(alive) {
        height = 0;
        width = 0;
        selection = 0;
        baseChartCommands.clear();
        xCoordsForPoints.clear();




        printf("What type of chart would you like to generate commands for? \n");
        printf("%d. Column Chart \n"
               "%d. Point Chart \n"
               "%d. Line Chart \n"
               "%d. Area Chart \n"
               "%d. Quit \n",
               1, 2, 3, 4, 5);

        // check between 1 and 5
        while (selection > 5 || selection < 1) {
            printf("Enter your integer value: ");
            cin >> selection;
        }

        // if not quit command, get base chart commands
        if(selection > 0 && selection < 5) {

            do {
                printf("Enter width of chart (max: 1500): ");
                cin >> width;
            }while(width <= 0 || width > 1500 || cin.fail());

            do {
                printf("Enter height of chart (max: 1500): ");
                cin >> height;
            }while(height <= 0 || height > 1500 || cin.fail());

            baseChartCommands = create_base_chart(height, width, dataValues);

        }
        // call chart functions
        switch (selection) {
            case 1:
                column_chart(baseChartCommands, dataValues, height, width);
                break;
            case 2:
                point_chart(baseChartCommands, dataValues, height, width);
                break;
            case 3:
                line_chart(baseChartCommands, dataValues, height, width);
                break;
            case 4:
                area_chart(baseChartCommands, dataValues, height, width);
                break;
            case 5:
                alive = false;
                printf("Closing application...\n");
                break;
            default:
                printf("Default hit \n");
        }

    }
    return 0;
}

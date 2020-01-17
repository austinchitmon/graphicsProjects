#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

//Graphics Project 1
//Create By: Austin Chitmon
// Description: First part of graphics project, driver for main program

//globals to shorthand printf function
string dl = "draw_line";
string dn = "draw_number";
string ds = "draw_string";
string dp = "draw_polygon";


void column_chart(int data[], int height, int width) {
    printf("Column chart called... \n");


}

void point_chart(int data[], int height, int width) {
    printf("Point chart called... \n");


}

void line_chart(int data[], int height, int width) {
    printf("Line chart called... \n");


}

void area_chart(int data[], int height, int width) {
    printf("Area chart called... \n");
}

void create_base_chart(int data[], int height, int width) {
    printf("Create base chart called... \n");
    int sizeHalf = sizeof(data);
    int xVals[sizeHalf];
    int yVals[sizeHalf];
    int scalex, scaley = 0;


    //seperate x and y values from data array
    for( int i,j = 0; i < sizeHalf; i++) {
        xVals[i] = data[j];
        j+=1;
        yVals[i] = data[j];
        j+=1;
    }

    // determine max y value
    int* maxy = max_element(yVals, yVals + sizeHalf);
    printf("Max y: %d \n", *maxy);

    // determine max x value
    int* maxx = max_element(xVals, xVals + sizeHalf);
    printf("Max x: %d \n", *maxx);

    //identify scale factors
    scaley = height / *maxx;
    scalex = width / *maxy;

    // draw axises

    // draw tic marks on x axis

    //draw numbers between tic marks

    // draw horizontal lines on y axis
}





int main() {
    // prime selection variable for type of chart
    int selection = 0;
    int height = 500;
    int width = 500;
    int data[] = {1, 11,
                2, 13,
                3, 16,
                4, 19,
                5, 33,
                6, 45,
                7, 71,
                8, 86};

    // prompt user for chart they want to display
    printf("What type of chart would you like to display? \n");
    printf("%d. Column Chart \n"
           "%d. Point Chart \n"
           "%d. Line Chart \n"
           "%d. Area Chart \n",
            1,2,3,4);

    // check between 1 and 4
    while(selection > 4 || selection < 1) {
        printf("Enter your integer value:");
        cin >> selection;
    }

    // create base chart
    printf("Calling create base chart... \n");
    create_base_chart(data, height, width);

    // call chart specific function
    switch(selection) {
        case 1:
            column_chart(data, height, width);
            break;
        case 2:
            point_chart(data, height, width);
            break;
        case 3:
            line_chart(data, height, width);
            break;
        case 4:
            area_chart(data, height, width);
            break;
        default:
            printf("Default hit \n");
    }


    return 0;
}

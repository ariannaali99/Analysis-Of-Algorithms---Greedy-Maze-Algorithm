#include "IOFunctions.h"
#include <iostream>
#include <fstream>

void IOFunctions::readFile() {
    string fileName = "C:\\Users\\Arian\\Documents\\Project 3\\input.txt";
    fstream in(fileName);

    if(in.is_open()) {
        //The first value xs the number of rows in the maze
        in >> rows;

        //The second value is the number of columns in the maze
        in >> columns;

        //The third value is the row that Tarzan starts at
        in >> startAtX;

        //The fourth value is the column that Tarzan starts at
        in >> startAtY;
        cout << "Starting position: " << startAtX << ", " << startAtY << endl;

        //Now, we need to fill in the map
        vector<string> line;
        string temp;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                in >> temp;
                line.push_back(temp);
            }
            maze.push_back(line);
            line.clear();
        }
    }
    else {
        cout << "Error opening file." << endl;
    }
    pathsToJojo = 0;
    findingJojo((startAtX-1), (startAtY-1));
    //printGraph();
    //getPath();
   //printPath();
}

void IOFunctions::findingJojo(int x, int y) {

    for(int i = 0; i < 1000; i++) {
        walk[i] = "\0";
    }

    if(maze[x][y].compare("X") == 0) {
        cout << "Invalid co-ordinates" << endl;
    }
    else if(maze[x][y].compare("J") == 0) {
        cout << "Jojo found already" << endl;
    }
    else {
        while(x >= 0 || y >= 0 || x < rows || y < columns) {
            cout << "Traversing Maze" << endl;

        }
        cout << "Finding Jojo Rec" << endl;
        findingJojoRec(x, y, 0);
    }
}

void IOFunctions::findingJojoRec(int x, int y, int n) {

    if(x < 0 || x > rows) {
        cout << x << endl;
        cout << "Invalid x" << endl;
        return;
    }
    if (y < 0 || y > columns) {
        cout << y << endl;
        cout << "Invalid y" << endl;
        return;
    }

    char a = (char)x;
    char b = (char)y;
    string temp;
    temp.clear();
    temp += a;
    temp += ",";
    temp += b;

    if(isRepeated(temp) == true) {
        cout << "isRepeated" << endl;
        return;
    }
    points.push_back(temp);

    if(maze[x][y].compare("X") == 0) {
        cout << "No vines here"<< endl;
        walk[(2*n)+1] = "X";
        walk[(2*n)+2] = "X";
        return;
    }
    else if(maze[x][y].compare("J") == 0){
        cout << "Jojo has been found" << endl;
        pathsToJojo++;
        walk[n] += "J";
        return;
    }
    else if(maze[x][y].compare("N") == 0) {
        walk[(2*n)+1] = "N-3";
        walk[(2*n)+2] = "N-4";
        cout << "N-3" << endl;
        findingJojoRec(x-3, y, (2*n)+1);
        cout << "N-4" << endl;
        findingJojoRec(x-4, y, (2*n)+2);
    }
    else if(maze[x][y].compare("S") == 0) {
        walk[(2*n)+1] = "S-3";
        walk[(2*n)+2] = "S-4";
        cout << "S-3" << endl;
        findingJojoRec(x+3, y, (2*n)+1);
        cout << "S-4" << endl;
        findingJojoRec(x+4, y, (2*n)+2);
    }
    else if(maze[x][y].compare("E") == 0) {
        walk[(2*n)+1] = "E-3";
        walk[(2*n)+2] = "E-4";
        cout << "E-3" << endl;
        findingJojoRec(x, y+3, (2*n)+1);
        cout << "E-4" << endl;
        findingJojoRec(x, y+4, (2*n)+2);
    }
    else if(maze[x][y].compare("W") == 0) {
        walk[(2*n)+1] = "W-3";
        walk[(2*n)+2] = "W-4";
        cout << "W-3" << endl;
        findingJojoRec(x, y-3, (2*n)+1);
        cout << "W-4" << endl;
        findingJojoRec(x, y-4, (2*n)+2);
    }
    else {
        return;
    }
}

void IOFunctions::printGraph() {
    cout << "Printing Graph" << endl;
    for(int i = 0; i < 1000; i++) {
        if(walk[i] != "\0") {
            cout << walk[i] << " ";
        }
    }
    cout << endl;
}

bool IOFunctions::isRepeated(string param) {
    int count = 0;
    for(int i = 0; i < points.size();i++) {
        if(points[i].compare(param)==0) {
            count++;
        }
        if(count > 1) {
            return true;
        }
    }
    return false;
}

void IOFunctions::getPath() {
    cout << "Getting Path" << endl;
    int n =0;
    for(int i = 0; i < 1000; i++) {
        if(walk[i].compare("\0") != 0) {
            cout << i << " " << walk[i] << endl;
            for(int j = 0; j < walk[i].length();j++) {
                if(walk[i].at(j) == 'J') {
                    cout << i << endl;
                    n = i;
                    break;
                }
            }
        }
    }

    while(n>=0) {
        string temp;
        for(int i = 0; i < walk[n].length();i++) {
            if(walk[n].at(i) == 'J') {
                break;
            }
            else {
                temp += walk[n].at(i);
            }
        }
        path.push(temp);
        cout << temp << endl;
        if(n%2==0) {
            //then this is the right child of the node
            n = n-2;
            n = n/2;
        }
        else if(n%2 ==1) {
            n = n -1;
            n = n/2;
        }
    }
}

void IOFunctions::printPath() {
    cout << "Printing Path" << endl;
    stack<string> temp = path;
    for(int i = 0; i < path.size(); i++) {
        if(i = (path.size()-1)) {
            cout << temp.top() << endl;
        }
        else {
            cout << temp.top() << " " ;
            temp.pop();
        }
    }
}
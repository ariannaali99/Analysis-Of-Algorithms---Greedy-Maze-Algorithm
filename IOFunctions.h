#ifndef PROJECT_3_IOFUNCTIONS_H
#define PROJECT_3_IOFUNCTIONS_H

#include <vector>
#include <string>
#include <array>
#include <stack>
#include<bits/stdc++.h>

using namespace std;
class IOFunctions {
protected:
    vector<vector<string>> maze;
    vector<string> traversals;
    string walk[1000];
    stack<string> path;
    int rows;
    int columns;
    int startAtX;
    int startAtY;
    int pathsToJojo;

public:
    void readFile();
    void findingJojo(int x, int y);
    void findingJojoRec(int x, int y, int n);
    void printGraph();
    bool isRepeated(string param);
    void getPath();
    void printPath();
    //void writeFile();
};


#endif //PROJECT_3_IOFUNCTIONS_H

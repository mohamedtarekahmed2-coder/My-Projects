#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<float> grades;
    float grade;
    
    ifstream inFile("degrees2025.txt");
    
    while (inFile >> grade) {
        if (grade < 320) {
            grades.push_back(grade);
        }
    }
    inFile.close();
    ofstream outFile("degrees2025.txt");
    

    for (float g : grades) {
        outFile << g << "\n";
    }
    outFile.close();

    return 0;
}
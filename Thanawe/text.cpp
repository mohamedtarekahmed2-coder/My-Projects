#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    int percentagesArray[21] = {0};
    
    ifstream file("degrees2025.txt");
    
    if (!file) {
        cout << "Error: Cannot open degrees.txt" << endl;
        return 1;
    }
    
    float degree;
    while (file >> degree) {
        if (degree >= 0 && degree <= 320) {
            float percent = (degree / 320.0f) * 100.0f;
            int index = (int)percent / 5;
            if (index > 20) {
                index = 20;
            }
            
            percentagesArray[index]++;
        }
    }
    
    file.close(); 
    
    cout << "Percentage Distribution (Every 5%):" << endl;
    cout << "------------------------------------------------" << endl;
    
    int scale = 1000; 
    cout << "Note: Each star (*) represents approx " << scale << " students." << endl;
    cout << "------------------------------------------------" << endl;
    
    for (int i = 0; i < 21; i++) {
        int startRange = i * 5;
        int endRange = (i == 20) ? 100 : (startRange + 4);
        cout << setw(3) << left << startRange << " - " 
             << setw(3) << left << endRange << " % | "
             << setw(7) << left << percentagesArray[i] << " : ";
        
        int starsCount = percentagesArray[i] / scale;
        
        for (int j = 0; j < starsCount; j++) {
            cout << "*";
        }
        cout << endl;
    }
    
    return 0;
}
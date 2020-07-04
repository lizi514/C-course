#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Building {
public:
    int height, left, right;
    Building(int inputHeight, int inputLeft, int inputRight){
        height = inputHeight; left = inputLeft; right = inputRight;
    }
};


int main()
{
    
    int c_rows = 28, c_columns = 83;
    vector<vector<double> > city;
    vector<double> row1(c_columns);
    city.insert(city.begin(), c_rows, row1);

    ifstream fin("skyline.in");
    if (! fin.is_open()) {
        cout << "Error opening the file skyline.in." << endl;
        return -1;
    }
    string str;
    vector<Building> buildings;
    int inputLeft, inputHeight1, inputRight, inputHeight2;
    while( getline(fin, str)){
        istringstream iss(str);
        if (str.size() > 0) {
            iss >> inputLeft >> inputHeight1 >> inputRight >> inputHeight2;
            Building newBuilding = Building(inputHeight1, inputLeft, inputRight);
            buildings.push_back(newBuilding);
        }
    }
    fin.close();

    for (int i = 0; i < buildings.size(); i++) {
        int x_start = buildings[i].left;
        int x_end = buildings[i].right;
        int yh = buildings[i].height;
        for (int k = 1; k <= yh + 1; k++) {
            for (int z = x_start + 1; z <= x_end + 1; z++) {
                city[k][z] = 1;
            }
        }
    }

    vector<int> pointx;
    vector<int> pointy;

    for (int j = 1; j < c_columns; j++) {
        for (int i = 1; i < city.size(); i++) {
            int countAdj = 0;
            int countDiag = 0;
            if (city[i][j] == 1) {
                if (city[i - 1][j - 1] == 0)
                    countDiag += 1;
                if (city[i - 1][j] == 0)
                    countAdj += 1;
                if (city[i - 1][j + 1] == 0)
                    countDiag += 1;
                if (city[i][j - 1] == 0)
                    countAdj += 1;
                if (city[i][j + 1] == 0)
                    countAdj += 1;
                if (city[i + 1][j - 1] == 0)
                    countDiag += 1;
                if (city[i + 1][j] == 0)
                    countAdj += 1;
                if (city[i + 1][j + 1] == 0)
                    countDiag += 1;
                if (((countAdj == 0) && (countDiag == 1)) || ((countAdj == 2) && (countDiag >= 2))) {
                    pointx.push_back(j - 1);
                    pointy.push_back(i - 1);
                }
            }
        }
    }

    for (int i = 1; i <= pointy.size() / 2; i++) {
        int change = 0;
        if (pointy[2 * i + 1] == pointy[2 * i - 1]) {
            change = pointy[2 * i + 1];
            pointy[2 * i + 1] = pointy[2 * i];
            pointy[2 * i] = change;
        }
    }

    ofstream fout("skyline.out");
    for (int i = 0; i < pointx.size(); i++) {
        fout << pointx[i] << "  " << pointy[i] << endl;
    }
    fout.close();
    
    return 0;

}

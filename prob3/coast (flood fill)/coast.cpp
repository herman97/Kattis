#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <utility>
#include <stdlib.h>

using namespace std;
typedef pair<long long, long long> pairs;
typedef vector<long long> vi;
typedef vector<vi> vvi;
typedef vector<char> vs;
typedef vector<vs> vvs;
typedef vector<pairs> vp;

void solver(vvs& karta, vp& land);
bool land(vvs& karta);

int main(int argc, char *argv[]) {
    long long n, m;
    vp land;

    cin >> n >> m;
    vvs karta (n+2, vs(m+2, '0'));

    string red;
    for (int i = 1; i <= n; i++) {
        cin >> red;
        for (int j = 1; j <= m; j++) {
            if (red[j-1] == '1') {
                land.push_back(pairs(i, j));
            }
            karta[i][j] = red[j-1];
        }
    }
    solver(karta, land);
}

void solver(vvs& karta, vp& land) {
    
    queue<pairs> q;
    q.push(pairs(0, 0));

    while (!q.empty()) {
        pairs p = q.front();
        q.pop();

        int row = p.first;
        int col = p.second;

        if (karta[row][col] != '0') {
            continue;
        }

        karta[row][col] = '2';
        if (row + 1 < karta.size() && karta[row + 1][col] == '0') {
            q.push(pairs(row+1, col));
        }
        if (row - 1 >= 0 && karta[row - 1][col] == '0') {
            q.push(pairs(row-1, col));
        }
        if (col - 1 >= 0 && karta[row][col-1] == '0') {
            q.push(pairs(row, col-1));
        }
        if (col + 1 < karta[row].size() && karta[row][col+1] == '0') {
            q.push(pairs(row, col+1));
        }
    }
    
    int edges = 0;
    for (auto l : land) {
        if (karta[l.first-1][l.second] == '2') {
            edges++;
        }
        if (karta[l.first+1][l.second] == '2') {
            edges++;
        }
        if (karta[l.first][l.second-1] == '2') {
            edges++;
        }
        if (karta[l.first][l.second+1] == '2') {
            edges++;
        }
    }
    cout << edges << endl;
}

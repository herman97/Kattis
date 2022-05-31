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
typedef vector<string> vs;

struct inter {
    double min;
    double max;

    inter() {
        this->min = -1;
        this->max = -1;
    }

    inter(double min, double max) {
        this->min = min;
        this->max = max;
    }
};

typedef vector<inter> vin;

void solver(vin lista, inter goal);
bool compareByLength(const inter &a, const inter &b);

int main(int argc, char *argv[]) {
    double n, l, w;
    while (cin >> n >> l >> w) {
        vin lista;
        inter goal = inter(0, l);

        double x, r;
        for (int i = 0; i < n; i++) {
            cin >> x >> r;

            if (r <= w/2) {
                continue;
            }
            double dx = sqrt((r*r)-((w/2)*(w/2)));

            inter ival = inter(x-dx, x+dx);
            lista.push_back(ival);
        }

        solver(lista, goal);

    }
}

bool compareByLength(const inter &a, const inter &b)
{
    return a.max < b.max;
}

void solver(vin lista, inter goal) {
    sort(lista.begin(), lista.end(), compareByLength);
    

    if (lista.back().max < goal.max) {
        cout << -1 << endl;
        return;
    }

    vector<inter> curr;
    inter currel;
    double currmin = goal.min;
    int id = -1;
    while (true) {
        id = -1;
        for (int i = lista.size()-1; i >= 0; i--) {
            if (lista[i].min <= currmin) {
                currel = lista[i];
                currmin = currel.max;
                id = i;
                curr.push_back(currel);
                break;
            }
        }

        if (id == -1) {
            break;
        } else {
            lista.erase(lista.begin() + id);
            currmin = currel.max;
            if (currmin >= goal.max) {
                break;
            }
            currel = inter();

        }
        /* if (currel.min != -1 && currel.max != -1) {
            if (currmin >= goal.max) {
                break;
            }
            currel = inter();
        } */

    }

    if (curr.size() == 0 || curr[0].min > goal.min || curr.back().max < goal.max) {
        cout << -1 << endl;
    } else {
        cout << curr.size() << endl;

    }

}


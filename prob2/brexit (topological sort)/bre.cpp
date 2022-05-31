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

typedef vector<int> vi;
typedef pair<int, int> pairs;
typedef vector<vi> vvi;

struct country {
    int id;
    int neighbour_count;
    int og_neighbour_count;
    bool to_leave;
    vector<int> real_neighbours;
};

void solver(vector<country> cv, int our_country, int leaver);

int main(int argc, char *argv[])
{
    int c, p, x, l;
    int country1, country2;
    vector<country> cv;
    country placeholder;
    cv.push_back(placeholder);

    if (argc == 2){
        ifstream infile(argv[1]);
        infile >> c >> p >> x >> l;
        if (x == l) {
            cout << "leave" << endl;
            return 0;
        } 
        for (int i = 1; i <= c; i++) {
            country a;

            a.id = i;
            a.neighbour_count = 0;
            a.og_neighbour_count = 0;
            a.to_leave = false;

            if (i == l) {
                a.to_leave = true;
            }

            cv.push_back(a);
        }
        for (int i = 0; i < p; i++) {
            infile >> country1;
            infile >> country2;

            cv[country1].neighbour_count++;
            cv[country2].neighbour_count++;
            cv[country1].og_neighbour_count++;
            cv[country2].og_neighbour_count++;
            cv[country1].real_neighbours.push_back(country2);
            cv[country2].real_neighbours.push_back(country1);
        }
        solver(cv, x, l);

    } else {
        
        cin >> c >> p >> x >> l;
        if (x == l) {
            cout << "leave" << endl;
            return 0;
        }
        for (int i = 1; i <= c; i++) {
            country a;

            a.id = i;
            a.neighbour_count = 0;
            a.og_neighbour_count = 0;
            a.to_leave = false;

            if (i == l) {
                a.to_leave = true;
            }
            cv.push_back(a);
        }
        for (int i = 0; i < p; i++) {
            cin >> country1;
            cin >> country2;

            cv[country1].neighbour_count++;
            cv[country2].neighbour_count++;
            cv[country1].og_neighbour_count++;
            cv[country2].og_neighbour_count++;
            cv[country1].real_neighbours.push_back(country2);
            cv[country2].real_neighbours.push_back(country1);
        }
        solver(cv, x, l);
    }
}

void solver(vector<country> cv, int our_country, int leaver) {
    queue<int> qi;
    qi.push(leaver);
    int ic;

    for (int i = 0; i < cv[leaver].real_neighbours.size(); i++) {
        cv[cv[leaver].real_neighbours[i]].neighbour_count--;
        qi.push(cv[leaver].real_neighbours[i]);
    }
    while(!qi.empty()) {
        ic = qi.front();
        qi.pop();
        if (!cv[ic].to_leave && cv[ic].neighbour_count*2 <= cv[ic].og_neighbour_count) {
            cv[ic].to_leave = true;
            for (int i = 0; i < cv[ic].real_neighbours.size(); i++) {
                cv[cv[ic].real_neighbours[i]].neighbour_count--;
                qi.push(cv[ic].real_neighbours[i]);
            }
        }
    }
    if (cv[our_country].to_leave) {
        cout << "leave" << endl;
    } else {
        cout << "stay" << endl;
    }
}
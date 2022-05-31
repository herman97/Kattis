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
//typedef pair<int, int> pairs;

//map<int, vi> pos;
//map<int, string> votes1;

void solve(vi values, vi weights, int num_vals, int max_weight);

int main(int argc, char *argv[])
{
    int cap, num_items = -1;
    vi values;
    vi weights;
    int num;
    int w, v = 0;

    if (argc == 2){
        ifstream infile(argv[1]);
        while(true) {
            infile >> cap >> num_items;
            if (cap == -1 || num_items == -1) {
                break;
            }
            for (int i = 0; i < num_items; i++) {
                infile >> v >> w;
                values.push_back(v);
                weights.push_back(w);
            }

            solve(values, weights, num_items, cap);
            values.clear();
            weights.clear();
            cap = -1;
            num_items = -1;
        }

    } else {
        while(true) {
            cin >> cap >> num_items;
            if (cap == -1 || num_items == -1) {
                break;
            }
            for (int i = 0; i < num_items; i++) {
                cin >> v >> w;
                values.push_back(v);
                weights.push_back(w);
            }

            solve(values, weights, num_items, cap);
            values.clear();
            weights.clear();
            cap = -1;
            num_items = -1;
        }
        
    }
    
}

void solve(vi values,vi weights, int num_vals, int max_weight) {
    //cout << endl;
    //cout << "----------------- start -----------------" << endl;
    vector<vi> keep;
    vector<vi> saved;
    vi temp_vec;
    
    for (int i = 0; i < num_vals; i++) {
        for (int j = 0; j <= max_weight; j++) {
            temp_vec.push_back(0);
        }
        keep.push_back(temp_vec);
        saved.push_back(temp_vec);
        temp_vec.clear();
    }
    //cout << keep.size() << " " << keep.at(0).size() << endl;
    if (num_vals == 1) {
        if (weights[0] <= max_weight) {
            cout << 1 << endl;
            cout << 0 << endl;
            return;
        }else {
            cout << 0 << endl;
            return;
        }
    }
    for (int i = 1; i < num_vals; i++) {
        //cout << i << endl;
        for(int j = 0; j <= max_weight; j++) {
            //cout << i << ":i j:" << j << endl;
            //cout << weights.at(i) << " weights.at(i)" << endl;
            /*if (j >= weights.at(i)) {
                cout << values.at(i) << " values.at(i)" << endl;
                cout << saved.at(i-1).at(j-weights.at(i)) << " saved.at(i-1).at(j-weights[i]) "<< endl;
                cout << saved.at(i-1).at(j) << " saved.at(i-1).at(j)" << endl;
            } */

            if (weights.at(i) <= j && values.at(i) + saved.at(i-1).at(j-weights.at(i)) > saved.at(i-1).at(j)) {
                //cout << " if " << endl;
                saved[i][j] = values.at(i) + saved.at(i-1).at(j-weights[i]);
                keep[i][j] = 1;
            } else {
                //cout << " ekse " << endl;
                saved[i][j] = saved[i-1][j];
                keep[i][j] = 0;
            }
        } 
    }  
    /* for (int i = 0; i < num_vals; i++) {
        for (int j = 0; j <= max_weight; j++) {
            cout << saved.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < num_vals; i++) {
        for (int j = 0; j <= max_weight; j++) {
            cout << keep.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;

    cout << " nu mer loop " << endl; */
    int temp = max_weight;
    vi p;
    vi::iterator it;

    for (int i = num_vals-1; i >= 0; i--) {
        //cout <<  i << " " <<  temp << " this is temp"  << weights[i] << endl;

        if (keep[i][temp] == 1) {
            //cout << " == 1" << endl;
            it = p.begin();
            p.insert(it, i);
            temp = temp-weights[i];
        }
    }
    cout << p.size() << endl;
    for (it = p.begin(); it != p.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    //cout << " sista raden " << endl;
}

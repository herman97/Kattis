/*
    Author: Herman Nordin
    Problem: Find the shortest path from a node to another node, given a graph.
    Complexity: O(V + E log V) since it is using a priority queue
*/


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

typedef vector<long long> vi;
typedef vector<vi> vvi;
map<long long, vvi> edges;

void solver(vi queries, long long start, long long num_nodes);
long long wait_time(long long curr, long long start, long long multi);
int main(int argc, char *argv[])
{

    // num nodes, num edges, num queries, start 
    long long num_probs = 0;

    long long n, m, q, s;
    long long u, v, t0, p, d;
    long long first = 1;
    long long x;

    if (argc == 2){   
        ifstream infile(argv[1]);
        while(true) {
            infile >> n;
            infile >> m;
            infile >> q;
            infile >> s;
            if (n == 0 && m == 0 && q == 0 && s == 0) {
                break;
            }

            if (first == 1) {
                first++;
            } else {
                cout << endl;
            }

            for (long long i = 0; i < m; i++) {
                infile >> u;
                infile >> v;
                infile >> t0;
                infile >> p;
                infile >> d;
                
                vi t;
                t.push_back(v);
                t.push_back(t0);
                t.push_back(p);
                t.push_back(d);
                edges[u].push_back(t);
            }
            vi queries;
            for (long long i = 0; i < q; i++) {
                infile >> x;
                queries.push_back(x);
            }
            solver(queries, s, n);
            edges.clear();
        }

    } else {
        while(true) {
            cin >> n;
            cin >> m;
            cin >> q;
            cin >> s;
            if (n == 0 && m == 0 && q == 0 && s == 0) {
                break;
            }

            if (first == 1) {
                first++;
            } else {
                cout << endl;
            }

            for (long long i = 0; i < m; i++) {
                cin >> u;
                cin >> v;
                cin >> t0;
                cin >> p;
                cin >> d;
                vi t;
                t.push_back(v);
                t.push_back(t0);
                t.push_back(p);
                t.push_back(d);
                edges[u].push_back(t);
            }
            vi queries;
            for (long long i = 0; i < q; i++) { 
                cin >> x;
                queries.push_back(x);
            }

            solver(queries, s, n);
            edges.clear();
        }
    }
}

long long wait_time(long long curr, long long start, long long multi) {
    if (start >= curr) {
        return start - curr;
    }
    //return multi - (curr - start);
    if (((curr - start)%multi) == 0) {
        return 0;
    }
    return multi - ((curr - start)%multi);
}

void solver(vi queries, long long start, long long num_nodes) {

    /*
    edge: to, start time, time multiplier, time it takes
    */
    vi time (num_nodes, 9223372036854775807);
    vi path (num_nodes, -1);
    time[start] = 0;
    long long curr;
    priority_queue<long long, vector<long long>, greater<long long> > pq2;
    pq2.push(start);

    while(!pq2.empty()) {
        curr = pq2.top();
        pq2.pop();

        for (auto n : edges[curr]) {
            if (n[2] == 0 && time[curr] > n[1]) {
                continue;
            } else {
                long long diff = wait_time(time[curr], n[1], n[2]);
                long long temp = time[curr] + diff + n[3];
                if (temp < time[n[0]]) {
                    time[n[0]] = temp;
                    path[n[0]] = curr;
                    pq2.push(n[0]);
                }    
            }
        }
    }

    for (auto node : queries) {
        long long c = time[node];
        if (c == 9223372036854775807 || node >= time.size()) {
            cout << "impossible" << endl;
        } else {
            cout << c << endl;
        }
    }
}
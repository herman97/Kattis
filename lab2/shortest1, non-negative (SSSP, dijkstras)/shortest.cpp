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
typedef pair<long long, long long> pairs;
typedef vector<pairs> pv;

map<long long, pv> edges;

void solver(vi queries, long long start, long long num_nodes);

int main(int argc, char *argv[])
{

    // num nodes, num edges, num queries, start 
    long long num_probs = 0;

    long long n, m, q, s;
    long long u, v, w;
    long long first = 1;
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
                infile >> w;
                edges[u].push_back(pairs(v, w));
            }
            vi queries;
            long long x;
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
                cin >> w;
                edges[u].push_back(pairs(v, w));
            }
            vi queries;
            long long x;
            for (long long i = 0; i < q; i++) { 
                cin >> x;
                queries.push_back(x);
            }

            solver(queries, s, n);
            edges.clear();
        }
    }
}

void solver(vi queries, long long start, long long num_nodes) {
    vi cost (num_nodes, 9223372036854775807);
    vi path (num_nodes, -1);
    
    cost[start] = 0;
    pairs curr;
    priority_queue<pairs, vector<pairs>, greater<pairs> > pq;
    //priority_queue<int, vector<int>, greater<int> > pq2;
    pq.push(pairs(0, start));
    while(!pq.empty()) {
        curr = pq.top();
        pq.pop();

        for (auto n : edges[curr.second]){
            long long temp = cost[curr.second] + n.second;
            if (temp < cost[n.first]) {
                cost[n.first] = temp;
                path[n.first] = curr.second;
                pq.push(pairs(cost[n.first], n.first));
            }
        }
    }

    for (auto node : queries) {
        long long c = cost[node];
        if (c == 9223372036854775807 || node >= cost.size()) {
            cout << "impossible" << endl;
        } else {
            cout << c << endl;
        }
    }
}
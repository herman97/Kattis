/*
    Author: Herman Nordin
    Problem: find the mincut in a given graph
    Complexity: Time complexity of ford-fulkerson is O(max_flow * E)
                Time complexity of bfs is O(V + E)
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
typedef pair<long long, long long> pairs;
typedef vector<long long> vi;
typedef vector<pairs> pv;
typedef vector<vi> vvi;

struct ret_val {
    long long mf;
    vector<long long> path;

    ret_val(long long mf, vector<long long> p) {
        this->mf = mf;
        this->path = p;
    }
};

struct Edge {
    long long node1;
    long long node2;
    long long flow;

    Edge(long long n1, long long n2, long long flow) {
        this->node1 = n1;
        this->node2 = n2;
        this->flow = flow;
    }
};

typedef vector<Edge> ve;
typedef map<long long, ve> nodemap;
typedef map<long long, vi> nm1;

void solver(long long& start, long long& end);
ret_val bfs(long long& start, long long& end);
long long dfs(vi& visited, long long start);

vvi edges;
vvi res_g;

int main(int argc, char *argv[])
{
    long long n, m, s, t;
    long long u, v, c;

    if (argc == 2){   
        ifstream infile(argv[1]);
        infile >> n >> m >> s >> t;
        edges = vvi(n);
        res_g = vvi(n);

        for (long long j = 0; j < n ; j++) {
            edges[j] = vi(n);
            res_g[j] = vi(n);
        }
        for (long long i = 0; i < m; i++) {
            infile >> u >> v >> c;
            edges[u][v] = c;
            res_g[u][v] = c;
        }
        solver(s, t);

    } else {
        cin >> n >> m >> s >> t;
        edges = vvi(n);
        res_g = vvi(n);
        for (long long j = 0; j < n ; j++) {
            edges[j] = vi(n);
            res_g[j] = vi(n);
        }
        for (long long i = 0; i < m; i++) {
            cin >> u >> v >> c;
            edges[u][v] = c;
            res_g[u][v] = c;
        }
        solver(s, t);
    }
}

long long dfs(vi& visited, long long start){
    visited[start] = 1;
    long long reachable = 1;
    vi q;
    q.push_back(start);

    while (!q.empty()) {
        long long curr = q.back();
        q.pop_back();

        for (long long i = 0; i < res_g[curr].size(); i++) {
            if (visited[i] != 1 && res_g[curr][i] > 0) {
                q.push_back(i);
                visited[i] = 1;
                reachable++;
            }
        }
    }
    return reachable;
    
}

void solver(long long& start, long long& end){
    long long max_flow = 0;
    bool solution_found = false;
    long long edges_used = 0;

    while(true) {
        
        ret_val r = bfs(start, end);
        vector<long long> path = r.path;
        if (path[end] == -1) {
            break;
        }

        solution_found = true;
        long long pf = r.mf;
        long long node = end;
        while (node != start) {
            long long prev = path[node];
            res_g[prev][node] -= pf;
            res_g[node][prev] += pf;
            node = prev;
        }
        max_flow += pf;

    }

    vi reachable_nodes(res_g[0].size(), 0);
    long long c = dfs(reachable_nodes, start);
    cout << c << endl;
    for (int i = 0; i < reachable_nodes.size(); i++) {
        if (reachable_nodes[i] == 1) {
            cout << i << endl;
        }
    }
    
}

ret_val bfs(long long& start, long long& end) {
    queue<long long> q;
    vector<bool> visited(res_g.size(), false);
    vector<long long> path(res_g.size(), -1);
    vector<long long> max_flow(res_g.size(), 9223372036854775807);
    q.push(start);

    visited[start] = true;

    while(!q.empty()) {
        long long curr = q.front();
        q.pop();
        for (long long i = 0; i < res_g[curr].size(); i++) {
            if (!visited[i] && res_g[curr][i] > 0) {
                long long f = min(res_g[curr][i], max_flow[curr]);
                max_flow[i] = f;
                visited[i] = true;
                q.push(i);
                path[i] = curr;
            }
        }
        if (visited[end]) {
            break;
        }
    }
    ret_val r = ret_val(max_flow[end], path);
    return r;
}
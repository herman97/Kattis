/*
    Author: Herman Nordin
    Problem: Find the maximum flow between two nodes
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
typedef vector<vi> vvi;

void solver(vvi& og, vvi& edges, vvi& res_g, vector<pairs>& possible, long long& start, long long& end, long long& num_nodes);
bool bfs(vvi& res_g, vvi& edges, long long& start, long long& end, long long& num_nodes, vi& path);

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

int main(int argc, char *argv[])
{   
    // https://www.programmersought.com/article/25526540847/
    // num nodes, num edges, source, sink
    vvi edges;
    vvi res_g;
    vvi og;
    vector<pairs> possible;

    long long n, m, s, t;
    long long u, v, c;
    long long source = 0;
    long long num_nodes;
    long long goal;
    
    cin >> n >> m >> s >> t;
    for (int i = 0; i < n; i++) {
        vi a(n, 0);
        res_g.push_back(a);
        vi c(n, 0);
        og.push_back(c);
        vi b;
        edges.push_back(b);
    }

    for (long long i = 0; i < m; i++) {
        cin >> u >> v >> c;
        //cout << u << " " << v << " " << c << endl;
        og[u][v] = c;
        edges[u].push_back(v);
        edges[v].push_back(u);
        //cout << " fel " << endl;
        res_g[u][v] = c;
        possible.push_back(pairs(u,v));
    }
    solver(og, edges, res_g, possible, s, t, n);
    
}

void solver(vvi& og, vvi& edges, vvi& res_g, vector<pairs>& possible, long long& start, long long& end, long long& num_nodes){
    long long max_flow = 0;
    vi path(num_nodes, -1);
    bool solution_found = false;

    // ford fulkersson algorithm
    while(true) {
        bool success = bfs(res_g, edges, start, end, num_nodes, path);
        if (!success) {
            break;
        }
        solution_found = true;
        long long pf = 9223372036854775807;
        long long node = end;

        while (path[node] != -1) {
            long long prev = path[node];
            pf = min(pf, res_g[prev][node]);
            node = prev;
        }

        node = end;
        while (path[node] != -1) {
            long long prev = path[node];
            res_g[prev][node] -= pf;
            res_g[node][prev] += pf;
            node = prev;
        }
        max_flow += pf;
    }
    ve edges1;
    if (solution_found) {
        for (auto& v: possible) {
            if (og[v.first][v.second] > 0 && res_g[v.first][v.second] < og[v.first][v.second]) {
                edges1.push_back(Edge(v.first, v.second, og[v.first][v.second] - res_g[v.first][v.second]));
            }
        }
    }
    
    cout << num_nodes << " " << max_flow << " " << edges1.size() << endl;
    for (auto& e : edges1) {
        cout << e.node1 << " " << e.node2 <<  " " << e.flow << endl;
    }
}

bool bfs(vvi& res_g, vvi& edges, long long& start, long long& end, long long& num_nodes, vi& path) {
    queue<long long> q;
    vector<bool> visited(num_nodes, false);
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        long long curr = q.front();
        q.pop();
        for (auto a: edges[curr]) {

            if (!visited[a] && res_g[curr][a] > 0) {
                visited[a] = true;
                q.push(a);
                path[a] = curr;
                if (visited[end]) {
                    return true;
                }
            }
        }
        if (visited[end]) {
            return true;
        }
    }
    return false;
}
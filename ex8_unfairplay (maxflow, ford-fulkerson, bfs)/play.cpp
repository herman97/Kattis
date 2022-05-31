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

void solver(vvi& edges, vvi& res_g, vector<pairs>& matches, int start, long long end, long long num_nodes, long long n, long long m);
bool bfs(vvi& res_g, vvi& edges, int start, long long end, long long num_nodes, vi& path);

int main(int argc, char *argv[])
{   
    // https://www.programmersought.com/article/25526540847/
    // num nodes, num edges, source, sink
    vi points;
    vvi edges;
    vvi res_g;
    vector<pairs> matches;

    long long n, m, p;
    int source = 0;
    long long num_nodes;
    long long goal;
    long long our_matches = 0;

    while (true) {
        cin >> n;
        if (n == -1) {
            return 0;
        }
        cin >> m;
        num_nodes = n + m + 2; // matches, teams, start and sink
        goal = n + m + 1;

        for (int i = 0; i < n; i++) {
            cin >> p;
            //cout << p << " points i: " << i << endl;
            points.push_back(p);
        }
        
        for (int i = 0; i < n + m + 2; i++) {
            vi a(num_nodes, 0);
            res_g.push_back(a);
            vi b;
            edges.push_back(b);
        }

        for (int i = 1; i < m + 1; i++) {
            long long t1, t2;
            cin >> t1 >> t2;
            matches.push_back(pairs(t1,t2));

            if (t1 == n || t2 == n) {
                our_matches++;
            } else {
                res_g[source][i] = 2;
                
                edges[source].push_back(i);
                edges[i].push_back(source);

                res_g[i][m+t1] = 99999;
                res_g[i][m+t2] = 99999;

                edges[i].push_back(m+t1);
                edges[i].push_back(m+t2);
                edges[m+t1].push_back(i);
                edges[m+t2].push_back(i);
            }
        }
        
        long long our_max_points = points.back() + (our_matches*2);
        for (int i = m + 1; i < m+n+1; i++) {
            res_g[i][goal] = our_max_points - points[i-m-1] - 1;
            edges[i].push_back(goal);
            edges[goal].push_back(i);
        }

        bool next = false;
        for (int i = 0; i < points.size()-1; i++) {
            if (our_max_points <= points[i]) {
                cout << "NO" << endl;
                next = true;
                break;
            }
        }

        if (next) {
            edges.clear();
            res_g.clear();
            matches.clear();
            points.clear();
            our_matches = 0;
            continue;
        }

        solver(edges, res_g, matches, source, goal, num_nodes, n, m);

        edges.clear();
        res_g.clear();
        matches.clear();
        points.clear();
        our_matches = 0;
    }
}

void solver(vvi& edges, vvi& res_g, vector<pairs>& matches, int start, long long end, long long num_nodes, long long n, long long m){
    long long max_flow = 0;
    vi path(num_nodes, -1);

    // ford fulkersson algorithm
    while(true) {

        bool success = bfs(res_g, edges, start, end, num_nodes, path);
        if (!success) {
            break;
        }
        long long pf = 9223372036854775807;
        long long node = end;
        while (node != start) {
            long long prev = path[node];
            pf = min(pf, res_g[prev][node]);
            node = prev;
        }

        node = end;
        while (node != start) {
            long long prev = path[node];
            res_g[prev][node] -= pf;
            res_g[node][prev] += pf;
            node = prev;
        }
        max_flow += pf;
    }

    for (int i = 1; i < m + 1; i++) {
        if (matches[i-1].first != n && matches[i-1].second != n && res_g[start][i] != 0) {
            cout << "NO" << endl;
            return;
        }
    }

    for (int i = 0; i < matches.size(); i++) {
        long long team1 = matches[i].first;
        long long team2 = matches[i].second;

        // our team always wins
        // cout << res_g[team1 + m][i+1] << " : " << res_g[team2 + m][i+1] << endl;
        if (team1 == n) {
            cout << "s0 ";
        } else if (team2 == n) {
            cout << "s2 ";
        } else if (res_g[team1 + m][i+1] == 2) {
            cout << "t0 ";
        } else if (res_g[team2 + m][i+1] == 2) {
            cout << "t2 ";
        } else {
            cout << "t1 ";
        }
    }
    cout << endl;
    
}

bool bfs(vvi& res_g, vvi& edges, int start, long long end, long long num_nodes, vi& path) {
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

                if (visited[end] || a == end) {
                    return true;
                }
            }
        }
    }
    return false;
}
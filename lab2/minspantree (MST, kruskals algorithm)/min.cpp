
/*
    Author: Herman Nordin
    Problem: Find a minimal spanning tree
    Time Complexity: Kruskals is O(E*logV)
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

map<long long, vi> pos;
map<long long, string> votes1;

struct Edge {
    long long dist;
    long long node1;
    long long node2;

    Edge() {
        this -> dist = -1;
        this -> node1 = -1;
        this -> node2 = -1;
    }

    Edge (long long dist, long long n1, long long n2) {
        this -> dist = dist;
        this -> node1 = n1;
        this -> node2 = n2;
    }
};

typedef vector<Edge> ve;
bool compareByDist(const Edge a, const Edge b);
bool compareByNode(const Edge a, const Edge b);


struct Graph {
    long long num_nodes;
    ve edges;
    vi parents;
    vi ranks;
    ve mst;

    Graph(long long num, ve edges) {
        this -> num_nodes = num;
        this -> edges = edges;
    }

    long long find_parent(long long node) {
        if (this->parents[node] == node) {
            return node;
        }
        return find_parent(this->parents[node]);
    }

    void krusses() {
        sort(this->edges.begin(), this->edges.end(), compareByDist);

        for (long long i = 0; i < this->num_nodes; i++) {
            this->parents.push_back(i);
            this->ranks.push_back(0);
        }
        long long cost = 0;

        for (long long i = 0; i < this->edges.size(); i++) {
            
            long long p1 = this->find_parent(this->edges[i].node1);
            long long p2 = this->find_parent(this->edges[i].node2);

            if (p1 != p2) {
                this->mst.push_back(this->edges[i]);
                cost += edges[i].dist;
                if (this->ranks[p1] < this->ranks[p2]) {
                    this->parents[p1] = p2;
                    this->ranks[p2]++;
                } else {
                    this->parents[p2] = p1;
                    this->ranks[p1]++;
                }
            }
        }
        
        if (this->mst.size() != this->num_nodes-1){
            cout << "Impossible" << endl;
        } else {
            cout << cost << endl;
            sort(this->mst.begin(), this->mst.end(), compareByNode);
            for (long long i = 0; i < mst.size(); i++){
                cout << this->mst[i].node1 << " " << this->mst[i].node2 << endl;
            }
        }
    }
};

bool compareByDist(const Edge a, const Edge b) {
    return a.dist < b.dist;
}

bool compareByNode(const Edge a, const Edge b) {
    return ((a.node1 < b.node1) || (a.node1==b.node1 && a.node2 < b.node2));
}

int main(int argc, char *argv[])
{
    ve vecedge;
    long long num_nodes, num_edges;
    long long u, v, w;

    if (argc == 2){
        ifstream infile(argv[1]);
        while (infile >> num_nodes >> num_edges) {
            if (num_nodes == 0 && num_nodes == 0) {
                break;
            }
            for (long long j = 0; j < num_edges; j++){
                infile >> u >> v >> w;
                Edge e;
                if (u < v) {
                    e = Edge(w, u, v);
                } else {
                    e = Edge(w, v, u);
                }
                vecedge.push_back(e);
            }
            Graph g = Graph(num_nodes, vecedge);
            g.krusses();
            vecedge.clear();
        }
    } else {
        while (cin >> num_nodes >> num_edges) {
            if (num_nodes == 0 && num_nodes == 0) {
                break;
            }
            for (long long j = 0; j < num_edges; j++){
                cin >> u >> v >> w;
                Edge e;
                if (u < v) {
                    e = Edge(w, u, v);
                } else {
                    e = Edge(w, v, u);
                }
                vecedge.push_back(e);
            }
            Graph g = Graph(num_nodes, vecedge);
            g.krusses();
            vecedge.clear();
        }
    } 
}
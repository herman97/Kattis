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

struct Node {
    int index;
    double x;
    double y;

    Node() {
        this->index = -1;
        this->x = -1;
        this->y = -1;
    }

    Node(int index, double x, double y) {
        this->index = index;
        this->x = x;
        this->y = y;
    }

    bool operator==(const Node& r) const {
        return index == r.index;
    }
};

typedef vector<Node> vn;
void solver(vn nodes);

struct Edge {
    double dist;
    Node node1;
    Node node2;

    Edge (double dist, Node n1, Node n2) {
        this -> dist = dist;
        this -> node1 = n1;
        this -> node2 = n2;
    }
};

typedef vector<Edge> ve;
bool compareByDist(const Edge a, const Edge b);
ve create_edges(vn nodes);

struct Graph {
    int num_nodes;
    ve edges;
    vi parents;
    vi ranks;
    ve mst;

    Graph(int num, ve edges) {
        this -> num_nodes = num;
        this -> edges = edges;
    }

    int find_parent(int node) {
        if (this -> parents[node] == node) {
            return node;
        }
        return find_parent(this -> parents[node]);
    }

    void krusses() {
        sort(this->edges.begin(), this->edges.end(), compareByDist);
        for (int i = 0; i < this->num_nodes; i++) {
            this->parents.push_back(i);
            this->ranks.push_back(0);
        }
        double cost = 0;

        for (int i = 0; i < this->edges.size(); i++) {
            
            int p1 = this->find_parent(this->edges[i].node1.index);
            int p2 = this->find_parent(this->edges[i].node2.index);

            if (p1 != p2) {
                this->mst.push_back(this->edges[i]);
                cost += edges[i].dist;
                //cout << this->edges[i].node1.index << ": node 1, node:" << this->edges[i].node2.index << endl;
                cout << this->ranks[p1] << " " << this->ranks[p2] << endl;
                if (this->ranks[p1] < this->ranks[p2]) {
                    this->parents[p1] = p2;
                    this->ranks[p2]++;
                } else {
                    this->parents[p2] = p1;
                    this->ranks[p1]++;
                }
            }
        }
        cout << fixed;
        cout << setprecision(2);
        cout << cost << endl;
    }
};

bool compareByDist(const Edge a, const Edge b) {
    return a.dist < b.dist;
}

ve create_edges(vn nodes) {
    ve edges;

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = i+1; j < nodes.size(); j++) {
            if (nodes[i] == nodes[j]) {
                continue;
            }
            double temp_dist = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2));
            Edge e = Edge(temp_dist, nodes[i], nodes[j]);
            edges.push_back(e);
        }
    }
    return edges;
}

int main(int argc, char *argv[])
{
    int num_probs = 0;
    vn lista;
    vi temp;
    ve vecedge;
    int num;
    double x; 
    double y;
    bool first = true;

    if (argc == 2){
          
        ifstream infile(argv[1]);
        infile >> num_probs;

        for (int j = 0; j < num_probs; j++){
            if (!first) {
                cout << endl;
            }
            int num_islands;
            infile >> num_islands;

            for (int i = 0; i < num_islands; i++) {
                infile >> x;
                infile >> y;

                Node temp_node = Node(i, x, y);
                lista.push_back(temp_node);
            }

            vecedge = create_edges(lista);
            Graph g = Graph(num_islands, vecedge);
            g.krusses();
            lista.clear();
            num_islands = 0;
            first = false;
        }
            

    } else {

        cin >> num_probs;
        
        for (int j = 0; j < num_probs; j++){
            int num_islands;
            cin >> num_islands;

            for (int i = 0; i < num_islands; i++) {
                if (!first) {
                    cout << endl;
                }
                cin >> x;
                cin >> y;
                Node temp_node = Node(i, x, y);
                lista.push_back(temp_node);
            }
            vecedge = create_edges(lista);
            Graph g = Graph(num_islands, vecedge);
            g.krusses();
            lista.clear();
            num_islands = 0;
            first = false;
        }
    }
    
}
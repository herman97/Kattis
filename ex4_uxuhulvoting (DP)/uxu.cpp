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

/*
    Voting by flipping one of three stones, changing the outcome of the voting. Solved with dynamic programming and recursion.
*/

using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pairs;

map<int, vi> pos;
map<int, string> votes1;

int solve(vector<vi> pos, int priest, int curr);
void setup();

int main(int argc, char *argv[])
{
    setup();
    int num_probs;
    vector<vi> lista;
    vi temp;
    vi num_priests;
    int num;
    int v = 0;

    if (argc == 2)
    {
        ifstream infile(argv[1]);
        infile >> num_probs;

        for (int i = 0; i < num_probs; i++)
        {
            infile >> v;
            for (int j = 0; j < v; j++)
            {
                for (int x = 0; x < 8; x++)
                {
                    infile >> num;
                    // cout << num << " this is num" << endl;
                    temp.push_back(num);
                }
                lista.push_back(temp);
                temp.clear();
            }
            int res = solve(lista, 1, 1);
            cout << votes1.at(res) << endl;
            lista.clear();
        }
    }
    else
    {

        cin >> num_probs;
        for (int i = 0; i < num_probs; i++)
        {
            cin >> v;
            for (int j = 0; j < v; j++)
            {
                for (int x = 0; x < 8; x++)
                {
                    cin >> num;
                    temp.push_back(num);
                }
                lista.push_back(temp);
                temp.clear();
            }

            int res = solve(lista, 1, 1);
            cout << votes1.at(res) << endl;
            lista.clear();
        }
    }
}

int solve(vector<vi> votes, int priest, int curr)
{
    int best = -1;

    if (votes.size() == priest)
    {
        for (int i = 0; i < 3; i++)
        {
            if (best == -1 || votes.at(priest - 1)[pos.at(curr)[i] - 1] < votes.at(priest - 1)[best - 1])
            {
                best = pos.at(curr)[i];
            }
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            int temp = solve(votes, priest + 1, pos.at(curr)[i]);
            if (best == -1 || votes.at(priest - 1)[temp] < votes.at(priest - 1)[best])
            {
                best = temp;
            }
        }
    }
    return best;
}

void setup()
{
    vi a;
    a.push_back(2);
    a.push_back(3);
    a.push_back(5);
    pos[1] = a;
    a.clear();
    a.push_back(6);
    a.push_back(4);
    a.push_back(1);
    pos[2] = a;
    a.clear();
    a.push_back(4);
    a.push_back(7);
    a.push_back(1);
    pos[3] = a;
    a.clear();
    a.push_back(8);
    a.push_back(2);
    a.push_back(3);
    pos[4] = a;
    a.clear();
    a.push_back(1);
    a.push_back(7);
    a.push_back(6);
    pos[5] = a;
    a.clear();
    a.push_back(5);
    a.push_back(8);
    a.push_back(2);
    pos[6] = a;
    a.clear();
    a.push_back(3);
    a.push_back(5);
    a.push_back(8);
    pos[7] = a;
    a.clear();
    a.push_back(4);
    a.push_back(7);
    a.push_back(6);
    pos[8] = a;

    votes1[1] = "NNN";
    votes1[2] = "NNY";
    votes1[3] = "NYN";
    votes1[4] = "NYY";
    votes1[5] = "YNN";
    votes1[6] = "YNY";
    votes1[7] = "YYN";
    votes1[8] = "YYY";
}
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

/*
    Divide a tree into pieces by chopping of the smallest leaf intil nothing is left of the tree
*/

void wood(priority_queue<int, vector<int>, std::greater<int>> pq, map<int, int> counter, queue<int> vector_v);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int len;
    priority_queue<int, vector<int>, std::greater<int>> pq; // priority queue sorting from smallest to largest instead of normal largest to smallest
    map<int, int> counter;
    queue<int> vector_v;

    cin >> len;

    int v;
    // a queue for the vector v. And a counter for how many times every element occurs
    for (int i = 0; i < len; i++)
    {
        cin >> v;
        counter[v]++;
        vector_v.push(v);
    }

    if (vector_v.back() != len + 1)
    {
        cout << "Error" << endl;
        return 0;
    }

    // a priority queue for what value we pair up next (values not in vector v)
    for (int i = 1; i <= len; i++)
    {
        if (counter.find(i) == counter.end())
        {
            pq.push(i);
        }
    }
    // if we dont have values to pair up its error maybe?
    if (pq.empty())
    {
        cout << "Error" << endl;
        return 0;
    }
    else
    {
        wood(pq, counter, vector_v);
    }
}

void wood(priority_queue<int, vector<int>, std::greater<int>> pq, map<int, int> counter, queue<int> vector_v)
{

    int element;
    while (!vector_v.empty())
    {

        element = vector_v.front();
        vector_v.pop();
        counter[element]--;

        cout << pq.top() << endl;
        pq.pop();

        if (counter[element] == 0)
        {
            pq.push(element);
        }
    }
}

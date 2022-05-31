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
    Check if the given clauses are satisfiable.

    Will use bitshifting to solve.
*/

using namespace std;
typedef vector<long long> vi;
typedef vector<string> vs;

vs split(string clause);
bool solver(int vars, vector<vi> &clauses);

int main(int argc, char *argv[])
{
    int tests;
    int num_vars;
    int num_clauses;
    string clause;

    cin >> tests;

    for (int q = 0; q < tests; q++)
    {
        cin >> num_vars;
        cin >> num_clauses;
        cin.ignore();

        vector<vi> clauses(0);

        for (int i = 0; i < num_clauses; i++)
        {
            getline(cin, clause);
            vs cl = split(clause);
            vi variables(num_vars, 0);
            bool will_always_work = false;

            for (auto c : cl)
            {
                if (c == "v")
                {
                    continue;
                }
                int index;
                int neg;

                if (c[0] == '~')
                {
                    neg = -1;
                    index = stoi(c.substr(2)) - 1;
                }
                else
                {
                    neg = 1;
                    index = stoi(c.substr(1)) - 1;
                }

                // if one varible is both negated and not in the same clause the clause will always succeed
                if (variables[index] * neg == -1)
                {
                    will_always_work = true;
                    break;
                }

                variables[index] = neg;
            }

            // Only push if clause is not always true
            if (!will_always_work)
            {
                clauses.push_back(variables);
            }
        }

        if (!solver(num_vars, clauses))
        {
            cout << "unsatisfiable" << endl;
        }
        else
        {
            cout << "satisfiable" << endl;
        }
    }
}

vs split(string clause)
{
    // split clause into a vector
    vs spliter;
    string s = "";
    for (auto c : clause)
    {
        if (c == ' ')
        {
            spliter.push_back(s);
            s = "";
        }
        else
        {
            s.push_back(c);
        }
    }
    spliter.push_back(s);
    return spliter;
}

bool solver(int vars, vector<vi> &clauses)
{
    // go through all possible solutions and check if they solve all clauses
    for (int i = 0; i < (1 << vars); i++)
    {
        bool rules_working = true;
        for (auto clause : clauses)
        {
            bool working_rule = false;
            for (int j = 0; j < vars; j++)
            {
                // check if the bit at place j is set
                if ((i & (1 << j)) >= 1 && clause[j] == 1)
                {
                    working_rule = true;
                    break;
                }
                else if ((i & (1 << j)) == 0 && clause[j] == -1)
                {
                    working_rule = true;
                    break;
                }
            }
            if (!working_rule)
            {
                rules_working = false;
                break;
            }
        }
        if (rules_working)
        {
            return true;
        }
    }
    return false;
}

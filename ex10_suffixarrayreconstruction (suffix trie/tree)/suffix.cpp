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
    Reconstruct a word by given suffixes.
    Starts from the back and places the suffixes in the word if possible, else returns impossible.

    Suffix trie/tree implementation.
*/

using namespace std;
typedef pair<long long, long long> pairs;
typedef vector<long long> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;

bool solver(string &word, string suffix, int index);

int main(int argc, char *argv[])
{

    int tests;
    int num_suffixes;
    int index;
    int len_word;
    string suffix;

    cin >> tests;

    for (int i = 0; i < tests; i++)
    {
        cin >> len_word;
        cin >> num_suffixes;
        string word(len_word, '$');
        bool cont = false;
        for (int j = 0; j < num_suffixes; j++)
        {
            cin >> index;
            cin >> suffix;
            if (!solver(word, suffix, index - 1))
            {
                // cout << word << " false" << endl;
                cont = true;
            }
        }
        for (int a = 0; a < word.size(); a++)
        {
            if (word[a] == '$')
            {
                cont = true;
                break;
            }
        }

        if (cont)
        {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        cout << word << endl;
    }
}

bool solver(string &word, string suffix, int index)
{
    bool star = false;
    for (int i = index; i < word.size(); i++)
    {
        if (suffix[i - index] == '*')
        {
            star = true;
            break;
        }
        else if (suffix[i - index] != word[i] && word[i] != '$')
        {
            return false;
            break;
        }
        else
        {
            cout << suffix[i - index] << " this is suffix " << endl;
            word[i] = suffix[i - index];
        }
    }

    if (star)
    {
        int c = word.size() - 1;
        for (int i = suffix.size() - 1; i >= 0; i--)
        {
            if (suffix[i] == '*')
            {
                break;
            }
            else if (suffix[i] != word[c] && word[c] != '$')
            {
                // cout << suffix[i] << " " << word[c] << " " << endl;
                return false;
                break;
            }
            else
            {
                word[c] = suffix[i];
            }
            c--;
        }
    }
    return true;
}

// veri_part1.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include "Stack.hpp"
#include "Node.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

Node *pushL(int *yeni, int *eski, int id, Node *root, vector<string> vek);
vector<string> split(string target, string delim);

int main()
{
    int id = 0;
    int *listyeni;
    int *listeski;
    Node *root = NULL;
    vector<string> v;

    ifstream file("Kisiler.txt");
    int number_of_lines = 0;

    if (file.is_open())
    {
        string line;
        while (std::getline(file, line))
        {
            number_of_lines++;
        }
        file.close();
    }

    listeski = new int[number_of_lines];
    listyeni = new int[number_of_lines];

    file.clear();
    file.open("Kisiler.txt");
    if (file.is_open())
    {
        string line;
        while (std::getline(file, line))
        {
            v = split(line, "#");
            root = pushL(listyeni, listeski, id, root, v);
            id++;
        }
        file.close();
    }

    cout << "AVL Agacinin postorder goruntusu:  \n\n";
    root->Postorder(root);
    delete (listeski);
    delete (listyeni);
    delete (root);
    return 0;
}

Node *pushL(int *listyeni, int *listeski, int id, Node *root, vector<string> vek)
{
    stringstream geek(vek[1]);
    stringstream geek2(vek[2]);
    int tarih = 0;
    int kilo = 0;
    geek >> tarih;
    geek2 >> kilo;
    for (int i = 0; i < id; i++)
    {
        listeski[i] = root->getLevelUtil(root, i, 1);
    }

    root = root->insert(root, 2020 - tarih, vek[0], kilo, id);
    for (int i = 0; i < id; i++)
    {
        listyeni[i] = root->getLevelUtil(root, i, 1);
    }

    for (int i = 0; i < id; i++)
    {
        if (listeski[i] < listyeni[i])
        {
            root->pushLocation(root, 'A', i);
        }
        else if (listeski[i] == listyeni[i])
        {
            root->pushLocation(root, 'D', i);
        }
        else if (listeski[i] > listyeni[i])
        {
            root->pushLocation(root, 'Y', i);
        }
    }
    id++;
    return root;
}

vector<string> split(string target, string delim)
{
    vector<string> v;
    if (!target.empty())
    {
        string::size_type start = 0;
        do
        {
            size_t x = target.find(delim, start);
            if (x == string::npos)
                break;

            v.push_back(target.substr(start, x - start));
            start = x + delim.size();
        } while (true);

        v.push_back(target.substr(start));
    }
    return v;
}

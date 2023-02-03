#ifndef CORRECT_H
#define CORRECT_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    string data;
    struct Node* left, * right;
    Node(string data)
    {
        this->data = data;
        left = right = NULL;
    }
};

vector<string> convert(string xml);
string parents(struct Node* node, string key);
int pos(vector<string>v,string x,struct Node* tag );
string correct(string xml);
#endif // CORRECT_H

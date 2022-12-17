#ifndef FORMAT_H
#define FORMAT_H
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
void indent(string& temp, int indent);
string queue_string(queue<string>& data);
string format(string xml);
string clear(string* file);
#endif // FORMAT_H

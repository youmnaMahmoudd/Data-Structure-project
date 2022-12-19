#ifndef XML_TO_JSON_H
#define XML_TO_JSON_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>
using namespace std;
class JsonNode
{
public:
    string key;
    string value;
    vector<JsonNode *> children;
    friend class Tree;
    void setvalue(string v);
};
class Tree
{
public:
    JsonNode *root;
    string format(int depth = 0, JsonNode *parent = nullptr);
    string XMLToJson(int level = 0, JsonNode *parent = nullptr);
    void setroot(JsonNode *t);
    void addNode(JsonNode *node, JsonNode *parent);
};
Tree parse(string g);
#endif // XML_TO_JSON_H

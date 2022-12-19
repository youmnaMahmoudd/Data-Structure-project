#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stack>
#include "Xml_to_Json.h"
using namespace std;
void Tree:: setroot(JsonNode *t)
{
    root = t;
}
void Tree ::addNode(JsonNode *node, JsonNode *parent)
{
    if (parent == nullptr)
    {
        parent = root;
    }
    parent->children.push_back(node);
}
Tree parse(string xml)
{
    Tree data;
    stack<JsonNode *> holdsParent;
    string roottag;
    int idx1 = 0, idx2=0;
    idx1 = xml.find("<", idx1);
    idx2 = xml.find(">", idx1);
    roottag = xml.substr(idx1 + 1, idx2 - idx1 - 1);
    JsonNode *root = new JsonNode;
    JsonNode *node = new JsonNode;
    node->key = roottag;
    data.setroot(root);
    data.addNode(node, root);
    idx1 = xml.find("<", idx2);
    idx2 = xml.find(">", idx1);
    JsonNode *parent = node;
    while (xml.find("<", idx2) != -1)
    {
        if (xml.substr(idx1 + 1, 1) != "/")
        {
            JsonNode *newnode = new JsonNode;
            newnode->key = xml.substr(idx1 + 1, idx2 - idx1 - 1);
            idx1 = xml.find("<", idx2);
            data.addNode(newnode, parent);
            if (idx1 != -1)
            {
                string v = xml.substr(idx2 + 1, idx1 - idx2 - 1);

                newnode->value = v;
                if (xml.substr(idx1 + 1, 1) != "/")
                {
                    holdsParent.push(parent);
                    parent = newnode;
                }
            }
            idx2 = xml.find(">", idx1);
        }
        if (xml.substr(idx1 + 1, 1) == "/")
        {
            idx1 = xml.find("<", idx2);
            idx2 = xml.find(">", idx1);
            if (idx1 != -1)
            {
                if (xml.substr(idx1 + 1, 1) == "/")
                {
                    if (!holdsParent.empty())
                    {
                        parent = holdsParent.top();
                        holdsParent.pop();
                    }
                }
            }
        }
    }
    return data;
}
string Tree ::XMLToJson(int level , JsonNode *parent )
{
    string S;
    string json = "";
    if (parent == nullptr)
    {
        parent = root;
        level = 0;
    }

    for (int i = 0; i < parent->children.size(); ++i)
    {
        JsonNode *node = parent->children[i]; // creating poienters to children of the parent node
        string Spacing = "\t";
        for (int i = 0; i < level; ++i)
        {

            Spacing += "\t";
        }
        json += Spacing + "\"" + node->key + "\": "; //"class":

        if (node->children.size() > 0)
        {
            json += XMLToJson(level + 1, node);
            if (i == parent->children.size() - 1)
            {
                json += "\t"; // no action
            }
            else
            {
                json += ",\n";
            }

        }
        else
        { // if it is leaf node
            if (i == parent->children.size() - 1)
            { // if last node in its level
                json += "\"" + node->value + "\"";
            }
            else
            {
                json += "\"" + node->value + "\""; //"1"
                json += ",\n";
            }
        }
        S = Spacing;
    }
    string x = "\t";
    return "{\n" + json + "\n" + S + "}";
}
//int main()
//{
//    string text;
//    string xml="";
//    vector<string> line;
//    while (getline(cin, text)) {
//        if (text.empty())break;
//        else {
//            line.push_back(text);
//            xml+=text;
//        }
//    }
//    Tree t =parse(xml);
//    string sr = t.XMLToJson();
//    cout<<sr;
//}

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <math.h>

using namespace std;

struct minHeapNode
{

    char c;
    int freq;
    minHeapNode *left;
    minHeapNode *right;

};

struct compare
{

    bool operator()(minHeapNode* l, minHeapNode* r)
    {
        return l->freq > r->freq;
    }

};

minHeapNode* root;
minHeapNode* getNode(char c, int freq, minHeapNode* left, minHeapNode* right);


void encode(minHeapNode* root, string s , map<char, string> &huffmanCode);


string HuffmanCoding(string text);


minHeapNode* getNode(char c, int freq, minHeapNode* left, minHeapNode* right)
{
    minHeapNode* node = new minHeapNode();

    node->c = c;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}



void encode(minHeapNode* root, string s , map<char, string> &huffmanCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->c] = s;
    }

    encode(root->left, s + "0", huffmanCode);
    encode(root->right, s + "1", huffmanCode);
}


string decode(minHeapNode* root , string s)
{
    string decode = "";
    minHeapNode* temp = root;
    for (int i=0;i<s.size();i++)
    {
        if (s[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;

        if (!(temp->left && temp->right))
        {
            decode += temp->c;
            temp = root;
        }
    }
    return decode;
}
minHeapNode* root1;
string compress(string text)
{
    map<char, int> freq_arr;

    int compvalue =0;

    for(size_t i=0; i<text.length(); i++)
    {
        char ch = text[i];
        freq_arr[ch] += 1;
    }

    // minheap
    priority_queue<minHeapNode*, vector<minHeapNode*>, compare> perQUEUE;


    for (auto pair: freq_arr) {
        perQUEUE.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (perQUEUE.size() != 1)
    {

        minHeapNode *left = perQUEUE.top();
        perQUEUE.pop();
        minHeapNode *right = perQUEUE.top();
        perQUEUE.pop();

        int sum = left->freq + right->freq;
        perQUEUE.push(getNode('\0', sum, left, right));
    }


     root1 = perQUEUE.top();

    string output="" ;
    string encodedStr;

        map<char, string> huffmanCode;
        encode(root1, "", huffmanCode);
        for(char i: text){
            encodedStr += huffmanCode[i];
        }
        output += encodedStr;

    return output;

}

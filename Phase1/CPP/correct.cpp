#include<iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <bitset>
#include <map>
#include <stack>
#include <cmath>
#include <set>
#include<cstdio>
#include<cstring>
#include <cctype>
#include <cstdio>
#include <list>
#include <format.h>

#define IOS ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define ll long long
#define MAXsize 222

#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define N 100005

#include <string>
#include <locale>


struct Node {
    string data;
    struct Node* left, * right;
    Node(string data)
    {
        this->data = data;
        left = right = NULL;
    }
};

vector<string> convert(string xml)
{
    xml= clear(&xml);

    vector<string> data;

    for (int i = 0; i < xml.size(); i++)
    {
        string temp = "";
        if (xml[i] == '<')
        {

            for (; xml[i] != '>'; i++)
                temp += xml[i];
            temp += xml[i];
            if(temp[0] != ' ' && temp[1] != ' ')

                data.push_back(temp);

        }
        else
        {
            for (; xml[i] != '<'; i++)
            {
                if (xml[i] == '\t' || xml[i] == '\n' || (xml[i] == ' ' && xml[i + 1] == ' ') || (xml[i] == ' ' && xml[i + 1] == '<')) {

                    while(xml[i+1]==' '){
                        i++;
                    }

                    continue;
                }
                else
                    temp += xml[i];
            }

            i--;
            data.push_back(temp);
        }
    }
    return data;
}


string parents(struct Node* node, string key)
{
    if(key=="name")return "user";
    if (node == NULL)
        return "NOO";

    if (node->left != NULL && node->left->data == key)
        return node->data;
    if (node->right != NULL && node->right->data == key)
        return node->data;
    string res1 = parents(node->left, key);
    string res2 = parents(node->right, key);
    if(res2=="followers")return res2;
    return res1;

}
int pos(vector<string>v,string x,struct Node* tag ){

    int i=0;
    for(i=v.size()-1;i>=0;i--){
        string s1;
        if (v[i][0] == '<')
        {
            int loc = v[i].find('>', 0);
            if (loc != -1)
            {
                if (v[i][1] == '/'){
                    s1 = v[i].substr( 2, loc - 2);

                    if(parents(tag, s1)==x)return i;
                }}
        }

    }
    return 0;

}
string correct(string xml){
    vector<string> line=convert(xml);
    struct Node* tag = new Node("users");
    tag->left = new Node("user");
    tag->left->left = new Node("posts");
    tag->left->left->left = new Node("post");
    tag->left->left->left->left = new Node("topics");
    tag->left->left->left->right = new Node("body");
    tag->left->left->left->left->left = new Node("topic");
    tag->left->right = new Node("followers");
    tag->left->right->right = new Node("follower");

    stack<string> s;
    string message="";
    vector<string> msg;
    for (int i = 0; i < line.size(); i++)
    {

        for (int j = 0; j < 1; j++)
        {
            string s1;
            if (line[i][j] == '<')
            {
                int loc = line[i].find('>', j);
                if (loc != -1)
                {
                    if (line[i][j + 1] == '/')
                    {
                        s1 = line[i].substr(j + 2, loc - j - 2);//<gg>
                        if (s1 == "name" || s1 == "id"|| s1=="body"|| s1=="topic") {

                            // msg.push_back(line[i]);
                            int a=msg.size()-1;
                            while (msg[a][0] != '<'){
                                a--;
                            };

                            msg.insert(msg.begin()+a+1,"<"+ s1 + ">");
                            msg.push_back(line[i]);


                        }
                        else {
                            if (s.empty()) continue;
                            if (s1 == s.top()) {
                                s.pop();
                                msg.push_back(line[i]);
                                break;
                            }
                            else {




                                if((s.top()==parents(tag, s1))||s.top()==parents(tag, parents(tag, s1))){

                                    int x =pos(msg,s.top(),tag);
                                    msg.insert(msg.begin()+x+1,"<"+ s1 + ">");
                                    msg.push_back(line[i]);


                                }

                            }


                        }
                    }

                    else
                    {
                        s1 = line[i].substr(j + 1, loc - j - 1);
                        if (s.empty()) {
                            if(s1=="users") {
                                s.push(s1);
                                msg.push_back(line[i]);
                                break;
                            }
                            else {
                                s.push("users");
                                s.push(s1);
                                msg.push_back("<users>");
                                msg.push_back(line[i]);
                            }
                        }
                        else {
                            string top = s.top();
                            if (s1 == "name" || s1 == "id"|| s1=="body"|| s1=="topic") {

                                msg.push_back(line[i]);
                                int a=1;
                                while (line[i + a][0] != '<') {

                                    msg.push_back(line[i+a]);
                                    a++;
                                }
                                i+=a;
                                if(line[i].substr(j + 2, loc - 1) == s1){

                                    msg.push_back("</"+ s1 + ">");
                                    break;
                                }
                                else{
                                    msg.push_back("</"+ s1 + ">");
                                    i--;
                                    break;
                                }
                            }
                            else if (parents(tag, top) == parents(tag, s1)) {
                                msg.push_back( "</" + top + ">");

                                s.pop();
                                msg.push_back(line[i]);

                                s.push(s1);
                                break;
                            }

                            else {
                                msg.push_back(line[i]);

                                s.push(s1);
                                break;
                            }
                        }
                    }


                }
            }
            else {
                msg.push_back(line[i]);

                break;
            }
        }

    }
    while (!s.empty()) {
        msg.push_back("</" + s.top() + ">");
        s.pop();
    }
    for(auto x:msg) {
        message+=x+"\n";
    }
    return message;
}

//int main() {
//	// your code goes here
//	return 0;
//}

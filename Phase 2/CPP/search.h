#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
class Post {
public:
    bool enter=false;

    string body= "";
    vector<string> topics =vector<string>{};

    void setbody(string l){
        body+=l;
    }
    void clear(){
        body= "";
        topics =vector<string>{};
        enter=false;
    }
};
class User {
public:
    int id = -1;
    string name = "";
    vector<Post> posts = vector<Post>{};
};
string clear(string* file);
bool isSubString(string target, string base);
string searchPosts(string keyWord,int count);
string search(string xml, string keyword);
int xmlprase(vector<string> x);
#endif // SEARCH_H

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
#include <correct.cpp>
#include <minify.h>
#include <search.h>

#define IOS ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define ll long long
#define MAXsize 222

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

bool isSubString(string target, string base)
{
    int targetIndex = 0;
    if (target.size() > base.size())
        return 0;
    for (int i = 0; i < base.size() - target.size() + 1; ++i) {
        if (base[i] == target[targetIndex]) {
            for (int j = i; targetIndex < target.size(); ++j) {
                if (base[j] != target[targetIndex]) {
                    targetIndex = 0;
                    i = j;
                    break;
                }
                if (base[j] == target[targetIndex] && targetIndex == target.size() - 1)
                    return 1;
                ++targetIndex;
            }
        }
    }
    return 0;
}
User users[10];
string searchPosts(string keyWord,int count)
{
    int postNumber = 1;
    string postList;
    for (int i=0;i<count;i++) {
        for (auto p : users[i].posts) { //looping through the body of all posts of a user
            if (isSubString(keyWord, p.body)) {
                postList.append("Post #" + to_string(postNumber++) +  ":\n" + "BY: " + users[i].name +" (" +
                                to_string(users[i].id+1) + ")" + "\n" + p.body + "\n_________\n");
                 break;
            }
            for (auto t : p.topics)
                if (isSubString(keyWord, t)) {
                    postList.append("Post #" + to_string(postNumber++) + ":\n"  + "BY: " + users[i].name +" (" +
                                    to_string(users[i].id+1) + ")" + "\n" + p.body + "\n_________\n");
                    break;
                }
        }
    }
    if (postList.empty())
        postList = "NO POSTS FOUND :(";
    return postList;
}
int xmlprase(vector<string> x){

    int current_id;
    int count=0;
    int j=-1;
    if(users[0].id==-1){
        for(int i=0;i<(int)x.size();i++){
            bool en=true;

            if (x[i].find("<user>") != string::npos) {
                if(en) {
                    j++;
                    en =false;
                }
                while (x[i].find("</user>") == string::npos) {

                    if (x[i++].find("<user>") != string::npos && x[i].find("<id>") != string::npos) {
                        current_id=x[++i][0]-'0' - 1;
                        users[j].id=current_id;
                        i++;
                        if(x[++i].find("<name>")!=string::npos){

                            users[j].name=x[++i];
                            i++;
                        }

                        count++;
                    }

                    if (x[i].find("<posts>") != string::npos){
                        while (x[i++].find("</posts>") == string::npos) {
                            Post p;
                            if((x[i-1].find("<post>")!=string::npos)||(x[i].find("<post>")!=string::npos)){
                                while (x[i++].find("</post>") == string::npos){
                                    p.enter=true;
                                    if (x[i].find("<body>") != string::npos) {
                                        p.body+=x[++i];

                                    }
                                    if (x[i].find("<topics>") != string::npos) {
                                        while(x[i].find("</topics>") == string::npos){
                                            if(x[++i].find("<topic>")!=string::npos){
                                                i++;
                                                p.topics.push_back(x[i]);
                                            }
                                        }
                                    }
                                }}
                            if(p.enter){
                                users[j].posts.push_back(p);
                                p.clear();
                                i--;
                            }

                        }
                    }

                }
            }

        }
    }
    else{
        for(auto x:users){
            if(x.id!=-1)count++;
        }
    }

    return count;
}

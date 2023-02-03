#include<iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <bitset>
#include <map>
#include<cstring>
#include <cctype>
#include <cstdio>
#include <list>
#include <correct.h>
#include <netAnalysis.h>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);

#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int arr[50][50]={0};


//The one with the highest followings
int mA(int arr[][50],int count){
    map<int,int> mp;
    int id=0,mx=0;
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            mp[i]+=arr[i][j];
        }

    }

    for(auto i:mp)
    {
        if(i.second>mx) mx=i.second,id=i.first+1;
    }
    return id;
}
//The one with the highest followers
int mI(int arr[][50],int count){
    map<int,int> mp;
    int id=0,mx=0;
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            mp[i]+=arr[j][i];
        }

    }
    for(auto i:mp)
    {
        if(i.second>mx) mx=i.second,id=i.first+1;
    }
    return id;
}
vector<int> mF(int arr[][50],int id1,int id2,int count){
    vector<int> mutual;

    for(int i=0;i<count;i++){
        if(arr[id1-1][i]==arr[id2-1][i]&&(arr[id2-1][i]==1)) {
            cout<<i;
            mutual.push_back(i+1);
        }
    }
    return mutual;
}

vector<int> sF(int arr[][50],int id1,int count) {
    vector<int> followers, suggest;
    map<int, int> mp;
    mp[id1-1] =1;
    for (int i = 0; i < count; i++) {
        if (arr[id1 - 1][i]) {
            followers.push_back(i);
            mp[i] = 1;
        }
    }
    int l = followers.size();
    for (int i = 0; i < l; i++) {
        int f1 = followers[i];
        for (int j = 0; j < count; ++j) {
            if (arr[f1][j] && !mp[j]) {
                suggest.push_back(j + 1);
                mp[j] = 1;
            }
        }
    }
    return suggest;
}

map<int,string> NA(vector<string> x){
    map<int,string>m;
    int follower,current_id;
    int count=0;

    int j=-1;
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
                    i++;
                    if(x[++i].find("<name>")!=string::npos){
                         i++;
                        m[current_id]=x[i];
                        i++;
                    }
                    count++;
                }

                if (x[i].find("<followers>") != string::npos) {
                    while (x[i++].find("</followers>") == string::npos) {
                        if (x[i].find("<id>") != string::npos) {
                            //  index = x[i].find('>') + 1;
                            follower = x[++i][0] - '0' - 1;
                            i++;
                            arr[current_id][follower]= 1;
                        }
                    }
                }
            }
        }}


return m;
    }
string mostActive(string xml){
    vector<string> ans=convert(xml);
    map<int,string> m =NA(ans);
   int id=mA(arr,m.size());
   string temp= "The most Active user:\n";
          temp+= "ID: ";
          temp+= to_string(id);
          temp+="\n";
          temp+= "Name: ";
          temp+=m[id-1];
          return temp;
}
string mostInfluencer(string xml){
    vector<string> ans=convert(xml);
    map<int,string> m =NA(ans);
    int id=mI(arr,m.size());
    string temp="The most influencer :\n";
    temp.append( "ID: "+to_string(id)+"\n"+"Name: "+m[id-1]);
    return temp;
}
string mutualFriends(int id1, int id2, string xml){
    vector<string> ans=convert(xml);
    map<int,string> m =NA(ans);
    vector<int> ids=mF(arr,id1,id2,m.size());
//    if(m[id1]=="")            return "USER 1 DOES NOT EXIST ON THE NETWORK";
//    if(m[id2]=="")            return "USER 2 DOES NOT EXIST ON THE NETWORK";
    if(ids.empty())return "NO MUTUAL FOLLOWERS FOUND";
    string sen="The mutual friends between ";
    sen.append(m[id1-1]+" and "+m[id2-1]+":\n");
    for(auto x:ids){
      sen.append("- "+m[x-1]+" ("+ to_string(x)+")\n");
    }
    return sen;
}
string suggestFriends(int id, string xml){
    vector<string> ans=convert(xml);
    map<int,string> m =NA(ans);
    vector<int> ids=sF(arr,id,m.size());
    if(m[id]=="")            return "This user doesn't exist on the network.";
    if(ids.empty())return "No recommendations found.";
    string sen="The list of recommended to follow: \n ";
    for(auto x:ids){
        sen.append("- "+m[x-1]+" ("+ to_string(x)+")\n");
    }
    return sen;
}





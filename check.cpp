#include<iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <deque>
#include <stack>
#include <cmath>
#include <numeric>
#include<cstdio>
#include<cstring>
#include <cctype>
#include <cstdio>
#include <list>
//#include <check.h>
#define IOS ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
#define ll long long
#define MAXsize 222
#define mod 1000000007
#define MOD 1000000007
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#define N 100005

#include <string>
#include <locale>

using namespace std;

#define loop(a, b) for(int i=a;i<b;i++)
using namespace std;

string check_error(string xml) {
    bool f = true;
    string text;
    string err="";
    vector<string> line;
    vector<string> error;
    int n = 0;

    int cnt = 0;    //to get the lines
    stack<string> s;  //I used pair to detect the lines to be able to mention them if there is an error
    deque<string> q;
    bool found = false;
    //Checking for the file

        cnt++;//tells me which line I am in
        for (int j = 0; j < xml.length(); j++) {
            string s1="";
            if (xml[j] == '<') {



                    if (xml[j + 1] == '/') // check if it is a cloasing tag
                    {
                        if(xml[j + 1] == '/')
                        {
                            j+=2;
                            while(xml[j]!='>') s1+=xml[j],j++;
                        }
                        found = false;

                        //case 1 (top of stack equals to tag)
                        if(!s.empty() && s.top()==s1)
                        {
                            s.pop();
                        }

                            //case 2 (stack not empty but the top of stack not equals to tag)
                        else if((!s.empty() && s.top()!=s1))
                        {
                            while((!s.empty() && s.top()!=s1))
                            {
                                q.push_back(s.top());
                                s.pop();
                                if(!s.empty() && s.top()==s1)
                                {
                                    s.pop();
                                    found= true;
                                    break;
                                }
                            }
                            if(s.empty() && !found)
                            {
                                if(q.empty())
                                {
                                    err+= "opening tag of "+s1+" not found:(";
                                    err+='\n';
                                    error.push_back("opening tag of "+s1+" not found:(");
                                }

                                else
                                {
                                    while(!q.empty() && q.front()!=s1)
                                    {
                                        s.push(q.back());
                                        q.pop_back();
                                        if(!q.empty()&& q.back()==s1)
                                        {
                                            q.pop_back();
                                            found = true;
                                            break;
                                        }

                                    }
                                }
                                if(q.empty()&&!found)
                                {
                                    error.push_back("opening tag of "+s1+" not found");
                                    err+="opening tag of "+s1+" not found";
                                    err+='\n';
                                }

                            }
                        }

                            //case 4 (stack and deque are empty)
                        else if(s.empty() && q.empty())
                        {
                            error.push_back("opening tag of "+s1+" not found");
                            err+="opening tag of "+s1+" not found";
                            err+='\n';
                        }
                    }



                    else // check if it is a opening tag
                    {

                        j+=1;
                        while(xml[j]!='>') s1+=xml[j],j++;
                        s.push(s1);
                    }



            }
        }


    while(!s.empty())
    {
        error.push_back("closing tag of "+s.top()+" not found");
        err+="closing tag of "+s.top()+" not found";
        err+='\n';
        s.pop();
    }
    while(!q.empty())
    {
        error.push_back("closing tag of "+q.back()+" not found");
        err+="closing tag of "+q.back()+" not found";
        err+='\n';
        q.pop_back();
    }
/*
    if(error.size()==0)
     cout<<"NO ERRORS :)";
    else
    {
        for(auto x : error)
            cout<<x<<endl;
    }
     */
     if(err!="") return err;
     return "NO ERRORS";
}

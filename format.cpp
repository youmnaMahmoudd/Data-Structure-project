#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include "format.h"
#include "string"
#include <check.h>
#include <minify.cpp>

using namespace std;

string format(string xml)
{
    if (check_error(xml)=="NO ERRORS"){
        queue<string> data;
            static int indentation = 0;
            string s = clear(&xml);
            for (int i = 0; i < s.size(); i++)
            {
                string temp = "";
                if (s[i] == '<') //tag
                {
                    if (!(s[i + 1] == '/')) //opening tag
                    {
                        indent(temp, indentation);
                        for (; s[i] != '>'; i++)
                            temp += s[i];
                        temp += s[i];
                        data.push(temp);
                        indentation++;
                    }
                    else //closing tag
                    {
                        indentation--;
                        indent(temp, indentation);
                        for (; s[i] != '>'; i++)
                            temp += s[i];
                        temp += s[i];
                        data.push(temp);
                    }
                }
                else //values
                {
                    indent(temp, indentation);
                    for (; s[i] != '<'; i++)
                    {
                        temp += s[i];
                    }
                    // string result = oneline (temp);
                    i--;
                    data.push(temp);
                }
            }
            return queue_string(data);
        }
    else{
       return "Correct the errors";
    }

}
    void indent(string& temp, int indentation)
    {
        for (int j = 0; j < indentation * 4; j++)
            temp += ' ';
    }


    string queue_string(queue<string>& data) //time O(n) // space O(1)
    {
        string answer = "";
        while (!data.empty())
        {
            answer += data.front();
            answer += '\n';
            data.pop();
        }
        return answer;
    }


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include "format.h"
#include "string"

string clear(string* file)  //time O(N) //space O(1)
   {
       string output = "";
       //to clear the white spaces and remove new lines:
       size_t i = 0;
       for (; i < file->size(); i++)
       {
           if ((*file)[i] == ' ')
               continue;
           else
               break;
       }
       for (; i < file->size(); i++)
       {
           if ((*file)[i] == '\t' || (*file)[i] == '\n' || ((*file)[i] == ' ' && (*file)[i + 1] == ' ') || ((*file)[i] == ' ' && (*file)[i + 1] == '<'))
               continue;
           else
           {
               output = output + (*file)[i];
           }
       }
       string result = "";
       for (size_t j = 0; j < output.size(); j++)
       {
           if (output[j] == '<') //opening tag
           {
               for (; output[j] != '>'; j++)
               {
                   if (output[j] == ' ')
                       continue;
                   else
                       result += output[j];
               }
           }
           result += output[j];
       }
       return *file = result;
}

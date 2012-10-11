/*
  LNGut.cpp
*/

#include <LNG/LNGut.h>

using namespace std;

namespace LNGut {

string path_join(int n, ...) // string *
{
  string s;
  va_list ap;
  va_start(ap, n);
  for(int c = 0; c < n; c++){
    string *p = va_arg(ap, string *);
    if(c > 0) s += '\\';
    s += *p;
  }
  va_end(ap);
  return s;
}

};

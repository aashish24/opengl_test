#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <GL/glx.h>

using namespace std;

double string_to_double( const std::string& s )
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
}

void render () 
{
  string line;
  ifstream myfile ("triangles.c");
  if (myfile.is_open())
    {
    while ( myfile.good() )
      {
      getline (myfile,line);

      if (line.size() < 13) break;

      vector<string> strs;
      int len = line.size() - 13;
      string values = line.substr(11, len);
      boost::split(strs, values, boost::is_any_of(","));
      float dvalues[3];
      int i = 0;
      for (vector<string>::iterator it = strs.begin();
           it != strs.end();
           ++it, ++i)
        {
        dvalues[i] =  string_to_double(*it);
        }

      if (line.substr(0, 10) == "glNormal3f")
        {
        glNormal3fv(dvalues);
        }
      else
        {
        glVertex3fv(dvalues);
        }
      }
    myfile.close();
    }

  else cout << "Unable to open file";
}

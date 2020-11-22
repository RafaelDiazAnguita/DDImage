#include "DDimage.hpp"
bool read_types(vector<string> &types){
    string line;
  ifstream myfile ("allowed_types.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
        types.push_back(line);
    myfile.close();
    return true;
  }

  else cout << "Unable to open file"; 

  return false;
}

bool check_type(string name,vector<string> types){
    for (size_t i = 0; i < types.size(); i++)
    if(name.find(types[i])!=string::npos)
    return true;

    return false;
}
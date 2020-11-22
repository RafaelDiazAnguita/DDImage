#include "DDimage.hpp"

void src_list(const char *path,vector<string> &paths) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) 
    return;
   
   while ((entry = readdir(dir)) != NULL)
    if(check_type(entry->d_name))
    paths.push_back((string) path+"/"+entry->d_name);
  
   
   closedir(dir);
}

int main(int argc,char *argv[]){

    vector<string> paths;
    src_list(argv[1],paths);

    for (size_t i = 0; i < paths.size(); i++)
    {
        cout<<paths[i]<<endl;
    }
    

    return 0;
}
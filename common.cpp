#include "DDimage.hpp"

void src_list(const char *path,vector<string> &paths) {
    struct dirent *entry;
    DIR *dir = opendir(path);
   
    if (dir == NULL) 
        return;

    vector<string> types;
    read_types(types);
    
    while ((entry = readdir(dir)) != NULL)
        if(check_type(entry->d_name,types))
            paths.push_back((string) path+entry->d_name);
  
    closedir(dir);
}
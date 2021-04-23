#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>
#include <filesystem>


#include <opencv2/highgui/highgui.hpp>

using namespace std;

class Pair{
    private:
        int original_,duplicated_;

    public:
        Pair(int original, int duplicated){
            original_ = original;
            duplicated_ = duplicated;
        }

        int get_original(){return original_;}
        int get_duplicated(){return duplicated_;}

};

class DFolder{

    private:
    string path_,allowed_types_file_;
    vector<string> files_,file_types_;
    vector<DFolder> subfolders_;

    /**
     * Check if the file has the correct type
     * @param name The name of the file
     * @param types allowed types
     * @return true if its a type 
     **/
    bool check_type(string name,vector<string> types){
        for (size_t i = 0; i < types.size(); i++)
        if(name.find(types[i])!=string::npos)
        return true;

        return false;
    }
    /**
     * Check if the vector has the element
     * @param index vector
     * @param x element
     * @return true if the vector has the element
     **/
    bool has(vector <int> index,int x){
        for (size_t i = 0; i < index.size(); i++)
            if(index[i]==x)
            return true;
        return false;
    }
    /**
     * Find duplicate elements
     * @param images images vector
     * @return index vector for remove
     **/
    vector<int> find_duplicate(vector<Pair> duplicate_sizes)
    {
        vector<int> index;
        
        for (float i = 0; i < duplicate_sizes.size(); i++)
        {
            if(i == duplicate_sizes.size()-1)
                int l=1;

            cv::Mat img1 = cv::imread(files_[duplicate_sizes[i].get_original()], cv::IMREAD_UNCHANGED);
            cv::Mat img2 = cv::imread(files_[duplicate_sizes[i].get_original()], cv::IMREAD_UNCHANGED);
            if(equal(img1,img2)){
                index.push_back(duplicate_sizes[i].get_duplicated());
            }
            
            float percent = i/(float)duplicate_sizes.size()*100;
            cout<<"\r"<<"% Completed -> "<<percent;
            
        }

        
        return index;
    }

    /**
     * Find duplicated sizes
     **/
    vector<Pair> find_duplicate_size()
    {
        vector<int> index;
        vector<Pair> pairs;
        for (size_t i = 0; i < files_.size(); i++)
        for (size_t j = i+1; j < files_.size(); j++){   
                

            if( !has(index,j) && std::filesystem::file_size(files_[i]) == std::filesystem::file_size(files_[j]) ){
                index.push_back(j);
                pairs.push_back(Pair(i,j));
            }
                    
        }
        
        return pairs;
    }
    public:

    /**
     * Create a DFolder Object
     * @param path path of the folder
     * @param allowed_types_file path to the allowed types file
     **/
    DFolder(string path,string allowed_types_file){
        if(path.at(path.length()-1)!='/')
            path_=path+"/";
        else
            path_=path; 
        allowed_types_file_=allowed_types_file;
        read_types(allowed_types_file_);
        read_data(path_);
        get_data();
    }

    /**
     *  Read Allowed types from file 
     *  @param path path to the file
     **/
    void read_types(string path){
        string line;
        ifstream myfile (path);
        if (myfile.is_open())
        {
            while ( getline (myfile,line) )
                file_types_.push_back(line);
            myfile.close();
        }
        else{
            cout << "Unable to open file"; 
            exit(-1);
        }
    }

    /**
     * Get the files and subfolders
     * @param path path to the folder
     */
    void read_data(string path) {
        //read paths
        struct dirent *entry;
        DIR *dir = opendir(path.c_str());
    
        if (dir == NULL) 
            return;
        
        while ((entry = readdir(dir)) != NULL){
            //files
            if(check_type(entry->d_name,file_types_)){
                cout<<"\r";
                files_.push_back((string) path+entry->d_name);
                cout<<"Reading file: "+ (string) path+entry->d_name;
            }
            
                
            //folders
            string name=entry->d_name;
            if(name.find(".")==string::npos)
                subfolders_.push_back(DFolder((string) path+entry->d_name,allowed_types_file_));
        }
        cout<<endl;
        closedir(dir);
    }

    /**
     * Check if two images are equal
     * @param a image a
     * @param b image b
     * @return true if are equal
     **/
    bool equal(const cv::Mat & a, const cv::Mat & b)
    {
        if ( (a.rows != b.rows) || (a.cols != b.cols) )
            return false;
        cv::Mat diff;
        cv::absdiff(a,b,diff);
        if(cv::sum( diff )[0]==0 && cv::sum( diff )[1]== 0 && cv::sum( diff )[2] == 0)
            return true;

        return false;
    }

    /**
     * Add to the files_ vector the subfolders files
     * @param super_files the up folder files_ vector 
     **/
    vector<string> get_data(){
        for (size_t i = 0; i < subfolders_.size(); i++)
        {
            vector<string> aux=subfolders_[i].get_data();
            for (size_t j = 0; j < aux.size(); j++)
                files_.push_back(aux[j]);
        }
        return files_;
    }
    /**
     * Remove duplicate elements
     **/
    void remove_duplicate(){
        cout<<"Finding duplicates... This may take some time, wait please."<<endl;
        vector<Pair> duplicate_sizes = find_duplicate_size();
        vector<int> duplicate_images = find_duplicate(duplicate_sizes);
        for (size_t i = 0; i < duplicate_images.size(); i++){
            cout<<"\r";
            cout << "Removing file: "+ files_[i];
            remove(files_[duplicate_images[i]].c_str());
        }
        cout<<endl;
        cout<<"Finished."<<endl;
    }
    

};
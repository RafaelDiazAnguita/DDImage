#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;

class DFolder{

    private:
    string path_,allowed_types_file_;
    vector<string> files_,folders_,file_types_;
    vector<cv::Mat> images_;
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
    vector<int> find_duplicate(vector<cv::Mat> &images)
    {
        vector<int> index;
        for (size_t i = 0; i < images.size(); i++)
        for (size_t j = 0; j < images.size(); j++)
        {
            if(equal(images[i],images[j]) && j > i && !has(index,j))
            index.push_back(j);
        }
        return index;
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
            if(check_type(entry->d_name,file_types_))
                files_.push_back((string) path+entry->d_name);
            //folders
            string name=entry->d_name;
            if(name.find(".")==string::npos)
                subfolders_.push_back(DFolder((string) path+entry->d_name,allowed_types_file_));
        }
        closedir(dir);
    }
    /**
     *PushBack cv::Mats to images vector 
     **/
    void read_images(){
        for (size_t i = 0; i < files_.size(); i++)
            images_.push_back(cv::imread(files_[i], cv::IMREAD_UNCHANGED)); 
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
        read_images();
        vector<int> duplicates=find_duplicate(images_);
        for (size_t i = 0; i < duplicates.size(); i++)
            remove(files_[duplicates[i]].c_str());
    }

};
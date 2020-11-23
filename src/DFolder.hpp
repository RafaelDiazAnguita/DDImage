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
    string path_;
    vector<string> files_,subfolders_,file_types_;
    vector<cv::Mat> images_;

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
        read_types(allowed_types_file);
        get_files(path);
        get_images();
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
     * Get the path of the files inside the folder
     * @param path path to the folder
     */
    void get_files(string path) {
        //read paths
        struct dirent *entry;
        DIR *dir = opendir(path.c_str());
    
        if (dir == NULL) 
            return;
        
        while ((entry = readdir(dir)) != NULL){
            if(check_type(entry->d_name,file_types_))
                files_.push_back((string) path+entry->d_name);
        }
        closedir(dir);
    }

    /**
     * Get the files that are images(mainly) whit the allowed types
     **/
    void get_images(){
        //save in cv::Mat vector
        for (size_t i = 0; i < files_.size(); i++)
        {
            //read image i
            cv::Mat img = cv::imread(files_[i], cv::IMREAD_UNCHANGED);
            if (img.empty())
            {
                std::cerr << "Error: could not open input image '" << files_[i]
                        << "'." << std::endl;
                exit(-1);
            }
            images_.push_back(img);
        }
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
     * Remove duplicate elements
     **/
    void remove_duplicate(){
        vector<int> duplicates=find_duplicate(images_);
        for (size_t i = 0; i < duplicates.size(); i++)
        {
            remove(files_[duplicates[i]].c_str());
        }
    }

};
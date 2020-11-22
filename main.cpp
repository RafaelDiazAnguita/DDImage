#include "DDimage.hpp"

int main(int argc,char *argv[]){

    //Getting paths to allowed images
    vector<string> paths;
    src_list(argv[1],paths);

    //open images
    vector<cv::Mat> images;
    for (size_t i = 0; i < paths.size(); i++)
    {
        //read image i
        cv::Mat img = cv::imread(paths[i], cv::IMREAD_UNCHANGED);
        if (img.empty())
        {
            std::cerr << "Error: could not open input image '" << paths[i]
                      << "'." << std::endl;
            return EXIT_FAILURE;
        }
        images.push_back(img);
    }
    //find the index of duplicate elements
    vector<int> duplicates=find_duplicate(images,images.size());
    //remove
    for (size_t i = 0; i < duplicates.size(); i++)
    {
        remove(paths[duplicates[i]].c_str());
    }

    return 0;
}
#include "DDimage.hpp"

bool has(vector <int> index,int x){
    for (size_t i = 0; i < index.size(); i++)
        if(index[i]==x)
        return true;
    return false;
}
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
vector<int> find_duplicate(vector<cv::Mat> &images, int n)
{
    vector<int> index;
    for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
    {
        if(equal(images[i],images[j]) && j > i && !has(index,j))
        index.push_back(j);
    }
    return index;
}
#ifndef DD_IMAGE_H
#define DD_IMAGE_H


#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace std;


bool read_types(vector<string> &types);
bool check_type(string name);

#endif 
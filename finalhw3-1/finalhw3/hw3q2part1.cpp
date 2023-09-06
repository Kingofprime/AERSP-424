
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc.hpp>
#include <iostream>
/*i changed the imread function
* opencv/sources/modules/imgcodecs/src/loadsave.cpp
*/
using namespace cv;
using namespace std;
int main() {
	string image_path = "a.jpg";
	Mat image = imread(image_path, IMREAD_COLOR);
	resize(image, image, { 500,500 }, 0, 0, cv::INTER_NEAREST);
	imshow("Image", image);
	waitKey(0);
	return 0;
}
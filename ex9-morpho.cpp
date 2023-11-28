#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{

	if (argc < 2){
		argv[1] = ("bstring.jpg"); //default画像

    }

    char* filename = argv[1];

    cv::Mat srcImage = cv::imread(filename);
    cv::Mat dstImage = srcImage;
    cv::Mat buffertImage;



    while(true){
        string cmd;
        cout << "Enter ['e'(erode) | 'd'(dilate) | 'r'(reset) | 'b'(back) | 's'(save)] >";
        cin >> cmd;

        cout << cmd;

        cv::Mat tempImage;

        if(cmd == "e"){
            /* code */
            cv::erode(dstImage, tempImage, cv::Mat());
            dstImage = tempImage;
        }else if(cmd == "d"){
            cv::dilate(dstImage, tempImage, cv::Mat());
            dstImage = tempImage;
        }else if(cmd == "r"){
            dstImage = srcImage;
        }else if(cmd == "b"){
            dstImage = buffertImage;
        }else if(cmd == "s"){
            
            cv::imwrite("cstring.jpg", dstImage);
        }
        cv::imshow("cstring", srcImage);

        buffertImage = dstImage;


    }
    




	return 0;
}

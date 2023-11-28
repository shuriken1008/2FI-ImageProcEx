#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 均等量子化法による色の制限
void posterize64(Mat& image) {
    // BGRの各チャネルを0～255を均等に4分割する
    int levels = 4;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            Vec3b& pixel = image.at<Vec3b>(i, j);
            pixel[0] = pixel[0] / levels * levels + levels / 2;
            pixel[1] = pixel[1] / levels * levels + levels / 2;
            pixel[2] = pixel[2] / levels * levels + levels / 2;
        }
    }
}

int main(int argc, char** argv){
	if (argc < 2)   
	{
		argv[1] = "sample.jpg";  //引数省略時のdefault設定 
	}

    cv::Mat inputImage = cv::imread(argv[1]);

    if (image.empty()) {
        cout << "画像が読み込めません" << endl;
        return -1;
    }

    // 均等量子化法による色の制限
    posterize64(inputImage);

    // 画像の表示
    imshow("output Image", inputImage);
    waitKey(0);

    return 0;
}

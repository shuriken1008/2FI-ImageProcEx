#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 均等量子化法による色の制限
void posterizeAny(Mat& image, int levels) {
    if (levels == 1) {
        // 分割数が1の場合は分割を行わない
        return;
    }

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
    char* input;

    if (argc == 2){
        input = "sample.jpg";
    }

    else if (argc != 3) {
        cout << "コマンド: " << argv[0] << " <入力画像> <分割数1~128>" << endl;
        return -1;
    }

    int levels = atoi(argv[2]);
    if (levels < 1 || levels > 128) {
        cout << "分割数は1から128で指定してください" << endl;
        return -1;
    }    input = argv[1];

    // 画像の読み込み
    Mat image = imread(argv[1]);
    cv::Mat inputImage = cv::imread(input);


    // 均等量子化法による色の制限
    posterizeAny(inputImage, levels);

    // 画像の表示
    imshow("output Image", inputImage);
    waitKey(0);

    return 0;
}

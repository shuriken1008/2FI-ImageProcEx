#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 画像の読み込み
    cv::Mat image = cv::imread("cskeleton.jpg");

    // 画像が正しく読み込まれたか確認
    if (image.empty()) {
        std::cerr << "Error: Could not open or find the image" << std::endl;
        return -1;
    }

    // 画像の行数と列数を取得
    int rows = image.rows;
    int cols = image.cols;

    // 画素数カウンター
    int pixelCount = 0;

    // 各画素の明るさを調べて画素数をカウント
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // 画素の明るさを取得
            uchar pixelValue = image.at<uchar>(i, j);
            if (pixelValue > 0) {
                pixelCount++;
            }
        }
    }

    // 画素数の出力
    std::cout << "Pixel count in the BINARY image: " << pixelCount << std::endl;

    return 0;
}

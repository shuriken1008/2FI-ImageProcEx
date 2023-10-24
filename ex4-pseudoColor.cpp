#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

int pseudoColor(char* name) {
    std::string fileName;
    fileName.assign(name);
    // 画像の読み込み
    cv::Mat inputImage = cv::imread(name);

    if (inputImage.empty()) {
        std::cerr << "画像を読み込めませんでした" << std::endl;
        return -1;
    }

    // グレースケール化
    cv::Mat grayscaleImage;
    cv::cvtColor(inputImage, grayscaleImage, cv::COLOR_BGR2GRAY);

    // BGRそれぞれのトーンカーブを適用
    cv::Mat bgrChannels[3];
    cv::split(inputImage, bgrChannels);

    // トーンカーブを適用する関数を定義
    auto applyToneCurve = [](cv::Mat& channel, const std::vector<int>& curve) {
        for (int i = 0; i < channel.rows; i++) {
            for (int j = 0; j < channel.cols; j++) {
                int pixelValue = channel.at<uchar>(i, j);
                channel.at<uchar>(i, j) = static_cast<uchar>(curve[pixelValue]);
            }
        }
    };

    std::vector<int> bCurve(256), gCurve(256), rCurve(256);

    // BGRそれぞれのトーンカーブを設定
    for (int i = 0; i < 256; i++) {
        if(i<64){
            bCurve[i] = 255;
            gCurve[i] = 4 * gCurve[i];;
            rCurve[i] = 0;
        }else if(i<128){
            bCurve[i] = -4 * bCurve[i] +512;
            gCurve[i] = 255;
            rCurve[i] = 0;
        }else if(i<192){
            bCurve[i] = 0;
            gCurve[i] = 255;
            rCurve[i] = 4 * rCurve[i];
        }else{
            bCurve[i] = 0;
            gCurve[i] = -4 * gCurve[i];
            rCurve[i] = 255;
        }
    }

    applyToneCurve(bgrChannels[0], bCurve);
    applyToneCurve(bgrChannels[1], gCurve);
    applyToneCurve(bgrChannels[2], rCurve);

    // トーンカーブを適用したBGRチャネルを合成して疑似カラー画像を生成
    cv::Mat pseudoColorImage;
    cv::merge(bgrChannels, 3, pseudoColorImage);

    // 画像を表示
    cv::imshow("Pseudo Color Image", pseudoColorImage);
    // 課題提出用：画像保存
    std::string grayFileName = fileName + "-gray.jpg";
    std::string pseudoColorFileName = fileName + "-pseudoColor.jpg"; 
    cv::imwrite(pseudoColorFileName, pseudoColorImage);
    cv::imwrite(grayFileName, grayscaleImage);
    cv::waitKey(0);

    return 0;
}


int main(int argc, char** argv){
	if (argc < 2)   
	{
		argv[1] = "sample.jpg";  //引数省略時のdefault設定 
	}
	pseudoColor(argv[1]);
	return 0;
}

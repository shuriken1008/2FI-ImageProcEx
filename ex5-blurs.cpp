#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//入力画像に平均化フィルタ，および，ガウシアンフィルタを適用した画像を表示
//ただし，平滑化カーネルサイズはそれぞれ3 と7 の2種類とし，合計4画像を表示
void blurs(char* name, int ksize){
	cv::Mat orgImage = cv::imread(name);	//画像の読み込み
	cv::Mat blurredImage;
	cv::Mat gaussianBlurredImage;
	//RGBチャンネル配列
	cv::Mat matArray[3];

	if (orgImage.empty())	//画像の読み込みに失敗したら終了
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}
	
	cv::blur(orgImage, blurredImage, Size(3,3));
	/*
	
	cv::GaussianBlur(orgImage, gaussianBlurredImage, cv::Size(3,3), 2, 0);

	//平滑化
	cv::imshow("blur", blurredImage);	
	//ガウシアンフィルタ
	cv::imshow("gaussian", gaussianBlurredImage);
	
	*/

	

}

int main(int argc, char** argv){
	if (argc < 2)   
	{
		argv[1] = "sample.jpg";  //引数省略時のdefault設定 
	}
		
	blurs(argv[1], 3);
	return 0;
}
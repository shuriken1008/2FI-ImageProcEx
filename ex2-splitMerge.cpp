#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

//緑色のみチャンネル反転した画像を表示
void reverseGreen(char* name){
	cv::Mat input = cv::imread(name);	//画像の読み込み
	cv::Mat output;

	//RGBチャンネル配列
	cv::Mat matArray[3];

	if (input.empty())	//画像の読み込みに失敗したら終了
	{
		cout << "画像ファイルを読み込めませんでした．" << endl;
		return;
	}

	//チャンネル毎に分離
	cv::split(input, matArray);
	//緑のみ反転
	matArray[2] = ~matArray[2];
    //各チャンネルを画像に統合
	cv::merge(matArray, 3, output);

    //表示
	cv::imshow("Input", input);	//入力画像
	cv::imshow("Output", output); //出力画像
    cv::imwrite("ex2-4-out.jpg", output); //提出用(画像の保存)
	cv::waitKey();
}

int main(int argc, char** argv){
	if (argc < 2)   
	{
		argv[1] = "sample.jpg";  //引数省略時のdefault設定 
	}
		
	reverseGreen(argv[1]);
	return 0;
}
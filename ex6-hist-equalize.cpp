#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;




// 単色画像のヒストグラム平坦化によるコントラスト調整
cv::Mat singleColorHistEqualize(cv::Mat src)
{
	// cv::imshow("Input", src);

	// ルックアップテーブル
	// 今回は1つのルックアップテーブルの中でヒストグラムや累積ヒストグラムの計算を完結させる
	int LUT[256] = {};

	// (1) 画素値のヒストグラムを算出 
	for (int i = 0; i < src.rows; i++)
		for (int j = 0; j < src.cols; j++)
			LUT[src.ptr(i, j)[0]]++;

	 // (2) (1)のヒストグラムから累積ヒストグラムを算出 
	for (int i = 1; i < 256; i++)
		LUT[i] += LUT[i - 1];

	// (3) 累積ヒストグラムから階調変換用LUTを作成 
	for (int i = 0; i < 256; i++)
		LUT[i] = LUT[i] * 255.0 / LUT[255];

	// (4) 画像走査内でLUTを用いて階調変換を行う
	cv::Mat result = cv::Mat(src.size(), CV_8UC1);
	for (int i = 0; i < result.rows; i++)
		for (int j = 0; j < result.cols; j++)
			result.ptr(i, j)[0] = LUT[src.ptr(i, j)[0]];

    return result;
}

//BGRのそれぞれにヒストグラム平坦化
void BGRHistEqualize(char* name){
    cv::Mat input = cv::imread(name);	//画像の読み込み
    cv::Mat output;
    //RGBチャンネル配列
	cv::Mat matArray[3];

    cv::Mat equalizedMatArr[3];

    cv::split(input, matArray);


    for (int i=0; i<3; i++){
        equalizedMatArr[i] = singleColorHistEqualize(matArray[i]);
    }

    cv::merge(equalizedMatArr, 3, output);

    cv::imshow("Output-BGR-HistEqualize", output);
    cv::imwrite("ex6-out_BGR.jpg", output); //提出用(画像の保存)

}


//HSV空間のうちValueのみヒストグラム平坦化
void valueHistEqualize(char* name){
    cv::Mat inputBGR = cv::imread(name);	//画像の読み込み
    cv::Mat inputHSV;
    cv::Mat outputHSV;
    cv::Mat outputBGR;

    //RGBチャンネル配列
    cv::Mat hsvArray[3];
    cv::Mat outputBGRArry[3];

    
    //BGR -> HSVに変換
    cv::cvtColor(inputBGR, inputHSV, cv::COLOR_BGR2HSV);
    ///HSV画像を分離
    cv::split(inputHSV, hsvArray);

    //Vのみヒストグラム平坦化
    hsvArray[2] = singleColorHistEqualize(hsvArray[2]);

    //HSV画像をmerge
    cv::merge(hsvArray, 3, outputHSV);

    //HSV -> BGRに再変換
    cv::cvtColor(outputHSV, outputBGR, cv::COLOR_HSV2BGR);


    cv::imshow("Output-Val-HistEqualize", outputBGR);
    cv::imwrite("ex6-out_V.jpg", outputBGR); //提出用(画像の保存)
    
}

void showInput(char* filename){
    cv::Mat src = cv::imread(filename);
    cv::imshow("Input", src);
}


int main(int argc, char* argv[])
{
    if (argc < 2)   
	{
		argv[1] = "sample.jpg";  //引数省略時のdefault設定 
	}

    //入力画像の表示
    showInput(argv[1]);

    //Vのみヒストグラム平坦化
    valueHistEqualize(argv[1]);

    //BGRごとにヒストグラム平坦化
    BGRHistEqualize(argv[1]);

    cv::waitKey();
	return 0;
}
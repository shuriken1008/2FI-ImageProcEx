#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;

// 引数で示す角度だけ反時計回りに回転する関数
void rotate(char* fileName, int angle, int rotateCenterX, int rotateCenterY, double scale){
	cv::Mat image = cv::imread(fileName);
	if (image.empty()){
		std::cout << "画像読み込み失敗" << std::endl;
		return;
	}

	cv::Point center;			// 回転中心


	// x,yが-1なら画像の中心にする改良
	if(rotateCenterX < 0){
		center.x = image.cols/2;	// 画像の中心
	}else{
		center.x = rotateCenterX;
	}
	if(rotateCenterY < 0){
		center.y = image.rows/2;
	}else{
		center.y = rotateCenterY;
	}


// 2次元のアフィン変換(ここでは回転)行列を求める
//	Mat cv::getRotationMatrix2D	(Point2f center, double angle, double scale)
//	center: 入力画像における回転中心（座標原点は左上）
//	angle: 度単位で表される回転角度(正の値は，反時計回りの回転)
//	scale: 等方性スケーリング係数
//	出力: 2×3 の出力行列へのポインタ
	cv::Mat mapMatrix = cv::getRotationMatrix2D(center, (double)angle, scale);
	cout << "Matrix row No.0 = " << mapMatrix.at<double>(0,0) <<
	", " << mapMatrix.at<double>(0,1) << ", " << mapMatrix.at<double>(0,2) << endl;
	cout << "Matrix row No.1 = " << mapMatrix.at<double>(1,0) <<
	", " << mapMatrix.at<double>(1,1) << ", " << mapMatrix.at<double>(1,2) << endl;

// 画像のアフィン変換を行う
//	void cv::warpAffine	(InputArray src, OutputArray dst, InputArray M,
//		Size dsize, [int flags = INTER_LINEAR, 
//		[int	borderMode = BORDER_CONSTANT, [const Scalar & borderValue = Scalar()]]])
//	src:入力画像
//	dst:出力画像
//	M: 2行 x 3列 の変換行列
//	dsize: 出力画像のサイズ
//	flags: 補間手法 (default cv::INTER_LINEAR (線形補間))
//	borderMode: 対応のとれない点を埋める方法 (default 0)
//  borderValue: 対応のとれない点を埋める値(cv::BORDER_CONSTANTの場合)
	cv::Mat result;
	cv::warpAffine(image, result, mapMatrix, cv::Size(image.cols,image.rows));
	
	cv::imshow("Input", image);
	cv::imshow("Rotated", result);
	cv::waitKey();
}

int main(int argc, char* argv[])
{
	char* args[6] = {argv[0],"sample.jpg","0", "-1", "-1", "0.8"}; //exe, path, deg, x, y, scale
    //[NOTE] x,y = -1 -> 画像の中心とする。

    //コマンド引数での引数不足分の補正: 初期値を引数に変更
    for (int i=1; i<=6; i++){
        if(argc >= i+1) args[i] = argv[i];
    }


	rotate(args[1],atoi(args[2]), atoi(args[3]), atoi(args[4]), atof(args[5]) );


	return 0;
}

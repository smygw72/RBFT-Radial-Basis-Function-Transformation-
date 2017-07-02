#pragma once
#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////////
//     　　 RBFTを用いて三角形メッシュの頂点の返還後の座標を求める     　    //
//    　　   マーカの入力座標と出力座標の対応点から係数を求める              //
//      　 　 時間軸方向を考慮するため3フレーム分の対応点を考える    　      //
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace cv;

class RBFT {

private:
	int N; // 頂点数
	vector<Point2i> A, B; // 変形前・変形後の座標
	Eigen::MatrixXf F, G, X; // F = GX

public:
	RBFT(std::vector<cv::Point2i> _before, std::vector<cv::Point2i> _after);
	~RBFT() {}
	double potential(const Point2i Ai, const Point2i Aj);

	/* Set関数 */
	void SetF();
	void SetG();
	void SetX();

	/* RBF補間実行 */
	std::vector<cv::Point2i> RBFT::Exe(const vector<Point2i> InputPoints);
};
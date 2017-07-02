#pragma once
#include "RBF.h"

using namespace std;
using namespace cv;

float phi(const Point2i x_i, const Point2i x_j) 
{
	return pow(pow(x_i.x - x_j.x, 2) + pow(x_i.y - x_j.y, 2), 0.5);
}

RBF::RBF(std::vector<cv::Point2i> _before, std::vector<cv::Point2i> _after)
{
	if (_before.size() != _after.size()) {
		std::cout << "[Warning]: ‘Î‰ž“_‚ªˆê’v‚µ‚Ä‚¢‚Ü‚¹‚ñ" << std::endl;
	}
	else {
		N = _after.size();
		before = _before;
		after = _after;
	}
}

void RBF::SetY()
{
	Y.resize(N, 2);

	for (int i = 0; i < N; ++i) {
		Y.coeffRef(i, 0) = after[i].x;
		Y.coeffRef(i, 1) = after[i].y;
	}
}

void RBF::SetPhi()
{
	Phi.resize(N, N);

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Phi.coeffRef(i, j) = phi(X[i], X[j]);
		}
	}
}

void RBF::SetW()
{
	W.resize(N, 2);

	Eigen::PartialPivLU<Eigen::MatrixXf> solver(Phi);

	W = solver.solve(Y);
}

cv::Point2i RBF::GetValue(const int i)
{
	Point2f fValue;

	for (int i = 0; i < N; ++i) {
//		fValue += Point2f(W.coeff(i, 0) * phi(Point2i(x, y), X[i]);
	}

	return (Point2i)fValue;
}

void RBF::Exe(const std::vector<cv::Point2i> _CenterPoints, std::vector<cv::Point2i>& _AllPoints)
{
	SetY(_CenterPoints);
	SetPhi();
	SetW();

	for (int i = 0; i < _AllPoints.size(); ++i) {
			_AllPoints[i] = GetValue(i);
	}

#if 0
	imshow("ROI(interpolated)", roi);
#endif
}
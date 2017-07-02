#include "RBFT.h"

RBFT::RBFT(std::vector<cv::Point2i> _before, std::vector<cv::Point2i> _after)
{
	if (_before.size() != _after.size()) {
		std::cout << "[warning]: 対応点が一致していません" << std::endl;
	}
	else {
		N = _before.size();
		A = _before;
		B = _after;
	}
}

double RBFT::potential(const Point2i Ai, const Point2i Aj)
{
	double p;
	//p = pow(pow(Ai.x - Aj.x, 2) + pow(Ai.y - Aj.y, 2), 0.5);
	p = exp(-((pow(Ai.x - Aj.x, 2) + pow(Ai.y - Aj.y, 2)) / pow((Width + Height) / 12, 2)));
	return p;
}

void RBFT::SetF()
{
	F.resize(N + 3, 2);
	F.setZero();

	for (int i = 0; i < N; ++i) {
		F(i, 0) = B[i].x;
		F(i, 1) = B[i].y;
	}
}

void RBFT::SetG()
{
	G.resize(N + 3, N + 3);
	G.setZero();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			G(i, j) = potential(A[i], A[j]);
		}
		G(i, i) += lamda;
	}

	for (int i = 0; i < N; ++i) {
		G(i, N) = 1;
		G(i, N + 1) = A[i].x;
		G(i, N + 2) = A[i].y;
		G(N, i) = 1;
		G(N + 1, i) = A[i].x;
		G(N + 2, i) = A[i].y;
	}
}

/* 頂点A → 頂点B へ変形するときのパラメータ行列Xを求める */
void RBFT::SetX()
{
	/* 行列の宣言 */
	X.resize(N + 3, 2);

	// F,GのSet
	SetF();
	SetG();

	X = G.inverse() * F;

#if 0 // 確認用
	cout << "-----A-----" << endl;
	cout << A << endl;
	cout << "-----B-----" << endl;
	cout << B << endl;
	cout << "-----F-----" << endl;
	cout << F << endl;
	cout << "-----G-----" << endl;
	cout << G << endl;
	cout << "-----X-----" << endl;
	cout << X << endl;
#endif
}

std::vector<cv::Point2i> RBFT::Exe(const vector<Point2i> InputPoints)
{
	std::vector<cv::Point2i> OutputPoints;
	OutputPoints.resize(InputPoints.size());

#ifdef _OPENMP
#pragma omp parallel for
#endif
	for (int i = 0; i < InputPoints.size(); ++i) {

		float x, y;
		x = y = 0;

		for (int j = 0; j < N; ++j) {
			x += potential(InputPoints[i], A[j]) * X(j, 0);
			y += potential(InputPoints[i], A[j]) * X(j, 1);
		}

		x += (X(N, 0) + InputPoints[i].x * X(N + 1, 0) + InputPoints[i].y * X(N + 2, 0));
		y += (X(N, 1) + InputPoints[i].x * X(N + 1, 1) + InputPoints[i].y * X(N + 2, 1));

		OutputPoints[i] = Point2i(x, y);
	}

#if 0 // 確認用
	cout << "-------------------RBF補間された結果----------------------" << endl;
	cout << InputPoints << endl;
#endif

	return OutputPoints;
}

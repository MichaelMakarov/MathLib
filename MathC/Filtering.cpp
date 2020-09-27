#include "Filtering.h"
#include "LinearAlgebra.h"

filter::KalmanFilter::KalmanFilter(const Vector& X0, const Matrix& P0)
{
	SetInitial(X0, P0);
	kf_I = Matrix::Identity(P0.ColsNumber());
}

void filter::KalmanFilter::SetInitial(const Vector& X0, const Matrix& P0)
{
	if (X0.Size() != P0.RowsNumber())
		throw std::exception("The dimension of the vector does not correspond the dimension of the matrix!");
	if (!P0.IsSquare())
		throw std::exception("The P0 must be square matrix!");
	kf_X0 = X0;
	kf_P0 = P0;
}

void filter::KalmanFilter::SetModel(
	const Matrix& F, 
	const Matrix& H,
	const Matrix& Q,
	const Matrix& R)
{
	if (!F.IsSquare())
		throw std::exception("F must be square matrix!");
	if (F.RowsNumber() != kf_X0.Size())
		throw std::exception("The dimension of the F does not correspond the X size!");
	if (!Q.IsSquare())
		throw std::exception("Q must be square matrix!");
	if (Q.RowsNumber() != kf_X0.Size())
		throw std::exception("The dimension of the Q dies not correspond the X size!");
	if (!R.IsSquare())
		throw std::exception("R must be square matrix!");
	if (R.RowsNumber() != H.RowsNumber())
		throw std::exception("R is not consistent to H!");
	kf_FT = kf_F = F; kf_FT.Transpose();
	kf_HT = kf_H = H; kf_HT.Transpose();
	kf_Q = Q;
	kf_R = R;
}

bool filter::KalmanFilter::Filter(
	const std::vector<Vector>& measurements, 
	const Vector& Bu, 
	std::vector<Vector>& filtered)
{
	if (Bu.Size() != kf_X0.Size()) return false;
	if (measurements.size() == 0) return true;
	filtered.clear();
	filtered.resize(measurements.size());
	size_t i = 0;
	Matrix K;
	// initializing
	kf_X = kf_X0;
	kf_P = kf_P0;
	for (const Vector& z : measurements)
	{
		// forecast (apriory estimation)
		kf_X = kf_F * kf_X + Bu;
		kf_P = kf_F * kf_P * kf_FT + kf_Q;
		// correction (aposteriory estimation)
		if (!linalg::Inverse(kf_H * kf_P * kf_HT + kf_R, K))
			return false;
		K = kf_P * kf_HT * K;
		kf_X += K * (z - kf_H * kf_X);
		kf_P = (kf_I - K * kf_H) * kf_P;
		filtered[i++] = kf_X;
	}

	return true;
}

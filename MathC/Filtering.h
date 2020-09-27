#pragma once
#include "Matrix.h"
#include <vector>

namespace filter
{
	// Представляет функционал фильтра Калмана.
	// Модель системы задана ДУ:
	// X_k = F * X_k-1 + B * u_k + q
	// Z_k = H * X_k + r
	// q ~ N(0, Q), r ~ N(0, R)
	class KalmanFilter
	{
	protected:
		Matrix kf_F, kf_FT;
		Matrix kf_H, kf_HT;
		Matrix kf_Q;
		Matrix kf_R;
		Matrix kf_I;
		Matrix kf_P;
		Vector kf_X;
		Matrix kf_P0;
		Vector kf_X0;

	public:
		// Создание экземпляра фильтра Калмана.
		// X0 - нач. значение вектора состония.
		// P0 - нач. значение матрицы ковариации.
		KalmanFilter(const Vector& X0, const Matrix& P0);
		// деструктор
		~KalmanFilter() {}

		// Изменение нач. значений вектора состояния и ковариационной матрицы.
		void SetInitial(const Vector& X0, const Matrix& P0);
		// Задание параметров модели.
		void SetModel(
			const Matrix& F,
			const Matrix& H,
			const Matrix& Q,
			const Matrix& R);

		// Фильтрация массива измерений.
		// measurements - массив измерений вектора состояния,
		// B - матрица при управлении.
		// U - вектор управления.
		// filtered - массив отфильтрованных значений измерений.
		// true, если расчёт прошёл без ошибок.
		bool Filter(
			const std::vector<Vector>& measurements,
			const Vector &Bu,
			std::vector<Vector>& filtered);
	};
}


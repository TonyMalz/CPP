#pragma once
#include "ChiliMath.h"
#include "Vec2.h"

template <class T>
class _Mat3{
public:
	T elems[3][3];
	
	_Mat3 operator *(const _Mat3 rhs)const{
		_Mat3 result;
		for (int row = 0; row < 3; ++row)
		{
			for (int col = 0; col < 3; ++col)
			{
				T sum = 0;
				for (int i = 0; i < 3; i++)
				{
					sum += elems[row][i] * rhs.elems[i][col];
				}
				result.elems[row][col] = sum;
			}
		}
		return result;
	}
	void operator *=(const  _Mat3 rhs){
		*this = *this*rhs;
	}
	
	void operator *=(const T rhs){
		for (T& elem : elems) {
			elem *= rhs;
		}
	}
	_Mat3 operator * (const T rhs)const{
		_Mat3 matrix = *this;
		matrix *= rhs;
		
		return matrix;
	}

	void operator /=(const T rhs){
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				elems[i][j] /= rhs;
			}
		}
	}
	_Mat3 operator / (const T rhs)const{
		_Mat3 matrix = *this;
		matrix /= rhs;

		return matrix;
	}

	_Vec2<T> operator *(const _Vec2<T> rhs)const{
		_Vec2<T> vector; 
		T x = rhs.x;
		T y = rhs.y;

		vector.x = x* elems[0][0] + y*elems[0][1] + elems[0][2];
		vector.y = x* elems[1][0] + y*elems[1][1] + elems[1][2];
		return vector;
	}

	static _Mat3 Rotation(const T angle) {
		_Mat3 matrix;
		T sine = sin(angle);
		T cosine = cos(angle);
		matrix = {
			cosine, -sine, 0,
			sine, cosine, 0,
			0, 0, 1
		};
		return matrix;
	}
	static _Mat3 Scale(const T scale) {
			_Mat3 matrix;
			matrix = {
				scale, 0, 0,
				0, scale, 0,
				0, 0, 1
			};
			return matrix;
		}
	static _Mat3 Translation(const _Vec2<T> translate) {
			_Mat3 matrix;
			matrix = {
				1, 0, translate.x,
				0, 1,  translate.y,
				0, 0, 1
			};
			return matrix;
		}
	static _Mat3 Identity(){
		_Mat3 matrix = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
		return matrix;
	}
};

typedef _Mat3<float> Mat3;
typedef _Mat3<double> Matd3;

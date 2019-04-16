//*****************************************************************************
//Title		:EllipticalMesher/Point.h
//Author	:Tanabe Yuta
//Date		:2019/04/16
//Copyright	:(C)2019 TanabeYuta
//*****************************************************************************

#pragma once
#include <array>
#include <cmath>

class Point
{
public:
	Point();
	~Point();
	Point(double, double);

	std::array<double, 2> x;

	Point operator+(const Point &);		//�x�N�g���̘a
	Point operator-(const Point &);		//�x�N�g���̍�
	Point operator*(const double &);	//�x�N�g���̎����{
	Point operator/(const double &);	//�x�N�g���̎�����

	double Norm();						//�x�N�g���̃m�������v�Z
};

Point operator*(const double &, const Point &);

Point operator/(const double &, const Point &);
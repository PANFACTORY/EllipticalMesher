//*****************************************************************************
//Title		:EllipticalMesher/EllipticalMesher.h
//Author	:Tanabe Yuta
//Date		:2019/04/16
//Copyright	:(C)2019 TanabeYuta
//*****************************************************************************


#pragma once
#include <vector>
#include <iostream>
#include "Point.h"


class EllipticalMesher
{
public:
	EllipticalMesher();
	~EllipticalMesher();
	EllipticalMesher(int, int);
	   
	
	void SetBoundaryPoint(int, Point);		//���E��̓_��ǉ�
	void MakeMesh();						//���b�V������
	void ExportMesh(std::string);			//���b�V���\��


private:
	const int inum;							//x�������̍��W�_��
	const int jnum;							//y�������̍��W�_��


	std::vector<Point> pb;					//���E��̓_
	std::vector<std::vector<Point>> pin;	//�����̓_


	static const int ITRMAX = 100000;		//�A���������\���o�̍ő唽����
	const double DEPS = 1.0e-8;				//���W�̃m�����̋��e�c��
};


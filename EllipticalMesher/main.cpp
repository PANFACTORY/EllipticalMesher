//*****************************************************************************
//Title		:EllipticalMesher/main.cpp
//Author	:Tanabe Yuta
//Date		:2019/04/16
//Copyright	:(C)2019 TanabeYuta
//*****************************************************************************

#include <iostream>
#include "EllipticalMesher.h"

int main() {
	EllipticalMesher Mesh(17, 5);		//���b�V���[�I�u�W�F�N�g

	


	Mesh.MakeMesh();					//���b�V������
	Mesh.ExportMesh("mesh");			//VTK�t�@�C���ɏo��
	return 0;
}
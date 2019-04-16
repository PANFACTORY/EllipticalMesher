//*****************************************************************************
//Title		:EllipticalMesher/EllipticalMesher.cpp
//Author	:Tanabe Yuta
//Date		:2019/04/16
//Copyright	:(C)2019 TanabeYuta
//*****************************************************************************

#include <string>
#include <fstream>
#include <sstream>
#include "EllipticalMesher.h"


EllipticalMesher::EllipticalMesher() : inum(0), jnum(0) {}


EllipticalMesher::~EllipticalMesher(){}


EllipticalMesher::EllipticalMesher(int _inum, int _jnum) : inum(_inum), jnum(_jnum){
	this->pb = std::vector<Point>(2 * (this->inum + this->jnum - 2));
	this->pin = std::vector<std::vector<Point>>(this->inum, std::vector<Point>(this->jnum, Point(0.0, 0.0)));
}


void EllipticalMesher::SetBoundaryPoint(int _i, Point _point){
	this->pb[_i] = _point;
}


void EllipticalMesher::MakeMesh(){
	//----------Dirichlet�����̐ݒ�----------
	int pbi = 0;		//���E�̃J�E���^
	//.....����.....
	for (int i = 0; i < this->inum - 1; i++, pbi++) {
		this->pin[i][0] = this->pb[pbi];
	}
	//.....�E��.....
	for (int i = 0; i < this->jnum - 1; i++, pbi++) {
		this->pin[this->inum - 1][i] = this->pb[pbi];
	}
	//.....���.....
	for (int i = this->inum - 1; i > 0; i--, pbi++) {
		this->pin[i][this->jnum - 1] = this->pb[pbi];
	}
	//.....����.....
	for (int i = this->jnum - 1; i > 0; i--, pbi++) {
		this->pin[0][i] = this->pb[pbi];
	}

	//----------Laplace�������̋���----------
	for (int k = 0; k < this->ITRMAX; k++) {
		double dxmax = 0.0;
		std::cout << "iteration = " << k + 1;

		for (int i = 1; i < this->inum - 1; i++) {
			for (int j = 1; j < this->jnum - 1; j++) {
				//.....Laplace�������̌W�����v�Z.....
				Point xxi = 0.5*(this->pin[i + 1][j] - this->pin[i - 1][j]);
				Point xiota = 0.5*(this->pin[i][j + 1] - this->pin[i][j - 1]);
				double alpha = pow(xiota.x[0], 2.0) + pow(xiota.x[1], 2.0);
				double beta = xxi.x[0] * xiota.x[0] + xxi.x[1] * xiota.x[1];
				double ganma = pow(xxi.x[0], 2.0) + pow(xxi.x[1], 2.0);

				//.....���W���X�V.....
				Point tmp = this->pin[i][j];
				this->pin[i][j] = 0.5*(alpha*(this->pin[i + 1][j] + this->pin[i - 1][j]) - 0.5*beta*(this->pin[i + 1][j + 1] - this->pin[i - 1][j + 1] - this->pin[i + 1][j - 1] + this->pin[i - 1][j - 1]) + ganma * (this->pin[i][j + 1] + this->pin[i][j - 1])) / (alpha + ganma);
				
				//.....���W�����̃m�����̍ő�l���X�V.....
				double dxtmp = (tmp - this->pin[i][j]).Norm();
				if (dxmax < dxtmp) {
					dxmax = dxtmp;
				}
			}
		}
		std::cout << "\t" << dxmax << "\n";

		//.....��������.....
		if (dxmax < DEPS) {
			std::cout << "Converged:k = " << k + 1;
			break;
		}
	}
}


void EllipticalMesher::ExportMesh(std::string _fname){
	std::ofstream fout(_fname + ".vtk");
	
	//----------Header�̏o��----------
	fout << "# vtk DataFile Version 4.1\n";
	fout << "vtk output\n";
	fout << "ASCII\n";
	fout << "DATASET UNSTRUCTURED_GRID\n";

	//----------�_�̒ǉ�----------
	fout << "\nPOINTS\t" << this->inum * this->jnum << "\tfloat\n";
	for (auto pinrow : this->pin) {
		for (auto pinone : pinrow) {
			fout << pinone.x[0] << "\t" << pinone.x[1] << "\t" << 0.0 << "\n";
		}
	}

	//----------�v�f�̒ǉ�----------
	fout << "\nCELLS " << (this->inum - 1)*(this->jnum - 1) << "\t" << (this->inum - 1)*(this->jnum - 1) * 5 << "\n";
	for (int i = 0; i < this->inum - 1; i++) {
		for (int j = 0; j < this->jnum - 1; j++) {
			fout << "4 " << i * (this->jnum)+j << "\t" << i * (this->jnum)+j + 1 << "\t" << (i + 1)*(this->jnum)+j + 1 << "\t" << (i + 1)*(this->jnum)+j << "\n";
		}
	}

	//----------�v�f�^�C�v�̐ݒ�----------
	fout << "\nCELL_TYPES\t" << (this->inum - 1)*(this->jnum - 1) << "\n";
	for (int i = 0; i < (this->inum - 1)*(this->jnum - 1); i++) {
		fout << "9\n";
	}

	fout.close();
}
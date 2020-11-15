#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include "header.h"
using std::fstream;



int main() {	
	int lx = 0, ly = 0, lz = 0;
	int a=0, a1, a2, a3, a4, a5, a6;
	std::string filename;
	std::cout << "Digite as dimensoes desejadas(x,y,z): ";
	std::cin >> lx >> ly >> lz;
	if((lx==0)&&(ly==0)&&(lz==0)){exit(0);}
	Sculptor cursor(lx, ly, lz);
	std::cout << "...\nConstruindo Matriz com dimenssoes: " << lx << " " << ly << " " << lz<<std::endl;
	while (a < 12) {
		std::cout << "a= " << a;
		std::cout << "..\nEscolha a opcao digitando o numero correspondente\n1-Mudar cor\n2-Colocar Voxel\n3-Tirar Voxel\n4-Colocar Cubo\n5-Tirar Cubo\n6-Colocar Esfera\n7-Tirar Esfera\n8-Colocar Elipsoide\n9-Tirar Elipsoide\n10-Salvar(WIP)\n11-Mostrar\n12-Sair\n\n";
		std::cin >> a;
		switch (a) {
		case 1:
			std::cout << "Digite a cor em RGB e a transparencia de 1 até 0(R, G, B, a) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			if ((a1 >= 0) && (a1 <= 1) && (a2 >= 0) && (a2 <= 1) && (a3 >= 0) && (a3 <= 1) && (a4 >= 0) && (a4 <= 1)) {
				std::cout << "Cor do cursor mudada para" << a1 << " " << a2 << " " << a3 << " " << a4;
				cursor.setColor(a1, a2, a3, a4);
				break;
			}
			else { break; }
		case 2:
			std::cout << "\nDigite a posicao(x, y, z) ";
		std::cin >> a1 >> a2 >> a3;
		cursor.putVoxel(a1, a2, a3);
		std::cout << "Colocado voxel em" << a1 << " " << a2 << " " << a3 << "\n";
		break;
		case 3:
			std::cout << "\nDigite a posicao(x, y , z) ";
			std::cin >> a1 >> a2 >> a3;
			cursor.cutVoxel(a1, a2, a3);
			std::cout << "Tirado voxel em" << a1 << " " << a2 << " " << a3 << "\n";
			break;
		case 4:
			std::cout << "\nDigite as posicoes das verticies(x0, x1, y0, y1, z0, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.putBox(a1, a2, a3, a4, a5, a6);
			std::cout << "Colocado cubo de x=" << a1 << "até x=" << a2 << " y" << a3 << " até y=" << a4 << " z=" << a5 << " até z=" << a6 << "\n";
			break;
		case 5:
			std::cout << "\nDigite as posicao das verticies(x0, x1, y0, y1, z0, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.cutBox(a1, a2, a3, a4, a5, a6);
			std::cout << "Trirado de x=" << a1 << "até x=" << a2 << " y" << a3 << " até y=" << a4 << " z=" << a5 << " até z=" << a6 << "\n";
			break;
		case 6:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.putSphere(a1, a2, a3, a4);
			std::cout << "Colocada esfera com centro" << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
			break;
		case 7:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.cutSphere(a1, a2, a3, a4);
			std::cout << "Tirada esfera com centro" << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
			break;
		case 8:
			std::cout << "\nDigite as posicao do centro e dimensoes do raio(x, y, z, rx, ry, rz) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.putEllipsoid(a1, a2, a3, a4, a5, a6);
			std::cout << "Colocado elipsoide com centro " << a1 << " " << a2 << " " << a3 << " e dimensoes do raio " << a4 << " " << a5 << " " << a6 << "\n";
			break;
		case 9: 
			std::cout << "\nDigite as posicao do centro e dimensoes do raio(x, y, z, rx, ry, rz) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.cutEllipsoid(a1, a2, a3, a4, a5, a6);
			std::cout << "Tirado elipsoide com centro " << a1 << " " << a2 << " " << a3 << " e dimensoes do raio " << a4 <<" "<< a5 << " " << a6 << "\n";
			break;
		case 10:
			std::cout << "\nDigite o nome/endereco do arquivo: \n ";
			std::cin >> filename;
			cursor.writeOFF(filename.c_str());
			break;
		case 11:
			std::cout << "\nMostrando Matriz\n";
			cursor.show();
			break;
		case 12:
			//cursor.freemem();
			break;
		
		}
	}
	return 0;
}


/*to do
*ajeitar liberação de memoria
*/
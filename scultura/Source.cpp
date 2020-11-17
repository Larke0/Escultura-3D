#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include "header.h"
using std::fstream;



int main() {	
	int lx = 0, ly = 0, lz = 0, a=0;
	int a1, a2, a3, a4, a5, a6;
	char y;
	bool as=0;
	std::string filename, filenameas;
	std::cout << "Digite 1 para criar uma nova matriz e 2 para carregar ";
	std::cin >> a;
	if (a == 2) {
		std::cout << "Digite o caminho do arquivo: ";
		std::cin >> filename;
		a1 = 1;
	}
	else {
		std::cout << "Digite as dimensoes desejadas(x,y,z): ";
		std::cin >> lx >> ly >> lz;
		if ((lx == 0) && (ly == 0) && (lz == 0)) { exit(0); }
		a1 = 0;
		std::cout << "...\nConstruindo Matriz com dimenssoes: " << lx << " " << ly << " " << lz << std::endl;
	}
	std::cout << "Deseja salvar automaticamente?(0-não 1-sim) ";
	std::cin >> a;
	if (a == 1) {
		as = 1;
		if(a1==0){
			std::cout << "Digite o caminho do arquivo: ";
			std::cin >> filename;
		}
	}
	filenameas = filename;
	a = 0;
	Sculptor cursor(lx, ly, lz, filename.c_str(), a1);
	while (a < 14) {
		//std::cout << "a= " << a;
		std::cout << "..\nEscolha a opcao digitando o numero correspondente\n1-Mudar cor\n2-Colocar Voxel\n3-Tirar Voxel\n4-Colocar Cubo\n5-Tirar Cubo\n6-Colocar Esfera\n7-Tirar Esfera\n8-Colocar Elipsoide\n9-Tirar Elipsoide\n10-Salvar(WIP)\n11-Mostrar\n14-Sair\n\n";
		std::cin >> a;
		switch (a) {
		case 1:
			std::cout << "Digite a cor em RGB de 0 ate 255 e transparencia em %(R, G, B, a) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			std::cout << "Cor do cursor mudada para " << a1 << " " << a2 << " " << a3 << " " << a4;
			cursor.setColor(a1, a2, a3, a4/100);
			break;
		case 2:
			while ((a1 >= 0)|| (a2 >= 0)|| (a2 >= 0)) {
				std::cout << "\nDigite a posicao(x, y, z) ou -1 -1 -1 para sair ";
				std::cin >> a1 >> a2 >> a3;
				cursor.putVoxel(a1, a2, a3);
				std::cout << "Colocado voxel em " << a1 << " " << a2 << " " << a3 << "\n";
			}
		break;
		case 3:
			while ((a1 >= 0) || (a2 >= 0) || (a2 >= 0)) {
				std::cout << "\nDigite a posicao(x, y, z) ou -1 -1 -1 para sair ";
				std::cin >> a1 >> a2 >> a3;
				cursor.cutVoxel(a1, a2, a3);
				std::cout << "tirado em " << a1 << " " << a2 << " " << a3 << "\n";
			}
			break;
		case 4:
			std::cout << "\nDigite as posicoes das verticies(x0, y0, z0, x1, y1, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.putBox(a1, a4, a2, a5, a3, a6);
			std::cout << "Colocado cubo de x=" << a1 << "ate x=" << a4 << " y" << a2 << " até y=" << a5 << " z=" << a3 << " até z=" << a6 << "\n";
			break;
		case 5:
			std::cout << "\nDigite as posicoes das verticies(x0, y0, z0, x1, y1, z1) ";
			std::cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6;
			cursor.cutBox(a1, a4, a2, a5, a3, a6);
			std::cout << "Tirado cubo de x=" << a1 << "ate x=" << a4 << " y" << a2 << " até y=" << a5 << " z=" << a3 << " até z=" << a6 << "\n";
			break;
		case 6:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.putSphere(a1, a2, a3, a4);
			std::cout << "Colocada esfera com centro " << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
			break;
		case 7:
			std::cout << "\nDigite as posicao do centro e o raio(x, y, z, r) ";
			std::cin >> a1 >> a2 >> a3 >> a4;
			cursor.cutSphere(a1, a2, a3, a4);
			std::cout << "Tirada esfera com centro " << a1 << " " << a2 << " " << a3 << " e raio " << a4 << "\n";
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
			std::cout << "\nDigite o nome/endereco do arquivo: \n ";
			std::cin >> filename;
			cursor.save(filename.c_str());
			break;
		case 13:
			std::cout << "\nDigite as coordenadas para analise: \n ";
			std::cin >> a1 >> a2 >> a3;
			cursor.read(a1, a2, a3);
			break;
		case 14:
			//cursor.freemem();
			break;
		}
		if (as) {
			cursor.save(filenameas.c_str());
		}
	}
	return 0;
}


/*to do
*ajeitar liberação de memoria
*/

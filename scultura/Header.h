#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
using std::fstream;

struct Voxel {
	float r, g, b; // Colors
	float a;
	// Transparency
	bool isOn; // Included or not
};
//typedef struct Voxel matriz;

struct verticie {
	float x, y, z;
	bool exists;
	int n;
};


class Sculptor {
protected:
	Voxel*** v;
	// 3D matrix
	int nx, ny, nz; // Dimensions
	float r, g, b, a; // Current drawing color
	int i, j, k;
public:
	Sculptor(int _nx, int _ny, int _nz);
	~Sculptor();
	void setColor(float r_, float g_, float b_, float alpha_);
	void putVoxel(int x, int y, int z);
	void cutVoxel(int x, int y, int z);
	void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
	void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
	void putSphere(int xcenter, int ycenter, int zcenter, int radius);
	void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
	void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
	void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
	void writeOFF(const char* filename);
	void freemem();
	void show();
};

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
	int i, j, k;
	nx = _nx; ny = _ny; nz = _nz;
	v = (Voxel***)malloc(_nx * sizeof(Voxel**));
	if (v == NULL) {
		std::cout << "Out of memory";
		exit(0);
	}
	for (i = 0; i < _nx; i++) {
		v[i] = (Voxel**)malloc(_ny * sizeof(Voxel*));
		for (j = 0; j < _ny; j++) {
			v[i][j] = (Voxel*)malloc(_nz * sizeof(Voxel));
		}
	}
	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			for (k = 0; k < nz; k++) {
				v[i][j][k].isOn = 0;
			}
		}
	}
};

Sculptor::~Sculptor(void) {
	//freemem();
}



void Sculptor::setColor(float r_, float g_, float b_, float alpha_) {
	r = r_; g = g_; b = b_; a = alpha_;
};

void Sculptor::putVoxel(int x, int y, int z) {
	if ((0 <= x) && (x < nx) && (0 <= y) && (y < ny) && (0 <= z) && (z < nz)) {
		v[x][y][z].isOn = true;
		v[x][y][z].r = r; v[x][y][z].g = g; v[x][y][z].b = b; v[x][y][z].a = a;
	}
};
void Sculptor::cutVoxel(int x, int y, int z) {
	v[x][y][z].isOn = false;
};
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	for (i = x0; i <= x1; i++) {
		for (j = y0; j <= y1; j++) {
			for (k = z0; k <= z1; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					v[i][j][k].isOn = true;
					v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
				}
			}
		}
	}
};
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
	for (i = x0; i <= x1; i++) {
		for (j = y0; j <= y1; j++) {
			for (k = z0; k <= z1; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					v[i][j][k].isOn = false;
				}
			}
		}
	}
};
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
	for (i = xcenter - (radius); i <= xcenter + radius; i++) {
		for (j = ycenter - radius; j <= ycenter + radius; j++) {
			for (k = zcenter - radius; k <= zcenter + radius; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					if (((pow((i - xcenter), 2)) + (pow((j - ycenter), 2)) + (pow((k - zcenter), 2))) <= (pow(radius, 2))) {
						v[i][j][k].isOn = true;
						v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
					}
				}
			}
		}
	}
};
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
	for (i = xcenter - (radius); i <= xcenter + radius; i++) {
		for (j = ycenter - radius; j <= ycenter + radius; j++) {
			for (k = zcenter - radius; k <= zcenter + radius; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					if (((pow((i - xcenter), 2)) + (pow((j - ycenter), 2)) + (pow((k - zcenter), 2))) <= (pow(radius, 2))) {
						v[i][j][k].isOn = false;
					}
				}
			}
		}
	}
};
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	for (i = xcenter - rx; i <= xcenter + rx; i++) {
		for (j = ycenter - ry; j <= ycenter + ry; j++) {
			for (k = zcenter - rz; k <= zcenter + rz; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					if (((pow((i - xcenter), 2) / pow(rx, 2)) + (pow((j - ycenter), 2) / pow(ry, 2)) + (pow((k - zcenter), 2) / pow(rz, 2))) <= 1) {
						v[i][j][k].isOn = true;
						v[i][j][k].r = r; v[i][j][k].g = g; v[i][j][k].b = b; v[i][j][k].a = a;
					}
				}
			}
		}
	}
};
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
	for (i = xcenter - rx; i <= xcenter + rx; i++) {
		for (j = ycenter - ry; j <= ycenter + ry; j++) {
			for (k = zcenter - rz; k <= zcenter + rz; k++) {
				if ((0 <= i) && (i < nx) && (0 <= j) && (j < ny) && (0 <= k) && (k < nz)) {
					if (((pow((i - xcenter), 2) / pow(rx, 2)) + (pow((j - ycenter), 2) / pow(ry, 2)) + (pow((k - zcenter), 2) / pow(rz, 2))) <= 1) {
						v[i][j][k].isOn = false;
					}
				}
			}
		}
	}
};


void Sculptor::freemem(void) {
	int i, j, k;
	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			free(v[i][j]); std::cout << "liberado v[" << i << "][" << j << "] \n";
		}
		free(v[i]); std::cout << "liberado v[" << i << "]\n";
	}
	free(v); std::cout << "Finalizado\n\n";
}



void Sculptor::show(void) {
	int i, j, k;
	for (k = 0; k < nz; k++) {
		std::cout << std::endl << " z=" << k << std::endl;
		for (j = ny - 1; j >= 0; j--) {
			for (i = 0; i < nx; i++) {
				if (v[i][j][k].isOn) { std::cout << "X "; }
				else {
					std::cout << "  ";
				};
			}
			std::cout << "\n";
		}
	}
}



void Sculptor::writeOFF(const char* filename) {
	int i, k, j, n = 0;
	int nv = 0, nf=0;
	verticie*** ver;
	fstream file;
	ver = (verticie***)malloc((nx + 1) * sizeof(verticie**));
	if (ver == NULL) {
		std::cout << "Out of memory";
		exit(0);
	}
	for (i = 0; i < (nx + 1); i++) {
		ver[i] = (verticie**)malloc((ny + 1) * sizeof(verticie*));
		for (j = 0; j < (ny + 1); j++) {
			ver[i][j] = (verticie*)malloc((nz + 1) * sizeof(verticie));
		}
	}
	for (i = 0; i < (nx + 1); i++) {
		for (j = 0; j < (ny + 1); j++) {
			for (k = 0; k < (nz + 1); k++) {
				ver[i][j][k].exists = 0;
			}
		}
	}
	//std::cout << "\n1-\n";
	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			for (k = 0; k < nz; k++) {
				if (v[i][j][k].isOn == true) {
					nf += 6;
					ver[i][j][k].exists = true; ver[i][j][k].x = i - 0.5; ver[i][j][k].y = j - 0.5; ver[i][j][k].z = k - 0.5;
					ver[i][j][k+1].exists = true; ver[i][j][k + 1].x = i - 0.5; ver[i][j][k + 1].y = j - 0.5; ver[i][j][k + 1].z = k + 0.5;
					ver[i][j+1][k].exists = true; ver[i][j + 1][k].x = i - 0.5; ver[i][j + 1][k].y = j + 0.5; ver[i][j + 1][k].z = k - 0.5;
					ver[i][j+1][k+1].exists = true; ver[i][j + 1][k + 1].x = i - 0.5; ver[i][j + 1][k + 1].y = j + 0.5; ver[i][j + 1][k + 1].z = k + 0.5;
					ver[i+1][j][k].exists = true; ver[i + 1][j][k].x = i + 0.5; ver[i + 1][j][k].y = j - 0.5; ver[i + 1][j][k].z = k - 0.5;
					ver[i+1][j][k + 1].exists = true; ver[i + 1][j][k + 1].x = i + 0.5; ver[i + 1][j][k + 1].y = j - 0.5; ver[i + 1][j][k + 1].z = k + 0.5;
					ver[i+1][j + 1][k].exists = true; ver[i + 1][j + 1][k].x = i + 0.5; ver[i + 1][j + 1][k].y = j + 0.5; ver[i + 1][j + 1][k].z = k - 0.5;
					ver[i+1][j + 1][k + 1].exists = true; ver[i + 1][j + 1][k + 1].x = i + 0.5; ver[i + 1][j + 1][k + 1].y = j + 0.5; ver[i + 1][j + 1][k + 1].z = k + 0.5;
				}
			}
		}
	}
	for (i = 0; i <= nx; i++) {
		for (j = 0; j <= ny; j++) {
			for (k = 0; k <= nz; k++) {
				if (ver[i][j][k].exists) { nv++; }
			}
		}
	}
	//std::cout << "\n2-\n";
	file.open(filename, std::ios::out);
	
	std::cout << "\nNumero de verticies: " << nv << "\n";
	std::cout << "\nNumero de faces: " << nf << "\n";
	std::cout << "\n Caminho do arquivo:" << filename << "\n";
	file << "OFF\n" << nv << " " << nf << " 0\n";
	


	for (i = 0; i < (nx + 1); i++) {
		for (j = 0; j < (ny + 1); j++) {
			for (k = 0; k < (nz + 1); k++) {
				if (ver[i][j][k].exists) {
					file << ver[i][j][k].x << " " << ver[i][j][k].y << " " << ver[i][j][k].z << "\n";
					ver[i][j][k].n = n;
					n++;
				}
			}
		}
	}nf = 0;
	for (i = 0; i < nx; i++) {
		for (j = 0; j < ny; j++) {
			for (k = 0; k < nz; k++) {
				if (v[i][j][k].isOn) {


					//-X
					file << "4 ";
					//i-0.5 j-0.5 z-0.5
					file << ver[i][j][k].n << " ";
					//i-0.5 j+0.5 z-0.5
					file << ver[i][j + 1][k].n << " ";
					//i-0.5 j+0.5 z+0.5
					file << ver[i][j + 1][k + 1].n << " ";
					//i-0.5 j-0.5 z+0.5
					file << ver[i][j][k + 1].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";


					//+X
					file << "4 ";
					//i+0.5 j-0.5 z-0.5
					file << ver[i + 1][j][k].n << " ";
					//i+0.5 j+0.5 z-0.5
					file << ver[i + 1][j + 1][k].n << " ";
					//i+0.5 j+0.5 z+0.5
					file << ver[i + 1][j + 1][k + 1].n << " ";
					//i+0.5 j-0.5 z+0.5
					file << ver[i + 1][j][k + 1].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";

					//-J
					file << "4 ";
					//i-0.5 j-0.5 z-0.5
					file << ver[i][j][k].n << " ";
					//i+0.5 j-0.5 z-0.5
					file << ver[i + 1][j][k].n << " ";
					//i+0.5 j-0.5 z+0.5
					file << ver[i + 1][j][k + 1].n << " ";
					//i-0.5 j-0.5 z+0.5
					file << ver[i][j][k + 1].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
					
					//+J
					file << "4 ";
					//i-0.5 j+0.5 z-0.5
					file << ver[i][j + 1][k].n << " ";
					//i+0.5 j+0.5 z-0.5
					file << ver[i + 1][j + 1][k].n << " ";
					//i+0.5 j+0.5 z+0.5
					file << ver[i + 1][j + 1][k + 1].n << " ";
					//i-0.5 j+0.5 z+0.5
					file << ver[i][j + 1][k + 1].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";

					//-Z
					file << "4 ";
					//i-0.5 j-0.5 z-0.5
					file << ver[i][j][k].n << " ";
					//i+0.5 j-0.5 z-0.5
					file << ver[i + 1][j][k].n << " ";
					//i+0.5 j+0.5 z-0.5
					file << ver[i + 1][j + 1][k].n << " ";
					//i-0.5 j+0.5 z-0.5
					file << ver[i][j + 1][k].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";

					//+Z
					file << "4 ";
					//i-0.5 j-0.5 z+0.5
					file << ver[i][j][k + 1].n << " ";	
					//i+0.5 j-0.5 z+0.5
					file << ver[i + 1][j][k + 1].n << " ";
					//i+0.5 j+0.5 z+0.5
					file << ver[i + 1][j + 1][k + 1].n << " ";
					//i-0.5 j+0.5 z+0.5
					file << ver[i][j + 1][k + 1].n << " ";
					file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";



					nf += 6;
					if (v[i][j][k].r == 0) { std::cout << "\nv[" << i << "][" << j << "][" << k << "]\n"; }
					}
				}
			}
		}
	std::cout << "\nSalvo nc=" << nf <<"\n";
	}









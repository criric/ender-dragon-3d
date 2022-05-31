#include "sculptor.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    this -> nx = _nx;
    this -> ny = _ny;
    this -> nz = _nz;

    this -> r = 0;
    this -> g = 0;
    this -> b = 0;
    this -> a = 0;

    v = new Voxel**[_nx];

    for(int i = 0; i < _nx; i++){
        v[i] = new Voxel*[_ny];

        for(int j = 0; j < _ny; j++){
            v[i][j] = new Voxel[_nz];

            for(int k = 0; k < _nz; k++){
                this -> v[i][j][k].isOn = false;
                this -> v[i][j][k].r = 0;
                this -> v[i][j][k].g = 0;
                this -> v[i][j][k].b = 0;
                this -> v[i][j][k].a = 0;
            }
        }
    }
}

Sculptor::~Sculptor(){
    for(int i = 0; i < nx; i++){
        for( int j = 0; j < ny; j++){
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v ;
}

void Sculptor::setColor(float _r, float _g, float _b, float _alpha){
    this -> r = _r;
    this -> g = _g;
    this -> b = _b;
    this -> a = _alpha;
}

void Sculptor::putVoxel(int x, int y, int z){
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >=0 && z < nz){
        this -> v[x][y][z].r = this -> r;
        this -> v[x][y][z].g = this -> g;
        this -> v[x][y][z].b = this -> b;
        this -> v[x][y][z].a = this -> a;
        this -> v[x][y][z].isOn = true;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    this -> v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++){
                this -> putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++){
                this -> cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    putEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    cutEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    float elipsoid;
    for(int i = xcenter - rx; i < xcenter + rx; i++){
        for(int j = ycenter - ry; j < ycenter + ry; j++){
            for(int k = zcenter - rz; k < zcenter + rz; k++){
                elipsoid = pow(i - xcenter, 2)/pow(rx,2) + pow(j - ycenter, 2)/pow(ry,2) + pow(k - zcenter,2)/pow(rz,2);
                if(elipsoid < 1){
                    this -> putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    float elipsoid;
    for(int i = xcenter - rx; i < xcenter + rx; i++){
        for(int j = ycenter - ry; j < ycenter + ry; j++){
            for(int k = zcenter - rz; k < zcenter + rz; k++){
                elipsoid = pow(i - xcenter, 2)/pow(rx,2) + pow(j - ycenter, 2)/pow(ry,2) + pow(k - zcenter,2)/pow(rz,2);
                if(elipsoid < 1){
                    this -> cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* file_name_sculptor){
    int vertex, face, edge = 0; //Vértices e faces
        int on_voxel;

        on_voxel=0;

        ofstream fout;//Pesquisar no cpp ofestream

        int p = 0;
        int cont = 0;

        fout.open(file_name_sculptor); //Abertura do arquivo

        if(!fout.is_open()){
            cout << "Falha na criação do arquivo" << "\n" << endl;
            exit(1);
        }

        //Contador de voxels ativos

        for(int k = 0; k < nz; k++){
            for(int i = 0; i < nx; i++ ){
                for(int j = 0; j < ny; j++){
                    if(v[i][j][k].isOn == true){
                        on_voxel++;
                    }
                }
            }
        }


        vertex = on_voxel*8; //Quantidade de vértices da figura

            face = on_voxel*6; //Quantidade de faces da figura


            //Para fazer a identificação
            fout << "OFF" << endl;

            //Número de faces, vértices e arestas
            fout << vertex << " " << face << " " << edge << endl;

            //Coordenadas espaciais
            for(int k = 0; k < nz; k++){
                for(int i = 0; i < nx; i++ ){
                    for(int j = 0; j < ny; j++){
                        if(v[i][j][k].isOn == true){
                            fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                            fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                            fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                            fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                            fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                            fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                            fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                            fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                        }
                    }
                }
            }

            for(int k = 0; k < nz; k++){
                    for(int i = 0; i < nx; i++ ){
                        for(int j = 0; j < ny; j++){
                            if(v[i][j][k].isOn == true){
                                p = 8 * cont;
                                fout << 4 << " " << p + 0 << " " << p + 3 << " " << p + 2 << " " << p + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                fout << 4 << " " << p + 4 << " " << p + 5 << " " << p + 6 << " " << p + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                fout << 4 << " " << p + 0 << " " << p + 1 << " " << p + 5 << " " << p + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                fout << 4 << " " << p + 0 << " " << p + 4 << " " << p + 7 << " " << p + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                fout << 4 << " " << p + 3 << " " << p + 7 << " " << p + 6 << " " << p + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                fout << 4 << " " << p + 1 << " " << p + 2 << " " << p + 6 << " " << p + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                                cont ++;
                            }
                        }
                    }
                }

            fout.close(); //Arquivo fechado
}

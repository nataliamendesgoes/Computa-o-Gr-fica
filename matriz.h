#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
#include <stdexcept>

class Matriz {
private:
    std::vector<std::vector<double>> info;

public:

    Matriz(int linhas, int colunas, double valor_inicial = 0.0);
    std::vector<double> col(int index) const;
    int linhas() const;
    int colunas() const;


    double& operator()(int linha, int coluna);
    double operator()(int linha, int coluna) const;

    Matriz operator+(const Matriz& outra) const;
    Matriz operator*(const Matriz& outra) const;
    Matriz identidade() const;
    Matriz translacao(double cx, double cy, double cz) const;
    Matriz escala(double cx, double cy, double cz) const;
    Matriz rotacaoX(double cx, double cy, double cz, double angulo) const;
    Matriz rotacaoY(double cx, double cy, double cz, double angulo) const;
    Matriz rotacaoZ(double cx, double cy, double cz, double angulo) const;
    Matriz matrizSCN(double cx, double cy, double cz, double angulo, double escalax, double escalay) const;
    Matriz matrizVPN(double cwx, double cwy, double cwz, double vpnx, double vpny, double vpnz) const;
    double atan_aprox(double x)const;
    Matriz matrizPerspectiva(double cx, double cy,double cz, double distancia) const;
};

#endif // MATRIZ_H

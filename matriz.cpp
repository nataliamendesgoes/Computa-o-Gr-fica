#include "matriz.h"
#include <iostream>
#include "objeto.h"
#include <vector>

Matriz::Matriz(int linhas, int colunas, double valor_inicial)
    : info(linhas, std::vector<double>(colunas, valor_inicial)) {}

std::vector<double> Matriz::col(int coluna) const {
    if (coluna < 0 || coluna >= colunas()) {
        throw std::out_of_range("Índice de coluna fora do intervalo.");
    }

    std::vector<double> resultado(linhas());
    for (int i = 0; i < linhas(); ++i) {
        resultado[i] = (*this)(i, coluna);
    }

    return resultado;
}


int Matriz::linhas() const {
    return info.size();
}

int Matriz::colunas() const {
    return info[0].size();
}

double& Matriz::operator()(int linha, int coluna) {
    return info[linha][coluna];
}

double Matriz::operator()(int linha, int coluna) const {
    return info[linha][coluna];
}

Matriz Matriz::operator+(const Matriz& outra) const {

    Matriz local(linhas(), colunas());
    for (int i = 0; i < linhas(); ++i) {
        for (int j = 0; j < colunas(); ++j) {
            local(i, j) = (*this)(i, j) + outra(i, j);
        }
    }
    return local;
}

Matriz Matriz::operator*(const Matriz& outra) const {
    Matriz local(linhas(), outra.colunas());
    for (int i = 0; i < linhas(); ++i) {
        for (int j = 0; j < outra.colunas(); ++j) {
            for (int k = 0; k < colunas(); ++k) {
                local(i, j) += (*this)(i, k) * outra(k, j);
            }
        }
    }
    return local;
}

Matriz Matriz::identidade() const {

    Matriz local(linhas(), colunas());

    for (int i = 0; i < linhas(); ++i) {
        for (int j = 0; j < colunas(); ++j) {
            local(i, j) = (i == j) ? 1.0 : 0.0;
        }
    }
    return local;
}
Matriz Matriz::translacao(double cx, double cy, double cz) const {
    Matriz matrizTranslacao = identidade();
    matrizTranslacao(0, 3) = cx;
    matrizTranslacao(1, 3) = cy;
    matrizTranslacao(2, 3) = cz;
    return matrizTranslacao;
}
Matriz Matriz::escala(double cx, double cy, double cz) const {
    Matriz matrizEscala = identidade();
    matrizEscala(0, 0) = cx;
    matrizEscala(1, 1) = cy;
    matrizEscala(2, 2) = cz;
    return matrizEscala;
}
Matriz Matriz::rotacaoX(double cx, double cy, double cz, double angulo) const {
    Matriz matrizRotacao = identidade();

    double rad = angulo * M_PI / 180.0;
    double cosAngulo = cos(rad);
    double sinAngulo = sin(rad);

    // rotacao em cx e cy
    matrizRotacao(1, 1) = cosAngulo;
    matrizRotacao(1, 2) = -sinAngulo;
    matrizRotacao(2, 1) = sinAngulo;
    matrizRotacao(2, 2) = cosAngulo;

    // volta origem
    Matriz matrizTranslacaoOrigem(4, 4);
    matrizTranslacaoOrigem = identidade();
    matrizTranslacaoOrigem(0, 3) = -cx;
    matrizTranslacaoOrigem(1, 3) = -cy;
    matrizTranslacaoOrigem(2, 3) = -cz;

    // volta local original
    Matriz matrizTranslacaoVolta(4, 4);
    matrizTranslacaoVolta = identidade();
    matrizTranslacaoVolta(0, 3) = cx;
    matrizTranslacaoVolta(1, 3) = cy;
    matrizTranslacaoVolta(2, 3) = cz;


    return matrizTranslacaoVolta * matrizRotacao * matrizTranslacaoOrigem;
}
Matriz Matriz::rotacaoY(double cx, double cy, double cz, double angulo) const {
    Matriz matrizRotacao = identidade();

    double rad = angulo * M_PI / 180.0;
    double cosAngulo = cos(rad);
    double sinAngulo = sin(rad);

    // rotacao em cx e cy
    matrizRotacao(0, 0) = cosAngulo;
    matrizRotacao(2, 0) = -sinAngulo;
    matrizRotacao(0, 2) = sinAngulo;
    matrizRotacao(2, 2) = cosAngulo;

    // volta origem
    Matriz matrizTranslacaoOrigem(4, 4);
    matrizTranslacaoOrigem = identidade();
    matrizTranslacaoOrigem(0, 3) = -cx;
    matrizTranslacaoOrigem(1, 3) = -cy;
    matrizTranslacaoOrigem(2, 3) = -cz;

    // volta local original
    Matriz matrizTranslacaoVolta(4, 4);
    matrizTranslacaoVolta = identidade();
    matrizTranslacaoVolta(0, 0) = cx;
    matrizTranslacaoVolta(1, 1) = cy;
    matrizTranslacaoVolta(1, 2) = cz;


    return matrizTranslacaoVolta * matrizRotacao * matrizTranslacaoOrigem;
}
Matriz Matriz::rotacaoZ(double cx, double cy, double cz, double angulo) const {
    Matriz matrizRotacao = identidade();

    double rad = angulo * M_PI / 180.0;
    double cosAngulo = cos(rad);
    double sinAngulo = sin(rad);

    // rotacao em cx e cy
    matrizRotacao(0, 0) = cosAngulo;
    matrizRotacao(0, 1) = -sinAngulo;
    matrizRotacao(1, 0) = sinAngulo;
    matrizRotacao(1, 1) = cosAngulo;

    // volta origem
    Matriz matrizTranslacaoOrigem(4, 4);
    matrizTranslacaoOrigem = identidade();
    matrizTranslacaoOrigem(0, 3) = -cx;
    matrizTranslacaoOrigem(1, 3) = -cy;
    matrizTranslacaoOrigem(2, 3) = -cz;

    // volta local original
    Matriz matrizTranslacaoVolta(4, 4);
    matrizTranslacaoVolta = identidade();
    matrizTranslacaoVolta(0, 3) = cx;
    matrizTranslacaoVolta(1, 3) = cy;
    matrizTranslacaoVolta(2, 3) = cz;


    return matrizTranslacaoVolta * matrizRotacao * matrizTranslacaoOrigem;
}
Matriz Matriz::matrizSCN(double cx, double cy,double cz, double angulo, double escalax, double escalay) const {
    Matriz matrizRotacao(4, 4);
    matrizRotacao = matrizRotacao.identidade();

    double rad = angulo * M_PI / 180.0;
    double cosAngulo = cos(rad);
    double sinAngulo = sin(rad);

    // Matriz de rotação
    matrizRotacao(0, 0) = cosAngulo;  // Índices base 0
    matrizRotacao(0, 1) = -sinAngulo;
    matrizRotacao(1, 0) = sinAngulo;
    matrizRotacao(1, 1) = cosAngulo;

    Matriz matrizTranslacaoParaOrigem(4, 4);
    matrizTranslacaoParaOrigem = matrizTranslacaoParaOrigem.identidade();
    matrizTranslacaoParaOrigem(0, 3) = -cx;
    matrizTranslacaoParaOrigem(1, 3) = -cy;
    matrizTranslacaoParaOrigem(2, 3) = -cz;


    Matriz matrizEscala(4, 4);
    matrizEscala = matrizEscala.identidade();
    matrizEscala(0, 0) = escalax;
    matrizEscala(1, 1) = escalay;


    Matriz matrizTranslacaoDeVolta(4, 4);
    matrizTranslacaoDeVolta = matrizTranslacaoDeVolta.identidade();
    matrizTranslacaoDeVolta(0, 3) = cx;
    matrizTranslacaoDeVolta(1, 3) = cy;
    matrizTranslacaoDeVolta(2, 3) = cz;

    return matrizTranslacaoDeVolta * matrizRotacao * matrizEscala * matrizTranslacaoParaOrigem;
}
Matriz Matriz::matrizPerspectiva(double cx, double cy,double cz, double distancia) const {

    Matriz matrizTranslacaoParaOrigem(4, 4);
    matrizTranslacaoParaOrigem = matrizTranslacaoParaOrigem.identidade();
    matrizTranslacaoParaOrigem(0, 3) = -cx;
    matrizTranslacaoParaOrigem(1, 3) = -cy;
    matrizTranslacaoParaOrigem(2, 3) = -cz;


    Matriz matrizperspectiva(4, 4);
    matrizperspectiva = matrizperspectiva.identidade();
    matrizperspectiva(3, 2) = -1/distancia;
    matrizperspectiva(3, 3) = 0;

    Matriz matrizTranslacaoDeVolta(4, 4);
    matrizTranslacaoDeVolta = matrizTranslacaoDeVolta.identidade();
    matrizTranslacaoDeVolta(0, 3) = cx;
    matrizTranslacaoDeVolta(1, 3) = cy;
    matrizTranslacaoDeVolta(2, 3) = cz;

    return matrizTranslacaoDeVolta * matrizperspectiva * matrizTranslacaoParaOrigem;
}

double Matriz::atan_aprox(double x) const {
    if (x < 1.0 && x > -1.0) {
        double x2 = x * x;
        return x * (1 - x2 / 3 + x2 * x2 / 5 - x2 * x2 * x2 / 7);
    } else {
        return 1.5708 - atan_aprox(1 / x);
    }
}

Matriz Matriz::matrizVPN(double cwx, double cwy, double cwz, double vpnx, double vpny, double vpnz) const {

    Ponto VPN = {vpnx - cwx, vpny - cwy, vpnz - cwz};

    double magnitude = std::sqrt(VPN.x() * VPN.x() + VPN.y() * VPN.y() + VPN.z() * VPN.z());
    if (magnitude == 0) {
        qDebug() << "Erro: VPN é o vetor nulo!";
        return Matriz::identidade();
    }

    VPN = {VPN.x() / magnitude, VPN.y() / magnitude, VPN.z() / magnitude};

    double theta_x = std::atan2(VPN.y(), VPN.z());  // Em radianos
    double theta_y = std::atan2(VPN.x(), VPN.z());  // Em radianos

    qDebug() << "Theta X (radianos):" << theta_x << "Theta Y (radianos):" << theta_y;

    // rotação em X
    Matriz matrizRotacaoX(4, 4);
    matrizRotacaoX = matrizRotacaoX.identidade();
    matrizRotacaoX(1, 1) = std::cos(theta_x);
    matrizRotacaoX(1, 2) = -std::sin(theta_x);
    matrizRotacaoX(2, 1) = std::sin(theta_x);
    matrizRotacaoX(2, 2) = std::cos(theta_x);

    // rotação em Y
    Matriz matrizRotacaoY(4, 4);
    matrizRotacaoY = matrizRotacaoY.identidade();
    matrizRotacaoY(0, 0) = std::cos(theta_y);
    matrizRotacaoY(0, 2) = std::sin(theta_y);
    matrizRotacaoY(2, 0) = -std::sin(theta_y);
    matrizRotacaoY(2, 2) = std::cos(theta_y);

    Matriz matrizTranslacaoParaOrigem(4, 4);
    matrizTranslacaoParaOrigem = matrizTranslacaoParaOrigem.identidade();
    matrizTranslacaoParaOrigem(0, 3) = -cwx;
    matrizTranslacaoParaOrigem(1, 3) = -cwy;
    matrizTranslacaoParaOrigem(2, 3) = -cwz;

    Matriz matrizTranslacaoDeVolta(4, 4);
    matrizTranslacaoDeVolta = matrizTranslacaoDeVolta.identidade();
    matrizTranslacaoDeVolta(0, 3) = cwx;
    matrizTranslacaoDeVolta(1, 3) = cwy;
    matrizTranslacaoDeVolta(2, 3) = cwz;

    return matrizTranslacaoDeVolta * matrizRotacaoY * matrizRotacaoX * matrizTranslacaoParaOrigem;
}



//Translação: Muda um objeto de lugar
// Rotação: Muda a orientação de um objeto
// Escala: Muda o tamanho de um objeto

#ifndef OBJETOS_H
#define OBJETOS_H

#include <QString>
#include <QPainter>
#include <QPolygon>
#include "matriz.h"
#include <QDebug>

class Ponto {
private:
    Matriz P;

public:

    Ponto(): P(4, 3) {
        this->P(0, 0) = 0;
        this->P(1, 0) = 0;
        this->P(2, 0) = 0;
        this->P(3, 0) = 1;
        this->P(0, 1) = 0;
        this->P(1, 1) = 0;
        this->P(2, 1) = 0;
        this->P(3, 1) = 1;
        this->P(0, 2) = 0;
        this->P(1, 2) = 0;
        this->P(2, 2) = 0;
        this->P(3, 2) = 1;
    }


    Ponto(double x, double y, double z): P(4, 3) {
        this->P(0, 0) = x;
        this->P(1, 0) = y;
        this->P(2, 0) = z;
        this->P(3, 0) = 1;
        this->P(0, 1) = 0;
        this->P(1, 1) = 0;
        this->P(2, 1) = 0;
        this->P(3, 1) = 1;
        this->P(0, 2) = 0;
        this->P(1, 2) = 0;
        this->P(2, 2) = 0;
        this->P(3, 2) = 1;
    }


    double x() const { return this->P(0, 0); }
    double y() const { return this->P(1, 0); }
    double z() const { return this->P(2, 0); }


    double xNormalizado() const { return this->P(0, 1); }
    double yNormalizado() const { return this->P(1, 1); }
    double zNormalizado() const { return this->P(2, 1); }

    double xViewPort() const { return this->P(0, 2); }
    double yViewPort() const { return this->P(1, 2); }
    double zViewPort() const { return this->P(2, 2); }

    void setX(double x) { this->P(0, 0) = x; }
    void setY(double y) { this->P(1, 0) = y; }
    void setZ(double z) { this->P(2, 0) = z; }


    void setXNormalizado(double x) { this->P(0, 1) = x; }
    void setYNormalizado(double y) { this->P(1, 1) = y; }
    void setZNormalizado(double z) { this->P(2, 1) = z; }

    void setViewPort(double x) { this->P(0, 2) = x; }
    void setYViwPort(double y) { this->P(1, 2) = y; }
    void setZViwPort(double z) { this->P(2, 2) = z; }


    Ponto transforma(const Matriz& matrizTransformacao) const {
        Matriz resultado = matrizTransformacao * P;

        Ponto pontoTransformado(resultado(0, 0), resultado(1, 0), resultado(2,0));


        pontoTransformado.setXNormalizado(resultado(0, 0));
        pontoTransformado.setYNormalizado(resultado(1, 0));
        pontoTransformado.setZNormalizado(resultado(2, 0));

        return pontoTransformado;
    }
    Matriz getP() const { return P; }

    void setP(int row, int col, double value) {
        if (row >= 0 && row < 4 && col >= 0 && col < 3) { // Valida índices
            P(row, col) = value;
        } else {
            qDebug() << "Índices inválidos para setP:" << row << col;
        }
    }
};

class Objeto {
public:
    QString nome;
    QString tipo;
    QList<Ponto> pontos;
    QList<Objeto> linhas;
    Ponto centro;
    QList<QList<int>> faces;
    QString textura; // Caminho da textura

    Objeto(){}


    void aplicaTransformacao(const Matriz& matrizTransformacao) {
        for (Ponto& ponto : pontos) {
            ponto = ponto.transforma(matrizTransformacao);
        }
    }
    Objeto(QString nome, QList<Ponto> pontos, QList<QList<int>> faces)
        : nome(nome), pontos(pontos), faces(faces) {}

    void setTextura(const QString& caminhoTextura) {
        textura = caminhoTextura;
    }

    QString getTextura() const {
        return textura;
    }

    //ponto
    Objeto(QString _nome, double _x, double _y, double _z) {
        this->nome = _nome;
        this->tipo = "ponto";

        pontos.append(Ponto(_x, _y, _z));
        centro = Ponto(_x, _y, _z);
    }
    Objeto(QString _nome, const Ponto& p1, const Ponto& p2) {
        this->nome = _nome;
        this->tipo = "linha";

        pontos.append(p1);
        pontos.append(p2);

        centro = Ponto(calculaCentroX(), calculaCentroY(), calculaCentroZ());
    }
    //linha
    Objeto(QString _nome, double _x1, double _y1, double _z1,double _x2, double _y2, double _z2 ) {
        this->nome = _nome;
        this->tipo = "linha";

        pontos.append(Ponto(_x1, _y1, _z1));
        pontos.append(Ponto(_x2, _y2, _z2));
        centro = Ponto(calculaCentroX(), calculaCentroY(), calculaCentroZ());
    }

    //triangulo
    Objeto(QString _nome, double _x1, double _y1,double _z1, double _x2, double _y2,double _z2, double _x3, double _y3,  double _z3) {
        this->nome = _nome;
        this->tipo = "triangulo";
        pontos.append(Ponto(_x1, _y1, _z1));
        pontos.append(Ponto(_x2, _y2, _z2));
        pontos.append(Ponto(_x3, _y3, _z3));

        // Criar as linhas do triângulo
        linhas.append(Objeto("Lado1", _x1, _y1, _z1, _x2, _y2, _z2));
        linhas.append(Objeto("Lado2", _x2, _y2, _z2, _x3, _y3, _z3));
        linhas.append(Objeto("Lado3", _x3, _y3, _z3, _x1, _y1, _z1));

        // Calcular o centro do triângulo
        centro = Ponto(calculaCentroX(), calculaCentroY(), calculaCentroZ());
    }

    Objeto(QString _nome, double _x1, double _y1, double _z1,double _x2, double _y2,double _z2, double _x3, double _y3, double _z3,double _x4, double _y4, double _z4) {
        this->nome = _nome;
        this->tipo = "retangulo";

        // Adicionar os vértices
        pontos.append(Ponto(_x1, _y1, _z1));
        pontos.append(Ponto(_x2, _y2, _z2));
        pontos.append(Ponto(_x3, _y3, _z3));
        pontos.append(Ponto(_x4, _y4, _z4));

        // Criar as linhas
        linhas.append(Objeto("Lado1", _x1, _y1,_z1, _x2, _y2, _z2));
        linhas.append(Objeto("Lado2", _x2, _y2,_z2, _x3, _y3, _z3));
        linhas.append(Objeto("Lado3", _x3, _y3,_z3, _x4, _y4, _z4));
        linhas.append(Objeto("Lado4", _x4, _y4,_z4, _x1, _y1, _z1));

        // Calcular o centro
        centro = Ponto(calculaCentroX(), calculaCentroY(), calculaCentroZ());
    }

    // Construtor para Estrela
    Objeto(QString _nome, double _x1, double _y1, double _z1, double _x2, double _y2, double _z2,double _x3, double _y3,double _z3,
           double _x4, double _y4, double _z4,double _x5, double _y5, double _z5,double _x6, double _y6, double _z6, double _x7,
           double _y7,double _z7, double _x8, double _y8,double _z8,  double _x9, double _y9, double _z9, double _x10, double _y10, double _z10) {
        this->nome = _nome;
        this->tipo = "estrela";

        // Adicionar os vértices
        pontos.append(Ponto(_x1, _y1, _z1));
        pontos.append(Ponto(_x2, _y2, _z2));
        pontos.append(Ponto(_x3, _y3, _z3));
        pontos.append(Ponto(_x4, _y4, _z4));
        pontos.append(Ponto(_x5, _y5, _z5));
        pontos.append(Ponto(_x6, _y6, _z6));
        pontos.append(Ponto(_x7, _y7, _z7));
        pontos.append(Ponto(_x8, _y8, _z8));
        pontos.append(Ponto(_x9, _y9, _z9));
        pontos.append(Ponto(_x10, _y10, _z10));

        // Criar as linhas
        linhas.append(Objeto("Lado1", _x1, _y1,_z1, _x2, _y2, _z2));
        linhas.append(Objeto("Lado2", _x2, _y2,_z2, _x3, _y3, _z3));
        linhas.append(Objeto("Lado3", _x3, _y3,_z3, _x4, _y4, _z4));
        linhas.append(Objeto("Lado4", _x4, _y4,_z4, _x5, _y5, _z5));
        linhas.append(Objeto("Lado5", _x5, _y5,_z5, _x6, _y6, _z6));
        linhas.append(Objeto("Lado6", _x6, _y6,_z6, _x7, _y7, _z7));
        linhas.append(Objeto("Lado7", _x7, _y7,_z7, _x8, _y8, _z8));
        linhas.append(Objeto("Lado8", _x8, _y8,_z8, _x9, _y9, _z9));
        linhas.append(Objeto("Lado9", _x9, _y9,_z9, _x10, _y10, _z10));
        linhas.append(Objeto("Lado10", _x10, _y10, _z10, _x1, _y1, _z1));

        // Calcular o centro
        centro = Ponto(calculaCentroX(), calculaCentroY(), calculaCentroZ());
    }

    // Funções auxiliares para cálculo do centro
    double calculaCentroX() const {
        double somaX = 0.0;
        for (const Ponto& ponto : pontos) {
            somaX += ponto.x();
        }
        return pontos.isEmpty() ? 0 : somaX / pontos.size();
    }

    double calculaCentroY() const {
        double somaY = 0.0;
        for (const Ponto& ponto : pontos) {
            somaY += ponto.y();
        }
        return pontos.isEmpty() ? 0 : somaY / pontos.size();
    }
    double calculaCentroZ() const {
        double somaZ = 0.0;
        for (const Ponto& ponto : pontos) {
            somaZ += ponto.z();
        }
        return pontos.isEmpty() ? 0 : somaZ / pontos.size();
    }
    void transformaLinhaParaViewport(const Matriz& matrizNormalizacao, const Matriz& matrizViewport) {
        for (Objeto& linha : linhas) {
            if (linha.tipo == "linha" && linha.pontos.size() == 2) {
                // Transformar os dois pontos da linha
                linha.pontos[0] = linha.pontos[0].transforma(matrizNormalizacao).transforma(matrizViewport);
                linha.pontos[1] = linha.pontos[1].transforma(matrizNormalizacao).transforma(matrizViewport);
            }
        }
    }


};

#endif // OBJETOS_H


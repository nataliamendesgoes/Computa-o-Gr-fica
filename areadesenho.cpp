#include <QPainter>
#include <QFrame>
#include <QDebug>
#include "areadesenho.h"
#include "matriz.h"
#include <vector>
#include "clipping.h"
#include <fstream>
#include <sstream>
#include <QString>
#include <QFile>

AreaDesenho::AreaDesenho(QWidget *parent)
    : QFrame(parent) {

    window.setRect(960, 480, 600, 600);
    preencherDisplayFile();
}
void AreaDesenho::carregarObj1(const QString& caminhoArquivoObj, const QString& caminhoArquivoMtl) {
    QFile fileObj(caminhoArquivoObj);
    QFile fileMtl(caminhoArquivoMtl);

    if (!fileObj.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erro ao abrir o arquivo OBJ!";
        return;
    }

    QTextStream inObj(&fileObj);
    QList<Ponto> pontos;
    QList<QList<int>> faces;
    QMap<QString, QString> materiais;
    QString materialAtual;

    // arquivo .obj
    while (!inObj.atEnd()) {
        QString linha = inObj.readLine();
        QStringList partes = linha.split(" ", Qt::SkipEmptyParts);
        if (partes.isEmpty()) continue;

        if (partes[0] == "mtllib") {
            qDebug() << "Material encontrado:" << partes[1];
        } else if (partes[0] == "usemtl") {
            materialAtual = partes[1];
        } else if (partes[0] == "v") {
            if (partes.size() >= 4) {
                double x = partes[1].toDouble();
                double y = partes[2].toDouble();
                double z = partes[3].toDouble();
                pontos.append(Ponto(x, y, z));
            }
        } else if (partes[0] == "f") {
            QList<int> face;
            for (int i = 1; i < partes.size(); i++) {
                int index = partes[i].toInt() - 1;
                if (index >= 0 && index < pontos.size()) {
                    face.append(index);
                }
            }
            faces.append(face);
        }
    }
    fileObj.close();

    //  arquivo .mtl
    if (fileMtl.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream inMtl(&fileMtl);
        QString materialNome;
        while (!inMtl.atEnd()) {
            QString linha = inMtl.readLine();
            QStringList partes = linha.split(" ", Qt::SkipEmptyParts);
            if (partes.isEmpty()) continue;

            if (partes[0] == "newmtl") {
                materialNome = partes[1];
            } else if (partes[0] == "map_Kd") {
                if (!materialNome.isEmpty()) {
                    materiais[materialNome] = partes[1];
                    qDebug() << "Material:" << materialNome << "-> Textura:" << partes[1];
                }
            }
        }
        fileMtl.close();
    } else {
        qDebug() << "Erro ao abrir o arquivo MTL!";
    }

    // adicionar ao displayFile
    if (!pontos.isEmpty()) {
        Objeto objeto("Pokemon1", pontos, faces);
        objeto.setTextura(materiais[materialAtual]);
        displayFile.append(objeto);
        listaWindow.append(objeto);
    } else {
        qDebug() << "Nenhum ponto foi carregado!";
    }
}
void AreaDesenho::carregarObj2(const QString& caminhoArquivoObj, const QString& caminhoArquivoMtl) {
    QFile fileObj(caminhoArquivoObj);
    QFile fileMtl(caminhoArquivoMtl);

    if (!fileObj.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erro ao abrir o arquivo OBJ!";
        return;
    }

    QTextStream inObj(&fileObj);
    QList<Ponto> pontos;
    QList<QList<int>> faces;
    QMap<QString, QString> materiais;
    QString materialAtual;

    //  arquivo .obj
    while (!inObj.atEnd()) {
        QString linha = inObj.readLine();
        QStringList partes = linha.split(" ", Qt::SkipEmptyParts);
        if (partes.isEmpty()) continue;

        if (partes[0] == "mtllib") {
            qDebug() << "Material encontrado:" << partes[1];
        } else if (partes[0] == "usemtl") {
            materialAtual = partes[1];
        } else if (partes[0] == "v") {
            if (partes.size() >= 4) {
                double x = partes[1].toDouble();
                double y = partes[2].toDouble();
                double z = partes[3].toDouble();
                pontos.append(Ponto(x, y, z));
            }
        } else if (partes[0] == "f") {
            QList<int> face;
            for (int i = 1; i < partes.size(); i++) {
                int index = partes[i].toInt() - 1;
                if (index >= 0 && index < pontos.size()) {
                    face.append(index);
                }
            }
            faces.append(face);
        }
    }
    fileObj.close();

    //  arquivo .mtl
    if (fileMtl.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream inMtl(&fileMtl);
        QString materialNome;
        while (!inMtl.atEnd()) {
            QString linha = inMtl.readLine();
            QStringList partes = linha.split(" ", Qt::SkipEmptyParts);
            if (partes.isEmpty()) continue;

            if (partes[0] == "newmtl") {
                materialNome = partes[1];
            } else if (partes[0] == "map_Kd") {
                if (!materialNome.isEmpty()) {
                    materiais[materialNome] = partes[1];
                    qDebug() << "Material:" << materialNome << "-> Textura:" << partes[1];
                }
            }
        }
        fileMtl.close();
    } else {
        qDebug() << "Erro ao abrir o arquivo MTL!";
    }

    //  adicionar ao displayFile
    if (!pontos.isEmpty()) {
        Objeto objeto("Pokemon2", pontos, faces);
        objeto.setTextura(materiais[materialAtual]); // Associa a textura ao objeto
        displayFile.append(objeto);
        listaWindow.append(objeto);
    } else {
        qDebug() << "Nenhum ponto foi carregado!";
    }
}


void AreaDesenho::preencherDisplayFile() {
    qDebug() << "Testando qDebug";
    if (displayFile.isEmpty()) {
        Objeto tela;
        Ponto pw1(960, 480, 1), pw2(1560, 480, 1), pw3(1560, 1080, 1), pw4(960, 1080, 1);
        tela.pontos << pw1 << pw2 << pw3 << pw4;
        tela.nome = "tela coordenada mundo";

        Objeto window("window", -1, -1, 1, -1, 1, 1, 1, -1, 1,1,1,1);
        qDebug() << "Testando qDebug";
        Objeto l1("linha 1", -50, -50, 2, 200, 200, 3),
            t1("triangulo 1", 200, 200, 1, 500, 200, 2, 350, 100, 3),
            r1("retangulo 1", 100, 400, 1, 200, 400, 2, 200, 500, 3, 100, 500, 4),
            r2("retangulo 2", 300, 400,4, 600, 400,3, 600, 600, 2, 300, 600, 4),
            estrela("estrela 1",  425, 390,1, 350, 340,2, 275, 390,3, 300, 315,4,250,
                    265, 5,325, 265, 6,350, 190,7,375, 265, 8,450, 265, 9,400, 315, 10);

        QString pokemon1("C:\\Users\\natal\\OneDrive\\Área de Trabalho\\Faculdade\\4° semestre\\CG\\entrega5teste\\80-pikachu\\Pikachu_OBJ.obj");
        QString pokemon1mlt("C:\\Users\\natal\\OneDrive\\Área de Trabalho\\Faculdade\\4° semestre\\CG\\entrega5teste\\80-pikachu\\Pikachu_MTl.mtl");

        carregarObj1(pokemon1, pokemon1mlt);

        QString pokemon2("C:\\Users\\natal\\OneDrive\\Área de Trabalho\\Faculdade\\4° semestre\\CG\\entrega5teste\\Charizard\\006 - Charizard\\P2_CharizardWP.obj");
        QString pokemon2mtl("C:\\Users\\natal\\OneDrive\\Área de Trabalho\\Faculdade\\4° semestre\\CG\\entrega5teste\\Charizard\\006 - Charizard\\P2_CharizardWP.mtl");


        carregarObj2(pokemon2, pokemon2mtl);

        displayFile.append(tela);
        displayFile.append(window);
        qDebug() << "Tamanho de displayFile apos preenchimento:" << displayFile.size();
    }
}



void AreaDesenho::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);

    QRect viewport(50, 50, 400, 400);
    painter.drawRect(viewport);

    qDebug() << "Chamando calcularVPN no paintEvent...";
    calcularVPN();
    qDebug() << "Chamando perspectiva no paintEvent...";
    perspectiva();
    qDebug() << "Chamando a funcao de escala no paintEvent...";
    escalarObjeto();
    qDebug() << "Chamando a funcao de rotacao no paintEvent...";
    rotacionarXObjeto();
    qDebug() << "Chamando a funcao de translacao no paintEvent...";
    transladarObjeto();
    qDebug() << "Chamando coordenadasnormalizada no paintEvent...";
    coordenadasnormalizada(painter);
}

void AreaDesenho::perspectiva() {
    double d = 200; // Distância do plano de projeção
    Ponto COP = {0, 0, 200}; // Centro de projeção

    // matriz de perspectiva
    Matriz pers(4, 4);
    pers = pers.matrizPerspectiva(0, 0, d , d);

    qDebug() << "Matriz de perspectiva:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << pers(i, j);
        }
    }

    for (Objeto& objeto : displayFile) {
        Objeto& objetoperspectiva = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }

        for (Ponto& ponto : objetoperspectiva.pontos) {
            Matriz coordenadas = ponto.getP();
            Matriz resultado = pers * coordenadas;

            double x_perspectiva = resultado(0, 0);
            double y_perspectiva = resultado(1, 0);
            double z_perspectiva = resultado(2, 0);

            ponto.setP(0, 0, x_perspectiva);
            ponto.setP(1, 0, y_perspectiva);
            ponto.setP(2, 0, z_perspectiva);

            // qDebug() << "Ponto perspectiva:" << x_perspectiva << y_perspectiva;
        }
    }
}

void AreaDesenho::calcularVPN(){
    Ponto COP = {0, 0 ,0};

    Matriz matrizVpn(4, 4);
    matrizVpn = matrizVpn.matrizVPN(0, 0, 200, 0, 0,0);

    qDebug() << "Matriz de VPN:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizVpn(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoperspectiva = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }

        for (Ponto& ponto : objetoperspectiva.pontos) {
            Matriz coordenadas = ponto.getP();
            Matriz resultado = matrizVpn * coordenadas;

            double x_vpn = resultado(0,0);
            double y_vpn= resultado(1,0);
            double z_vpn = resultado(2, 0);

            ponto.setP(0, 0, x_vpn);
            ponto.setP(1, 0, y_vpn);
            ponto.setP(2, 0, z_vpn);


            //qDebug() << "Ponto vpn:" << x_vpn << y_vpn <<z_vpn;
        }
    }

}
void AreaDesenho::escalarObjeto(){


    Matriz matrizEscala(4, 4);


    qDebug() << "Matriz de escala:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizEscala(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoEscala = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }
        if(objeto.nome =="Pokemon1")
            matrizEscala = matrizEscala.escala(40, 40, 1);
        else
            matrizEscala = matrizEscala.escala(10, 10, 1);

        for (Ponto& ponto : objetoEscala.pontos) {
            Matriz coordenadas = ponto.getP();
            Matriz resultado = matrizEscala * coordenadas;

            double x_vpn = resultado(0,0);
            double y_vpn= resultado(1,0);
            double z_vpn = resultado(2, 0);

            ponto.setP(0, 0, x_vpn);
            ponto.setP(1, 0, y_vpn);
            ponto.setP(2, 0, z_vpn);


            //qDebug() << "Ponto vpn:" << x_vpn << y_vpn <<z_vpn;
        }
    }

}
void AreaDesenho::rotacionarXObjeto(){


    Matriz matrizRotacao(4, 4);
    matrizRotacao = matrizRotacao.rotacaoX(0, 0, 0, 180);

    qDebug() << "Matriz de escala:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizRotacao(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoRotacao = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }
        if(objeto.nome =="Pokemon1"){


            for (Ponto& ponto : objetoRotacao.pontos) {
                Matriz coordenadas = ponto.getP();
                Matriz resultado = matrizRotacao * coordenadas;

                double x = resultado(0,0);
                double y= resultado(1,0);
                double z = resultado(2, 0);

                ponto.setP(0, 0, x);
                ponto.setP(1, 0, y);
                ponto.setP(2, 0, z);
            }
        }
    }

}
void AreaDesenho::rotacionarYObjeto(){


    Matriz matrizRotacao(4, 4);
    matrizRotacao = matrizRotacao.rotacaoY(0, 0, 0, 180);

    qDebug() << "Matriz de escala:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizRotacao(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoRotacao = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }
        if(objeto.nome =="Pokemon1"){


            for (Ponto& ponto : objetoRotacao.pontos) {
                Matriz coordenadas = ponto.getP();
                Matriz resultado = matrizRotacao * coordenadas;

                double x = resultado(0,0);
                double y= resultado(1,0);
                double z = resultado(2, 0);

                ponto.setP(0, 0, x);
                ponto.setP(1, 0, y);
                ponto.setP(2, 0, z);
            }
        }
    }

}
void AreaDesenho::rotacionarZObjeto(){


    Matriz matrizRotacao(4, 4);
    matrizRotacao = matrizRotacao.rotacaoZ(0, 0, 0, 180);

    qDebug() << "Matriz de escala:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizRotacao(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoRotacao = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }
        if(objeto.nome =="Pokemon1"){


            for (Ponto& ponto : objetoRotacao.pontos) {
                Matriz coordenadas = ponto.getP();
                Matriz resultado = matrizRotacao * coordenadas;

                double x = resultado(0,0);
                double y= resultado(1,0);
                double z = resultado(2, 0);

                ponto.setP(0, 0, x);
                ponto.setP(1, 0, y);
                ponto.setP(2, 0, z);
            }
        }
    }

}
void AreaDesenho::transladarObjeto(){


    Matriz matrizTranslacao(4, 4);


    qDebug() << "Matriz de tranlacao:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << matrizTranslacao(i, j);
        }
    }
    for (Objeto& objeto : displayFile) {
        Objeto& objetoTranslacao = objeto;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }
        if(objeto.nome =="Pokemon1")
            matrizTranslacao = matrizTranslacao.translacao(100, 350, 1);
        else
            matrizTranslacao = matrizTranslacao.translacao(400, 350, 1);

        for (Ponto& ponto : objetoTranslacao.pontos) {
            Matriz coordenadas = ponto.getP();
            Matriz resultado = matrizTranslacao * coordenadas;

            double x = resultado(0,0);
            double y= resultado(1,0);
            double z = resultado(2, 0);

            ponto.setP(0, 0, x);
            ponto.setP(1, 0, y);
            ponto.setP(2, 0, z);
        }
    }

}
void AreaDesenho::coordenadasnormalizada(QPainter &painter) {

    QRect viewport(50, 50, 400, 400);
    painter.drawRect(viewport);
    const double xmin_normalizado = 0;
    const double ymin_normalizado = 0;
    const double zmin_normalizado = 0;
    const double xmax_normalizado = 1.0;
    const double ymax_normalizado = 1.0;
    const double zmax_normalizado = 1.0;

    double vpMinX = 50, vpMinY = 50;
    double vpMaxX = 450, vpMaxY = 450;


    double Xwmin = 960, Ywmin = 480;
    double Xwmax = 1560, Ywmax = 1080;
    double Zwmin = 0, Zwmax = 500;

    double largura_window = vpMaxX - vpMinX;
    double altura_window = vpMaxY - vpMinY;
    double largura_viewport = Xwmax - Xwmin;
    double altura_viewport = Ywmax - Ywmin;

    double escalax =  largura_window / largura_viewport;
    double escalay =  altura_window / altura_viewport;


    Matriz transformacao(4, 4);
    transformacao = transformacao.matrizSCN(191, 191, 191, 0, escalax, escalay);


    qDebug() << "Matriz de transformação:";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            qDebug() << transformacao(i, j);
        }
    }

    for (Objeto& objeto : displayFile) {
        Objeto objetoNormalizado = objeto;
        Objeto objetoClipping;
        objetoClipping.nome = objeto.nome;
        qDebug() << "Processando objeto:" << objeto.nome;

        if (objeto.nome == "tela coordenada mundo" || objeto.nome == "window") {
            qDebug() << "Objeto ignorado:" << objeto.nome;
            continue;
        }

        for (Ponto& ponto : objetoNormalizado.pontos) {
            qDebug() << "Ponto original:" << ponto.x() << ponto.y();
            Matriz coordenadas = ponto.getP();
            Matriz resultado = transformacao * coordenadas;

            double x_normalizado = ((resultado(0,0) - vpMinX) / largura_window);
            double y_normalizado = ((resultado(1,0) - vpMinY) / altura_window);
            ponto.setP(0, 1, x_normalizado);
            ponto.setP(1, 1, y_normalizado);
            ponto.setP(2, 1, 1.0);

        }

        for (size_t i = 0; i < objetoNormalizado.pontos.size()-1; ++i) {

            double x1_normalizado = objetoNormalizado.pontos[i].xNormalizado();
            double y1_normalizado = objetoNormalizado.pontos[i].yNormalizado();
            double x2_normalizado = objetoNormalizado.pontos[i+1].xNormalizado();
            double y2_normalizado = objetoNormalizado.pontos[i+1].yNormalizado();

            // Clipping
            //qDebug() << "Ponto antes do clipping: (" << x1_normalizado << ", " << y1_normalizado << ") -> ("
                //<< x2_normalizado << ", " << y2_normalizado << ")";
            if (cohenSutherlandClip(xmin_normalizado, ymin_normalizado, xmax_normalizado, ymax_normalizado,
                                    x1_normalizado, y1_normalizado, x2_normalizado, y2_normalizado)) {

                double x1_viewport = vpMinX + x1_normalizado * (vpMaxX - vpMinX);
                double y1_viewport = vpMinY + y1_normalizado * (vpMaxY - vpMinY);
                double x2_viewport = vpMinX + x2_normalizado * (vpMaxX - vpMinX);
                double y2_viewport = vpMinY + y2_normalizado * (vpMaxY - vpMinY);

                objeto.pontos[i].setP(0, 2, x1_viewport);
                objeto.pontos[i].setP(1, 2, y1_viewport);
                objeto.pontos[i].setP(2, 2, 1.0);

                objeto.pontos[i+1].setP(0, 2, x2_viewport);
                objeto.pontos[i+1].setP(1, 2, y2_viewport);
                objeto.pontos[i+1].setP(2, 2, 1.0);

                if(objeto.nome == "Pokemon1")
                    painter.setPen(QPen(Qt::yellow, 2));
                else
                    painter.setPen(QPen(Qt::blue, 2));
                painter.drawLine(static_cast<int>(x1_viewport), static_cast<int>(y1_viewport),
                                 static_cast<int>(x2_viewport), static_cast<int>(y2_viewport));

            }else{
                qDebug()<<"Linha fora";
                objeto.pontos[i].setP(0, 2, -1);
                objeto.pontos[i].setP(1, 2, -1);
                objeto.pontos[i].setP(2, 2, 1.0);

                objeto.pontos[i+1].setP(0, 2, -1);
                objeto.pontos[i+1].setP(1, 2, -1);
                objeto.pontos[i+1].setP(2, 2, 1.0);
            }
        }
        double x1 = objeto.pontos.last().getP()(0, 2);
        double y1 = objeto.pontos.last().getP()(1, 2);
        double x2 = objeto.pontos.first().getP()(0, 2);
        double y2 = objeto.pontos.first().getP()(1, 2);

        if (x1 >= viewport.left() && x1 <= viewport.right() && y1 >= viewport.top() && y1 <= viewport.bottom()&&
            x2 >= viewport.left() && x2 <= viewport.right() && y2 >= viewport.top() && y2 <= viewport.bottom()) {

            if(objeto.nome == "Pokemon1")
                painter.setPen(QPen(Qt::yellow, 2));
            else
                painter.setPen(QPen(Qt::blue, 2));
            painter.drawLine(static_cast<int>(x1), static_cast<int>(y1),
                             static_cast<int>(x2), static_cast<int>(y2));
        }
        listaWindow.append(objeto);

    }
}


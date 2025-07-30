#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "areadesenho.h"
#include <QVBoxLayout>
#include <QFrame>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AreaDesenho *areaDesenho = new AreaDesenho(this);
    areaDesenho->setObjectName("areaDesenho");
    areaDesenho->setMinimumSize(600, 600);
    if (ui->areaContainer->layout()) {
        ui->areaContainer->layout()->addWidget(areaDesenho);
    } else {
        QVBoxLayout *layout = new QVBoxLayout(ui->areaContainer);
        layout->addWidget(areaDesenho);
        ui->areaContainer->setLayout(layout);
    }

    connect(ui->xRotacao, &QRadioButton::toggled, this, &MainWindow::on_xRotacao_toggled);
    connect(ui->yRotacao, &QRadioButton::toggled, this, &MainWindow::on_yRotacao_toggled);
    connect(ui->zRotacao, &QRadioButton::toggled, this, &MainWindow::on_zRotacao_toggled);
    connect(ui->camera, &QRadioButton::toggled, this, &MainWindow::on_camera_toggled);
    connect(ui->pokemon1, &QRadioButton::toggled, this, &MainWindow::on_pokemon1_toggled);
    connect(ui->pokemon2, &QRadioButton::toggled, this, &MainWindow::on_pokemon2_toggled);
    connect(ui->escala, &QRadioButton::toggled, this, &MainWindow::on_escala_toggled);
    connect(ui->rotacao, &QRadioButton::toggled, this, &MainWindow::on_rotacao_toggled);
    connect(ui->translacao, &QRadioButton::toggled, this, &MainWindow::on_translacao_toggled);
    connect(ui->anguloRotacaospinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_anguloRotacaospinBox_valueChanged);
    connect(ui->XScrollBar, &QScrollBar::valueChanged, this, &MainWindow::on_XScrollBar_valueChanged);
    connect(ui->YScrollBar, &QScrollBar::valueChanged, this, &MainWindow::on_YScrollBar_valueChanged);
    connect(ui->ZScrollBar, &QScrollBar::valueChanged, this, &MainWindow::on_ZScrollBar_valueChanged);
}
/*void MainWindow::on_btnCarregarObj_clicked() {
    QString caminhoArquivo = QFileDialog::getOpenFileName(this, "Abrir Arquivo .obj", "", "OBJ Files (*.obj)");
    if (!caminhoArquivo.isEmpty()) {
        areaDesenho->carregarObj(caminhoArquivo);
        areaDesenho->update(); // Redesenha a área de desenho
    }
}*/

void MainWindow::on_escala_toggled(bool checked) {
    if (checked) {
       // double escalaX = on_XScrollBar_valueChanged();
       // double escalaY= on_YScrollBar_valueChanged();
//
    }
}
void MainWindow::on_rotacao_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_translacao_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_xRotacao_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_yRotacao_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_zRotacao_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_camera_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_pokemon1_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_pokemon2_toggled(bool checked) {
    if (checked) {
        // Código para lidar com a seleção de xRotacao
    }
}
void MainWindow::on_anguloRotacaospinBox_valueChanged(int value) {
    //return value;
}

void MainWindow::on_XScrollBar_valueChanged(int value) {
    // Código para lidar com o valor da barra de rolagem
}
void MainWindow::on_YScrollBar_valueChanged(int value) {
    // Código para lidar com o valor da barra de rolagem
}
void MainWindow::on_ZScrollBar_valueChanged(int value) {
    // Código para lidar com o valor da barra de rolagem
}

/*void MainWindow::aplicarMudancaAoObjeto(int indiceObjeto, int tipoTransformacao) {

    AreaDesenho* areaDesenho = findChild<AreaDesenho*>("areaDesenho");

    if (areaDesenho) {
        qDebug() << "Tamanho de displayFile:" << areaDesenho->displayFile.size();

        if (indiceObjeto < areaDesenho->displayFile.size()) {
            Objeto& objeto = areaDesenho->displayFile[indiceObjeto];

            Matriz matrizMudanca(3, 3);
            //double cx = objeto.calculaCentroX();
            //double cy = objeto.calculaCentroY();
            switch(tipoTransformacao) {
            case 1:
                matrizMudanca = matrizMudanca.translacao();
                break;
            case 2:
                matrizMudanca = matrizMudanca.escala();
                break;
            case 3:
                matrizMudanca = matrizMudanca.rotacao();
                break;
            default:
                qDebug() << "Tipo de transformação inválido.";
                return;
            }

            for (Ponto& ponto : objeto.pontos) {
                Matriz pontoMatriz(3, 1);
                pontoMatriz(0, 0) = ponto.x();
                pontoMatriz(1, 0) = ponto.y();
                pontoMatriz(2, 0) = 1;

                pontoMatriz = matrizMudanca * pontoMatriz;

                ponto.setX(pontoMatriz(0, 0));
                ponto.setY(pontoMatriz(1, 0));
            }

            areaDesenho->update();
        } else {
            qDebug() << "Índice do objeto fora dos limites: " << indiceObjeto;
        }
    } else {
        qDebug() << "ÁreaDesenho não encontrada.";
    }
}
*/

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void aplicarMudancaAoObjeto(int indiceObjeto, int tipoTransformacao);
    void on_xRotacao_toggled(bool checked) ;
    void on_yRotacao_toggled(bool checked) ;
    void on_zRotacao_toggled(bool checked) ;
    void on_camera_toggled(bool checked) ;
    void on_pokemon1_toggled(bool checked) ;
    void on_pokemon2_toggled(bool checked) ;
    void on_escala_toggled(bool checked) ;
    void on_rotacao_toggled(bool checked) ;
    void on_translacao_toggled(bool checked) ;
    void on_anguloRotacaospinBox_valueChanged(int value) ;
    void on_XScrollBar_valueChanged(int value) ;
    void on_YScrollBar_valueChanged(int value) ;
    void on_ZScrollBar_valueChanged(int value) ;
    void on_btnCarregarObj_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

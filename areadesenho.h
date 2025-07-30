#ifndef AREADESENHO_H
#define AREADESENHO_H

#include <QFrame>
#include "objeto.h"
#include "matriz.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <QString>

class AreaDesenho : public QFrame {
    Q_OBJECT
public:

    QVector<Objeto> displayFile;
    void preencherDisplayFile();
    explicit AreaDesenho(QWidget *parent = nullptr);
    void coordenadasnormalizada(QPainter &painter) ;
    void carregarObj1(const QString& caminhoArquivoobj, const QString& caminhoArquivomtl);
    void carregarObj2(const QString& caminhoArquivoobj, const QString& caminhoArquivomtl);
    void perspectiva();
    void calcularVPN();
    void escalarObjeto();
    void rotacionarXObjeto();
    void rotacionarYObjeto();
    void rotacionarZObjeto();
    void transladarObjeto();
protected:

    void paintEvent(QPaintEvent *event) override;

private:

    QRect window;
    QVector<Objeto> listaWindow;
};

#endif // AREADESENHO_H

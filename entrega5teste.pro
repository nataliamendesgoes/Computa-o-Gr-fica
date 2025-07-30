QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    areadesenho.cpp \
    clipping.cpp \
    clippingvolumetrico.cpp \
    main.cpp \
    mainwindow.cpp \
    matriz.cpp

HEADERS += \
    areadesenho.h \
    clipping.h \
    clippingvolumetrico.h \
    mainwindow.h \
    matriz.h \
    objeto.h

FORMS += \
    mainwindow.ui

DISTFILES += entrega5teste/80-pikachu/Pikachu_OBJ.obj \
             entrega5teste/80-pikachu/Pikachu_MTL.mtl \
             entrega5teste/Charizard/006-Charizard/P2_CharizardWP.obj \
             entrega5teste/Charizard/006-Charizard/P2_CharizardWP.mtl \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

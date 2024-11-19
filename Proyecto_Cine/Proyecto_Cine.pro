 HEAD:Proyecyo_Cine/Proyecyo_Cine.pro
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asientos.cpp \
    cine.cpp \
    clientes.cpp \
    empleados.cpp \
    horarios.cpp \
    iniciosesion.cpp \
    main.cpp \
    pago.cpp \
    peliculas.cpp \
    precios.cpp \
    sala.cpp \
    venta.cpp \
    verclientes.cpp \
    verempleados.cpp \
    verhistorial.cpp \
    verpeliculas.cpp

HEADERS += \
    asientos.h \
    cine.h \
    clientes.h \
    empleados.h \
    horarios.h \
    iniciosesion.h \
    pago.h \
    peliculas.h \
    precios.h \
    sala.h \
    venta.h \
    verclientes.h \
    verempleados.h \
    verhistorial.h \
    verpeliculas.h

FORMS += \
    asientos.ui \
    cine.ui \
    clientes.ui \
    empleados.ui \
    horarios.ui \
    iniciosesion.ui \
    pago.ui \
    peliculas.ui \
    precios.ui \
    venta.ui \
    verclientes.ui \
    verempleados.ui \
    verhistorial.ui \
    verpeliculas.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
 f839cb2e0aef11a33ebe0426f67c5e18f022f8b2:Proyecto_Cine/Proyecto_Cine.pro

RESOURCES += \
    Recursos.qrc

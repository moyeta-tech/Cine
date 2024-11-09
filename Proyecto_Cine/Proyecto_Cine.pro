 HEAD:Proyecyo_Cine/Proyecyo_Cine.pro
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    asientos.cpp \
    cine.cpp \
    cliente.cpp \
    empleado.cpp \
    horarios.cpp \
    main.cpp \
    pagos.cpp \
    peliculas.cpp \
    persona.cpp \
    precios.cpp \
    reserva.cpp \
    sala.cpp

HEADERS += \
    asientos.h \
    cine.h \
    cliente.h \
    empleado.h \
    horarios.h \
    pagos.h \
    peliculas.h \
    persona.h \
    precios.h \
    reserva.h \
    sala.h

FORMS += \
    asientos.ui \
    cine.ui \
    horarios.ui \
    pagos.ui \
    peliculas.ui \
    precios.ui \
    reserva.ui

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

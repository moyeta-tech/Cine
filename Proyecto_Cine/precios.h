#ifndef PRECIOS_H
#define PRECIOS_H

#include <QWidget>

namespace Ui {
class precios;
}

class precios : public QWidget
{
    Q_OBJECT

public:
    explicit precios(QWidget *parent = nullptr);
    ~precios();

private:
    Ui::precios *ui;
};

#endif // PRECIOS_H

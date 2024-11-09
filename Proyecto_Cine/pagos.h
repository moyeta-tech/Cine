#ifndef PAGOS_H
#define PAGOS_H

#include <QWidget>

namespace Ui {
class pagos;
}

class pagos : public QWidget
{
    Q_OBJECT

public:
    explicit pagos(QWidget *parent = nullptr);
    ~pagos();

private:
    Ui::pagos *ui;
};

#endif // PAGOS_H

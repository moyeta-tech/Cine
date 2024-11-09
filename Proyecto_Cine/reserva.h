#ifndef RESERVA_H
#define RESERVA_H

#include <QDialog>

namespace Ui {
class reserva;
}

class reserva : public QDialog
{
    Q_OBJECT

public:
    explicit reserva(QWidget *parent = nullptr);
    ~reserva();

private:
    Ui::reserva *ui;
};

#endif // RESERVA_H

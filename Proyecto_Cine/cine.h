#ifndef CINE_H
#define CINE_H

#include <QMainWindow>

namespace Ui {
class Cine;
}

class Cine : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cine(QWidget *parent = nullptr);
    ~Cine();

private:
    Ui::Cine *ui;
};

#endif // CINE_H

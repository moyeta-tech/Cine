#ifndef HORARIOS_H
#define HORARIOS_H

#include <QWidget>

namespace Ui {
class horarios;
}

class horarios : public QWidget
{
    Q_OBJECT

public:
    explicit horarios(QWidget *parent = nullptr);
    ~horarios();

private:
    Ui::horarios *ui;
};

#endif // HORARIOS_H

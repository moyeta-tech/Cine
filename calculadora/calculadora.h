#ifndef CALCULADORA_H
#define CALCULADORA_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class calculadora;
}
QT_END_NAMESPACE

class calculadora : public QWidget
{
    Q_OBJECT

public:
    calculadora(QWidget *parent = nullptr);
    ~calculadora();

private:
    Ui::calculadora *ui;
};
#endif // CALCULADORA_H

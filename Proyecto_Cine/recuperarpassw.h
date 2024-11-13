#ifndef RECUPERARPASSW_H
#define RECUPERARPASSW_H

#include <QDialog>
#include <QFile>

namespace Ui {
class RecuperarPassw;
}

class RecuperarPassw : public QDialog
{
    Q_OBJECT

public:
    explicit RecuperarPassw(QWidget *parent = nullptr);
    ~RecuperarPassw();

private slots:
    void recuperarPassword();
    void cancelarRecuperacion();
    void initstylesheet();

private:
    Ui::RecuperarPassw *ui;
};

#endif // RECUPERARPASSW_H

#ifndef METEO_H
#define METEO_H

#include <QDialog>

namespace Ui {
class meteo;
}

class meteo : public QDialog
{
    Q_OBJECT

public:
    explicit meteo(QWidget *parent = nullptr);
    ~meteo();
    void saisir_donnee();
    int data();
    int json();

private:
    Ui::meteo *ui;
};

#endif // METEO_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),id("MARECAR"),mdp("admin"),Meteo (new meteo)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::connexcion);

}

void MainWindow::connexcion(){
    if (ui->lineEdit->text() == QString::fromStdString(id) && ui->lineEdit_2->text() == QString::fromStdString(mdp)) {

        QMessageBox::information(this, "AUTHENTIFICATION", "connexcion reussi");
        this->close();
        Meteo->open();

    } else {
        QMessageBox::warning(this, "AUTHENTIFICATION", "incorrect");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Accès aux différentes valeurs
//   double temperature = detailsObject["temperature"].toDouble();
//    QString ventDirection = detailsObject["vent-direction"].toString();
//   int ventSpeed = detailsObject["vent-speed"].toInt();
//  int humidite = detailsObject["humidité"].toInt();
//  int pression = detailsObject["pression"].toInt();
// Affichage des valeurs
//  qDebug() << "Temperature:" << temperature;
//  qDebug() << "Vent Direction:" << ventDirection;
//  qDebug() << "Vent Speed:" << ventSpeed;
// qDebug() << "Humidité:" << humidite;
// qDebug() << "Pression:" << pression;

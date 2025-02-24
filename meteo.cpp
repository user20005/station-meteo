#include "meteo.h"
#include "ui_meteo.h"
#include <QPixmap>
#include <QCoreApplication>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QInputDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>


meteo::meteo(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::meteo)
{
    ui->setupUi(this);
    QPixmap pix(QCoreApplication::applicationDirPath() + "/img.jpg");
    ui->img->setPixmap(pix.scaled(200, 200, Qt::KeepAspectRatio));
    ui->pushButton_1->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    QValidator *validator = new QIntValidator(this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    connect(ui->pushButton,&QPushButton::clicked,this,&meteo::data);
}

meteo::~meteo()
{
    delete ui;
}

int meteo::data()
{

    QValidator *validator = new QIntValidator(this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    int aaaa = ui->lineEdit->text().toInt();
    int mm = ui->lineEdit_3->text().toInt();
    int jj = ui->lineEdit_2->text().toInt();
    //mm >= 01 && mm < 13
    if(ui->lineEdit->text().length() == 4 &&  ui->lineEdit_3->text().length() == 2 && ui->lineEdit_2->text().length() ==2 ){
        if( aaaa == 2019 && mm == 01  && jj >= 01 && jj < 32 ){
            ui->pushButton_1->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->pushButton_3->setVisible(true);
            ui->pushButton_4->setVisible(true);
            ui->data->setPlainText("");
            json();
        }else{
             QMessageBox::warning(this,"WARNING","La date n'est pas valide.");
            ui->data->setPlainText("");
             ui->date->setPlainText("");
        }
    }else{
        QMessageBox::warning(this,"WARNING","Le format n'est pas valide.");
        ui->data->setPlainText("");
        ui->date->setPlainText("");
    }

    return 1;
}

int meteo::json(){

    QString filePath = QCoreApplication::applicationDirPath() + "/data.json";
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Impossible d'ouvrir le fichier.";
        return 1;
    }
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    QJsonObject root = jsonDoc.object();
    QJsonArray dateT = root["date"].toArray();
    QJsonObject date = dateT[0].toObject();
        QString aaaa = ui->lineEdit->text();
        QString mm = ui->lineEdit_3->text();
        QString jj = ui->lineEdit_2->text();
        QString date1 = aaaa + "-" + mm + "-" +jj;
        ui->date->setPlainText(date1);
    QJsonObject dateDetail = date[date1].toObject();
    QJsonObject time = dateDetail["time"].toObject();
    double temp = 0,ventspeed = 0,pression= 0,humd = 0;
    int count = 0;
    int N = 0, NE = 0, NO = 0, S = 0, SE = 0, SO = 0, O = 0, E = 0;
    for (const QString& timeKey : time.keys()) {
        if (timeKey >= "08:00" && timeKey <= "18:00") {
            QJsonObject detailsObject = time[timeKey].toObject();
            temp += detailsObject["temperature"].toInt();
            humd += detailsObject["humidité"].toInt();
            ventspeed += detailsObject["vent-speed"].toInt();
            pression += detailsObject["pression"].toInt();
            QString ventDirection = detailsObject["vent-direction"].toString();

            if (ventDirection == "Nord") {
                N++;
            } else if (ventDirection == "Nord-est") {
                NE++;
            } else if (ventDirection == "Nord-ouest") {
                NO++;
            } else if (ventDirection == "Sud") {
                S++;
            } else if (ventDirection == "Sud-est") {
                SE++;
            } else if (ventDirection == "Sud-ouest") {
                SO++;
            } else if (ventDirection == "Ouest") {
                O++;
            } else if (ventDirection == "Est") {
                E++;
            }
            count++;
        }

    }

    QString mostFrequentVentDirection;
    int maxCount = 0;

    if (N >= maxCount) {
        maxCount = N;
        mostFrequentVentDirection = "Nord";
    }
    if (NE >= maxCount) {
        maxCount = NE;
        mostFrequentVentDirection = "Nord-est";
    }
    if (NO >= maxCount) {
        maxCount = NO;
        mostFrequentVentDirection = "Nord-ouest";
    }
    if (S >= maxCount) {
        maxCount = S;
        mostFrequentVentDirection = "Sud";
    }
    if (SE >= maxCount) {
        maxCount = SE;
        mostFrequentVentDirection = "Sud-est";
    }
    if (SO >= maxCount) {
        maxCount = SO;
        mostFrequentVentDirection = "Sud-ouest";
    }
    if (O >= maxCount) {
        maxCount = O;
        mostFrequentVentDirection = "Ouest";
    }
    if (E >= maxCount) {
        maxCount = E;
        mostFrequentVentDirection = "Est";
    }
    //qDebug() << "Direction du vent la plus fréquente entre 8h et 18h : " << mostFrequentVentDirection <<maxCount;

    double avTemp = temp / count;
    int avhumd = humd / count;
    int avventspeed = ventspeed / count;
    connect(ui->pushButton_1, &QPushButton::clicked, [=]() {
        ui->data->setPlainText("Moyenne de température entre 8h et 18h :\n  ->   " + QString::number(avTemp) + "°C");
      QFile file("C:/Users/frti1017/Documents/GUI-Vision/result_storage.txt");
      if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
      {
          // We're going to streaming text to the file
          QTextStream stream(&file);

          stream << "Moyenne de température entre 8h et 18h :\n  ->   " + QString::number(avTemp) + "°C" + date1;

      }
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=]() {
        ui->data->setPlainText("Moyenne de humidité entre 8h et 18h :\n  ->   " + QString::number(avhumd) + "%");
    });
    connect(ui->pushButton_3, &QPushButton::clicked, [=]() {
         ui->data->setPlainText("Moyenne de vent-speed entre 8h et 18h :\n ->   " + QString::number(avventspeed) + "km/h");
    });
    connect(ui->pushButton_4, &QPushButton::clicked, [=]() {
       ui->data->setPlainText("la direction prédominante du vent entre 8h00 et 18h00 était :\n ->   " + mostFrequentVentDirection);
    });
    return 0;
}

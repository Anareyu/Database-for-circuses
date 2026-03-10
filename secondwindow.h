#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QMessageBox>
#include <QPixmap>



namespace Ui {class SecondWindow;}


class SecondWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = 0);
    ~SecondWindow();

    void open_form();

private:
    Ui::SecondWindow *ui;

public:
    enum State{
        AddElement,
        EditElement,
        SearchElement
    };

    State state;

    struct circle{
        QString name;
        QString dir;
        int year;
        QString country;
        QString city;
        int seats;
        int size;
        bool avail;
        QString name_pic;
    };

    int index=0;
    circle *arr;
    circle parameteres;
    circle tempo;
    int rows=0;
    const int MAX_SIZE = 100;

    QVector <QString> cities;
    QVector <int> numCities;
    int allCities = 0;

private slots:
    void on_pB_OK_clicked();
    void on_pB_cancel_clicked();
    void on_pushButton_pic_clicked();
};



#endif // SECONDWINDOW_H

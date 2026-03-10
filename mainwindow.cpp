#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"
#include <QDebug.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sw = new SecondWindow(this);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_add_element_triggered()
{

    sw->state = sw->AddElement;
    sw->setWindowTitle("Добавить элемент");
    sw->open_form();
    sw->exec();
    reload();
    select_elem(sw->rows);
    ui->tableWidget->clearSelection();
}

void MainWindow::reload()
{

    ui->tableWidget->setRowCount(sw->rows);
    for (int i = 0; i < sw->rows; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem (sw->arr[i].name));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem (sw->arr[i].dir));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem (QString::number(sw->arr[i].year)));
    }
}

void MainWindow::select_elem(int k)
{
    if(sw->rows==0){
        return;
    }
    ui->le_country->setText(sw->arr[k].country);
    ui->le_city->setText(sw->arr[k].city);
    ui->le_amount_of_seats->setText(QString::number(sw->arr[k].seats));
    ui->le_size_of_troupe->setText(QString::number(sw->arr[k].size));
    if(sw->arr[k].avail)
        ui->le_availability_of_animals->setText("Есть");
    else
        ui->le_availability_of_animals->setText("Нет");

    QPixmap pic(sw->arr[k].name_pic);
    pic = pic.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt :: KeepAspectRatio);

    ui->label_pic->setPixmap(pic);
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    rw = ui->tableWidget->currentRow();
    select_elem(rw);
}

void MainWindow::on_action_edit_triggered()
{
    sw->state = sw->EditElement;
    sw->index = ui->tableWidget->currentRow();
    sw->setWindowTitle("Изменить элемент");
    sw->open_form();
    sw->exec();
    reload();
    select_elem(0);
}

void MainWindow::on_action_delete_triggered()
{
    rw = ui->tableWidget->currentRow();
    for (int i = rw; i < (sw->rows)-1; i++)
        sw->arr[i] = sw->arr[i+1];
    (sw->rows)--;
    reload();
    select_elem(0);
}

void MainWindow::on_action_save_file_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Choose file");
    QFile fl(file_name);
    fl.open(QIODevice::WriteOnly);

    if (!fl.isOpen())
    {
        QMessageBox :: warning (this, "error", "Не открылось :(");
        return;
    }
    QTextStream record(&fl);
    for (int i = 0; i < sw->rows; ++i)
    {
        record << sw->arr[i].name << "\n";
        record << sw->arr[i].dir << "\n";
        record << sw->arr[i].year << "\n";
        record << sw->arr[i].country << "\n";
        record << sw->arr[i].city << "\n";
        record << sw->arr[i].seats << "\n";
        record << sw->arr[i].size << "\n";
        record << sw->arr[i].avail << "\n";
        record << sw->arr[i].name_pic << "\n";
    }
    fl.close();
}

void MainWindow::on_action_load_file_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Choose file");
    QFile fl(file_name);
    fl.open(QIODevice::ReadOnly);

    if (!fl.isOpen())
    {
        QMessageBox :: warning (this, "error", "Не открылось :(");
        return;
    }
    QTextStream record(&fl);
    sw->rows=0;
    while(!record.atEnd())
    {
        sw->arr[sw->rows].name = record.readLine();
        sw->arr[sw->rows].dir = record.readLine();
        sw->arr[sw->rows].year = record.readLine().toInt();
        sw->arr[sw->rows].country = record.readLine();
        sw->arr[sw->rows].city = record.readLine();
        sw->arr[sw->rows].seats = record.readLine().toInt();
        sw->arr[sw->rows].size = record.readLine().toInt();
        sw->arr[sw->rows].avail = record.readLine().toInt();
        sw->arr[sw->rows].name_pic = record.readLine();
        sw->rows++;
    }
    reload();
    fl.close();
}


void MainWindow::on_action_search_for_fields_triggered()
{
    sw->state = sw->SearchElement;
    sw->setWindowTitle("Поиск");
    sw->open_form();
    sw->exec();

    ui->tableWidget->clearSelection();
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    bool flag = true;

    for(int i = 0; i<sw->rows;i++){
        qDebug()<<sw->parameteres.name;
        if (sw->parameteres.name != "" && sw->parameteres.name != sw->arr[i].name){
            flag = false;
        }
        if(sw->parameteres.dir != "" && sw->parameteres.dir != sw->arr[i].dir){
            flag = false;
        }
        if(sw->parameteres.year!=1770 && sw->parameteres.year != sw->arr[i].year){
            flag = false;
        }
        if(sw->parameteres.country != "-" && sw->parameteres.country != sw->arr[i].country){
            flag = false;
        }
        if(sw->parameteres.city != "-" && sw->parameteres.city != sw->arr[i].city){
            flag = false;
        }
        if(sw->parameteres.seats != 0 && sw->parameteres.seats != sw->arr[i].seats){
            flag = false;
        }
        if(sw->parameteres.size != 0 && sw->parameteres.size != sw->arr[i].size){
            flag = false;
        }
        if(sw->parameteres.avail != sw->arr[i].avail){
            flag = false;
        }
        if(sw->parameteres.name_pic != "Path" && sw->parameteres.name_pic != sw->arr[i].name_pic){
            flag = false;
        }

        if (flag){
            ui->tableWidget->selectRow(i);
        }
        else{
            flag=true;
        }
    }

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

}


void MainWindow::on_action_sort_for_amount_triggered()
{
    ui->tableWidget->clearSelection();
    for (int i =0; i<sw->rows-1;i++){
        for (int j = i+1; j<sw->rows;j++){
            if(sw->arr[i].seats>sw->arr[j].seats){
                sw->tempo = sw->arr[i];
                sw->arr[i] = sw->arr[j];
                sw->arr[j] = sw->tempo;
            }
        }
    }
    reload();
}


void MainWindow::on_action_youngest_circle_animals_triggered()
{
    int max=0;
    int maxi=0;
    for (int i =0;i<sw->rows;i++){
        if (sw->arr[i].year>max && sw->arr[i].avail){
            max = sw->arr[i].year;
            maxi=i;
        }
    }
    if (max==0){
        QMessageBox::warning(this,"", "Error");
    }
    else{
        select_elem(maxi);
        ui->tableWidget->selectRow(maxi);
    }
}


void MainWindow::on_action_biggest_of_troupe_triggered()
{
    ui->tableWidget->clearSelection();
    int max=0;
    int maxi=0;
    for (int i =0;i<sw->rows;i++){
        if (sw->arr[i].size>max && !sw->arr[i].avail){
            max = sw->arr[i].size;
            maxi=i;
        }
    }
    if (max==0){
        QMessageBox::warning(this,"", "Error");
    }
    else{
        select_elem(maxi);
        ui->tableWidget->selectRow(maxi);
    }
}


void MainWindow::on_action_select_many_circles_triggered()
{
    ui->tableWidget->clearSelection();
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    int value = QInputDialog::getInt(this,"","Введите пороговое значение",0,0,9999999);
    for(int i = 0; i<sw->rows;i++){
        if (sw->arr[i].size>value){
            ui->tableWidget->selectRow(i);
        }
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}


void MainWindow::on_action_save_bin_file_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Choose file");
    QFile fl(file_name);
    fl.open(QIODevice::WriteOnly);

    if (!fl.isOpen())
    {
        QMessageBox :: warning (this, "error", "Не открылось :(");
        return;
    }
    QDataStream record(&fl);
    for (int i = 0; i < sw->rows; i++)
    {
        record << sw->arr[i].name
        << sw->arr[i].dir
        << sw->arr[i].year
        << sw->arr[i].country
        << sw->arr[i].city
        << sw->arr[i].seats
        << sw->arr[i].size
        << sw->arr[i].avail
        << sw->arr[i].name_pic;
    }
    fl.close();
}


void MainWindow::on_action_load_bin_file_triggered()
{

    QString file_name = QFileDialog::getOpenFileName(this, "Choose file");
    QFile fl(file_name);
    fl.open(QIODevice::ReadOnly);

    if (!fl.isOpen())
    {
        QMessageBox :: warning (this, "error", "Не открылось :(");
        return;
    }
    QDataStream record(&fl);
    sw->rows=0;
    while(!record.atEnd())
    {
        record >> sw->arr[sw->rows].name
        >> sw->arr[sw->rows].dir
        >> sw->arr[sw->rows].year
        >> sw->arr[sw->rows].country
        >> sw->arr[sw->rows].city
        >> sw->arr[sw->rows].seats
        >> sw->arr[sw->rows].size
        >> sw->arr[sw->rows].avail
        >> sw->arr[sw->rows].name_pic;
        sw->rows++;
    }
    reload();
    fl.close();

}


void MainWindow::on_action_delete_all_triggered()
{
    sw->rows=0;
    reload();
}


void MainWindow::on_action_city_max_amount_triggered()
{
    for (int i = 0; i<sw->rows; i++){
        for(int j = 0; j<sw->allCities;j++){
            if(sw->arr[i].city == sw->cities[j]){
                sw->numCities[j]++;
                break;
            }
        }
    }

    int max=0;
    int maxj = 0;
    for(int j = 0; j<sw->allCities;j++){
        if(max < sw->numCities[j]){
            max = sw->numCities[j];
            maxj=j;
        }
    }


    QMessageBox::warning(this, "", "Город с бОльшим количеством цирков - это: "+sw->cities[maxj]+"\n"+"Количество цирков: " + \
                         QString::number(max),"ok");

}


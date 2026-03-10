#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "QMessageBox"
#include "QDebug.h"

SecondWindow::SecondWindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::SecondWindow)
{
  ui->setupUi(this);
  arr = new circle [MAX_SIZE];

  QFile fl1("D:/Codes/qt/circles2/files/initialization/countries.txt");

  QFile fl2("D:/Codes/qt/circles2/files/initialization/cities.txt");

  fl1.open(QIODevice::ReadOnly);
  if (!fl1.isOpen())
      QMessageBox::warning(this, "", "Error");

  QTextStream text1(&fl1);
  while(!text1.atEnd())
  {
      ui->comboBox_country->addItem(text1.readLine());
  }

  fl2.open(QIODevice::ReadOnly);
  if (!fl2.isOpen())
      QMessageBox::warning(this, "", "Error");

  QTextStream text2(&fl2);
  while(!text2.atEnd())
  {
      QString buff = text2.readLine();
      cities.append(buff);
      numCities.append(0);
      allCities++;
      ui->comboBox_city->addItem(buff);
  }
  fl1.close();
  fl2.close();
}

SecondWindow::~SecondWindow()
{
  delete ui;
}

void SecondWindow::open_form()
{
  if (state == AddElement || state==SearchElement){
      ui->le_name->clear();
      ui->le_director->clear();
      ui->spinBox_year->setValue(1770);
      ui->comboBox_country->setCurrentText("-");
      ui->comboBox_city->setCurrentText("-");
      ui->spinBox_amount_of_seats->setValue(0);
      ui->spinBox_size_of_troupe->setValue(0);
      ui->rB_availability_of_animals->setChecked(false);
      ui->label_pic->clear();

      ui->label_pic_path->setText("Path");
  }

  else if (state == EditElement){

      ui->le_name->setText(arr[index].name);
      ui->le_director->setText(arr[index].dir);
      ui->spinBox_year->setValue(arr[index].year);
      ui->comboBox_country->setCurrentText(arr[index].country);
      ui->comboBox_city->setCurrentText(arr[index].city);
      ui->spinBox_amount_of_seats->setValue(arr[index].seats);
      ui->spinBox_size_of_troupe->setValue(arr[index].size);
      ui->rB_availability_of_animals->setChecked(arr[index].avail);

      QPixmap pic(arr[index].name_pic);
      pic = pic.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio);
      ui->label_pic->setPixmap(pic);
      ui->label_pic_path->setText("Path");

  }
}



void SecondWindow::on_pB_OK_clicked()
{

    if(state==SearchElement){
        parameteres.name = ui->le_name->text();
        parameteres.dir = ui->le_director->text();
        parameteres.year = ui->spinBox_year->value();
        parameteres.country = ui->comboBox_country->currentText();
        parameteres.city = ui->comboBox_city->currentText();
        parameteres.seats = ui->spinBox_amount_of_seats->value();
        parameteres.size = ui->spinBox_size_of_troupe->value();
        parameteres.avail = ui->rB_availability_of_animals->isChecked();
        parameteres.name_pic = ui->label_pic_path->text();

        this->close();
        return;
    }
    if (state == AddElement){
        index = rows;
        rows++;
    }
    arr[index].name = ui->le_name->text();
    arr[index].dir = ui->le_director->text();
    arr[index].year = ui->spinBox_year->value();
    arr[index].country = ui->comboBox_country->currentText();
    arr[index].city = ui->comboBox_city->currentText();
    arr[index].seats = ui->spinBox_amount_of_seats->value();
    arr[index].size = ui->spinBox_size_of_troupe->value();
    arr[index].avail = ui->rB_availability_of_animals->isChecked();
    arr[index].name_pic = ui->label_pic_path->text();

    this->close();

}


void SecondWindow::on_pB_cancel_clicked()
{
    this->close();
}


void SecondWindow::on_pushButton_pic_clicked()
{
    QString file_name = QFileDialog :: getOpenFileName(this, "choose the picture");
    QFile fl(file_name);
    ui->label_pic_path->setText(file_name);
    QPixmap pic(file_name);
    pic = pic.scaled(ui->label_pic->width(), ui->label_pic->height(), Qt::KeepAspectRatio);
    ui->label_pic->setPixmap(pic);
}


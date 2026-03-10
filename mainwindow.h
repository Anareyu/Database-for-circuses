#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <secondwindow.h>


namespace Ui { class MainWindow; }


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int rw;

private slots:

    void on_action_add_element_triggered();

    void reload();

    void select_elem(int k);

    void on_tableWidget_itemSelectionChanged();

    void on_action_edit_triggered();

    void on_action_delete_triggered();

    void on_action_save_file_triggered();

    void on_action_load_file_triggered();

    void on_action_search_for_fields_triggered();

    void on_action_sort_for_amount_triggered();

    void on_action_youngest_circle_animals_triggered();

    void on_action_biggest_of_troupe_triggered();

    void on_action_select_many_circles_triggered();

    void on_action_save_bin_file_triggered();

    void on_action_load_bin_file_triggered();

    void on_action_delete_all_triggered();

    void on_action_city_max_amount_triggered();

private:
    Ui::MainWindow *ui;
    SecondWindow *sw;


};
#endif // MAINWINDOW_H

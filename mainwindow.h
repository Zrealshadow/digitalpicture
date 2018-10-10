#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <histogram.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_input_clicked();
    
    void on_trans_clicked();
    
    void on_save_clicked();
    

    void on_input_3_clicked();

    void on_save_3_clicked();


    void on_grey_clicked();

    void on_input_4_clicked();

    void on_save_4_clicked();


    void on_bmp2txt_clicked();

    void on_input_plot_clicked();

    void on_plot_2_clicked();

    void on_save_plot_clicked();

    void on_input_hist_clicked();

    void on_hist_clicked();

    void on_save_hist_clicked();

    void on_input_hist_point_clicked();

    void on_save_hist_point_clicked();

    void on_bright_point_clicked();

    void on_dim_point_clicked();

    void on_show_histogram_point_clicked();

private:
    Ui::MainWindow *ui;
    Histogram *hist_show;

};

#endif // MAINWINDOW_H

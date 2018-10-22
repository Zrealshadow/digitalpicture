#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <histogram.h>
#include <spacemove.h>
#include <spacezoom.h>
#include <spacerotate.h>
#include <spacesmooth.h>
#include <spacesharpen.h>
#include <spaceconv.h>
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

    void on_profile_point_clicked();



    void on_equal_point_clicked();

    void on_input_space_clicked();

    void on_space_zoom_clicked();

    void on_space_move_clicked();

    void on_space_Flip_clicked();

    void on_space_Rotate_clicked();

    void on_space_smooth_clicked();

    void on_space_sharpen_clicked();

    void on_space_conv_clicked();

    void on_compare_space_clicked();

private:
    Ui::MainWindow *ui;
    Histogram *hist_show;
    void __init__();
    void input_init();
    bool input_isvalid(QImage *img);
    QLabel * output_label();
};

#endif // MAINWINDOW_H

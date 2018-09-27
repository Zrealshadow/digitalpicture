#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    
    void on_grey_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

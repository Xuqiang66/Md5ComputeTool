#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <md5.h>

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_pBtn_choosefile_clicked();
    void on_pBtn_start_clicked();

private:
    int MO_compute_file_md5(const char *file_path, char *md5_str);

private:
    Ui::MainWindow *ui;

    QString filename;
};

#endif // MAINWINDOW_H

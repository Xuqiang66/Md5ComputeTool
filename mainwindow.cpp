#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pBtn_start->setEnabled(false);

    filename = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBtn_choosefile_clicked()
{
    ui->label_filename->setText(QString::fromLocal8Bit("请选择文件"));

    filename = QFileDialog::getOpenFileName(this, "ChooseFile", "", nullptr);

    QString showinfo = QString::fromLocal8Bit("当前选择的文件是\n").append(filename);

    ui->label_filename->setText(showinfo);

    ui->pBtn_start->setEnabled(true);
}

void MainWindow::on_pBtn_start_clicked()
{
    char md5_str[MD5_STR_LEN + 1];

    MO_compute_file_md5(filename.toStdString().c_str(), md5_str);
    printf("md5=%s\n", md5_str);

    ui->textEdit_md5->setText(QString(md5_str));
}

int MainWindow::MO_compute_file_md5(const char *file_path, char *md5_str)
{
    int i;
    int fd;
    int ret;
    unsigned char data[READ_DATA_SIZE];
    unsigned char md5_value[MD5_SIZE];
    MD5_CTX md5;

    fd = open(file_path, O_RDONLY);
    if (-1 == fd)
    {
        perror("open");
        return -1;
    }

    // init md5
    MD5_Init(&md5);

    while (1)
    {
        ret = read(fd, data, READ_DATA_SIZE);
        if (-1 == ret)
        {
            perror("read");
            return -1;
        }

        MD5_Update(&md5, data, ret);

        if (0 == ret || ret < READ_DATA_SIZE)
        {
            break;
        }
    }

    ::close(fd);

    MD5_Final(md5_value, &md5);

    for (i = 0; i < MD5_SIZE; i++)
    {
        snprintf(md5_str + i * 2, 2 + 1, "%02x", md5_value[i]);
    }
    md5_str[MD5_STR_LEN] = '\0'; // add end

    return 0;
}

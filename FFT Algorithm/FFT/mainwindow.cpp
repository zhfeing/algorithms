#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FFT.h"
Mat Img;
Mat FFT_output;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//open a picture
void MainWindow::on_action_triggered()
{
    QString filename = QFileDialog::getOpenFileName(
       this,
       "Open Picture",
       QDir::currentPath(),
       "Picture files (*.jpg *.bmp);;");

    if (!filename.isNull())
    {   //用户选择了图片
        // 处理图片
        Img.release();
        Img = cv::imread(filename.toAscii().data());
        cv::imshow("Image",Img);
    }
}

void MainWindow::on_action_2_triggered()
{
    exit(0);
}

void MainWindow::on_action_FFT_triggered()
{
    if(0==Img.rows||0==Img.cols)//a empty picture
    {
        QMessageBox::information(this, "FFT", "FAILED: No picture");
        return;
    }

    int newSize;
    if(Img.rows >= MAX_SIZE || Img.cols >= MAX_SIZE)//cannot deal with
    {
        QMessageBox::information(this, "Warning", "Picture's size is too large, some data will be abandoned");
        newSize = MAX_SIZE;
    }
    else
    {
        if(!findMaxSubSizeWithPowerOfTwo(Img, newSize))
            QMessageBox::information(this, "Waring", "Picture's size is not the power of two, some data will be abandoned");
        //newSize *= 2;      //to get a bigger picture
    }
    Mat beforeFFT = Mat(newSize, newSize, Img.type());
    MatCopy(beforeFFT, Img, true);
    cv::imshow("Before FFT", beforeFFT);
    FFT_output = Mat(newSize, newSize, Img.type());
    MatCopy(FFT_output, beforeFFT, false);
    img_FFT(FFT_output, beforeFFT);
    cv::imshow("After FFT", FFT_output);
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{

}

void MainWindow::on_graphicsView_destroyed()
{

}

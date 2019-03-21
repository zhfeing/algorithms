#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <Qfile>
#include <QFileDialog>
#include <Qdir>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_action_FFT_triggered();

    void on_graphicsView_destroyed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

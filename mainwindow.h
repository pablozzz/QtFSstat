#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <qfilesystemmodel.h>
#include <QTreeView>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QProgressBar>
#include "statistic.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void get_stat();                //Create new threat for getting statistics

private:

    void createGUI();                   //MainWindow GUI constructor

    QLabel *label;
    QLabel *filecounter;
    QLabel *PBlabel;
    QPushButton *button;
    QPushButton *exit_button;
    QPushButton *choose_dir;
    QGridLayout *layout;
    QFileSystemModel *model;
    QTreeView *tree;
    QTreeWidgetItem *dir;
    QItemSelectionModel *selectionModel;
    QProgressBar *progressBar;
};

#endif // MAINWINDOW_H

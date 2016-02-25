#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <qfilesystemmodel.h>
#include <QTreeView>
#include <QTreeWidgetItem>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void get_stat();                //Create new threat for getting statistics

private:
    void createGUI();               //MainWindow GUI constructor
    QString fileSize(qint64 nSize); //Get absolute path and return filesize in bytes,kilobytes,etc.

    QLabel *label;
    QLabel *filecounter;
    QPushButton *button;
    QPushButton *exit_button;
    QPushButton *choose_dir;
    QGridLayout *layout;
    QFileSystemModel *model;
    QTreeView *tree;
    QTreeWidgetItem *dir;
    QItemSelectionModel *selectionModel;
};

#endif // MAINWINDOW_H

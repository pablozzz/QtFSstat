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
#include <QTextEdit>
#include <QTableView>
#include <QStandardItemModel>
#include "statistic.h"
#include <QThread>
#include "newthread.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    void buildStat(QDir dirPath);

private slots:
    void get_stat();                //Create new threat for getting statistics
    void printStat();

private:

    void createGUI();                   //MainWindow GUI constructor

    void addThread(QDir dirPath);

    QLabel *label;
    QLabel *statlabel;
    QLabel *PBlabel;
    QPushButton *button;
    QPushButton *exit_button;
    QPushButton *choose_dir;
    QTextEdit *StatDisplay;
    QHBoxLayout *mainlayout;
    QVBoxLayout *leftlayout;
    QVBoxLayout *rightlayout;
    QFileSystemModel *model;
    QTreeView *tree;
    QTreeWidgetItem *dir;
    QItemSelectionModel *selectionModel;
    QTableView *table;
    QStandardItemModel *tablemodel;
    QProgressBar *progressBar;
    newThread *wrapper;

};

#endif // MAINWINDOW_H

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
#include <QThread>
#include <QTimer>

#include "wrapper.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    void buildStat(QDir dirPath);

private slots:
    void getStat();                //Create new threat for getting statistics
    void printStat();
    void timerEvent();
private:

    void createGUI();                   //MainWindow GUI constructor
    void addThread(QDir dirPath);

    QLabel *label;
    QLabel *statlabel;
    QLabel *pogressBarLabel;
    QPushButton *button;
    QPushButton *exitButton;
    QPushButton *chooseDir;
    QTextEdit *statDisplay;
    QHBoxLayout *mainLayout;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    QFileSystemModel *model;
    QTreeView *tree;
    QTreeWidgetItem *dir;
    QItemSelectionModel *selectionModel;
    QTableView *table;
    QStandardItemModel *tableModel;
    QProgressBar *progressBar;
    Wrapper *wrapper;
    QTimer *timer;

};

#endif // MAINWINDOW_H

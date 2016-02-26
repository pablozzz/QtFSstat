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

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void get_stat();                //Create new threat for getting statistics

private:

    struct stat_info                        //struct for statistic info
    {
        qint64 fileCounter;                 //all files in folder
        qint64 sizeCounter;                 //all files size
        QMap<QString,qint64> sizeStore;     // file groups with sizes
    };

    void createGUI();                   //MainWindow GUI constructor
    QString fileSize(qint64 nSize);     //Get absolute path and return filesize in bytes,kilobytes,etc.
    void getFilesStat(QDir dir_path, stat_info *folder_stat);   //Get full files statisic about folder dir_path
    void dirIterator(QDir dir_path);    //Subdirectories runner;
    void SubDirsCounter(QDir dir_path); //Count subdirectories in folder



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

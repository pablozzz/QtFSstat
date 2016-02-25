#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow()
{
    createGUI();
    setLayout(layout);
    setWindowTitle("File System Statistics");
}


void MainWindow::createGUI()
{
    label = new QLabel("Please choose directory:");
    exit_button = new QPushButton ("Exit");
    layout = new QGridLayout;
    layout->addWidget(label,0,0);
    layout->addWidget(exit_button,0,1);

    connect(exit_button,SIGNAL(clicked(bool)),this,SLOT(close()));

    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    tree = new QTreeView();
    tree->setModel(model);
    layout->addWidget(tree,1,0);
    selectionModel= tree->selectionModel();

    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
               this, SLOT(get_stat()));

}

void MainWindow::get_stat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dir_path = model->fileInfo(index).absoluteFilePath();

    //Files counter
    int files_counter = 0;
    foreach (QString fileName,dir_path.entryList(QDir::Files))
    {
        files_counter++;
    }
    qDebug() << "Files: " << files_counter;

    //Subdirectories counter
    int subdir_counter = 0;
    foreach (QString DirName,dir_path.entryList(QDir::Dirs))
    {
        subdir_counter++;
        qDebug() << DirName;
    }
    subdir_counter -=2; //For exclude "." and ".." subdirectories
    qDebug() << "Subdirectories: " << subdir_counter;

}

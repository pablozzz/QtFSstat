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
    qint64 files_Size = 0;
    QMap<QString,qint64> sizeStore;

    foreach (QString fileName,dir_path.entryList(QDir::Files))
    {
        QString full_path = dir_path.absoluteFilePath(fileName);

        QFileInfo *fileinfo= new QFileInfo(full_path);
        qint64 nSize = fileinfo->size();

        //add new extinsions and it's sizes in dictionary
        QString ext = fileinfo->completeSuffix();
        if (sizeStore.contains(ext))
        {
            sizeStore[ext] += nSize;
        }
        else
        {
            sizeStore.insert(ext, nSize);
        }
        files_Size += fileinfo->size();
        files_counter++;
    }


    //print all extensions sizes

    QMap<QString,qint64> ::iterator it = sizeStore.begin();
    for (;it != sizeStore.end(); ++it)
    {
        qDebug() << "Filgroup: " <<it.key() << "Size: " <<this->fileSize(it.value());

    }

    qDebug() << "Files: " << files_counter;
    qDebug() << "All files_size" << fileSize(files_Size);

    //Subdirectories counter
    int subdir_counter = 0;
    foreach (QString DirName,dir_path.entryList(QDir::Dirs))
    {
        subdir_counter++;
    }
    subdir_counter -=2; //For exclude "." and ".." subdirectories
    qDebug() << "Subdirectories: " << subdir_counter;

}

QString MainWindow::fileSize(qint64 nSize)
{
    int i = 0;
    for (;nSize > 1023; nSize/=1024, i++)
    {
        if(i >= 4)
        {
            break;
        }

    }
    return QString().setNum(nSize)+"BKMGT"[i];

}

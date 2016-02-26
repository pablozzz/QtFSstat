#include "mainwindow.h"

MainWindow::MainWindow()
{
    createGUI();
    setLayout(layout);
    setWindowTitle("File System Statistics");
}


void MainWindow::createGUI()
{
    //create title label and buttons
    label = new QLabel("Please choose directory:");
    exit_button = new QPushButton ("Exit");
    layout = new QGridLayout;
    layout->addWidget(label,0,0);
    layout->addWidget(exit_button,0,1);

    connect(exit_button,SIGNAL(clicked(bool)),this,SLOT(close()));

    //create tree view for directory tree
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    tree = new QTreeView();
    tree->setModel(model);
    layout->addWidget(tree,1,0);
    selectionModel= tree->selectionModel();

    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
               this, SLOT(get_stat()));

    //create process bar label
    PBlabel = new QLabel("Progress");
    //PBlabel->setHidden(true);
    layout->addWidget(PBlabel,2,0);

    //create process bar
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    //progressBar->setHidden(true);
    layout->addWidget(progressBar,3,0);


}


void MainWindow::get_stat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dir_path = model->fileInfo(index).absoluteFilePath();

    //start it in new thread
    this->SubDirsCounter(dir_path);
    this->dirIterator(dir_path);
}

void MainWindow::dirIterator(QDir dir_path)
{
     //Files counter
    stat_info *folder_stat = new stat_info;
    folder_stat->fileCounter = 0;
    folder_stat->sizeCounter = 0;
    QDirIterator it(dir_path, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        this->getFilesStat(it.next(), folder_stat);
    }

    //print all extensions size
    QMap<QString,qint64> ::iterator iter = folder_stat->sizeStore.begin();
    for (;iter != folder_stat->sizeStore.end(); ++iter)
    {
        qDebug() << "Filgroup: " <<iter.key() << "Size: " <<this->fileSize(iter.value());

    }
}

void MainWindow::getFilesStat(QDir dir_path, stat_info* folder_stat)
{

    foreach (QString fileName,dir_path.entryList(QDir::Files))
    {
        QString full_path = dir_path.absoluteFilePath(fileName);
        QFileInfo *fileinfo= new QFileInfo(full_path);
        qint64 nSize = fileinfo->size();

        //add new extinsions and it's sizes in dictionary
        QString ext = fileinfo->completeSuffix();
        if (folder_stat->sizeStore.contains(ext))
        {
            folder_stat->sizeStore[ext] += nSize;
        }
        else
        {
            folder_stat->sizeStore.insert(ext, nSize);
        }
        folder_stat->sizeCounter += nSize;
        folder_stat->fileCounter++;

    }

}

void MainWindow::SubDirsCounter(QDir dir_path)
{
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

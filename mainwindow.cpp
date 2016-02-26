#include "mainwindow.h"
#include "newthread.h"

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

    //create textedit for display statistic information
    StatDisplay = new QTextEdit;
    layout->addWidget(StatDisplay,1,1);

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
    newThread thread;
    connect(&thread,SIGNAL(progress(int)),progressBar, SLOT(setValue(int)));
    //thread.start();

}


void MainWindow::get_stat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dir_path = model->fileInfo(index).absoluteFilePath();

    //start it in new thread
    stat = new Statistic();
    stat->SubDirsCounter(dir_path);
    stat->dirIterator(dir_path);
    this->printStat();
}
void MainWindow::printStat()
{
    QString info = "Subdirectories in selected folder: "+ stat->getsubdirsCounter(); //+ stat->SubDirsCounter();
    StatDisplay->setText(info);
    info = "Files in selected folder: " + QString::number(stat->getfileCounter());
    StatDisplay->append(info);
    info = "All files size in selected folder: " + stat->fileSize(stat->getsizeCounter());
    StatDisplay->append(info);


    //print all extensions size
    StatDisplay->append("Group | count | full_size | middle_size" );
    QMap<QString,qint64> ::iterator iter = stat->sizeStore.begin();
    for (;iter != stat->sizeStore.end(); ++iter)
    {
        QString group = iter.key();
        QString filesInGroup =  QString::number(stat->countStore[iter.key()]);
        QString groupSize = stat->fileSize(iter.value());
        QString middleSize = stat->fileSize(iter.value()/stat->countStore[iter.key()]);
        info = group+" | "+filesInGroup+" | "+ groupSize+ " | "+ middleSize;
        StatDisplay->append(info);
    }
}




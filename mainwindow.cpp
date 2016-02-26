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
    QString info = "Subdirectories in selected folder: " ; //+ stat->SubDirsCounter();
    StatDisplay->setText(stat->getsubdirsCounter());

    //print all extensions size
    QMap<QString,qint64> ::iterator iter = stat->sizeStore.begin();
    for (;iter != stat->sizeStore.end(); ++iter)
    {
        qDebug() << "Filgroup: " <<iter.key() << "Size: " <<stat->fileSize(iter.value());

    }
    //print all extensions count
    QMap<QString,qint64> ::iterator iter2 = stat->countStore.begin();
    for (;iter2 != stat->countStore.end(); ++iter2)
    {
        qDebug() << "Filgroup: " <<iter2.key() << "Count: " << iter2.value();

    }
}




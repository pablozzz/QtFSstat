#include "mainwindow.h"


MainWindow::MainWindow()
{
    createGUI();
    setLayout(mainlayout);
    setWindowTitle("File System Statistics");
}


void MainWindow::createGUI()
{
    //create layouts
    mainlayout = new QHBoxLayout;
    leftlayout = new QVBoxLayout;
    rightlayout = new QVBoxLayout;

    //create lables
    label = new QLabel("Please choose directory:");
    leftlayout->addWidget(label);
    statlabel = new QLabel("Statistic information");
    rightlayout->addWidget(statlabel);

    //create tree view for directory tree
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    tree = new QTreeView();
    tree->setModel(model);
    tree->hideColumn(1);           //hidden size "column"
    tree->setColumnWidth(0,200);   //size for "folder tree" column
    tree->setColumnWidth(2,50);    //size for "type" column
    leftlayout->addWidget(tree);

    selectionModel= tree->selectionModel();

    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
               this, SLOT(get_stat()));


    //create textedit for display statistic information
    StatDisplay = new QTextEdit;
    rightlayout->addWidget(StatDisplay);

    table = new QTableView;
    tablemodel = new QStandardItemModel(0,3,this);
    table->setModel(tablemodel);
    rightlayout->addWidget(table);

    //create process bar label
    PBlabel = new QLabel("Progress");
    //PBlabel->setHidden(true);
    leftlayout->addWidget(PBlabel);

    //create process bar
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    //progressBar->setHidden(true);
    leftlayout->addWidget(progressBar,3,0);

    exit_button = new QPushButton ("Exit");
    connect(exit_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    rightlayout->addWidget(exit_button);

    mainlayout->addLayout(leftlayout);
    mainlayout->addLayout(rightlayout);
}


void MainWindow::get_stat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dir_path = model->fileInfo(index).absoluteFilePath();
    qDebug() << dir_path;
    //start it in new thread

    this->buildStat(dir_path);

}

void MainWindow::addThread(QDir dirPath)
{
    wrapper = new newThread(dirPath);
    QThread* thread = new QThread;

    wrapper->moveToThread(thread);

    connect(thread,SIGNAL(started()),wrapper,SLOT(process()));
    connect(wrapper,SIGNAL(done()), thread, SLOT(quit()));
    connect(wrapper,SIGNAL(done()),this,SLOT(printStat()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));

    thread->start();

    return;

}

void MainWindow::buildStat(QDir dirPath)
{
    this->addThread(dirPath);
}


void MainWindow::printStat()
{
    //clere table and construct header
    tablemodel->clear();
    tablemodel->setHorizontalHeaderItem(0, new QStandardItem(QString("group")));
    tablemodel->setHorizontalHeaderItem(1, new QStandardItem(QString("count")));
    tablemodel->setHorizontalHeaderItem(2, new QStandardItem(QString("size")));
    tablemodel->setHorizontalHeaderItem(3, new QStandardItem(QString("avg size")));

    StatDisplay->setText(wrapper->getPath());
    QString info = "Subdirectories in selected folder: "+ wrapper->subDirsCouter;
    StatDisplay->append(info);
    info = "Files in selected folder: " + QString::number(wrapper->fileCounter);
    StatDisplay->append(info);
    info = "All files size in selected folder: " + QString::number(wrapper->sizeCounter);
    StatDisplay->append(info);


    //print all extensions size

    QMap<QString,qint64> ::iterator iter = wrapper->sizeStore.begin();
    int row = 0;
    for (;iter != wrapper->sizeStore.end(); ++iter)
    {

        QString group = iter.key();
        QString filesInGroup =  QString::number(wrapper->countStore[iter.key()]);
        QString groupSize = QString::number(iter.value());
        QString avgSize = QString::number(iter.value()/wrapper->countStore[iter.key()]);

        tablemodel->appendRow(new QStandardItem());  //add new string in table

        QStandardItem *file_group = new QStandardItem(group);
        tablemodel->setItem(row,0,file_group);       //add group in table

        QStandardItem *file_count = new QStandardItem(filesInGroup); //add count in table
        tablemodel->setItem(row,1,file_count);


        QStandardItem *group_size = new QStandardItem(groupSize);
        tablemodel->setItem(row,2,group_size);

        QStandardItem *avg_size = new QStandardItem(avgSize);
        tablemodel->setItem(row,3,avg_size);
        row++;
    }
}


#include "mainwindow.h"


MainWindow::MainWindow()
{
    createGUI();
    setLayout(mainLayout);
    setWindowTitle("File System Statistics");
}


void MainWindow::createGUI()
{
    //create layouts
    mainLayout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;

    //create lables
    treeWndLabel = new QLabel("Please choose directory:");
    leftLayout->addWidget(treeWndLabel);
    statLabel = new QLabel("Statistic information");
    rightLayout->addWidget(statLabel);

    //create tree view for directory tree
    model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    tree = new QTreeView();
    tree->setModel(model);
    tree->hideColumn(1);           //hidden size "column"
    tree->setColumnWidth(0,200);   //size for "folder tree" column
    tree->setColumnWidth(2,70);    //size for "type" column
    leftLayout->addWidget(tree);

    selectionModel= tree->selectionModel();

    connect(selectionModel,
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this,SLOT(getStat()));


    //create textedit for display statistic information
    statDisplay = new QTextEdit;
    rightLayout->addWidget(statDisplay);

    //create table and table header
    table = new QTableView;
    tableModel = new QStandardItemModel(0,4,this);
    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("group")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("count")));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QString("size")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QString("avg size")));

    table->setModel(tableModel);
    rightLayout->addWidget(table);

    //create process bar label
    pogressBarLabel = new QLabel("Progress");
    leftLayout->addWidget(pogressBarLabel);

    //create process bar
    progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);
    leftLayout->addWidget(progressBar,3,0);

    exitButton = new QPushButton ("Exit");
    connect(exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    rightLayout->addWidget(exitButton);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
}


void MainWindow::getStat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dirPath  = model->fileInfo(index).absoluteFilePath();

    //check selected path
    QFileInfo *selectedPath = new QFileInfo(dirPath.path());
    if (selectedPath->isDir())
    {
        //create and start timer for progress bar
        timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
        timer->start(1000);

        //start it in new thread
        this->computeStat(dirPath);
    }
    else
    {
        statDisplay->clear();
        statDisplay->append("Sorry, it's not a directory");
    }

}

void MainWindow::addThread(QDir dirPath)
{
    wrapper = new Wrapper(dirPath);
    QThread* thread = new QThread;

    wrapper->moveToThread(thread);

    connect(thread,SIGNAL(started()),wrapper,SLOT(process()));
    connect(wrapper,SIGNAL(done()), thread, SLOT(quit()));
    connect(wrapper,SIGNAL(done()),this,SLOT(printStat()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    connect(wrapper,SIGNAL(timerValue(int)),progressBar,SLOT(setValue(int)));

    thread->start();

    return;

}

void MainWindow::computeStat(QDir dirPath)
{
    this->addThread(dirPath);
}


void MainWindow::printStat()
{
    //cleare table and construct header
    tableModel->clear();
    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("group")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("count")));
    tableModel->setHorizontalHeaderItem(2, new QStandardItem(QString("size")));
    tableModel->setHorizontalHeaderItem(3, new QStandardItem(QString("avg size")));

    //show selected folder path
    statDisplay->setText(wrapper->statistic->getPath());

    QString info = "Subdirectories in selected folder: "
            + wrapper->statistic->getSubDirsCounter();

    info += "\nFiles in selected folder: "
         + QString::number(wrapper->statistic->getFileCounter());

    info += "\nAll files size in selected folder: "
         + wrapper->statistic->getFileSize(wrapper->statistic->getSizeCounter());

    statDisplay->append(info);

    //print all extensions count and size

    //load QMap elements in local variable
    QMap<QString,qint64> countStore = wrapper->statistic->getCountStore();
    QMap<QString,qint64> sizeStore  = wrapper->statistic->getSizeStore();

    QMap<QString,qint64> ::iterator iter = sizeStore.begin();
    int row = 0;
    for (;iter != sizeStore.end(); ++iter)
    {

        QString group = iter.key();

        QString filesInGroup =  QString::number(countStore[iter.key()]);
        QString groupSize = wrapper->statistic->getFileSize(iter.value());

        qint64 avgSizeBytes = iter.value()/countStore[iter.key()];
        QString avgSize = wrapper->statistic->getFileSize(avgSizeBytes);
        //add new string in table
        tableModel->appendRow(new QStandardItem());
        //add group in table
        QStandardItem *fileGroup = new QStandardItem(group);
        tableModel->setItem(row,0,fileGroup);
        //add count in table
        QStandardItem *fileCount = new QStandardItem(filesInGroup);
        tableModel->setItem(row,1,fileCount);
        //add size of group in table
        QStandardItem *groupSizeRow = new QStandardItem(groupSize);
        tableModel->setItem(row,2,groupSizeRow);
        //add average size in table
        QStandardItem *avgSizeRow = new QStandardItem(avgSize);
        tableModel->setItem(row,3,avgSizeRow);
        row++;
    }
}

void MainWindow::timerEvent()
{
    int curPbval = progressBar->value();
    if (curPbval < 99)
        progressBar->setValue(curPbval+1);
}

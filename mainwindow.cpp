#include "mainwindow.h"
#include "newthread.h"

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

    newThread thread;
    connect(&thread,SIGNAL(progress(int)),progressBar, SLOT(setValue(int)));
    //thread.start();

    mainlayout->addLayout(leftlayout);
    mainlayout->addLayout(rightlayout);
}


void MainWindow::get_stat()
{
    const QModelIndex index = tree->selectionModel()->currentIndex();
    QDir dir_path = model->fileInfo(index).absoluteFilePath();

    //start it in new thread
    stat = new Statistic(dir_path);
    stat->dirIterator();
    this->printStat();
}
void MainWindow::printStat()
{
    //clere table and construct header
    tablemodel->clear();
    tablemodel->setHorizontalHeaderItem(0, new QStandardItem(QString("group")));
    tablemodel->setHorizontalHeaderItem(1, new QStandardItem(QString("count")));
    tablemodel->setHorizontalHeaderItem(2, new QStandardItem(QString("size")));
    tablemodel->setHorizontalHeaderItem(3, new QStandardItem(QString("avg size")));

    StatDisplay->setText(stat->getPath());
    QString info = "Subdirectories in selected folder: "+ stat->getsubdirsCounter(); //+ stat->SubDirsCounter();
    StatDisplay->append(info);
    info = "Files in selected folder: " + QString::number(stat->getfileCounter());
    StatDisplay->append(info);
    info = "All files size in selected folder: " + stat->fileSize(stat->getsizeCounter());
    StatDisplay->append(info);


    //print all extensions size

    QMap<QString,qint64> ::iterator iter = stat->sizeStore.begin();
    int row = 0;
    for (;iter != stat->sizeStore.end(); ++iter)
    {

        QString group = iter.key();
        QString filesInGroup =  QString::number(stat->countStore[iter.key()]);
        QString groupSize = stat->fileSize(iter.value());
        QString avgSize = stat->fileSize(iter.value()/stat->countStore[iter.key()]);

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




#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent) : QWidget(parent)
{
    this->moveToCenter();
    setWindowTitle("Starting");
    this->createGui();
    setLayout(layout_);
}

void StartWindow::moveToCenter()
{
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void StartWindow::createGui()
{
    layout_ = new QHBoxLayout;
    label_ = new QLabel("Directory tree construction...");
    layout_->addWidget(label_);
}

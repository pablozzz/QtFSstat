#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QLabel>
#include <QGridLayout>

class StartWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StartWindow(QWidget *parent = 0);

private:
    void moveToCenter(); //move this widget in screen centre
    void createGui();

    QHBoxLayout* layout_;
    QLabel* label_;
};

#endif // STARTWINDOW_H

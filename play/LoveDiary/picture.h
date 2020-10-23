#ifndef PICTURE_H
#define PICTURE_H

#include <QDialog>

namespace Ui {
class Picture;
}

class Picture : public QDialog
{
    Q_OBJECT

public:
    explicit Picture(QWidget *parent = 0);
    ~Picture();

private:
    Ui::Picture *ui;
};

#endif // PICTURE_H

#ifndef SORTTABLEELEMENTSBYCOUNTWGT_H
#define SORTTABLEELEMENTSBYCOUNTWGT_H

#include <QDialog>

class SortTableElementsByCountWgt : public QDialog
{
    Q_OBJECT

public:
    explicit SortTableElementsByCountWgt(QWidget *parent, const QRect& rect);
    ~SortTableElementsByCountWgt();
};

#endif // SORTTABLEELEMENTSBYCOUNTWGT_H

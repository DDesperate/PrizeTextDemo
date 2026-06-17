#ifndef NUMLINEEDIT_H
#define NUMLINEEDIT_H

#include <QLineEdit>

class NumLineEdit : public QLineEdit
{
  Q_OBJECT

public:
  NumLineEdit(QWidget *parent = nullptr);
  void fmtNum();
  QList<quint8> strToList();
  void setListIn(const QList<quint8> numList);

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;

};

#endif // MYLINEEDIT_H

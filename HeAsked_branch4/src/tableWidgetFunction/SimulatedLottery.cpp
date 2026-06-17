#include<QLineEdit>
#include"cmn.hpp"
#include"widget.h"

void Widget::SimulatedLottery(QLineEdit *prizeLe,QLineEdit *selectPrizeLe,QTextBrowser* tb)
{

      tb->clear();
      //对PrizeLe进行如下操作

      QStringList prize = prizeLe->text().split(" ");
      prize = prize.toSet().toList();//去重
      prize.sort();//排序
      QString strLe;//间隔空格放进QString
      for(auto iter:prize){
          if(iter.toInt() >0 && iter.toInt()<=80)
              strLe += iter + " ";
      }
      prizeLe->setText(strLe.trimmed());//去掉两端空格以及\r\n后放进LineEdit

      QStringList selectPrize = selectPrizeLe->text().split(" ");
      selectPrize = selectPrize.toSet().toList();//去重
      selectPrize.sort();//排序
      strLe.clear();//间隔空格放进QString
      for(auto iter:selectPrize){
          if(iter.toInt() >0 && iter.toInt()<=80)
              strLe += iter + " ";
      }
      selectPrizeLe->setText(strLe.trimmed());//去掉两端空格以及\r\n后放进LineEdit

      //获取到选中的prize放到数据结构中
      QVector<QString> selectPrizeVec = strLe.trimmed().split(" ").toVector();

      int selectNum = group->checkedButton()->text().mid(1).toInt();

      //排列组合形成表table
      QVector<QVector<QString>> table;
      table = Combine(selectPrizeVec,selectNum);
      int SimuliateList[15] = {0};      //这里为什么是15？
      for(auto list:table){
          int count = 0;
          for(auto iter:list){
              if(prize.contains(iter))
                  count++;
          }
          SimuliateList[count]++;
      }
      tb->setAlignment(Qt::AlignCenter);
      for(int i = selectNum;i>=0;i--)
      {
          tb->append(QString::fromUtf8("中%1：%2注").arg(i).arg(SimuliateList[i]));
      }

}

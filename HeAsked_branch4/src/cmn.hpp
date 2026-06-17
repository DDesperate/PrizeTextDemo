#ifndef CMN_HPP
#define CMN_HPP

#include<QVector>
//Cmn排列组合，原理详见"排列组合.md"
template <typename T>
QVector<T> Combine(const T data, const int m)
{
    //n为容器中的元素个数
    //檢查元素數量是否超過m，超过则返回一个空的容器
    int n = static_cast<int>(data.size());
    if (m <= 0 || m > n)
        return{};

    int start = 0, depth = 0;
    QVector<T> result;
    T temp(m, 0);   //创建一个长度为m的容器，每个元素为0
    CombineInner(data, result, temp, n, m, start, depth);
    return result;
}

template <typename T>
void CombineInner(const T& data, QVector<T>& result, T& temp, const int n, const int m, int start, int depth)
{
    for (int i = start; i < n - (m - depth - 1); ++i)
    {
        temp[depth] = data[i];                                              //每层输出一个元素
        if (depth == m - 1)
            result.push_back(temp);                                         //只选m个数组合，个数达到后存入
        else
            CombineInner(data, result, temp, n, m, i + 1, depth + 1);       //递归深入
    }
}

#endif // CMN_H

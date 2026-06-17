#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QVector>
#include "downstruct.h"
#include "sparsestruct.h"

/**
 * @brief 数据格式转换工具类
 * 
 * 提供原始数据格式与稀疏数组格式之间的相互转换功能
 */
class DataConverter
{
public:
    // ========== 原始格式 → 稀疏数组 ==========
    
    /**
     * @brief 将单行数据转换为稀疏数组格式
     */
    static SparseRow toSparseRow(const slctTbRow &row);
    
    /**
     * @brief 将整个表格数据转换为稀疏数组格式
     */
    static SparseTableData toSparseData(const QVector<slctTbRow> &data);
    
    // ========== 稀疏数组 → 原始格式 ==========
    
    /**
     * @brief 将稀疏数组行转换回原始格式
     */
    static slctTbRow fromSparseRow(const SparseRow &sparseRow);
    
    /**
     * @brief 将整个稀疏数组数据转换回原始格式
     */
    static QVector<slctTbRow> fromSparseData(const SparseTableData &sparseData);
    
    // ========== 辅助方法 ==========
    
    /**
     * @brief 将单个奖注信息转换为稀疏格式
     */
    static SparsePrizeInfo toSparsePrizeInfo(const slcInfo &info);
    
    /**
     * @brief 将稀疏奖注信息转换回原始格式
     */
    static slcInfo fromSparsePrizeInfo(const SparsePrizeInfo &sparseInfo);
};

#endif // DATACONVERTER_H

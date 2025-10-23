#pragma once
#include <QObject>
#include <QVector>
#include <vector>
#include <string>

struct TipData {
    double total_bill;
    double tip;
    std::string sex;
    std::string smoker;
    std::string day;
    std::string time;
    int size;
};

class DataProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<double> tipsPerDay READ tipsPerDay NOTIFY dataChanged)
    Q_PROPERTY(double maxTipSum READ maxTipSum NOTIFY dataChanged)
    Q_PROPERTY(double maxSingleTip READ maxSingleTip NOTIFY dataChanged)
    Q_PROPERTY(double maxSingleBill READ maxSingleBill NOTIFY dataChanged)
    Q_PROPERTY(QVector<double> getAllTips READ getAllTips NOTIFY dataChanged)
    Q_PROPERTY(QVector<double> getAllBills READ getAllBills NOTIFY dataChanged)
    Q_PROPERTY(QVector<int> getAllSize READ getAllSize NOTIFY dataChanged )
public:
    explicit DataProvider(QObject* parent = nullptr);

    // Data accessors
    QVector<double> tipsPerDay() const;
    double maxTipSum() const;
    double maxSingleTip() const;
    double maxSingleBill() const;
    QVector<double> getAllTips() const;
    QVector<double> getAllBills() const;
    QVector<int> getAllSize() const;

    // Method to populate/update data
    void setTips(const std::vector<TipData>& newTips);

signals:
    void dataChanged();

private:
    std::vector<TipData> m_tips;
};

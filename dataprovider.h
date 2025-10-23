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
    Q_PROPERTY(QVector<int> tipsPerDay READ tipsPerDay NOTIFY dataChanged)
    Q_PROPERTY(int maxPerDay READ maxPerDay NOTIFY dataChanged)
    Q_PROPERTY(QVector<double> allTips READ allTips NOTIFY dataChanged)
    Q_PROPERTY(QVector<double> allTotalBills READ allTotalBills NOTIFY dataChanged)

public:
    explicit DataProvider(QObject* parent = nullptr);

    // Data accessors
    QVector<int> tipsPerDay() const;
    int maxPerDay() const;
    QVector<double> allTips() const;
    QVector<double> allTotalBills() const;

    // Method to populate/update data
    void setTips(const std::vector<TipData>& newTips);

signals:
    void dataChanged();

private:
    std::vector<TipData> m_tips;
};

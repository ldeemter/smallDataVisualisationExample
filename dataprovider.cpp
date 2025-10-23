#include "DataProvider.h"

DataProvider::DataProvider(QObject* parent)
    : QObject(parent)
{
    // Optional: populate default data here
}

void DataProvider::setTips(const std::vector<TipData>& newTips) {
    m_tips = newTips;
    emit dataChanged(); // notify QML to update charts
}

QVector<int> DataProvider::tipsPerDay() const {
    int mondaySum = 0, tuesSum = 0, wedSum = 0, thuSum = 0, friSum = 0, satSum = 0, sunSum = 0;

    for (const auto& tip : m_tips) {
        if (tip.day == "Mon") mondaySum += tip.size;
        else if (tip.day == "Tue") tuesSum += tip.size;
        else if (tip.day == "Wed") wedSum += tip.size;
        else if (tip.day == "Thu") thuSum += tip.size;
        else if (tip.day == "Fri") friSum += tip.size;
        else if (tip.day == "Sat") satSum += tip.size;
        else if (tip.day == "Sun") sunSum += tip.size;
    }

    return {mondaySum, tuesSum, wedSum, thuSum, friSum, satSum, sunSum};
}

int DataProvider::maxPerDay() const {
    QVector<int> sums = tipsPerDay();
    return *std::max_element(sums.begin(), sums.end());
}

QVector<double> DataProvider::allTips() const {
    QVector<double> tipsVec;
    for (const auto& tip : m_tips)
        tipsVec.append(tip.tip);
    return tipsVec;
}

QVector<double> DataProvider::allTotalBills() const {
    QVector<double> billsVec;
    for (const auto& tip : m_tips)
        billsVec.append(tip.total_bill);
    return billsVec;
}

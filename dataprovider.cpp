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

QVector<double> DataProvider::tipsPerDay() const {
    double mondaySum = 0, tuesSum = 0, wedSum = 0, thuSum = 0, friSum = 0, satSum = 0, sunSum = 0;

    for (const auto& tip : m_tips) {
        if (tip.day == "Mon") mondaySum += tip.tip;
        else if (tip.day == "Tue") tuesSum += tip.tip;
        else if (tip.day == "Wed") wedSum += tip.tip;
        else if (tip.day == "Thur") thuSum += tip.tip;
        else if (tip.day == "Fri") friSum += tip.tip;
        else if (tip.day == "Sat") satSum += tip.tip;
        else if (tip.day == "Sun") sunSum += tip.tip;
    }

    return {mondaySum, tuesSum, wedSum, thuSum, friSum, satSum, sunSum};
}

double DataProvider::maxTipSum() const {
    QVector<double> sums = tipsPerDay();
    return *std::max_element(sums.begin(), sums.end());
}


double DataProvider::maxSingleTip() const {
    double currentMaxTip= 0;
    for (const auto& tip : m_tips)
        if (currentMaxTip<tip.tip){
            currentMaxTip = tip.tip;
        }
    return currentMaxTip;
}

double DataProvider::maxSingleBill() const {
    double currentMaxTip= 0;
    for (const auto& tip : m_tips)
        if (currentMaxTip<tip.total_bill){
            currentMaxTip = tip.total_bill;
        }
    return currentMaxTip;
}
QVector<double> DataProvider::getAllTips() const {
    QVector<double> tipsVec;
    for (const auto& tip : m_tips)
        tipsVec.append(tip.tip);
    return tipsVec;
}

QVector<double> DataProvider::getAllBills() const {
    QVector<double> billsVec;
    for (const auto& tip : m_tips)
        billsVec.append(tip.total_bill);
    return billsVec;
}

QVector<int> DataProvider::getAllSize() const {
    QVector<int> sizes;
    for (const auto& tip : m_tips)
        sizes.append(tip.size);
    return sizes;
}

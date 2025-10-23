import QtQuick
import QtQuick.Controls
import QtGraphs
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1600
    height: 800
    title: "Dynamic Bar Graph"
    Rectangle{
        x:0
        y:0
        height: 14
        width: parent.width / 2
        color: graphsView.theme.backgroundColor
        Text{
            text: "Tip Sum per day"
            color: "#fff"
        }
    }

    Rectangle{
        x:0
        y:14
        width: parent.width / 2
        height: parent.height - 14
        GraphsView {
            id: graphsView
            anchors.fill : parent

            theme: GraphsTheme {
                colorScheme: GraphsTheme.ColorScheme.Dark
                seriesColors: ["#E0D080", "#B0A060"]
                borderColors: ["#807040", "#706030"]
                grid.mainColor: "#ccccff"
                grid.subColor: "#eeeeff"
                axisY.mainColor: "#ccccff"
                axisY.subColor: "#eeeeff"
            }
            axisX: BarCategoryAxis {
                categories: ["Mon", "Tue", "Wen", "Thu", "Fri", "Sat", "Sun"]
                lineVisible: false
            }
            axisY: ValueAxis {
                min: 0
                max: dataProvider.maxPerDay
                subTickCount: 4
            }
            BarSeries {
                BarSet {
                    id: barSet
                    values: dataProvider.tipsPerDay
                }
            }
        }

    }

    Rectangle{
        x: parent.width / 2
        y: 0
        height: 14
        width: parent.width / 2
        color: graphsView.theme.backgroundColor
        Text{
            text: "Correlation between tip and total bill"
            color: "#fff"
        }
    }

    Rectangle{
        x: parent.width / 2 -14
        y: 0
        width: parent.width / 2
        height: parent.height
        GraphsView {
            anchors.fill: parent
            axisX: ValueAxis {
                max: 30
            }
            axisY: ValueAxis {
                max: 20
            }


            ScatterSeries {
                id: series
                color: "#00ff00"
                Component.onCompleted: {
                    console.log("Data changed!")
                    let tips = dataProvider.allTips
                    let bills = dataProvider.allTotalBills
                    for (let i = 0; i < tips.length; i++) {
                        series.append(bills[i], tips[i])
                    }
                }

            }
        }
    }
}

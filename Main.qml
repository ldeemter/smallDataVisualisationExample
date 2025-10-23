import QtQuick
import QtQuick.Controls
import QtGraphs
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 1600
    height: 800
    title: "Dynamic Bar Graph"

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 2
        rows: 2
        columnSpacing: 5
        rowSpacing: 0

        // Header for Bar Chart
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 32
            Layout.column: 0
            Layout.row: 0
            color: "#2d2d30"

            Text {
                anchors.centerIn: parent
                text: "Tip Sum per day"
                color: "#ffffff"
                font.pixelSize: 12
                font.weight: Font.Medium
            }
        }

        // Header for Scatter Chart
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 32
            Layout.column: 1
            Layout.row: 0
            color: "#2d2d30"

            Text {
                anchors.centerIn: parent
                text: "Correlation between tip and total bill"
                color: "#ffffff"
                font.pixelSize: 12
                font.weight: Font.Medium
            }
        }

        // Bar Chart Container
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.column: 0
            Layout.row: 1
            color: "#1e1e1e"
            border.color: "#404040"
            border.width: 1

            GraphsView {
                id: graphsView
                anchors.fill: parent
                anchors.margins: 2

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
                    categories: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
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

        // Scatter Chart Container
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.column: 1
            Layout.row: 1
            color: "#1e1e1e"
            border.color: "#404040"
            border.width: 1

            GraphsView {
                anchors.fill: parent
                anchors.margins: 2

                theme: GraphsTheme {
                    colorScheme: GraphsTheme.ColorScheme.Dark
                }

                axisX: ValueAxis {
                    min: 0
                    max: 30
                    titleText: "Total Bill ($)"
                }
                axisY: ValueAxis {
                    min: 0
                    max: 20
                    titleText: "Tip ($)"
                }

                ScatterSeries {
                    id: series
                    color: "#00ff00"

                    pointDelegate: Component {
                        Rectangle {
                            width: 6
                            height: 6
                            radius: 3
                            color: "#00ff00"
                            border.color: "#ffffff"
                            border.width: 1
                        }
                    }

                    Connections {
                        target: dataProvider
                        function onDataChanged() {
                            console.log("Data changed - updating scatter plot")
                            series.clear()
                            let tips = dataProvider.allTips
                            let bills = dataProvider.allTotalBills
                            for (let i = 0; i < tips.length; i++) {
                                series.append(bills[i], tips[i])
                            }
                        }
                    }

                    Component.onCompleted: {
                        console.log("Scatter series completed - loading initial data")
                        if (dataProvider) {
                            let tips = dataProvider.allTips
                            let bills = dataProvider.allTotalBills
                            console.log("Initial tips:", tips)
                            console.log("Initial bills:", bills)
                            if (tips && bills) {
                                for (let i = 0; i < tips.length; i++) {
                                    console.log('Added point:', bills[i], tips[i])
                                    series.append(bills[i], tips[i])
                                }
                            }
                        } else {
                            console.log("dataProvider not available yet")
                        }
                    }
                }
            }
        }
    }
}

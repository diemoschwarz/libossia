import QtQuick 2.0
import Ossia 1.0 as Ossia

Item
{
    Ossia.OSCQueryServer {
        id: dev
    }

    Rectangle {
        color: "red"
        height: 200
        Ossia.Property on height { id: rec_height }
        width: 200
        Ossia.Property on width { id: rec_width }
        x: 100
        y: 100
        Ossia.Property on rotation { id: rec_rot }
    }

    Ossia.Interval {
        id: root
        nominalDuration: 2000
        minDuration: 2000
        maxDuration: 2000

        Ossia.Automation {
            target: rec_height
            yMin: 10
            yMax: 400
        }
        Ossia.Automation {
            target: rec_width
            yMin: 50
            yMax: 100
        }

        Ossia.Scenario {
            id: scenario
            startSync: Ossia.Sync {
                Ossia.Condition {
                    id: c1
                }
            }

            Ossia.Interval {
                follows: c1
                precedes: c2
                nominalDuration: 1000
                minDuration: 1000
                maxDuration: 1000

                Ossia.Automation {
                    target: rec_rot
                    yMin: 100
                    yMax: 500
                }
            }

            Ossia.Sync {
                Ossia.Condition {
                    id: c2
                }
            }

            Ossia.Interval {
                follows: c2
                precedes: c3
                nominalDuration: 1000
                minDuration: 1000
                maxDuration: 1000

                Ossia.Automation {
                    target: rec_rot
                    yMin: 500
                    yMax: 100
                }
            }

            Ossia.Sync {
                Ossia.Condition {
                    id: c3
                }
            }

        }
    }

    Component.onCompleted: root.play()
}

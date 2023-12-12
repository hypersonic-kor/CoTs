#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include <QString>
#include <QMap>

class WorldClock : public QMainWindow {
    Q_OBJECT

public:
    WorldClock(QWidget *parent = nullptr) : QMainWindow(parent) {
        timeDiff.insert("서울", qMakePair(9, "KST"));
        timeDiff.insert("워싱턴 DC", qMakePair(-5, "EST"));
        timeDiff.insert("리스본", qMakePair(0, "WET"));
        timeDiff.insert("호눌룰루", qMakePair(-10, "HST"));
        timeDiff.insert("베이징", qMakePair(8, "CST"));
        timeDiff.insert("타슈켄트", qMakePair(5, "TJT"));
        timeDiff.insert("이슬라마바드", qMakePair(5, "PKT"));
        timeDiff.insert("뉴델리", qMakePair(5.5, "IST"));
        timeDiff.insert("하르툼", qMakePair(3, "ART"));
        timeDiff.insert("방기", qMakePair(1, "CET"));
        timeDiff.insert("마드리드", qMakePair(1, "CET"));
        timeDiff.insert("누크", qMakePair(1.5, "NST"));
        timeDiff.insert("뉴욕", qMakePair(-4, "EDT"));
        timeDiff.insert("런던", qMakePair(0, "GMT"));
        timeDiff.insert("파리", qMakePair(1, "CET"));
        timeDiff.insert("도쿄", qMakePair(9, "JST"));
        timeDiff.insert("시드니", qMakePair(11, "AEDT"));
        timeDiff.insert("상파울루", qMakePair(-3, "BRT"));
        timeDiff.insert("카이로", qMakePair(2, "EET"));
        timeDiff.insert("모스크바", qMakePair(3, "MSK"));
        timeDiff.insert("베를린", qMakePair(1, "CET"));
        timeDiff.insert("상트페테르부르크", qMakePair(3, "MSK"));
        timeDiff.insert("상하이", qMakePair(8, "CST"));
        timeDiff.insert("홍콩", qMakePair(8, "HKT"));
        timeDiff.insert("두바이", qMakePair(4, "GST"));
        timeDiff.insert("멕시코 시티", qMakePair(-5, "CDT"));
        timeDiff.insert("부에노스 아이레스", qMakePair(-3, "ART"));
        timeDiff.insert("방콕", qMakePair(7, "ICT"));
        timeDiff.insert("유럽/아프리카", qMakePair(0, "GMT"));
        timeDiff.insert("태평양", qMakePair(-8, "PST"));
        // 추가할 나라 및 지역 추가

        InitializeClocks();
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTimes()));
        timer->start(1000);
    }

private slots:
    void UpdateTimes() {
        for (const QString &city : timeDiff.keys()) {
            labels[city]->setText(QString("%1: %2").arg(city).arg(GetLocalTime(city)));
        }
    }

private:
    QMap<QString, QPair<int, QString>> timeDiff;
    QMap<QString, QLabel*> labels;

    void InitializeClocks() {
        int idx = 0;
        for (const QString &city : timeDiff.keys()) {
            QLabel *label = new QLabel(this);
            label->setGeometry(20, 5 + idx * 30, 200, 20);
            label->setText(QString("%1: %2").arg(city).arg(GetLocalTime(city)));
            label->setFont(QFont("Arial", 9));
            label->show();
            labels.insert(city, label);
            idx++;
        }
    }

    QString GetLocalTime(const QString &city) {
        int cityTimeDiff = timeDiff[city].first;
        QString cityStandardTime = timeDiff[city].second;
        QDateTime currentUtcTime = QDateTime::currentDateTimeUtc();
        QDateTime localTime = currentUtcTime.addSecs(cityTimeDiff * 3600);
        return localTime.toString(QString("%1 yyyy MM dd HH mm ss").arg(cityStandardTime));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    WorldClock clock;
    clock.show();
    return app.exec();
}

#include "main.moc"

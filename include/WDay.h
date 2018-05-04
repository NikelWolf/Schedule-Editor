#ifndef WDAY_H
#define WDAY_H

#include <QtWidgets>
#include "WLesson.h"

class WDay : public QWidget {
Q_OBJECT
public:

    QVector<QStringList> timeOfLesson = {
            {" 9-00", "10-30"},
            {"10-40", "12-10"},
            {"13-00", "14-30"},
            {"14-40", "16-10"},
            {"16-20", "17-50"},
            {"18-00", "19-30"},
    };
    QLabel *wdayOfWeek;
    std::array<WLesson *, 6> wlessons;

    explicit WDay( const QString &dayOfWeek, QWidget *parent = nullptr);
    ~WDay() override = default;

    void createWidgets(const QString &dayOfWeek);

signals:

public slots:
};

#endif // WDAY_H
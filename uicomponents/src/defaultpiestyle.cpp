#include "defaultpiestyle.h"

DefaultPieStyle * DefaultPieStyle::s_instance = 0;
DefaultPieStyle * DefaultPieStyle::instance()
{
    if (s_instance == 0) {
        s_instance = new DefaultPieStyle;
    }
    return s_instance;
}

DefaultPieStyle::DefaultPieStyle(QObject *parent) :
    StyleOption(parent)
{
    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::blue));
    setFont(QFont());
}


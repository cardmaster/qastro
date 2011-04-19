#ifndef DEFAULTPIESTYLE_H
#define DEFAULTPIESTYLE_H
#include "styleoption.h"

class DefaultPieStyle : public StyleOption
{
    Q_OBJECT
public:
    static DefaultPieStyle *instance();

private:
    static DefaultPieStyle *s_instance;
    explicit DefaultPieStyle(QObject *parent = 0);
};

#endif // DEFAULTPIESTYLE_H

#ifndef SCCONTROLLER_H
#define SCCONTROLLER_H

#include "scmodel.h"
#include <QObject>
#include <string>
#include <QString>


namespace s21 {
    class SCController : public QObject
    {
        Q_OBJECT

    public:
        friend class SCView;
        SCController(QObject *parent = nullptr);
        virtual ~SCController() = default;

        QString PassNum(QString text);
        QString PassX();
        QString PassOpenBracket();
        QString PassClosingBracket();
        QString PassOperator(QString text);
        QString PassTringonometric(QString text);
        QString PassDot();
        QString ClickedAC();
        QString ClickedBS();
        QString InitCalculation();


        plotOutputData PassPlotData(plotInputData data);

        // std::pair<float, std::string> PassExpr(std::string expr);

    private:
        SCModel *model_;
    };
}


#endif // SCCONTROLLER_H

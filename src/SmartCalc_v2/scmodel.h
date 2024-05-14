#ifndef SCMODEL_H
#define SCMODEL_H
#include <iostream>
#include <string>
#include <list>
#include <ostream>
#include <QObject>
#include <QRegularExpression>
#include "QCustomPlot/lib/qcustomplot.h"

namespace s21 {

class plotInputData {
public:
    double x_min, x_max, y_min, y_max;
    double h_step, x_val;
    plotInputData() 
    : x_min(0.0f)
    , x_max(0.0f)
    , y_min(0.0f)
    , y_max(0.0f)
    , h_step(0.0f)
    , x_val(0.0f) 
    {}
};

class plotOutputData {
public:
    QVector<double> x_vector;
    QVector<double> y_vector;
    double y_res;
};

class SCModel : public QObject
{
    Q_OBJECT

public:
    explicit SCModel(QObject *parent = nullptr);
    virtual ~SCModel() = default;

    //  Insertion to expr QString
    QString InsertNum(QString text);
    QString InsertX();
    QString InsertOpenBracket();
    QString InsertClosingBracket();
    QString InsertOperator(QString text);
    QString InsertTrigonometric(QString text);
    QString InsertDot();
    QString ClearExpr();
    QString EraseLast();

    //  Calculation
    QString StartCalculations();
    plotOutputData PlotCalculations(plotInputData data);

private:
    QString expr;
    std::string expr_std;
    int bracket_counter;
    int error;
    QRegularExpression reg_expr;
    std::list<std::pair<std::pair<std::string, double>,int>> expr_listed;

/*
        /===========LIST_ELEMENT===========\
        |   /-----------pair-----------\   |
        |   |   /---pair---\           |   |
        |   |   |  string  |    int    |   |
        |   |   |  double  |           |   |
        |   |   \----------/           |   |
        |   \--------------------------/   |
        \==================================/
        string  - for operators (x.first.first)
        double  - for nums      (x.first.second)
        int     - for priority  (x.second)
*/

    //  Support Insertion
    void ChopWrap(int a);
    void PhantomMulti();
    void OpenBracketsWrap();
    void ClosingBracketsWrap();

    //  Main Calculation
    void ValidateExpr();
    std::pair<double, std::string> CalculateExpression(std::string expr);
    void ExprToList();
    void RawListToPostPolish();
    std::pair<double, int> CalculateList();
    QString PrepareNum(double num);

    //  Sup Calculation
    void CharHandler(std::string::iterator &it);
    void PushToList(const std::string &elem);
    void NumPushCase(const std::string &elem);
    void OperatorPushCase(const std::string &elem);
    void BinaryCase(std::list<std::pair<std::pair<std::string, double>,int>>::iterator &it);
    void UnaryCase(std::list<std::pair<std::pair<std::string, double>,int>>::iterator &it);
};
};
#endif // SCMODEL_H

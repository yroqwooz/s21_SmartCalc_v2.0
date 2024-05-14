#ifndef SCVIEW_H
#define SCVIEW_H

#include <QMainWindow>
#include <QRegularExpression>
#include <string>
#include <QWidget>
#include "./ui_scview.h"
// #include <QDebug>

#include "plotwindow.h"
#include "sccontroller.h"
#include "CreditCalc/cccontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SCView;
}
QT_END_NAMESPACE

namespace s21 {


class SCView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SCView(QWidget *parent = nullptr);
    ~SCView();

signals:
    void InitUploadPData();

public slots:
    void UpdateCreditRes(std::list<CreditData> ResList);

private slots:
    void SignalsAndSlots();
    void NumPressed();

    void on_Button_AC_clicked();
    void on_Button_plus_clicked();
    void on_Button_dot_clicked();
    void on_Button_minus_clicked();
    void on_Button_multi_clicked();
    void on_Button_divide_clicked();
    void on_Button_mod_clicked();
    void on_Button_exp_clicked();
    void on_Button_backspace_clicked();
    void on_Button_bracket_open_clicked();
    void on_Button_bracket_close_clicked();
    void on_Button_sin_clicked();
    void on_Button_cos_clicked();
    void on_Button_tan_clicked();
    void on_Button_asin_clicked();
    void on_Button_acos_clicked();
    void on_Button_atan_clicked();
    void on_Button_ln_clicked();
    void on_Button_log_clicked();
    void on_Button_sqrt_clicked();
    void on_Button_result_clicked();
    void on_Button_plot_clicked();
    void on_Button_x_clicked();
    void on_button_calc_clicked();
    void on_actionSmartCalc_triggered();
    void on_actionCreditCalc_triggered();

private:
    Ui::SCView *ui;
    SCController* controller_;
    CCController* cc_controller_;
    PlotWindow *plot_window_;

    QTableWidget QResList;

    QString OperatorHandler(const QString &a);
    QString SymbolicHandler(const QString &a);
    // void CalculateX();
};

}

#endif // SCVIEW_H

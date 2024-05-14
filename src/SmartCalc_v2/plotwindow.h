#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QWidget>
#include "QCustomPlot/lib/qcustomplot.h"
#include <string>
#include <vector>
#include "sccontroller.h"

namespace Ui {
class PlotWindow;
}
namespace s21 {

class PlotWindow : public QWidget
{
    friend class SCView;
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = nullptr, SCController *c_ptr_ = nullptr);
    SCController *m_controller_;
    ~PlotWindow();

private:
    Ui::PlotWindow *ui;

    QDoubleValidator m_doubleValidator;
    QDoubleValidator step_doubleValidator;

    QPen plot_line;
    plotInputData data;
    QVector<double> x_vector, y_vector;

    void SetupPlotArea();
    void SetupValidators();
    void SetDefaultValues();
    void SetPenProperties();


private slots:
    void on_render_clicked();
};

}
#endif // PLOTWINDOW_H

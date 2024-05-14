#include "plotwindow.h"

#include "ui_plotwindow.h"

s21::PlotWindow::PlotWindow(QWidget *parent, SCController *c_ptr_)
    : QWidget(parent),
      ui(new Ui::PlotWindow),
      m_controller_(c_ptr_),
      m_doubleValidator(-1000000, 1000000, 8, this),
      step_doubleValidator(0.001, 1, 8, this)

{
  ui->setupUi(this);
  SetupPlotArea();
  SetupValidators();
  SetDefaultValues();
  SetPenProperties();

  ui->plot_graph->addGraph();
  ui->plot_graph->graph(0)->setData(x_vector, y_vector);

  ui->plot_graph->setInteraction(QCP::iRangeDrag, true);
  ui->plot_graph->setInteraction(QCP::iRangeZoom, true);
  ui->plot_graph->replot();
}

s21::PlotWindow::~PlotWindow() { delete ui; }

void s21::PlotWindow::SetupPlotArea() {
  QCustomPlot *plot_ = ui->plot_graph;

  plot_->setBackground(QBrush(Qt::black));
  plot_->xAxis->setTickLabelColor(Qt::white);
  plot_->xAxis->setBasePen(QPen(Qt::white));
  plot_->xAxis->setLabelColor(Qt::white);
  plot_->xAxis->setTickPen(QPen(Qt::white));
  plot_->xAxis->setSubTickPen(QPen(Qt::white));
  plot_->yAxis->setTickLabelColor(Qt::white);
  plot_->yAxis->setBasePen(QPen(Qt::white));
  plot_->yAxis->setLabelColor(Qt::white);
  plot_->yAxis->setTickPen(QPen(Qt::white));
  plot_->yAxis->setSubTickPen(QPen(Qt::white));
}

void s21::PlotWindow::SetupValidators() {
  ui->line_xmax->setValidator(&m_doubleValidator);
  ui->line_ymax->setValidator(&m_doubleValidator);
  ui->line_xmin->setValidator(&step_doubleValidator);
  ui->line_x_val->setValidator(&m_doubleValidator);
  ui->line_y_val->setValidator(&m_doubleValidator);
}

void s21::PlotWindow::SetDefaultValues() {
  ui->line_ymax->setText("10");
  ui->line_xmax->setText("10");
  ui->line_xstep->setText("1");
  ui->line_ymin->setText("-10");
  ui->line_xmin->setText("-10");
  ui->line_x_val->setText("0");
}

void s21::PlotWindow::SetPenProperties() {
  plot_line.setColor(QColor(241, 164, 59));
  plot_line.setWidthF(3);
}

void s21::PlotWindow::on_render_clicked() {
  data.x_val = (ui->line_x_val->text().toDouble());
  data.x_min = (ui->line_xmin->text().toDouble());
  data.x_max = (ui->line_xmax->text().toDouble());
  data.y_min = (ui->line_ymin->text().toDouble());
  data.y_max = (ui->line_ymax->text().toDouble());
  data.h_step = ui->line_xstep->text().toDouble();

  ui->plot_graph->clearGraphs();

  plotOutputData res = m_controller_->PassPlotData(data);

  ui->plot_graph->addGraph();
  ui->plot_graph->graph(0)->addData(res.x_vector, res.y_vector);
  ui->plot_graph->graph(0)->setPen(plot_line);
  ui->plot_graph->replot();

  ui->line_y_val->setText(QString::number(res.y_res));
}

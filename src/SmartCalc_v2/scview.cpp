#include "scview.h"

s21::SCView::SCView(QWidget *parent) : QMainWindow(parent), ui(new Ui::SCView) {
  ui->setupUi(this);

  controller_ = new SCController(this);
  cc_controller_ = new CCController(this);
  plot_window_ = new PlotWindow(nullptr, controller_);
  ui->stackedWidget->setCurrentIndex(0);

  SignalsAndSlots();
}

s21::SCView::~SCView() { delete ui; }

void s21::SCView::SignalsAndSlots() {
  connect(ui->Button_num_0, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_1, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_2, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_3, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_4, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_5, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_6, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_7, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_8, SIGNAL(clicked()), this, SLOT(NumPressed()));
  connect(ui->Button_num_9, SIGNAL(clicked()), this, SLOT(NumPressed()));
}

void s21::SCView::NumPressed() {
  ui->Expression->setText(
      controller_->PassNum(((QPushButton *)sender())->text()));
}

void s21::SCView::on_Button_x_clicked() {
  ui->Expression->setText(controller_->PassX());
}

void s21::SCView::on_Button_AC_clicked() {
  ui->Expression->setText(controller_->ClickedAC());
}

void s21::SCView::on_Button_plus_clicked() {
  ui->Expression->setText(OperatorHandler("+"));
}

void s21::SCView::on_Button_minus_clicked() {
  ui->Expression->setText(OperatorHandler("-"));
}

void s21::SCView::on_Button_multi_clicked() {
  ui->Expression->setText(OperatorHandler("*"));
}

void s21::SCView::on_Button_divide_clicked() {
  ui->Expression->setText(OperatorHandler("/"));
}

void s21::SCView::on_Button_mod_clicked() {
  ui->Expression->setText(OperatorHandler("mod"));
}

void s21::SCView::on_Button_exp_clicked() {
  ui->Expression->setText(OperatorHandler("^"));
}

QString s21::SCView::OperatorHandler(const QString &a) {
  return controller_->PassOperator(a);
}

void s21::SCView::on_Button_dot_clicked() {
  ui->Expression->setText(controller_->PassDot());
}

void s21::SCView::on_Button_backspace_clicked() {
  ui->Expression->setText(controller_->ClickedBS());
}

void s21::SCView::on_Button_bracket_open_clicked() {
  ui->Expression->setText(controller_->PassOpenBracket());
}

void s21::SCView::on_Button_bracket_close_clicked() {
  ui->Expression->setText(controller_->PassClosingBracket());
}

QString s21::SCView::SymbolicHandler(const QString &a) {
  return controller_->PassTringonometric(a);
}

void s21::SCView::on_Button_sin_clicked() {
  ui->Expression->setText(SymbolicHandler("sin"));
}

void s21::SCView::on_Button_cos_clicked() {
  ui->Expression->setText(SymbolicHandler("cos"));
}

void s21::SCView::on_Button_tan_clicked() {
  ui->Expression->setText(SymbolicHandler("tan"));
}

void s21::SCView::on_Button_asin_clicked() {
  ui->Expression->setText(SymbolicHandler("asin"));
}

void s21::SCView::on_Button_acos_clicked() {
  ui->Expression->setText(SymbolicHandler("acos"));
}

void s21::SCView::on_Button_atan_clicked() {
  ui->Expression->setText(SymbolicHandler("atan"));
}

void s21::SCView::on_Button_ln_clicked() {
  ui->Expression->setText(SymbolicHandler("ln"));
}

void s21::SCView::on_Button_log_clicked() {
  ui->Expression->setText(SymbolicHandler("log"));
}

void s21::SCView::on_Button_sqrt_clicked() {
  ui->Expression->setText(SymbolicHandler("sqrt"));
}

void s21::SCView::on_Button_result_clicked() {
  ui->Expression->setText(controller_->InitCalculation());
}

void s21::SCView::on_Button_plot_clicked() {
  plot_window_->move(x() + ui->centralwidget->width(), y());
  plot_window_->show();
}

// Credit Calc

void s21::SCView::on_button_calc_clicked() {
  cc_controller_->PassTotalCredit(ui->total_credit->text().toDouble());
  cc_controller_->PassTime(ui->time->text().toDouble());
  cc_controller_->PassTimeMultiplier(ui->time_multiplier->currentIndex());
  cc_controller_->PassPercentage(ui->percent->text().toDouble());
  cc_controller_->PassCalcType(ui->type->currentIndex());
  auto res = cc_controller_->InitCalculation();
  UpdateCreditRes(res);
}

void s21::SCView::UpdateCreditRes(std::list<CreditData> ResList) {
  auto it = ResList.begin();
  ui->overpay->setText(QString::number(it->payment_base, 'f', 2));
  ui->total_pay->setText(QString::number(it->payment_percent, 'f', 2));
  if (ui->type->currentIndex()) {
    it++;
    ui->mounth_pay->setText(QString::number(it->pay_amount, 'f', 2) + " -- " +
                            QString::number(ResList.back().pay_amount, 'f', 2));
  } else {
    ui->mounth_pay->setText(QString::number(it->pay_amount, 'f', 2));
    it++;
  }
  ui->tableWidget->setRowCount(ui->time->text().toInt() *
                               pow(12, ui->time_multiplier->currentIndex()));
  for (int i = 0; it != ResList.end(); it++, i++) {
    ui->tableWidget->insertRow(ui->tableWidget->rowCount() + 1);
    QTableWidgetItem *tbw_1 =
        new QTableWidgetItem(QString::number(it->pay_amount, 'f', 2));
    QTableWidgetItem *tbw_2 =
        new QTableWidgetItem(QString::number(it->payment_base, 'f', 2));
    QTableWidgetItem *tbw_3 =
        new QTableWidgetItem(QString::number(it->payment_percent, 'f', 2));
    QTableWidgetItem *tbw_4 =
        new QTableWidgetItem(QString::number(it->remaining_amount, 'f', 2));
    ui->tableWidget->setItem(i, 0, tbw_1);
    ui->tableWidget->setItem(i, 1, tbw_2);
    ui->tableWidget->setItem(i, 2, tbw_3);
    ui->tableWidget->setItem(i, 3, tbw_4);
  }
}

namespace s21 {
void SCView::on_actionSmartCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(0);
}

void SCView::on_actionCreditCalc_triggered() {
  ui->stackedWidget->setCurrentIndex(1);
}
}  // namespace s21

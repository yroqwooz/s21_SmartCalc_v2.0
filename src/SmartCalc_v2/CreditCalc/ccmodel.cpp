#include "ccmodel.h"

s21::CCModel::CCModel(QObject *parent)
    : QObject{parent},
      total_credit_sum(0),
      time(0),
      time_multiplier(1),
      percent(0),
      type(0) {
  connect(this, SIGNAL(CalculationEnded(std::list<CreditData>)),
          parent->parent(), SLOT(UpdateCreditRes(std::list<CreditData>)));
}

void s21::CCModel::RecieveTotalCredit(float value) { total_credit_sum = value; }

void s21::CCModel::RecieveTime(int value) { time = value; }

void s21::CCModel::RecieveTimeMultiplier(int value) {
  if (value) {
    time_multiplier = 12;
  } else {
    time_multiplier = 1;
  }
}

void s21::CCModel::RecievePercent(float value) { percent = value; }

void s21::CCModel::RecieveCalcType(int value) { type = value; }

std::list<s21::CreditData> s21::CCModel::CalculateCredit() {
  if (!PaymentList.empty()) {
    PaymentList.clear();
  }
  if (type == 0) {
    AnnuitentCase();
  } else if (type == 1) {
    DifferentialCalc();
  }
  // emit CalculationEnded(PaymentList);
  return PaymentList;
}

void s21::CCModel::AnnuitentCase() {
  float mounth_pay = 0.0, debt_total = 0.0;
  mounth_pay =
      total_credit_sum *
      ((0.01 * percent / 12) +
       (((0.01 * percent / 12)) / (pow(1 + (0.01 * percent / 12), time) - 1)));
  float percent_part = 0.0, debt_part = 0.0, loan_left = total_credit_sum,
        percent_total = 0.0;

  for (int i = 0; i < time * time_multiplier; i++) {
    percent_part = loan_left * (0.01 * percent / 12);
    debt_part = mounth_pay - percent_part;
    debt_total += debt_part;
    loan_left -= debt_part;
    percent_total += percent_part;
    PaymentList.push_back(CreditData(percent_part + debt_part, debt_part,
                                     percent_part, loan_left));
  }
  PaymentList.push_front(CreditData(mounth_pay, percent_total,
                                    total_credit_sum + percent_total, 0.0));
}

void s21::CCModel::DifferentialCalc() {
  float loan_part = total_credit_sum / (time * time_multiplier),
        loan_left = total_credit_sum;
  float total_pay = 0.0, debt_total = 0.0, percent_total = 0.0;

  for (int i = 0; i < time * time_multiplier; i++) {
    float percent_curr = loan_left * (0.01 * percent / 12);
    float combined_pay = percent_curr + loan_part;
    total_pay += combined_pay;
    debt_total += loan_part;
    percent_total += percent_curr;
    loan_left -= loan_part;
    PaymentList.push_back(
        CreditData(combined_pay, loan_part, percent_curr, loan_left));
  }
  PaymentList.push_front(
      CreditData(total_pay, (total_pay - total_credit_sum), total_pay, 0.0));
}

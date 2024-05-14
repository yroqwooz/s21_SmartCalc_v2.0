#ifndef CCMODEL_H
#define CCMODEL_H

#include <QDebug>
#include <QObject>

namespace s21 {

class CreditData {
 public:
  float pay_amount;
  float payment_base;
  float payment_percent;
  float remaining_amount;

  CreditData() : CreditData(0.0f, 0.0f, 0.0f, 0.0f) {}
  CreditData(float pay_amount, float payment_base, float payment_percent,
             float remaining_amount)
      : pay_amount(pay_amount),
        payment_base(payment_base),
        payment_percent(payment_percent),
        remaining_amount(remaining_amount) {}
  ~CreditData() = default;
};

class CCModel : public QObject {
  Q_OBJECT
 public:
  explicit CCModel(QObject *parent = nullptr);

  void RecieveTotalCredit(float value);
  void RecieveTime(int value);
  void RecieveTimeMultiplier(int value);
  void RecievePercent(float value);
  void RecieveCalcType(int value);

  std::list<CreditData> CalculateCredit();

 private:
  // std::list<int,float,float> test;
  // test.
  // class

  float total_credit_sum;
  int time;
  int time_multiplier;
  float percent;
  int type;
  std::list<CreditData> PaymentList;

  void AnnuitentCase();
  void DifferentialCalc();
};

}  // namespace s21

#endif  // CCMODEL_H

#ifndef CCCONTROLLER_H
#define CCCONTROLLER_H

#include <QObject>

#include "ccmodel.h"

namespace s21 {

class CCController : public QObject {
  Q_OBJECT
 public:
  explicit CCController(QObject* parent = nullptr);
  void PassTotalCredit(float value);
  void PassTime(int value);
  void PassTimeMultiplier(int value);
  void PassPercentage(float value);
  void PassCalcType(int value);

  std::list<s21::CreditData> InitCalculation();

 private:
  CCModel* cc_model_;
};

}  // namespace s21

#endif  // CCCONTROLLER_H

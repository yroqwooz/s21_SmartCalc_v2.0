#include "cccontroller.h"

s21::CCController::CCController(QObject *parent) : QObject{parent} {
  cc_model_ = new s21::CCModel(this);
}

void s21::CCController::PassTotalCredit(float value) {
  cc_model_->RecieveTotalCredit(value);
}

void s21::CCController::PassTime(int value) { cc_model_->RecieveTime(value); }

void s21::CCController::PassTimeMultiplier(int value) {
  cc_model_->RecieveTimeMultiplier(value);
}

void s21::CCController::PassPercentage(float value) {
  cc_model_->RecievePercent(value);
}

void s21::CCController::PassCalcType(int value) {
  cc_model_->RecieveCalcType(value);
}

std::list<s21::CreditData> s21::CCController::InitCalculation() {
  return (cc_model_->CalculateCredit());
}

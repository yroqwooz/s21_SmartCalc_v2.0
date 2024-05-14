#include "sccontroller.h"

s21::SCController::SCController(QObject *parent) : QObject(parent) {
  model_ = new s21::SCModel(this);
}

QString s21::SCController::PassNum(QString text) {
  return (model_->InsertNum(text));
}

QString s21::SCController::PassX() { return (model_->InsertX()); }

QString s21::SCController::PassOpenBracket() {
  return (model_->InsertOpenBracket());
}

QString s21::SCController::PassClosingBracket() {
  return (model_->InsertClosingBracket());
}

QString s21::SCController::PassOperator(QString text) {
  return (model_->InsertOperator(text));
}

QString s21::SCController::PassTringonometric(QString text) {
  return (model_->InsertTrigonometric(text));
}

QString s21::SCController::PassDot() { return (model_->InsertDot()); }

QString s21::SCController::ClickedAC() { return (model_->ClearExpr()); }

QString s21::SCController::ClickedBS() { return (model_->EraseLast()); }

QString s21::SCController::InitCalculation() {
  return (model_->StartCalculations());
}

s21::plotOutputData s21::SCController::PassPlotData(plotInputData data) {
  return (model_->PlotCalculations(data));
}

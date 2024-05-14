#include "scmodel.h"

s21::SCModel::SCModel(QObject *parent)
    : QObject(parent), expr("0"), expr_std(""), bracket_counter(0), error(0) {}

//  Insertion to expr QString
QString s21::SCModel::InsertNum(QString text) {
  if (expr == "0") {
    expr = "";
  }
  if (!expr.isEmpty()) {
    if (expr.back() != 'x') {
      expr += text;
    }
  } else {
    expr = text;
  }
  return expr;
}

QString s21::SCModel::InsertX() {
  if (expr == "0" || expr == "") {
    expr = "x";
  } else {
    QChar last_symb = expr.back();
    if (!((last_symb >= '0' && last_symb <= '9') || last_symb == ')' ||
          last_symb == 'x' || last_symb == '.')) {
      expr += "x";
    }
  }
  return expr;
}

QString s21::SCModel::InsertOpenBracket() {
  OpenBracketsWrap();
  return expr;
}

QString s21::SCModel::InsertClosingBracket() {
  ClosingBracketsWrap();
  return expr;
}

QString s21::SCModel::InsertOperator(QString text) {
  QChar last_symb = expr.back();
  reg_expr.setPattern("[-+*/^d.]");
  if (expr == "0" || expr == "+" || expr == "-") {
    if ((text == "+" || text == "-") && text != expr) {
      expr = text;
    }
  } else if ((last_symb >= '0' && last_symb <= '9') || last_symb == ')' ||
             last_symb == 'x') {
    expr += text;

  } else if (expr.right(1).contains(reg_expr)) {
    QString::iterator it = expr.end();
    it--;
    it--;
    if (*it == '(') {
      if ((text == "+" || text == "-") && text != expr) {
        ChopWrap(1);
        expr += text;
      }
    } else {
      if (last_symb == 'd') {
        ChopWrap(3);
      } else {
        ChopWrap(1);
      }
      expr += text;
    }
  } else if (expr.right(1) == "(" && (text == "+" || text == '-')) {
    expr += text;
  }
  return expr;
}

QString s21::SCModel::InsertTrigonometric(QString text) {
  if (expr != "0" && expr.back() != '.') {
    PhantomMulti();
    expr += text;
  } else {
    expr = text;
  }
  OpenBracketsWrap();
  return expr;
}

QString s21::SCModel::InsertDot() {
  QString::iterator it = expr.end();
  it--;
  while (*it >= '0' && *it <= '9') {
    it--;
  }
  if (*it != '.' && *it != 'x') {
    expr += ".";
  }
  return expr;
}

QString s21::SCModel::ClearExpr() {
  expr = "0";
  bracket_counter = 0;
  return expr;
}

QString s21::SCModel::EraseLast() {
  if (!expr.isEmpty()) {
    QChar last_symb = expr.back();
    ChopWrap(1);
    if (last_symb == '(') {
      bracket_counter -= 1;
      QChar last_symb = expr.back();
      while (last_symb >= 'a' && last_symb <= 'z' && expr != "0" &&
             last_symb != 'x') {
        expr.chop(1);
        if (expr != "") {
          last_symb = expr.back();
        } else {
          expr = "0";
        }
      }

    } else if (last_symb == ')') {
      bracket_counter += 1;
    }
  }
  return expr;
}

//  Calculation
QString s21::SCModel::StartCalculations() {
  std::string std_expr = expr.toStdString();
  std::pair<double, std::string> res = {0, ""};
  if (!expr.contains("x")) {
    ValidateExpr();
    if (error == 0) {
      res = CalculateExpression(std_expr);
      if (res.second == "" && error == 0) {
        expr = PrepareNum(res.first);
      }
    } else {
      qDebug() << "ERROR = " << error;
    }
  }
  return expr;
}

s21::plotOutputData s21::SCModel::PlotCalculations(plotInputData data) {
  plotOutputData res;

  int N = (data.x_max - data.x_min) / data.h_step + 2;
  if (N > 1000000) {
    N = 1000000;
  }

  if (expr.contains("l")) {
    data.x_min = data.h_step;
  }

  QVector<double> x_vector, y_vector;
  for (int i = 0; i < N; i++) {
    float curr_step = data.x_min + i * data.h_step;
    if (curr_step < 1e-07 && curr_step > -1e-07) {
      curr_step = 0.0;
    }
    QString replaced = expr;
    replaced.replace("x", "(" + QString::number(curr_step) + ")");
    auto dot_res = CalculateExpression(replaced.toStdString());

    if (dot_res.first >= data.y_min && dot_res.first <= data.y_max) {
      x_vector.push_back(data.x_min + (i * data.h_step));
      y_vector.push_back(dot_res.first);
    }
  }
  QString replaced = expr;
  replaced.replace("x", "(" + QString::number(data.x_val) + ")");

  auto y_res = CalculateExpression(replaced.toStdString());

  res.x_vector = x_vector;
  res.y_vector = y_vector;
  res.y_res = y_res.first;

  return res;
}

//  Support Insertion
void s21::SCModel::ChopWrap(int a) {
  if (expr.length() <= a) {
    expr = "0";
  } else {
    expr.chop(a);
  }
}

void s21::SCModel::PhantomMulti() {
  if (!expr.isEmpty()) {
    QChar last_symb = expr.back();
    if ((last_symb <= '9' && last_symb >= '0') || last_symb == ')') {
      expr += "*";
    }
  }
}

void s21::SCModel::OpenBracketsWrap() {
  if (expr == "0") {
    expr = "(";
  } else {
    PhantomMulti();
    expr += "(";
  }
  bracket_counter += 1;
}

void s21::SCModel::ClosingBracketsWrap() {
  if (bracket_counter != 0) {
    QString::iterator it = expr.end();
    it--;
    bool status = false;
    while (*it != '(') {
      it--;
    }
    size_t length = expr.end() - 1 - it;
    QString sub_expr = expr.right(length);
    QRegularExpression reg_expr;
    reg_expr.setPattern(
        "[-+][x0-9+]|[x0-9+]|[x0-9+][*/^%][x0-9+]|[x0-9+]mod[x0-9+]");
    if (sub_expr.contains(reg_expr)) {
      status = true;
    }
    reg_expr.setPattern("[-+*/^d]");
    QString last_symb = expr.right(1);
    if (last_symb.contains(reg_expr)) {
      if (last_symb == "d") {
        ChopWrap(3);
      } else {
        ChopWrap(1);
      }
    }
    if (status) {
      expr += ")";
      bracket_counter -= 1;
    }
  }
}

// CALCULATION BLOCK
//  Main Calculation
void s21::SCModel::ValidateExpr() {
  int curr_error = 0;
  if (bracket_counter != 0) {
    curr_error = 1;
  }
  reg_expr.setPattern("[0-9]");
  if (!expr.contains(reg_expr)) {
    curr_error = 2;
  }
  reg_expr.setPattern(
      "[-+]|[0-9+][*/^%]([0-9.+])|mod|sin|cos|tan|ln|asin|acos|atan|sqrt|log");
  if (!expr.contains(reg_expr)) {
    curr_error = 3;
  }
  if (!expr.isEmpty()) {
    if (expr.back() == '.') {
      curr_error = 4;
    }
  }

  error = curr_error;
}

std::pair<double, std::string> s21::SCModel::CalculateExpression(
    std::string expr) {
  error = 0;
  expr_listed.clear();
  expr_std = expr;
  std::pair<double, int> res = {0.0, 0};
  ExprToList();
  RawListToPostPolish();
  res = CalculateList();
  std::string str = "";
  if (res.second != 1) {
    str = "Error calculation: Invalid expression";
  }
  std::pair<double, std::string> res_pair = {res.first, str};
  return res_pair;
}

void s21::SCModel::ExprToList() {
  auto it = expr_std.begin();
  for (; it != expr_std.end(); it++) {
    CharHandler(it);
  }
}

void s21::SCModel::RawListToPostPolish() {
  std::list<std::pair<std::pair<std::string, double>, int>> res_polish;
  std::list<std::pair<std::pair<std::string, double>, int>> stack;
  for (auto it = expr_listed.begin(); it != expr_listed.end(); it++) {
    std::string str = (*it).first.first;
    if (str == "") {
      res_polish.push_back(
          {{(*it).first.first, (*it).first.second}, (*it).second});
    }
    if (str == "sin" || str == "cos" || str == "tan" || str == "asin" ||
        str == "acos" || str == "atan" || str == "sqrt" || str == "(" ||
        str == "ln" || str == "log") {
      stack.push_back({{(*it).first.first, (*it).first.second}, (*it).second});
    }
    if (str == ")") {
      auto it_stack = stack.end();
      it_stack--;
      while ((*it_stack).first.first != "(") {
        res_polish.push_back(
            {{(*it_stack).first.first, (*it_stack).first.second},
             (*it_stack).second});
        it_stack--;
        stack.pop_back();
      }
      stack.pop_back();
    }
    if (str == "+" || str == "-" || str == "*" || str == "/" || str == "^" ||
        str == "mod") {
      if (!stack.empty()) {
        auto it_stack = stack.end();
        it_stack--;
        while ((*it_stack).second >= (*it).second && !stack.empty() &&
               (*it_stack).first.first != "(") {
          res_polish.push_back(
              {{(*it_stack).first.first, (*it_stack).first.second},
               (*it_stack).second});
          it_stack--;
          stack.pop_back();
        }
      }
      stack.push_back({{(*it).first.first, (*it).first.second}, (*it).second});
    }
  }
  auto it_stack = stack.end();
  it_stack--;
  while (it_stack != (stack.begin())) {
    res_polish.push_back({{(*it_stack).first.first, (*it_stack).first.second},
                          (*it_stack).second});
    it_stack--;
  }
  if (stack.end() != stack.begin()) {
    res_polish.push_back({{(*it_stack).first.first, (*it_stack).first.second},
                          (*it_stack).second});
  }
  stack.clear();
  expr_listed.clear();
  expr_listed.swap(res_polish);
}

std::pair<double, int> s21::SCModel::CalculateList() {
  int calc_status = 1;
  ;
  for (auto it = expr_listed.begin(); it != expr_listed.end();) {
    std::string str = (*it).first.first;
    if (((str == "+" || str == "-") && (*it).second == 6) || str == "sin" ||
        str == "cos" || str == "tan" || str == "asin" || str == "acos" ||
        str == "atan" || str == "sqrt" || str == "ln" || str == "log") {
      UnaryCase(it);
    } else if (str == "+" || str == "-" || str == "*" || str == "/" ||
               str == "^" || str == "mod") {
      BinaryCase(it);
    } else {
      it++;
    }
  }
  if (expr_listed.size() != 1) {
    calc_status = 0;
  }
  return {(*((expr_listed.begin()))).first.second, calc_status};
}

QString s21::SCModel::PrepareNum(double num) {
  QString res;
  std::string str = std::to_string(num);
  if (num != static_cast<int>(num)) {
    res = QString::number(num, 'f', 7);
    reg_expr.setPattern("0+$");
    res.remove(reg_expr);
  } else {
    res = QString::number(num);
  }
  return res;
}

//  Sup Calculation
void s21::SCModel::CharHandler(std::string::iterator &it) {
  auto it_runner = it;
  std::string res;
  if ((*it >= '0' && *it <= '9') || *it == '.') {
    while ((*it_runner >= '0' && *it_runner <= '9') ||
           (*it_runner == '.' || *it_runner == ',')) {
      it_runner++;
    }
    auto it_temp = it_runner;
    it_temp++;
    if (*it_runner == 'e' || (*it_runner == '-' && *it_temp == 'e')) {
      while ((*it_runner >= '0' && *it_runner <= '9') ||
             (*it_runner == '.' || *it_runner == ',')) {
        it_runner++;
      }
    }
    res.append(it, it_runner);
    --it_runner;
  } else if (*it == '+' || *it == '-' || *it == '*' || *it == '/' ||
             *it == '^' || *it == 'm') {
    if (*it == 'm') {
      res.append("mod");
      it_runner += 2;
    } else {
      res.push_back(*it);
    }
  } else if (*it == '(' || *it == ')') {
    res.push_back(*it);
  } else if (*it >= 'a' && *it <= 'z' && *it != 'm') {
    while (*it_runner >= 'a' && *it_runner <= 'z') {
      it_runner++;
    }
    res.append(it, it_runner);
    it_runner--;
  }
  PushToList(res);
  it = it_runner;
}

void s21::SCModel::PushToList(const std::string &elem) {
  char first_symb = elem.begin().operator*();
  if ((first_symb >= '0' && first_symb <= '9') || first_symb == '.' ||
      first_symb == ',') {
    NumPushCase(elem);
  } else {
    OperatorPushCase(elem);
  }
}

void s21::SCModel::NumPushCase(const std::string &elem) {
  std::string::size_type sz;
  // qDebug() << "HI1";
  double res = std::stod(elem, &sz);
  // qDebug() << "HI2";
  expr_listed.push_back({{"", res}, 0});
  // qDebug() << "HI3";
}

void s21::SCModel::OperatorPushCase(const std::string &elem) {
  int priority = 0;
  if (elem == "+" || elem == "-") {
    priority = 1;
    if (expr_listed.end().operator--().operator*().first.first == "(" ||
        expr_listed.empty()) {
      priority = 6;
    }
  } else if (elem == "*" || elem == "/") {
    priority = 2;
  } else if (elem == "^") {
    priority = 3;
  } else if (elem == "sin" || elem == "cos" || elem == "asin" ||
             elem == "acos" || elem == "tan" || elem == "atan" ||
             elem == "ln" || elem == "log") {
    priority = 4;
  } else if (elem == "sqrt" || elem == "mod") {
    priority = 5;
  } else if (elem == "(" || elem == ")") {
    priority = 6;
  }
  if (priority != 0) {
    expr_listed.push_back({{elem, 0.0}, priority});
  }
}

void s21::SCModel::BinaryCase(
    std::list<std::pair<std::pair<std::string, double>, int>>::iterator &it) {
  auto it_second = it;
  it_second--;
  auto it_first = it_second;
  it_first--;
  std::string str = (*it).first.first;
  if (str == "+") {
    (*it_second).first.second =
        (*it_first).first.second + (*it_second).first.second;
  } else if (str == "-") {
    (*it_second).first.second =
        (*it_first).first.second - (*it_second).first.second;
  } else if (str == "*") {
    (*it_second).first.second =
        (*it_first).first.second * (*it_second).first.second;
  } else if (str == "/") {
    (*it_second).first.second =
        (*it_first).first.second / (*it_second).first.second;
  } else if (str == "^") {
    int sign = ((*it_first).first.second < 0 ? 1 : 0);
    double second_whole,
        second_fr = modf((*it_second).first.second, &second_whole);
    (*it_second).first.second =
        pow(fabs((*it_first).first.second), (*it_second).first.second);
    if (sign && ((static_cast<int>(second_whole) % 2 == 0 && second_fr > 0.0) ||
                 (static_cast<int>(second_whole) % 2 == 1))) {
      (*it_second).first.second *= -1;
    }
  } else if (str == "mod") {
    int temp_first = fabs(floor((*it_first).first.second));
    int temp_second = fabs(floor((*it_first).first.second));
    if (fabs((*it_first).first.second) - temp_first < 0.1 ||
        fabs((*it_second).first.second) - temp_second < 0.1) {
      (*it_second).first.second = static_cast<int>((*it_first).first.second) %
                                  static_cast<int>((*it_second).first.second);
    } else {
      error = 1;
    }
  }
  it++;
  it_second++;
  expr_listed.erase(it_first);
  expr_listed.erase(it_second);
}

void s21::SCModel::UnaryCase(
    std::list<std::pair<std::pair<std::string, double>, int>>::iterator &it) {
  auto it_prev = it;
  std::string str = (*it).first.first;
  it_prev--;
  if (str == "-") {
    (*it_prev).first.second = 0 - (*it_prev).first.second;
  } else if (str == "+") {
    (*it_prev).first.second = (*it_prev).first.second;
  } else if (str == "sin") {
    (*it_prev).first.second = sin((*it_prev).first.second);
  } else if (str == "cos") {
    (*it_prev).first.second = cos((*it_prev).first.second);

  } else if (str == "tan") {
    (*it_prev).first.second = tan((*it_prev).first.second);

  } else if (str == "asin") {
    (*it_prev).first.second = asin((*it_prev).first.second);

  } else if (str == "acos") {
    (*it_prev).first.second = acos((*it_prev).first.second);

  } else if (str == "atan") {
    (*it_prev).first.second = atan((*it_prev).first.second);

  } else {
    if ((*it_prev).first.second < 0.0) {
      error = 4;
    } else {
      if (str == "log") {
        (*it_prev).first.second = log10((*it_prev).first.second);
      } else if (str == "ln") {
        (*it_prev).first.second = log((*it_prev).first.second);
      } else if (str == "sqrt") {
        (*it_prev).first.second = sqrt((*it_prev).first.second);
      }
    }
  }
  it++;
  it_prev++;
  expr_listed.erase(it_prev);
}

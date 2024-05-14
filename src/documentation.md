# SmartCalc v2.0

Solo project.

The SmartCalc_v2.0 program is implemented using the MVC template. The ability to plot f(x) graphics is provided; the QCustomPlot library is used.

The program is implemented in two modes:
* SmartCalc - an engineering calculator with trigonometric functions, the ability to plot f(x) and calculate the Y value in expressions of the format y = x.
* CreditCalc - a loan calculator for calculating the total payment at the end of the loan period, as well as a description of monthly payments, the current amount and the percentage of the overpayment.

## Сборка программы:

The project is built using the make command in the src folder, the following goals exist:

* install - installing the application into the build directory located in the same directory.
* uninstall - unistallation.
* dvi - info about project.
* dist - archiving project.
* stylecheck - bringing the code to the clang-format style.
* clean - move to bin all generated test/build files.

## Общий вид:
### SmartCalc_v2.0
![alt text](<screenshots/imgSC01.png>)
![alt text](<screenshots/imgSC02.png>)

### CreditCalc_v2.0
![alt text](<screenshots/imgCC01.png>)


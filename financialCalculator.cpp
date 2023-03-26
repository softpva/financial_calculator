// This class build a financial calculator
// that can calculate the future value of an investment
// or the present value of an investment
// or the number of months to reach a certain amount
// or the interest rate needed to reach a certain amount
// or the monthly payment needed to pay off a loan in a certain number of years
// and the total amount paid back on a loan.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "financialCalculator.hpp"

using namespace std;

financialCalculator::financialCalculator()
{
    presentValue = 0.0;
    futureValue = 0.0;
    interestRate = 0.0;
    numberOfMonths = 0;
    monthlyPayment = 0.0;
    totalMontlhyPaid = 0.0;
}

void financialCalculator::setPresentValue(double p)
{
    presentValue = p;
}
void financialCalculator::setFutureValue(double f)
{
    futureValue = f;
}
void financialCalculator::setInterestRate(double i)
{
    if (i > 1)
        interestRate = i / 100;
    else
        interestRate = i;
}
void financialCalculator::setNumberOfMonths(int n)
{
    numberOfMonths = n;
}

void financialCalculator::setMonthlyPayment(double m)
{
    monthlyPayment = m;
}

double financialCalculator::getPresentValue()
{
    return presentValue;
}

double financialCalculator::getFutureValue()
{
    return futureValue;
}

double financialCalculator::getInterestRate()
{
    return interestRate;
}

int financialCalculator::getNumberOfMonths()
{
    return numberOfMonths;
}

double financialCalculator::getMonthlyPayment()
{
    return monthlyPayment;
}

double financialCalculator::getTotalAmountPaid()
{
    return totalMontlhyPaid;
}

void financialCalculator::calculateFutureValue()
{
    futureValue = presentValue * pow((1 + interestRate), numberOfMonths) + monthlyPayment * (pow((1 + interestRate), numberOfMonths) - 1) / interestRate;
}

void financialCalculator::calculatePresentValue()
{
    presentValue = futureValue / pow((1 + interestRate), numberOfMonths) + monthlyPayment * (1 - pow((1 + interestRate), -numberOfMonths)) / interestRate;
}

void financialCalculator::calculateNumberOfMonths()
{
    double pv = presentValue;
    double fv = futureValue;
    double pmt = monthlyPayment;
    double n = 0;
    double r = interestRate;
    n = log((fv * r + pmt) / (pmt + pv * r)) / log(1 + r);
    numberOfMonths = int(round(n));
}

void financialCalculator::calculateInterestRate()
{
    double pv = presentValue;
    double fv = futureValue;
    double pmt = monthlyPayment;
    double n = numberOfMonths;
    double r = 0;
    double increment = 0.0001;
    double calc;
    if (pmt == 0 && pv > 0 && n > 0 && fv > 0)
    {
        r = pow((fv / pv), (1.0 / n)) - 1;
        interestRate = r;
        return;
    }
    if (fv == 0 && pv > 0 && n > 0 && pmt > 0)
    {
        calc = pmt * n;
        while (calc > pv)
        {
            r += increment;
            calc = pmt * (1 - pow((1 + r), -n)) / r;
        }
        interestRate = r;
        return;
    }
    if (pv == 0 && fv > 0 && n > 0 && pmt > 0)
    {
        calc = pmt * n;
        while (calc < fv)
        {
            r += increment;
            calc = pmt * (pow((1 + r), n) - 1) / r;
        }
        interestRate = r;
        return;
    }
}

void financialCalculator::calculateMonthlyPayment()
{
    if (presentValue > 0 && futureValue == 0)
    {
        monthlyPayment = presentValue * interestRate / (1 - pow((1 + interestRate), -numberOfMonths));
        return;
    }
    if (futureValue > 0 && presentValue == 0)
    {
        monthlyPayment = futureValue * interestRate / (pow((1 + interestRate), numberOfMonths) - 1);
    }
}

double financialCalculator::calculateTotalAmountPaid()
{
    totalMontlhyPaid = monthlyPayment * numberOfMonths;
    return totalMontlhyPaid;
}

void financialCalculator::displayMenu()
{
    cout << "-----------------" << endl;
    cout << "Financial Calculator" << endl;
    cout << "1. Calculate the future value of an investment" << endl;
    cout << "2. Calculate the present value of an investment" << endl;
    cout << "3. Calculate approximately the number of periods to match a determined situation" << endl;
    cout << "4. Calculate the interest rate, known the present value and monthly payments " << endl;
    cout << "5. Calculate the interest rate, known the present value and future value " << endl;
    cout << "6. Calculate the interest rate, known the future value and payments per period" << endl;
    cout << "7. Calculate the monthly payment needed to pay off a loan in a certain number of periods" << endl;
    cout << "8. Calculate the monthly payment needed to obtain a future reserve" << endl;
    cout << "0. Exit" << endl;
    cout << "-----------------" << endl;
}

void financialCalculator::displayResults()
{
    char choice;
    cout << "-----------------" << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Present Value: $" << presentValue << endl;
    cout << "Future Value: $" << futureValue << endl;
    cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    cout << "Number of Months: " << numberOfMonths << endl;
    cout << "Monthly Payment: $" << monthlyPayment << endl;
    cout << "Total Amount Paid Monthly: $" << calculateTotalAmountPaid() << endl;
    cout << "-----------------" << endl;
    cout << "Digit any key to continue: ";
    cin.ignore();
    cin.get(choice);

}

// The main function used to test the class
int main()
{
    financialCalculator calculator;
    int choice;
    double prv;

    do
    {
        calculator.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        while (choice < 0 || choice > 8)
        {
            cout << "Error! Please enter a number between 0 or 8 (0 to exit) : ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            cout << "Calculate the future value of an investment." << endl;
            cout << "-----------------" << endl;
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(prv));
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            calculator.calculateFutureValue();
            calculator.displayResults();
            break;
        case 2:
            cout << "Calculate the present value of an investment" << endl;
            cout << "-----------------" << endl;
            cout << "Enter the future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(prv));
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            calculator.calculatePresentValue();
            calculator.displayResults();
            break;
        case 3:
            cout << "Calculate approximately the number of periods to match a determined situation" << endl;
            cout << "-----------------" << endl;
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            calculator.calculateNumberOfMonths();
            calculator.displayResults();
            break;
        case 4:
            cout << "Calculate the interest rate, known the present value and monthly payments " << endl;
            cout << "-----------------" << endl;
            calculator.setFutureValue(0.0);
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(round(prv)));
            calculator.calculateInterestRate();
            calculator.displayResults();
            break;
        case 5:
            cout << "Calculate the interest rate, known the present value and future value " << endl;
            cout << "-----------------" << endl;
            calculator.setMonthlyPayment(0.0);
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(round(prv)));
            calculator.calculateInterestRate();
            calculator.displayResults();
            break;
        case 6:
            cout << "Calculate the interest rate, known the future value and payments per period" << endl;
            cout << "-----------------" << endl;
            calculator.setPresentValue(0.0);
            cout << "Enter the future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(round(prv)));
            calculator.calculateInterestRate();
            calculator.displayResults();
            break;
        case 7:
            cout << "Calculate the monthly payment needed to pay off a loan in a certain number of periods" << endl;
            cout << "-----------------" << endl;
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(prv));
            calculator.calculateMonthlyPayment();
            calculator.displayResults();
            break;
        case 8:
            cout << "Calculate the monthly payment needed to obtain a future reserve" << endl;
            cout << "-----------------" << endl;
            cout << "Enter the desired future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(prv));
            calculator.calculateMonthlyPayment();
            calculator.displayResults();
            break;
        case 0:
            cout << "-----------------" << endl;
            cout << "Thank you for using the financial calculator." << endl;
            break;
        }
    } while (choice);
    return 0;
}

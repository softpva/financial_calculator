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
// tested ok
void financialCalculator::calculateFutureValue()
{
    futureValue = presentValue * pow((1 + interestRate), numberOfMonths) + monthlyPayment * (pow((1 + interestRate), numberOfMonths) - 1) / interestRate;
}
// tested ok
void financialCalculator::calculatePresentValue()
{
    presentValue = futureValue / pow((1 + interestRate), numberOfMonths) + monthlyPayment * (1 - pow((1 + interestRate), -numberOfMonths)) / interestRate;
}
// tested ok
void financialCalculator::calculateNumberOfMonths()
{
    double PV = presentValue;
    double FV = futureValue;
    double PMT = monthlyPayment;
    double n = 0;
    double r = interestRate;
    n = log((FV * r + PMT) / (PMT + PV * r)) / log(1 + r);
    numberOfMonths = int(round(n));
}

// TODO: test this method
//  calculate the interest rate using the present value and the future value and the number of months and the monthly payment
void financialCalculator::calculateInterestRate()
{
    double PV = presentValue;
    double FV = futureValue;
    double PMT = monthlyPayment;
    double n = numberOfMonths;
    double r = 0;
    // if there is no monthly payment
    // tested ok
    if (PMT == 0)
    {
        r = pow((FV / PV), (1.0 / n)) - 1;
        interestRate = r;
        return;
    }
    //TODO: build the cases above
    // if there is no present value 
    if (PV == 0)
    {

        
        interestRate = r;
        return;
    }
    // if there is no future value
    // doesn't work
    if (FV == 0)
    {
        
        interestRate = r;
        return;
    }
}

// void financialCalculator::calculateInterestRate()
// {
//     interestRate = pow((futureValue / presentValue), (1.0 / numberOfMonths)) - 1;
// }

// calculate the monthly payment
void financialCalculator::calculateMonthlyPayment()
{
    monthlyPayment = presentValue * interestRate / (1 - pow((1 + interestRate), -numberOfMonths));
}

// calculate the total amount paid
void financialCalculator::calculateTotalAmountPaid()
{
    totalMontlhyPaid = monthlyPayment * numberOfMonths;
}

// calculate th number of months to reach the future values
// TODO: check and ajust this function
void financialCalculator::calculateNumberOfPayments()
{
    double PV = presentValue;
    double FV = futureValue;
    double PMT = monthlyPayment;
    double n = 0;
    double r = interestRate / 12.0; // convert annual rate to monthly rate
    n = log((FV * r + PMT) / (PMT + PV * r)) / log(1 + r);
    numberOfMonths = int(n);
}

// display the menu
void financialCalculator::displayMenu()
{
    cout << "Financial Calculator" << endl;
    cout << "1. Calculate the future value of an investment" << endl;
    cout << "2. Calculate the present value of an investment" << endl;
    cout << "3. Calculate the number of months to reach a certain amount" << endl;
    cout << "4. Calculate the interest rate, knowing the present value and monthly payments " << endl;
    cout << "5. Calculate the interest rate, knowing the present value and future value " << endl;
    cout << "6. Calculate the interest rate, knowing the future value and monthly payments " << endl;
    cout << "7. Calculate the monthly payment needed to pay off a loan in a certain number of years" << endl;
    cout << "8. Calculate the total amount paid back on a loan" << endl;
    cout << "0. Exit" << endl;
}

// display the results
void financialCalculator::displayResults()
{
    cout << "-----------------" << endl;
    cout << fixed << showpoint << setprecision(2);
    cout << "Present Value: $" << presentValue << endl;
    cout << "Future Value: $" << futureValue << endl;
    cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    cout << "Number of Months: " << numberOfMonths << endl;
    cout << "Monthly Payment: $" << monthlyPayment << endl;
    cout << "Total Amount Paid Monthly: $" << totalMontlhyPaid << endl;
}

// double FinancialCalculator::calculateInterestRate(double presentValue, double futureValue, double payment, double numberOfPayments) {
//     double n = numberOfPayments;
//     double r = 0.1; // initial guess for the interest rate
//     double epsilon = 0.00001; // tolerance for the solution
//     double numerator, denominator, f, df;

//     // Use Newton's method to solve for the interest rate
//     do {
//         numerator = (futureValue - presentValue * pow(1 + r, n)) / payment;
//         denominator = pow(1 + r, n) - 1;
//         f = numerator / denominator - r;
//         df = (n * presentValue * pow(1 + r, n - 1)) / pow(payment + presentValue * pow(1 + r, n), 2) - 1;
//         r = r - f / df;
//     } while (fabs(f) > epsilon);

//     return r;
// }

// main function to test the class
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
        while (choice < 0 || choice > 6)
        {
            cout << "Error! Please enter a number between 1 or 6 (0 to exit) : ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
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
            cout << "Enter the future value: ";
            cin >> prv;
            calculator.setFutureValue(prv);
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the monthly payment: ";
            cin >> prv;
            calculator.setMonthlyPayment(prv);
            calculator.calculateNumberOfMonths();
            calculator.displayResults();
            break;
        case 4:
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
            cout << "Enter the present value: ";
            cin >> prv;
            calculator.setPresentValue(prv);
            cout << "Enter the interest rate: ";
            cin >> prv;
            calculator.setInterestRate(prv);
            cout << "Enter the number of months: ";
            cin >> prv;
            calculator.setNumberOfMonths(int(prv));
            calculator.calculateTotalAmountPaid();
            calculator.displayResults();
            break;
        case 0:
            cout << "Thank you for using the financial calculator." << endl;
            break;
        }
    } while (choice);
    return 0;
}

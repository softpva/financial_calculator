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
// #include "financialCalculator.h"

using namespace std;

class financialCalculator
{
    private:
        double presentValue;
        double futureValue;
        double interestRate;
        int numberOfMonths;
        double monthlyPayment;
        double totalAmountPaid;
    public:
        financialCalculator(); // constructor
        void setPresentValue(double);
        void setFutureValue(double);
        void setInterestRate(double);
        void setNumberOfMonths(int);
        void setMonthlyPayment(double);
        void setTotalAmountPaid(double);
        double getPresentValue();
        double getFutureValue();
        double getInterestRate();
        int getNumberOfMonths();
        double getMonthlyPayment();
        double getTotalAmountPaid();
        void calculateFutureValue();
        void calculatePresentValue();
        void calculateNumberOfMonths();
        void calculateInterestRate();
        void calculateMonthlyPayment();
        void calculateTotalAmountPaid();
        void displayMenu();
        void displayResults();
};

// constructor
financialCalculator::financialCalculator()
{
    // initialize the variables
    presentValue = 0.0;
    futureValue = 0.0;
    interestRate = 0.0;
    numberOfMonths = 0;
    monthlyPayment = 0.0;
    totalAmountPaid = 0.0;
}

// set the present value
void financialCalculator::setPresentValue(double p)
{
    presentValue = p;
}

// set the future value
void financialCalculator::setFutureValue(double f)
{
    futureValue = f;
}

// set the interest rate
void financialCalculator::setInterestRate(double i)
{
    interestRate = i;
}

// set the number of months
void financialCalculator::setNumberOfMonths(int n)
{
    numberOfMonths = n;
}

// set the monthly payment
void financialCalculator::setMonthlyPayment(double m)
{
    monthlyPayment = m;
}

// set the total amount paid
void financialCalculator::setTotalAmountPaid(double t)
{
    totalAmountPaid = t;
}

// get the present value
double financialCalculator::getPresentValue()
{
    return presentValue;
}

// get the future value
double financialCalculator::getFutureValue()
{
    return futureValue;
}

// get the interest rate
double financialCalculator::getInterestRate()
{
    return interestRate;
}

// get the number of months
int financialCalculator::getNumberOfMonths()
{
    return numberOfMonths;
}

// get the monthly payment
double financialCalculator::getMonthlyPayment()
{
    return monthlyPayment;
}

// get the total amount paid
double financialCalculator::getTotalAmountPaid()
{
    return totalAmountPaid;
}

// calculate the future value
void financialCalculator::calculateFutureValue()
{
    futureValue = presentValue * pow((1 + interestRate), numberOfMonths);
}

// calculate the present value
void financialCalculator::calculatePresentValue()
{
    presentValue = futureValue / pow((1 + interestRate), numberOfMonths);
}

// calculate the number of months
void financialCalculator::calculateNumberOfMonths()
{
    numberOfMonths = log(futureValue / presentValue) / log(1 + interestRate);
}

// calculate the interest rate
void financialCalculator::calculateInterestRate()
{
    interestRate = pow((futureValue / presentValue), (1.0 / numberOfMonths)) - 1;
}

// calculate the monthly payment
void financialCalculator::calculateMonthlyPayment()
{
    monthlyPayment = presentValue * interestRate / (1 - pow((1 + interestRate), -numberOfMonths));
}

// calculate the total amount paid
void financialCalculator::calculateTotalAmountPaid()
{
    totalAmountPaid = monthlyPayment * numberOfMonths;
}

// display the menu
void financialCalculator::displayMenu()
{
    cout << "Financial Calculator" << endl;
    cout << "1. Calculate the future value of an investment" << endl;
    cout << "2. Calculate the present value of an investment" << endl;
    cout << "3. Calculate the number of months to reach a certain amount" << endl;
    cout << "4. Calculate the interest rate needed to reach a certain amount" << endl;
    cout << "5. Calculate the monthly payment needed to pay off a loan in a certain number of years" << endl;
    cout << "6. Calculate the total amount paid back on a loan" << endl;
    cout << "7. Exit" << endl;
}

// display the results
void financialCalculator::displayResults()
{
    cout << fixed << showpoint << setprecision(2);
    cout << "Present Value: $" << presentValue << endl;
    cout << "Future Value: $" << futureValue << endl;
    cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    cout << "Number of Months: " << numberOfMonths << endl;
    cout << "Monthly Payment: $" << monthlyPayment << endl;
    cout << "Total Amount Paid: $" << totalAmountPaid << endl;
}



/* TODO
* 1. Edit main()
* 2. Test the class
* 3. Transfer to a header file
* 4. Test again
* 5. Convert to wasm
*/

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
        while (choice < 1 || choice > 7)
        {
            cout << "Error! Please enter a number between 1 or 7 : ";
            cin >> choice;
        }
        switch (choice)
        {
            case 1:
                cout << "Enter the present value: "; cin >> prv;
                calculator.setPresentValue(prv); prv = 0.0;
                cout << "Enter the interest rate: "; cin >> prv;
                calculator.setInterestRate(prv);
                cout << "Enter the number of months: "; cin >> prv;
                calculator.setNumberOfMonths(int(prv));
                calculator.calculateFutureValue();
                calculator.displayResults();
                break;
            case 2:
                cout << "Enter the future value: "; cin >> prv;
                calculator.setFutureValue(prv);
                cout << "Enter the interest rate: "; cin >> prv;
                calculator.setInterestRate(prv);
                cout << "Enter the number of months: "; cin >> prv;
                calculator.setNumberOfMonths(int(prv));
                calculator.calculatePresentValue();
                calculator.displayResults();
                break;
            // case 3:
            //     cout << "Enter the future value: ";
            //     cin >> calculator.futureValue;
            //     cout << "Enter the present value: ";
            //     cin >> calculator.presentValue;
            //     cout << "Enter the interest rate: ";
            //     cin >> calculator.interestRate;
            //     calculator.calculateNumberOfMonths();
            //     calculator.displayResults();
            //     break;
            // case 4:
            //     cout << "Enter the future value: ";
            //     cin >> calculator.futureValue;
            //     cout << "Enter the present value: ";
            //     cin >> calculator.presentValue;
            //     cout << "Enter the number of months: ";
            //     cin >> calculator.numberOfMonths;
            //     calculator.calculateInterestRate();
            //     calculator.displayResults();
            //     break;
            // case 5:
            //     cout << "Enter the present value: ";
            //     cin >> calculator.presentValue;
            //     cout << "Enter the interest rate: ";
            //     cin >> calculator.interestRate;
            //     cout << "Enter the number of months: ";
            //     cin >> calculator.numberOfMonths;
            //     calculator.calculateMonthlyPayment();
            //     calculator.displayResults();
            //     break;
            // case 6:
            //     cout << "Enter the present value: ";
            //     cin >> calculator.presentValue;
            //     cout << "Enter the interest rate: ";
            //     cin >> calculator.interestRate;
            //     cout << "Enter the number of months: ";
            //     cin >> calculator.numberOfMonths;
            //     calculator.calculateTotalAmountPaid();
            //     calculator.displayResults();
            //     break;
                case 7:
                cout << "Thank you for using the financial calculator." << endl;
                break;                
        }
    } while (choice != 7);
    return 0;
}















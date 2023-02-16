#include <iostream>
#include <cmath>

using namespace std;

class FinanCalc {
    private:
        double PV;
        double r;
        double n;
        double FV;
        double monthly_payment;

    public:
        FinanCalc(double PV, double r, double n) {
            this->PV = PV;
            this->r = r;
            this->n = n;
        }

        void setPV(double PV) {
            this->PV = PV;
        }

        void setR(double r) {
            this->r = r;
        }

        void setN(double n) {
            this->n = n;
        }

        double getFV() {
            FV = PV * pow(1 + r, n);
            return FV;
        }

        double getPV() {
            PV = FV / pow(1 + r, n);
            return PV;
        }

        double getMonthlyPayment() {
            monthly_payment = PV * (r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
            return monthly_payment;
        }
};

int main() {
    FinanCalc fc(0, 0, 0);

    fc.setPV(1000);
    fc.setR(0.05);
    fc.setN(10);

    cout << "The future value (FV) is: $" << fc.getFV() << endl;
    cout << "The present value (PV) is: $" << fc.getPV() << endl;
    cout << "The monthly payment is: $" << fc.getMonthlyPayment() << endl;

    return 0;
}

// Go to sExe/emsdk/
// On terminal: emcc finanCalc.cpp -o finanCalc.html

/*
In this code, we have created a class FinancialCalculator with a constructor to set the initial values of PV, r, and n. The class has three setter methods to change the values of PV, r, and n and three getter methods to get the future value (getFV()), present value (getPV()), and monthly payment (getMonthlyPayment()). The calculations are performed in the getter methods. In the main function, we create an object of the FinancialCalculator class and use the setters to set the values for PV, r, and n. Finally, we use the getters to get the results of the financial calculations.
*/

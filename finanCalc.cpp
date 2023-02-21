#include <iostream>
#include <cmath>

using namespace std;

class FinanCalc
{
private:
    double pv;
    double r;
    double n;
    double fv;
    double mp;

public:
    FinanCalc(double PV, double r, double n, double FV, double mp)
    {
        this->pv = PV;
        this->r = r;
        this->n = n;
        this->fv = 0;
        this->mp = 0;
    }

    FinanCalc()
    {
        this->pv = 0;
        this->r = 0;
        this->n = 0;
        this->fv = 0;
        this->mp = 0;
    }

    void setPV(double PV)
    {
        this->pv = PV;
    }

    void setR(double r)
    {
        this->r = r;
    }

    void setN(double n)
    {
        this->n = n;
    }

    double getFV()
    {
        fv = pv * pow(1 + r, n);
        return fv;
    }

    double getPV()
    {
        pv = fv / pow(1 + r, n);
        return pv;
    }

    double getMonthlyPayment()
    {
        mp = pv * (r * pow(1 + r, n)) / (pow(1 + r, n) - 1);
        return mp;
    }
};

int main()
{
    // FinanCalc fc(0, 0, 0, 0, 0);
    FinanCalc fc;

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

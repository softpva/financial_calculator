/* TODO
* 1. Edit main() OK
* 2. Test the class Ok
* 3. Transfer to a header file OK
* 4. Adjust html file to new logic.
* 4. Check formulas
* 4. Test again
* 5. Convert to wasm
* 6. Link to javascript
* 7. Test
* 8. Make the md files.
*/

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
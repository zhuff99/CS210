#pragma once

#ifndef BANKACCOUNT
#define BANKACCOUNT

// this class was created to make a bank account based off user input
// from the BankAccount_Project2 class

class BankAccount
{
    //sets these variables to private
private:
    double investmentAmount;
    double monthlyDeposit;
    int numYears;
    double annualInterest;

    // sets our constructor to public 
public:
    BankAccount(double investmentAmount, double monthlyDeposit, double annualInterest, int numYears) {
        setInvestmentAmount(investmentAmount);
        setMonthlyDeposit(monthlyDeposit);
        setAnnualInterest(annualInterest);
        setNumYears(numYears);
    }

    BankAccount() {
        investmentAmount = 0;
        monthlyDeposit = 0;
        annualInterest = 0;
        numYears = 0;
    }


    double getInvestmentAmount();
    void setInvestmentAmount(double investmentAmount);

    double getMonthlyDeposit();
    void setMonthlyDeposit(double monthlyDeposit);

    double getAnnualInterest();
    void setAnnualInterest(double annualInterest);

    int getNumYears();
    void setNumYears(int numYears);

};





#endif

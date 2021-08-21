#include "BankAccount.h"


// This header file is used to create our mutators and accesors 

void BankAccount::setInvestmentAmount(double investmentAmount) {
	this->investmentAmount = investmentAmount;
}

void BankAccount::setMonthlyDeposit(double monthlyDeposit) {
	this->monthlyDeposit = monthlyDeposit;
}

void BankAccount::setAnnualInterest(double annualInterest) {
	this->annualInterest = annualInterest;
}

void BankAccount::setNumYears(int numYears) {
	this->numYears = numYears;
}

double BankAccount::getInvestmentAmount() {
	return investmentAmount;
}

double BankAccount::getMonthlyDeposit() {
	return monthlyDeposit;
}

double BankAccount::getAnnualInterest() {
	return annualInterest;
}

int BankAccount::getNumYears() {
	return numYears;
}
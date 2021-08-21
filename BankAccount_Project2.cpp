#include <iostream>
#include <iomanip>
#include <string>


#include "BankAccount.h"

/*
* This program asks for user input and displays a chart based off the information given.
* It was created to imitate a bank account and show users how their interest rates can change
* with the addition or subtraction of monthly deposits or a different starting value.
* 
* @author Zachary Huff
* @CS210 Southern New Hampshire University
*
*/




//static auto myBankAccount = make_unique<BankAccount>(0, 0, 0, 0); //I didn't understand this i tried to get it to work but
                                                                    //was unable to

static double test;

using namespace std;
BankAccount newBankAccount(0, 0, 0, 0); //creates a new bank account that is empty

/*
* This method displays the menu for the user so they know what information
* that they have to input into the program.
* 
* @param none
* 
* 
*/

void printMenu() {

    cout << "\n\n********************************" << endl;
    cout << "********** DATA INPUT **********\n" << endl;

    cout << "Initial Investment Amount: $" << newBankAccount.getInvestmentAmount() << endl;
    cout << "Monthly deposit: $" << newBankAccount.getMonthlyDeposit() << endl;
    cout << "Annual interest: %" << newBankAccount.getAnnualInterest() << endl;
    cout << "Number of years: " << newBankAccount.getNumYears() << endl;
    cout << endl;
    system("pause");

}


/*
* This method is used to get user input and also validate each input making
* sure that the inputs contain only doubles or an integer value.
*
*/
void userInput() {

    bool isTrue;
    double temp;
    
    cout << "********************************" << endl;
    cout << "********** DATA INPUT **********\n" << endl;

    for (int i = 0; i <= 4; i++) {

        switch (i) {        //switch for use of gathering 4 sets of user information
        case 1:
            cout << "Initial Investment Amount: " << endl;
            
            do {
                isTrue = true;
                cin >> temp;
                if (!cin) {             //make sure first input is a number
                    isTrue = false;
                    cin.clear();            //clear error flags
                    cin.ignore(1000, '\n');     //empty input buffer
                }
                else {
                    string dummy;       
                    getline(cin, dummy);            //check rest of stream for any non numerical inputs
                    if (dummy.find_first_not_of(" ") != string::npos) isTrue = false;
                    
                }
                if (!isTrue) cout << "Invalid double; try again\n";
            } while (!isTrue);      //continue to do this until given proper double value

            newBankAccount.setInvestmentAmount(temp);
            temp = 0;
            break;

        case 2:
            cout << "Monthly deposit: " << endl;

            do {
                isTrue = true;
                cin >> temp;
                if (!cin) {
                    isTrue = false;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    string dummy;
                    getline(cin, dummy);
                    if (dummy.find_first_not_of(" ") != string::npos) isTrue = false;

                }
                if (!isTrue) cout << "Invalid double; try again\n";
            } while (!isTrue);

            newBankAccount.setMonthlyDeposit(temp);
            temp = 0;
            break;

        case 3:
            cout << "Annual interest: " << endl;
            do {
                isTrue = true;
                cin >> temp;
                if (!cin) {
                    isTrue = false;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    string dummy;
                    getline(cin, dummy);
                    if (dummy.find_first_not_of(" ") != string::npos) isTrue = false;

                }
                if (!isTrue) cout << "Invalid double; try again\n";
            } while (!isTrue);

            newBankAccount.setAnnualInterest(temp);
            temp = 0;
            break;

        case 4:
            cout << "Number of years: " << endl;
            do {
                isTrue = true;
                cin >> temp;
                if (!cin) {
                    isTrue = false;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    string dummy;
                    getline(cin, dummy);
                    if (dummy.find_first_not_of(" ") != string::npos) isTrue = false;

                }
                if (!isTrue) cout << "Invalid integer; try again\n";
            } while (!isTrue);
            newBankAccount.setNumYears(temp);
            temp = 0;
            break;
        }

    }
    cout << endl;
    system("pause");    //pause and wait for user input
    printMenu();        //prints menu method

}
 
/*
* This method is used to print the users information to the console. I struggled much more
* than I should have trying to get this to work. It ended up taking a majority of the time
* I was able to work on this project. 
*
*/
void printYearlyStaticReport() {

    //variables used
    int months = newBankAccount.getNumYears() * 12;
    double initialInvestment = newBankAccount.getInvestmentAmount();
    double monthlyAddition = newBankAccount.getMonthlyDeposit();
    double annualInterest = newBankAccount.getAnnualInterest() / 100;
    
    //for first loop
    double yearEndBalance = (initialInvestment * annualInterest) + initialInvestment;
    double yearEndInterest = (initialInvestment * annualInterest);
    
    // for second




    cout << "\t\tBalance and Interest Without Additional Monthly Deposits" << endl;
    cout << "====================================================================================" << endl;
    cout << "\tYear" << "\t\t   Year End Balance \t\t Year End Earned Interest" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;

    //loops to calculate user input per month and display them to console

    for (int i = 1; i <= months; i++) {
        
        if (i % 12 == 0) {
            int year = i / 12;
            cout << "\t"  << year << "\t\t\t" << yearEndBalance << "\t\t\t\t" << yearEndInterest << endl;
            yearEndBalance += annualInterest * yearEndBalance;
            yearEndInterest = yearEndBalance*annualInterest;
        }

    }
    cout << endl;
    system("pause");
    
    //for interest with monthly deposits

    cout << "\t\t   Balance and Interest With Additional Monthly Deposits" << endl;
    cout << "====================================================================================" << endl;
    cout << "\tYear" << "\t\t   Year End Balance \t\t Year End Earned Interest" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;


    double yearEndTotal = initialInvestment;

    //prints balance with monthly deposits

    for (int i = 1; i <= months; i++) {

        yearEndTotal += monthlyAddition;
        yearEndTotal += (yearEndTotal * annualInterest)/12;

        if (i % 12 == 0) {
            int year = i / 12;
            yearEndInterest = yearEndTotal * annualInterest;
            cout << "\t" << year << "\t\t\t"  << yearEndTotal << "\t\t\t\t" << yearEndInterest << endl;
        }

    }

    cout << endl;
    system("pause");    //wait for user input

}

/*
* This method is used to check if the user would like to input new numbers.
* If I has more time I would have allowed the user to input and change specific
* values and print them to the screen, but this is a decent workaround.
* 
* 
*/

    void userContinue() {   

        string userString = "";
        bool isTrue = true;
        int i = 0;
        while (isTrue) {
      
           cout << "\nWould you like to change your inputs? [y/n]" << endl;
          
            cin >> userString;

            if (userString == "y" || userString == "Y") {
                userInput();
                printYearlyStaticReport();
                userString = "";
            }
            if (userString == "n" || userString == "N") {
                isTrue = false;
            }
            else if(userString != "") {
                cout << "\nPlease Enter a valid character" << endl;
                userString = "";
            }

        }
    }

    //main method 

int main() {
    userInput();
    printYearlyStaticReport();
    userContinue();
    return 0;
}
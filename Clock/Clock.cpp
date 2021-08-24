#include <iostream>
#include <unistd.h> //used for sleep function
#include <thread>  //So we can still loop while waiting for user input

//testing

#include <curses.h>
#include<stdlib.h>

using namespace std;
static bool isTrue = true;
using namespace literals::chrono_literals;

static string userInput;
static bool endProgram = false;

static int sHours = 0;
static int sMinutes = 0;
static int sSeconds = 0;


void printClocks(int printHour, int printMins, int printSecs) {
    cout << "*****************************";
    cout << "\t*****************************" << endl;

    cout << "*\t\t" << " 12-Hour Clock" << "\t\t*";
    cout << "\t*\t  " << " 24-Hour Clock" << "\t\t*" << endl;


    if (printHour > 12) {
        cout << "*\t\t  " << printHour - 12 << ":";                // Accounting for clock over 12 PM
        cout << printMins << ":";
        cout << printSecs << " P M " << "\t\t*";
    } else if (printHour == 0) {
        cout << "*\t\t  " << printHour + 12 << ":";                // Accounting for clock changing at 12 AM
        cout << printMins << ":";
        cout << printSecs << " A M " << "\t\t*";
    } else if (printHour == 12) {
        cout << "*\t\t  " << printHour << ":";                // accounting for clock changing at 12 PM
        cout << printMins << ":";
        cout << printSecs << " P M " << "\t\t*";
    } else {
        cout << "*\t\t  " << printHour << ":";                // Handles everything else
        cout << printMins << ":";
        cout << printSecs << " A M " << "\t\t*";
    }

    cout << "\t*\t\t  " << printHour << ":";        // military time no need to change 24h clock cycle
    cout << printMins << ":";
    cout << printSecs << "\t\t\t*" << endl;
    cout << "*****************************";
    cout << "\t*****************************" << endl;
}


void calculateTime(int hour = 0, int minute = 0, int second = 0){
    //cout << "Number of seconds elapsed since January 1, 1990:" << ttime << endl;
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);

    //use % 24 for hours, % 60 for seconds and minutes
    int localDay = (local_time->tm_mday);
    int localHour = (local_time->tm_hour);
    int localMinute = (local_time->tm_min);
    int localSecond = (local_time->tm_sec);
    int dayOffSet = 0;

    localHour += hour;
    localMinute += minute;
    localSecond += second;
    string timeDay = "";

    if((localHour / 24) > 0 ){
        dayOffSet = (localHour / 24);
        localHour %= 24;
        localDay += dayOffSet;
    }

    if((localMinute / 60) > 0){
        localMinute %= 60;
        localHour += 1;
    }

    if((localSecond / 60) > 0){
        localSecond %= 60;
        localMinute += 1;
    }

    printClocks(localHour, localMinute, localSecond);           // calls method that prints clocks

}

/*
 * This method is a lazy way to clear the screen placeholder
 * until I can figure out a more efficient way.
 *
 * I found a clrscr() function on the internet but I am unable to use it because
 * when I try to add the library it is not found.
 *
 */

void clearScreen()
{
    //cout << string( 100, '\n' );
    system("cls");
    //if windows
    //system("clear");

}
void timeMenu() {
    string menuOption;
    string newMenuOutput;

    int countHour = 0;
    int countMinute = 0;
    int countSecond = 0;


    while (isTrue) {

        //TODO beautify the menu


        calculateTime(sHours, sMinutes, sSeconds);

        //display menu
        cout << "\t\t\t\t*****************************" << endl;
        cout << "\t\t\t\t* 1--Add One Hour\t\t\t*" << endl;
        cout << "\t\t\t\t* 2--Add One Minute\t\t\t*" << endl;
        cout << "\t\t\t\t* 3--Add One Second\t\t\t*" << endl;
        cout << "\t\t\t\t* 4--Exit Program\t\t\t*" << endl;
        cout << "\t\t\t\t*****************************" << endl;

        this_thread::sleep_for(1s);             //  waiting one second


        if (userInput == "1") {         //for saturday this works!!! copy this format use static variables
            sHours++;
            //calculateTime(countHour, 0, 0);
            userInput = "";
            break;
            //continue;
        } else if (userInput == "2") {
            sMinutes++;
            userInput = "";
            //calculateTime(0, countMinute, 0);
            break;
        } else if (userInput == "3") {
            //sSeconds++;
            userInput = "";
            //calculateTime(0, 0, countSecond);
            break;
        } else if (userInput == "4") {
            cout << "Exiting..." << endl;
            this_thread::sleep_for(1s);
            endProgram = true;
            break;
        }
        clearScreen();
    }
}

int main() {



    while(!endProgram) {
        thread worker(timeMenu);
        cin >> userInput;
        worker.join();
    }


        //calculateTime();
        //militaryTime();

    return 0;
}

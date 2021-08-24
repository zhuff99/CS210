#include <iostream>
#include <unistd.h> //used for sleep function
#include <thread>  //So we can still loop while waiting for user input

//testing
#include <curses.h>
#include<stdlib.h>
/**
 * This program prints out a standard and military clock side-by-side and prints a menu
 * under those two clocks informing the user what actions they are allowed to take.
 * It does this infinitely until a user manually stops the program by entering "4".
 *
 * Program working on Clion IDE with Mac OS as of July 17, 1900.
 * I attempted to run on terminal for testing purposed but was getting errors. It runs without error on IDE though.
 *
 *
 * @author Zachary Huff
 *
 */


using namespace std;
static bool isTrue = true;
using namespace literals::chrono_literals;          //used to add 1s delay in the timeMenu() method
                                                    //also the function giving terminal an error
                                                    //no problems in ide though.

static string userInput = "";            //static string for userInput needed after adding threads
static bool endProgram = false;

static int sHours = 0;          // static ints so we can use them in entire program not just single method
static int sMinutes = 0;
static int sSeconds = 0;


/**
 * This was the last method I created. I noticed I was using way to much duplicated
 * code when I had these functions in the calculateTime() method. I wanted to make it
 * look a bit cleaner so I added this method to help with that. There is still
 * alot of duplicated code here as well but I struggled attempting to clean it
 * up further.
 *
 *
 * @param printHour, printMins, printSecs used to calculateTime after addition by user
 * @return void
 *
 */


void printClocks(int printHour, int printMins, int printSecs) {
    cout << "*****************************";
    cout << "\t*****************************" << endl;

    cout << "*\t\t" << " 12-Hour Clock" << "\t\t*";
    cout << "\t*\t  " << " 24-Hour Clock" << "\t\t*" << endl;


    if (printHour > 12) {
        if(printHour-12 < 10) {
            cout << "*\t\t  0" << printHour - 12 << ":";                // Accounting for clock over 12 PM
        }
        else{
            cout << "*\t\t  " << printHour - 12 << ":";                // Accounting for clock over 12 PM
        }
        if(printMins < 10){
            cout << "0" << printMins << ":";                           // all other if-else are accounting for numbers less than 10
                                                                       // which we need to add the placeholder "0" in front of
        }
        else{
        cout << printMins << ":";
        }
        if(printSecs < 10){
            cout << "0" << printSecs << " P M " << "\t\t*";
        }
        else{
            cout << printSecs << " P M " << "\t\t*";
        }
    }

    else if (printHour == 0) {
        cout << "*\t\t  " << printHour + 12 << ":";                // Accounting for clock changing at 12 AM

        if(printMins < 10){
            cout << "0" << printMins << ":";
        }
        else{
            cout << printMins << ":";
        }
        if(printSecs < 10){
            cout << "0" << printSecs << " A M " << "\t\t*";
        }
        else{
            cout << printSecs << " A M " << "\t\t*";

        }
    }

    else if (printHour == 12) {
        cout << "*\t\t  " << printHour << ":";                // accounting for clock changing at 12 PM

        if(printMins < 10){
            cout << "0" << printMins << ":";
        } else {
            cout << "0" << printMins << ":";
        }
        if(printSecs < 10){
            cout << printSecs << " P M " << "\t\t*";
        }
        else{
            cout << printSecs << " P M " << "\t\t*";

        }
    }

    else if (printHour < 10){
        cout << "*\t\t  0" << printHour << ":";                // if 1-9 am
        if(printMins < 10){
            cout << "0" << printMins << ":";
        }
        else{
            cout << printMins << ":";
        }
        if(printSecs < 10){
            cout << "0" << printSecs << " A M " << "\t\t*";
        }
        else{
            cout << printSecs << " A M " << "\t\t*";

        }
    }

    else{
        cout << "*\t\t  " << printHour << ":";                // Handles everything else
        if(printMins < 10){
            cout << "0" << printMins << ":";
        }
        else{
            cout << printMins << ":";
        }
        if(printSecs < 10){
            cout << "0" << printSecs << " A M " << "\t\t*";
        }
        else{
            cout << printSecs << " A M " << "\t\t*";
        }
    }


    if(printHour < 10){
        cout << "\t*\t\t  0" << printHour << ":";
    }
    else {
        cout << "\t*\t\t  " << printHour << ":";        // military time no need to change 24h clock cycle

    }
    if(printMins < 10){
        cout << "0" << printMins << ":";
    }
    else{
        cout << printMins << ":";
    }
    if(printSecs < 10){
        cout << "0" << printSecs << "\t\t\t*" << endl;
    }
    else{
        cout << printSecs << "\t\t\t*" << endl;
    }
    cout << "*****************************";
    cout << "\t*****************************" << endl;
}

/**
 *
 * This method is used to calculate the time based on the addition of hours, minutes, and seconds
 * based on user input.
 *
 * @param hour, minute, second incremented by the timeMenu() method if user chooses to
 * @return void
 */


void calculateTime(int hour = 0, int minute = 0, int second = 0){
    time_t ttime = time(0);         //Number of seconds elapsed since January 1, 1990
    tm *local_time = localtime(&ttime);         //Structure containing a calendar date and time broken down into its components.

    int localDay = (local_time->tm_mday);       //int variables used to store days, hours, mins, and seconds
    int localHour = (local_time->tm_hour);
    int localMinute = (local_time->tm_min);
    int localSecond = (local_time->tm_sec);
    int dayOffSet = 0;

    localHour += hour;              //functions used to add time according to user input
    localMinute += minute;
    localSecond += second;

    if((localHour / 24) > 0 ){              //if the hours exceed 24 we need to reset hours back to 0 and also
                                            //add a day to the time
        dayOffSet = (localHour / 24);
        localHour %= 24;
        localDay += dayOffSet;
    }

    if((localMinute / 60) > 0){         // if minutes exceed 60 we need to add an hour and reset minutes back to 0
        localMinute %= 60;
        localHour += 1;
    }

    if((localSecond / 60) > 0){         // if seconds exceeds 60 we need to add a minute and reset seconds back to 0
        localSecond %= 60;
        localMinute += 1;
    }

    printClocks(localHour, localMinute, localSecond);           // calls method that prints clocks using new
                                                                // calculated time.

}

/**
 * This method is a lazy way to clear the screen placeholder
 * until I can figure out a more efficient way.
 *
 * I found a clrscr() function on the internet but I am unable to use it because
 * when I try to add the library it is not found.
 *
 * UPDATE: Still could not get this method to properly work I tried many
 * different things. If I could receive some feedback on a proper way to
 * clear the screen on a mac OS I would really appreciate it.
 *
 *
 * @param none
 * @return void
 *
 */

void clearScreen()
{
    cout << string( 100, '\n' );
    //system("cls");
    //if windows
    //system("clear");

}

/**
 *
 * This method is used to print out the menu for the user
 * it also calls the calculate time method for the user to see
 * the actual time, and the time after it is changed by the user.
 *
 * @param none
 * @return void
 *
 */
void timeMenu() {
    string menuOption;
    string newMenuOutput;

    int countHour = 0;              //variables needed
    int countMinute = 0;
    int countSecond = 0;


    while (isTrue) {            //while loop to continue until user says otherwise

        calculateTime(sHours, sMinutes, sSeconds);      //call calculateTime() with the variable changing
                                                        //according to each time user wants to add time
                                                        //they keep incrementing because they are static

        //display menu
        cout << "\t\t\t\t*****************************" << endl;
        cout << "\t\t\t\t* 1--Add One Hour\t\t\t*" << endl;
        cout << "\t\t\t\t* 2--Add One Minute\t\t\t*" << endl;
        cout << "\t\t\t\t* 3--Add One Second\t\t\t*" << endl;
        cout << "\t\t\t\t* 4--Exit Program\t\t\t*" << endl;
        cout << "\t\t\t\t*****************************" << endl;

        this_thread::sleep_for(1s);             //  waiting one second


        if (userInput == "1") {         //if user enters "1" time is incremented 1 Hour
            sHours++;
            userInput = "";             //set userInput back to empty string
            break;
        } else if (userInput == "2") {   //if user enters "2" time is incremented 1 Minute
            sMinutes++;
            userInput = "";
            break;
        } else if (userInput == "3") {  //if user enters "3" 1 second will be added as 1 second has passed
            //sSeconds++;               //no need to increment this because whether user adds a second or not
                                        //one will be added regardless because the method waits one second.
            userInput = "";
            break;
        } else if (userInput == "4") {
            cout << "Exiting..." << endl;
            this_thread::sleep_for(1s);     //waits 1 second then exits the program
            endProgram = true;                  //static boolean is set to true thus ending the thread
            break;
        }
        else if(userInput != ""){                               //catches anything other than 1-4
            cout << "\n\n\t\t**Please, only input [1-4] all other input will be ignored. **" <<endl;
            this_thread::sleep_for(3s);     //After error message waits 3s for user to read it
            userInput = "";
            break;
        }
        clearScreen();
    }
}

/**
     * The least amount of code I could manage to stuff into the main method
     * It is a while loops that continues to call the menu method until user
     * enters the number "4". Then the static boolean endProgram is set to true
     * and the program exits.
     *
     * @param none
     * @return 0
     *
     */

int main() {

    while(!endProgram) {
        thread worker(timeMenu);        //multiple threads needed to run loop continuously while still waiting
                                        //for the user to input.
        cin >> userInput;
        worker.join();                  //The function returns when the thread execution has completed.
    }
    return 0;
}

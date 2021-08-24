#include <iostream>
#include <vector>
#include <fstream>
/**
 *  This program reads in from a file and takes the integer fahrenheit values at the end of each
 *  line, stores them in a vector and converts them to celsius. It then creates a new text file
 *  with the converted temperatures.
 *
 * @author Zachary Huff
 *
 */

using namespace std;
vector <int> myTemps;   // used to hold temperatures of each city
vector <string> myCities; // we will use this to hold the name of each city
int temp;


/**
 *
 * This method opens a txt file and grabs the two integer values at the end of each line.
 * This method only works for values that are in the tens place. If a temperature was int the single
 * digits and/or a hundreds place value more code would be needed. Or it would need to be
 * achieved in a different manner. This works well for the file we are given. Although the runtime
 * may not be great because of the amount of loops used.
 *
 * @param none
 *
 * @return none
 */


void readFile() {
    string cityString;
    string myText;
    ifstream myFile("FahrenheitTemperature.txt");

    while (getline (myFile, myText)) {          //reads file line by line
        for(int i = 0; i < myText.length(); i++){      //takes each line of file and grabs next to values after ' ' this would not work for any other file

            if(myText.at(i) == ' '){        //This takes the two values after the space in each line
                //TODO account for temps less than 10 and greater than 100

                temp = (int)((myText.at(i+1)-48)*(10) + (int)myText.at(i + 2) -48); //-48 converts from ASCII to an integer value we can use.
                                                                                              // time the first number by 10 to get tens place and add second value
                    myTemps.push_back(temp);        //store these values into an array
                }
            }

        for(int i = 0; i < myText.length()-3; i++){     //this loop is used to store the city names into our vector
            cityString.push_back(myText.at(i));
        }
        myCities.push_back(cityString);                 //add string to vector
        cityString = "";                                //reset string to empty
        }
    myFile.close();
}

/**
 * This method is used to create our new file and convert our fahrenheit vector to celsius.
 *
 * @param none
 * @return none
 */

void writeFile(){
    int count = 0;
    double newTemp;
    readFile();     //calls our readFile method which populates the vectors
    ofstream newFile("CelsiusTemperature.txt");     //creates new text file

    //outfile << "my text here!" << std::endl;

    for(int i = 0; i < myTemps.size(); i++){        //loops through and converts temps
        newTemp = myTemps.at(i);
        newTemp = (double)(newTemp - 32) * (0.55);
        myTemps.at(i) = newTemp;
        newTemp = 0;
    }

    for(int i = 0; i < myCities.size(); i ++){      //prints our cities and new temps to .txt file
        newFile << myCities.at(i) << " " << myTemps.at(i) << endl;
        count++;
    }
    newFile.close();        //close the file

    cout << "Check: \"CelsiusTemperature.txt\" for the output of this program.";        //message for use to let them know what the program did
}

/**
 * main method calls writeFile where new file is created
 *
 * @return
 */

int main() {
    writeFile();
    return 0;
}

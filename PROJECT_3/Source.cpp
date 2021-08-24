#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
*
* @author Zachary Huff
* @date 8/15/21
* CS210 Southern New Hampshire University
* 
* This program takes inputs from the user and uses that data in python
* to calculate numbers and loop through a text file.
* 
* 
*/


/*
*	This method loops through user input checking for only number inputs
*	if one of the inputs is not an integer it returns false
*/

bool checkInput(string input) {
	for (int i = 0; i <= input.length(); i++)
		if (isdigit(input[i]) == false) {
			return false;
		}
		else
			return true;
}


/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("python");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"python");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	//variables needed
	string user; 
	int userInput = 0; 

	//while loop used to continue until user inputs 4

	while (userInput == 0) {
		cout << "\n1: List items along with amount total" << endl;
		cout << "2: Number of times a specific item was purchased" << endl;
		cout << "3: Histogram for each item in file" << endl;
		cout << "4: Exit program\n" << endl;


		cin >> user;			// user input


		if (checkInput(user) == false) {			//check for valid input (int)
			cout << "Please enter an integer value" << endl;
		}

		else {
			int i = stoi(user);		//convert user input to a string with stoi()
			userInput = i;

			if (userInput == 1) {	//prints list of all items with corresponding number of times found in file
				CallProcedure("printsomething");
				userInput = 0;
			}
			else if (userInput == 2) {					//User enters product and if it is found displays number of times found
				string product;
				cout << "Enter a product: ";
				cin >> product;
				cout << callIntFunc("PrintMe", product) << endl;
				userInput = 0;
			}
			else if (userInput == 3) {
				string myText;
				int counter;

				CallProcedure("Histogram");
				cout << "Writing file" << endl;

				ifstream newFile("frequency.dat");

				while (getline(newFile, myText)) {				//loop through each line of file
					counter = std::stoi(myText.substr(myText.find(":") + 1));		//convert to int
					myText = myText.substr(0, myText.find(":"));								// Find name of product
					cout << myText << " " << std::string(counter, '+') << endl;			//display name with number of times found indicated by "+"
				}

				userInput = 0;
			}
			//break out of program
			else if (userInput == 4) {
				break;
			}
			//user for invalid entries
			else {
				cout << "Invalid entry, Please use [1-4]";
				userInput = 0;
			}
		}

	}
}
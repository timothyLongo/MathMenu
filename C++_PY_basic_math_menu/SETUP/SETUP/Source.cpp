#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iomanip>


using namespace std;

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
	PyObject* my_module = PyImport_ImportModule("myfirstprogram");
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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
	//printf("Result is %d\n", _PyLong_AsInt(presult));
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
	pName = PyUnicode_FromString((char*)"myfirstprogram");
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
	//printf("Result is %d\n", _PyLong_AsInt(presult));
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


// Menu
// All work done below
void Menu() {
	string userIn;
	bool keepLoopin = true;
	cout << "----< WELCOME! >----" << endl << endl;
	while (keepLoopin) {
		cout << setw(26) << setfill('-') << "" << endl; // menu is displayed
		cout << "|   C++ with Python V1   |" << endl;
		cout << setw(26) << setfill('-') << "" << endl;
		cout << "[1] Display a Multiplication Table" << endl;
		cout << "[2] Double a Value" << endl;
		cout << "[3] Exit" << endl << endl;
		cin >> userIn;
		if (userIn.at(0) == '1') {
			cout << endl << "[ Enter a number for the table: ]" << endl << endl;
			int userNum;
			cin >> userNum;
			while (cin.fail()) { // input validation
				system("CLS"); // clear the screen to prevent clutter of screen
				cin.clear();  // clear the failed bit in the cin stream
				cin.ignore(1000, '\n');  // ignore the next 1000 characters up to the new line so as not to fail the stream again
				cout << endl << "----< Invalid input >----" << endl << endl;
				cout << "     Enter a number:" << endl << endl;
				cin >> userNum;
			}
			system("CLS");
			cout << "-----< Times Table for " << userNum << " >-----" << endl << endl;
			cout << callIntFunc("MultiplicationTable", userNum); // python MultiplicationTable function called
			cout << "'s times table complete!" << endl << endl;  // times table show, then loop continues back to the top menu
		}
		else if (userIn.at(0) == '2') {
			cout << endl << "[ Enter a number to double: ]" << endl << endl;
			int userNum;
			cin >> userNum;
			while (cin.fail()) { // input validation
				system("CLS");
				cin.clear();
				cin.ignore(1000, '\n');
				cout << endl << "----< Invalid input >----" << endl << endl;
				cout << "     Enter a number:" << endl << endl;
				cin >> userNum;
			}
			system("CLS");
			cout << "|---< " << userNum << " DOUBLED is >---|" << endl << endl; // doubled value show, then loop continues back to the top menu
			cout << "-------<(  " << callIntFunc("DoubleValue", userNum) << "  )>-------" << endl << endl; // python DoubleValue function called
		}
		else if (userIn.at(0) == '3') {
			exit(0); // terminates program
		}
		else {
			system("CLS");
			cout << "---< Try again >---" << endl << endl;
		}

	}
}

int main()
{
	Menu();
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);

	return 0;
}
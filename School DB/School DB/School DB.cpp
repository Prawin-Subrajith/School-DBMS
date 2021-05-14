#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <ctype.h>

#include <time.h>    
#include "timeeee.h"



using namespace std;

char ch; int x;

char SQLQueryAdmin[] = "SELECT *From StaffDet";
char SQLQueryViewMARKS_12A[200] = "SELECT *FROM Marks_12A WHERE Test_Name = ";
char SQLQueryViewOrderby[] = "SELECT DISTINCT  Test_Name FROM Marks_12A";
char SQLQueryUpdate[200] = "UPDATE  ";
char SQLQueryADD[100000] = "INSERT INTO ";
char SQLQueryViewFee[] = "SELECT *FROM FeesPay_12A";
char SQLQueryDelete[10000] = "DELETE FROM ";
char SQLQueryLookUp[10000] = "SELECT ";

char pw[64], id[50];int login();

SQLHANDLE SQLEnvHandle = NULL;
SQLHANDLE SQLConnectionHandle = NULL;
SQLHANDLE SQLStatementHandle = NULL;
SQLRETURN retCode = 0;

class credentials {
public:
	string user_id = "";
	char username[50] = "";
	char staff_function[50] = "";
	char user_type[50] = "";
	int pass();
	string retpw() {
		return password;
	}
protected:
	string password = "";
}A;

int credentials::pass() {
	cout << "Enter User ID\t:";
	cin >> user_id;
	cout << "Enter pass\t:";
	while (ch = _getch()) {//character 13 is enter -->ASCII VALUE
		{
			if (ch == 13) {
				/*password.push_back(ch);
				cout << '*';*/
				x = login();
				return x;
			}
			else if (ch == 8) {

				if (password.length() > 0) {
					cout << "\b \b";//remove Mask * on screen;
					password.erase(password.length() - 1); //erase String length
				}
			}
			else {

				cout << "*";

				password += ch; //the input password was assigned to variable passwd.
			}
		}

	}
}


class students {
public:
	char roll_number[10] = " ";
	char subject_number[10] = "";
	char test_name[30] = " ";
	char marks[10] = " ";
	char  Feeamt[1000] = "";
	char date[12] = " ";
	char Pmode[30] = " ";
}B;

class Staff :public credentials, public students {
public:
	char staff_id[50] = "";
	char contact[11] = " ";
	char address[100000000] = " ";
}S, R;




void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
}



int menu() {
	int choice;

	void add_at();void mod_at();void view_t();
	void add_nt();void mod_nt();void view_nt();
	void del_A(int x);
	string(A.staff_function);string(A.user_type);

	time();
	
	if (strncmp(A.staff_function, "Teaching", sizeof(8)) == 0 && strncmp(A.user_type, "Admin_T", sizeof(7)) == 0) {
		system("cls");

		cout.width(40); cout << "THE PSBB MILLENNIUM SCHOOL\n";
		cout.width(90); cout << "Logged In " << A.username << "\n";

		cout.width(20); cout << "1.Add Records\n";
		cout.width(20); cout << "2.Modify Records\n";
		cout.width(20); cout << "3.View Records\n";
		cout.width(20); cout << "4.Exit\n";
		cout.width(20);cout << "Enter choice:\t";
		cin >> choice;

		if (choice == 1) {
			add_at();
			system("pause");
		}

		else if (choice == 2) {
			mod_at();
			system("pause");
		}

		else if (choice == 3) {
			view_t();
			system("pause");
		}

		else if (choice == 4) {
			system("cls");
			cout << "DEVELOPED BY TEJENDRA SARADHI & BARATHI OF 12-A \n PSBB MILLENNIUM SCHOOL,CBE \n COPYRIGHTS 2019-2020\n";

			exit(0);
		}

		else {
			system("pause");
			menu();
		}
	}

	else if (strncmp(A.staff_function, "Teaching", sizeof(8)) == 0 && strncmp(A.user_type, "User", sizeof(4)) == 0) {
		system("cls");

		cout.width(40); cout << "THE PSBB MILLENNIUM SCHOOL\n";
		cout.width(90); cout << "Logged In " << A.username << "\n";

		cout.width(20); cout << "1.View Records\n";
		cout.width(20); cout << "2.Exit\n";
		cout.width(20);cout << "Enter choice:\t";
		cin >> choice;

		if (choice == 1) {
			view_t();
			system("pause");
		}

		else if (choice == 2) {
			system("cls");
			cout << "DEVELOPED BY TEJENDRA SARADHI & BARATHI OF 12-A \n PSBB MILLENNIUM SCHOOL,CBE \n COPYRIGHTS 2019-2020\n";

			exit(0);
		}

		else {
			system("pause");
			menu();
		}

	}

	else if (strncmp(A.staff_function, "Non-Teaching", sizeof(12)) == 0 && strncmp(A.user_type, "Admin_NT", sizeof(8)) == 0) {

		cout.width(40); cout << "THE PSBB MILLENNIUM SCHOOL\n";
		cout.width(90); cout << "Logged In " << A.username << "\n";

		cout.width(20); cout << "1.Add Records\n";
		cout.width(20); cout << "2.Modify Records\n";
		cout.width(20); cout << "3.View Records\n";
		cout.width(20); cout << "4.Exit\n";
		cout.width(20);cout << "Enter choice:\t";
		cin >> choice;

		if (choice == 1) {
			add_nt();
			system("pause");
		}

		else if (choice == 2) {
			mod_nt();
			system("pause");
		}

		else if (choice == 3) {
			view_nt();
			system("pause");
		}

		else if (choice == 4) {
			system("cls");
			cout << "DEVELOPED BY TEJENDRA SARADHI & BARATHI OF 12-A \n PSBB MILLENNIUM SCHOOL,CBE \n COPYRIGHTS 2019-2020\n";

			exit(0);
		}

		else {
			system("pause");
			menu();
		}
	}

	else if (strncmp(A.staff_function, "Non-Teaching", sizeof(12)) == 0 && strncmp(A.user_type, "User", sizeof(4)) == 0) {

		cout.width(40); cout << "THE PSBB MILLENNIUM SCHOOL\n";
		cout.width(90); cout << "Logged In " << A.username << "\n";

		cout.width(20); cout << "1.View Records\n";
		cout.width(20); cout << "2.Exit\n";
		cout.width(20);cout << "Enter choice:\t";
		cin >> choice;

		if (choice == 1) {
			view_nt();
			system("pause");
		}

		else if (choice == 2) {
			system("cls");
			cout << "DEVELOPED BY TEJENDRA SARADHI & BARATHI OF 12-A \n PSBB MILLENNIUM SCHOOL,CBE \n COPYRIGHTS 2019-2020\n";

			exit(0);
		}

		else {
			system("pause");
			menu();
		}

	}


	else if (strncmp(A.staff_function, "Non-Teaching", sizeof(12)) == 0 && strncmp(A.user_type, "SuperAdmin", sizeof(10)) == 0) {

		cout.width(40); cout << "THE PSBB MILLENNIUM SCHOOL\n";
		cout.width(90); cout << "Logged In " << A.username << "\n";

		cout.width(20); cout << "1.Delete Record \n";
		cout.width(20); cout << "2.Exit \n";
		cout.width(20);cout << "Enter choice:\t";
		cin >> choice;

		if (choice == 1) {
			cout << "\n\tCHOOSE THE OPTION:\n";
			cout << "1.Student Record\n";cout << "2.Staff Record\n";cout << "Enter choice:\t";
			cin >> choice;
			del_A(choice);
		}

		else if (choice == 2) {
			system("cls");
			cout << "DEVELOPED BY TEJENDRA SARADHI & BARATHI OF 12-A \n PSBB MILLENNIUM SCHOOL,CBE \n COPYRIGHTS 2019-2020\n";

			exit(0);
		}

		else {
			system("pause");
			menu();
		}
	}


	return -2;
}




int login() {
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryAdmin, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {

			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {

				// Fetches the next rowset of data from the result

				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &A.username, sizeof(A.username), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &A.staff_function, sizeof(A.staff_function), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &A.user_type, sizeof(A.user_type), NULL);
				SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &id, sizeof(id), NULL);
				SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, &pw, sizeof(pw), NULL);
				// Retrieves data for a single column in the result set

				if (A.user_id == id && A.retpw() == pw) {
					return 1; break;
				}

				else if (A.user_id == id && A.retpw() != pw) {
					cout << "\n INCORRECT PASSWORD";
					system("pause");
					return 10;
					break;
				}

			}
			return 0;
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}

int main() {
	system("cls");
	cout.width(50);cout << "Welcome to DB\n";
	if (A.pass() == 1) {

		system("cls");
		int x = menu();
		return x;
	}
	else
		return -1;

}

//                                             >>>>>>>>>>>>>>>>>>>>>> TEACHING <<<<<<<<<<<<<<<<<<<<<<

void view_t() {
	system("cls");
	cout.width(70); cout << "THE PSBB MILLENNIUM SCHOOL\n\n";
	void test_list();
	test_list();
	system("cls");
	cout.width(70); cout << "THE PSBB MILLENNIUM SCHOOL\n\n";
	cout << setw(10) << "Roll_Number";
	cout << setw(20) << "Subject_Number";
	cout << setw(25) << "Table_Name";
	cout << setw(28) << "Marks";
	cout << "\n";
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryViewMARKS_12A, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &B.roll_number, sizeof(B.roll_number), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &B.subject_number, sizeof(B.subject_number), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &B.test_name, sizeof(B.test_name), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &B.marks, sizeof(B.marks), NULL);

				cout << setw(10) << B.roll_number;
				cout << setw(15) << B.subject_number << "\t\t\t";
				cout << B.test_name;
				cout << "\t" << B.marks;
				cout << "\n";
			}

		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}

void test_list() {
	char test_name[50];
	cout << setw(20) << "TEST LIST \n\n";
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryViewOrderby, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &test_name, sizeof(test_name), NULL);

				cout << "\t" << test_name << "\n";
			}
			cout << "Enter Table Name :";
			cin >> test_name;
			strcat_s(SQLQueryViewMARKS_12A, sizeof(SQLQueryViewMARKS_12A), " '");
			strcat_s(SQLQueryViewMARKS_12A, sizeof(SQLQueryViewMARKS_12A), test_name);
			strcat_s(SQLQueryViewMARKS_12A, sizeof(SQLQueryViewMARKS_12A), "'");
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}




void mod_at() {
	char Roll_Number[10];char col_name[50], value[100];
	view_t();void view_mod_at(char number[]);
	cout << "\n Enter the Roll Number Who's Record must be modified :";cin >> Roll_Number;
	view_mod_at(Roll_Number);
	cout << "What do you want to MODIFY?\n";
	cin >> col_name;
	cout << "Enter New Value";
	cin >> value;
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), "Marks_12A SET ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), col_name);
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), " = ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), value);
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), " WHERE Roll_No = ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), Roll_Number);

	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryUpdate, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			// function here
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}

void view_mod_at(char number[10]) {

	system("cls");
	cout << setw(10) << "Roll_Number";
	cout << setw(20) << "Subject_Number";
	cout << setw(25) << "Table_Name";
	cout << setw(28) << "Marks";
	cout << "\n";


	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryViewMARKS_12A, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &B.roll_number, sizeof(B.roll_number), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &B.subject_number, sizeof(B.subject_number), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &B.test_name, sizeof(B.test_name), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &B.marks, sizeof(B.marks), NULL);
				if (strcmp(B.roll_number, number)) {
					cout << setw(10) << B.roll_number;
					cout << setw(15) << B.subject_number << "\t\t\t";
					cout << B.test_name;
					cout << "\t" << B.marks;
					cout << "\n";
				}
			}

		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}



void add_at() {
	students C;
	cout << "ENTER DETAILS \n";
	cout << "Roll Number:";cin >> C.roll_number;
	cout << "Subject Number:";cin >> C.subject_number;
	cout << "Test Name:";cin >> C.test_name;
	cout << "Marks:";cin >> C.marks;

	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), " Marks_12A ");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), " VALUES ( ");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.roll_number);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.subject_number);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.test_name);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.marks);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ")");



	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryADD, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			view_t();
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}


//                                                 >>>>>>>>>>>>>>>>>>>>>> NON - TEACHING <<<<<<<<<<<<<<<<<<<<<<

void view_nt() {

	students C;
	system("cls");
	cout.width(70); cout << "THE PSBB MILLENNIUM SCHOOL\n\n";
	cout.width(60); cout << "FEE TABLE\n\n";
	cout << setw(10) << "Roll_Number";
	cout << setw(20) << "Fee Amount";
	cout << setw(25) << "Date Paid";
	cout << setw(28) << "Payment Mode";
	cout << "\n";
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryViewFee, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, B.roll_number, sizeof(B.roll_number), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &C.Feeamt, sizeof(C.Feeamt), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &C.date, sizeof(C.date), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &C.Pmode, sizeof(C.Pmode), NULL);

				cout << setw(10) << B.roll_number;
				cout << setw(15) << C.Feeamt << "\t\t\t";
				cout << C.date;
				cout << "\t\t" << C.Pmode;
				cout << "\n";
			}

		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects

}





void mod_nt() {

	char Roll_Number[10];char col_name[50], value[100];
	view_nt();void view_mod_nt(char number[]);
	cout << "\n Enter the Roll Number Who's Record must be modified :";cin >> Roll_Number;
	view_mod_nt(Roll_Number);
	cout << "What do you want to MODIFY?\n";
	cin >> col_name;
	cout << "Enter New Value";
	cin >> value;
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), "FeesPay_12A SET ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), col_name);
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), " = ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), value);
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), " WHERE Roll_No = ");
	strcat_s(SQLQueryUpdate, sizeof(SQLQueryUpdate), Roll_Number);
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryUpdate, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			view_nt();
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects

}

void view_mod_nt(char number[]) {
	system("cls");
	cout.width(70); cout << "THE PSBB MILLENNIUM SCHOOL\n\n";
	cout << setw(10) << "Roll_Number";
	cout << setw(20) << "Fee Amount";
	cout << setw(25) << "Date Paid";
	cout << setw(28) << "Payment Mode";
	cout << "\n";


	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryViewFee, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &B.roll_number, sizeof(B.roll_number), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &B.Feeamt, sizeof(B.Feeamt), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &B.date, sizeof(B.date), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &B.Pmode, sizeof(B.Pmode), NULL);
				if (strcmp(B.roll_number, number)) {
					cout << setw(10) << B.roll_number;
					cout << setw(15) << B.Feeamt << "\t\t\t";
					cout << B.date;
					cout << "\t" << B.Pmode;
					cout << "\n";
				}
			}

		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects

}


void add_nt() {
	students C;
	cout << "ENTER DETAILS \n";
	cout << "Roll_Number";cin >> C.roll_number;
	cout << "Fee Amount";cin >> C.Feeamt;
	cout << "Date Paid";cin >> C.date;
	cout << "Payment Mode";cin >> C.Pmode;
	cout << "\n";

	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), " FeesPay_12A ");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), " VALUES ( ");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.roll_number);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.Feeamt);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.date);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ",");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), C.Pmode);
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), "'");
	strcat_s(SQLQueryADD, sizeof(SQLQueryADD), ")");

	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryADD, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			view_nt();
		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}


//                                                 >>>>>>>>>>>>>>>>>>>>>> SUPER ADMIN <<<<<<<<<<<<<<<<<<<<<<



void view_A() {
	students C;
	system("cls");
	cout.width(70); cout << "THE PSBB MILLENNIUM SCHOOL\n\n";
	cout.width(60); cout << "STAFF DETAILS\n";
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryAdmin, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {

				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, R.staff_id, sizeof(R.staff_id), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &R.username, sizeof(R.username), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &R.staff_function, sizeof(R.staff_function), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &R.user_type, sizeof(R.user_type), NULL);
				SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &id, sizeof(id), NULL);
				SQLGetData(SQLStatementHandle, 7, SQL_C_DEFAULT, &R.contact, sizeof(R.contact), NULL);
				SQLGetData(SQLStatementHandle, 8, SQL_C_DEFAULT, &R.address, sizeof(R.address), NULL);

				cout << "\nStaff ID : " << R.staff_id << "\nUser Name : " << R.username << "\nStaff Function : " << R.staff_function << "\nUser Type : " << R.user_type << "\nUser ID : " << id << "\nContact : " << R.contact << "\nAddress : " << R.address << "\n";
				cout << "\n---------------------------------------------------------------------------------------------------------------\n";
				cout << "---------------------------------------------------------------------------------------------------------------\n";
			}


		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects
}




void del_A(int option) {
	int choice;

	if (option == 1) {
		cout << "\n\tCHOOSE THE OPTION:\n";
		cout << "1.Fees Table \n";
		cout << "2.Marks Table\n";
		cout << "Enter choice:\t";
		cin >> choice;
		if (choice == 1) {
			view_nt();
			cout << "\nEnter The Roll_Number to DELETE THE RECORD\n";
			cin >> B.roll_number;
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " FeesPay_12A ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " WHERE Roll_No = ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), B.roll_number);
		}

		else if (choice == 2) {
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "Marks_12A");

			view_t();
			cout << "\nEnter The Roll Number to DELETE THE RECORD\n";
			cin >> B.roll_number;
			cout << "\nEnter The Test Name to DELETE THE RECORD\n";
			cin >> B.test_name;
			cout << "\nEnter The Subject Number to DELETE THE RECORD\n";
			cin >> B.subject_number;

			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " WHERE Roll_NO = ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), B.roll_number);
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " and ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "Test_Name = ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "'");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), B.test_name);
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "'");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " and ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "Subject_No = ");
			strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), B.subject_number);
		}

	}
	else if (option == 2) {
		view_A();
		strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), "StaffDet");
		cout << "\nEnter The Staff ID to DELETE THE RECORD\n";
		cin >> S.staff_id;
		strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), " WHERE Staff_Id = ");
		strcat_s(SQLQueryDelete, sizeof(SQLQueryDelete), S.staff_id);
	}

	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=School DB; UID=; PWD=;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;

		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQueryDelete, SQL_NTS)) {
			// Executes a preparable statement
			showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
			break;
		}
		else {


			if (option == 1 && choice == 1) {
				view_nt();
				cout << "\n\nRECORD DELETED\n\n";
			}

			else if (option == 1 && choice == 2) {
				cout << "\n\nRECORD DELETED\n\n";
			}

			else if (option == 2) {
				view_A();
				cout << "\n\nRECORD DELETED\n\n";
			}

		}
	} while (FALSE);

	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
	// Frees the resources and disconnects

}


#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
using namespace std;


const int Max_Size_CONSTANT = 1024; // constant variable "Max_Size_CONSTANT"
//========================
//Create "Book Structure":
//========================
//Create the "book" array with size = "Max_Size_CONSTANT"
struct Book
{
	string Title;
	int Production_Year;
	int Number_of_Copies;
	string Category;
	string Edition;
}Books[Max_Size_CONSTANT];

//========================
//Create "Account Structure":
//========================
//Create the "Accounts" array with size = "Max_Size_CONSTANT"
struct Account
{
	string ID;
	string Name;
	string Email;
	string Password;
	string Account_Type;
	int Creation_day;
	int Creation_month;
	int Creation_year;
	string Phone[3];
	int Number_of_Phones;
}Accounts[Max_Size_CONSTANT];

int gAccount_Counter = 0; //global variable "gAccount_Counter"
int gBook_Counter = 10; //global variable "gBook_Counter"
int gID = 1000; //global variable "gID"

//==================
// Initialize books:
//==================
//Initialize array "Books" with 10 different books.
void initialize_books() {
	for (int i = 0; i < 10; i++) {
		Books[i].Title = "Book" + to_string(i + 1);
		Books[i].Category = "Category" + to_string(i + 1);
		Books[i].Edition = "Edition" + to_string(i + 1);
		Books[i].Production_Year = 1950 + i;
		Books[i].Number_of_Copies = i + 1;
		//cout << "title : " << book[i].Title << endl;
	}
}
//=======================
// Initialize 4 accounts:
//=======================
//Initialize array "Accounts" with 4 different Accounts.
Account _4Accounts[4];
void initialize_4Accounts() {
	for (int i = 0; i < 4; i++) {
		_4Accounts[i].ID = to_string(i + 1);
		_4Accounts[i].Email = "account" + to_string(i + 1);
		_4Accounts[i].Password = to_string(i + 1);
	}
}
//====================
// Create New Account:
//====================
//create new account and initialize it by the given info (name,email,password,....).
//Return:
//	a) the index in "Accounts" array which store it if succeed:
//		1. initialize this index in "Accounts" array by the given info
//		2. set the time right now (time of creation account)
//	b) -1 if no more spaces in "Accounts" array
int create_account(string Name, string Email, string Password, string Account_Type, string Phone[3], int Number_of_Phones) {
	if (gAccount_Counter == Max_Size_CONSTANT) return -1;
	Accounts[gAccount_Counter].ID = to_string(gID);
	Accounts[gAccount_Counter].Name = Name;
	Accounts[gAccount_Counter].Email = Email;
	Accounts[gAccount_Counter].Password = Password;
	Accounts[gAccount_Counter].Account_Type = Account_Type;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Accounts[gAccount_Counter].Creation_day = ltm->tm_mday;
	Accounts[gAccount_Counter].Creation_month = ltm->tm_mon;
	Accounts[gAccount_Counter].Creation_year = ltm->tm_year;
	Accounts[gAccount_Counter].Number_of_Phones = Number_of_Phones;
	for (int i = 0; i < Number_of_Phones; i++) {
		Accounts[gAccount_Counter].Phone[i] = Phone[i];
	}
	gAccount_Counter++;
	gID++;
	return gAccount_Counter - 1;
}
//==============
// Find Account:
//==============
//Search for the account by the given info(email,password).
//Return:
//	a) the index in "Accounts" array which equals to given info it if found
//	b) -1 if not found this info in "Accounts" array
int find_account(string Email, string Password) {
	for (int i = 0; i < gAccount_Counter; i++) {
		if (Accounts[i].Email == Email && Accounts[i].Password == Password) return i;
	}
	return -1;
}
//==================
// Is Found Account:
//==================
//Search for the account by the given info(email).
//Return:
//	a) true if found this email in "Accounts" array
//	b) false if not found this email in "Accounts" array
bool is_found_account(string Email) {
	for (int i = 0; i < gAccount_Counter; i++) {
		if (Accounts[i].Email == Email) return true;
	}
	return false;
}
//===========
// Find Book:
//===========
//Search for the Book by the given info(Title).
//Return:
//	a) Book Info if found this "Title" in "Books" array
//	b) Book False if not found this "Title" in "Books" array
Book find_book(string Title) {
	for (int i = 0; i < gBook_Counter; i++) {
		if (Books[i].Title == Title) return Books[i];
	}
	Book b;
	b.Production_Year = -100;
	return b;
}
//=================
// Is Staff Member:
//=================
//Search for the type of account by the given info(account).
//Return:
//	a) true if found this "account" is "Staff" type
//	b) false if not found this "account" is "Staff" type
bool is_staff_member(Account account) {
	if (account.Account_Type == "Staff")
		return true;
	else
		return false;
}
//==========
// Buy Book:
//==========
//Search for the Book by the given info(Book) and decrement its copies.
//Return:
//	a) Number_of_Copies if greater than 0
//	b) -1 if Number_of_Copies equal 0
int buy_book(Book Book) {
	for (int i = 0; i < gBook_Counter; i++) {
		if (Books[i].Title == Book.Title) {
			if (Books[i].Number_of_Copies == 0)return -1;
			else return --Books[i].Number_of_Copies;
		}
	}

}
//=================
// Generate Report:
//=================
//Generate Reports that show all information of the new users, 
// whose accounts were created within the last 7 days.
void generate_report() {
	cout << "##################################################################################################################\n";
	cout << "#\tID\t#\tName\t#\tEmail\t\t\t#\tPhone\t\t#\tAccout Type\t#\n";
	cout << "##################################################################################################################\n";
	time_t now = time(0);
	tm* ltm = localtime(&now);
	for (int i = 0; i < gAccount_Counter; i++) {
		if (ltm->tm_year - Accounts[i].Creation_year == 0) {
			if (ltm->tm_mon - Accounts[i].Creation_month == 0) {
				if (ltm->tm_mday - Accounts[i].Creation_day <= 7) {
					cout << "#\t" << Accounts[i].ID << "\t#\t" << Accounts[i].Name << "\t#\t" << Accounts[i].Email;
					for (int j = 0; j < Accounts[i].Number_of_Phones; j++) {
						if (j == 0) {
							cout << "\t\t#\t" << Accounts[i].Phone[j] << "\t#\t" << Accounts[i].Account_Type << "\t\t#\n";
						}
						else
							cout << "#\t\t#\t\t#\t\t\t\t#\t" << Accounts[i].Phone[j] << "\t#\t\t\t#\n";
					}
					cout << "##################################################################################################################\n";
				}
			}
		}

	}
}

int main() {
	system("color F0");
	initialize_books();
	initialize_4Accounts();
	while (true) {
		string account_4;
		string password_4;
		cout << "[start] Enter Email: ";
		cin >> account_4;
		cout << "[start] Enter Password: ";
		cin >> password_4;
		bool found = false;
		for (int i = 0; i < 4; i++) {
			if (_4Accounts[i].Email == account_4 && _4Accounts[i].Password == password_4)
				found = true;
		}
		if (found) {
			while (true)
			{
				cout << "\t\t\tMENU #1\t\t\t\n";
				cout << "[1] Create Account.\n";
				cout << "[2] Login.\n";
				cout << "[3] Exit.\n";
				cout << "[Enter choice (1,2,3)]: ";
				int choice;
				cin >> choice;
				int Account_status = -1;
				Account currentAccount;
				switch (choice)
				{
				case 1:
				{
					//Create new Account Choice
					string name;
					string email;
					string password;
					string type;
					int num_of_phones;
					string phones[3];
					cout << "[create account] Enter Name: ";
					cin >> name;
					cout << "[create account] Enter Email: ";
					cin >> email;
					if (is_found_account(email) != true) {
						cout << "[create account] Enter Password: ";
						cin >> password;
						cout << "[create account] Accout Type (Student, Staff, Guest): ";
						cin >> type;
						if (type != "Student" && type != "Staff" && type != "Guest") {
							cout << "[create account] Something went wrong, try again\n";
						}
						else {
							cout << "[create account] Enter number of phones (1:3): ";
							cin >> num_of_phones;
							if (num_of_phones > 0 && num_of_phones <= 3) {
								for (int i = 0; i < num_of_phones; i++) {
									cout << "[create account] Enter Phone #" << i + 1 << ": ";
									cin >> phones[i];
								}
								int n = create_account(name, email, password, type, phones, num_of_phones);
								Account_status = 1;
								currentAccount = Accounts[n];
								cout << "[create account] Create Account Done\n";
							}
							else {
								cout << "[create account] Something went wrong, try again\n";
							}
						}
					}
					else {
						cout << "[create account] Account already exists !! you should login\n";
					}
					break;
				}
				case 2:
				{
					//Log in choice
					string email;
					string password;
					cout << "[log-in] Enter Email: ";
					cin >> email;
					cout << "[log-in] Enter Password: ";
					cin >> password;
					int account_index = find_account(email, password);
					if (account_index != -1) {
						Account_status = 1;
						currentAccount = Accounts[account_index];
					}
					else {
						cout << "[log-in] Account Not exist !! you should Create Account\n";
					}
					break;
				}
				case 3:return 0;
				default:
					cout << "[menu #1] Invaild Choice\n";
					break;
				}
				while (Account_status == 1) {
					cout << "\t\t\tMENU #2\t\t\t\n";
					cout << "[1] Search book by title.\n";
					cout << "[2] Search book by Production Year.\n";
					cout << "[3] Generate Report.\n";
					cout << "[4] Buy Book.\n";
					cout << "[5] Open another account.\n";
					cout << "[6] Exit.\n";
					cout << "[Enter choice(1, 2, 3, 4, 5, 6)]: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						//search by book title choice
						string title;
						cout << "[search title] Enter Title: ";
						cin >> title;
						Book book = find_book(title);
						if (book.Production_Year != -100) {
							cout << "[search title] Book Title: " << book.Title << endl;
							cout << "[search title] Book Gategory: " << book.Category << endl;
							cout << "[search title] Book Production Year: " << book.Production_Year << endl;
							cout << "[search title] Book Edition: " << book.Edition << endl;
							cout << "[search title] Search Book by title Done\n ";
						}
						else {
							cout << "[search title] Book Not found\n";
						}
						break;
					}
					case 2:
					{
						//search by book production year choice
						int production_year;
						cout << "[search production year] Enter Production Year: ";
						cin >> production_year;
						cout << "################################################################################\n";
						cout << "#\tTitle\t#\tGategory\t#\tYear\t#\tEdition\t\n";
						cout << "################################################################################\n";
						for (int i = 0; i < gBook_Counter; i++) {
							if (Books[i].Production_Year == production_year) {

								cout << "#\t" << Books[i].Title << "\t#\t" << Books[i].Category << "\t#\t" << Books[i].Production_Year << "\t#\t" << Books[i].Edition << "\t\n";
								cout << "################################################################################\n";
							}
						}
						cout << "[search production year] Search Book by production year Done\n ";
						break;
					}
					case 3:
					{
						//generate report for Staff Members only choice
						if (is_staff_member(currentAccount))
							generate_report();
						else
							cout << "[generate report] Sorry YOUR ACCOUNT NOT ALLOWED TO GENERATE REPORT \n ";
						break;
					}
					case 4:
					{
						//buy book for staff Members only choice
						if (is_staff_member(currentAccount)) {
							string title;
							cout << "[buy book] Enter Title: ";
							cin >> title;
							Book book = find_book(title);
							if (book.Production_Year != -100) {
								int found = buy_book(book);
								if (found != -1) {
									cout << "[buy book] Buy Book Done\n";
								}
								else {
									cout << "[buy book] Sorry Not found copies of this book \n";
								}
							}
							else {
								cout << "[buy book] Book Not found\n";
							}
						}
						else {
							cout << "[buy book] Sorry YOU ARE NOT ALLOWED TO BUY ANY BOOK \n";
						}
						break;
						break;
					}
					case 5:
					{
						//switch account choice
						Account_status = 0;
						break;
					}
					case 6:
					{
						//Exit choice
						return 0;
					}
					default:
						cout << "[menu #2] Invaild Choice\n";
						break;
					}

				}
			}
		}
		else {
			cout << "[start] Invalid Master Email !!" << endl;
		}
	}

	return 0;
}
//This is Jose's, Nausheen's, Michelle's, and John's database program

#include <iostream>
#include <fstream>
#include <string>


#include "Mineral.h"
#include "BST/BinarySearchTree.h"
#include "RockDatabase.h"
using namespace std;

#define MAX 1000


class DatabaseMenu{
private:
	RockDatabase rockBase;

public:
	DatabaseMenu(){ rockBase.loadFromFile("mineral.txt");
	mainMenu();
	}
	void mainMenu();
	void caseSearch();
	void caseList();
	void caseAdd();
	void caseDelete();
	void caseUndo();
	void caseWriteFile();
	void caseInfo();
	void caseStatistic();
	~DatabaseMenu(){rockBase.saveToFile("backup.txt");}
};


void display(Mineral *anItem)
{
   cout << "\t" << *anItem << endl;
}



int main()
{
	DatabaseMenu menu;
	cin.get();
	return 0;
}


void DatabaseMenu::mainMenu()
{
	char choice;
	bool quit = false;
	cout << string(50, '-') << endl;
	cout << "Welcome to Jose's, Nausheen's, Michelle's, and John's mineral database!" << endl;



	while (!quit)
	{	// update below
		cout << "Please select a letter." << endl
			<< "A - Add New \n"
			<< "D - Delete \n"
			<< "N - Undo Delete\n"
			<< "H - Statistics\n"
			<< "L - List \n"
			<< "S - Search for \n"
			<< "W - Write data into file\n"
			<< "I - Info about developers\n"
			<< "Q - Quit\n";

		cin >> choice;
		choice = toupper(choice);
		cout << endl;

		switch (choice)
		{
		case 'A': // add
			caseAdd();
			break;
		case 'D': // delete
			caseDelete();
			break;
		case 'S': // search
			caseSearch();
			break;
		case 'L': // list
			caseList();
			break;
		case 'W': // write to file
			caseWriteFile();
			break;
		case 'H': // Statistic
			caseStatistic();
			break;
		case 'N': // undo delete
			caseUndo();
			break;
        case 'I':
            caseInfo();
            break;
		case 'Q': // quit
			quit = true;
			break;
		default:
			cout << "Invalid input.\n";
		}
		cout << endl;
	}

	cout << "Goodbye." << endl;
}

/*************************************************
*************************************************/
void DatabaseMenu::caseInfo(){
    cout << "Michelle Ly: File I/O" << endl;
    cout << "John Dwyer: Screen I/O" << endl;
    cout << "Nausheen Sujela: Hash structure/functions" << endl;
    cout << "Jose Sepulveda: BST, Integration" << endl;

}
void DatabaseMenu::caseAdd()
{
	rockBase.addMineral();
}

void DatabaseMenu::caseUndo()
{
	if (rockBase.undoDelete()){
		cout << "Delete was reverted." << endl;
		return;
	}
	cout << "Nothing to undo." << endl;

}

/*************************************************
*************************************************/
void DatabaseMenu::caseDelete()
{
	string mineralName;
	bool valid = true;
	cout << "What mineral would you like to delete?\n" << endl;
		cin.ignore();
		getline(cin, mineralName);

		if (rockBase.deleteItem(mineralName)){
			cout << "Successfully deleted, " << mineralName << endl;
			return;
		}
		cout << "Sorry, " << mineralName << " not found." << endl;

		return;
}

/*************************************************
*************************************************/
void DatabaseMenu::caseStatistic()
{

    rockBase.showHashStats();
}

/*************************************************
*************************************************/
void DatabaseMenu::caseWriteFile()
{
    string str;
    cout << "Enter a filename to write to: ";
    cin.ignore();
    getline(cin, str);
    rockBase.saveToFile(str);
}



/*************************************************
*************************************************/
void DatabaseMenu::caseSearch()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select a search type from the options below:\n" << endl
			<< "P - Primary Search\n" // change names later
			<< "S - Secondary Search\n"
			<< "Q - Return to previous menu\n" << endl;
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'P':{ // primary key
            string s;
            cout << "Enter a seach query: ";
            cin.ignore();
            getline(cin, s);// secondary key
            if(!rockBase.search(s)){
                cout << "Nothing found.\n";
            }

			break;
			}
		case 'S':{
            string s;
            cout << "Enter a seach query: ";
            cin.ignore();
            getline(cin, s);// secondary key
            if(!rockBase.secondarySearch(s)){
                cout << "Nothing found.\n";
            }
			break;
			}
		case 'Q': // previous
			valid = false;
			break;
		default:
			valid = false;
			cout << endl << "Invalid input. ";
			break;
		}
	}

	return;
}

/*************************************************
*************************************************/
void DatabaseMenu::caseList()
{
	char subChoice;
	bool valid = true;

	while (valid)
	{
		cout << "Please select a display method.\n" << endl;
		cout << "U - display unsorted\n"
			<< "P - display sorted by name\n"
			<< "S - display sorted by crystal system\n"
			<< "I - display indented tree by primary\n"
			<< "R - return to previous menu\n" << endl;
		cin >> subChoice;
		subChoice = toupper(subChoice);
		cout << endl;

		switch (subChoice)
		{
		case 'U':
			cout << "Unsorted List as Followed:" << endl;
			rockBase.printHash();
			break;
		case 'P':
			rockBase.printPrimarySorted();
			break;

		case 'S':
			rockBase.printSecondarySorted();
			break;

        case 'I':
            rockBase.indented();
            break;

		case 'R':
			return;
			break;

		default:
			cout << "Invalid input." << endl;
			break;
		}
	}
}

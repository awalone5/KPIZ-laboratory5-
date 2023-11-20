#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
using namespace std;
struct NOTE {
	string NAME;
	string TEL;
	int BDAY[3];
};

void copyTo(string, string);
int countWords(string);
string loudestWord(string);
void showData(vector<NOTE>);
void findByName(vector<NOTE>);
void findByTel(vector<NOTE>);
void findByDate(vector<NOTE>);
void edit(vector<NOTE>&, string);
void addNewNote(vector<NOTE>&, string);
void deleteNote(vector<NOTE>&, string);

int main()
{
	string input = "C:\\Users\\admin\\source\\input.txt";
	string output = "C:\\Users\\admin\\source\\output.txt";
    ifstream istream;
	ofstream ostream;
	copyTo(input, output);
	cout << "Number of words in input.txt: " << countWords(input) << endl;
	cout << "Word with biggest number of loud letters: " << loudestWord(input) << endl;

	//-------------------------------------------------------------- TASK 2

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string targetFile = "C:\\Users\\admin\\source\\database.txt";
	ifstream inputFile(targetFile);
	if (!inputFile.is_open())
	{
		cerr << "Error opening file!" << endl;
		return 1;
	}

	vector<NOTE> notes;
	NOTE currentNote;
	string line;

	while (getline(inputFile, line))
	{
		currentNote.NAME = line;

		getline(inputFile, line);
		currentNote.TEL = line;

		getline(inputFile, line);
		istringstream dateStream(line);

		char dot;
		dateStream >> currentNote.BDAY[0] >> dot >> currentNote.BDAY[1] >> dot >> currentNote.BDAY[2];

		notes.push_back(currentNote);
	}

	showData(notes);
	bool isExit = false;
	cout << "How to use this program:" << endl << "To see all data enter: 1" << endl << "To find by name enter: 2" << endl << "To find by telephone number enter: 3" << endl << "To find by date of birthd enter: 4" << endl << "To edit note enter: 5" << endl << "To delete note enter: 6" << endl << "To make new note enter: 7" << endl << "If you want to exit enter: 8" << endl;
	do
	{
		int choose;
		string buffer;
		getline(cin, buffer);
		choose = stoi(buffer);

		switch (choose)
		{
		case 1:
			showData(notes);
			break;
		case 2:
			findByName(notes);
			break;
		case 3:
			findByTel(notes);
			break;
		case 4:
			findByDate(notes);
			break;
		case 5:
			edit(notes, targetFile);
			break;
		case 6:
			deleteNote(notes, targetFile);
			break;
		case 7:
			addNewNote(notes, targetFile);
			break;
		case 8:
			isExit = true;
			break;
		default:
			cerr << "Err. Unknown choose" << endl;
			break;
		}
	} while (!isExit);
	inputFile.close();
}

void copyTo(string pathToInput, string pathToOutput) {
	string line;
	ifstream istream;
	ofstream ostream;
	ostream.open(pathToOutput);
	istream.open(pathToInput);
	if (istream.is_open())
	{
		while (getline(istream, line))
		{
			bool lastCharWasSpace = false;
			line.erase(remove_if(line.begin(), line.end(), [&lastCharWasSpace](char c) {
				if (isspace(c))
				{
					if (lastCharWasSpace)
					{
						return true;
					}
					lastCharWasSpace = true;
					return false;
				}
				else
				{
					lastCharWasSpace = false;
					return false;
				}
			}), line.end());
			ostream << line << endl;
		}
		istream.close();
	}
	else
	{
		cout << "there is no such file" << endl;
		istream.close();
	}
}

int countWords(string pathToFile) {
	ifstream istream;
	istream.open(pathToFile);
	string line;
	int result = 0;

	if (istream.is_open()) {

		while (getline(istream, line)) {
			stringstream ss(line);
			string word;

			while (ss >> word) {
				result++;
			}
		}

		istream.close();
		return result;
	}
}

string loudestWord(string pathToFile) {
	ifstream istream;
	istream.open(pathToFile);
	string line;
	int biggest = 0;
	string result;

	if (istream.is_open()) {

		while (getline(istream, line))
		{
			stringstream ss(line);
			string word;

			while (ss >> word)
			{
				vector<char> letters(word.begin(), word.end());
				int countOfLoudLetters = 0;
				for (int i = 0; i < letters.size(); i++)
				{
					if (letters[i] == 'a' || letters[i] == 'A' || letters[i] == 'e' || letters[i] == 'E' || letters[i] == 'i' || letters[i] == 'I' ||
						letters[i] == 'O' || letters[i] == 'o' || letters[i] == 'U' || letters[i] == 'u' || letters[i] == 'Y' || letters[i] == 'y')
					{
						countOfLoudLetters++;
					}
				}
				if (countOfLoudLetters > biggest)
				{
					biggest = countOfLoudLetters;
					result = word;
				}
			}

			istream.close();
			return result;
		}
	}
}

void showData(vector<NOTE> notes) {
	int index = 0;
	for (auto& note : notes)
	{
		cout << index << ": " << note.NAME << " ";
		cout << note.TEL << " ";
		cout << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
		index++;
	}
	cout << endl;
}

void findByName(vector<NOTE> notes) {
	string targetName;
	cout << "Enter the name of the target" << endl;
	getline(cin, targetName);
	bool found = false;
	for (auto& note : notes)
	{
		if (note.NAME == targetName)
		{
			found = true;
			cout << note.NAME << " ";
			cout << note.TEL << " ";
			cout << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
			cout << endl;
		}
	}

	if (!found)
	{
		cout << "there is no such guy as: " << targetName << endl;
	}
}

void findByTel(vector<NOTE> notes) {
	string targetTel;
	cout << "Enter the telephon number of the target" << endl;
	getline(cin, targetTel);
	bool found = false;
	for (auto& note : notes)
	{
		if (note.TEL == targetTel)
		{
			found = true;
			cout << note.NAME << " ";
			cout << note.TEL << " ";
			cout << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
			cout << endl;
		}
	}

	if (!found)
	{
		cout << "there is no such telephone number as: " << targetTel << endl;
	}
}

void findByDate(vector<NOTE> notes) {
	bool found = false;
	cout << "Enter the date of birthd of the target" << endl;
	int targetDate[3];
	cout << "Enter the day: ";
	cin >> targetDate[0];
	cout << "Enter the mounth: ";
	cin >> targetDate[1];
	cout << "Enter the year: ";
	cin >> targetDate[2];
	for (auto& note : notes)
	{
		if ((targetDate[0] == note.BDAY[0]) && (targetDate[1] == note.BDAY[1]) && (targetDate[2] == note.BDAY[2]))
		{
			found = true;
			cout << note.NAME << " ";
			cout << note.TEL << " ";
			cout << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
			cout << endl;
		}
	}
	if (!found)
	{
		cout << "there is no such birth date as: " << targetDate[0] << "." << targetDate[1] << "." << targetDate[2] << endl;
	}
}

void edit(vector<NOTE>& notes, string targetFile) {
	bool found = false;
	cout << "Enter the name of the target: " << endl;
	string targetName;
	getline(cin, targetName);
	for (auto& note : notes)
	{
		if (note.NAME == targetName)
		{
			found = true;

			cout << "Enter new data for the entry with name " << targetName << ":" << endl;

			cout << "Enter new name: ";
			getline(cin, note.NAME);

			cout << "Enter new telephone number: ";
			getline(cin, note.TEL);

			cout << "Edit of birth day" << endl;
			cout << "Enter the day: ";
			cin >> note.BDAY[0];
			cout << "Enter the mounth: ";
			cin >> note.BDAY[1];
			cout << "Enter the year: ";
			cin >> note.BDAY[2];

			cout << "Entry with name " << targetName << " has been updated." << endl;
		}
	}

	if (!found)
	{
		cout << "No entries found for name: " << targetName << endl;
	}

	ofstream outputFile(targetFile);
	if (!outputFile.is_open())
	{
		cout << "Error opening file for writing!" << endl;
	}

	for (auto& note : notes)
	{
		outputFile << note.NAME << endl;
		outputFile << note.TEL << endl;
		outputFile << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
	}

	outputFile.close();
}

void addNewNote(vector<NOTE>& notes, string targetFile) {
	NOTE newEntry;

	cout << "Enter name: ";
	getline(cin, newEntry.NAME);

	cout << "Enter telephone number: ";
	getline(cin, newEntry.TEL);

	cout << "Edit of birth day" << endl;
	cout << "Enter the day: ";
	cin >> newEntry.BDAY[0];
	cout << "Enter the mounth: ";
	cin >> newEntry.BDAY[1];
	cout << "Enter the year: ";
	cin >> newEntry.BDAY[2];

	notes.push_back(newEntry);
	cout << "New entry added successfully." << endl;

	ofstream outputFile(targetFile);
	if (!outputFile.is_open()) {
		cerr << "Error opening file for writing!" << endl;
	}

	for (auto& note : notes) {
		outputFile << note.NAME << endl;
		outputFile << note.TEL << endl;
		outputFile << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
	}

	outputFile.close();
}

void deleteNote(vector<NOTE>& notes, string targetFile) {
	string targetName;
	cout << "Enter the name of the target" << endl;
	getline(cin, targetName);
	auto it = remove_if(notes.begin(), notes.end(), [targetName](NOTE& note) {
		return note.NAME == targetName;
		});

	if (it != notes.end()) {
		notes.erase(it, notes.end());
		cout << "Entry with name " << targetName << " has been deleted." << endl;
	}
	else {
		cout << "No entries found for name: " << targetName << endl;
	}

	ofstream outputFile(targetFile);
	if (!outputFile.is_open()) {
		cerr << "Error opening file for writing!" << endl;
	}

	for (auto& note : notes) {
		outputFile << note.NAME << endl;
		outputFile << note.TEL << endl;
		outputFile << note.BDAY[0] << "." << note.BDAY[1] << "." << note.BDAY[2] << endl;
	}

	outputFile.close();
}
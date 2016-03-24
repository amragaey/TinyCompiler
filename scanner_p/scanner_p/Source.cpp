#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void getToken(string);
bool isDigit(char);
bool isLetter(char);
bool isSpace(char);
bool isSymbol(char);

enum DFAstates { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
DFAstates state = START; //set START to be intial state

string RES_WORDS[] = { "if","then","else","end","repeat","until","read","write" };

int main() {
	//reading sample tiny code from file
	ifstream file;
	string line, code;
	file.open("tiny_sample_code.txt");
	while (!file.eof()) {
		getline(file, line);
		code += line;
	}

	//writing scanner output to file
	freopen("parser_input.txt", "w", stdout);
	getToken(code); // this is written to redir.txt
	fclose(stdout);
	system("pause");

	return 0;
}


void getToken(string l)
{
	string mytoken;
	bool res_flag = 0;
	int i = 0;
	while (state != DONE) {
		switch (state) {
		case START:
			if (isSpace(l[i])) {
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else if (isDigit(l[i])) {
				state = INNUM;
			}
			else if (isLetter(l[i])) {
				state = INID;
			}
			else if (l[i] == ':') {
				state = INASSIGN;
			}
			else if (l[i] == '{') {
				i++;
				state = INCOMMENT;
			}
			else if (isSymbol(l[i])) {
				switch (l[i]) {
				case ';': cout << l[i] << endl; break;
				default: cout << l[i] << " "; break;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			else state = DONE;
			break;

		case INCOMMENT:
			if (state == INCOMMENT) {
				while (l[i] != '}') {
					i++;
				}
				i++;
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;

		case INNUM:
			while (isDigit(l[i])) {
				mytoken += l[i];
				i++;
			}
			cout << "number" << " ";
			mytoken = "";
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INID:
			while (isLetter(l[i])) {
				mytoken += l[i];
				i++;
			}
			for (int i = 0; i < 8; i++)
			{
				if (RES_WORDS[i] == mytoken) res_flag = 1;
			}
			if (res_flag) cout << endl << mytoken << " ";
			else cout << "identifier" << " ";
			mytoken = "";
			res_flag = 0;
			if (i == l.length()) state = DONE;
			else state = START;
			break;

		case INASSIGN:
			if (l[i] == ':') {
				i += 2;
				cout << ":=" << " ";
				state = START;
			}
			else {
				if (i == l.length()) state = DONE;
				else state = START;
			}
			break;
		case DONE:
			break;
		}
	}
}

bool isDigit(char d) { return (d >= '0' && d <= '9'); }

bool isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }

bool isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }

bool isSymbol(char c) { return (c == '+' || '-' || '*' || '/' || '=' || '<' || '(' || ')' || ';'); }
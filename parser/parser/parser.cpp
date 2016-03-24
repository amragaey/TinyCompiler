#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream file;
string token;

enum stmtTypes {IF, REPEAT, ASSIGN, READ, WRITE, ERROR};

stmtTypes getStmtType(string s)
{
	if (s == "if") return IF;
	if (s == "identifier") return ASSIGN;
	if (s == "read") return READ;
	if (s == "write") return WRITE;
	if (s == "repeat") return REPEAT;
	else return ERROR;
}

void match(string s) 
{
	if (s == token) 
	{ 
		file >> token;
	}
	else 
	{
		cout << endl << "-- Program not found" << endl;
		exit(1);
	}
}

void program();
void stmt_seq();
void stmt();
void if_stmt();
void repeat_stmt();
void assign_stmt();
void read_stmt();
void write_stmt();
void exp();
void comparison_op();
void simple_exp();
void addop();
void term();
void mulop();
void factor();


int main() 
{
	file.open("parser_input.txt");
	file >> token;
	program();
	file.close();
	system("pause");
	return 0;
}

// program -> stmt-seq
void program()
{
	stmt_seq();
	cout << endl << "-- Program found" << endl;
}

// stmt-seq -> stmt {; stmt}
void stmt_seq()
{
	stmt();
	while (token == ";") 
	{
		match(";");
		stmt();
	}
}

// stmt -> if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
void stmt() 
{
	switch (getStmtType(token))
	{
	case IF:
		if_stmt(); break;
	case REPEAT:
		repeat_stmt(); break;
	case ASSIGN:
		assign_stmt(); break;
	case READ: 
		read_stmt(); break;
	case WRITE:
		write_stmt(); break;
	case ERROR:
		cout << "no stmt found"; exit(1); break;
	default:
		break;
	}
}

// if-stmt -> if exp then stmt-seq [else stmt-seq] end
void if_stmt() 
{
	match("if");
	exp();
	match("then");
	stmt_seq();
	if (token == "else") stmt_seq();
	match("end");
	cout << "- if statement found" << endl;
}

// repeat-stmt -> repeat stmt-seq until exp
void repeat_stmt() 
{
	match("repeat");
	stmt_seq();
	match("until");
	exp();
	cout << "- repeat found" << endl;
}

// assign-stmt -> identifier := exp
void assign_stmt() 
{
	match("identifier");
	match(":=");
	exp();
	cout << "- assignment found" << endl;
}

// read-stmt -> read identifier
void read_stmt() 
{
	match("read");
	match("identifier");
	cout << "- read found" << endl;
}

// write-stmt -> write exp
void write_stmt() 
{
	match("write");
	exp();
	cout << "- write found" << endl;
}

// exp -> simple-exp [comparison-op simple-exp]
void exp() 
{
	simple_exp();
	if (token == "<" || token == "=") 
	{
		comparison_op();
		simple_exp();
	}
}

// comparison-op -> < | =
void comparison_op() 
{
	if (token == "<") match("<");
	if (token == "=") match("=");
}

// simple-exp -> term { addop term }
void simple_exp() 
{
	term();
	while (token == "+" || token == "-") {
		addop();
		term();
	}
}

// addop -> + | -
void addop() 
{
	if (token == "+") match("+");
	if (token == "-") match("-");
}

// term -> factor { mulop factor }
void term() 
{
	factor();
	while (token == "*" || token == "/") 
	{
		mulop();
		factor();
	}
}

// mulop -> * | /
void mulop() 
{
	if (token == "*") match("*");
	if (token == "/") match("/");
}

// factor -> (exp) | number | identifier
void factor() 
{
	if (token == "(") 
	{ 
		match("(");
		exp();
		match(")");
	}
	else if (token == "number") 
	{
		match("number");
	}
	else if (token == "identifier") 
	{
		match("identifier");
	}
}
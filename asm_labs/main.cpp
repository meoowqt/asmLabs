#include <iostream>
#include "main.h"
using namespace std;

int main() {
	setlocale(0, "");
	int lab;
	cout << "Ќапишите номер лабораторной, которую вы хотите запустить:\n";
	cin >> lab;
	switch (lab)
	{
	case 2: lab_2(); break;
	case 3: lab_3(); break;
	case 4: lab_4(); break;
	case 5: lab_5(); break;
	case 6: lab_6(); break;
	default:
		cout << "ƒанной лабораторной не существует :(\n";
		break;
	}
}
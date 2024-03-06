#include<iostream>
using namespace std;

double check(double a, double b) {
	if (a > b) return 12 * b / a - 2 * b;
	else if (a < b) return (6 * a - 103) / b;
	else return -57;
}

int lab_6()
{
	setlocale(0, "");
	double a, b, result;
	cout << "12 * b/a - 2b, a > b;\n-57, a = b;\n(6a - 103)/b, a < b;\n";
	cout << "Введите a: ";
	cin >> a;
	cout << "Введите b: ";
	cin >> b;
	int status;
	int state = -1;
	const double b12 = 12, b2 = 2, a6 = 6, c103 = 103, am57 = -57;

	__asm
	{
		finit // инициализация сопроцессора

		fld b // st(0) = b
		fld a // st(0) = a , st(1) = b

		fcom st(1) // сравниваем a и b

		fstsw status // сохраняем регистр флагов сопроцессора
		mov ah, byte ptr[status + 1] // сохраняем второй байт
		sahf // записываем содержимое ah в регистр FLAGS

		jp errorNotComp // если несравнимы
		ja aBigger// переход если a больше
		jb bBigger// переход если b больше

		fld qword ptr[am57]

		fxam// анализируем содержимое st(0)
		fnstsw ax// сохраняем регистр состояния сопроцессора swr в ax
		sahf// записываем ah в регистр флагов процессора eflags

		jnz c3_0; если с3 = 0
		jz c3_1; если с3 = 1

		aBigger :
		ftst // сравниваем st(0) и 0
			fnstsw ax// сохраняем регистр состояния сопроцессора swr в ax
			sahf// записываем ah в регистр флагов процессора eflags
			jz zero
			fdiv //st(0)=b/a

			fmul qword ptr[b12] // st(0) = 12 * b/a
			fld qword ptr[b]// st(0) = b, st(0) = 12 * b/a
			fmul qword ptr[b2]// st(0) = 2 * b, st(1) = 12 * b/a
			fsub//st(0) = 12 * b/a - 2 * b

			fstp qword ptr[result]
			fld qword ptr[result]

			fxam// анализируем содержимое st(0)
			fnstsw ax// сохраняем регистр состояния сопроцессора swr в ax
			sahf// записываем ah в регистр флагов процессора eflags

			jnz c3_0// если с3 = 0
			jz c3_1// если с3 = 1

			bBigger :
		//(6 * a - 103) / b
		fldz //st(0) = 0, st(1) = a, st(2) = b
			fcomp st(2) //вещественное сравнение b с 0 с выталкиванием
			// st(0) = a, st(1) = b
			fnstsw ax// сохраняем регистр состояния сопроцессора swr в ax
			sahf// записываем ah в регистр флагов процессора eflags
			jz zero;
		fmul qword ptr[a6] // st(0) = a * 6, st(1) = b
			fld c103 // st(0) = 103, st(1) = 6 * a, st(2) = b
			fsub //st(0) = 6 * a - 103, st(1) = b
			fdiv st, st(1)// st(0) = (6 * a - 103) / b

			fstp qword ptr[result]
			fld qword ptr[result]

			fxam// анализируем содержимое st(0)
			fnstsw ax// в ax содержимое swr
			sahf// содержимое ah в регистр флагов

			jnz c3_0// если с3 = 0
			jz c3_1// если с3 = 1

			zero :
		mov state, 8
			jmp endProg

			errorNotComp :
		mov state, 0
			jmp endProg

			c3_0 :
		jnp c2_0// если c2 = 0
			jnc c0_0// если c0 = 0
			mov state, 4
			jmp endProg

			c0_0 :
		mov state, 3
			fstp result
			jmp endProg

			c2_0 :
		jnc c0__0// если c0 = 0
			mov state, 2
			jmp endProg

			c0__0 :
		mov state, 1
			jmp endProg

			c3_1 :
		jnp c2__0// если c2 = 0
			mov state, 7
			jmp endProg

			c2__0 :
		jnc c0___0// если c0 = 0
			mov state, 6
			jmp endProg

			c0___0 :
		mov state, 5
			fstp result
			jmp endProg

			endProg :
	}
	if (state == 0) cout << "Error: не сравнимо";
	else if (state == 1) cout << "Неподдерживаемый формат";
	else if (state == 2) cout << "Нечисло";
	else if (state == 3) cout << "Конечное число" << endl << "Assembler: " << result << endl << "C++: " << check(a, b);
	else if (state == 4) cout << "Бесконечность";
	else if (state == 5) cout << "Ноль" << endl << "Assembler: " << result << endl << "C++: " << check(a, b);
	else if (state == 6) cout << "Пустой регистр";
	else if (state == 7) cout << "Ненормированное число";
	else if (state == 8) cout << "Error: Деление на ноль";
	return 0;
}

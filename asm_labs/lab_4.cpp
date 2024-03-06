#include <iostream>

using namespace std;

int lab_4()
{
	setlocale(0, "");
	int m, b;
	int* a;
	cout << "Ќайти сумму положительных элементов массива A={a[i]}, удовлетвор€ющих условию : b <= a[i]\n";
	cout << "¬ведите размер массива: ";
	cin >> m;
	cout << "¬ведите элементы массива: \n";
	a = new int[m];
	for (int i = 0; i < m; i++) {
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}
	cout << "¬ведите b: ";
	cin >> b;
	int flag = 0;
	int result = 0;

	__asm
	{
		xor esi, esi // подготовка регистра индекса в массиве
		mov ebx, a // указатель на начало массива
		mov ecx, m // количество элементов массива

		begin_loop : // начало цикла
		xor eax, eax
			mov eax, [ebx + esi * 4] // определ€ем текущий элемент массива
			cmp eax, 0 // сравниваем элемент массива с 0
			jg calculation // если array[i] > 0
			jl loop_end // если array[i] < 0
			jmp loop_end // если array[i] = 0, переходим к следующей операции

			calculation :
		cmp eax, b // сравниваем с b
			jl loop_end // если меньше, то пропускаем, если больше или равно, то выполн€ем вычислени€

			add result, eax // добавл€ем результат

			xor eax, eax
			mov flag, 2 // если есть элементы, удовлетвор€ющие условию
			jmp loop_end

			error :
		mov flag, 1
			jmp close

			loop_end :
		inc esi //переходим к следующему элементу
			loop begin_loop; //повтор€ем цикл дл€ всех элементов массива

	close:
	}

	if (flag == 1) { cout << "Overflow!\n"; return -1; }
	else if (flag == 0) { cout << "Array does not contain elements that satisfy the condition!\n"; return -1; }
	else if (flag == 2)
	{
		int sum = 0;
		for (int i = 0; i < m; ++i)
		{
			if (a[i] > 0 && a[i] >= b) { sum += a[i]; }
		}
		cout << "C++: " << sum << endl;

		cout << "Assembler: " << result;
	}

	return 0;
}

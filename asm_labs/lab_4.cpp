#include <iostream>

using namespace std;

int lab_4()
{
	setlocale(0, "");
	int m, b;
	int* a;
	cout << "����� ����� ������������� ��������� ������� A={a[i]}, ��������������� ������� : b <= a[i]\n";
	cout << "������� ������ �������: ";
	cin >> m;
	cout << "������� �������� �������: \n";
	a = new int[m];
	for (int i = 0; i < m; i++) {
		cout << "a[" << i << "] = ";
		cin >> a[i];
	}
	cout << "������� b: ";
	cin >> b;
	int flag = 0;
	int result = 0;

	__asm
	{
		xor esi, esi // ���������� �������� ������� � �������
		mov ebx, a // ��������� �� ������ �������
		mov ecx, m // ���������� ��������� �������

		begin_loop : // ������ �����
		xor eax, eax
			mov eax, [ebx + esi * 4] // ���������� ������� ������� �������
			cmp eax, 0 // ���������� ������� ������� � 0
			jg calculation // ���� array[i] > 0
			jl loop_end // ���� array[i] < 0
			jmp loop_end // ���� array[i] = 0, ��������� � ��������� ��������

			calculation :
		cmp eax, b // ���������� � b
			jl loop_end // ���� ������, �� ����������, ���� ������ ��� �����, �� ��������� ����������

			add result, eax // ��������� ���������

			xor eax, eax
			mov flag, 2 // ���� ���� ��������, ��������������� �������
			jmp loop_end

			error :
		mov flag, 1
			jmp close

			loop_end :
		inc esi //��������� � ���������� ��������
			loop begin_loop; //��������� ���� ��� ���� ��������� �������

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

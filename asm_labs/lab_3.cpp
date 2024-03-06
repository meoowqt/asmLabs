#include <iostream>

using namespace std;

int lab_3()
{
	setlocale(0, "");
	int a, b;
	cout << "12 * b/a - 2b, a > b;\n-57, a = b;\n(6a - 103)/b, a < b;\n";
	cout << "������� a: ";
	cin >> a;
	cout << "������� b: ";
	cin >> b;

	int result;
	int flag = 0;
	__asm {
		mov eax, a; eax = a
		mov ebx, b; ebx = b
		cmp eax, ebx; ��������� ���������
		je aEQb; �������, ���� ��� �����
		jg aGTb; �������, ���� a > b
		jl aLTb; �������, ���� a < b

		aEQb : ; a = b
		xor eax, eax
		mov eax, -57; eax = -57
		jmp exit_end; ������� � �����

		aLTb : ; a < b
		xor ecx, ecx
		mov ecx, 6;
		imul ecx; eax = 6a
			jo of_exit; ������� ��� ������������

			sub eax, 103; eax = 6a - 103
			jo of_exit; ������� ��� ������������

			cdq; ��������� eax �� edx : eax
			CMP ebx, 0;
		jz dbz_exit; ������ ������� �� ����
			idiv ebx; eax = (6a - 103) / b
			jo of_exit; ������� ��� ������������
			jmp exit_end; �������, ���� �� � �������

			aGTb : ; a > b

			xor eax, eax;
		xor ebx, ebx;
		xor ecx, ecx;

		mov eax, b; eax = b
			mov ebx, a; ebx = a
			mov ecx, 12; ecx = 12
			imul ecx; eax = 12b
			jo of_exit;

		cdq; ��������� eax �� edx : eax
			CMP ebx, 0;
		jz dbz_exit; ������ ������� �� ����
			idiv ebx; eax = 12b / a
			jo of_exit;

		xor ebx, ebx;
		mov ebx, b; ebx = b
			add ebx, ebx; ebx = 2b
			jo of_exit;

		sub eax, ebx; eax = 12b / a - 2b
			jo of_exit;

		jmp exit_end

			dbz_exit : ; ��������� ������� �� 0
			mov flag, 1;
		jmp exit_end; �����

			of_exit : ; ��������� ������������
			mov flag, 2
			jmp exit_end; �����

			exit_end :
		mov result, eax; �����
	}
	switch (flag)
	{
	case 1: cout << "������! ������� �� ����!"; return -1;
	case 2: cout << "������! ������������!"; return -1;
	default: cout << "Assembler: " << result << endl; break;
	}

	if (a > b)
	{
		cout << "C++: " << 12 * b / a - 2 * b << endl;
	}
	else if (a < b)
	{
		cout << "C++: " << (6 * a - 103) / b << endl;
	}
	else
	{
		cout << "C++: " << -57 << endl;
	}

	return 0;
}
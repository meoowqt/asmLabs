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
	cout << "������� a: ";
	cin >> a;
	cout << "������� b: ";
	cin >> b;
	int status;
	int state = -1;
	const double b12 = 12, b2 = 2, a6 = 6, c103 = 103, am57 = -57;

	__asm
	{
		finit // ������������� ������������

		fld b // st(0) = b
		fld a // st(0) = a , st(1) = b

		fcom st(1) // ���������� a � b

		fstsw status // ��������� ������� ������ ������������
		mov ah, byte ptr[status + 1] // ��������� ������ ����
		sahf // ���������� ���������� ah � ������� FLAGS

		jp errorNotComp // ���� ����������
		ja aBigger// ������� ���� a ������
		jb bBigger// ������� ���� b ������

		fld qword ptr[am57]

		fxam// ����������� ���������� st(0)
		fnstsw ax// ��������� ������� ��������� ������������ swr � ax
		sahf// ���������� ah � ������� ������ ���������� eflags

		jnz c3_0; ���� �3 = 0
		jz c3_1; ���� �3 = 1

		aBigger :
		ftst // ���������� st(0) � 0
			fnstsw ax// ��������� ������� ��������� ������������ swr � ax
			sahf// ���������� ah � ������� ������ ���������� eflags
			jz zero
			fdiv //st(0)=b/a

			fmul qword ptr[b12] // st(0) = 12 * b/a
			fld qword ptr[b]// st(0) = b, st(0) = 12 * b/a
			fmul qword ptr[b2]// st(0) = 2 * b, st(1) = 12 * b/a
			fsub//st(0) = 12 * b/a - 2 * b

			fstp qword ptr[result]
			fld qword ptr[result]

			fxam// ����������� ���������� st(0)
			fnstsw ax// ��������� ������� ��������� ������������ swr � ax
			sahf// ���������� ah � ������� ������ ���������� eflags

			jnz c3_0// ���� �3 = 0
			jz c3_1// ���� �3 = 1

			bBigger :
		//(6 * a - 103) / b
		fldz //st(0) = 0, st(1) = a, st(2) = b
			fcomp st(2) //������������ ��������� b � 0 � �������������
			// st(0) = a, st(1) = b
			fnstsw ax// ��������� ������� ��������� ������������ swr � ax
			sahf// ���������� ah � ������� ������ ���������� eflags
			jz zero;
		fmul qword ptr[a6] // st(0) = a * 6, st(1) = b
			fld c103 // st(0) = 103, st(1) = 6 * a, st(2) = b
			fsub //st(0) = 6 * a - 103, st(1) = b
			fdiv st, st(1)// st(0) = (6 * a - 103) / b

			fstp qword ptr[result]
			fld qword ptr[result]

			fxam// ����������� ���������� st(0)
			fnstsw ax// � ax ���������� swr
			sahf// ���������� ah � ������� ������

			jnz c3_0// ���� �3 = 0
			jz c3_1// ���� �3 = 1

			zero :
		mov state, 8
			jmp endProg

			errorNotComp :
		mov state, 0
			jmp endProg

			c3_0 :
		jnp c2_0// ���� c2 = 0
			jnc c0_0// ���� c0 = 0
			mov state, 4
			jmp endProg

			c0_0 :
		mov state, 3
			fstp result
			jmp endProg

			c2_0 :
		jnc c0__0// ���� c0 = 0
			mov state, 2
			jmp endProg

			c0__0 :
		mov state, 1
			jmp endProg

			c3_1 :
		jnp c2__0// ���� c2 = 0
			mov state, 7
			jmp endProg

			c2__0 :
		jnc c0___0// ���� c0 = 0
			mov state, 6
			jmp endProg

			c0___0 :
		mov state, 5
			fstp result
			jmp endProg

			endProg :
	}
	if (state == 0) cout << "Error: �� ��������";
	else if (state == 1) cout << "���������������� ������";
	else if (state == 2) cout << "�������";
	else if (state == 3) cout << "�������� �����" << endl << "Assembler: " << result << endl << "C++: " << check(a, b);
	else if (state == 4) cout << "�������������";
	else if (state == 5) cout << "����" << endl << "Assembler: " << result << endl << "C++: " << check(a, b);
	else if (state == 6) cout << "������ �������";
	else if (state == 7) cout << "��������������� �����";
	else if (state == 8) cout << "Error: ������� �� ����";
	return 0;
}

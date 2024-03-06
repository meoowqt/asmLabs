#include <iostream>

using namespace std;

int err = 0;

double calc(double a, double b, double c)
{
    double result = 0;
    const double b6 = 6, c21 = 21, c3 = 3;
    __asm
    {
        finit

        fld qword ptr[b] // st(0) = b
        fmul qword ptr[b6] // st(0) = 6 * b
        fld qword ptr[c] // st(0) = c, st(1) = 6 * b
        fmul qword ptr[c21] // st(0) = 21 * c, st(1) = 6 * b
        fsub // st(0) = 6 * b - 21 * c

        fld qword ptr[a] // st(0) = a, st(1) = 6 * b - 21 * c
        fld qword ptr[c] // st(0) = c, st(1) = a, st(2) = 6 * b - 21 * c
        ftst // сравниваем st(0) и 0
        fstsw ax // записываем содержимое SWR в регистр АХ
        sahf ////запись флагов из ax в flags
        jz error_zero // если c = 0
        fdiv//st(0) = a/c, st(1) = 6 * b - 21 * c
        fld qword ptr[b]//st(0)=b, st(1) = a/c, st(2) = 6 * b - 21 * c
        fadd//st(0)=b + a/c, st(1) = 6 * b - 21 * c
        fld qword ptr[c3]//st(0) = 3, st(1) = b + a/c, st(2) = 6 * b - 21 * c
        fadd//st(0) = b + a/c + 3, st(1) = 6 * b - 21 * c
        ftst // сравниваем st(0) и 0
        fstsw ax // записываем содержимое SWR в регистр АХ
        sahf ////запись флагов из ax в flags
        jz error_zero
        fdivp st(1), st // st(0) = (6 * b - 21 * c) / (b + a/c + 3)
        jmp endProg

        error_zero :
        mov err, 1
            endProg :
            fstp result // result = st(0)
    }
    return result;
}
int lab_5()
{
    setlocale(0, "");
    double a, b, c;

    double result;
    cout << "Выражение (6 * b - 21 * c) / (b + a/c + 3)\n";
    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;
    cout << "Введите c: ";
    cin >> c;
    result = calc(a, b, c);
    if (err == 1)
    {
        cout << "Error 'zero'!" << endl;
        return -1;
    }
    else
    {
        cout << "C++: " << (6 * b - 21 * c) / (b + a / c + 3) << endl;
        cout << "Assembler: " << result << endl;
    }
    return 0;
}
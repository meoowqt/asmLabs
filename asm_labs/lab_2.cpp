#include <iostream>

using namespace std;

int lab_2()
{
    setlocale(0, "");
    int a, b, c;
    int flag1 = 0;
    int flag2 = 0;
    int result;
    cout << "Выражение (6 * b - 21 * c) / (b + a/c + 3)\n";
    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;
    cout << "Введите c: ";
    cin >> c;

    int x = 6;
    int y = 21;

    __asm
    {
        mov eax, a

        ; готовимся к делению
        cdq; расширяем eax до edx : eax
        CMP c, 0;
        jz error_zf; ошибка деление на ноль
            idiv c; <eax> = a / c


            add eax, 3; <eax> = a / c + 3
            jo error_of; ошибка переполнения

            add eax, b; <eax> = a / c + 3 + b
            jo error_of; ошибка переполнения

            push eax; поместили a / c + 3 + b в стек

            xor eax, eax
            mov eax, b; <eax> = b
            imul x; eax = > b * 6
            jo error_of; ошибка переполнения

            mov ebx, eax

            mov eax, c
            imul y; eax = > c * 21
            jo error_of; ошибка переполнения

            sub ebx, eax; <eax> = 6 * b - 21 * c
            jo error_of; ошибка переполнения

            mov eax, ebx

            xor ebx, ebx
            ; готовимся к делению
            pop ebx; <ebx> = a / c + 3 + b
            cdq; eax == > <edx:eax> = 6 * b - 21 * c
            CMP ebx, 0;
        jz error_zf
            idiv ebx; <eax> = (6 * b - 21 * c) / (b + a / c + 3)
            jo error_of
            jmp END

            error_zf :
        mov flag2, 1
            jmp END

            error_of :
        mov flag1, 1
            jmp END

            END :
        mov result, eax
    }
    if (flag1 == 1) { cout << "Ошибка! Переполнение!\n"; return -1; }
    if (flag2 == 1) { cout << "Ошибка! Деление на ноль!\n"; return -1; }

    int temp = (6 * b - 21 * c) / (b + a / c + 3);
    cout << "C++: " << temp << endl;
    cout << "Assembler: " << result << endl;
    return 0;
}
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <locale.h>
#include <iostream>
using namespace std;

class Patient;
class Doctor //информация о враче
{
    string type, FIO; 
    int kab = 0, time_1 = 0, time_2 = 0;
public:
    Doctor() { ; }
    Doctor(int kab1, string type1, string FIO1, int time1, int time2) { kab = kab1; type = type1, FIO = FIO1, time_1 = time1, time_2 = time2; }
    void show_doctors(int i) //функция для вывода врачей
    {
        cout << left << setw(5) << i << setw(10) << kab << setw(20) << type << setw(20) << FIO << time_1 << ":00-" << time_2 << ":00" << endl;
    } 
    void show_doctor() //функция для вывода одного врача
    {
        cout << "Кабинет: " << kab << endl;
        cout << "Специальность: " << type << endl;
        cout << "ФИО: " << FIO << endl;
        cout << "Время приема: " << time_1 << ":00-" << time_2 << ":00" << '\n' << endl;
    } 
    void show_time(int i) //функция для вывода времени записи
    {
        cout << "Время записи: " << time_1 + i/3 << ":" << i%3*2 << "0" << '\n' << endl;
    } 
    void show_FIO(int i) //функция для вывода фамилии врача
    {
        cout << i + 1 << " - " << FIO << endl;
    } 
    friend void talon(Patient* number, Doctor doctor);
    friend void spisok(Patient* number, Doctor doctor);
    friend void check(Patient* number, Doctor doctor, int talon_number);
    friend void cancel(Patient* number, Doctor doctor, int talon_number);
};

class Lab //информация о лаборатории
{
    string lab;
    int kab = 0, time_1 = 0, time_2 = 0;
public:
    Lab() { ; }
    Lab(int kab1, string lab1, int time1, int time2) { kab = kab1, lab = lab1, time_1 = time1, time_2 = time2; }
    void show_labs(int i) //функция для вывода лабораторий
    {
        cout << left << setw(5) << i << setw(10) << kab << setw(20) << lab << time_1 << ":00-" << time_2 << ":00" << endl;
    } 
    void show_lab() //функция для вывода одной лаборатории
    {
        cout << "Кабинет: " << kab << endl;
        cout << "лаборатория: " << lab << endl;
        cout << "Время приема: " << time_1 << ":00-" << time_2 << ":00" << '\n' << endl;
    } 
    void show_time(int i) //функция для вывода времени записи
    {
        cout << "Время записи: " << time_1 + i / 2 << ":" << i % 2 * 3 << "0" << '\n' << endl;
    } 
    void show_l(int i) //функция для вывода названия лаборатории
    {
        cout << i + 1 << " - " << lab << endl;
    } 
    friend void talon_2(Patient* number, Lab lab);
    friend void spisok_2(Patient* number, Lab lab);
    friend void check_2(Patient* number, Lab lab, int talon_number);
    friend void cancel_2(Patient* number, Lab lab, int talon_number);
};

class Patient //информация о пациенте
{
    string Name, Surname;
    int Age = 0, Phone = 0;
    int Talon = 0; //номер талона
public:
    Patient() { ; }
    void get_person() //функция для ввода персональных данных
    {
        cout << "Имя: ";
        cin >> Name;
        cout << "Фамилия: ";
        cin >> Surname;
        cout << "Возраст: ";
        cin >> Age;
        cout << "Контактный телефон: ";
        cin >> Phone;
        cout << endl;
    }
    void show_person() //функция для вывода персональных данных
    {
        cout << "Имя: " << Name << endl;
        cout << "Фамилия: " << Surname << endl;
        cout << "Возраст: " << Age << endl;
        cout << "Контактный телефон: " << Phone << endl;
    } 
    friend void talon(Patient* number, Doctor doctor);
    friend void talon_2(Patient* number, Lab lab);
    friend void spisok(Patient* number, Doctor doctor);
    friend void spisok_2(Patient* number, Lab lab);
    friend void check(Patient* number, Doctor doctor, int talon_number);
    friend void check_2(Patient* number, Lab lab, int talon_number);
    friend void cancel(Patient* number, Doctor doctor, int talon_number);
    friend void cancel_2(Patient* number, Lab lab, int talon_number);
};

void talon(Patient* number, Doctor doctor) //функция для вывода доступных талонов и выбора нужного времени к доктору
{
    int Time = 0;
    int k = doctor.time_1;
    int min = 0;
    int sum = 0;
    for (int i = 0; i < ((doctor.time_2 - doctor.time_1) * 3 + 1); i++) //проверка наличия каких-либо талонов
    {
        if (number[i].Talon == 0) sum++;
    }
    if (sum != 0)
    {
        cout << "\nДоступные талоны:\n"; //вывод доступных талонов
        for (int i = 0; i < ((doctor.time_2 - doctor.time_1) * 3); i++)
        {
            if (number[i].Talon == 0) cout << i + 1 << " - " << k << ":" << min << "0\n";
            min = min + 2;
            if (min > 4) { k++; min = 0; }
        }
        cout << "\n(Если хотите выйти, введите цифру - 0)\n";
        cout << "\nВыберите время\n";
        cout << ">>> ";
        cin >> Time; //запись на конкретное время
        if (Time == 0) cout << endl;
        if ((Time <= ((doctor.time_2 - doctor.time_1) * 3)) && (Time > 0))
        {
            if (number[Time - 1].Talon == 0)
            {
                cout << "\nВведите данные\n";
                number[Time - 1].get_person();
                srand(time(NULL)); //формирование номера талона
                number[Time - 1].Talon = rand();
                cout << "Номер вашего талона: " << number[Time - 1].Talon << "\n\n";
            }
            else cout << "\nТалон не доступен, выберите другой\n\n";
        }
        else if (Time != 0) cout << "\nТакого талона не существует, выберите другой.\n\n";
    }
    else cout << "\nДоступных талонов нет, выберите другой.\n\n";
}

void talon_2(Patient* number, Lab lab) //функция для вывода доступных талонов и выбора нужного времени в лабораторию
{
    int Time = 0;
    int k = lab.time_1;
    int min = 0;
    int sum = 0;
    for (int i = 0; i < ((lab.time_2 - lab.time_1) * 2); i++) //проверка наличия каких-либо талонов
    {
        if (number[i].Talon == 0) sum++;
    }
    if (sum != 0)
    {
        cout << "\nДоступные талоны:\n"; //вывод доступных талонов
        for (int i = 0; i < ((lab.time_2 - lab.time_1) * 2); i++)
        {
            if (number[i].Talon == 0) cout << i + 1 << " - " << k << ":" << min << "0\n";
            min = min + 3;
            if (min > 3) { k++; min = 0; }
        }
        cout << "\n(Если хотите выйти, введите цифру - 0)\n";
        cout << "\nВыберите время\n";
        cout << ">>> ";
        cin >> Time; //запись на конкретное время
        if (Time == 0) cout << endl;
        if ((Time <= ((lab.time_2 - lab.time_1) * 2)) && (Time > 0))
        {
            if (number[Time - 1].Talon == 0)
            {
                cout << "\nВведите данные\n";
                number[Time - 1].get_person();
                srand(time(NULL)); //формирование номера талона
                number[Time - 1].Talon = rand();
                cout << "Номер вашего талона: " << number[Time - 1].Talon << "\n\n";
            }
            else cout << "\nТалон не доступен, выберите другой\n\n";
        }
        else if (Time != 0) cout << "\nТакого талона не существует, выберите другой.\n\n";
    }
    else cout << "\nДоступных талонов нет, выберите другой.\n\n";
}

void spisok(Patient* number, Doctor doctor) //функция для вывода пациентов, записанных к врачу
{
    for (int i = 0; i < ((doctor.time_2 - doctor.time_1) * 3); i++)
        if (number[i].Talon != 0)
        {
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            doctor.show_time(i);
        }
}

void spisok_2(Patient* number, Lab lab) //функция для вывода пациентов, записанных в лабораторию
{
    for (int i = 0; i < ((lab.time_2 - lab.time_1) * 2); i++)
        if (number[i].Talon != 0)
        {
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            lab.show_time(i);
        }
}

void check(Patient* number, Doctor doctor, int talon_number) //функция проверки записи к врачу
{
    for (int i = 0; i < ((doctor.time_2 - doctor.time_1) * 3); i++)
        if (talon_number == number[i].Talon)
        {
            cout << "\nТалон №" << talon_number << "\n\n";
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            cout << "\nВРАЧ:\n";
            doctor.show_doctor();
            doctor.show_time(i);
        }
}

void check_2(Patient* number, Lab lab, int talon_number) //функция проверки записи в лабораторию
{
    for (int i = 0; i < ((lab.time_2 - lab.time_1) * 2); i++)
        if (talon_number == number[i].Talon)
        {
            cout << "\nТалон №" << talon_number << "\n\n";
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            cout << "\nЛАБОРАТОРИЯ:\n";
            lab.show_lab();
            lab.show_time(i);
        }
}

void cancel(Patient* number, Doctor doctor, int talon_number) //функция для отмены записи к врачу
{
    for (int i = 0; i < ((doctor.time_2 - doctor.time_1) * 3); i++)
        if (talon_number == number[i].Talon)
        {
            cout << "\nЗапись по талону №" << talon_number << " отменена\n\n";
            number[i].Talon = 0; //обнуление талона
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            cout << "\nВРАЧ:\n";
            doctor.show_doctor();
            doctor.show_time(i);
        }
}

void cancel_2(Patient* number, Lab lab, int talon_number) //функция для отмены записи в лабораторию
{
    for (int i = 0; i < ((lab.time_2 - lab.time_1) * 2); i++)
        if (talon_number == number[i].Talon)
        {
            cout << "\nЗапись по талону №" << talon_number << " отменена\n\n";
            number[i].Talon = 0; //обнуление талона
            cout << "ПАЦИЕНТ:\n";
            number[i].show_person();
            cout << "\nЛАБОРАТОРИЯ:\n";
            lab.show_lab();
            lab.show_time(i);
        }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int quantity = 8, quantity_2 = 5;
    Doctor doctor[8]; // врачи
    doctor[0] = Doctor(123, "Дерматолог", "Иванов А.С", 9, 13);
    doctor[1] = Doctor(307, "Кардиолог", "Петров И.Д", 14, 19);
    doctor[2] = Doctor(110, "Невролог", "Сидорова Е.С", 14, 17);
    doctor[3] = Doctor(205, "Офтальмолог", "Степанова Г.Л", 11, 16);
    doctor[4] = Doctor(107, "Психиатр", "Грачев Ф.Н", 15, 18);
    doctor[5] = Doctor(202, "Терапевт", "Тихонова Д.С", 9, 14);
    doctor[6] = Doctor(203, "Терапевт", "Потапов Н.Д", 15, 20);
    doctor[7] = Doctor(101, "Хирург", "Трофимов К.Н", 14, 16);
    Lab lab[5]; // лаборатории
    lab[0] = Lab(104, "Флюорография", 15, 18);
    lab[1] = Lab(206, "ЭКГ", 14, 18);
    lab[2] = Lab(215, "Прививочная", 10, 16);
    lab[3] = Lab(314, "Рентгенография", 11, 17);
    lab[4] = Lab(109, "Сдача крови", 9, 14);
    Patient* one[8]; //пациенты
    for (int i=0; i<quantity; i++)
    one[i] = new Patient[36];
    Patient* two[5];
    for (int i = 0; i < quantity_2; i++)
    two[i] = new Patient[36];
    int variant = 0, number = 0;
    int talon_number = 0; //номер вводимого для отмены талона
    while (variant != 8)
    {
        cout << "   РЕГИСТРАТУРА\n";
        cout << "Выберите:\n";
        cout << "   1 - Расписание\n";
        cout << "   2 - Запись на прием к специалисту\n";
        cout << "   3 - Запись в лабораторию\n";
        cout << "   4 - Проверка записи\n";
        cout << "   5 - Список пациентов записанных на прием к специалисту\n";
        cout << "   6 - Список пациентов записанных на прием в лабораторию\n";
        cout << "   7 - Отмена записи\n";
        cout << "   8 - Завершение\n";
        cout << ">>> ";
        cin >> variant;
        cout << endl;
        switch (variant)
        {
        case 1: //вывод расписания
            cout << left << setw(5) << "№" << setw(10) << "КАБИНЕТ" << setw(20) << "СПЕЦИАЛЬНОСТЬ" << setw(20) << "ФИО" << setw(20) << "ВРЕМЯ ПРИЕМА" << endl;
            for (int i = 0; i < quantity; i++)
                doctor[i].show_doctors(i + 1);
            cout << endl;
            cout << left << setw(5) << "№" << setw(10) << "КАБИНЕТ" << setw(20) << "ЛАБОРАТОРИЯ" << setw(20) << "ВРЕМЯ РАБОТЫ" << endl;
            for (int i = 0; i < quantity_2; i++)
                lab[i].show_labs(i + 1);
            cout << endl;
            break;
        case 2: //запись на прием к врачу
            cout << left << setw(5) << "№" << setw(10) << "КАБИНЕТ" << setw(20) << "СПЕЦИАЛЬНОСТЬ" << setw(20) << "ФИО" << setw(20) << "ВРЕМЯ ПРИЕМА" << endl;
            for (int i=0; i<quantity; i++)
                doctor[i].show_doctors(i+1);
            cout << "\n(Если хотите выйти, введите цифру - 0)\n";
            cout << "\nВведите номер cпециалиста:\n";
            cout << ">>> ";
            cin >> number; //выбор конкретного врача
            if (number == 0) { cout << endl; break; }
            if ((number > 0) && (number <= quantity))
                talon(one[number - 1], doctor[number - 1]); //запись к выбранному врачу, на какое то время
            else if (number != 0) cout << "\nДанного специалиста не существует, выберите другого.\n\n";
            break;
        case 3: //запись в лабораторию
            cout << left << setw(5) << "№" << setw(10) << "КАБИНЕТ" << setw(20) << "ЛАБОРАТОРИЯ" << setw(20) << "ВРЕМЯ РАБОТЫ" << endl;
            for (int i = 0; i < quantity_2; i++)
                lab[i].show_labs(i + 1);
            cout << "\n(Если хотите выйти, введите цифру - 0)\n";
            cout << "\nВведите номер лаборатории:\n";
            cout << ">>> ";
            cin >> number; //выбор лаборатории
            if (number == 0) { cout << endl; break; }
            if ((number > 0) && (number <= quantity_2))
                talon_2(two[number - 1], lab[number - 1]); //запись в выбранную лабораторию, на какое то время
            else if (number != 0) cout << "\nДанной лаборатории не существует, выберите другую.\n\n";
            break;
        case 4: //проверка записи
            cout << "(Если хотите выйти, введите цифру - 0)\n\n";
            cout << "Введите номер талона: ";
            cin >> talon_number; 
            if (talon_number == 0) { cout << endl; break; }
            for (int i = 0; i < quantity; i++)
                check(one[i], doctor[i], talon_number);
            for (int i = 0; i < quantity_2; i++)
                check_2(two[i], lab[i], talon_number);
            cout << endl;
            break;
        case 5: //вывод списка пациентов, записанных к врачу
            cout << "СПЕЦИАЛИСТЫ:\n";
            for (int i = 0; i < quantity; i++)
                doctor[i].show_FIO(i);
            cout << "\n(Если хотите выйти, введите цифру - 0)\n";
            cout << "\nВведите номер специалиста:\n";
            cout << ">>> ";
            cin >> number; 
            cout << endl;
            if (number == 0) { cout << endl; break; }
            if ((number > 0) && (number <= quantity))  //вывод информации о докторе и списка пациентов
            {
                doctor[number - 1].show_doctor();
                spisok(one[number - 1], doctor[number - 1]);
            }
            else if (number != 0) cout << "Данного специалиста не существует, выберите другого.\n\n";
            break;
        case 6: //вывод списка пациентов, записанных в лабораторию
            cout << "ЛАБОРАТОРИИ:\n";
            for (int i = 0; i < quantity_2; i++)
                lab[i].show_l(i);
            cout << "\n(Если хотите выйти, введите цифру - 0)\n";
            cout << "\nВведите номер специалиста:\n";
            cout << ">>> ";
            cin >> number;
            cout << endl;
            if (number == 0) { cout << endl; break; }
            if ((number > 0) && (number <= quantity_2)) //вывод информации о лаборатории и списка пациентов
            {
                lab[number - 1].show_lab();
                spisok_2(two[number - 1], lab[number - 1]);
            }
            else if (number != 0) cout << "Данной лаборатории не существует, выберите другую.\n\n";
            break;
        case 7: //отмена записи
            cout << "(Если хотите выйти, введите цифру - 0)\n\n";
            cout << "Введите номер талона: ";
            cin >> talon_number; //ввод номера талона, для отмены записи
            if (talon_number == 0) { cout << endl; break; }
            for (int i = 0; i < quantity; i++) //проверка и отмена записи к врачу
            cancel(one[i], doctor[i], talon_number);
            for (int i = 0; i < quantity_2; i++) //проверка и отмена записи в лабораторию
            cancel_2(two[i], lab[i], talon_number);
            cout << endl;
            break;
        case 8: cout << "Завершено"; break;
        }
    }
    cout << endl;
    return 0;
}

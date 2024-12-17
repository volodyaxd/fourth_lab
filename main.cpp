#include <iostream>
#include <stdexcept>
#include <windows.h>

class Time {
private:
    short int hours;   // Часы
    short int minutes; // Минуты

    void normalize() {
        if (minutes < 0) {
            hours -= (1 + (-minutes) / 60);
            minutes = (minutes + 60) % 60;
        }
        if (hours < 0) {
            hours = (hours + 24) % 24;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes = minutes % 60;
        }
        if (hours >= 24) {
            hours = hours % 24;
        }
    }

public:
    // Конструктор по умолчанию
    Time() : hours(0), minutes(0) {}

    // Конструктор с параметрами
    Time(short int h, short int m) : hours(h), minutes(m) {
        if (h < 0 || h >= 24 || m < 0 || m >= 60) {
            throw std::invalid_argument("Некорректное время");
        }
        normalize();
    }

    // Конструктор копирования
    Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

    // Метод для вычитания времени
    Time operator-(const Time& other) const {
        Time result;
        result.hours = hours - other.hours;
        result.minutes = minutes - other.minutes;
        result.normalize();
        return result;
    }

    // Унарная операция: вычитание одной минуты
    Time operator--() {
        minutes--;
        normalize();
        return *this;
    }

    // Операция приведения к short int (явная)
    explicit operator short int() const {
        return hours; // Возвращаем только часы
    }

    // Операция приведения к bool (неявная)
    explicit operator bool() const {
        return (hours != 0 || minutes != 0); // true, если время не ноль
    }

    // Бинарная операция: добавление минут к времени
    Time operator+(unsigned int min) const {
        Time result = *this; // Копируем текущее время
        result.minutes += min;
        result.normalize();
        return result;
    }

    // Бинарная операция: сложение двух времён
    Time operator+(const Time& other) const {
        Time result;
        result.hours = hours + other.hours;
        result.minutes = minutes + other.minutes;
        result.normalize();
        return result;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << (t.hours < 10 ? "0" : "") << t.hours << ":"
           << (t.minutes < 10 ? "0" : "") << t.minutes;
        return os;
    }
};
void displayMenu() {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1. Ввод времени\n";
    std::cout << "2. Вычитание времени\n";
    std::cout << "3. Вычитание одной минуты\n";
    std::cout << "4. Приведение к часам\n";
    std::cout << "5. Проверка на ноль\n";
    std::cout << "6. Добавление минут\n";
    std::cout << "7. Сложение двух времён\n";
    std::cout << "0. Выход\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Time time1, time2;
    int choice;

    while (true) {
        displayMenu();
        std::cout << "Введите номер действия: ";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    short int h1, m1;
                    std::cout << "Введите первое время (часы и минуты): ";
                    std::cin >> h1 >> m1;
                    time1 = Time(h1, m1);
                    std::cout << "Первое время установлено: " << time1 << std::endl;
                    break;
                }
                case 2: {
                    short int h2, m2;
                    std::cout << "Введите второе время (часы и минуты): ";
                    std::cin >> h2 >> m2;
                    time2 = Time(h2, m2);
                    Time result = time1 - time2;
                    std::cout << "Результат вычитания: " << result << std::endl;
                    break;
                }
                case 3: {
                    std::cout << "Первое время до вычитания минуты: " << time1 << std::endl;
                    --time1; // Вычитаем 1 минуту
                    std::cout << "Первое время после вычитания минуты: " << time1 << std::endl;
                    break;
                }
                case 4: {
                    short int hoursOnly = static_cast<short int>(time1);
                    std::cout << "Часы первого времени: " << hoursOnly << std::endl;
                    break;
                }
                case 5: {
                    bool isNonZero = static_cast<bool>(time1);
                    std::cout << "Первое время не равно нулю: " << (isNonZero ? "true" : "false") << std::endl;
                    break;
                }
                case 6: {
                    unsigned int minutesToAdd;
                    std::cout << "Введите количество минут для добавления: ";
                    std::cin >> minutesToAdd;
                    Time addedMinutes = time1 + minutesToAdd; // Добавляем минуты
                    std::cout << "Первое время + " << minutesToAdd << " минут: " << addedMinutes << std::endl;
                    break;
                }
                case 7: {
                    Time sumTime = time1 + time2; // Складываем два времени
                    std::cout << "Сумма двух времён: " << sumTime << std::endl;
                    break;
                }
                case 0:
                    std::cout << "Выход из программы." << std::endl;
                    return 0;
                default:
                    std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }

    return 0;
}

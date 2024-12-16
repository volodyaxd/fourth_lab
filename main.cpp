#include <iostream>
#include <stdexcept>

class Time {
private:
    short int hours;
    short int minutes;

public:
    // Конструкторы
    Time() : hours(0), minutes(0) {}
    Time(short int h, short int m) : hours(h), minutes(m) {
        if (m >= 60) {
            hours += m / 60;
            minutes = m % 60;
        }
        if (h < 0 || m < 0) throw std::invalid_argument("Часы и минуты не могут быть отрицательными.");
    }
    Time(const Time& t) : hours(t.hours), minutes(t.minutes) {}

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << t.hours << " ч " << t.minutes << " мин";
        return os;
    }

    // Метод добавления минут
    Time addMinutes(unsigned int m) {
        Time result = *this;
        result.minutes += m;
        if (result.minutes >= 60) {
            result.hours += result.minutes / 60;
            result.minutes %= 60;
        }
        return result;
    }

    // Метод вычитания времени
    Time operator-(const Time& t) {
        Time result;
        result.minutes = minutes - t.minutes;
        result.hours = hours - t.hours;
        
        if (result.minutes < 0) {
            result.minutes += 60;
            result.hours--;
        }
        if (result.hours < 0) {
            throw std::invalid_argument("Результат времени не может быть отрицательным.");
        }
        return result;
    }

    // Метод для проверки, является ли время нулевым
    bool isZero() const {
        return hours == 0 && minutes == 0;
    }
};

int main() {
    short int h1, m1, h2, m2;

    std::cout << "Введите часы и минуты для первого времени (часы минуты): ";
    std::cin >> h1 >> m1;
    Time t1(h1, m1);

    std::cout << "Введите часы и минуты для второго времени (часы минуты): ";
    std::cin >> h2 >> m2;
    Time t2(h2, m2);

    Time t3 = t1.addMinutes(50);
    Time t4 = t1 - t2;

    std::cout << "Время 1: " << t1 << std::endl;
    std::cout << "Время 2: " << t2 << std::endl;
    std::cout << "Время 1 + 50 минут: " << t3 << std::endl;
    std::cout << "Время 1 - Время 2: " << t4 << std::endl;

    return 0;
}

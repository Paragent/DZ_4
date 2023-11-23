#include <iostream>
#include <cmath>

using namespace std;

class Date {
private:
    int year, month, day, hour, minute, second;
    bool isOurEra;

    bool isLeapYear(int year) const {
        if (year % 4 != 0) {
            return false;
        } else if (year % 100 != 0) {
            return true;
        } else if (year % 400 != 0) {
            return false;
        } else {
            return true;
        }
    }

    int daysInMonth(int year, int month) const {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            return 31;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            return 30;
        } else if (month == 2) {
            return isLeapYear(year) ? 29 : 28;
        } else {
            return 0;
        }
    }

    void checkThis() {
        if(isOurEra && day == 0){
            day++;
        }
        if(isOurEra && month == 0){
            month++;
        }
        if(isOurEra && year == 0){
            year++;
        }
        if(!isOurEra && day == 0){
            day++;
        }
        if(!isOurEra && month == 0){
            month++;
        }
        if(!isOurEra && year == 0){
            year++;
        }
        while (month > 12) {
            month -= 12;
            year++;
        }
        while (month <= 0) {
            month += 12;
            year--;
        }
        while (day > daysInMonth(year, month)) {
            day -= daysInMonth(year, month);
            month++;
        }
        if (day <= 0) {
            month--;
            day += daysInMonth(year, month);
        }
        while (hour >= 24) {
            hour -= 24;
            day++;
        }
        while (hour < 0) {
            hour += 24;
            day--;
        }
        while (minute >= 60) {
            minute -= 60;
            hour++;
        }
        while (minute < 0) {
            minute += 60;
            hour--;
        }
        while (second < 0) {
            second += 60;
            minute--;
        }
        if (year < 0){
            isOurEra = false;
            year = abs(year);
        }
    }

public:
    Date() {
        this->isOurEra = true;
        this->year = 1960;
        this->month = 1;
        this->day = 1;
        this->hour = 0;
        this->minute = 0;
        this->second = 0;
    }

    Date(int Year, int Month, int Day, int Hour, int Minute, int Second, bool Era) {
        this->isOurEra = Era;
        this->year = Year;
        this->month = Month;
        this->day = Day;
        this->hour = Hour;
        this->minute = Minute;
        this->second = Second;

        checkThis();
    }

    Date (const Date& dt){
            this->isOurEra = dt.isOurEra;
            this->year = dt.year;
            this->month = dt.month;
            this->day = dt.day;
            this->hour = dt.hour;
            this->minute = dt.minute;
            this->second = dt.second;
    }

    Date add(int years = 0, int months = 0, int days = 0, int hours = 0, int minutes = 0, int seconds = 0) {
        int newYear = year + years;
        int newMonth = month + months;
        int newDay = day + days;
        int newHour = hour + hours;
        int newMinute = minute + minutes;
        int newSecond = second + seconds;

        while (newMonth > 12) {
            newMonth -= 12;
            newYear++;
        }

        while (newMonth <= 0) {
            newMonth += 12;
            newYear--;
        }

        while (newDay > daysInMonth(newYear, newMonth)) {
            newDay -= daysInMonth(newYear, newMonth);
            newMonth++;
        }

        if (newDay <= 0) {
            newMonth--;
            newDay += daysInMonth(newYear, newMonth);
        }

        while (newHour >= 24) {
            newHour -= 24;
            newDay++;
        }

        while (newMinute >= 60) {
            newMinute -= 60;
            newHour++;
        }

        while (newSecond >= 60) {
            newSecond -= 60;
            newMinute++;
        }

        year = newYear;
        month = newMonth;
        day = newDay;
        hour = newHour;
        minute = newMinute;
        second = newSecond;

        return *this;
}

Date subtract(int years, int months, int days, int hours, int minutes, int seconds) {
    int newYear = year - years;
    int newMonth = month - months;
    int newDay = day - days;
    int newHour = hour - hours;
    int newMinute = minute - minutes;
    int newSecond = second - seconds;

    while (newDay <= 0) {
        newMonth--;
        if (newMonth <= 0) {
            newMonth += 12;
            newYear--;
        }
        newDay += daysInMonth(newYear, newMonth);
    }

    while (newHour < 0) {
        newHour += 24;
        newDay--;
        if (newDay <= 0) {
            newMonth--;
            if (newMonth <= 0) {
                newMonth += 12;
                newYear--;
            }
            newDay += daysInMonth(newYear, newMonth);
        }
    }

    while (newMinute < 0) {
        newMinute += 60;
        newHour--;
        if (newHour < 0) {
            newHour += 24;
            newDay--;
            if (newDay <= 0) {
                newMonth--;
                if (newMonth <= 0) {
                    newMonth += 12;
                    newYear--;
                }
                newDay += daysInMonth(newYear, newMonth);
            }
        }
    }

    while (newSecond < 0) {
        newSecond += 60;
        newMinute--;
        if (newMinute < 0) {
            newMinute += 60;
            newHour--;
            if (newHour < 0) {
                newHour += 24;
                newDay--;
                if (newDay <= 0) {
                    newMonth--;
                    if (newMonth <= 0) {
                        newMonth += 12;
                        newYear--;
                    }
                    newDay += daysInMonth(newYear, newMonth);
                }
            }
        }
    }

    while (newMonth <= 0) {
        newMonth += 12;
        newYear--;
    }

    if (newYear < 0 && isOurEra) {
        year = abs(newYear);
        month = newMonth;
        day = newDay;
        hour = newHour;
        minute = newMinute;
        second = newSecond;
        isOurEra = false;
    } else if (newYear == 0) {
        year = 1;
        month = newMonth;
        day = newDay;
        hour = newHour;
        minute = newMinute;
        second = newSecond;
    } else {
        year = newYear;
        month = newMonth;
        day = newDay;
        hour = newHour;
        minute = newMinute;
        second = newSecond;
    }

    return *this;
}


    Date& operator+=(const Date& dt) {
        this->year += dt.year;
        this->month += dt.month;
        this->day += dt.day;
        this->hour += dt.hour;
        this->minute += dt.minute;
        this->second += dt.second;

        checkThis();

        return *this;
    }

    Date operator+(const Date& dt) const {
        Date res = *this;
        res.checkThis();
        return res += dt;
    }

    Date& operator-=(const Date& dt) {
        this->year -= dt.year;
        this->month -= dt.month;
        this->day -= dt.day;
        this->hour -= dt.hour;
        this->minute -= dt.minute;
        this->second -= dt.second;

        checkThis();

        return *this;
    }

    Date operator-(const Date& dt) const {
        Date res = *this;
        res.checkThis();
        return res-=dt;
    }

    Date& operator=(const Date& dt) {
        this->year = dt.year;
        this->month = dt.month;
        this->day = dt.day;
        this->hour = dt.hour;
        this->minute = dt.minute;
        this->second = dt.second;
        this->isOurEra = dt.isOurEra;

        return *this;
    }

    bool operator==(const Date& dt) const {
        return (this->year == dt.year &&
                this->month == dt.month &&
                this->day == dt.day &&
                this->hour == dt.hour &&
                this->minute == dt.minute &&
                this->second == dt.second &&
                this->isOurEra == dt.isOurEra);
    }

    bool operator>(const Date& dt) const {
        if (this->year > dt.year) return true;
        else if (this->year < dt.year) return false;

        if (this->month > dt.month) return true;
        else if (this->month < dt.month) return false;

        if (this->day > dt.day) return true;
        else if (this->day < dt.day) return false;

        if (this->hour > dt.hour) return true;
        else if (this->hour < dt.hour) return false;

        if (this->minute > dt.minute) return true;
        else if (this->minute < dt.minute) return false;

        return this->second > dt.second;
    }

    bool operator<(const Date& dt) const {
        return !(*this == dt || *this > dt);
    }

    friend ostream& operator<<(ostream& os, const Date& dt) {
        os << dt.day << "/";
        os << dt.month << "/";
        os << dt.year << " ";
        os << dt.hour << ":";
        os << dt.minute << ":";
        os << dt.second << " ";
        os << (dt.isOurEra? "AD":"BC");
        return os;
    }
};

int main() {
    Date d1;
    cout << d1  << endl;
    Date d2(2060, 1, 1, 0, 0, 0, true);
    cout << (d1 > d2) << endl;
    cout << (d1 < d2) << endl;
    cout << (d1 == d2) << endl;
    Date d3 = d2.subtract(2060, 1, 1, 0, 0, 0);
    cout << d3 << endl;
    cout << d3+d2-d1 << endl;
    Date d4(d3 + d2 - d1);
    cout << d4 << endl;
    Date d5(d4);
    cout << d5 << endl;
    d4 += d5 - d4.add(40, 1, 1, 0, 0, 0);

    cout << d3 << endl;
    cout << d4 << endl;
    cout << d5 << endl;

    Date d6(0, 0, 0, 0, 0, 0, false);
    Date d7(0, 0, 0, 0, 0, 0, true);
    cout << d6 << endl;
    cout << d7 << endl;

    Date d8 = d6 - d7 - d1;
    cout << d6 + d7 << endl;
    Date d9(d8);

    cout << d9 << endl; // 1/1/1 0:0:0 BC  31/12/1961 0:0:0 BC

    Date d10;
    Date d11 = d10 - d10;// 1/1/1 0:0:0 AD
    Date d12(d11);
    Date d13;
    cout << d13 + d11 - d10 << endl;// 2/2/1961 0:0:0 AD   1/1/1 0:0:0 AD

    return 0;
}


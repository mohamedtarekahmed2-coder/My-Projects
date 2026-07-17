#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
    int _Day = 1;
    int _Month = 1;
    int _Year = 1900;

public:
    // --- Enums ---
    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    // --- Constructors ---
    clsDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
    }

    clsDate(string sDate)
    {
        vector<string> vDate;
        vDate = clsString::Split(sDate, "/");

        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);
    }

    clsDate(int Day, int Month, int Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(int DateOrderInYear, int Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1._Day;
        _Month = Date1._Month;
        _Year = Date1._Year;
    }

    // --- Getters & Setters ---
    void SetDay(int Day)
    {
        _Day = Day;
    }
    int GetDay()
    {
        return _Day;
    }

    void SetMonth(int Month)
    {
        _Month = Month;
    }
    int GetMonth()
    {
        return _Month;
    }

    void SetYear(int Year)
    {
        _Year = Year;
    }
    int GetYear()
    {
        return _Year;
    }

    // --- Print & Conversions ---
    void Print()
    {
        cout << DateToString() << endl;
    }

    static string DateToString(clsDate Date)
    {
        return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
    }

    string DateToString()
    {
        return DateToString(*this);
    }

    // --- Basic Date Validations & Helpers ---
    static clsDate GetSystemDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);

        int Day, Month, Year;
        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;

        return clsDate(Day, Month, Year);
    }

    static bool IsValidDate(clsDate Date)
    {
        if (Date._Day < 1 || Date._Day > 31)
            return false;

        if (Date._Month < 1 || Date._Month > 12)
            return false;

        if (Date._Month == 2)
        {
            if (isLeapYear(Date._Year))
            {
                if (Date._Day > 29)
                    return false;
            }
            else
            {
                if (Date._Day > 28)
                    return false;
            }
        }

        int DaysInMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > DaysInMonth)
            return false;

        return true;
    }

    bool IsValid()
    {
        return IsValidDate(*this);
    }

    // --- Year Calculations ---
    static bool isLeapYear(int Year)
    {
        return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
    }

    bool isLeapYear()
    {
        return isLeapYear(_Year);
    }

    static int NumberOfDaysInAYear(int Year)
    {
        return isLeapYear(Year) ? 366 : 365;
    }

    int NumberOfDaysInAYear()
    {
        return NumberOfDaysInAYear(_Year);
    }

    static int NumberOfHoursInAYear(int Year)
    {
        return NumberOfDaysInAYear(Year) * 24;
    }

    int NumberOfHoursInAYear()
    {
        return NumberOfHoursInAYear(_Year);
    }

    static int NumberOfMinutesInAYear(int Year)
    {
        return NumberOfHoursInAYear(Year) * 60;
    }

    int NumberOfMinutesInAYear()
    {
        return NumberOfMinutesInAYear(_Year);
    }

    static int NumberOfSecondsInAYear(int Year)
    {
        return NumberOfMinutesInAYear(Year) * 60;
    }

    int NumberOfSecondsInAYear()
    {
        return NumberOfSecondsInAYear(_Year);
    }

    // --- Month Calculations ---
    static int NumberOfDaysInAMonth(int Month, int Year)
    {
        if (Month < 1 || Month > 12)
            return 0;

        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : days[Month - 1];
    }

    int NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }

    static int NumberOfHoursInAMonth(int Month, int Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    int NumberOfHoursInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year) * 24;
    }

    static int NumberOfMinutesInAMonth(int Month, int Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year) * 60;
    }

    static int NumberOfSecondsInAMonth(int Month, int Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year) * 60;
    }

    // --- Names & Calendar ---
    static int DayOfWeekOrder(int Day, int Month, int Year)
    {
        int a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }

    int DayOfWeekOrder()
    {
        return DayOfWeekOrder(_Day, _Month, _Year);
    }

    static string DayintName(int DayOfWeekOrder)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder];
    }

    static string DayintName(int Day, int Month, int Year)
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(Day, Month, Year)];
    }

    string DayintName()
    {
        string arrDayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[DayOfWeekOrder(_Day, _Month, _Year)];
    }

    static string MonthintName(int MonthNumber)
    {
        string Months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return Months[MonthNumber - 1];
    }

    string MonthintName()
    {
        return MonthintName(_Month);
    }

    static void PrintMonthCalendar(int Month, int Year)
    {
        int NumberOfDays;
        int current = DayOfWeekOrder(1, Month, Year);
        NumberOfDays = NumberOfDaysInAMonth(Month, Year);

        printf("\n  _______________%s_______________\n\n", MonthintName(Month).c_str());
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;
        for (i = 0; i < current; i++)
            printf("     ");

        for (int j = 1; j <= NumberOfDays; j++)
        {
            printf("%5d", j);
            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }
        printf("\n  _________________________________\n");
    }

    void PrintMonthCalendar()
    {
        PrintMonthCalendar(_Month, _Year);
    }

    static void PrintYearCalendar(int Year)
    {
        printf("\n  _________________________________\n\n");
        printf("           Calendar - %d\n", Year);
        printf("  _________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }
    }

    void PrintYearCalendar()
    {
        PrintYearCalendar(_Year);
    }

    // --- Date Comparisons ---
    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year < Date2._Year) ? true : 
               ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : 
               (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
    }

    bool IsDateBeforeDate2(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return (Date1._Year == Date2._Year) && (Date1._Month == Date2._Month) && (Date1._Day == Date2._Day);
    }

    bool IsDateEqualDate2(clsDate Date2)
    {
        return IsDate1EqualDate2(*this, Date2);
    }

    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

    bool IsDateAfterDate2(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
    {
        if (IsDate1BeforeDate2(Date1, Date2))
            return enDateCompare::Before;

        if (IsDate1EqualDate2(Date1, Date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }

    enDateCompare CompareDates(clsDate Date2)
    {
        return CompareDates(*this, Date2);
    }

    // --- Date Differences & Math ---
    static int DaysFromTheBeginingOfTheYear(int Day, int Month, int Year)
    {
        int TotalDays = 0;
        for (int i = 1; i <= Month - 1; i++)
        {
            TotalDays += NumberOfDaysInAMonth(i, Year);
        }
        TotalDays += Day;
        return TotalDays;
    }

    int DaysFromTheBeginingOfTheYear()
    {
        return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
    }

    static clsDate GetDateFromDayOrderInYear(int DateOrderInYear, int Year)
    {
        clsDate Date;
        int RemainingDays = DateOrderInYear;
        int MonthDays = 0;

        Date._Year = Year;
        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainingDays;
                break;
            }
        }
        return Date;
    }

    static void SwapDates(clsDate &Date1, clsDate &Date2)
    {
        clsDate TempDate = Date1;
        Date1 = Date2;
        Date2 = TempDate;
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        int Days = 0;
        int SwapFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            SwapDates(Date1, Date2);
            SwapFlagValue = -1;
        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = AddOneDay(Date1);
        }

        return IncludeEndDay ? ++Days * SwapFlagValue : Days * SwapFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static int CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    // --- Increase Date Operations ---
    static clsDate AddOneDay(clsDate Date)
    {
        if (IsLastDayInMonth(Date))
        {
            if (IsLastMonthInYear(Date._Month))
            {
                Date._Month = 1;
                Date._Day = 1;
                Date._Year++;
            }
            else
            {
                Date._Day = 1;
                Date._Month++;
            }
        }
        else
        {
            Date._Day++;
        }
        return Date;
    }

    void AddOneDay()
    {
        *this = AddOneDay(*this);
    }

    void AddDays(int Days)
    {
        int RemainingDays = Days + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
        int MonthDays = 0;
        _Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(_Month, _Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                _Month++;

                if (_Month > 12)
                {
                    _Month = 1;
                    _Year++;
                }
            }
            else
            {
                _Day = RemainingDays;
                break;
            }
        }
    }

    static clsDate IncreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static clsDate IncreaseDateByXWeeks(int Weeks, clsDate &Date)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void IncreaseDateByXWeeks(int Weeks)
    {
        IncreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate IncreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 12)
        {
            Date._Month = 1;
            Date._Year++;
        }
        else
        {
            Date._Month++;
        }

        int NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > NumberOfDaysInCurrentMonth)
        {
            Date._Day = NumberOfDaysInCurrentMonth;
        }
        return Date;
    }

    void IncreaseDateByOneMonth()
    {
        IncreaseDateByOneMonth(*this);
    }

    static clsDate IncreaseDateByXDays(int Days, clsDate &Date)
    {
        for (int i = 1; i <= Days; i++)
        {
            Date = AddOneDay(Date);
        }
        return Date;
    }

    void IncreaseDateByXDays(int Days)
    {
        IncreaseDateByXDays(Days, *this);
    }

    static clsDate IncreaseDateByXMonths(int Months, clsDate &Date)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void IncreaseDateByXMonths(int Months)
    {
        IncreaseDateByXMonths(Months, *this);
    }

    static clsDate IncreaseDateByOneYear(clsDate &Date)
    {
        Date._Year++;
        return Date;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

    static clsDate IncreaseDateByXYears(int Years, clsDate &Date)
    {
        Date._Year += Years;
        return Date;
    }

    void IncreaseDateByXYears(int Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    static clsDate IncreaseDateByOneDecade(clsDate &Date)
    {
        Date._Year += 10;
        return Date;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static clsDate IncreaseDateByXDecades(int Decades, clsDate &Date)
    {
        Date._Year += Decades * 10;
        return Date;
    }

    void IncreaseDateByXDecades(int Decades)
    {
        IncreaseDateByXDecades(Decades, *this);
    }

    static clsDate IncreaseDateByOneCentury(clsDate &Date)
    {
        Date._Year += 100;
        return Date;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    static clsDate IncreaseDateByOneMillennium(clsDate &Date)
    {
        Date._Year += 1000;
        return Date;
    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    // --- Decrease Date Operations ---
    static clsDate DecreaseDateByOneDay(clsDate Date)
    {
        if (Date._Day == 1)
        {
            if (Date._Month == 1)
            {
                Date._Month = 12;
                Date._Day = 31;
                Date._Year--;
            }
            else
            {
                Date._Month--;
                Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
            }
        }
        else
        {
            Date._Day--;
        }
        return Date;
    }

    void DecreaseDateByOneDay()
    {
        *this = DecreaseDateByOneDay(*this);
    }

    static clsDate DecreaseDateByOneWeek(clsDate &Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByOneWeek()
    {
        DecreaseDateByOneWeek(*this);
    }

    static clsDate DecreaseDateByXWeeks(int Weeks, clsDate &Date)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByOneWeek(Date);
        }
        return Date;
    }

    void DecreaseDateByXWeeks(int Weeks)
    {
        DecreaseDateByXWeeks(Weeks, *this);
    }

    static clsDate DecreaseDateByOneMonth(clsDate &Date)
    {
        if (Date._Month == 1)
        {
            Date._Month = 12;
            Date._Year--;
        }
        else
            Date._Month--;

        int NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);
        if (Date._Day > NumberOfDaysInCurrentMonth)
        {
            Date._Day = NumberOfDaysInCurrentMonth;
        }
        return Date;
    }

    void DecreaseDateByOneMonth()
    {
        DecreaseDateByOneMonth(*this);
    }

    static clsDate DecreaseDateByXDays(int Days, clsDate &Date)
    {
        for (int i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }
        return Date;
    }

    void DecreaseDateByXDays(int Days)
    {
        DecreaseDateByXDays(Days, *this);
    }

    static clsDate DecreaseDateByXMonths(int Months, clsDate &Date)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByOneMonth(Date);
        }
        return Date;
    }

    void DecreaseDateByXMonths(int Months)
    {
        DecreaseDateByXMonths(Months, *this);
    }

    static clsDate DecreaseDateByOneYear(clsDate &Date)
    {
        Date._Year--;
        return Date;
    }

    void DecreaseDateByOneYear()
    {
        DecreaseDateByOneYear(*this);
    }

    static clsDate DecreaseDateByXYears(int Years, clsDate &Date)
    {
        Date._Year -= Years;
        return Date;
    }

    void DecreaseDateByXYears(int Years)
    {
        DecreaseDateByXYears(Years, *this);
    }

    static clsDate DecreaseDateByOneDecade(clsDate &Date)
    {
        Date._Year -= 10;
        return Date;
    }

    void DecreaseDateByOneDecade()
    {
        DecreaseDateByOneDecade(*this);
    }

    static clsDate DecreaseDateByXDecades(int Decades, clsDate &Date)
    {
        Date._Year -= Decades * 10;
        return Date;
    }

    void DecreaseDateByXDecades(int Decades)
    {
        DecreaseDateByXDecades(Decades, *this);
    }

    static clsDate DecreaseDateByOneCentury(clsDate &Date)
    {
        Date._Year -= 100;
        return Date;
    }

    void DecreaseDateByOneCentury()
    {
        DecreaseDateByOneCentury(*this);
    }

    static clsDate DecreaseDateByOneMillennium(clsDate &Date)
    {
        Date._Year -= 1000;
        return Date;
    }

    void DecreaseDateByOneMillennium()
    {
        DecreaseDateByOneMillennium(*this);
    }

    // --- Special Date Helpers (Last Days/Months) ---
    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
    }

    bool IsLastDayInMonth()
    {
        return IsLastDayInMonth(*this);
    }

    static bool IsLastMonthInYear(int Month)
    {
        return (Month == 12);
    }

    // --- Weekends & Business Days Operations ---
    static int IsEndOfWeek(clsDate Date)
    {
        return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
    }

    int IsEndOfWeek()
    {
        return IsEndOfWeek(*this);
    }

    static bool IsWeekEnd(clsDate Date)
    {
        int DayIndex = DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
        return (DayIndex == 5 || DayIndex == 6);
    }

    bool IsWeekEnd()
    {
        return IsWeekEnd(*this);
    }

    static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

    bool IsBusinessDay()
    {
        return IsBusinessDay(*this);
    }

    static int DaysUntilTheEndOfWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
    }

    int DaysUntilTheEndOfWeek()
    {
        return DaysUntilTheEndOfWeek(*this);
    }

    static int DaysUntilTheEndOfMonth(clsDate Date1)
    {
        clsDate EndOfMontDate;
        EndOfMontDate._Day = NumberOfDaysInAMonth(Date1._Month, Date1._Year);
        EndOfMontDate._Month = Date1._Month;
        EndOfMontDate._Year = Date1._Year;

        return GetDifferenceInDays(Date1, EndOfMontDate, true);
    }

    int DaysUntilTheEndOfMonth()
    {
        return DaysUntilTheEndOfMonth(*this);
    }

    static int DaysUntilTheEndOfYear(clsDate Date1)
    {
        clsDate EndOfYearDate;
        EndOfYearDate._Day = 31;
        EndOfYearDate._Month = 12;
        EndOfYearDate._Year = Date1._Year;

        return GetDifferenceInDays(Date1, EndOfYearDate, true);
    }

    int DaysUntilTheEndOfYear()
    {
        return DaysUntilTheEndOfYear(*this);
    }

    static int CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
    {
        int Days = 0;
        while (IsDate1BeforeDate2(DateFrom, DateTo))
        {
            if (IsBusinessDay(DateFrom))
                Days++;

            DateFrom = AddOneDay(DateFrom);
        }
        return Days;
    }

    static int CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
    {
        return CalculateBusinessDays(DateFrom, DateTo);
    }

    static clsDate CalculateVacationReturnDate(clsDate DateFrom, int VacationDays)
    {
        int WeekEndCounter = 0;
        for (int i = 1; i <= VacationDays; i++)
        {
            if (IsWeekEnd(DateFrom))
                WeekEndCounter++;

            DateFrom = AddOneDay(DateFrom);
        }
        for (int i = 1; i <= WeekEndCounter; i++)
            DateFrom = AddOneDay(DateFrom);

        return DateFrom;
    }
};
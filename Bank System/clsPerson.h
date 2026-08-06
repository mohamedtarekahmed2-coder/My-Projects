#pragma once

#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:
    string FirstName, LastName, Email, Phone;

public:
// Constructors
    clsPerson(const string &first_name, const string &last_name, const string &email, const string &phone) 
                : FirstName(first_name), LastName(last_name), Email(email), Phone(phone) {}

// Getters & Setters
    string GetFirstName()
    {
        return FirstName;
    }
    void SetFirstName(const string &name)
    {
        FirstName = name;
    }

    string GetLastName()
    {
        return LastName;
    }
    void SetLastName(const string &name)
    {
        LastName = name;
    }

    string GetEmail()
    {
        return Email;
    }
    void SetEmail(const string &email_)
    {
        Email = email_;
    }

    string GetPhone()
    {
        return Phone;
    }
    void SetPhone(const string &phone_)
    {
        Phone = phone_;
    }

// Methods
    string FullName()
    {
        return FirstName + " " + LastName;
    }

};

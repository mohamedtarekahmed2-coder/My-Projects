#pragma once

#include <iostream>
#include <string>

using namespace std;

class clsPerson
{
private:
    string first_name, last_name, email, phone;

public:
// Constructors
    clsPerson(const string &first_name, const string &last_name, const string &email, const string &phone) 
                : first_name(first_name), last_name(last_name), email(email), phone(phone) {}

// Getters & Setters
    string GetFirstName()
    {
        return first_name;
    }
    void SetFirstName(const string &name)
    {
        first_name = name;
    }

    string GetLastName()
    {
        return last_name;
    }
    void SetLastName(const string &name)
    {
        last_name = name;
    }

    string GetEmail()
    {
        return email;
    }
    void SetEmail(const string &email_)
    {
        email = email_;
    }

    string GetPhone()
    {
        return phone;
    }
    void SetPhone(const string &phone_)
    {
        phone = phone_;
    }

// Methods
    string FullName()
    {
        return first_name + " " + last_name;
    }

};

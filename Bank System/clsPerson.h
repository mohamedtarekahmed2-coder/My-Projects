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
    string get_first_name()
    {
        return first_name;
    }
    void set_first_name(const string &name)
    {
        first_name = name;
    }

    string get_last_name()
    {
        return last_name;
    }
    void set_last_name(const string &name)
    {
        last_name = name;
    }

    string get_email()
    {
        return email;
    }
    void set_email(const string &email_)
    {
        email = email_;
    }

    string get_phone()
    {
        return phone;
    }
    void set_phone(const string &phone_)
    {
        phone = phone_;
    }

// Methods
    string full_name()
    {
        return first_name + " " + last_name;
    }

};

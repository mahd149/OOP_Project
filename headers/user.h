//user.h

# pragma once

#include <iostream>
#include<string>

using namespace std;

class User
{
    protected:
    string user_name;
    string user_email;
    string password;

    public :
    
    void set_username(string );
    void set_password(string );
    void set_email( string);

    string get_username();
    string get_password();
    string get_email();

    virtual bool login(string , string);
    void Register(string, string, string);


};
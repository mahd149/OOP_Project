//user.h

# pragma once
//abstract class
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
    // string user_name;
    // string user_email;
    // string password;
    //add constructor (to all the header files please)
    User(string u_name = "Unknown", string u_email = "", string pass = "");

    void set_username(string );
    void set_password(string );
    void set_email( string);

    string get_username();
    string get_password();
    string get_email();

    virtual bool login(string input_email, string input_password) = 0;    
    virtual ~User() {}


};
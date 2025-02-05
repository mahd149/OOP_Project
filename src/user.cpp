// user.cpp
#include "../headers/user.h"


User::User(string u_name, string u_email, string pass ) :
user_name(u_name), user_email(u_email), password(pass) { }

// Implement setters
void User::set_username(string username) {
    this->user_name = username;
}

void User::set_password(string password) {
    this->password = password;
}

void User::set_email(string email) {
    this->user_email = email;
}

// Implement getters
string User::get_username() {
    return user_name;
}

string User::get_password() {
    return password;
}

string User::get_email() {
    return user_email;
}
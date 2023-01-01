// A couple of useless exceptions redefined here, 
// just for show

#pragma once
#include <exception>

class MessagesListException: public std::exception
{
public:
    const char* what() const noexcept override // virtual const char* what() const throw()
    {
        return "Shit has happened, man: you're trying to read an empty message queue";
    }
}; // myexception;

class NewUserLoginException : public std::exception
{
public:
    const char* what() const noexcept override // virtual const char* what() const throw()
    {
        return "Damn! Someone is already working under your login. Try another one";
    }
}; // newUserLoginException;

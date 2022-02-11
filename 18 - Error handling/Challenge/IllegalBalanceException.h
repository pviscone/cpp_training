#ifndef __ILLEGAL_BALANCE_EXCEPTION_H__
#define __ILLEGAL_BALANCE_EXCEPTION_H__
#include <exception>
class IllegalBalanceException : public std::exception {

    public:
        virtual const char* what() const noexcept;
        IllegalBalanceException() {}
        ~IllegalBalanceException() {}
    };
#endif // __ILLEGAL_BALANCE_EXCEPTION_H__

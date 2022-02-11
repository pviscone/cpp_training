#ifndef _INSUFFICENT_FUNDS_EXCEPTION_H_
#define _INSUFFICENT_FUNDS_EXCEPTION_H_

#include <exception>

class InsufficentFundsException : public std::exception {
    public:
        virtual const char* what() const noexcept;
        InsufficentFundsException() {}
        ~InsufficentFundsException() {}
};




#endif // _INSUFFICENT_FUNDS_EXCEPTION_H_

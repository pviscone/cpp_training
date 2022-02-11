#include "InsufficentFundsException.h"

const char* InsufficentFundsException::what() const noexcept {
    return "Insufficent funds exception";
}
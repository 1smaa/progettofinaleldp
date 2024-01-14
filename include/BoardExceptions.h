#ifndef BOARDEXCEPTIONS_H
#define BOARDEXCEPTIONS_H

#include <stdexcept>
/*
*   CIAN IRENE
*/

class PositionError : std::out_of_range {
public:
    explicit PositionError(int x) : std::out_of_range{"Posizione "+std::to_string(this->error_value)+" non valida."}, error_value{x} {};
    int error_value;
    const char* what() const noexcept override { return ("Posizione "+std::to_string(this->error_value)+" non valida.").c_str(); }
};

class PlayerError: std::runtime_error{
public:
    explicit PlayerError(std::string s) : std::runtime_error{s}, error_value{s}{};
    std::string error_value;
    const char* what() const noexcept override { return this->error_value.c_str(); }
};

class BoxError : std::runtime_error{
public:
    explicit BoxError(std::string s) : std::runtime_error{s}, error_value{s}{};
    std::string error_value;
    const char* what() const noexcept override { return this->error_value.c_str(); }
};

#endif
#ifndef ABSTRACT_TEXT_H
#define ABSTRACT_TEXT_H

#include "containers.h"

class Abstract_text{
public:
    virtual unsigned long count_symbols() const = 0;
    virtual unsigned long count_words() const = 0;
    virtual int print([[maybe_unused]] const DisplayParameters& display) const = 0;
    virtual ~Abstract_text() {};
};

#endif
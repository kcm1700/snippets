#pragma once

// with C++11, one may use 'delete' keyword to make compiler not generate method automatically.
class NonCopyable
{
protected:
    NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable & operator=(const NonCopyable&);
};



#include <functional>

class ScopedFinalizer : NonCopyable
{
    std::function<void()> _function;
    bool _cancel;

public:
    ScopedFinalizer(std::function<void()> f) : _function(f), _cancel(false) { }
    ~ScopedFinalizer()
    {
        if (_cancel) return;
        _function();
    }

    void Cancel() { _cancel = true; }
};



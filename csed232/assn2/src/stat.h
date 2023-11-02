#ifndef STAT_H
#define STAT_H

#include <string>

class stat {
public:
    virtual std::size_t num_stats() const noexcept = 0;
    virtual std::wstring title() const noexcept = 0;
    virtual std::wstring const* stat_names() const noexcept = 0;
    virtual std::wstring const* stats() const noexcept  = 0;
    virtual bool ranked() const noexcept = 0;
};

#endif // ifndef STAT_H
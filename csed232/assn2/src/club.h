#ifndef CLUB_H
#define CLUB_H

#include <string>
#include "option.hpp"

class club {
public:
    std::wstring name;
    std::size_t won;
    std::size_t lost;
    std::size_t tied;
    
    club(std::wstring const& _name, std::size_t _won, std::size_t _lost, std::size_t _tied);
    std::size_t games();
    option<float> gb(club const& leading);
    option<float> pct();
};

#endif // ifndef CLUB_H
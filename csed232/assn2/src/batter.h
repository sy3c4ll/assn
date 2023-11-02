#ifndef BATTER_H
#define BATTER_H

#include "stat.h"
#include "option.hpp"

class batter : public stat {
public:
    std::wstring name;
    std::wstring club;
    std::size_t ab;
    std::size_t hit;
    std::size_t bb;
    std::size_t db;
    std::size_t sf;

    batter(std::wstring const& _name, std::wstring const& _club, std::size_t _ab, std::size_t _hit, std::size_t _bb, std::size_t _db, std::size_t _sf) noexcept;
    option<float> ba() const noexcept;
    option<float> obp() const noexcept;
    bool operator==(batter const& other) const noexcept;
    bool operator!=(batter const& other) const noexcept;
    bool operator<(batter const& other) const noexcept;
    bool operator>(batter const& other) const noexcept;
    bool operator<=(batter const& other) const noexcept;
    bool operator>=(batter const& other) const noexcept;

    std::size_t num_stats() const noexcept override;
    std::wstring title() const noexcept override;
    std::wstring const* stat_names() const noexcept override;
    std::wstring const* stats() const noexcept override;
    bool ranked() const noexcept override;
};

#endif // ifndef BATTER_H
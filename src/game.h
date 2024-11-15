#ifndef GAME_H
#define GAME_H

#include "utility.h"
#include <vector>

class Game final
{
    using mines_field_t = std::vector< std::vector <bool>>;
    using settings_t    = utility::GameModeFieldSettings;

public:
    Game();

public:
    void BuildMines(const settings_t&);
    bool IsMined(int x, int y) const;

    const mines_field_t& GetField()const noexcept;
    int CalcMinesAroundCell(const int x,const int y)const;

private:
    void FillField();

private:
    mines_field_t mines_field_ = {};
    settings_t    settings_    = {};
};

#endif // GAME_H

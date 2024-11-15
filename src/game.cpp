#include "game.h"
#include <QRandomGenerator>
#include <algorithm>

Game::Game()
{
}

void Game::BuildMines(const settings_t& settings)
{
    settings_ = settings;
    FillField();
}

void Game::FillField()
{
    auto rg = QRandomGenerator::global();

    mines_field_.clear();

    int mines_count = settings_.mines;

    mines_field_t vec (settings_.width, std::vector<bool>(settings_.height, false));
    mines_field_ = vec;

    while(mines_count>0){
        int x = rg->bounded(0,settings_.width);
        int y = rg->bounded(0,settings_.height);

        if(mines_field_[x][y] == true){
            continue;
        }

        mines_field_[x][y] = true;
        --mines_count;
    }
}

bool Game::IsMined(int x, int y) const
{
    return mines_field_[x][y];
}

const Game::mines_field_t& Game::GetField() const noexcept
{
    return mines_field_;
}

int Game::CalcMinesAroundCell(const int x, const int y) const
{
    int count = 0;

    for(int x_t = x-1; x_t < x+2; ++x_t){
        for(int y_t = y-1; y_t < y+2; ++y_t){
            if(x_t < 0 || x_t >= settings_.width  ||
               y_t < 0 || y_t >= settings_.height ){
                continue;
            }
            if(mines_field_[x_t][y_t])++count;
        }
    }

    return count;
}


#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

namespace utility
{
    struct GameModeFieldSettings{
        int height;
        int width;
        int mines;
    };

    struct ScoreData{
        QString name = "";
        int easy = 0;
        int medium = 0;
        int hard = 0;
    };

    enum class GameOver{
        WIN,
        LOST
    };

    enum class GameMode{
        EASY,
        MEDIUM,
        HARD,
        CUSTOM
    };

    enum class SortScoresMode{
        NAME,
        EASY,
        MEDIUM,
        HARD
    };

    inline const QString GameModeById [3] = {"Easy", "Medium", "Hard"};

}//namespace utility;

namespace style
{
    inline const QString forest = "QWidget{"
                                        "background-color: #0A523C;"
                                        "color: white;"
                                        "font: 700 14pt}"
                                  "QPushButton{"
                                        "background-color: #207E62;"
                                        "border-color: #2A5F4F; "
                                        "border-style: solid; "
                                        "border-width: 1px;}"
                                  "QPushButton:hover{"
                                        "background-color: #70BFA7;"
                                        "border-color: #2A5F4F; "
                                        "border-style: solid; "
                                        "border-width: 1px;}"
                                  "QPushButton:pressed{"
                                        "background-color: #0A523C;"
                                        "border-color: #2A5F4F; "
                                        "border-style: solid; "
                                        "border-width: 1px;}"
                                  "QPushButton:disabled"
                                        "{background-color: #8D917A;"
                                        "border-style: solid; "
                                        "border-width: 1px; "
                                        "border-color: #6B6D60;}";

    inline const QString space = "QWidget{background-color: #23123C;"
                                        "color: white;"
                                        "font: 700 14pt}"
                                 "QPushButton{"
                                         "background-color: #46365C;"
                                         "border-color: #393045; "
                                         "border-style: solid; "
                                         "border-width: 1px; "
                                         "color: white;}"
                                 "QPushButton:hover{"
                                         "background-color: #8E78AE;"
                                         "border-color: #5B5B7A; "
                                         "border-style: solid; "
                                         "border-width: 1px;}"
                                 "QPushButton:pressed{"
                                         "background-color: #393045;"
                                         "border-color: #393045; "
                                         "border-style: solid; "
                                         "border-width: 1px;}"
                                 "QPushButton:disabled{"
                                         "background-color: #6C6CA3;"
                                         "border-color: #5B5B7A;"
                                         "border-style: solid;"
                                         "border-width: 1px;}";

    inline const QString classic = "QWidget{"
                                        "background-color: #6B6B6B;"
                                        "font: 700 14pt}"
                                   "QPushButton{"
                                        "background-color: #C0C0C0;}"
                                   "QPushButton:hover{"
                                        "background-color: #DEDEDE}"
                                   "QPushButton:pressed{"
                                        "background-color: #8E8E8E;}"
                                   "QPushButton:disabled{"
                                        "background-color: #B4B4B4; "
                                        "border-color: #8E8E8E; "
                                        "border-style: solid; "
                                        "border-width: 1px;}";


    inline const QString forest_utility = "QPushButton{"
                                                "background-color: #207E62;"
                                                "border-style: inset; "
                                                "border-width: 2px; "
                                                "border-radius: 10px; "
                                                "border-color: #2A5F4F;}"
                                          "QPushButton:hover{"
                                                "background-color: #70BFA7;}"
                                          "QPushButton:pressed{"
                                                "background-color: #0A3A2A;}"
                                          "QWidget{"
                                                "color: rgb(220,220,220);"
                                                "font: 800 8pt;"
                                                "padding: 0 0 2px 0}";

    inline const QString space_utility = "QPushButton{"
                                                "background-color: #46365C;"
                                                "border-style: inset; "
                                                "border-width: 2px; "
                                                "border-radius: 10px; "
                                                "border-color: #130627;}"
                                         "QPushButton:hover{"
                                                "background-color: #8E78AE;}"
                                         "QPushButton:pressed{"
                                                "background-color: #130627;}"
                                         "QWidget{"
                                                "color:rgb(220,220,220);"
                                                "font: 800 8pt;"
                                                "padding: 0 0 2px 0}";

    inline const QString classic_utility = "QWidget{"
                                                "color:rgb(0,0,0);"
                                                "font: 800 8pt;"
                                                "padding: 0 0 2px 0;}"
                                           "QPushButton{"
                                                "background-color: #BDBDBD;"
                                                "border-style: inset; "
                                                "border-width: 2px; "
                                                "border-radius: 10px; "
                                                "border-color: #7B7B7B;}"
                                           "QPushButton:hover{"
                                                "background-color: #DEDEDE;}"
                                           "QPushButton:pressed{"
                                                "background-color: #7B7B7B;}";

    inline const QString mines_around_1_color = "QWidget{color: #0000C8;}";
    inline const QString mines_around_2_color = "QWidget{color: #006400;}";
    inline const QString mines_around_3_color = "QWidget{color: #C80000;}";
    inline const QString mines_around_4_color = "QWidget{color: #000064;}";
    inline const QString mines_around_5_color = "QWidget{color: #640000;}";
    inline const QString mines_around_6_color = "QWidget{color: #006464;}";
    inline const QString mines_around_7_color = "QWidget{color: black  ;}";
    inline const QString mines_around_8_color = "QWidget{color: #640064;}";

    inline const QString icon_bomb = "💣";
    inline const QString icon_explosive = "💥";
    inline const QString icon_flag = "🚩";
    inline const QString icon_game_started = "🙂";
    inline const QString icon_game_win = "😎";
    inline const QString icon_game_lost = "😵";

    inline constexpr int MIN_SCRN_WIDTH  = 460;
    inline constexpr int MIN_SCRN_HEIGHT  = 460;

    inline constexpr int MAX_SCRN_WIDTH  = 1900;
    inline constexpr int MAX_SCRN_HEIGHT  = 1000;

    inline constexpr int SCRN_SPACING_WIDTH  = 40;
    inline constexpr int SCRN_SPACING_HEIGHT = 200;

}//namespace style_window;

#endif // UTILITY_H

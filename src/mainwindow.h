#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "utility.h"
#include "scores.h"
#include "game.h"
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QGridLayout>
#include <QPushButton>
#include <QLayout>
#include <QRegularExpression>
#include <QRandomGenerator>
#include <algorithm>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    static constexpr int button_size_min_  = 25;
    static constexpr int button_size_max_  = 55;
    static constexpr int button_size_step_ = 15;

    static constexpr int buttons_max_width_  = 60;
    static constexpr int buttons_max_height_ = 30;

    static constexpr int buttons_min_width_  = 2;
    static constexpr int buttons_min_height_ = 2;

    static constexpr int mines_max_ = buttons_max_width_ * buttons_max_height_ - 1;
    static constexpr int mines_min_ = 1;

    static constexpr int score_default_step_ = 10;

    static constexpr  utility::GameModeFieldSettings settings_easy_   = {10,10,10};
    static constexpr  utility::GameModeFieldSettings settings_medium_ = {15,15,33};
    static constexpr  utility::GameModeFieldSettings settings_hard_   = {20,20,80};

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

private:

    Game         game_;
    Scores       scores_ = Scores("save.json");
    QGridLayout* layout_;
    QTimer*      timer_;
    QWidget*     widget_field_;

    int game_time_          = 0;
    int user_score_         = 0;
    int score_step_         = 0;
    int cells_marked_       = 0;
    int reamins_demine_     = 0;
    bool game_started_      = false;
    bool game_over_         = false;
    int button_size_        = button_size_min_;
    QString nickname_       = "Unknown";

    QString style_window_   = style::forest;
    QString style_utility_  = style::forest_utility;

    utility::GameModeFieldSettings game_settings_ = settings_easy_;
    utility::GameMode game_mode_                  = utility::GameMode::EASY;

private:

    void InitGame();
    void BuildGame();
    void StartGame();
    void ResetGame();
    void GameOver(const utility::GameOver mode);

    void ChangeStyle();
    void ResizeButtons();
    void ResizeWindow();

    void SetGameSettings();
    void SetCustomGameSettings();
    void ShowScores();

    void MarkCell(QPushButton* button);
    void OpenEmptyCells(const int x,const int y);
    void OpenCell(QPushButton* button,const int x, const int y);

    static QString GetCellColor(const int mines_around);

    void DeleteButtons();

    void EasterEgg(const int x, const int y);

private slots:

    void TimerSlot();
    void on_pushButton_Start_clicked();
    void on_pushButton_Settings_clicked();
    void on_pushButtonSettingsExit_clicked();
    void on_pushButtonScoresExit_clicked();
    void on_pushButtonScroes_clicked();
    void on_pushButtonNewGame_clicked();
    void on_pushButtonSizeMinus_clicked();
    void on_pushButtonSizePlus_clicked();
    void on_radioButtonStyleForest_clicked();
    void on_radioButtonStyleSpace_clicked();
    void on_radioButtonStyleClassic_clicked();
    void on_pushButtonScoreSortName_clicked();
    void on_pushButtonScoreSortEasy_clicked();
    void on_pushButtonScoreSortMedium_clicked();
    void on_pushButtonScoreSortHard_clicked();
};

#endif // MAINWINDOW_H

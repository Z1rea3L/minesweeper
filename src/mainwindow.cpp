#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitGame();
}

MainWindow::~MainWindow()
{
    DeleteButtons();
    delete ui;
}

// utility ================================================

void MainWindow::InitGame()
{
    ui->widget_scores->hide();
    ui->widget_settings->hide();

    ui->radioButtonEasy->setChecked(true);
    ui->radioButtonStyleForest->setChecked(true);
    ui->pushButton_Start->setText(style::icon_game_started);

    this->adjustSize();

    widget_field_ = new QWidget();
    timer_        = new QTimer(this);
    layout_       = new QGridLayout();

    layout_->setSpacing(0);
    layout_->setAlignment(Qt::AlignCenter);

    widget_field_->setLayout(layout_);
    ui->scrollArea->setWidget(widget_field_);

    connect(timer_, SIGNAL(timeout()), this, SLOT(TimerSlot()));

    for (int x = 0; x < buttons_max_width_; ++x) {
        for (int y = 0; y < buttons_max_height_; ++y) {

            auto button = new QPushButton();
            layout_->addWidget(button, y, x);

            connect(button, &QPushButton::clicked, [=]() {
                OpenCell(button, x, y);
            });

            button->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(button, &QPushButton::customContextMenuRequested, this, [=]() {
                MarkCell(button);
            });
        }
    }

    BuildGame();
    ChangeStyle();
}

void MainWindow::DeleteButtons()
{
    QLayoutItem *item;
    while ((item = layout_->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        delete item;

        if (widget) {
            widget->deleteLater();
        }
    }
}

//game ================================================

void MainWindow::BuildGame()
{
    ResetGame();
    game_.BuildMines(game_settings_);

    for (int x = 0; x < buttons_max_width_; ++x) {
        for (int y = 0; y < buttons_max_height_; ++y) {
            auto button = qobject_cast<QPushButton*>(layout_->itemAtPosition(y, x)->widget());

            if(x < game_settings_.width && y < game_settings_.height){
                button->setFixedSize(QSize(button_size_, button_size_));
                button->setEnabled(true);
                button->setText("");
                button->show();
            }else{
                button->hide();
            }
        }
    }
}

void MainWindow::ResetGame(){
    game_over_ = false;
    game_started_ = false;
    timer_->stop();

    user_score_ = 0;
    game_time_ = 0;
    score_step_ = score_default_step_;
    cells_marked_ = game_settings_.mines;
    reamins_demine_ = game_settings_.height * game_settings_.width - game_settings_.mines;

    ui->label_Time->setText("00 : 00");
    ui->label_Score->setText(QString::number(user_score_));
    ui->pushButton_Start->setText(style::icon_game_started);
    ui->label_Mines_Left->setText(QString::number(cells_marked_));
}

void MainWindow::StartGame()
{
    timer_->start(1000);
    game_started_ = true;
}

void MainWindow::GameOver(const utility::GameOver mode){
    timer_->stop();
    game_over_    = true;
    game_started_ = false;

    if(user_score_ == 0) ui->label_Score->setText("ha-ha :)");

    if(mode == utility::GameOver::WIN){
        scores_.AddScore(nickname_, game_mode_, user_score_);
        ui->pushButton_Start->setText(style::icon_game_win);
        ui->label_Mines_Left->setText("0");

    }else if(mode == utility::GameOver::LOST){
        ui->pushButton_Start->setText(style::icon_game_lost);
    }

    auto mines_field = game_.GetField();
    for(int x = 0; x < static_cast<int>(mines_field.size()); ++x){
        for(int y = 0; y < static_cast<int>(mines_field[x].size()); ++y){
            if(mines_field[x][y]){
                auto button = qobject_cast<QPushButton*>(layout_->itemAtPosition(y, x)->widget());

                if(mode == utility::GameOver::WIN){
                    button->setText(style::icon_flag);
                }else{
                    button->setText(style::icon_explosive);
                }
            }
        }
    }
}

void MainWindow::OpenCell(QPushButton* button, const int x, const int y){
    if(game_over_ || button->text() == style::icon_flag) return;

    if(QApplication::keyboardModifiers() & Qt::ShiftModifier && !game_started_){
        EasterEgg(x, y);
        return;
    }

    if(!game_started_) StartGame();

    if(game_.IsMined(x, y)){
        GameOver(utility::GameOver::LOST);
        button->setText(style::icon_bomb);
        return;
    }

    --reamins_demine_;
    button->setEnabled(false);
    user_score_ += score_step_;
    ui->label_Score->setText(QString::number(user_score_));
    const int mines = game_.CalcMinesAroundCell(x,y);

    if(mines == 0){
        OpenEmptyCells(x,y);
    }else{
        button->setText(QString::number(mines));
        button->setStyleSheet(GetCellColor(mines));
    }

    if(reamins_demine_ == 0){
        GameOver(utility::GameOver::WIN);
    }
}

void MainWindow::OpenEmptyCells(const int x, const int y)
{
    for(int x_t = x-1; x_t < x+2; ++x_t){
        for(int y_t = y-1; y_t < y+2; ++y_t){

            if(x_t < 0 || x_t >= game_settings_.width  ||
               y_t < 0 || y_t >= game_settings_.height ||
               game_.IsMined(x_t, y_t) || (x_t == x && y_t == y)){
                continue;
            }

            auto button = qobject_cast<QPushButton*>(layout_->itemAtPosition(y_t, x_t)->widget());
            auto mines = game_.CalcMinesAroundCell(x_t, y_t);

            if(button->text() == style::icon_flag || !button->isEnabled()){
                continue;
            }

            button->setEnabled(false);
            --reamins_demine_;

            if(mines == 0){
                OpenEmptyCells(x_t, y_t);
            }else{
                button->setText(QString::number(mines));
                button->setStyleSheet(GetCellColor(mines));
            }
        }
    }
}


void MainWindow::MarkCell(QPushButton* button){
    if(game_over_) return;
    if(!game_started_) StartGame();

    if(button->text() == style::icon_flag){
        button->setText("");
        ++cells_marked_;
        ui->label_Mines_Left->setText(QString::number(cells_marked_));

    }else{
        button->setText(style::icon_flag);
        --cells_marked_;
        ui->label_Mines_Left->setText(QString::number(cells_marked_));
    }
}

QString MainWindow::GetCellColor(const int mines_around){
    switch (mines_around){
        case 1:
            return style::mines_around_1_color;
        case 2:
            return style::mines_around_2_color;
        case 3:
            return style::mines_around_3_color;
        case 4:
            return style::mines_around_4_color;
        case 5:
            return style::mines_around_5_color;
        case 6:
            return style::mines_around_6_color;
        case 7:
            return style::mines_around_7_color;
        case 8:
            return style::mines_around_8_color;
    }

    return "";
}

void MainWindow::SetGameSettings()
{
    const QString input_nickname = ui->lineEditUserName->text();
    input_nickname.isEmpty() ? nickname_ = "Unknown" : nickname_ = input_nickname;

    if(ui->radioButtonEasy->isChecked()){
        game_settings_ = settings_easy_;
        game_mode_ = utility::GameMode::EASY;
    }
    else if(ui->radioButtonMedium->isChecked()){
        game_settings_ = settings_medium_;
        game_mode_ = utility::GameMode::MEDIUM;
    }
    else if(ui->radioButtonHard->isChecked()){
        game_settings_ = settings_hard_;
        game_mode_ = utility::GameMode::HARD;
    }
    else{
        SetCustomGameSettings();
        game_mode_ = utility::GameMode::CUSTOM;

    }
}

void MainWindow::SetCustomGameSettings()
{
    const QString input_height = ui->lineEditHeight->text();
    const QString input_width  = ui->lineEditWidth->text();
    const QString input_mines  = ui->lineEditMines->text();

    static const QRegularExpression re("^[0-9]*$");
    if (!re.match(input_height).hasMatch() || !re.match(input_width).hasMatch() || !re.match(input_mines).hasMatch()) {
        return;
    }else{
        game_settings_.width = std::clamp(input_width.toInt(), buttons_min_width_, buttons_max_width_);
        game_settings_.height = std::clamp(input_height.toInt(), buttons_min_height_, buttons_max_height_);
        game_settings_.mines = std::clamp(input_mines.toInt(), mines_min_, game_settings_.width * game_settings_.height - 1);

        ui->lineEditWidth->setText(QString::number(game_settings_.width));
        ui->lineEditHeight->setText(QString::number(game_settings_.height));
        ui->lineEditMines->setText(QString::number(game_settings_.mines));
    }
}

//style ================================================

void MainWindow::ResizeWindow()
{
    button_size_ = button_size_min_;
    widget_field_->setStyleSheet("QWidget{font: 700 " + QString::number(button_size_/2) + "pt;}");

    int width = std::max(style::MIN_SCRN_WIDTH, button_size_ * game_settings_.width + style::SCRN_SPACING_WIDTH);
    int height = std::max(style::MIN_SCRN_HEIGHT, button_size_ * game_settings_.height + style::SCRN_SPACING_HEIGHT);

    this->setMinimumSize(width, height);
    this->adjustSize();
}

void MainWindow::ResizeButtons()
{
    for (int x = 0; x < game_settings_.width; ++x) {
        for (int y = 0; y < game_settings_.height; ++y) {
            auto button = qobject_cast<QPushButton*>(layout_->itemAtPosition(y, x)->widget());
            button->setFixedSize(QSize(button_size_, button_size_));
        }
    }

    widget_field_->setStyleSheet("QWidget{font: 700 " + QString::number(button_size_/2) + "pt;}");
}

void MainWindow::ChangeStyle()
{
    this->setStyleSheet(style_window_);
    ui->widget_utility->setStyleSheet(style_utility_);
}

void MainWindow::ShowScores(){
    ui->label_Scores_List_Name->setText("");
    ui->label_Scores_List_Easy->setText("");
    ui->label_Scores_List_Medium->setText("");
    ui->label_Scores_List_Hard->setText("");

    for(const auto& score_data : scores_.GetScores()){
        ui->label_Scores_List_Name->setText(ui->label_Scores_List_Name->text() + score_data.name  + "\n");

        ui->label_Scores_List_Easy->setText(ui->label_Scores_List_Easy->text() + QString::number(score_data.easy)  + "\n");

        ui->label_Scores_List_Medium->setText(ui->label_Scores_List_Medium->text() + QString::number(score_data.medium)  + "\n");

        ui->label_Scores_List_Hard->setText(ui->label_Scores_List_Hard->text() + QString::number(score_data.hard) + "\n" );
    }
}

//he-he ================================================

void MainWindow::EasterEgg(const int x, const int y)
{
    timer_->stop();
    game_over_ = true;

    auto button = qobject_cast<QPushButton*>(layout_->itemAtPosition(y, x)->widget());
    button -> setEnabled(false);
    button -> setText("9");
    button -> setStyleSheet("QWidget{color: rgb(255,255,0);}");
    timer_->stop();
    ui->pushButton_Start->setText("💀");
    ui->label_Score->setText("👁️");
    ui->label_Time->setText("👁️");
}

//slots ================================================

void MainWindow::TimerSlot(){
    ++game_time_;

    ui->label_Time->setText(QString::number(game_time_ / 600)     +
                            QString::number(game_time_ / 60 % 10) +
                            " : "                                 +
                            QString::number(game_time_ % 60 / 10) +
                            QString::number(game_time_ % 10));

    if(score_step_ > 1 && game_time_ % 60 == 0){
        --score_step_;
    }
}

void MainWindow::on_pushButton_Start_clicked()
{
    BuildGame();
}


void MainWindow::on_pushButton_Settings_clicked()
{
    ui->widget_settings->show();
    ui->widget_default->hide();
}

void MainWindow::on_pushButtonScroes_clicked()
{
    ui->widget_scores->show();
    ui->widget_default->hide();
    ShowScores();
}


void MainWindow::on_pushButtonSettingsExit_clicked()
{
    ui->widget_settings->hide();
    ui->widget_default->show();
}


void MainWindow::on_pushButtonScoresExit_clicked()
{
    ui->widget_scores->hide();
    ui->widget_default->show();
}

void MainWindow::on_pushButtonNewGame_clicked()
{
    ui->widget_settings->hide();
    ui->widget_default->show();

    SetGameSettings();
    ResizeWindow();
    BuildGame();
}

void MainWindow::on_pushButtonSizeMinus_clicked()
{
    if(button_size_ == button_size_min_)return;
    button_size_ -= button_size_step_;

    ResizeButtons();
}


void MainWindow::on_pushButtonSizePlus_clicked()
{
    if(button_size_ == button_size_max_)return;
    button_size_ += button_size_step_;

    ResizeButtons();
}

void MainWindow::on_radioButtonStyleForest_clicked()
{
    style_window_ = style::forest;
    style_utility_= style::forest_utility;

    ChangeStyle();
}

void MainWindow::on_radioButtonStyleSpace_clicked()
{
    style_window_ = style::space;
    style_utility_= style::space_utility;

    ChangeStyle();
}

void MainWindow::on_radioButtonStyleClassic_clicked()
{
    style_window_ = style::classic;
    style_utility_= style::classic_utility;

    ChangeStyle();
}

void MainWindow::on_pushButtonScoreSortName_clicked()
{
    scores_.SortScores(utility::SortScoresMode::NAME);
    ShowScores();
}


void MainWindow::on_pushButtonScoreSortEasy_clicked()
{
    scores_.SortScores(utility::SortScoresMode::EASY);
    ShowScores();
}


void MainWindow::on_pushButtonScoreSortMedium_clicked()
{
    scores_.SortScores(utility::SortScoresMode::MEDIUM);
    ShowScores();
}


void MainWindow::on_pushButtonScoreSortHard_clicked()
{
    scores_.SortScores(utility::SortScoresMode::HARD);
    ShowScores();
}

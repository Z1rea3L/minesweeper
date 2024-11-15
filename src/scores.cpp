#include "scores.h"

Scores::Scores(QString file_name)
{
    file_.setFileName(file_name);

    if (!file_.open(QIODevice::ReadWrite)) {
        return;
    }

    QByteArray jsonData = file_.readAll();
    data_ =  QJsonDocument::fromJson(jsonData);

    file_.close();
    FillScoresVec();
}

void Scores::AddScore(const QString& nickname, const utility::GameMode mode, const int score)
{
    if(mode == utility::GameMode::CUSTOM) return;

    QJsonObject names = data_.object();
    QJsonObject scores;

    if(names.contains(nickname)){
        scores = names[nickname].toObject();

        if(scores[utility::GameModeById[static_cast<int>(mode)]].toInt() > score)return;

        scores[utility::GameModeById[static_cast<int>(mode)]] = score;
        names[nickname] = scores;

    }else{
        scores["Easy"]   = 0;
        scores["Medium"] = 0;
        scores["Hard"]   = 0;
        scores[utility::GameModeById[static_cast<int>(mode)]] = score;
        names[nickname] = scores;
    }

    QJsonDocument new_data(names);
    data_ = new_data;

    if (!file_.open(QIODevice::WriteOnly)) {
        return;
    }

    file_.write(data_.toJson());
    file_.close();

    FillScoresVec();
}

void Scores::FillScoresVec()
{
    scores_.clear();
    const auto names = data_.object();

    for(const auto& nickname : names.keys()){
        auto scores = names[nickname].toObject();
        utility::ScoreData score_data;

        score_data.name = nickname;
        score_data.easy = scores["Easy"].toInt();
        score_data.medium = scores["Medium"].toInt();
        score_data.hard = scores["Hard"].toInt();

        scores_.push_back(score_data);
    }

}

const std::vector<utility::ScoreData>& Scores::GetScores() const
{
    return scores_;
}

void Scores::SortScores(const utility::SortScoresMode mode)
{
    std::sort(scores_.begin(),scores_.end(),[&mode](const auto lhs, const auto rhs){
        switch(mode){
            case utility::SortScoresMode::NAME:
                return lhs.name < rhs.name;
                break;
            case utility::SortScoresMode::EASY:
                return lhs.easy > rhs.easy;
                break;
            case utility::SortScoresMode::MEDIUM:
                return lhs.medium > rhs.medium;
                break;
            case utility::SortScoresMode::HARD:
                return lhs.hard > rhs.hard;
                break;
        }
    });
}


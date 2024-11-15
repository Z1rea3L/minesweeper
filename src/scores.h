#ifndef SCORES_H
#define SCORES_H

#include "utility.h"
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <vector>
#include <algorithm>

class Scores final
{
public:
    Scores(QString file_name);

    void AddScore(const QString& nickname, const utility::GameMode mode, const int score);

    const std::vector<utility::ScoreData>& GetScores() const;

    void SortScores(const utility::SortScoresMode mode);

private:
    QJsonDocument data_;
    std::vector <utility::ScoreData> scores_;
    QFile file_;
    void FillScoresVec();
};

#endif // SCORES_H

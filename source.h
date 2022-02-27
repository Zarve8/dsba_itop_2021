#ifndef SOURCE_H
#define SOURCE_H

#include "gamelist.h"
#include <fstream>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QMessageBox>

class Source
{ 
    bool is_opened = false;
    QString filename;
    QString favdir = "Favourites.csv";

public:
    Source();
    ~Source();
    int Load(QString filename);
    int AddNew(std::string name, std::string year, std::string platform);
    int SimpleSearch(std::string name, GameList &gl);
    int AdvancedSearch(std::string year, std::string platform, std::string genre, std::string publisher, GameList &gl);
    int AddFavourite(std::string name, std::string year, std::string publisher, std::string row);
    int GetFavourites(GameList &gl, bool sort=false);
    int DeleteFavourite(std::string name, int ind);
};

#endif // SOURCE_H

#ifndef GAMELIST_H
#define GAMELIST_H

#include <vector>
#include <istream>
#include <QString>

class GameList
{
public:
    GameList();
    void Add_Game(std::string name, std::string year, std::string platform, std::string row);
    void Sort();
    int num = 0;
    std::vector<std::string> namelist = std::vector<std::string>(0);
    std::vector<std::string> yearlist = std::vector<std::string>(0);
    std::vector<std::string> platformlist = std::vector<std::string>(0);
    std::vector<std::string> rows = std::vector<std::string>(0);
};

#endif // GAMELIST_H

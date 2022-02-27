#include "gamelist.h"

#include<vector>

GameList::GameList()
{

}

void GameList::Add_Game(std::string name, std::string year, std::string platform, std::string row){
    this->namelist.push_back(name);
    this->yearlist.push_back(year);
    this->platformlist.push_back(platform);
    this->rows.push_back(row);
    this->num++;
}

void GameList::Sort(){
    bool x = true;
    while(x){
         x = false;
         for(int i = 0; i < this->num-1; i++){
             if(namelist[i]>namelist[i+1]){
                 std::string s = namelist[i];
                 namelist[i] = namelist[i+1];
                 namelist[i+1] = s;
                 s = yearlist[i];
                 yearlist[i] = yearlist[i+1];
                 yearlist[i+1] = s;
                 s = platformlist[i];
                 platformlist[i] = platformlist[i+1];
                 platformlist[i+1] = s;
                 s = rows[i];
                 rows[i] = rows[i+1];
                 rows[i+1] = s;
                 x = true;
             }
             if(namelist[i] == namelist[i+1] && yearlist[i]>yearlist[i+1]){
                 std::string s = namelist[i];
                 namelist[i] = namelist[i+1];
                 namelist[i+1] = s;
                 s = yearlist[i];
                 yearlist[i] = yearlist[i+1];
                 yearlist[i+1] = s;
                 s = platformlist[i];
                 platformlist[i] = platformlist[i+1];
                 platformlist[i+1] = s;
                 s = rows[i];
                 rows[i] = rows[i+1];
                 rows[i+1] = s;
                 x = true;
             }
         }
    }
}

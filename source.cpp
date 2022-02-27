#include "source.h"

Source::Source()
{
    std::ifstream f;
    f.open(this->favdir.toStdString());
    if(!f.is_open()){
        std::ofstream fout;
        fout.open(this->favdir.toStdString());
        fout.close();
    }
    else{
        f.close();
    }

}

int Source::Load(QString filename){
    if(is_opened){return 1;}
    QFile fin(filename);
    if(fin.open(QFile::ReadWrite | QFile::Text)){
        fin.close();
        this->is_opened = true;
        this->filename = filename;
        return 0;
    }
    else{
        return 1;
    }
}

Source::~Source(){

}


int Source::AddNew(std::string name, std::string year, std::string platform){
    QFile fin(this->filename);
    if(!fin.open(QFile::ReadWrite | QFile::Text)) return 1;
    if(!(name!="" && year!="" && platform!="")) return 1;
    QTextStream out(&fin);
    out.readAll();
    QString s = "\n"+QString::fromStdString(name)+","+QString::fromStdString(platform)+","+QString::fromStdString(year);
    out.operator<<(s);
    fin.close();
    return 0;
}


int Source::SimpleSearch(std::string name, GameList& gl){
    QFile fin(this->filename);
    if(!fin.open(QFile::ReadOnly | QFile::Text)) return 1;
    if(name=="") return 1;
    QTextStream in(&fin);
    QString text = in.readAll();
    QStringList rows = text.split("\n");
    int n = rows.size();
    int i = 0;
    while(i<n){
        QStringList words = rows[i].split(",");
        if(words[0].toStdString()==name){
            gl.Add_Game(words[0].toStdString(), words[2].toStdString(), words[1].toStdString(), rows[i].toStdString());
            fin.close();
            return 0;
        }
        i++;
    }
    fin.close();
    return 1;
}


int Source::AdvancedSearch(std::string year, std::string platform, std::string genre, std::string publisher, GameList &gl){
    QFile fin(this->filename);
    if(!fin.open(QFile::ReadOnly | QFile::Text)) return 1;
    if(year=="" && platform=="" && genre=="" && publisher=="" ) return 1;
    QTextStream in(&fin);
    QString text = in.readAll();
    QStringList rows = text.split("\n");
    int n = rows.size();
    int i = 0;
    while(i<n){
        QStringList words = rows[i].split(",");
        if(words.size()<5){i++; continue;}
        bool x = ((year=="")||(words[2].toStdString()==year))&&((publisher=="")||(words[4].toStdString()==publisher))&&
                ((genre=="")||(words[3].toStdString()==genre))&&((platform=="")||(words[1].toStdString()==platform));
        if(x){
            gl.Add_Game(words[0].toStdString(), words[2].toStdString(), words[1].toStdString(), rows[i].toStdString());
        }
        i++;
    }
    fin.close();
    if(gl.num==0){return 1;}
    return 0;
}


int Source::AddFavourite(std::string name, std::string year, std::string publisher, std::string row){
    QFile fin(this->favdir);
    if(!fin.open(QFile::ReadWrite | QFile::Text)){return 1;}
    QTextStream in(&fin);
    QString text = in.readAll();
    QStringList rows = text.split("\n");
    int n = rows.size();
    int i = 0;
    if(rows.size()>0){
        while(i<n){
            QStringList words = rows[i].split(",");
            if(words[0].toStdString() == name){fin.close(); return 0;}
            i++;
        }
    }
    in.operator<<("\n" + QString::fromStdString(row));
    fin.close();
    return 0;
}


int Source::GetFavourites(GameList &gl, bool to_sort){
    QFile fin(this->favdir);
    if(!fin.open(QFile::ReadOnly | QFile::Text)){return 1;}
    QTextStream in(&fin);
    QString text = in.readAll();
    QStringList rows = text.split("\n");
    int n = rows.size();
    int i = 0;
    if(rows.size()>0){
        while(i<n){
            QStringList words = rows[i].split(",");
            if(words.size()<3){i++; continue;}
            gl.Add_Game(words[0].toStdString(), words[2].toStdString(), words[1].toStdString(), rows[i].toStdString());
            i++;
        }
    }
    if(to_sort){
        gl.Sort();
    }
    return 0;
}


int Source::DeleteFavourite(std::string name, int ind){
    QFile fin(this->favdir);
    if(!fin.open(QFile::ReadWrite | QFile::Text)){return 1;}
    QTextStream in(&fin);
    QString text = in.readAll();
    QStringList rows = text.split("\n");
    int n = rows.size();
    int i = 0;
    while(i<n){
        QStringList words = rows[i].split(",");
        if(words.size() == 0){i++; continue;}
        if(words[0].toStdString()==name){
            rows.erase(rows.begin()+i);
            text = QString();
            for(int j = 0; j < rows.size(); j++){
                text += rows[j] + "\n";
            }
            fin.resize(0);
            in.operator<<(text);
            fin.close();
            return 0;
        }
        i++;
    }
    return 1;
}









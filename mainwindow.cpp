#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("");

    Source source;
    this->s = source;

    ui->stackedWidget->setCurrentIndex(0);
    ui->Add->setDisabled(true);
    ui->Simple->setDisabled(true);
    ui->Advance->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//MainMenu events
void MainWindow::on_Load_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Open file", "", "files (*.csv *.txt)");
    if(s.Load(file) == 0){
        ui->Add->setDisabled(false);
        ui->Simple->setDisabled(false);
        ui->Advance->setDisabled(false);
        ui->Load->setDisabled(true);
    }
    else{
        QMessageBox::warning(this, "Error", "Could not open the file");
    }
}


void MainWindow::on_Add_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_Simple_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_Advance_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_Favourites_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    this->UpdateFavourites();
}


void MainWindow::on_About_clicked()
{
    this->aw = new AboutW(nullptr);
    aw->show();

}

//Add New CSV events
void MainWindow::on_AddToCSV_clicked()
{
    std::string name  = ui->NameAddLine->text().toStdString();
    std::string year  = ui->YearAddLine->text().toStdString();
    std::string platform  = ui->PlatformAddLine->text().toStdString();
    if(this->s.AddNew(name, year, platform) == 0){
        QMessageBox::warning(this, "Warning", "Game added to CSV");
        ui->NameAddLine->clear();
        ui->YearAddLine->clear();
        ui->PlatformAddLine->clear();
    }
    else{
        QMessageBox::warning(this, "Error", "Could not add game to CSV");
    }
}


void MainWindow::on_BackFromAdd_clicked()
{
    ui->NameAddLine->clear();
    ui->YearAddLine->clear();
    ui->PlatformAddLine->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

//Simple search events
void MainWindow::on_FindSimple_clicked()
{
    GameList ggl;
    bool x = this->s.SimpleSearch(ui->NameSimple->text().toStdString(), ggl);
    this->gl = ggl;
    if(!x){
          ui->stackedWidget->setCurrentIndex(2);
          ui->GameNameFound->setText(QString::fromStdString(gl.namelist[0]));
    }
    else{
        QMessageBox::warning(this, "Warning", "No such game found");
    }
}


void MainWindow::on_BackFromSimple_clicked()
{
    ui->NameSimple->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

//Simple found events
void MainWindow::on_AddToFav_clicked()
{
    if(this->s.AddFavourite(gl.namelist[0], gl.yearlist[0], gl.platformlist[0], gl.rows[0])==0){
        QMessageBox::warning(this, "Warning", "Game is added to favourites");
        ui->AddToFav->setDisabled(true);
    }
    else{
        QMessageBox::warning(this, "Error", "Could not add game to favourites");
    }
}


void MainWindow::on_BackToSimple_clicked()
{
    ui->AddToFav->setDisabled(false);
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_BackFromSimpleFound_clicked()
{
    ui->AddToFav->setDisabled(false);
    ui->NameSimple->clear();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_ToFavouritesFromSimple_clicked()
{
    ui->AddToFav->setDisabled(false);
    ui->NameSimple->clear();
    ui->stackedWidget->setCurrentIndex(6);
    this->UpdateFavourites();
}

//Advance search events
void MainWindow::on_FindAdvanced_clicked()
{
    std::string year = ui->YearFindLine->text().toStdString();
    std::string genre = ui->GenreFindLine->text().toStdString();
    std::string platform = ui->PlatformFindLine->text().toStdString();
    std::string publisher = ui->PublisherFindLine->text().toStdString();
    GameList gll;
    bool x = this->s.AdvancedSearch(year, platform, genre, publisher, gll);
    this->gl = gll;
    if(!x){
        ui->stackedWidget->setCurrentIndex(5);
        int num = gl.num;
        ui->FoundTable->setRowCount(num);
        ui->FoundTable->setColumnCount(3);
        ui->FoundTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Year_of_Release"<< "Platform");
        for(int i = 0; i < num; i++){
            QTableWidgetItem *iname = new QTableWidgetItem(QString::fromStdString(gl.namelist[i]));
            QTableWidgetItem *iyear = new QTableWidgetItem(QString::fromStdString(gl.yearlist[i]));
            QTableWidgetItem *iplatform = new QTableWidgetItem(QString::fromStdString(gl.platformlist[i]));
            ui->FoundTable->setItem(i, 0, iname);
            ui->FoundTable->setItem(i, 1, iyear);
            ui->FoundTable->setItem(i, 2, iplatform);
        }
    }
    else{
        QMessageBox::warning(this, "Error", "No such games found");
    }

}


void MainWindow::on_BackFromAdvanced_clicked()
{
    ui->YearFindLine->clear();
    ui->GenreFindLine->clear();
    ui->PlatformFindLine->clear();
    ui->PublisherFindLine->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

//Advanced found events
void MainWindow::on_AddToFavouritesFromAdvancedFound_clicked()
{
    int n = ui->FoundTable->currentRow();
    if(n < 0){return;}
    std::string name = this->gl.namelist[n];
    std::string platform = this->gl.platformlist[n];
    std::string year = this->gl.yearlist[n];
    std::string row = this->gl.rows[n];
    if(this->s.AddFavourite(name, year, platform, row)==0){
        QMessageBox::warning(this, "Warning", "Game is added to favourites");
    }
    else{
        QMessageBox::warning(this, "Error", "Could not add game to favourites");
    }
}


void MainWindow::on_BackToAdvancedSearch_clicked()
{
    ui->FoundTable->clear();
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_BackFromAdvancedFound_clicked()
{
    ui->FoundTable->clear();
    ui->YearFindLine->clear();
    ui->GenreFindLine->clear();
    ui->PlatformFindLine->clear();
    ui->PublisherFindLine->clear();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_ToFavouritesFromAdvancedFound_clicked()
{
    ui->FoundTable->clear();
    ui->YearFindLine->clear();
    ui->GenreFindLine->clear();
    ui->PlatformFindLine->clear();
    ui->PublisherFindLine->clear();
    this->UpdateFavourites();
    ui->stackedWidget->setCurrentIndex(6);
}

//Favourites widget events
void  MainWindow::UpdateFavourites(bool to_sort){
    GameList gll;
    bool x = this->s.GetFavourites(gll, to_sort);
    this->gl = gll;
    if(!x){
        ui->FavouritesTable->clear();
        int num = gl.num;
        ui->FavouritesTable->setRowCount(num);
        ui->FavouritesTable->setColumnCount(3);
        ui->FavouritesTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Year_of_Release"<< "Platform");
        for(int i = 0; i < num; i++){
            QTableWidgetItem *iname = new QTableWidgetItem(QString::fromStdString(gl.namelist[i]));
            QTableWidgetItem *iyear = new QTableWidgetItem(QString::fromStdString(gl.yearlist[i]));
            QTableWidgetItem *iplatform = new QTableWidgetItem(QString::fromStdString(gl.platformlist[i]));
            ui->FavouritesTable->setItem(i, 0, iname);
            ui->FavouritesTable->setItem(i, 1, iyear);
            ui->FavouritesTable->setItem(i, 2, iplatform);
        }
    }
    else{
        ui->FavouritesTable->clear();
        QMessageBox::warning(this, "Error", "Colud not update the table");
    }
}


void MainWindow::on_BackFromFavourite_clicked()
{
    ui->FavouritesTable->clear();
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_DeleteFav_clicked()
{
    int n = ui->FavouritesTable->currentRow();
    if(n<0){return;}
    if(this->s.DeleteFavourite(gl.namelist[n], n)==0){
        QMessageBox::warning(this, "Warning", "Game deleted from favourites");
    }
    else{
        QMessageBox::warning(this, "Error", "Could not delete the game");
    }
    this->UpdateFavourites();
}


void MainWindow::on_SortFav_clicked()
{
    this->UpdateFavourites(true);
}





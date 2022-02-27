#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "source.h"
#include "aboutw.h"
#include<QString>
#include<QFileDialog>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Load_clicked();

    void on_Add_clicked();

    void on_Simple_clicked();

    void on_Advance_clicked();

    void on_Favourites_clicked();

    void on_AddToCSV_clicked();

    void on_BackFromAdd_clicked();

    void on_FindSimple_clicked();

    void on_BackFromSimple_clicked();

    void on_AddToFav_clicked();

    void on_BackToSimple_clicked();

    void on_BackFromSimpleFound_clicked();

    void on_ToFavouritesFromSimple_clicked();

    void on_FindAdvanced_clicked();

    void on_BackFromAdvanced_clicked();

    void on_AddToFavouritesFromAdvancedFound_clicked();

    void on_BackToAdvancedSearch_clicked();

    void on_BackFromAdvancedFound_clicked();

    void on_ToFavouritesFromAdvancedFound_clicked();

    void on_BackFromFavourite_clicked();

    void UpdateFavourites(bool to_sort=false);

    void on_DeleteFav_clicked();

    void on_SortFav_clicked();

    void on_About_clicked();

private:
    Ui::MainWindow *ui;
    AboutW *aw;
    Source s;
    GameList gl;
};
#endif // MAINWINDOW_H

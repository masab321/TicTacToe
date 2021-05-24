#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QString>
#include<utility>
#include<stdlib.h>
#include<time.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void clear_board();
    void user_move(int x, int y);
    pair<int, int> computer_move_easy();
    pair<int, int> computer_move_medium();
    pair<int, int> computer_move_hard();
    bool valid_move(int x, int y);

private slots:

    void on_button11_clicked();

    void on_button12_clicked();

    void on_button13_clicked();

    void on_button21_clicked();

    void on_button22_clicked();

    void on_button23_clicked();

    void on_button31_clicked();

    void on_button32_clicked();

    void on_button33_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    QString user_val = "O";
    int board[4][4];
    bool won = 0;
    int difficulty = 1;
    int dif_level = 9;
    void update_board(int x, int y, QString val);
    int check_result();
    void check_result_driver();
    pair<int, int> check_winning_move(int val);
    int move_count = 1;
};
#endif // MAINWINDOW_H

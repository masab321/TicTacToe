#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
    clear_board();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear_board(){

    ui->result->setText("");

    ui->button11->setText("");
    ui->button12->setText("");
    ui->button13->setText("");
    ui->button21->setText("");
    ui->button22->setText("");
    ui->button23->setText("");
    ui->button31->setText("");
    ui->button32->setText("");
    ui->button33->setText("");

    for(int i = 0 ; i < 4; i++) for(int j = 0; j < 4; j++) board[i][j] = 2;
    won = 0;
    move_count = 1;
}

bool MainWindow::valid_move(int x, int y){
    if(board[x][y] == 2) return true;
    return false;
}

void MainWindow::update_board(int x, int y, QString val){
    if(val == "X") board[x][y] = 1;
    if(val == "O") board[x][y] = 0;
    move_count++;
    if(x == 1 and y == 1) ui->button11->setText(val);
    else if(x == 1 and y == 2) ui->button12->setText(val);
    else if(x == 1 and y == 3) ui->button13->setText(val);
    else if(x == 2 and y == 1) ui->button21->setText(val);
    else if(x == 2 and y == 2) ui->button22->setText(val);
    else if(x == 2 and y == 3) ui->button23->setText(val);
    else if(x == 3 and y == 1) ui->button31->setText(val);
    else if(x == 3 and y == 2) ui->button32->setText(val);
    else if(x == 3 and y == 3) ui->button33->setText(val);

}

int MainWindow::check_result(){
    int cnt = 0;
    for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++){
        if(board[i][j] != 2) cnt++;
    }
    for(int i = 1; i < 4; i++){
        bool got = 1;
        int pre = board[i][1];
        for(int j = 1; j < 4; j++) if(board[i][j] != pre) got = 0;
        if(got and pre != 2) return pre;
    }
    for(int i = 1; i < 4; i++){
        bool got = 1;
        int pre = board[1][i];
        for(int j = 1; j < 4; j++) if(board[j][i] != pre) got = 0;
        if(got and pre != 2) return pre;
    }
    if(board[1][1] != 2 and board[1][1] == board[2][2] and board[3][3] == board[2][2]) return board[1][1];
    if(board[2][2] != 2 and board[2][2] == board[1][3] and board[2][2] == board[3][1]) return board[2][2];
    if(cnt == 9) return 2;
    return 3;
}

void MainWindow::check_result_driver(){
    int res = check_result();
    won = 1;
    QPalette sample_palette;
    sample_palette.setColor(QPalette::Window, Qt::white);
    sample_palette.setColor(QPalette::WindowText, Qt::red);

    //ui->result->setAutoFillBackground(true);
    ui->result->setPalette(sample_palette);
    if(res == 0 and user_val == "O") ui->result->setText("PLAYER");
    else if(res == 1 and user_val == "X") ui->result->setText("PLAYER");
    else if(res == 1 and user_val == "O") ui->result->setText("COMPUTER");
    else if(res == 0 and user_val == "X") ui->result->setText("COMPUTER");
    else if(res == 2) ui->result->setText("DRAW");
    else if(res == 3) won = 0;
}

pair<int, int> MainWindow::computer_move_easy(){
    vector<pair<int,int>> vm;
    auto dd = check_winning_move(user_val == "X" ? 0 : 1);
    if(dd.first != 0) return dd;
    for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++){
        if(valid_move(i, j) and board[i][j] == 2)
            vm.push_back({i, j});
    }
    if(vm.empty()) return {0, 0};
    int ind = rand() % (int)vm.size();
    return vm[ind];
}

pair<int,int> MainWindow::check_winning_move(int val){ // takes 0 or 1 as parameter and checks for a wining position.
    for(int i = 1; i < 4; i++){
        int val_cell = 0;
        int empty_cell = 0;
        for(int j = 1; j < 4; j++){
            if(board[i][j] == val) val_cell++;
            if(board[i][j] == 2) empty_cell++;
        }
        if(val_cell == 2 and empty_cell == 1){
            for(int j = 1; j < 4; j++) if(board[i][j] == 2) return {i, j};
        }
    }
    for(int i = 1; i < 4; i++){
        int val_cell = 0;
        int empty_cell = 0;
        for(int j = 1; j < 4; j++){
            if(board[j][i] == val) val_cell++;
            if(board[j][i] == 2) empty_cell++;
        }
        if(val_cell == 2 and empty_cell == 1){
            for(int j = 1; j < 4; j++) if(board[j][i] == 2) return {j, i};
        }
    }
    int val_cell = 0, empty_cell = 0;
    for(int i = 1; i < 4; i++){
        if(board[i][i] == val) val_cell++;
        if(board[i][i] == 2) empty_cell++;
    }
    if(val_cell == 2 and empty_cell == 1){
        for(int i = 1; i < 4; i++) if(board[i][i] == 2) return {i, i};
    }
    val_cell = 0; empty_cell = 0;
    for(int i = 1; i < 4; i++){
        if(board[i][4 - i] == val) val_cell++;
        if(board[i][4 - i] == 2) empty_cell++;
    }
    if(val_cell == 2 and empty_cell == 1){
        for(int i = 1; i < 4; i++) if(board[i][4 - i] == 2) return {i, 4 - i};
    }
    return {0, 0};
}

pair<int, int> MainWindow::computer_move_medium(){
    int c_val = user_val == "X" ? 0 : 1;
    int u_val = user_val == "X" ? 1 : 0;

    auto rule1 = check_winning_move(c_val); //computer jita
    if(rule1.first != 0) return rule1;

    auto rule2 = check_winning_move(u_val); //player
    if(rule2.first != 0) return rule2;

    //rule3
    vector<pair<int, int>> good_moves;
    // find a square from which there is chance to win in next two moves.
    for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++) if(board[i][j] == c_val){
        if(i + 1 < 4 and board[i + 1][j] == 2 and i - 1 > 0 and board[i - 1][j] == 2) good_moves.push_back( {i + 1, j});
        if(i - 1 > 0 and board[i - 1][j] == 2 and i + 1 < 4 and board[i - 1][j] == 2) good_moves.push_back( {i - 1, j});
        if(i + 1 < 4 and j + 1 < 4 and board[i + 1][j + 1] == 2 and i - 1 > 0 and j - 1 > 0 and board[i - 1][j - 1] == 2) good_moves.push_back( {i + 1, j + 1});
        if(i - 1 > 0 and j - 1 > 0 and board[i - 1][j - 1] == 2 and i + 1 < 4 and j + 1 < 4 and board[i + 1][j + 1] == 2) good_moves.push_back( {i - 1, j - 1});
        if(j - 1 > 0 and board[i][j - 1] == 2 and j + 1 < 4 and board[i][j + 1] == 2) good_moves.push_back( {i, j - 1});
        if(j + 1 < 4 and board[i][j + 1] == 2 and j - 1 > 0 and board[i][j - 1] == 2) good_moves.push_back( {i, j + 1});
        if(j + 1 < 4 and i - 1 > 0 and board[i - 1][j + 1] == 2 and j - 1 > 0 and i + 1 < 4 and board[i + 1][j - 1] == 2) good_moves.push_back( {i - 1, j + 1});
        if(j - 1 > 0 and i + 1 < 4 and board[i + 1][j - 1] == 2 and j + 1 < 4 and i - 1 > 0 and board[i - 1][j + 1] == 2) good_moves.push_back( {i + 1, j - 1});
    }
    if(!good_moves.empty()) return good_moves[rand() % (int)good_moves.size()];
    return computer_move_easy();
}

pair<int, int> MainWindow::computer_move_hard(){
    int c_val = user_val == "X" ? 0 : 1;
    int u_val = user_val == "X" ? 1 : 0;

    auto rule1 = check_winning_move(c_val); //computer
    if(rule1.first != 0) return rule1;

    auto rule2 = check_winning_move(u_val); //player
    if(rule2.first != 0) return rule2;

    //play intelligently..
    if(move_count == 1){ //random square
        return computer_move_easy();
    }
    if(move_count == 2){
        if(board[2][2] == 2) return {2,2}; //if the middle square is empty return centre square.
        vector<pair<int, int>> vm;
        vm.push_back({1,1});
        vm.emplace_back(1, 3);
        vm.emplace_back(3, 1);
        vm.emplace_back(3, 3);
        int ind = rand() % 4;
        return vm[ind]; // return a corner square.
    }
    if(move_count == 3){
        for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++) if(board[i][j] == c_val){
            vector<pair<int, int>> vm;
            vm.push_back({1,1});
            vm.emplace_back(1, 3);
            vm.emplace_back(3, 1);
            vm.emplace_back(3, 3);

            // if the last computer move is on the center.
            if(i == 2 and j == 2){
                pair<int, int> last_user_move;
                for(int k = 1; k < 4; k++) for(int l = 1; l < 4; l++) if(board[k][l] == user_val) last_user_move = {k, l};
                auto ret = vm[0];
                int best = 0;
                for(auto k: vm) if(board[k.first][k.second] == 2){
                    if(abs(last_user_move.first - k.first) + abs(last_user_move.second - k.second) > best){
                        ret = k;
                        best = abs(last_user_move.first - k.first) + abs(last_user_move.second - k.second);
                    }
                }
                return ret; // the corner square that has the highest distance from the last user move.
            }


            //if the last computer move is on a side or corner.
            if(i != 2 and j != 2){
                auto ret = vm[0];
                int best = 0;
                for(auto k: vm) if(board[k.first][k.second] == 2){
                    if(abs(i - k.first) + abs(j - k.second) > best){
                        ret = k;
                        best = abs(i - k.first) + abs(j - k.second);
                    }
                }
                return ret; //a corner square that has the maximum distance from the last computer move.
            }
        }
    }
    if(move_count == 4){
        for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++) if(board[i][j] == c_val){
            if(i == 2 and j == 2){ // the last computer move was on center...
                vector<pair<int, int>> good_moves;
                for(int i = 1; i < 4; i++) for(int j = 1; j < 4; j++) if(board[i][j] == c_val){
                    if(i + 1 < 4 and board[i + 1][j] == 2 and i - 1 > 0 and board[i - 1][j] == 2) good_moves.push_back( {i + 1, j});
                    if(i - 1 > 0 and board[i - 1][j] == 2 and i + 1 < 4 and board[i - 1][j] == 2) good_moves.push_back( {i - 1, j});
                    if(j - 1 > 0 and board[i][j - 1] == 2 and j + 1 < 4 and board[i][j + 1] == 2) good_moves.push_back( {i, j - 1});
                    if(j + 1 < 4 and board[i][j + 1] == 2 and j - 1 > 0 and board[i][j - 1] == 2) good_moves.push_back( {i, j + 1});
                }
                // find such an square near the previous move where computer has the best chance to win in next two moves.
                if(!good_moves.empty()) return good_moves[rand() % (int)good_moves.size()];
            }
            else if(i != 2 and j != 2){ // the last computer move was not in center.
                vector<pair<int, int>> good_moves;
                if(board[1][1] == 2) good_moves.push_back({1, 1});
                if(board[1][3] == 2) good_moves.push_back({1, 3});
                if(board[3][1] == 2) good_moves.push_back({3, 1});
                if(board[3][3] == 2) good_moves.push_back({3, 3});
                // return any corner square which was not used yet.
                if(!good_moves.empty()) return good_moves[rand() % (int)good_moves.size()];
           }
        }
    }

    // finally return a move of medium strategy.
    return computer_move_medium();
}

void MainWindow::user_move(int x, int y){ //engine.
    if(valid_move(x, y) && won == 0){ // check for valid moves and also checks for end.
        update_board(x, y, user_val); // updates the game state.
        check_result_driver(); // result check korar jonno.
        int cx = 0, cy = 0;
        if(difficulty == 1){
            auto cm = computer_move_easy();
            cx = cm.first; cy = cm.second;
        }else if(difficulty == 2){
            auto cm = computer_move_medium();
            cx = cm.first; cy = cm.second;
        }else if(difficulty == 3){
            auto cm = computer_move_hard();
            cx = cm.first; cy = cm.second;
        }
        if(cx != 0 and cy != 0 and won == 0) update_board(cx, cy, (user_val == "X" ? "O" : "X"));
        check_result_driver();
    }
}


void MainWindow::on_button11_clicked()
{
    if(dif_level == 9) return;
    user_move(1, 1);
}

void MainWindow::on_button12_clicked()
{
    if(dif_level == 9) return;
    user_move(1, 2);
}

void MainWindow::on_button13_clicked()
{
    if(dif_level == 9) return;
    user_move(1, 3);
}

void MainWindow::on_button21_clicked()
{
    if(dif_level == 9) return;
    user_move(2, 1);
}

void MainWindow::on_button22_clicked()
{
    if(dif_level == 9) return;
    user_move(2, 2);
}

void MainWindow::on_button23_clicked()
{
    if(dif_level == 9) return;
    user_move(2, 3);
}

void MainWindow::on_button31_clicked()
{
    if(dif_level == 9) return;
    user_move(3, 1);
}

void MainWindow::on_button32_clicked()
{
    if(dif_level == 9) return;
    user_move(3, 2);
}

void MainWindow::on_button33_clicked()
{
    if(dif_level == 9) return;
    user_move(3, 3);
}

void MainWindow::on_pushButton_3_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 1;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("EASY");
    dif_level = 1;
}

void MainWindow::on_pushButton_4_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 1;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("EASY");
    dif_level = 1;
}

void MainWindow::on_pushButton_5_clicked()
{
    clear_board();
    user_val = "X";
    difficulty = 1;
    won = 0;
    ui->player_value->setText(user_val);
    auto mm = computer_move_easy();
    update_board(mm.first, mm.second, "O");
    ui->difficulty_level->setText("EASY");
    dif_level = 1;
}

void MainWindow::on_pushButton_8_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 2;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("MEDIUM");
    dif_level = 2;
}

void MainWindow::on_pushButton_7_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 2;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("MEDIUM");
    dif_level = 2;
}

void MainWindow::on_pushButton_6_clicked()
{
    clear_board();
    user_val = "X";
    difficulty = 2;
    won = 0;
    ui->player_value->setText(user_val);
    auto mm = computer_move_medium();
    update_board(mm.first, mm.second, "O");
    ui->difficulty_level->setText("MEDIUM");
    dif_level = 2;
}

void MainWindow::on_pushButton_11_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 3;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("HARD");
    dif_level = 3;
}

void MainWindow::on_pushButton_10_clicked()
{
    clear_board();
    user_val = "O";
    difficulty = 3;
    won = 0;
    ui->player_value->setText(user_val);
    ui->difficulty_level->setText("HARD");
    dif_level = 3;

}

void MainWindow::on_pushButton_9_clicked()
{
    clear_board();
    user_val = "X";
    difficulty = 3;
    won = 0;
    ui->player_value->setText(user_val);
    auto mm = computer_move_hard();
    update_board(mm.first, mm.second, "O");
    ui->difficulty_level->setText("HARD");
    dif_level = 3;

}

void MainWindow::on_pushButton_2_clicked()
{
    if(dif_level == 9) return;
    won = 0;
    clear_board();
    ui->player_value->setText(user_val);
    if(user_val == "X"){
        pair<int, int> mm;
        if(difficulty == 1) mm = computer_move_easy();
        else if(difficulty == 2) mm = computer_move_medium();
        else if(difficulty == 3) mm = computer_move_hard();
        update_board(mm.first, mm.second, "O");
    }
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}


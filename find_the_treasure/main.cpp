#include "include/raylib.h"
#include "iostream"
#include "vector"
struct Person{
    int x;
    int y;
    int columns = 0;
    int rows = 0;
};
struct Tresure{
    int x;
    int y;
    bool collected= false;
};
struct Key{
    int x;
    int y;
    bool collected= false;
};


void draw_doors (int max, int Player_columns, int Player_rows){
    if (Player_rows == 0 && Player_columns == 0) {
        DrawRectangle(885, 1030, 150, 50, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
    }
    if(Player_rows==0 && Player_columns == max-1){
        DrawRectangle(885,1030,150,50,BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
    }
    if (Player_rows == max-1 && Player_columns == 0) {
        DrawRectangle(885, 0, 150, 50, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
    }
    if (Player_rows == max-1 && Player_columns == max-1) {
        DrawRectangle(885, 0, 150, 50, BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
    }
    if (Player_rows == 0 && Player_columns > 0 && Player_columns < max-1){
        DrawRectangle(885, 1030, 150, 50, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
    }
    if (Player_rows == max-1 && Player_columns > 0 && Player_columns < max-1){
        DrawRectangle(885, 0, 150, 50, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
    }
    if (Player_columns == 0 && Player_rows > 0 && Player_rows < max-1){
        DrawRectangle(885, 1030, 150, 50, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
        DrawRectangle(885, 0, 150, 50, BLUE);
    }
    if (Player_columns == max-1 && Player_rows > 0 && Player_rows < max-1){
        DrawRectangle(885, 0, 150, 50, BLUE);
        DrawRectangle(885, 1030, 150, 50, BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
    }
    if (Player_columns > 0 && Player_columns < max-1 && Player_rows > 0 && Player_rows < max-1){
        DrawRectangle(885, 0, 150, 50, BLUE);
        DrawRectangle(885, 1030, 150, 50, BLUE);
        DrawRectangle(0, 465, 50, 150, BLUE);
        DrawRectangle(1870, 465, 50, 150, BLUE);
    }
}
void draw_tresure(int room_x, int room_y, int Player_columns, int Player_rows, bool collected){
    if(room_x==Player_rows && room_y == Player_columns  && collected == false){
        DrawRectangle(860, 440, 200, 200, GREEN);
    }
}
void draw_keys(std::vector <Key> key,int Player_columns, int Player_rows){
    for (int i = 0; i < key.size(); ++i) {
        if (key.at(i).x==Player_rows && key.at(i).y == Player_columns){
            if (key.at(i).collected == false){
                DrawRectangle(935,515,50,50, YELLOW);
            }
        }
    }
}
void collect_keys (std::vector <Key> & key,int Player_columns, int Player_rows, int Player_x, int Player_y, int &keys){
    for (int i = 0; i < key.size(); ++i) {
        if (key.at(i).x==Player_rows && key.at(i).y == Player_columns){
            if(Player_x>=835&&Player_x<=1085&&Player_y>=415&&Player_y<=765 && key.at(i).collected == false){
                key.at(i).collected=true;
                keys++;
            }
        }
    }
}
void collect_tresure (int room_x, int room_y, int Player_columns, int Player_rows, int &keys, int Player_x, int Player_y, bool & collected){
    if(room_x==Player_columns && room_y == Player_rows){
        if(Player_x>=835&&Player_x<=1085&&Player_y>=415&&Player_y<=765 && collected == false){
            collected=true;
        }
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int max = 3;
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "TEST");

    std::vector <Key> v;

    while (v.size() < max) {
        bool add = true;
        Key key {
            rand()%max,
            rand()%max
        };

        for (int i = 0; i < v.size() && add; i++) {
            if (key.x == v.at(i).x && key.y == v.at(i).y) {
                add = false;
            }
        }

        if (add) {
            v.push_back(key);
        }
    }

    for (int i = 0; i < max; ++i) {
        std::cout<<v.at(i).x<<v.at(i).y<<std::endl;
    }



    Person Player;
    Player.y=screenHeight/2;
    Player.x=screenWidth/2;
    Player.columns = 0;
    Player.rows = 0;

    int rany=rand()%max;
    int ranx=rand()%max;

    bool compatible=false;
    int check=0;

    while(compatible == false){

        for (int i = 0; i < v.size(); ++i) {
            if (ranx == v.at(i).x && rany == v.at(i).y || ranx ==0 && rany ==0){
                check++;
            }
        }

        std::cout<<ranx<<rany<<std::endl;

        if (check==0){
            compatible=true;
        }

        else{
            ranx=rand()%max;
            rany=rand()%max;
            check=0;
        }
    }

    int keys_collected=0;



    Tresure rooms;

    Texture2D background1 = LoadTexture("../assets/selezione2.png");

    rooms.x=ranx;
    rooms.y=rany;

    SetTargetFPS(60);
                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }
        if (IsKeyDown(KEY_W)&& Player.y>=50){
            Player.y -= 10;
        }
        if (IsKeyDown(KEY_A)&& Player.x>=50){
            Player.x -= 10;
        }
        if (IsKeyDown(KEY_S)&& Player.y<=1030){
            Player.y += 10;
        }
        if (IsKeyDown(KEY_D)&& Player.x<=1870){
            Player.x += 10;
        }
        if (Player.x >= 885 && Player.x <= 1035 && Player.y >= 1030) {

            if (Player.rows < max-1) {
                Player.rows += 1;
                Player.x = 960;
                Player.y = 75;
            }
        }
        if (Player.x >= 885 && Player.x <= 1035 && Player.y <= 50) {

            if (Player.rows > 0) {
                Player.rows -= 1;
                Player.x = 960;
                Player.y = 1005;
            }
        }
        if (Player.y >= 465 && Player.y <= 615 && Player.x >= 1870) {

            if (Player.columns < max-1) {
                Player.columns += 1;
                Player.x = 75;
                Player.y = 540;
            }
        }
        if (Player.y >= 465 && Player.y <= 615 && Player.x <= 50) {

            if (Player.columns > 0) {
                Player.columns -= 1;
                Player.x = 1845;
                Player.y = 540;
            }
        }

        collect_keys(v,Player.columns,Player.rows,Player.x,Player.y,keys_collected);
        if (keys_collected == max){
            collect_tresure(rooms.x, rooms.y, Player.columns, Player.rows,keys_collected, Player.x, Player.y, rooms.collected);
        }



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(Player.x-50,Player.y-50,100, 100, MAROON);

        draw_doors(max, Player.columns, Player.rows);

        draw_keys(v,Player.columns,Player.rows);

        draw_tresure(rooms.x, rooms.y, Player.columns, Player.rows, rooms.collected);

        std::cout<<keys_collected<<std::endl;





        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


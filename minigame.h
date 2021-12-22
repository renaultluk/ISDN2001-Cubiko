#include "cubiko.h"
#include "minigame_run.h"
#include "minigame_jump.h"

int highscore = 0;

//lv_obj_t * minigameScreen;

//extern const lv_img_dsc_t cube_run_player_run;
//extern const lv_img_dsc_t cube_run_map;

class player {
    private:
        float x;
        float y;
        float baseline_y;
        float w;
        float h;
        float y_speed;
        bool jumped;
        uint8_t* sprites[3]; // 0 = running, 1 = jumping, 2 = dead
        int sprite_index;

    public:
        player();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        float get_y_speed() const;
        int get_sprite_index() const;
        uint8_t* get_current_sprite() const;
        void set_sprite_index(int);
        void update();
        void jump();
};

class gameMap {
    protected:
        float x;
        float y;
        float w;
        float h;
        // String sprites[4];
        // int sprite_index;
        // lv_obj_t * ground[4];
        // int ground_index;
        char* current_ground;
    
    public:
        gameMap();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        char* get_current_ground() const;
        void update(float speed);
};

class background : public gameMap {
    public:
        background();
};

class obstacle {
    private:
        float x;
        float y;
        float w;
        float h;
        char* sprites[2];
        int sprite_index;
    
    public:
        obstacle();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        char* get_current_sprite() const;
        void update(int speed);
        bool collided(player p);
};

class Minigame {
  private:
    player current_player;
    gameMap current_map;
    // background current_background;
    obstacle obstacles[10];
    int obstacle_count;
    float current_speed;
    float baseline_speed;
    int score;
    int level;
    bool game_over;
    
  public:
    Minigame();
    void setup();
    void loop();
    void draw();
    void update();
    void gameOverScreen();
    void set_score(int score);
    void generate_obstacle();
    void dequeue_obstacle(int i);
};

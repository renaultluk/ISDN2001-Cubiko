#include <TFT_eSPI.h>

#define BUTTON_PIN 25
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

int highscore = 0;
bool button_pressed = false;

class player {
    private:
        float x;
        float y;
        float baseline_y;
        float w;
        float h;
        float y_speed;
        bool jumped;

    public:
        player();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        float get_y_speed() const;
        void update();
        void jump();
};

class obstacle {
    private:
        float x;
        float y;
        float w;
        float h;
    
    public:
        obstacle();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        void update(int speed);
        bool collided(player p);
};

class Minigame {
  private:
    player current_player;
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

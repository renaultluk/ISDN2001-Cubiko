class player {
    private:
        int y;
        int baseline_y;
        int w;
        int h;
        int y_speed;
        bool jumped;
        int sprites[4]; // 0,1 = running, 2 = jumping, 3 = dead
        int sprite_index;

    public:
        player();
        int get_y() const;
        int get_w() const;
        int get_h() const;
        int get_y_speed() const;
        void update();
        void jump();
};

class gameMap {
    private:
        int x;
        int y;
        int h;
        int sprites[4];
        int sprite_index;
    
    public:
        gameMap();
        int get_x() const;
        int get_y() const;
        int get_y_speed() const;
        int get_h() const;
        void update(int speed);
};

class obstacle {
    private:
        int x;
        int y;
        int w;
        int h;
        int sprites[4];
        int sprite_index;
    
    public:
        obstacle();
        int get_x() const;
        int get_y() const;
        int get_w() const;
        int get_h() const;
        void update(int speed);
        bool collided(player p);
};

class Minigame {
  private:
    player current_player;
    gameMap current_map;
    obstacle obstacles[10];
    int obstacle_count;
    int current_speed;
    int baseline_speed;
    int score;
    int level;
    int highscore;
    bool game_over;
    
  public:
    Minigame();
    void setup();
    void loop();
    void draw();
    void update();
    void reset();
    void set_score(int score);
    void dequeue_obstacle(int i);
};
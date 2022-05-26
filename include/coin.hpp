const int coin_frame_size = 6;
const string coin_frame_path[] = {
    "resource/coin/1.1.png",
    "resource/coin/2.1.png",
    "resource/coin/3.1.png",
    "resource/coin/4.1.png",
    "resource/coin/5.1.png",
    "resource/coin/6.1.png",
};

struct coin_type {
    bool moving = true;
    bool show = false;
    int v = 0;
    int x = Game::WINDOW_WIDTH;
    int y = Game::WINDOW_HEIGHT;
};

const int coins_width = 35;
const int coins_height = 16;
coin_type coins[coins_height][coins_width];
const unsigned int coin_speed = 4;
const unsigned int coins_series_delay = 0;

Texture coin_tex[coin_frame_size];

bool load_coin_texture() {
    for (int i = 0; i < coin_frame_size; ++i)
        coin_tex[i]= SBDL::loadTexture (coin_frame_path[i]);
    return true;
}

bool set_coin_place() {
    for (int i = 0; i < coins_height; ++i)
        for (int j = 0; j < coins_width; ++j) {
            coins[i][j].x = Game::WINDOW_WIDTH / coins_width * (j + coins_series_delay) + Game::WINDOW_WIDTH;
            coins[i][j].y = Game::WINDOW_HEIGHT / coins_height * i;
            coins[i][j].v = j % coin_frame_size;
            coins[i][j].moving = true;
        }
    return true;
}

bool coin_pattern[] =
{
  1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
  0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,0,
  0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
  0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
  0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
  1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,
  0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,
  1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,
  1,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,
  0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,
  0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
  0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
  0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,
  1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0
};

int coin_pattern_length = (sizeof(coin_pattern)/sizeof(*coin_pattern));

bool set_coin_pattern() {
    for (int i = 0; i < coins_height; ++i)
        for (int j = 0; j < coins_width; ++j) {
            int line = i * coins_height + j;
            if (line < coin_pattern_length)
                coins[i][j].show = coin_pattern[line];
        }
    return true;
}

bool all_coin_out_check() {
    bool is_coin = false;
    for (int i = 0; i < coins_height; i++)
        for (int j = 0; j < coins_width; j++)
            is_coin |= coins[i][j].moving;
    return !is_coin;
}

bool restart_coins() {
    set_coin_pattern();
    set_coin_place();
    return true;
}

bool move_coin() {
    for (int i = 0; i < coins_height; i++)
        for (int j = 0; j < coins_width; j++) {
            if (coins[i][j].moving)
                coins[i][j].x -= coin_speed;
            if (coin_tex[coins[i][j].v].width + coins[i][j].x < 0)
                coins[i][j].moving = false;

        }
    if (all_coin_out_check()) restart_coins();
    return true;
}

void show_coin_texture() {
    for (int i = 0; i < coins_height; ++i)
        for (int j = 0; j < coins_width; ++j) {
            if (!coins[i][j].show) continue;
            SBDL::showTexture(coin_tex[coins[i][j].v], coins[i][j].x, coins[i][j].y);
            coins[i][j].v = (coins[i][j].v + 1) % coin_frame_size;
        }
}

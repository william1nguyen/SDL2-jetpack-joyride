#define start 0
#define one 1
#define two 2

#define lab 0
#define sector 1
#define volca 2
#define paral 3

int first_x = 0;
long int came_x = 0;

Texture background[4][3];

bool load_background_texture() {
    background[lab][start] = SBDL::loadTexture("resource/background/Lab Start.png");
    background[lab][one] = SBDL::loadTexture("resource/background/Lab1.png");
    background[lab][two] = SBDL::loadTexture("resource/background/Lab2.png");

    background[sector][start] = SBDL::loadTexture("resource/background/Sector Start.png");
    background[sector][one] = SBDL::loadTexture("resource/background/Sector1.png");
    background[sector][two] = SBDL::loadTexture("resource/background/Sector2.png");

    background[volca][start] = SBDL::loadTexture("resource/background/Volcano Start.png");
    background[volca][one] = SBDL::loadTexture("resource/background/Volcano1.png");
    background[volca][two] = SBDL::loadTexture("resource/background/Volcano2.png");

    background[paral][start] = SBDL::loadTexture("resource/background/warehouse Start.png");
    background[paral][one] = SBDL::loadTexture("resource/background/warehouse.png");
    background[paral][two] = SBDL::loadTexture("resource/background/warehouse.png");

    return true;
}

bool show_background (bool restart = false) {
    if (restart)
        first_x = 0;
    first_x -= Game::velocity;
    came_x = 0;

    SBDL::showTexture(background[lab][start], first_x + came_x, 0);
    came_x += background[lab][start].width;

    SBDL::showTexture(background[lab][one], first_x + came_x, 0);
    came_x += background[lab][one].width;

    SBDL::showTexture(background[lab][two], first_x + came_x, 0);
    came_x += background[lab][two].width;

    SBDL::showTexture(background[sector][start], first_x + came_x, 0);
    came_x += background[sector][start].width;

    SBDL::showTexture(background[sector][one], first_x + came_x, 0);
    came_x += background[sector][one].width;

    SBDL::showTexture(background[sector][two], first_x + came_x, 0);
    came_x += background[sector][two].width;

    SBDL::showTexture(background[volca][start], first_x + came_x, 0);
    came_x += background[volca][start].width;

    SBDL::showTexture(background[volca][one], first_x + came_x, 0);
    came_x += background[volca][one].width;

    SBDL::showTexture(background[volca][two], first_x + came_x, 0);
    came_x += background[volca][two].width;

    SBDL::showTexture(background[paral][start], first_x + came_x, 0);
    came_x += background[paral][start].width;

    SBDL::showTexture(background[paral][one], first_x + came_x, 0);
    came_x += background[paral][one].width;

    SBDL::showTexture(background[paral][two], first_x + came_x, 0);
    came_x += background[paral][two].width;

    SBDL::showTexture(background[lab][start], first_x + came_x, 0);

    first_x %= came_x;
    return true;
}

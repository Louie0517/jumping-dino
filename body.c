#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <process.h>

void settRGBColor(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void settColor(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void getup() {
    system("cls");
    gotoxy(70, 2);
    settColor(5);
    printf("SCORE : ");
    gotoxy(1, 25);
    for (int x = 0; x < 79; x++)
        printf("█");
}

void playBackgroundMusic(void* args) {
    mciSendString("open \"C:\\COMPROG\\UserSounds.wav\" type waveaudio alias bgm", NULL, 0, NULL);
    mciSendString("play bgm repeat", NULL, 0, NULL);
}

int t, gameSpeed = 2, scr = 0, dino_y = 15;
int soundPlayed = 0;

void Dino(int jump) {
    static int a = 1;
    static int musicThreadStarted = 0;
    static int soundPlayed = 0;

    if (!musicThreadStarted) {
        _beginthread(playBackgroundMusic, 0, NULL);
        musicThreadStarted = 1;
    }

    if ((jump == 1 || jump == 2) && !soundPlayed) {
        mciSendString("close jump", NULL, 0, NULL);
        mciSendString("open \"C:\\COMPROG\\JumpSounds.wav\" type waveaudio alias jump", NULL, 0, NULL);
        mciSendString("play jump", NULL, 0, NULL);
        soundPlayed = 1;
    }
    if (jump == 0) {
        t = 0;
        soundPlayed = 0;
    } else if (jump == 2) {
        t--;
    } else {
        t++;
        if(t > 30) {
            jump = 30;
        }
    }
    if (t > 25) {
        t = 400;
    }
    settRGBColor(255, 215, 0);
    dino_y = 15 - t;

    gotoxy(2, dino_y);
    printf("                 ");
    gotoxy(2, dino_y + 1);
    printf("         ████████ ");
    gotoxy(2, dino_y + 2);
    printf("         ██▄█████ ");
    gotoxy(2, dino_y + 3);
    printf("         █████▄▄   ");
    gotoxy(2, dino_y + 4);
    printf(" █      █████    ");
    gotoxy(2, dino_y + 5);
    printf(" ██   ███████▄▄   ");
    gotoxy(2, dino_y + 6);
    printf(" ████████████ ▀    ");
    gotoxy(2, dino_y + 7);
    printf("   ████████      ");
    gotoxy(2, dino_y + 8);
    if (jump == 1 || jump == 2) {
        printf("    ██ ███       ");
        gotoxy(2, dino_y + 9);
        printf("    ██   ██      ");
    } else if (a == 1) {
        printf("    ███ ███      ");
        gotoxy(2, dino_y + 9);
        printf("      ██         ");
        a = 2;
    } else if (a == 2) {
        printf("     ███ █       ");
        gotoxy(2, dino_y + 9);
        printf("         ██      ");
        a = 1;
    }
    gotoxy(2, dino_y + 10);
    if (jump != 0) {
        printf("                ");
    }  else {
    int numBlocks = 4;
    int initialWidth = 118;
    int widthDecrement = 20;
    int screenWidth = 120;

    for (int block = 0; block < numBlocks; block++) {
        if (block == 0) {
            settColor(5);
        } else {
            settColor(11);
        }

        int blockWidth = initialWidth - (block * widthDecrement);
        if (blockWidth < 0) {
            blockWidth = 0;
        }
        if (block == 0) {
            for (int i = 0; i < blockWidth; i++) {
                printf("█");
            }
        } else {
            int padding = (screenWidth - blockWidth) / 2;
            for (int i = 0; i < padding; i++) {
                printf(" ");
            }

            for (int i = 0; i < blockWidth; i++) {
                printf("█");
            }
        }
        printf("\n");
    }
    settColor(12);
}
    delay(gameSpeed);
}

void moveTo(int x, int y) {
    gotoxy(x, y);
}

void displayGameOver(){
    PlaySound(TEXT("C:\\COMPROG\\gameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
    getchar();
    const char *logo[] = {
        " ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ ██╗",
        "██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║",
        "██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝██║",
        "██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝",
        "╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗",
        " ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝"
    };

    int numLines = sizeof(logo) / sizeof(logo[0]);
    int x = 28;
    int y = 8;

    for (int i = 0; i < numLines; i++) {
        int red = 255;
        int green = 20 - (i * 20);
        int blue = 147 - (i * 15);

        if (green < 0) green = 0;
        if (blue < 0) blue = 0;

        settRGBColor(red, green, blue);
        gotoxy(x, y + i);
        printf("%s\n", logo[i]);
    }

    getchar();
}

void updateGameSpeed(int* score, int* gameSpeed) {
    if (*score >= 25 && *gameSpeed > 5) {
        *gameSpeed -= 11;
    } else if (*score >= 15 && *gameSpeed > 10) {
        *gameSpeed -= 9;
    } else if (*score >= 5 && *gameSpeed > 3) {
        *gameSpeed -= 7;
    }

    if (*gameSpeed < 5) {
        *gameSpeed = 5;
    }
}

void cactus() {
    static int x = 0;
    static int cactus_mode = 0;
    static int obstaclePosition = 0, score = 0;
    static int jumpHeight = 0;

    if (x > 74) {
    x = rand() % 10 + 1;
    cactus_mode = rand() % 2;
}

    gotoxy(74 - x, 20);
    printf("█    █ ");
    gotoxy(74 - x, 21);
    printf("█    █ ");
    gotoxy(74 - x, 22);
    printf(" ████  ");
    gotoxy(74 - x, 23);
    printf("  █    ");
    gotoxy(74 - x, 24);
    printf("  █    ");

    if (cactus_mode == 1) {
        gotoxy(84 - x, 20);
        printf("█    █ ");
        gotoxy(84 - x, 21);
        printf("█    █ ");
        gotoxy(84 - x, 22);
        printf(" ████  ");
        gotoxy(84 - x, 23);
        printf("  █    ");
        gotoxy(84 - x, 24);
        printf("  █    ");
    }

    int dino_x_start = 1, dino_x_end = 6;
    int dino_y_start = dino_y, dino_y_end = dino_y + 9;

    int cactus1_x_start = 74 - x, cactus1_x_end = cactus1_x_start + 2;
    int cactus1_y_start = 20, cactus1_y_end = 24;

    int collision1 = (dino_x_end >= cactus1_x_start + 2 && dino_x_start <= cactus1_x_end - 2 &&
                  dino_y_end >= cactus1_y_start + 2 && dino_y_start <= cactus1_y_end - 2);

    int cactus2_x_start = 84 - x, cactus2_x_end = cactus2_x_start + 4;
    int collision2 = 0;
    if (cactus_mode == 1) {
        collision2 = (dino_x_end >= cactus2_x_start + 2 && dino_x_start <= cactus2_x_end - 2 &&
                  dino_y_end >= cactus1_y_start + 2 && dino_y_start <= cactus1_y_end - 2);
    }

    if (collision1 || collision2) {
        system("cls");
        displayGameOver();
        getchar();
        exit(0);
    }

    if (x == 73) {
        x = 0;
        score++;
        settColor(11);
        gotoxy(78, 2);
        printf("     ");
        settColor(11);
        gotoxy(78, 2);
        printf("%d", score);
        updateGameSpeed(&score, &gameSpeed);

        if (score % 50 == 0 && gameSpeed > 10) {
            gameSpeed -= 2;
        }
    }
    x++;
    Sleep(gameSpeed);
}

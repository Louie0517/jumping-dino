#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#pragma comment(lib, "winmm.lib")
#include "jj.c"

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void setRGBColor(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void resetColor() {
    printf("\033[0m");
}

void setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hConsole, position);
}

void JumpingDino(int x, int y) {
    PlaySound(TEXT("C:\\COMPROG\\UserSounds.wav"), NULL, SND_FILENAME | SND_ASYNC);
    system("chcp 65001");
    const char *logo[] = {
        "     ██╗██╗   ██╗███╗   ███╗██████╗ ██╗███╗   ██╗ ██████╗     ██████╗ ██╗███╗   ██╗ ██████╗ ",
        "     ██║██║   ██║████╗ ████║██╔══██╗██║████╗  ██║██╔════╝     ██╔══██╗██║████╗  ██║██╔═══██╗",
        "     ██║██║   ██║██╔████╔██║██████╔╝██║██╔██╗ ██║██║  ███╗    ██║  ██║██║██╔██╗ ██║██║   ██║",
        "██   ██║██║   ██║██║╚██╔╝██║██╔═══╝ ██║██║╚██╗██║██║   ██║    ██║  ██║██║██║╚██╗██║██║   ██║",
        "╚█████╔╝╚██████╔╝██║ ╚═╝ ██║██║     ██║██║ ╚████║╚██████╔╝    ██████╔╝██║██║ ╚████║╚██████╔╝",
        " ╚════╝  ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚═════╝ ╚═╝╚═╝  ╚═══╝ ╚═════╝ "
    };

    int numLines = sizeof(logo) / sizeof(logo[0]);
    for (int i = 0; i < numLines; i++) {
        int red = 127;
        int green = 0 - (i * 20);
        int blue = 255 - (i * 15);
        if (green < 0) {
            green = 0;
        }
        setRGBColor(red, green, blue);
        setCursorPosition(x, y + i);
        printf("%s\n", logo[i]);
    }
    getchar();

    int a = 51;
    int b = 15;
    setCursorPosition(a, b);
    setColor(11);
    printf("type 'Enter' to start: ");
    getchar();
    system("cls");
}

void getUserInput() {
    int x = 4;
    int y = 6;
    const char *sign[] = {
        "                        ▄▄ •              ▄▄ • ▄▄▌  ▄▄▄ .    .▄▄ · ▪   ▄▄ •  ▐ ▄     ▪   ▐ ▄ ",
        "                       █ ▀ ▪▪     ▪     ▐█ ▀ ▪██•  ▀▄.▀·    ▐█ ▀. ██ ▐█ ▀ ▪•█▌▐█    ██ •█▌▐█",
        "                      ▄█ ▀█▄ ▄█▀▄  ▄█▀▄ ▄█ ▀█▄██▪  ▐▀▀▪▄    ▄▀▀▀█▄▐█·▄█ ▀█▄▐█▐▐▌    ▐█·▐█▐▐▌",
        "                      ▐█▄▪▐█▐█▌.▐▌▐█▌.▐▌▐█▄▪▐█▐█▌▐▌▐█▄▄▌    ▐█▄▪▐█▐█▌▐█▄▪▐███▐█▌    ▐█▌██▐█▌",
        "                       ▀▀▀▀  ▀█▄▀▪ ▀█▄▀▪·▀▀▀▀ .▀▀▀  ▀▀▀      ▀▀▀▀ ▀▀▀·▀▀▀▀ ▀▀ █▪    ▀▀▀▀▀ █▪"
    };

    int numLines = sizeof(sign) / sizeof(sign[0]);
    for (int i = 0; i < numLines; i++) {
        int red = 168 - (i * 10);
        int green = 201 - (i * 29);
        int blue = 230 - (i * 29);
        if (green < 0) {
            green = 0;
        }
        if (blue < 0) {
            blue = 0;
        }
        setRGBColor(red, green, blue);
        setCursorPosition(x, y + i);
        printf("%s", sign[i]);
    }

    int a = 67;
    int b = 12;
    char Email[100];
    char Password[100];
    setColor(5);
    setCursorPosition(a, b);
    printf("\n                                                  EMAIL: ");
    scanf("%s", &Email);
    b++;
    setCursorPosition(a, b);
    setRGBColor(204, 51, 153);
    printf("\n                                                  PASSWORD: ");
    scanf("%s", &Password);
}

int main() {
    srand(time(0));
    int x, y;
    JumpingDino(20, 7);
    getUserInput();
    getup();
    char ch;
    int i;
    getup();
    while (1) {
        while (!kbhit()) {
            Dino(0);
            cactus();
        }
        ch = getch();
        if (ch == ' ') {
            for (i = 0; i < 10; i++) {
                Dino(1);
                cactus();
            }
            for (i = 0; i < 10; i++) {
                Dino(2);
                cactus();
            }
        } else if (ch == 'x') {
            return 0;
        }
        x = rand() % 10 + 1;
    }
    return 0;
}

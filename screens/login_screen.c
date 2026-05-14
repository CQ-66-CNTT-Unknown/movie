#include "login_screen.h"
#include "../project/globals.h"
#include "../utils/input_utils.h"
#include "raylib.h"
#include <string.h>

char loginUsername[50] = "";
char loginPassword[50] = "";
int loginFocusField = 0; // 0 = username, 1 = password
char loginError[100] = "";

void DrawLoginScreen(Vector2 m) {
    /* ---- Background ---- */
    DrawRectangle(0, 0, 1280, 720, (Color){15, 15, 15, 255});

    /* ---- Header ---- */
    DrawRectangle(0, 0, 1280, 115, (Color){227, 27, 35, 255});
    /* Film-strip edges */
    for(int i = 0; i < 16; i++) {
        DrawRectangle(i*22, 0, 14, 115, (Color){200, 20, 25, 255});
        DrawRectangle(i*22+2, 8,  10, 16, (Color){150, 10, 12, 200});
        DrawRectangle(i*22+2, 91, 10, 16, (Color){150, 10, 12, 200});
    }
    for(int i = 0; i < 16; i++) {
        DrawRectangle(1280-i*22-16, 0, 14, 115, (Color){200, 20, 25, 255});
        DrawRectangle(1280-i*22-14, 8,  10, 16, (Color){150, 10, 12, 200});
        DrawRectangle(1280-i*22-14, 91, 10, 16, (Color){150, 10, 12, 200});
    }
    DrawRectangle(280, 0, 720, 115, (Color){227, 27, 35, 255});
    DrawText("CGV", 490, 10, 82, WHITE);
    DrawText("CINEMAS", 680, 30, 46, (Color){255, 210, 210, 255});

    /* ---- Login Form Container ---- */
    int formX = 390;
    int formY = 180;
    int formW = 500;
    int formH = 360;
    
    DrawRectangleRounded((Rectangle){formX, formY, formW, formH}, 0.1f, 10, (Color){25, 25, 25, 255});
    DrawRectangleRoundedLines((Rectangle){formX, formY, formW, formH}, 0.1f, 10, (Color){227, 27, 35, 150});

    /* ---- Title ---- */
    DrawText("DANG NHAP", formX + 110, formY + 30, 40, (Color){227, 27, 35, 255});

    /* ---- Username Field ---- */
    int inputY = formY + 110;
    Rectangle usernameBox = {formX + 40, inputY, 420, 50};
    Color usernameBgColor = (loginFocusField == 0) ? (Color){45, 45, 45, 255} : (Color){35, 35, 35, 255});
    Color usernameBorderColor = (loginFocusField == 0) ? (Color){227, 27, 35, 255} : (Color){80, 80, 80, 255});
    
    DrawRectangleRounded(usernameBox, 0.08f, 10, usernameBgColor);
    DrawRectangleRoundedLines(usernameBox, 0.08f, 10, usernameBorderColor);
    DrawText("Tai khoan:", formX + 50, inputY - 35, 18, (Color){200, 200, 200, 255});
    DrawText(loginUsername, usernameBox.x + 15, usernameBox.y + 15, 20, WHITE);

    /* ---- Password Field ---- */
    inputY += 90;
    Rectangle passwordBox = {formX + 40, inputY, 420, 50};
    Color passwordBgColor = (loginFocusField == 1) ? (Color){45, 45, 45, 255} : (Color){35, 35, 35, 255});
    Color passwordBorderColor = (loginFocusField == 1) ? (Color){227, 27, 35, 255} : (Color){80, 80, 80, 255});
    
    DrawRectangleRounded(passwordBox, 0.08f, 10, passwordBgColor);
    DrawRectangleRoundedLines(passwordBox, 0.08f, 10, passwordBorderColor);
    DrawText("Mat khau:", formX + 50, inputY - 35, 18, (Color){200, 200, 200, 255});
    
    // Draw password as dots
    char passwordDisplay[50];
    strcpy(passwordDisplay, "");
    for(int i = 0; i < strlen(loginPassword); i++) {
        strcat(passwordDisplay, "*");
    }
    DrawText(passwordDisplay, passwordBox.x + 15, passwordBox.y + 15, 20, WHITE);

    /* ---- Error Message ---- */
    if(strlen(loginError) > 0) {
        DrawText(loginError, formX + 50, inputY + 70, 16, (Color){255, 100, 100, 255});
    }

    /* ---- Login Button ---- */
    Rectangle loginBtn = {formX + 90, inputY + 110, 320, 50};
    Color loginBtnColor = CheckCollisionPointRec(m, loginBtn) 
                         ? (Color){255, 55, 60, 255} : (Color){227, 27, 35, 255});
    DrawRectangleRounded(loginBtn, 0.1f, 10, loginBtnColor);
    DrawText("DANG NHAP", loginBtn.x + 70, loginBtn.y + 12, 24, WHITE);

    /* ---- Handle Input ---- */
    if(CheckCollisionPointRec(m, usernameBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        loginFocusField = 0;
        loginError[0] = '\0';
    }
    if(CheckCollisionPointRec(m, passwordBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        loginFocusField = 1;
        loginError[0] = '\0';
    }

    // Text input handling
    if(loginFocusField == 0) {
        HandleTextInput(loginUsername, 49);
        if(IsKeyPressed(KEY_TAB)) {
            loginFocusField = 1;
        }
    } else if(loginFocusField == 1) {
        HandleTextInput(loginPassword, 49);
        if(IsKeyPressed(KEY_TAB)) {
            loginFocusField = 0;
        }
    }

    /* ---- Login Button Click ---- */
    if(CheckCollisionPointRec(m, loginBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Call the login function
        User loginResult = login_user(loginUsername, loginPassword);
        if(loginResult.user_id > 0) {
            // Login successful
            strcpy(currentUserID, loginUsername);
            loginUsername[0] = '\0';
            loginPassword[0] = '\0';
            loginError[0] = '\0';
            loginFocusField = 0;
            currentScreen = SCREEN_MENU;
        } else {
            strcpy(loginError, "Tai khoan hoac mat khau sai!");
        }
    }

    /* ---- Enter key to login ---- */
    if(IsKeyPressed(KEY_ENTER)) {
        User loginResult = login_user(loginUsername, loginPassword);
        if(loginResult.user_id > 0) {
            strcpy(currentUserID, loginUsername);
            loginUsername[0] = '\0';
            loginPassword[0] = '\0';
            loginError[0] = '\0';
            loginFocusField = 0;
            currentScreen = SCREEN_MENU;
        } else {
            strcpy(loginError, "Tai khoan hoac mat khau sai!");
        }
    }

    /* ---- Footer ---- */
    DrawRectangle(0, 686, 1280, 34, (Color){22, 22, 22, 255});
    DrawRectangle(0, 685, 1280, 1,  (Color){55, 55, 55, 255});
    DrawText("© CGV Cinemas Vietnam  |  Hotline: 1900 6017",
             415, 697, 16, (Color){110, 110, 110, 255});
}

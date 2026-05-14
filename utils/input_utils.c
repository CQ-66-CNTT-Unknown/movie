#include "input_utils.h"
#include <string.h>

void HandleTextInput(char *buf, int maxLen) {
    int key = GetCharPressed();

    while(key > 0) {
        if(key >= 32 && key <= 125 &&
           strlen(buf) < maxLen - 1) {

            int l = strlen(buf);

            buf[l] = (char)key;
            buf[l+1] = '\0';
        }

        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE) &&
       strlen(buf) > 0) {

        buf[strlen(buf)-1] = '\0';
    }
}
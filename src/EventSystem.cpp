#include "../include/EventSystem.h"
#include "../include/TerminalSettings.h"

class WaveGenerator;

EventSystem::EventWithChar EventSystem::getEvent(int key) {
    EventWithChar result;
    result.character = 0;

    switch (key) {
        case TerminalSettings::KEY_F1: result.event = QUIT; break;
        case TerminalSettings::KEY_F2: result.event = FILE_MENU; break;
        case TerminalSettings::KEY_ARROW_UP: result.event = CURSOR_UP; break;
        case TerminalSettings::KEY_ARROW_DOWN: result.event = CURSOR_DOWN; break;
        case TerminalSettings::KEY_ARROW_LEFT: result.event = CURSOR_LEFT; break;
        case TerminalSettings::KEY_ARROW_RIGHT: result.event = CURSOR_RIGHT; break;
        case ' ': result.event = SELECT; break;
        case TerminalSettings::KEY_DELETE: result.event = DELETE; break;
        case 'c': case 'C': result.event = CREATE_CLIP; break;
        case '\r': case '\n': result.event = CONFIRM; break;
        case TerminalSettings::KEY_ESC: result.event = CANCEL; break;
        case '\t': result.event = TAB; break;
        case 127: case 8: result.event = BACKSPACE; break;
        default:
            if (key >= 32 && key <= 126) {
                result.event = CHAR_INPUT;
                result.character = static_cast<char>(key);
            } else {
                result.event = QUIT;
            }
            break;
    }

    return result;
}
#pragma once

/**
 * @class EventSystem
 * @brief Central event handling system for processing user input and system events.
 *
 * The EventSystem provides a unified interface for converting raw input (key codes)
 * into semantic application events. It supports both simple events and events with
 * associated character data.
 */
class EventSystem {
public:
    /**
     * @enum Event
     * @brief Semantic application events representing user actions
     *
     * These events abstract away raw input details, providing a clean interface
     * for the application logic to respond to user interactions.
     */
    enum Event {
        /** @brief Application quit request */
        QUIT,

        /** @brief Cursor navigation events */
        CURSOR_UP, CURSOR_DOWN, CURSOR_LEFT, CURSOR_RIGHT,

        /** @brief Object manipulation events */
        SELECT, DELETE,

        /** @brief Playback control events */
        PLAY, PAUSE,

        /** @brief Content creation and UI events */
        CREATE_CLIP, FILE_MENU, CONFIRM, CANCEL,

        /** @brief Text navigation and editing events */
        TAB, BACKSPACE,

        /** @brief Generic character input (use with EventWithChar) */
        CHAR_INPUT
    };

    /**
     * @struct EventWithChar
     * @brief Combines an event with associated character data
     *
     * Used primarily for CHAR_INPUT events where the specific character
     * matters (e.g., text entry).
     */
    struct EventWithChar {
        /** @brief The semantic event type */
        Event event;

        /** @brief Associated character (valid when event == CHAR_INPUT) */
        char character;
    };

    /**
     * @brief Converts a raw key code into a semantic application event
     * @param key Raw input key code (platform-specific)
     * @return EventWithChar containing the semantic event and any associated character
     *
     * This is the main entry point for input processing. The method maps
     * low-level key codes to high-level application events, optionally
     * extracting character data for text input scenarios.
     */
    EventWithChar getEvent(int key);
};
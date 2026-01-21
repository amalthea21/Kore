#pragma once

#include <string>
#include <map>

/**
 * @class ClipDialog
 * @brief Interactive dialog for creating new audio clips.
 *
 * Presents a form-based UI with three fields:
 * - Position (at): When the clip starts on the timeline
 * - Duration (time): How long the clip plays
 * - Note: Musical note (A4, C#5) or frequency in Hz
 *
 * Supports navigation with Tab and accepts input via keyboard.
 */
class ClipDialog {
public:
    /**
     * @enum Field
     * @brief Input fields in the clip creation dialog
     */
    enum Field {
        AT,    /**< Position/start time field */
        TIME,  /**< Duration field */
        NOTE   /**< Note/frequency field */
    };

    /**
     * @struct ClipParams
     * @brief Parameters returned when dialog is confirmed
     */
    struct ClipParams {
        float at;         /**< Start position in seconds */
        float time;       /**< Duration in seconds */
        float frequency;  /**< Frequency in Hz */
        bool confirmed;   /**< True if user confirmed, false if cancelled */
    };

    /**
     * @brief Construct dialog with default values (0s position, 2s duration, A4 note)
     */
    ClipDialog();

    /**
     * @brief Render the dialog centered in terminal
     * @param termWidth Current terminal width for centering
     *
     * Shows:
     * - Three input fields with current values
     * - Active field highlighted in blue
     * - Keyboard shortcuts at bottom
     */
    void render(int termWidth) const;

    /**
     * @brief Move to next field (wraps from NOTE to AT)
     */
    void nextField();

    /**
     * @brief Move to previous field (wraps from AT to NOTE)
     */
    void prevField();

    /**
     * @brief Handle character input for current field
     * @param c Character to append (filtered by field type)
     *
     * AT/TIME fields: Accept digits and decimal point
     * NOTE field: Accept letters, digits, # and decimal point
     */
    void handleInput(char c);

    /**
     * @brief Remove last character from current field
     */
    void handleBackspace();

    /**
     * @brief Mark dialog as confirmed and complete
     */
    void confirm();

    /**
     * @brief Mark dialog as cancelled and complete
     */
    void cancel();

    /**
     * @brief Get parsed parameters from dialog inputs
     * @return ClipParams with validated values
     *
     * Parsing rules:
     * - AT: Defaults to 0.0 if invalid
     * - TIME: Defaults to 1.0 if invalid or ≤0
     * - NOTE: Looks up note name, falls back to Hz, defaults to 440.0
     */
    ClipParams getParams() const;

    /**
     * @brief Get currently active field
     * @return Current field enum value
     */
    Field getCurrentField() const { return currentField; }

    /**
     * @brief Check if user has confirmed or cancelled
     * @return True when dialog interaction is finished
     */
    bool isComplete() const { return complete; }

private:
    Field currentField;       /**< Currently selected field */
    std::string atInput;      /**< User input for position */
    std::string timeInput;    /**< User input for duration */
    std::string noteInput;    /**< User input for note/frequency */
    bool complete;            /**< Dialog finished flag */
    bool confirmed;           /**< True if confirmed, false if cancelled */

    /**
     * @brief Mapping of note names to frequencies (A4 = 440Hz)
     *
     * Includes notes from C0 (16.35Hz) to B5 (987.77Hz)
     * with both natural notes and sharps (#).
     */
    static const std::map<std::string, float> noteFrequencies;

    /**
     * @brief Parse AT field to float
     * @return Position in seconds, or 0.0 if invalid
     */
    float parseAt() const;

    /**
     * @brief Parse TIME field to float
     * @return Duration in seconds, or 1.0 if invalid/negative
     */
    float parseTime() const;

    /**
     * @brief Parse NOTE field to frequency
     * @return Frequency in Hz, or 440.0 if invalid
     *
     * Tries in order:
     * 1. Note name lookup (case-insensitive)
     * 2. Direct frequency value
     * 3. Default to 440.0 Hz (A4)
     */
    float parseNote() const;

    /**
     * @brief Get string value of a field
     * @param field Which field to query
     * @return Current input string
     */
    std::string getFieldValue(Field field) const;

    /**
     * @brief Set string value of a field
     * @param field Which field to modify
     * @param value New input string
     */
    void setFieldValue(Field field, const std::string& value);
};
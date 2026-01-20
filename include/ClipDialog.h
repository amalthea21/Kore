#pragma once

#include <string>
#include <map>

class ClipDialog {
public:
    enum Field { AT, TIME, NOTE };
    
    struct ClipParams {
        float at;
        float time;
        float frequency;
        bool confirmed;
    };

    ClipDialog();
    
    void render(int termWidth) const;
    void nextField();
    void prevField();
    void handleInput(char c);
    void handleBackspace();
    void confirm();
    void cancel();
    
    ClipParams getParams() const;
    Field getCurrentField() const { return currentField; }
    bool isComplete() const { return complete; }
    
private:
    Field currentField;
    std::string atInput;
    std::string timeInput;
    std::string noteInput;
    bool complete;
    bool confirmed;

    static const std::map<std::string, float> noteFrequencies;
    
    float parseAt() const;
    float parseTime() const;
    float parseNote() const;
    std::string getFieldValue(Field field) const;
    void setFieldValue(Field field, const std::string& value);
};
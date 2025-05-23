// InputBuffer.h
#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H

#include "InputTypes.h"
#include <deque>

class InputBuffer
{
public:
    void addInput(InputDirection direction, InputAction action);
    bool matchSequence(const SpecialMove& move);
    void clearBuffer(); // usually used after a SpecialMove was executed

private:
    struct Input
    {
        InputDirection direction;
        InputAction action;
        int frames; // how many frames this input has been held
    };

    static constexpr int BUFFER_SIZE = 30;
    static constexpr int MAX_LENIENCY_FRAMES = 15;
    std::deque<Input> buffer; // the input buffer
};

#endif // INPUT_BUFFER_H

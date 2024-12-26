#include "InputBuffer.h"

void InputBuffer::addInput(InputDirection direction, InputAction action)
{
    // If the new input matches the last input, increment its frame count
    if (!buffer.empty() && buffer.back().direction == direction)
    {
        buffer.back().frames++;
    }
    else
    {
        // Otherwise add new input state
        buffer.push_back({direction, action, 1});
    }

    // Keep buffer size manageable
    if (buffer.size() > BUFFER_SIZE)
    {
        buffer.erase(buffer.begin());
    }
}

bool InputBuffer::matchSequence(const SpecialMove& move)
{
    int moveIndex = move.sequence.size() - 1; // Start from end of desired sequence
    int bufferIndex = buffer.size() - 1;      // Start from most recent input

    while (moveIndex >= 0 && bufferIndex >= 0)
    {
        const auto& requiredInput = move.sequence[moveIndex];
        const auto& currentInput = buffer[bufferIndex];

        if (currentInput.direction == requiredInput.first)
        {
            moveIndex--; // Found a match, look for next required input
        }
        else if (currentInput.frames > MAX_LENIENCY_FRAMES)
        {
            // If we've held this non-matching input too long, sequence fails
            return false;
        }

        bufferIndex--;
    }

    return moveIndex < 0; // Did we match all required inputs?
}

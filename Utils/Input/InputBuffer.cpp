#include "InputBuffer.h"
#include <iostream>

void InputBuffer::addInput(InputDirection direction, InputAction action)
{
    // Check both direction and action before incrementing frame count
    if (!buffer.empty() && buffer.back().direction == direction && buffer.back().action == action)
    {
        buffer.back().frames++;
    }
    else
    {
        // Otherwise, add a new input state
        buffer.push_back({direction, action, 1});
    }

    // Maintain buffer size
    if (buffer.size() > BUFFER_SIZE)
    {
        buffer.erase(buffer.begin());
    }

    /*
    // Print the entire buffer for debugging
    std::cout << "Current buffer: ";
    for (const auto& input : buffer)
    {
        std::cout << "(" << directionToString(input.direction) << ", " << actionToString(input.action) << ", "
                  << input.frames << ") ";
    }
    std::cout << std::endl;
    */
}

bool InputBuffer::matchSequence(const SpecialMove& move)
{
    int moveIndex = move.sequence.size() - 1; // Start from end of desired sequence
    int bufferIndex = buffer.size() - 1;      // Start from most recent input

    int leniency = 0;

    while (moveIndex >= 0 && bufferIndex >= 0)
    {
        const auto& requiredInput = move.sequence[moveIndex];
        const auto& currentInput = buffer[bufferIndex];

        if (currentInput.direction == requiredInput.first && currentInput.action == requiredInput.second)
        {
            moveIndex--;  // Match found
            leniency = 0; // Reset leniency counter
        }
        else
        {
            leniency += currentInput.frames;
            if (leniency > MAX_LENIENCY_FRAMES)
            {
                return false; // Too much irrelevant input
            }
        }

        bufferIndex--;
    }

    return moveIndex < 0; // Did we match all required inputs?
}

void InputBuffer::clearBuffer()
{
    buffer.clear();
    std::cout << "InputBuffer cleared" << std::endl;
}

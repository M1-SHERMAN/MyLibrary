/**
 * @file Gate.cpp
 * @brief Implementation of the Gate system for Unreal Engine 5 Blueprint nodes.
 *
 * This file contains the C++ implementation of the Gate system, which is designed to mimic
 * the functionality of the Gate node in Unreal Engine 5 Blueprints. The Gate system
 * allows for controlled execution flow through a single output based on the state of the gate.
 */

class FGate
{
private:
    bool bIsOpen;

public:
    FGate(bool val) : bIsOpen(val) {}

    // Reset the gate state to open
    void Reset()
    {
        bIsOpen = true;
    }

    // Execute Gate logic - execute when the gate is open, then close
    template <typename FunctionType>
    void Execute(FunctionType &&InFunction)
    {
        if (bIsOpen)
        {
            bIsOpen = false; // Close the gate after execution
            InFunction();    // Execute the passed function
        }
    }

    // Get the gate state
    bool IsOpen() const
    {
        return bIsOpen;
    }

    // Open the gate
    void Open()
    {
        bIsOpen = true;
    }

    // Close the gate
    void Close()
    {
        bIsOpen = false;
    }

    // Toggle the gate
    void Toggle()
    {
        bIsOpen = !bIsOpen;
    }

    // Function for Exit logic
    void Exit()
    {
        // Add code to be executed here
    }
};
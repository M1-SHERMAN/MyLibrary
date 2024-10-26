/**
 * @file MultipleGate.cpp
 * @brief Implementation of the MultiGate system for Unreal Engine 5 Blueprint nodes.
 *
 * This file contains the C++ implementation of the MultiGate system, which is designed to mimic
 * the functionality of the MultiGate node in Unreal Engine 5 Blueprints. The MultiGate system
 * allows for controlled execution flow through multiple outputs based on different modes:
 * Sequential, Random, and Loop.
 *
 * Key features:
 * - Supports three execution modes: Sequential, Random, and Loop
 * - Allows for looping behavior
 * - Provides option to allow or prevent repeated execution of the same index
 * - Uses Unreal Engine's random number generator for the Random mode
 * - Implements a flexible and reusable design for various use cases in game logic
 *
 * This implementation can be used as a standalone C++ component or integrated into larger
 * systems that require multi-gate functionality similar to UE5 Blueprints.
 */

// Enum class for selecting execution mode
UENUM()
enum class EMultiGateMode : uint8
{
    Sequential, // Sequential mode
    Random,     // Random mode
    Loop        // Loop mode
};

class FMultiGate
{
private:
    int32 CurrentIndex;         // Current index, used to track the current execution position
    EMultiGateMode Mode;        // Execution mode (Sequential, Random, or Loop)
    bool bIsLooping;            // Whether to loop execution
    bool bAllowRepeat;          // Whether to allow repeated execution of the same index
    FRandomStream RandomStream; // UE's random number generator, used for random mode

public:
    // Default constructor
    FMultiGate()
        : CurrentIndex(0), Mode(EMultiGateMode::Sequential), bIsLooping(false), bAllowRepeat(false)
    {
        RandomStream.GenerateNewSeed(); // Initialize random number generator with a random seed
    }

    // Parameterized constructor
    FMultiGate(int InCurIdx,
               EMultiGateMode InMode,
               bool bInLooping,
               bool bInAllowRepeat)
        : CurrentIndex(InCurIdx), Mode(InMode), bIsLooping(bInLooping), bAllowRepeat(bInAllowRepeat)
    {
        if (CurrentIndex < 0)
        {
            CurrentIndex = 0;
        }

        RandomStream.GenerateNewSeed();
    }

    // Set execution mode
    void SetMode(EMultiGateMode InMode)
    {
        Mode = InMode;
    }

    // Set whether to loop
    void SetLooping(bool bInLooping)
    {
        bIsLooping = bInLooping;
    }

    // Reset MultiGate state
    void Reset()
    {
        CurrentIndex = 0;
    }

    // Set whether to allow repeat
    void SetAllowRepeat(bool bInAllowRepeat)
    {
        bAllowRepeat = bInAllowRepeat;
    }

    // Get next output index
    int32 GetNextIndex(int32 NumFunctions)
    {
        // Use switch to execute based on different modes
        switch (Mode)
        {
        // Random mode, return a random number
        case EMultiGateMode::Random:
        {
            // If there's only one function, directly return 0
            if (NumFunctions == 1)
            {
                return 0;
            }
            // Ensure not to execute the same index consecutively
            // Declare a variable to store the next random index
            int32 NextRandom;
            do
            {
                // Generate a random number between 0 and NumFunctions - 1
                NextRandom = RandomStream.RandHelper(NumFunctions);
            } while (NextRandom == CurrentIndex); // If the generated random number is the same as the current index, regenerate
            return NextRandom; // Return a random number different from the current index
        }

        // Loop mode
        case EMultiGateMode::Loop:
            if (CurrentIndex >= NumFunctions)
            {
                CurrentIndex = 0;
            }
            return CurrentIndex++;

        // Sequential mode
        case EMultiGateMode::Sequential:
        default:
            if (CurrentIndex >= NumFunctions)
            {
                // In Sequential mode, return an invalid index after executing all indices
                return INDEX_NONE;
            }
            return CurrentIndex++;
        }
    }

    // Execute MultiGate logic
    template <typename... FunctionTypes>
    void Execute(FunctionTypes &&...InFunctions)
    {
        // Get the number of input functions
        const int32 NumFunctions = sizeof...(FunctionTypes);
        // If no function is passed or the current index is out of range, return directly
        if (NumFunctions == 0 || CurrentIndex >= NumFunctions)
        {
            return;
        }

        // Use an array to store all functions
        std::function<void()> Functions[] = {std::forward<FunctionTypes>(InFunctions)...};

        // Get the next index to execute
        int32 NextIndex = GetNextIndex(NumFunctions);

        // Check if the index is valid
        if (NextIndex != INDEX_NONE && NextIndex < NumFunctions && (bAllowRepeat || NextIndex != CurrentIndex))
        {
            // Update current index
            CurrentIndex = NextIndex;
            // Execute the function corresponding to the current index
            Functions[CurrentIndex]();
        }
    }

    // Get the currently active output index
    int32 GetCurrentIndex() const
    {
        return CurrentIndex;
    }

    // Set random seed
    void SetRandomSeed(int32 NewSeed)
    {
        RandomStream.Initialize(NewSeed);
    }
};
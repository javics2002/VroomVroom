#include "VroomVroomInput.h"

std::string playerButtonName(std::string buttonName, int playerNumber)
{
    return buttonName + std::to_string(playerNumber);
}

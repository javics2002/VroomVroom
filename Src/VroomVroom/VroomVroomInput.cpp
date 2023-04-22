#include "VroomVroomInput.h"

using namespace VroomVroom;

std::string VroomVroom::playerButtonName(std::string buttonName, int playerNumber)
{
    return buttonName + std::to_string(playerNumber);
}

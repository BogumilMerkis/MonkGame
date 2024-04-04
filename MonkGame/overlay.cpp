#include <iostream>
#include "imgui.h"
#include "overlay.h"
#include <string>
#include "Dungeon.h"
#include <vector>
using namespace std;

static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
static ImGuiTreeNodeFlags tree_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Selected;
static ImGuiSelectableFlags selectable_flags = ImGuiSelectableFlags_Disabled;


void BattleOverlay::render(string monster){
    ImGui::SetNextWindowPos(ImVec2(350, 0));

    if (ImGui::Begin("Battle", 0, window_flags)) {
        ImGui::Text("Monk vs %s", monster.c_str());
    }
    ImGui::End();
}


void MapOverlay :: render(Dungeon& dungeon, int currentRoomIndex) {
    ImGui::Begin("Dungeon Map",0, window_flags);

    // Display current room
    ImGui::Text("Current Room: %d", currentRoomIndex + 1);
    ImGui::Separator();

    // Display connected rooms
    ImGui::Text("Connected Rooms:");
    const vector<Room*>& connectedRooms = dungeon.getRooms()[currentRoomIndex]->getConnectedRooms();
    for (int i = 0; i < connectedRooms.size(); ++i) {
        ImGui::Text("- Room %d", connectedRooms[i]->getRoomNumber());
        ImGui::SameLine();
        ImGui::Button("hi");
    }

    ImGui::End();
}

void overlay::render()
{
}

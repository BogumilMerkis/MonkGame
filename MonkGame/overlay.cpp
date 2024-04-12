#include <iostream>
#include "imgui.h"
#include "Overlay.h"
#include <string>
#include "Dungeon.h"
#include <vector>
#include "CharacterClass.h"
#include "PlayerCharacter.h"
#include <imgui_internal.h>

using namespace std;

static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

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
    if (currentRoomIndex >= 0 && currentRoomIndex < dungeon.getRooms().size()) {
        for (int i = 0; i < connectedRooms.size(); ++i) {
            ImGui::Text("- Room %d", connectedRooms[i]->getRoomNumber());
            ImGui::SameLine();
            ImGui::Button("hi");
        }
    }

    ImGui::End();
}

void Overlay::render()
{
}


bool CharacterCreationOverlay::render(bool showCharacterCreationWindow) {
    
        ImGui::Begin("Character Creation", &showCharacterCreationWindow, window_flags);

        // Class selection
        ImGui::Text("Select Class:");
        ImGui::RadioButton("Monk", &selectedClass, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Barbarian", &selectedClass, 2);
        ImGui::Separator();
        // Name input
        ImGui::InputText("Name", playerName, sizeof(playerName));

        // Description input
        ImGui::InputTextMultiline("Description", playerDescription, sizeof(playerDescription));

        // Slider input number of rooms in dungeon
        ImGui::SliderInt("Number of Rooms", &numRooms, 3, 16);
        bool nameFilled = strlen(playerName) > 0;
        bool descriptionFilled = strlen(playerDescription) > 0;
        bool classSelected = selectedClass != 0;

        // Enable or disable Create Character button based on input validation
        bool canCreateCharacter = nameFilled && descriptionFilled && classSelected;

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !canCreateCharacter);
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, canCreateCharacter ? 1.0f : 0.5f);

        if (ImGui::Button("Create Character")) {
            try {

                modifyCharacter();
                
                // Character created successfully, reset inputs
                playerName[0] = '\0';
                playerDescription[0] = '\0';
                selectedClass = 0;
                
                // Pop flags, end render
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
                ImGui::End();
                return false;
            }
            catch (const exception& e) {
                cout << "Unexpected Error: SEEK HELP";
            }
        }

        // Pop flags, end render
        ImGui::PopItemFlag();
        ImGui::PopStyleVar();
        ImGui::End();
        return showCharacterCreationWindow;
}

PlayerCharacter& CharacterCreationOverlay::getCharacter()
{
    return character;
}

int CharacterCreationOverlay::getNumRooms()
{
    return numRooms;
}

void CharacterCreationOverlay::modifyCharacter() {
    // Modify the character object based on user input
    character.setPlayerName(playerName);
    switch (selectedClass) {
    case 1:
        character.setCharacterClass(make_unique<Monk>());
        break;
    case 2:
        character.setCharacterClass(make_unique<Barbarian>());
        break;
    }
    character.setDescription(playerDescription);
}

CharacterCreationOverlay::CharacterCreationOverlay() : playerName{'\0'}, playerDescription{'\0'}
{
}

CharacterCreationOverlay::~CharacterCreationOverlay()
{
}

#include <iostream>
#include "Overlay.h"
#include <string>
#include "Dungeon.h"
#include <vector>
#include "CharacterClass.h"
#include "PlayerCharacter.h"
#include <imgui_internal.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>



using namespace std;

static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
void BattleOverlay::render(string monster){
    ImGui::SetNextWindowPos(ImVec2(350, 0));

    if (ImGui::Begin("Battle", 0, window_flags)) {
        ImGui::Text("Monk vs %s", monster.c_str());
    }
    ImGui::End();
}


void MapOverlay::startBattle(string monsterName) {
    // Load the goblin image

    //IDirect3DDevice9Ex_CreateTexture
    ImGui::Begin("Battle", 0, window_flags | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("             ,      ,");
    ImGui::Text("            /(.-""-.)\\");
    ImGui::Text("        |\  \/      \/  /|");
    ImGui::Text("        |\  \/      \/  /|");
    // Display the goblin image

    ImGui::Text("Prepare to fight %s!", monsterName.c_str());
    if (ImGui::Button("Start Battle")) {
        // Handle battle logic here
    }


}

void MapOverlay::render(Dungeon& dungeon, int& currentRoomIndex) {
    Room* currentRoom = dungeon.getRooms()[currentRoomIndex];
    
    ImGui::Begin("Dungeon Map",0, window_flags);
    
    // Display current room
    ImGui::Text("Current Room: %d", currentRoomIndex + 1);
    ImGui::Text("Description: %s", currentRoom->describe().c_str());
    ImGui::Separator();
    ImGui::Text("           ,      ,");
    ImGui::Text("          / (.-""-.) \\");
    ImGui::Text("      |\\  \\/      \\/  /|");
    ImGui::Text("      | \\ / =.  .= \\ / |");
    ImGui::Text("       \\( \   o\\/o   / )/");
    ImGui::Text("       \\_, '-/  \\-' ,_/");

    // Display connected rooms
   
    if (typeid(*currentRoom) == typeid(MonsterRoom)) {
        cout << "hi";
        MonsterRoom* monsterRoom = dynamic_cast<MonsterRoom*>(currentRoom);
        string buttonLabel = "Fight " + monsterRoom->getMonster()->getName();
        if (ImGui::Button(buttonLabel.c_str())) {
            // Implement your fight logic here
            startBattle(monsterRoom->getMonster()->getName());
            ImGui::End();

        }
    }
    else {
        ImGui::Text("Connected Rooms:");
        vector<Room*> connectedRooms = dungeon.getRooms()[currentRoomIndex]->getConnectedRooms();

        for (Room* room : connectedRooms) {
            string buttonLabel = "Room " + to_string(room->getRoomNumber());
            if (ImGui::Button(buttonLabel.c_str())) {
                currentRoomIndex = room->getRoomNumber() - 1;
            }
        }
    }
    ImGui::End();
}

bool CharacterCreationOverlay::render(bool showCharacterCreationWindow) {
        // Empty object examples instatiated for tooltips
        Monk monk =  Monk(); 
        Barbarian barb =  Barbarian();

        ImGui::Begin("Character Creation", &showCharacterCreationWindow, window_flags);

        // Class selection
        ImGui::Text("Select Class:");
        ImGui::RadioButton("Monk", &selectedClass, 1);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("%s Hp: %d, Attack: %d", monk.getClassDescription().c_str(), monk.getStartingHp(), monk.getStartingAttack());
        ImGui::SameLine();
        
        ImGui::RadioButton("Barbarian", &selectedClass, 2);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("%s Hp: %d, Attack: %d", barb.getClassDescription().c_str(), barb.getStartingHp(), barb.getStartingAttack());
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

        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !canCreateCharacter); // Disable button from allowing character creation
        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, canCreateCharacter ? 1.0f : 0.5f); // Change opacity alpha to 0.5f if conditions aren't met

        if (ImGui::Button("Create Character")) {
            try {
                
                modifyCharacter();
                
                // Character created successfully, reset inputs
                playerName[0] = '\0';
                playerDescription[0] = '\0';
                selectedClass = 0;
                
                // Pop flags, end render
                pop();
                return false; // close window
            }
            catch (const exception& e) {
                cout << "Unexpected Error: SEEK HELP";
            }
        }
        // Pop flags, end render
        pop();
        return showCharacterCreationWindow; // keep window
}

PlayerCharacter& CharacterCreationOverlay::getCharacter()
{
    return character;
}

int CharacterCreationOverlay::getNumRooms() const
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

void CharacterCreationOverlay::pop()
{
    ImGui::PopItemFlag();
    ImGui::PopStyleVar();
    ImGui::End();
}

CharacterCreationOverlay::CharacterCreationOverlay() : playerName{'\0'}, playerDescription{'\0'}
{
}

CharacterCreationOverlay::~CharacterCreationOverlay()
{
}

void Overlay::render(string)
{
}

#include "CharacterClass.h"
#include "Dungeon.h"
#include "LoadTexture.h"
#include "Overlay.h"
#include "PlayerCharacter.h"
#include <cstdlib>
#include "./vendor/imgui/imgui_internal.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;



bool Overlay::entityImage(string monsterName, ID3D11Device* g_pd3dDevice) // Universal Helper
{
    string path = filepath;
    int my_image_width = 0;
    int my_image_height = 0;
    ID3D11ShaderResourceView* my_texture = NULL;
    path += monsterName + ".png";
    bool ret = LoadTextureFromFile(g_pd3dDevice, path.c_str(), &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
    float aspect_ratio = float(my_image_width) / float(my_image_height);
    int new_width = int(400 * aspect_ratio);
    int new_height = int(400 * aspect_ratio);
    ImGui::Image((void*)my_texture, ImVec2(new_height, new_width));
    return true;
}

void BattleOverlay::render(Monster* monster, Room* currentRoom, PlayerCharacter& p1){
    ImGui::SetNextWindowPos(ImVec2(650, 0));

    ImGui::Begin("Battle", 0, window_flags);
    ImGui::Text("%s vs %s", p1.getName().c_str(), monster->getName().c_str());
    ImGui::Separator();
    ImGui::Text("%s", p1.getName().c_str());
    string hpText = to_string(p1.getHp()) + " / " + to_string(p1.getMaxHp());
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    ImGui::ProgressBar(float(p1.getHp()/p1.getMaxHp()), ImVec2(0.0f, 0.0f), hpText.c_str()); // Change the value as per your need
    //ImGui::Separator();
    ImGui::Spacing();

    // Draw the second health bar
    ImGui::Text("%s", monster->getName().c_str());
    ImGui::ProgressBar(0.5f, ImVec2(0.0f, 0.0f)); // Change the value as per your need
    ImGui::PopStyleColor();
    ImGui::End();
}

bool MapOverlay::render(Dungeon& dungeon, int& currentRoomIndex, ID3D11Device* g_pd3dDevice, PlayerCharacter& p1) {
    ImGui::SetNextWindowPos(ImVec2(100, 0));
    Room* currentRoom = dungeon.getRooms()[currentRoomIndex];
    ImGui::Begin("Dungeon Map",0, window_flags);

    // Display current room
    ImGui::Text("Current Room: %d", currentRoomIndex + 1);
    
    if (typeid(*currentRoom) == typeid(MonsterRoom)) { // Check if current room is a monster room
        MonsterRoom* monsterRoom = dynamic_cast<MonsterRoom*>(currentRoom); // Re-instantiate current room as a monster room for local use
   
        ImGui::Text("%s", monsterRoom->describe().c_str()); // Describe whats in the monster room
        string monsterName = monsterRoom->getMonster()->getName();
        string buttonLabel = "Fight " + monsterName;
        if (entityImage(monsterName, g_pd3dDevice)) {
            if (ImGui::Button(buttonLabel.c_str())) {
                ImGui::SameLine();
                ImGui::End();
                return true;
            }
        } 
    }else if(typeid(*currentRoom) == typeid(EmptyRoom)){ // Check if current room is an empty room
        // Display connected rooms
        ImGui::Text("%s", currentRoom->describe().c_str()); // Describe current room (not monster room)
        ImGui::Text("Connected Rooms (click to travel):");
        vector<Room*> connectedRooms = dungeon.getRooms()[currentRoomIndex]->getConnectedRooms();

        for (Room* room : connectedRooms) {
            string buttonLabel = "Room " + to_string(room->getRoomNumber());
            if (ImGui::Button(buttonLabel.c_str())) {
                currentRoomIndex = room->getRoomNumber() - 1;
            }
        }
        if (ImGui::Button("Pray"))
            p1.healHpMax();
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Heal to full hp. Current hp: %d/%d", p1.getHp(), p1.getMaxHp());

        ImGui::End();
        return false;
    }
    ImGui::End();
}

bool CharacterCreationOverlay::render(bool showCharacterCreationWindow, ID3D11Device* g_pd3dDevice) {
        // Empty object examples instatiated for tooltips
        Monk monk =  Monk(); 
        Barbarian barb =  Barbarian();

        ImGui::Begin("Character Creation", &showCharacterCreationWindow, window_flags);

        // Class selection
        ImGui::Text("Select Class:");
        ImGui::RadioButton("Monk", &selectedClass, 1);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
            ImGui::SetTooltip("%s Hp: %d, Attack: %d", monk.getClassDescription().c_str(), monk.getStartingHp(), monk.getStartingAttack());
            entityImage("Monk", g_pd3dDevice); // Display image of Monk
        }
        ImGui::SameLine();
        
        ImGui::RadioButton("Barbarian", &selectedClass, 2);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
            ImGui::SetTooltip("%s Hp: %d, Attack: %d", barb.getClassDescription().c_str(), barb.getStartingHp(), barb.getStartingAttack());
            entityImage("Barbarian", g_pd3dDevice); // Display image of Barbarian
        }
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
                
                createCharacter(selectedClass);
                // Pop flags, end render
                pop();
                return false; // close window
            }
            catch (const exception& e) {
                cout << "Unexpected Error: SEEK HELP \n" << e.what();
            }
        }
        // Pop flags, end render
        pop();
        return showCharacterCreationWindow; // keep window open just in case
}

PlayerCharacter& CharacterCreationOverlay::getCharacter()
{
    return character;
}

int CharacterCreationOverlay::getNumRooms() const
{
    return numRooms;
}

void CharacterCreationOverlay::createCharacter(int selectedClass) {
    // Modify the character object based on user input
    
    switch (selectedClass) {
    case 1: {
        character = PlayerCharacter(playerName, make_unique<Monk>(), playerDescription);
        break;
    }
    case 2: {
        character = PlayerCharacter(playerName, make_unique<Barbarian>(), playerDescription);
        break;
    }
    }
}

void Overlay::pop()
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

void Overlay::render()
{
}
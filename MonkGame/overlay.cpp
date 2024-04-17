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

bool Overlay::imageHelper(string fileName, ID3D11Device* g_pd3dDevice) // Universal Helper
{
    string path = filepath;
    int my_image_width = 0;
    int my_image_height = 0;
    ID3D11ShaderResourceView* my_texture = NULL;
    path += fileName + ".png";
    bool ret = LoadTextureFromFile(g_pd3dDevice, path.c_str(), &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
    float aspect_ratio = float(my_image_width) / float(my_image_height);
    int new_width = int(400 * aspect_ratio);
    int new_height = int(500 * aspect_ratio);
    ImGui::Image((void*)my_texture, ImVec2(new_height, new_width));
    
    my_texture->Release();

    return true;
}
void BattleOverlay::dead() {
    ImGui::Begin("Death", 0, window_flags);
    ImGui::SetWindowFontScale(3.0f);
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "YOU HAVE DIED!");
    ImGui::SetWindowFontScale(2.0f);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Exit?").x) * 0.5f);
    if (ImGui::Button("Exit?")) {
        exit(0);
    }
    ImGui::End();
}
void BattleOverlay::healthBars(Monster* monster, PlayerCharacter& p1) {
    
    string playerName = p1.getName();
    string monsterName = monster->getName();
    int playerHp = p1.getHp();
    int playerMaxHp = p1.getMaxHp();
    int monsterHp = monster->getHp();
    int monsterMaxHp = monster->getMaxHp();
    ImGui::Text("%s vs %s", playerName.c_str(), monsterName.c_str());
    ImGui::Separator();
    ImGui::Text("%s", playerName.c_str());
    string playerHpText = to_string(playerHp) + " / " + to_string(playerMaxHp);
    string monsterHpText = to_string(monsterHp) + " / " + to_string(monsterMaxHp);
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Set both progbars to red
    ImGui::ProgressBar(float(playerHp / playerMaxHp), ImVec2(0.0f, 0.0f), playerHpText.c_str()); 

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    // Draw the second health bar
    ImGui::Text("%s", monsterName.c_str());
    ImGui::ProgressBar(float(monsterHp / monsterMaxHp), ImVec2(0.0f, 0.0f), monsterHpText.c_str()); 
    ImGui::PopStyleColor();
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();
}
void BattleOverlay::playerTurn(Monster* monster, PlayerCharacter& p1, bool turn) {
    
    static int attackSuccess = 0; // 0 is waiting, 1 is fail, 2 is success
    static int defendSuccess = 0; // 0 is waiting, 1 is fail, 2 is success
    static bool changed = false;
    static bool attackButtonPressed = false;
    static bool defendButtonPressed = false;

    if (turn && p1.getHp() > 0) {
        if (!attackButtonPressed && !defendButtonPressed && ImGui::Button("Attack")) {
            attackButtonPressed = true;
            if (p1.action()) {
                attackSuccess = 2;
            }
            else {
                attackSuccess = 1;
            } 
        }
        ImGui::SameLine();
        if (!defendButtonPressed && !attackButtonPressed) { // Only display defend button is not on full hp.
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, !(p1.getHp() < p1.getMaxHp())); // Disable button from allowing character creation
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, p1.getHp() < p1.getMaxHp() ? 1.0f : 0.5f); // Change opacity alpha to 0.5f if conditions aren't met
            if (ImGui::Button("Defend")) {
                defendButtonPressed = true;
                if (p1.action()) {
                    defendSuccess = 2;
                }
                else {
                    defendSuccess = 1;
                }
            }
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }
        if ((attackButtonPressed || defendButtonPressed) && p1.getHp() > 0 && monster->getHp() > 0) {
            ImGui::SameLine();
            if (ImGui::Button("End Turn")) {
                // Reset
                changed = false;
                attackSuccess = 0;
                defendSuccess = 0;
                attackButtonPressed = false;
                defendButtonPressed = false;
                // Next turn
                turnOrder++;
            }
        }  
    }
    if (attackSuccess == 2) { // Success
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "\n%s%s", p1.getName().c_str(), p1.getAttackText().c_str());
            if (!changed) {
                monster->setHp(monster->getHp() - p1.getAttack());
                changed = true;
            }
    }
    else if (attackSuccess == 1) { // Fail
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "\n%s swings and misses the %s", p1.getName().c_str(), monster->getName().c_str());
    }
    else if (defendSuccess == 2) { // Success
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "\n%s%s", p1.getName().c_str(), p1.getDefendText().c_str());
        if (p1.getHp() != p1.getMaxHp() && !changed) {
            p1.setHp(p1.getHp() + 1); // Make change to hp
            changed = true;
        }
    }
    else if (defendSuccess == 1) { // Fail
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "\n%s tries to take a defensive stance but trips and breaks their stance", p1.getName().c_str());
    }  
}

void BattleOverlay::monsterTurn(Monster* monster, PlayerCharacter& p1, bool turn) {
    static int monsterAttackSuccess = 0; // 0 is waiting, 1 is fail, 2 is success
    static int monsterDefendSuccess = 0; // 0 is waiting, 1 is fail, 2 is success
    static bool decider;
    static bool actionUsed = false;
    srand(time(NULL));
    static bool monsterChanged = false;
    if (!turn && !actionUsed) {
        decider = monster->action();
        
        if (decider && monsterAttackSuccess == 0) {
            
            if (monster->action()) {
                monsterAttackSuccess = 2;
                
            }
            else if(!monster->action()){
                monsterAttackSuccess = 1;
            }
            actionUsed = true;
        }
        else if (!decider && monsterDefendSuccess == 0) {
            if (monster->action()) {
                monsterDefendSuccess = 2;
            }
            else if (!monster->action()){
                monsterDefendSuccess = 1;
            }
            actionUsed = true;
        }
        
    }
    if (actionUsed && monster->getHp() > 0 && p1.getHp() > 0) {
        ImGui::SameLine();
        if (ImGui::Button("End Turn")) {
            // Reset
            monsterChanged = false;
            monsterAttackSuccess = 0;
            monsterDefendSuccess = 0;
            actionUsed = false;

            // Next turn
            turnOrder++;
        }
    }
    if (monsterAttackSuccess == 2) { // Success
        ImGui::Text("\n%s", monster->getAttackText().c_str());
        if (!monsterChanged) {
            p1.setHp(p1.getHp() - monster->getAttack()); // Make change to hp
            monsterChanged = true;

        }
    }
    else if (monsterAttackSuccess == 1) { // Fail
        ImGui::Text("\n%s strikes and misses.", monster->getName().c_str());

    }
    else if (monsterDefendSuccess == 2) { // Success
        
        if (!monsterChanged && monster->getHp() != monster->getMaxHp()) {
            monster->setHp(monster->getHp() + 1);
            ImGui::Text("\n%s", monster->getDefendText().c_str());
            monsterChanged = true;
        }
        else {
            ImGui::Text("\n%s tries to recover but is already on full hp.",monster->getName());
        }
    }
    else if (monsterDefendSuccess == 1) { // Fail
        ImGui::Text("\n%s tries to stay back and recover but slips and is off balance.", monster->getName().c_str());

    }
}

void BattleOverlay::setTurnOrder(int turnOrder)
{
    this->turnOrder = turnOrder;
}

bool BattleOverlay::render(Monster* monster, Room* currentRoom, PlayerCharacter& p1, ID3D11Device* g_pd3dDevice){
    //ImGui::SetNextWindowPos(ImVec2(650, 0));
    ImGui::Begin("Battle", 0, window_flags);
    // Store commonly used getters to reduce unnecessary calls to handlers
    string playerName = p1.getName();
    string monsterName = monster->getName();
    int playerHp = p1.getHp();
    int playerMaxHp = p1.getMaxHp();
    int monsterHp = monster->getHp();
    int monsterMaxHp = monster->getMaxHp();
    bool turn = turnOrder % 2;

    healthBars(monster, p1); // render health bars
    imageHelper(monsterName, g_pd3dDevice);
    ImGui::NewLine();
    ImGui::NewLine();
    playerTurn(monster, p1, turn); // Handle player turns
    monsterTurn(monster, p1, turn); // Handle monster turns

    if (monster->getHp() <= 0) { // Monster defeated
        
        ImGui::BeginPopupModal("MonsterDeadPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("You have killed the %s", monster->getName().c_str());
        if (ImGui::Button("Close")) {
            setTurnOrder(1);
            ImGui::End();
            return false; // Close the battle overlay
        }   
    }
    else if (p1.getHp() <= 0) { // Player defeated
 
        ImGui::BeginPopupModal("PlayerDeadPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("You have died!");
        if (ImGui::Button("Close")) {
            setTurnOrder(1);
            ImGui::End();
            return false; // Close the battle overlay
        }
    }
    else {
        ImGui::End();
        return true;
    }
    ImGui::End();
}

bool MapOverlay::render(Dungeon& dungeon, int& currentRoomIndex, ID3D11Device* g_pd3dDevice, PlayerCharacter& p1, bool encounter) {
    
    static bool prayerUsedInRoom = false; // Flag to track if 'Pray' button has been pressed
    ImGui::SetNextWindowPos(ImVec2(100, 0));
    Room* currentRoom = dungeon.getRooms()[currentRoomIndex];
    ImGui::Begin("Dungeon Map",0, window_flags);
    ImGui::Text("Current HP: %d/%d", p1.getHp(), p1.getMaxHp());
    // Display current room
    ImGui::Text("Current Room: %d", currentRoomIndex + 1);

        if (typeid(*currentRoom) == typeid(MonsterRoom) && dynamic_cast<MonsterRoom*>(currentRoom)->getMonster()->getHp() > 0){ // Check if current room is a monster room
            encounter = true;
           
            MonsterRoom* monsterRoom = dynamic_cast<MonsterRoom*>(currentRoom); // Re-instantiate current room as a monster room for local use
            if (monsterRoom->getMonster()->getHp() > 0){
                ImGui::Text("%s", monsterRoom->describe().c_str()); // Describe whats in the monster room
                string monsterName = monsterRoom->getMonster()->getName();
                imageHelper(monsterName, g_pd3dDevice);
                string buttonLabel = "Fight " + monsterName;
                
                if (ImGui::Button(buttonLabel.c_str())) {
                    ImGui::SameLine();
                    ImGui::End();
                    return true;
                }
            }
        }
        if ( !encounter ){ // If there is no encounter
            
            // Display connected rooms
            if (typeid(*currentRoom) == typeid(TreasureRoom)) {
                ImGui::Text("Congratulations you reached the treasure!");
                imageHelper("TreasureRoom", g_pd3dDevice);
                ImGui::End();
                return false;
            }
            imageHelper("EmptyRoom", g_pd3dDevice);
            ImGui::Text("%s", currentRoom->describe().c_str()); // Describe current room (not monster room)
            ImGui::Text("Connected Rooms (click to travel):");
            vector<Room*> connectedRooms = dungeon.getRooms()[currentRoomIndex]->getConnectedRooms();

            for (Room* room : connectedRooms) {
                string buttonLabel = "Room " + to_string(room->getRoomNumber());
                if (ImGui::Button(buttonLabel.c_str())) {
                    currentRoomIndex = room->getRoomNumber() - 1;
                    prayerUsedInRoom = false;
                }
            }
            if (!prayerUsedInRoom && p1.getHp() < p1.getMaxHp()) {
                if (ImGui::Button("Pray")) {
                    p1.healHpMax();
                    prayerUsedInRoom = true;

                }
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    ImGui::SetTooltip("Heal to full hp. Current hp: %d/%d", p1.getHp(), p1.getMaxHp());
            }
            ImGui::End();
            return false;
        
        }
        
    
    ImGui::End();
    return false;
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
            imageHelper("Monk", g_pd3dDevice); // Display image of Monk
        }
        ImGui::SameLine();
        
        ImGui::RadioButton("Barbarian", &selectedClass, 2);
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
            ImGui::SetTooltip("%s Hp: %d, Attack: %d", barb.getClassDescription().c_str(), barb.getStartingHp(), barb.getStartingAttack());
            imageHelper("Barbarian", g_pd3dDevice); // Display image of Barbarian
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
                cout << "Unexpected Error: SEEK HELP \n";
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

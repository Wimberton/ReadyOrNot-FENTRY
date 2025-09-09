#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>
#include <ShlObj.h>
#include <tchar.h>

#include <imgui.h>

#include "SDKExt.h"
#include "Configuration.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "DetourManager.h"
#include "ActorCache.h"

// helper funcs
inline const char* GetKeyName(int key) {
    if (key == 0) {
        return "No key set";
    }

    switch (key) {
    case VK_LBUTTON: return "Left Mouse Button";
    case VK_RBUTTON: return "Right Mouse Button";
    case VK_MBUTTON: return "Middle Mouse Button";
    case VK_XBUTTON1: return "Side Mouse Button 1";
    case VK_XBUTTON2: return "Side Mouse Button 2";
    
    // Navigation keys that often get confused with numpad
    case VK_HOME: return "Home";
    case VK_END: return "End";
    case VK_PRIOR: return "Page Up";
    case VK_NEXT: return "Page Down";
    case VK_INSERT: return "Insert";
    case VK_DELETE: return "Delete";
    case VK_UP: return "Up Arrow";
    case VK_DOWN: return "Down Arrow";
    case VK_LEFT: return "Left Arrow";
    case VK_RIGHT: return "Right Arrow";
    
    // Numpad keys
    case VK_NUMPAD0: return "Numpad 0";
    case VK_NUMPAD1: return "Numpad 1";
    case VK_NUMPAD2: return "Numpad 2";
    case VK_NUMPAD3: return "Numpad 3";
    case VK_NUMPAD4: return "Numpad 4";
    case VK_NUMPAD5: return "Numpad 5";
    case VK_NUMPAD6: return "Numpad 6";
    case VK_NUMPAD7: return "Numpad 7";
    case VK_NUMPAD8: return "Numpad 8";
    case VK_NUMPAD9: return "Numpad 9";
    case VK_MULTIPLY: return "Numpad *";
    case VK_ADD: return "Numpad +";
    case VK_SEPARATOR: return "Numpad Separator";
    case VK_SUBTRACT: return "Numpad -";
    case VK_DECIMAL: return "Numpad .";
    case VK_DIVIDE: return "Numpad /";
    
    // Function keys
    case VK_F1: return "F1";
    case VK_F2: return "F2";
    case VK_F3: return "F3";
    case VK_F4: return "F4";
    case VK_F5: return "F5";
    case VK_F6: return "F6";
    case VK_F7: return "F7";
    case VK_F8: return "F8";
    case VK_F9: return "F9";
    case VK_F10: return "F10";
    case VK_F11: return "F11";
    case VK_F12: return "F12";
    
    // Other commonly used keys
    case VK_SPACE: return "Space";
    case VK_TAB: return "Tab";
    case VK_RETURN: return "Enter";
    case VK_ESCAPE: return "Escape";
    case VK_BACK: return "Backspace";
    case VK_SHIFT: return "Shift";
    case VK_CONTROL: return "Ctrl";
    case VK_MENU: return "Alt";
    case VK_CAPITAL: return "Caps Lock";
    case VK_NUMLOCK: return "Num Lock";
    case VK_SCROLL: return "Scroll Lock";
    case VK_PAUSE: return "Pause";
    case VK_SNAPSHOT: return "Print Screen";

    default: {
        static char keyName[64] = {};
        if (GetKeyNameTextA(MapVirtualKeyA(key, MAPVK_VK_TO_VSC) << 16, keyName, 64) > 0) {
            return keyName;
        }
        return "Unknown Key";
    }
    }
}

inline void HandleKeySetting(int& keyToSet, bool& waitingForKey) {
    if (waitingForKey) {
        for (int key = 0x01; key <= 0xFE; key++) {
            if (GetAsyncKeyState(key) & 0x8000) {
                if (key == VK_ESCAPE) {
                    keyToSet = 0; // Set to 0 when ESC is pressed
                    Configuration::Save();
                    waitingForKey = false;
                }
                else {
                    keyToSet = key;
                    Configuration::Save();
                    waitingForKey = false;
                }
                break;
            }
        }
    }
}

// Component Validator
inline bool IsComponentValid(const UActorComponent* Component) {
    return Component && Component->IsValidLowLevel() && !Component->IsDefaultObject();
}

// Actor Validator
inline bool IsActorValid(const AActor* Actor) {
    return Actor && Actor->IsValidLowLevel() && IsComponentValid(Actor->RootComponent) && !Actor->IsActorBeingDestroyed() && !Actor->bActorIsBeingDestroyed;
}

inline AReadyOrNotPlayerController* CachedARONPC = nullptr;
inline APlayerController* CachedAPC = nullptr;
inline AReadyOrNotCharacter* CachedARONCharacter = nullptr;
inline ABaseWeapon* CachedWeapon = nullptr;
inline UInventoryComponent* CachedInventoryComponent = nullptr;

inline std::string CurrentLevelName = "";
inline std::atomic<bool> IsLevelTransitioning{false};
inline std::mutex LevelTransitionMutex;

// Force weapon cache invalidation
inline void InvalidateWeaponCache() {
    CachedWeapon = nullptr;
}

inline void CheckForLevelTransition() {
    const UWorld* World = GetWorld();
    if (!World) return;
    
    std::string levelName = World->Name.ToString();
    std::lock_guard<std::mutex> lock(LevelTransitionMutex);
    
    if (levelName != CurrentLevelName) {
        IsLevelTransitioning.store(true);

        CachedAPC = nullptr;
        CachedARONPC = nullptr;
        CachedARONCharacter = nullptr;
        CachedWeapon = nullptr;
        CachedInventoryComponent = nullptr;
        
        // LOG("[LevelTransition] Level transition detected: %s -> %s\n", CurrentLevelName.c_str(), levelName.c_str());
        CurrentLevelName = levelName;
        
        std::thread([](std::atomic<bool>* flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            flag->store(false);
        }, &IsLevelTransitioning).detach();
    }
}

// ARONPC - Ready or Not Player Controller
inline AReadyOrNotPlayerController* GetARONPC() {
    CheckForLevelTransition();
    
    if (IsLevelTransitioning.load()) {
        return nullptr;
    }

    if (IsActorValid(CachedARONPC)) {
        return CachedARONPC;
    }

    CachedARONPC = nullptr;

    const UWorld* World = GetWorld();
    if (!World) return nullptr;
    if (World->Name.ToString() == "Lobby_P" || World->Name.ToString() == "TransitionMap") return nullptr;

    UGameInstance* GameInstance = World->OwningGameInstance;
    if (!GameInstance || !GameInstance->LocalPlayers || GameInstance->LocalPlayers.Num() <= 0) return nullptr;

    const ULocalPlayer* LocalPlayer = GameInstance->LocalPlayers[0];
    if (!LocalPlayer || !LocalPlayer->PlayerController || !LocalPlayer->PlayerController->IsA(AReadyOrNotPlayerController::StaticClass())) return nullptr;

    auto ARONPC = static_cast<AReadyOrNotPlayerController*>(LocalPlayer->PlayerController);
    return IsActorValid(ARONPC) ? CachedARONPC = ARONPC : nullptr;
}

//APC
inline APlayerController* GetAPC() {
    // Check for level transitions first
    CheckForLevelTransition();
    
    if (IsLevelTransitioning.load()) {
        return nullptr;
    }

    if (IsActorValid(CachedAPC)) {
        return CachedAPC;
    }

    CachedAPC = nullptr;

    const UWorld* World = GetWorld();
    if (!World) return nullptr;
    if (World->Name.ToString() == "Lobby_P" || World->Name.ToString() == "Level_Transition") return nullptr;

    UGameInstance* GameInstance = World->OwningGameInstance;
    if (!GameInstance || !GameInstance->LocalPlayers || GameInstance->LocalPlayers.Num() <= 0) return nullptr;

    const ULocalPlayer* LocalPlayer = GameInstance->LocalPlayers[0];
    if (!LocalPlayer || !LocalPlayer->PlayerController || !LocalPlayer->PlayerController->IsA(APlayerController::StaticClass())) return nullptr;

    auto APC = static_cast<APlayerController*>(LocalPlayer->PlayerController);
    return IsActorValid(APC) ? CachedAPC = APC : nullptr;
}

// ARON Character - Ready or Not Character
inline AReadyOrNotCharacter* GetARONCharacter() {
    if (IsLevelTransitioning.load()) {
        return nullptr;
    }
    
    if(IsActorValid(CachedARONCharacter)) {
        return CachedARONCharacter;
    }

    CachedARONCharacter = nullptr;

    AReadyOrNotPlayerController* LocalPC = GetARONPC();
    if(!IsActorValid(LocalPC)) return nullptr;

    if (!LocalPC->Character || !LocalPC->Character->IsA(AReadyOrNotCharacter::StaticClass())) return nullptr;
    
    auto ARONCharacter = static_cast<AReadyOrNotCharacter*>(LocalPC->Character);
    return IsActorValid(ARONCharacter) ? CachedARONCharacter = ARONCharacter : nullptr;
}

// Legacy function name for backward compatibility - now calls GetARONCharacter
inline AReadyOrNotCharacter* GetAHCharacter() {
    return GetARONCharacter();
}

// Cached InventoryComponent
inline UInventoryComponent* GetInventoryComp() {
    if (IsLevelTransitioning.load()) {
        return nullptr;
    }

    if (IsComponentValid(CachedInventoryComponent)) {
        return CachedInventoryComponent;
    }
    CachedInventoryComponent = nullptr;

    const UWorld* World = GetWorld();
    if (!World) return nullptr;

    AReadyOrNotPlayerController* PlayerController = GetARONPC();
    if (!IsActorValid(PlayerController)) return nullptr;

    AReadyOrNotCharacter* ReadyOrNotCharacter = GetARONCharacter();
    if (!IsActorValid(ReadyOrNotCharacter)) return nullptr;

    UInventoryComponent* Inventory = ReadyOrNotCharacter->InventoryComp;
    if (IsComponentValid(Inventory)) {
        CachedInventoryComponent = Inventory;
    }

    return CachedInventoryComponent;
}

inline ABaseWeapon* GetCurrentWeapon() {
    if (IsLevelTransitioning.load()) {
        return nullptr;
    }
    
    if (IsActorValid(CachedWeapon)) {
        return CachedWeapon;
    }

    CachedWeapon = nullptr;

    AReadyOrNotCharacter* ARONCharacter = GetARONCharacter();
    if (!IsActorValid(ARONCharacter))
        return nullptr;

    ABaseWeapon* CurrentWeapon = nullptr;

    UInventoryComponent* InventoryComp = GetInventoryComp();
    if (IsComponentValid(InventoryComp)) {
        ABaseItem* EquippedItem = InventoryComp->GetEquippedItem();
        if (IsActorValid(EquippedItem) && EquippedItem->IsA(ABaseWeapon::StaticClass())) {
            CurrentWeapon = static_cast<ABaseWeapon*>(EquippedItem);
            if (IsActorValid(CurrentWeapon)) {
                CachedWeapon = CurrentWeapon;
                return CachedWeapon;
            }
        }
    }

    return nullptr;
}

// Custom FOV Functions
inline void SetCustomFOV(float FOVValue) {
    if (!Configuration::cfg_EnableCustomFOV)
        return;
        
    SDK::APlayerController* PlayerController = GetAPC();
    if (!PlayerController || !IsActorValid(PlayerController))
        return;
    
    PlayerController->FOV(FOVValue);
}

// AimRotation Calc
inline FRotator CalculateAimRotation(const FVector& TargetLocation, const FVector& CurrentLocation) {
    FVector Direction = (TargetLocation - CurrentLocation).GetNormalized();

    FRotator AimRotation;
    AimRotation.Pitch = std::atan2(Direction.Z, std::sqrt(Direction.X * Direction.X + Direction.Y * Direction.Y)) * (180.0f / M_PI);
    AimRotation.Yaw = std::atan2(Direction.Y, Direction.X) * (180.0f / M_PI);
    AimRotation.Roll = 0;

    return AimRotation;
}
// Aim 2D Distance Calc
inline float GetDistance2D(const FVector2D& A, const FVector2D& B) {
    return std::sqrt((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
}
// Aim 3D Distance Calc
inline float GetDistance3D(const FVector& A, const FVector& B) {
    return std::sqrt(
        (A.X - B.X) * (A.X - B.X) +
        (A.Y - B.Y) * (A.Y - B.Y) +
        (A.Z - B.Z) * (A.Z - B.Z)
    );
}

enum bones {
    Root = 0,
    Hips = 1,
    Spine = 2,
    jigglebone_6 = 3,
    jigglebone_7 = 4,
    jigglebone_8 = 5,
    jigglebone_9 = 6,
    Spine1 = 7,
    Spine2 = 8,
    Spine3 = 9,
    Spine4 = 10,
    jigglebone_1 = 11,
    jigglebone_2 = 12,
    jigglebone_3 = 13,
    jigglebone_4 = 14,
    jigglebone_5 = 15,
    Neck = 16,
    Neck1 = 17,
    Neck2 = 18,
    Head = 19,
    jigglebone_22 = 20,
    jigglebone_23 = 21,
    LeftShoulder = 22,
    LeftArm = 23,
    LeftArmRoll = 24,
    jigglebone_18 = 25,
    jigglebone_19 = 26,
    LeftForeArm = 27,
    LeftForeArmRoll = 28,
    LeftHand = 29,
    LeftHandThumb1 = 30,
    LeftHandThumb2 = 31,
    LeftHandThumb3 = 32,
    LeftHandThumb4 = 33,
    LeftHandIndex = 34,
    LeftHandIndex1 = 35,
    LeftHandIndex2 = 36,
    LeftHandIndex3 = 37,
    LeftHandIndex4 = 38,
    LeftHandMiddle = 39,
    LeftHandMiddle1 = 40,
    LeftHandMiddle2 = 41,
    LeftHandMiddle3 = 42,
    LeftHandMiddle4 = 43,
    LeftHandRing = 44,
    LeftHandRing1 = 45,
    LeftHandRing2 = 46,
    LeftHandRing3 = 47,
    LeftHandRing4 = 48,
    LeftHandPinky = 49,
    LeftHandPinky1 = 50,
    LeftHandPinky2 = 51,
    LeftHandPinky3 = 52,
    LeftHandPinky4 = 53,
    Left_weapon = 54,
    LeftForeArm_s = 55,
    RightShoulder = 56,
    RightArm = 57,
    RightArmRoll = 58,
    jigglebone_20 = 59,
    jigglebone_21 = 60,
    RightForeArm = 61,
    RightForeArmRoll = 62,
    RightHand = 63,
    RightHandThumb1 = 64,
    RightHandThumb2 = 65,
    RightHandThumb3 = 66,
    RightHandThumb4 = 67,
    RightHandIndex = 68,
    RightHandIndex1 = 69,
    RightHandIndex2 = 70,
    RightHandIndex3 = 71,
    RightHandIndex4 = 72,
    RightHandMiddle = 73,
    RightHandMiddle1 = 74,
    RightHandMiddle2 = 75,
    RightHandMiddle3 = 76,
    RightHandMiddle4 = 77,
    RightHandRing = 78,
    RightHandRing1 = 79,
    RightHandRing2 = 80,
    RightHandRing3 = 81,
    RightHandRing4 = 82,
    RightHandPinky = 83,
    RightHandPinky1 = 84,
    RightHandPinky2 = 85,
    RightHandPinky3 = 86,
    RightHandPinky4 = 87,
    Right_weapon = 88,
    RightForeArm_s = 89,
    back_left_attachpoint = 90,
    back_right_attachpoint = 91,
    hip_left_attachpoint = 92,
    hip_right_attachpoint = 93,
    RightUpleg = 94,
    RightUpLegRoll = 95,
    jigglebone_24 = 96,
    jigglebone_25 = 97,
    RightLeg = 98,
    RightLegRoll = 99,
    jigglebone_26 = 100,
    jigglebone_27 = 101,
    RightFoot = 102,
    RightToeBase = 103,
    RightLeg_s = 104,
    LeftUpLeg = 105,
    LeftUpLegRoll = 106,
    jigglebone_12 = 107,
    jigglebone_13 = 108,
    LeftLeg = 109,
    LeftLegRoll = 110,
    jigglebone_14 = 111,
    jigglebone_15 = 112,
    LeftFoot = 113,
    LeftToeBase = 114,
    LeftLeg_s = 115,
    RightUpLeg_s = 116,
    LeftUpLeg_s = 117,
    VB_Right_Holder = 118,
    VB_IK_HandRoot = 119,
    VB_IK_RightHand = 120,
    VB_Gun_LeftHand = 121,
    VB_IK_LeftHand = 122,
    VB_IK_FootRoot = 123,
    VB_IK_RightFoot = 124,
    VB_IK_LeftFoot = 125,
    VB_RightLegJoint = 126,
    VB_LeftLegJoint = 127,
    VB_LeftJoint = 128,
    VB_Gun_RightHand = 129,
    VB_RightJoint = 130,
    VB_Left_Holder = 131,
    VB_AimTarget = 132
};

inline bool WorldToScreen(const SDK::FVector& worldLoc, SDK::FVector2D* screenPos)
{
    bool isOnScreen = SDK::UGameplayStatics::ProjectWorldToScreen(GetAPC(), worldLoc, screenPos, true);
    return isOnScreen;
}
inline TArray<AReadyOrNotCharacter*> GetValidActors(AActor* PawnPlayer) {
    TArray<AActor*> FoundActors;
    TArray<AReadyOrNotCharacter*> ValidActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AReadyOrNotCharacter::StaticClass(), &FoundActors);

    for (AActor* Actor : FoundActors) {
        AReadyOrNotCharacter* Character = static_cast<AReadyOrNotCharacter*>(Actor);
        if (!Character || !IsActorValid(Character)) {
            continue;
        }

        if (Actor == PawnPlayer) {
            continue;
        }

        ValidActors.Add(Character);
    }

    return ValidActors;
}

inline AActor* CurrentAimbotTarget = nullptr;
inline FName GetSelectedBoneName(int boneIndex) {
    switch (boneIndex) {
    case 0: return SDK::UKismetStringLibrary::Conv_StringToName(L"Head");          // Head
    case 1: return SDK::UKismetStringLibrary::Conv_StringToName(L"Neck");          // Neck
    case 2: return SDK::UKismetStringLibrary::Conv_StringToName(L"Spine");         // Spine
    case 3: return SDK::UKismetStringLibrary::Conv_StringToName(L"Spine1");        // Chest
    case 4: return SDK::UKismetStringLibrary::Conv_StringToName(L"Hips");          // Pelvis
    default: return SDK::UKismetStringLibrary::Conv_StringToName(L"Head");         // Default to Head
    }
}

// Convert ImU32 to ImGui's float[4] color format
inline void ImU32ToFloat4(ImU32 color, float outColor[4]) {
    outColor[0] = ((color >> IM_COL32_R_SHIFT) & 0xFF) / 255.0f; // Red
    outColor[1] = ((color >> IM_COL32_G_SHIFT) & 0xFF) / 255.0f; // Green
    outColor[2] = ((color >> IM_COL32_B_SHIFT) & 0xFF) / 255.0f; // Blue
    outColor[3] = ((color >> IM_COL32_A_SHIFT) & 0xFF) / 255.0f; // Alpha
}

// Convert float[4] color format to ImU32
inline ImU32 Float4ToImU32(const float color[4]) {
    return IM_COL32(
        static_cast<uint8_t>(color[0] * 255.0f), // Red
        static_cast<uint8_t>(color[1] * 255.0f), // Green
        static_cast<uint8_t>(color[2] * 255.0f), // Blue
        static_cast<uint8_t>(color[3] * 255.0f)  // Alpha
    );
}

#define IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)

#define StrPrinter ::_StrPrinter()

class _StrPrinter : public std::string {
public:
    _StrPrinter() = default;

    template <typename T>
    _StrPrinter& operator<<(T&& data) {
        _stream << std::forward<T>(data);
        this->std::string::operator=(_stream.str());
        return *this;
    }

    std::string operator<<(std::ostream& (*f)(std::ostream&)) const { return static_cast<std::string>(*this); }

private:
    std::stringstream _stream;
};

#define WStrPrinter ::_WStrPrinter()

class _WStrPrinter : public std::wstring {
public:
    _WStrPrinter() = default;

    template <typename T>
    _WStrPrinter& operator<<(T&& data) {
        _stream << std::forward<T>(data);
        this->std::wstring::operator=(_stream.str());
        return *this;
    }

    std::wstring operator<<(std::ostream& (*f)(std::ostream&)) const { return static_cast<std::wstring>(*this); }

private:
    std::wstringstream _stream;
};

struct vec3 {
    float x, y, z;

    explicit vec3(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) : x(x), y(y), z(z) {}

    FVector ToFVector() const { return FVector(x, y, z); }
    // Vector addition
    vec3 operator+(const vec3& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
    // Vector subtraction
    vec3 operator-(const vec3& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
    // Scalar multiplication
    vec3 operator*(const float scalar) const { return vec3(x * scalar, y * scalar, z * scalar); }
    // Dot product
    float Dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }
    // Cross product
    vec3 Cross(const vec3& other) const {
        return vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float Size() const { return std::sqrt(x * x + y * y + z * z); }

    float Distance(const vec3& other) const { return (*this - other).Size(); }

    std::string ToString() const {
        std::stringstream ss;
        ss << "vec3(" << x << ", " << y << ", " << z << ")";
        return ss.str();
    }
};

inline FString CharToWide(const char* NarrowString) {
    wchar_t WideString[1024];
    MultiByteToWideChar(CP_ACP, 0, NarrowString, -1, WideString, 1024);
    return FString(WideString);
}

template <typename SearchType>
SearchType GetFlagSingle(std::string Text, std::map<SearchType, std::vector<std::string>>& map) {
    SearchType T = static_cast<SearchType>(0);
    for (auto& Entry : map) {
        bool bFound = false;

        for (auto& Str : Entry.second) {
            if (Text.find(Str) != std::string::npos) {
                T = Entry.first;
                bFound = true;
                break;
            }
        }

        if (bFound)
            break;
    }
    return T;
}

template <typename SearchType>
SearchType GetFlagSingleEnd(std::string Text, std::map<SearchType, std::vector<std::string>>& map) {
    SearchType T = static_cast<SearchType>(0);
    for (auto& Entry : map) {
        bool bFound = false;

        for (auto& Str : Entry.second) {
            if (Text.ends_with(Str)) {
                T = Entry.first;
                bFound = true;
                break;
            }
        }

        if (bFound)
            break;
    }
    return T;
}

template <typename SearchType>
SearchType GetFlagMulti(std::string Text, std::map<SearchType, std::vector<std::string>>& map) {
    SearchType T = static_cast<SearchType>(0);
    for (auto& Entry : map) {
        for (auto& Str : Entry.second) { if (Text.find(Str) != std::string::npos) { T |= Entry.first; } }
    }
    return T;
}

template <size_t size_x>
bool AnyTrue(bool(&arr)[size_x]) {
    for (int x = 0; x < size_x; x++) {
        if (arr[x])
            return true;
    }
    return false;
}

template <size_t size_x, size_t size_y>
bool AnyTrue2D(bool(&arr)[size_x][size_y]) {
    for (int x = 0; x < size_x; x++) {
        for (int y = 0; y < size_y; y++) {
            if (arr[x][y])
                return true;
        }
    }
    return false;
}

template <size_t size_x, size_t size_y, size_t size_z>
bool AnyTrue3D(bool(&arr)[size_x][size_y][size_z]) {
    for (int x = 0; x < size_x; x++) {
        for (int y = 0; y < size_y; y++) {
            for (int z = 0; z < size_z; z++) {
                if (arr[x][y][z])
                    return true;
            }
        }
    }
    return false;
}

inline bool IsGameWindowActive() {
    const HWND foregroundWindow = GetForegroundWindow();
    TCHAR windowClassName[256];
    GetClassName(foregroundWindow, windowClassName, sizeof(windowClassName) / sizeof(TCHAR));
    return _tcscmp(windowClassName, TEXT("UnrealWindow")) == 0;
}

union FunctionPointerUnion {
    const void* ProcessEventPointer;
    void (*ProcessEventFunction)(const UObject*, UFunction*, void*);
};

#define STATIC_CLASS(CName, SearchContainer)                          \
{                                                                     \
    static class UClass* Clss = nullptr;                              \
    if (!Clss || !Clss->IsValidLowLevel() || Clss->IsDefaultObject()) \
        Clss = UObject::FindClassFast(CName);                         \
    SearchContainer.push_back(Clss);                                  \
}

inline bool IsKeyUp(const int key) {
    static bool wasKeyDown = false;
    bool isKeyDown = GetAsyncKeyState(key) & 0x8000;

    if (wasKeyDown && !isKeyDown) {
        wasKeyDown = false; 
        return true;
    }

    wasKeyDown = isKeyDown;
    return false;
}

// Vector math utilities
namespace VectorMath {

    static FVector GetVectorRight(const FRotator& Rotation) {
        const float YawRadians = Rotation.Yaw * M_PI / 180.0f;

        const float CY = std::cos(YawRadians - M_PI / 2);
        const float SY = std::sin(YawRadians - M_PI / 2);

        return FVector(CY, SY, 0.0f);
    }
}

namespace CustomMath {

    constexpr float PI = 3.14159265358979323846f;

    template <typename T>
    inline T Clamp(const T& value, const T& min, const T& max) {
        return value < min ? min : (value > max ? max : value);
    }

    template <typename T>
    inline T Abs(const T& value) { return value < 0 ? -value : value; }

    inline float DegreesToRadians(float degrees) { return degrees * (PI / 180.0f); }

    // Custom square root function
    inline float Sqrt(float value) { return std::sqrt(value); }

    // Custom square function
    template <typename T>
    inline T Square(const T& value) { return value * value; }

    // Custom arccosine function
    inline float Acos(float value) { return std::acos(Clamp(value, -1.0f, 1.0f)); }

    inline float DistanceBetweenPoints(const FVector2D& Point1, const FVector2D& Point2) {
        return sqrt(pow(Point2.X - Point1.X, 2) + pow(Point2.Y - Point1.Y, 2));
    }

    // Custom radians to degrees function
    inline float RadiansToDegrees(float radians) { return radians * (180.0f / PI); }

    inline double Fmod(double Value, double Mod) { return std::fmod(Value, Mod); }

    inline FRotator RInterpTo(const FRotator& Current, const FRotator& Target, double DeltaTime, float InterpSpeed) {
        // If no interpolation speed, just return the target
        if (InterpSpeed <= 0.0f) { return Target; }

        // Calculate the difference in each component
        double DeltaPitch = Target.Pitch - Current.Pitch;
        double DeltaYaw = Target.Yaw - Current.Yaw;
        double DeltaRoll = Target.Roll - Current.Roll;

        // Wrap angles to ensure shortest path is taken
        DeltaPitch = Fmod(DeltaPitch + 180.0, 360.0) - 180.0;
        DeltaYaw = Fmod(DeltaYaw + 180.0, 360.0) - 180.0;
        DeltaRoll = Fmod(DeltaRoll + 180.0, 360.0) - 180.0;

        // Calculate the step for each component based on the interpolation speed and delta time
        double PitchStep = DeltaPitch * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);
        double YawStep = DeltaYaw * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);
        double RollStep = DeltaRoll * Clamp(InterpSpeed * DeltaTime, 0.0, 1.0);

        // Generate the new interpolated rotation
        FRotator InterpolatedRotation;
        InterpolatedRotation.Pitch = Current.Pitch + PitchStep;
        InterpolatedRotation.Yaw = Current.Yaw + YawStep;
        InterpolatedRotation.Roll = Current.Roll + RollStep;

        return InterpolatedRotation;
    }

    inline ImVec2 addImVec2(ImVec2 a, ImVec2 b) {
        return { a.x + b.x, a.y + b.y };
    }
}

// Drawing utility functions
inline void drawTextOutlined(ImDrawList* drawList, ImVec2 pos, ImU32 color, const char* text, const ImFont* font) {
    if (!text || !drawList || !font)
        return;

    const float fontSize = font->FontSize * 1.0f;
    static const ImVec2 offsets[] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    unsigned char mainAlpha = (color >> IM_COL32_A_SHIFT) & 0xFF;

    constexpr unsigned char outlineRGB = 0; // Black
    ImU32 outlineColor = IM_COL32(outlineRGB, outlineRGB, outlineRGB, mainAlpha);

    for (const auto& offset : offsets) {
        drawList->AddText(font, fontSize, CustomMath::addImVec2(pos, offset), outlineColor, text);
    }

    drawList->AddText(font, fontSize, pos, color, text);
}

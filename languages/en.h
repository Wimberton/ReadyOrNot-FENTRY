#pragma once

// Embedded English translations for Ready or Not Cheat
// Edit this file to update English translations, then rebuild the DLL

namespace EmbeddedTranslations {
    // Visual Settings Tab Content
    static const char* EN_VISUAL_SETTINGS_CONTENT = R"(# English Language File for Ready or Not Cheat
# Format: key=value

# Main Application
window.main_title=RONFentry - Ready or Not Cheat

# Tab Names
tab.visuals=Visuals
tab.player_mods=Player Mods
tab.weapon_mods=Weapon Mods
tab.world_mods=World Mods
tab.settings_hotkeys=Settings & Hotkeys

# General Visual Settings
header.general_visual=General Visual Settings
checkbox.watermark=Watermark
tooltip.watermark=Toggle display of the custom watermark on the screen
slider.esp_thickness=ESP Thickness
tooltip.esp_thickness=Modify the line thickness of all ESP elements
combo.esp_box_style=ESP Box Style
tooltip.esp_box_style=Switch between various ESP Box layouts
esp.general.unlit_mode=Unlit Mode
tooltip.esp.unlit_mode=Enable unlit rendering mode to see through walls and lighting effects

# General ESP Settings (affect all character types)
checkbox.esp_boxes=ESP Boxes
tooltip.esp_boxes=Toggle display of ESP boxes for all character types
checkbox.esp_names_distance=Names/Distance
tooltip.esp_names_distance=Display character names and their distance from your position
checkbox.esp_health=Health Bars
tooltip.esp_health=Display character health bars - know their current health amounts
checkbox.esp_lines=Tracelines
tooltip.esp_lines=Display character tracelines - helpful in pinpointing character positions
checkbox.esp_lines_top=Tracelines From Top
tooltip.esp_lines_top=Display character tracelines from the top of the screen, not the bottom

# Player Visual Options
header.player_visual=Player Visual Options
checkbox.player_esp=Player ESP
tooltip.player_esp=Toggle display of any enabled player ESP features
checkbox.player_boxes=Player Boxes
tooltip.player_boxes=Toggle display of player ESP boxes
checkbox.player_skeleton=Player Skeleton
tooltip.player_skeleton=Display player skeletons - see their crouch/prone/facing direction
checkbox.player_names_distance=Player Names/Distance
tooltip.player_names_distance=Display player names and their distance from your player position
checkbox.player_health=Player Health
tooltip.player_health=Display player health - know their current health amounts
checkbox.player_lines=Player Lines
tooltip.player_lines=Display player tracelines - helpful in pinpointing player positions
checkbox.player_lines_top=Player Lines From Top
tooltip.player_lines_top=Display player tracelines from the top of the screen, not the bottom
slider.player_esp_distance=Player ESP Distance
tooltip.player_esp_distance=Maximum distance to show player ESP (in meters)
color.visible_esp_color=Visible ESP Color
color.hidden_esp_color=Hidden ESP Color
color.aim_target_esp_color=Aim Target ESP Color

# AI Character ESP Settings
header.ai_visual=AI Character Visual Options
label.sert_teams=SERT Teams
checkbox.sert_red_esp=SERT Red ESP
tooltip.sert_red_esp=Display ESP for SERT Red team members
checkbox.sert_red_boxes=SERT Red Boxes
checkbox.sert_red_names=SERT Red Names
checkbox.sert_red_health=SERT Red Health
checkbox.sert_red_lines=SERT Red Lines
color.sert_red_esp_color=SERT Red ESP Color

checkbox.sert_blue_esp=SERT Blue ESP
tooltip.sert_blue_esp=Display ESP for SERT Blue team members
checkbox.sert_blue_boxes=SERT Blue Boxes
checkbox.sert_blue_names=SERT Blue Names
checkbox.sert_blue_health=SERT Blue Health
checkbox.sert_blue_lines=SERT Blue Lines
color.sert_blue_esp_color=SERT Blue ESP Color

checkbox.suspect_esp=Suspect ESP
tooltip.suspect_esp=Display ESP for suspect characters
checkbox.suspect_boxes=Suspect Boxes
checkbox.suspect_names=Suspect Names
checkbox.suspect_health=Suspect Health
checkbox.suspect_lines=Suspect Lines
color.suspect_esp_color=Suspect ESP Color

checkbox.civilian_esp=Civilian ESP
tooltip.civilian_esp=Display ESP for civilian characters
checkbox.civilian_boxes=Civilian Boxes
checkbox.civilian_names=Civilian Names
checkbox.civilian_health=Civilian Health
checkbox.civilian_lines=Civilian Lines
color.civilian_esp_color=Civilian ESP Color

checkbox.squad_esp=Squad ESP
tooltip.squad_esp=Display ESP for your squad members
checkbox.squad_boxes=Squad Boxes
checkbox.squad_names=Squad Names
checkbox.squad_health=Squad Health
checkbox.squad_lines=Squad Lines
color.squad_esp_color=Squad ESP Color

checkbox.wounded_esp=Wounded ESP
tooltip.wounded_esp=Display ESP for wounded/incapacitated characters
checkbox.wounded_boxes=Wounded Boxes
checkbox.wounded_names=Wounded Names
checkbox.wounded_health=Wounded Health
checkbox.wounded_lines=Wounded Lines
color.wounded_esp_color=Wounded ESP Color

label.ai_distance_settings=AI Distance Settings
slider.ai_esp_distance=AI ESP Distance
tooltip.ai_esp_distance=Maximum distance to show AI character ESP (in meters)

# Object & Interactive ESP Settings
header.object_visual=Object & Interactive ESP
label.evidence_investigation=Evidence & Investigation
checkbox.evidence_esp=Evidence ESP
tooltip.evidence_esp=Display ESP for evidence items that can be collected
color.evidence_esp_color=Evidence ESP Color
checkbox.collected_evidence_esp=Collected Evidence ESP
tooltip.collected_evidence_esp=Display ESP for evidence that has already been collected
color.collected_evidence_esp_color=Collected Evidence ESP Color

label.items_equipment=Items & Equipment
checkbox.items_esp=Items ESP
tooltip.items_esp=Display ESP for items and equipment on the ground
color.items_esp_color=Items ESP Color

label.interactive_objects=Interactive Objects
checkbox.doors_esp=Doors ESP
tooltip.doors_esp=Display ESP for doors and entry points
color.doors_esp_color=Doors ESP Color
checkbox.traps_esp=Traps ESP
tooltip.traps_esp=Display ESP for traps and explosive devices
color.traps_esp_color=Traps ESP Color
checkbox.securables_esp=Securables ESP
tooltip.securables_esp=Display ESP for objectives that need to be secured
color.securables_esp_color=Securables ESP Color

label.object_distance_settings=Object Distance Settings
slider.object_esp_distance=Max Object ESP Distance
tooltip.object_esp_distance=Maximum distance to show object ESP (in meters)

# Debug ESP Settings
header.debug_esp=Debug ESP Options
checkbox.debug_class_names=Show Class Names
tooltip.debug_class_names=Display the actual class names of all objects for debugging
checkbox.debug_distance=Show Debug Distance
tooltip.debug_distance=Display distance in the debug class name display
slider.debug_max_distance=Debug Max Distance
tooltip.debug_max_distance=Maximum distance to show debug class names (in meters)
warning.debug_performance=WARNING: Debug mode may cause performance impact!
text.debug_usage_help=Use debug mode to identify class names of objects for ESP development and configuration.

)";

    // Player Mods Tab Content
    static const char* EN_PLAYER_MODS_CONTENT = R"(
# Player Mods Tab
header.player_settings=Player Settings
checkbox.no_flash_concussion=No Flash / Concussion
tooltip.no_flash_concussion=Disable all flashbang and concussion effects
checkbox.godmode=Godmode
tooltip.godmode=Infinite health - automatically heal all limbs and revive when incapacitated
checkbox.no_inventory_weight=No Inventory Weight
tooltip.no_inventory_weight=Remove all weight restrictions on your player inventory
checkbox.unlock_all_items=Unlock All Items
tooltip.unlock_all_items=Automatically unlock all weapon and character customization items

# Movement Settings
header.movement_settings=Movement Settings
checkbox.no_player_stagger=No Player Stagger
tooltip.no_player_stagger=Weapons and shots will no longer stagger your player
checkbox.infinite_stamina=Infinite Stamina
tooltip.infinite_stamina=Remove the limitations of any stamina loss. Infinite sprinting
checkbox.noclip=NoClip
tooltip.noclip=Fly around the map. Be careful in multiplayer modes
checkbox.speed_hack=Speed Hack
tooltip.speed_hack=Move around the map super fast - useful for tactical positioning
slider.speed_multiplier=Speed Multiplier
tooltip.speed_multiplier=Multiplier for movement speed
esp.general.custom_fov=Custom FOV
tooltip.esp.custom_fov=Enable custom field of view adjustment for better visibility
esp.general.custom_fov_value=FOV Value
tooltip.esp.custom_fov_value=Set the field of view angle (60-130 degrees)
checkbox.teleport_to_target=Teleport to Target
tooltip.teleport_to_target=Enable hotkey to teleport to your aimed target

# Name Changer
header.name_changer=Name Changer
text.name_changer=Name Changer
input.player_name_hint=Enter new player name...
tooltip.player_name_input=Enter the name you want to change to
button.set_name=Set Name
tooltip.set_name_button=Click to change your player name

# Notifications
notification.teleport_attempt=Attempting teleport...
notification.name_changed=Name changed to
notification.name_change_failed=Failed to change player name
notification.empty_name=Please enter a name before changing
)";

    // Weapon Mods Tab Content
    static const char* EN_WEAPON_MODS_CONTENT = R"(
# Weapon Mods Tab
header.aimbot_settings=Aimbot Settings
checkbox.enable_aimbot=Enable Aimbot
tooltip.enable_aimbot=Enable locking onto the selected player bone with your weapons
checkbox.visibility_check=Visibility Check
tooltip.visibility_check=Make the aimbot only enable when the player is fully visible to you
checkbox.show_fov_circle=Show FOV Circle
tooltip.show_fov_circle=Display the FOV circle - The aimbot will only trigger if the players are within the circle
checkbox.magic_bullet=Silent Aimbot
tooltip.magic_bullet=Makes bullets hit target without visibly moving your aim - more undetectable
combo.target_bone=Target Bone
tooltip.target_bone=Select which bone the aimbot should target
slider.aimbot_smoothing=Aimbot Smoothing
tooltip.aimbot_smoothing=Modify the smoothing factor of the aimbot. Lower values = snappier, rage aimbot. Higher = more legit.
slider.fov_radius=FOV Radius
tooltip.fov_radius=Modify the circle radius in which the aimbot will lock onto players
slider.fov_opacity=FOV Opacity
tooltip.fov_opacity=Customize the opacity of the FOV circle

# Weapon Settings
header.weapon_settings=Weapon Settings
checkbox.no_recoil_spread=No Recoil / Spread
tooltip.no_recoil_spread=Remove firing recoil of your weapons and make bullets super accurate
checkbox.infinite_ammo=Infinite Ammo
tooltip.infinite_ammo=Modify and set any ammo count. Infinite ammo
checkbox.instant_reload=Instant Reload
tooltip.instant_reload=Reload weapons instantly without animation delays
slider.ammo_amount=Ammo Amount
tooltip.ammo_amount=Set the amount of ammo
)";

    // Settings & Hotkeys Tab Content
    static const char* EN_SETTINGS_HOTKEYS_CONTENT = R"(
# Settings & Hotkeys Tab
header.ui_settings=UI Settings
text.select_theme=Select Theme
button.edit_custom_theme=Edit Custom Theme
tooltip.edit_custom_theme_disabled=Select 'Custom Theme' to begin editing.
popup.custom_theme_editor=Custom Theme Editor
text.widgets=Widgets
button.save=Save
button.close_without_saving=Close Without Saving
text.undo_changes=Undo Changes.

# Hotkey Settings
header.hotkey_settings=HotKey Settings
text.aimkey=Aimkey: %s
button.set_aimkey=Set Aimkey
text.press_key_cancel=Press a key... (ESC to cancel)
text.press_key_unbind=Press a key... (ESC to unbind)
tooltip.aimkey=Key to hold for aimbot activation
text.speed_key=Speed Key: %s
button.set_speed_key=Set Speed Key
text.noclip_key=NoClip Key: %s
button.set_noclip_key=Set NoClip Key
text.teleport_key=Teleport Key: %s
button.set_teleport_key=Set Teleport Key
text.unified_teleport_key=Unified Teleport Key: %s
button.set_unified_teleport_key=Set Unified Teleport Key
tooltip.unified_teleport=Teleport to your current aim target, or forward if no target

# Teleport Settings Headers and UI
header.teleport_settings=Teleport Settings
checkbox.unified_teleport=Enable Teleport
checkbox.smaller_tp_targeting=Smaller TP Targeting
slider.tp_fov_radius=TP FOV Radius
tooltip.smaller_tp_targeting=Only teleport to targets within a smaller FOV radius for precision
tooltip.tp_fov_radius=The FOV radius for smaller teleport targeting
slider.actor_teleport_offset=Actor Teleport Offset
tooltip.actor_teleport_offset=Distance to offset from target actor to avoid clipping inside
slider.tp_no_target_distance=Forward Teleport Distance
tooltip.tp_no_target_distance=Distance to teleport forward when no target is selected

# Suspect Mods Settings
header.suspect_mods=Suspect Mods
checkbox.no_suspect_firefight=No Suspect Firefight
tooltip.no_suspect_firefight=Prevents suspects and civilians from engaging in combat by resetting their combat state
checkbox.disarm_all_suspects=Disarm All Suspects
tooltip.disarm_all_suspects=Prevents suspects and civilians from drawing, raising, or using weapons
checkbox.force_suspect_surrender=Force Suspect Surrender
tooltip.force_suspect_surrender=Forces all suspects to immediately surrender and comply with commands
checkbox.auto_comply_suspects=Auto-Comply Suspects
tooltip.auto_comply_suspects=Makes suspects automatically comply to all commands with maximum responsiveness

# Trap Mods Settings
header.trap_mods=Trap Mods
checkbox.disable_all_traps=Disable All Traps
tooltip.disable_all_traps=Disables all door traps and tripwires to prevent them from triggering

# Language Selection
combo.language=Language
tooltip.language=Select your preferred language
note.translation_feedback=Found a translation error? Let us know in Discord!

# Notifications
notification.first_use=Thank you for using our RONFentry, Ready or Not Cheat. To get started, open the menu with the 'INSERT' key.

# Hotkey Names
key.no_key_set=No key set
key.left_mouse=Left Mouse Button
key.right_mouse=Right Mouse Button
key.middle_mouse=Middle Mouse Button
key.side_mouse_1=Side Mouse Button 1
key.side_mouse_2=Side Mouse Button 2
key.unknown_key=Unknown Key

# Function Keys
key.f1=F1
key.f2=F2
key.f3=F3
key.f4=F4
key.f5=F5
key.f6=F6
key.f7=F7
key.f8=F8
key.f9=F9
key.f10=F10
key.f11=F11
key.f12=F12

# Special Keys
key.caps_lock=Caps Lock
key.scroll_lock=Scroll Lock
key.num_lock=Num Lock
key.tab=Tab
key.space=Space
key.enter=Enter
key.escape=Escape
key.backspace=Backspace
key.insert=Insert
key.delete=Delete
key.home=Home
key.end=End
key.page_up=Page Up
key.page_down=Page Down

# Arrow Keys
key.up_arrow=Up Arrow
key.down_arrow=Down Arrow
key.left_arrow=Left Arrow
key.right_arrow=Right Arrow

# Modifier Keys
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Left Shift
key.right_shift=Right Shift
key.left_ctrl=Left Ctrl
key.right_ctrl=Right Ctrl
key.left_alt=Left Alt
key.right_alt=Right Alt

# Numpad Keys
key.numpad_0=Numpad 0
key.numpad_1=Numpad 1
key.numpad_2=Numpad 2
key.numpad_3=Numpad 3
key.numpad_4=Numpad 4
key.numpad_5=Numpad 5
key.numpad_6=Numpad 6
key.numpad_7=Numpad 7
key.numpad_8=Numpad 8
key.numpad_9=Numpad 9
key.numpad_multiply=Numpad *
key.numpad_add=Numpad +
key.numpad_subtract=Numpad -
key.numpad_decimal=Numpad .
key.numpad_divide=Numpad /
key.numpad_enter=Numpad Enter
)";

    // Gamemode Mods Tab Content
    static const char* EN_GAMEMODE_MODS_CONTENT = R"(
# Gamemode Mods Tab
tab.gamemode_mods=Gamemode Mods

# Gamemode Features
header.gamemode_features=Gamemode Features
header.gamemode_info=Gamemode Information

# Incapacitate All
text.incapacitate_all_key=Incapacitate All Key: %s
button.set_incapacitate_key=Set Incapacitate All Key
tooltip.incapacitate_all=Instantly incapacitate all suspects and civilians on the map

# Instant Win
text.instant_win_key=Instant Win Key: %s
button.set_instant_win_key=Set Instant Win Key
tooltip.instant_win=Instantly complete the mission with success

# Instant Lose
text.instant_lose_key=Instant Lose Key: %s
button.set_instant_lose_key=Set Instant Lose Key
tooltip.instant_lose=Instantly fail the mission

# Arrest All
text.arrest_all_key=Arrest All Key: %s
button.set_arrest_all_key=Set Arrest All Key
tooltip.arrest_all=Instantly arrest all suspects and civilians on the map

# Report All
text.report_all_key=Report All Key: %s
button.set_report_all_key=Set Report All Key
tooltip.report_all=Instantly report all suspects and civilians on the map

# Collect All Evidence
text.collect_all_evidence_key=Collect All Evidence Key: %s
button.set_collect_all_evidence_key=Set Collect All Evidence Key
tooltip.collect_all_evidence=Instantly collect all evidence items on the map

# Information Text
info.gamemode_features=These features allow you to manipulate the game state and mission outcome. Use with caution as they will affect your mission scoring.
info.incapacitate_desc=Incapacitate All: Instantly incapacitates all hostile suspects and civilians, making them unable to move or fight.
info.instant_win_desc=Instant Win: Immediately ends the mission with a successful completion. This will affect your mission statistics.
info.instant_lose_desc=Instant Lose: Immediately fails the current mission. Use this if you want to quickly restart or exit a mission.
info.arrest_all_desc=Arrest All: Automatically arrests all suspects and civilians on the map, potentially contributing to mission objectives.
info.report_all_desc=Report All: Automatically reports all suspects and civilians on the map to TOC (Tactical Operations Center).
)";

    // Combine all sections into the final content
    static const char* ENGLISH_CONTENT = []() {
        static std::string combined = std::string(EN_VISUAL_SETTINGS_CONTENT) + 
                                     std::string(EN_PLAYER_MODS_CONTENT) + 
                                     std::string(EN_WEAPON_MODS_CONTENT) + 
                                     std::string(EN_GAMEMODE_MODS_CONTENT) + 
                                     std::string(EN_SETTINGS_HOTKEYS_CONTENT);
        return combined.c_str();
    }();
}
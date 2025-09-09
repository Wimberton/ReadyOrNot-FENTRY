#pragma once

#include "Configuration.h"
#include "Utils.h"
#include "ReadyornotOverlay.h"
#include "LocalizationManager.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace ESP_VisualSettings {
    inline void Show() {

        ImGui::Columns(2, nullptr, false);

        if (ImGui::CollapsingHeader((LOC("header.general_visual") + "##GeneralVisualSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Checkbox(LOC("checkbox.watermark").c_str(), &Configuration::bShowWatermark)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.watermark").c_str());

            if (ImGui::Checkbox(LOC("esp.general.unlit_mode").c_str(), &Configuration::cfg_EnableUnlitMode)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.esp.unlit_mode").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.esp_thickness").c_str(), &Configuration::cfg_ESPThickness, 1.0f, 2.0f, "%.5f")) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.esp_thickness").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo(LOC("combo.esp_box_style").c_str(), &Configuration::cfg_AimbotBox, espBoxStyles, BOX_STYLES_COUNT)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.esp_box_style").c_str());
        }

        if (ImGui::CollapsingHeader((LOC("header.debug_esp") + "##DebugESPSettingsHeader").c_str())) {
          if (ImGui::Checkbox(LOC("checkbox.debug_class_names").c_str(), &Configuration::cfg_ShowDebugClassNames)) {
              Configuration::Save();
          }
          if (ImGui::IsItemHovered())
              ImGui::SetTooltip(LOC("tooltip.debug_class_names").c_str());
          
          if (ImGui::Checkbox(LOC("checkbox.debug_distance").c_str(), &Configuration::cfg_ShowDebugDistance)) {
              Configuration::Save();
          }
          if (ImGui::IsItemHovered())
              ImGui::SetTooltip(LOC("tooltip.debug_distance").c_str());
          
          float debugDistanceInMeters = Configuration::cfg_DebugMaxDistance / 100.0f;
          ImGui::SetNextItemWidth(200.0f);
          if (ImGui::SliderFloat(LOC("slider.debug_max_distance").c_str(), &debugDistanceInMeters, 10.0f, 500.0f)) {
              Configuration::cfg_DebugMaxDistance = debugDistanceInMeters * 100.0f;
              Configuration::Save();
          }
          if (ImGui::IsItemHovered())
              ImGui::SetTooltip(LOC("tooltip.debug_max_distance").c_str());
          
          ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), LOC("warning.debug_performance").c_str());
          ImGui::TextWrapped(LOC("text.debug_usage_help").c_str());
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader((LOC("header.player_visual") + "##PlayerVisualSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Checkbox(LOC("checkbox.player_esp").c_str(), &Configuration::cfg_DrawPlayerESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.player_esp").c_str());

            if (Configuration::cfg_DrawPlayerESP) {
                if (ImGui::Checkbox(LOC("checkbox.player_boxes").c_str(), &Configuration::cfg_DrawPlayerBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.player_boxes").c_str());

                if (ImGui::Checkbox(LOC("checkbox.player_names_distance").c_str(), &Configuration::cfg_DrawPlayerNames)) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.player_names_distance").c_str());

                if (ImGui::Checkbox(LOC("checkbox.player_health").c_str(), &Configuration::cfg_DrawPlayerHealth)) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.player_health").c_str());

                if (ImGui::Checkbox(LOC("checkbox.player_lines").c_str(), &Configuration::cfg_DrawPlayerLines)) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.player_lines").c_str());

                if (ImGui::Checkbox(LOC("checkbox.player_lines_top").c_str(), &Configuration::cfg_DrawPlayerLinesTop)) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.player_lines_top").c_str());

                float PdistanceInMeters = Configuration::cfg_MaxPlayerESPDistance / 100.0f;
                ImGui::SetNextItemWidth(200.0f);
                if (ImGui::SliderFloat(LOC("slider.player_esp_distance").c_str(), &PdistanceInMeters, 10.0f, 1000.0f)) {
                    Configuration::cfg_MaxPlayerESPDistance = PdistanceInMeters * 100.0f;
                    Configuration::Save();
                }

                ImU32ToFloat4(PlayerESPColorVisible, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.visible_esp_color").c_str(), tempPlayerColor)) {
                    PlayerESPColorVisible = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }

                ImU32ToFloat4(PlayerESPColorNonVisible, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.hidden_esp_color").c_str(), tempPlayerColor)) {
                    PlayerESPColorNonVisible = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }

                ImU32ToFloat4(PlayerESPColorAimed, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.aim_target_esp_color").c_str(), tempPlayerColor)) {
                    PlayerESPColorAimed = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }
        }

        // AI Character ESP Settings
        if (ImGui::CollapsingHeader((LOC("header.ai_visual") + "##AIVisualSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            // SERT Red Team
            if (ImGui::Checkbox(LOC("checkbox.sert_red_esp").c_str(), &Configuration::cfg_DrawSERTRedESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.sert_red_esp").c_str());

            float AIdistanceInMeters = Configuration::cfg_MaxAIESPDistance / 100.0f;
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.ai_esp_distance").c_str(), &AIdistanceInMeters, 10.0f, 1000.0f)) {
                Configuration::cfg_MaxAIESPDistance = AIdistanceInMeters * 100.0f;
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.ai_esp_distance").c_str());

            if (Configuration::cfg_DrawSERTRedESP) {
                if (ImGui::Checkbox(LOC("checkbox.sert_red_boxes").c_str(), &Configuration::cfg_DrawSERTRedBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_red_names").c_str(), &Configuration::cfg_DrawSERTRedNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_red_health").c_str(), &Configuration::cfg_DrawSERTRedHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_red_lines").c_str(), &Configuration::cfg_DrawSERTRedLines)) {
                    Configuration::Save();
                }

                ImU32ToFloat4(SERTRedESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.sert_red_esp_color").c_str(), tempPlayerColor)) {
                    SERTRedESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // SERT Blue Team
            if (ImGui::Checkbox(LOC("checkbox.sert_blue_esp").c_str(), &Configuration::cfg_DrawSERTBlueESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.sert_blue_esp").c_str());

            if (Configuration::cfg_DrawSERTBlueESP) {
                if (ImGui::Checkbox(LOC("checkbox.sert_blue_boxes").c_str(), &Configuration::cfg_DrawSERTBlueBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_blue_names").c_str(), &Configuration::cfg_DrawSERTBlueNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_blue_health").c_str(), &Configuration::cfg_DrawSERTBlueHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.sert_blue_lines").c_str(), &Configuration::cfg_DrawSERTBlueLines)) {
                    Configuration::Save();
                }

                ImU32ToFloat4(SERTBlueESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.sert_blue_esp_color").c_str(), tempPlayerColor)) {
                    SERTBlueESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Suspects
            if (ImGui::Checkbox(LOC("checkbox.suspect_esp").c_str(), &Configuration::cfg_DrawSuspectESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.suspect_esp").c_str());

            if (Configuration::cfg_DrawSuspectESP) {
                if (ImGui::Checkbox(LOC("checkbox.suspect_boxes").c_str(), &Configuration::cfg_DrawSuspectBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.suspect_names").c_str(), &Configuration::cfg_DrawSuspectNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.suspect_health").c_str(), &Configuration::cfg_DrawSuspectHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.suspect_lines").c_str(), &Configuration::cfg_DrawSuspectLines)) {
                    Configuration::Save();
                }

                ImU32ToFloat4(SuspectESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.suspect_esp_color").c_str(), tempPlayerColor)) {
                    SuspectESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Civilians
            if (ImGui::Checkbox(LOC("checkbox.civilian_esp").c_str(), &Configuration::cfg_DrawCivilianESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.civilian_esp").c_str());

            if (Configuration::cfg_DrawCivilianESP) {
                if (ImGui::Checkbox(LOC("checkbox.civilian_boxes").c_str(), &Configuration::cfg_DrawCivilianBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.civilian_names").c_str(), &Configuration::cfg_DrawCivilianNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.civilian_health").c_str(), &Configuration::cfg_DrawCivilianHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.civilian_lines").c_str(), &Configuration::cfg_DrawCivilianLines)) {
                    Configuration::Save();
                }
                
                ImU32ToFloat4(CivilianESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.civilian_esp_color").c_str(), tempPlayerColor)) {
                    CivilianESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Squad
            if (ImGui::Checkbox(LOC("checkbox.squad_esp").c_str(), &Configuration::cfg_DrawSquadESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.squad_esp").c_str());

            if (Configuration::cfg_DrawSquadESP) {
                if (ImGui::Checkbox(LOC("checkbox.squad_boxes").c_str(), &Configuration::cfg_DrawSquadBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.squad_names").c_str(), &Configuration::cfg_DrawSquadNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.squad_health").c_str(), &Configuration::cfg_DrawSquadHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.squad_lines").c_str(), &Configuration::cfg_DrawSquadLines)) {
                    Configuration::Save();
                }

                ImU32ToFloat4(SquadESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.squad_esp_color").c_str(), tempPlayerColor)) {
                    SquadESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Wounded Characters
            if (ImGui::Checkbox(LOC("checkbox.wounded_esp").c_str(), &Configuration::cfg_DrawWoundedESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.wounded_esp").c_str());

            if (Configuration::cfg_DrawWoundedESP) {
                if (ImGui::Checkbox(LOC("checkbox.wounded_boxes").c_str(), &Configuration::cfg_DrawWoundedBoxes)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.wounded_names").c_str(), &Configuration::cfg_DrawWoundedNames)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.wounded_health").c_str(), &Configuration::cfg_DrawWoundedHealth)) {
                    Configuration::Save();
                }
                if (ImGui::Checkbox(LOC("checkbox.wounded_lines").c_str(), &Configuration::cfg_DrawWoundedLines)) {
                    Configuration::Save();
                }

                ImU32ToFloat4(WoundedESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.wounded_esp_color").c_str(), tempPlayerColor)) {
                    WoundedESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }
        }

        // Object & Interactive ESP Settings
        if (ImGui::CollapsingHeader((LOC("header.object_visual") + "##ObjectESPSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            
            // Evidence ESP
            if (ImGui::Checkbox(LOC("checkbox.evidence_esp").c_str(), &Configuration::cfg_DrawEvidenceESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.evidence_esp").c_str());

            float ObjectDistanceInMeters = Configuration::cfg_MaxObjectESPDistance / 100.0f;
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.object_esp_distance").c_str(), &ObjectDistanceInMeters, 10.0f, 500.0f)) {
                Configuration::cfg_MaxObjectESPDistance = ObjectDistanceInMeters * 100.0f;
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.object_esp_distance").c_str());

            if (Configuration::cfg_DrawEvidenceESP) {
                ImU32ToFloat4(EvidenceESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.evidence_esp_color").c_str(), tempPlayerColor)) {
                    EvidenceESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Collected Evidence ESP
            if (ImGui::Checkbox(LOC("checkbox.collected_evidence_esp").c_str(), &Configuration::cfg_DrawCollectedEvidenceESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.collected_evidence_esp").c_str());

            if (Configuration::cfg_DrawCollectedEvidenceESP) {
                ImU32ToFloat4(CollectedEvidenceESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.collected_evidence_esp_color").c_str(), tempPlayerColor)) {
                    CollectedEvidenceESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }
            
            // Items ESP
            if (ImGui::Checkbox(LOC("checkbox.items_esp").c_str(), &Configuration::cfg_DrawItemsESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.items_esp").c_str());

            if (Configuration::cfg_DrawItemsESP) {
                ImU32ToFloat4(ItemsESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.items_esp_color").c_str(), tempPlayerColor)) {
                    ItemsESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }
            
            // Doors ESP
            if (ImGui::Checkbox(LOC("checkbox.doors_esp").c_str(), &Configuration::cfg_DrawDoorsESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.doors_esp").c_str());

            if (Configuration::cfg_DrawDoorsESP) {
                ImU32ToFloat4(DoorsESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.doors_esp_color").c_str(), tempPlayerColor)) {
                    DoorsESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }

            // Traps ESP
            if (ImGui::Checkbox(LOC("checkbox.traps_esp").c_str(), &Configuration::cfg_DrawTrapsESP)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.traps_esp").c_str());

            if (Configuration::cfg_DrawTrapsESP) {
                ImU32ToFloat4(TrapsESPColor, tempPlayerColor);
                if (ImGui::ColorEdit4(LOC("color.traps_esp_color").c_str(), tempPlayerColor)) {
                    TrapsESPColor = Float4ToImU32(tempPlayerColor);
                    Configuration::Save();
                }
            }
        }
    }
}
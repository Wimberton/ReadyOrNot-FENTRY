#pragma once

#include "Configuration.h"
#include "Utils.h"
#include "ReadyornotOverlay.h"
#include "LocalizationManager.h"
#include "PlayerFeatures.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Player_ModSettings {
    inline void Show() {

        ImGui::Columns(2, nullptr, false);

        if (ImGui::CollapsingHeader((LOC("header.player_settings") + "##PlayerSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            if (ImGui::Checkbox(LOC("checkbox.godmode").c_str(), &Configuration::cfg_EnableGodmode)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.godmode").c_str());
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader((LOC("header.movement_settings") + "##MovementSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            if (ImGui::Checkbox(LOC("checkbox.noclip").c_str(), &Configuration::cfg_EnableNoClip)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.noclip").c_str());

            if (ImGui::Checkbox(LOC("checkbox.speed_hack").c_str(), &Configuration::cfg_EnableSpeedhack)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.speed_hack").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.speed_multiplier").c_str(), &Configuration::cfg_speedPlayerValue, 1.0f, 3.0f, "%1.0f")) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.speed_multiplier").c_str());

            if (ImGui::Checkbox(LOC("esp.general.custom_fov").c_str(), &Configuration::cfg_EnableCustomFOV)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.esp.custom_fov").c_str());

            if (Configuration::cfg_EnableCustomFOV) {
                ImGui::SetNextItemWidth(200.0f);
                if (ImGui::SliderFloat(LOC("esp.general.custom_fov_value").c_str(), &Configuration::cfg_CustomFOV, 60.0f, 130.0f, "%.0f")) {
                    Configuration::Save();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.esp.custom_fov_value").c_str());
            }
        }
    }
}
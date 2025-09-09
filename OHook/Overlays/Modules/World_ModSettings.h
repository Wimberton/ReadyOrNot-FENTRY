#pragma once

#include "Configuration.h"
#include "Utils.h"
#include "ReadyornotOverlay.h"
#include "LocalizationManager.h"
#include "PlayerFeatures.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace World_ModSettings {
    inline void Show() {

        ImGui::Columns(2, nullptr, false);

        if (ImGui::CollapsingHeader((LOC("header.suspect_mods") + "##SuspectModsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            
            if (ImGui::Checkbox(LOC("checkbox.no_suspect_firefight").c_str(), &Configuration::cfg_NoSuspectFirefight)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.no_suspect_firefight").c_str());

            if (ImGui::Checkbox(LOC("checkbox.disarm_all_suspects").c_str(), &Configuration::cfg_DisarmAllSuspects)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.disarm_all_suspects").c_str());

            if (ImGui::Checkbox(LOC("checkbox.force_suspect_surrender").c_str(), &Configuration::cfg_ForceSuspectSurrender)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.force_suspect_surrender").c_str());

            if (ImGui::Checkbox(LOC("checkbox.auto_comply_suspects").c_str(), &Configuration::cfg_AutoComplySuspects)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.auto_comply_suspects").c_str());
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader((LOC("header.trap_mods") + "##TrapModsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            
            if (ImGui::Checkbox(LOC("checkbox.disable_all_traps").c_str(), &Configuration::cfg_DisableAllTraps)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.disable_all_traps").c_str());
        }
    }
}
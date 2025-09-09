#pragma once

#include "Configuration.h"
#include "Utils.h"
#include "ReadyornotOverlay.h"
#include "LocalizationManager.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Weapon_ModSettings {
    inline void Show() {

        ImGui::Columns(2, nullptr, false);

        if (ImGui::CollapsingHeader((LOC("header.aimbot_settings") + "##AimbotSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Checkbox(LOC("checkbox.enable_aimbot").c_str(), &Configuration::cfg_EnableAimbot)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.enable_aimbot").c_str());

            if (ImGui::Checkbox(LOC("checkbox.visibility_check").c_str(), &Configuration::cfg_AimVisCheck)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.visibility_check").c_str());

            if (ImGui::Checkbox(LOC("checkbox.show_fov_circle").c_str(), &Configuration::cfg_DrawFOVCircle)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.show_fov_circle").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo(LOC("combo.target_bone").c_str(), &Configuration::cfg_AimbotTargetBone, boneTargets, BONE_TARGETS_COUNT)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.target_bone").c_str());

            ImGui::SetNextItemWidth(200.0);
            if (ImGui::SliderFloat(LOC("slider.aimbot_smoothing").c_str(), &Configuration::cfg_AimbotSmoothing, 1.0f, 100.0f)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.aimbot_smoothing").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.fov_radius").c_str(), &Configuration::cfg_FOVRadius, 3.0f, 280.0f, "%1.0f")) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.fov_radius").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderFloat(LOC("slider.fov_opacity").c_str(), &Configuration::cfg_CircleAlpha, 0.1f, 1.0f)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.fov_opacity").c_str());
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader((LOC("header.weapon_settings") + "##WeaponSettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Checkbox(LOC("checkbox.no_recoil_spread").c_str(), &Configuration::cfg_AimbotNoSpread)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.no_recoil_spread").c_str());

            if (ImGui::Checkbox(LOC("checkbox.infinite_ammo").c_str(), &Configuration::cfg_InfiniteAmmo)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.infinite_ammo").c_str());

            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::SliderInt(LOC("slider.ammo_amount").c_str(), &Configuration::cfg_CustomAmmoCount, 30, 3000)) {
                Configuration::Save();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.ammo_amount").c_str());
        }
    }
}
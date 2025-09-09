#pragma once

#include "Configuration.h"
#include "Utils.h"
#include "ReadyornotOverlay.h"
#include "LocalizationManager.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Fentry_Settings {
    inline void Show() {

        ImGui::Columns(2, nullptr, false);

        if (ImGui::CollapsingHeader((LOC("header.ui_settings") + "##FentrySettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            // Language selection dropdown
            static const char* languageNames[] = { "English", "Español", "Português", "中文" };
            int currentLang = static_cast<int>(LocalizationManager::GetCurrentLanguage());
            
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo("##LanguageSelector", &currentLang, languageNames, IM_ARRAYSIZE(languageNames))) {
                LocalizationManager::SetLanguage(static_cast<Language>(currentLang));
            }
            ImGui::SameLine();
            ImGui::Text("%s", LOC("combo.language").c_str());
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("%s", LOC("tooltip.language").c_str());
            }
            
            // Translation feedback note
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f)); // Light gray color
            ImGui::TextWrapped("%s", LOC("note.translation_feedback").c_str());
            ImGui::PopStyleColor();
            
            ImGui::Spacing();
            
            ImGui::SetNextItemWidth(200.0f);
            if (ImGui::Combo("##ThemesCombo", &Configuration::selectedTheme, ReadyornotOverlay::themes, IM_ARRAYSIZE(ReadyornotOverlay::themes))) {
                switch (Configuration::selectedTheme) {
                case 0: // Origin
                    ImGui::StyleColorsDark();
                    Configuration::Save();
                    break;
                case 1: // Spectrum Light
                    ImGui::Spectrum::StyleColorsSpectrum();
                    Configuration::Save();
                    break;
                case 2: // Magma
                    ImGui::Magma::StyleColorsMagma();
                    Configuration::Save();
                    break;
                case 3: // Custom theme
                    Configuration::ApplyCustomTheme();
                    Configuration::Save();
                    break;
                default:
                    break;
                }
            }
            ImGui::SameLine();
            ImGui::Text(LOC("text.select_theme").c_str());

            ImGuiStyle* style = &ImGui::GetStyle();
            auto guiColor = style->Colors;

            static int selectedColor = -1;
            static std::string currentColorName = LOC("text.widgets");

            static bool openCustomThemePopup = false;

            if (Configuration::selectedTheme != 3) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, (Configuration::selectedTheme == 3));
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, style->Alpha * 0.25f);
                ImGui::Button(LOC("button.edit_custom_theme").c_str());
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();

                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(LOC("tooltip.edit_custom_theme_disabled").c_str());
            }
            else {
                if (ImGui::Button(LOC("button.edit_custom_theme").c_str())) {
                    openCustomThemePopup = true;

                    previousColors.clear();

                    for (int i = 0; i < ImGuiCol_COUNT; ++i) {
                        ImVec4 col = style->Colors[i];
                        previousColors[i] = col;
                    }
                }
            }

            if (ImGui::BeginPopupModal((LOC("popup.custom_theme_editor") + "##CustomThemeEditor").c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
                if (ImGui::BeginCombo(LOC("text.widgets").c_str(), currentColorName.c_str())) {
                    for (const auto& colorPair : GuiColors) {
                        int colorEnum = colorPair.first;
                        const std::string& colorName = colorPair.second;

                        bool isSelected = (selectedColor == colorEnum);
                        if (ImGui::Selectable(colorName.c_str(), isSelected)) {
                            selectedColor = colorEnum;
                            currentColorName = colorName;
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                if (selectedColor != -1) {
                    ImVec4& color = style->Colors[selectedColor];

                    ImGui::Text("%s color", currentColorName.c_str());
                    ImGui::SameLine();
                    if (ImGui::ColorEdit4("##GuiColorPicker", reinterpret_cast<float*>(&color), ImGuiColorEditFlags_NoInputs)) {
                        auto colorIt = Configuration::customColors.find(selectedColor);
                        if (colorIt != Configuration::customColors.end()) {
                            if (colorIt->second != color) {
                                colorIt->second = color;
                            }
                        }
                        else {
                            Configuration::customColors.insert(std::make_pair(selectedColor, color));
                        }
                        style->Colors[selectedColor] = color;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Undo##UndoGuiColor")) {
                        // Undo colour function
                        auto it = previousColors.find(selectedColor);
                        auto colorIt = Configuration::customColors.find(selectedColor);
                        if (it != previousColors.end()) {
                            style->Colors[selectedColor] = it->second;
                            colorIt->second = it->second;
                        }
                    }
                    if (ImGui::IsItemHovered())
                        ImGui::SetTooltip(LOC("text.undo_changes").c_str());

                    ImGui::BeginGroupPanel("Widget Preview");
                    {
                        ImGui::Spacing();

                        // Widget preview
                        GetWidgetForPreview(selectedColor);

                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();
                }

                ImGui::Separator();
                float windowWidth = ImGui::GetWindowSize().x;
                float buttonWidth = 160.0f * 2 + ImGui::GetStyle().ItemSpacing.x;
                ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);

                // Save button
                if (ImGui::Button(LOC("button.save").c_str(), ImVec2(160, 0))) {
                    // Save to config.
                    Configuration::Save();
                    openCustomThemePopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();

                // Cancel button
                if (ImGui::Button(LOC("button.close_without_saving").c_str(), ImVec2(160, 0))) {
                    // Restore old colors.
                    auto colorIt = Configuration::customColors.find(selectedColor);
                    for (auto& it : previousColors) {
                        int idx = it.first;
                        ImVec4 col = it.second;
                        style->Colors[idx] = col;
                        colorIt->second = col;
                    }

                    previousColors.clear();
                    openCustomThemePopup = false;
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            if (openCustomThemePopup) {
                ImGui::OpenPopup((LOC("popup.custom_theme_editor") + "##CustomThemeEditor").c_str());
            }
        }

        ImGui::NextColumn();

        if (ImGui::CollapsingHeader((LOC("header.hotkey_settings") + "##PlayerHotKeySettingsHeader").c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::Text(LOC("text.aimkey").c_str(), GetKeyName(Configuration::cfg_AimbotKey));
            if (!waitingForKey) {
                if (ImGui::Button(LOC("button.set_aimkey").c_str())) {
                    waitingForKey = true;
                }
            }
            else {
                ImGui::Text(LOC("text.press_key_cancel").c_str());
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(LOC("tooltip.aimkey").c_str());

            HandleKeySetting(Configuration::cfg_AimbotKey, waitingForKey);

            ImGui::Text(LOC("text.speed_key").c_str(), GetKeyName(Configuration::cfg_SpeedKey));
            if (!waitingForSpeedKey) {
                if (ImGui::Button(LOC("button.set_speed_key").c_str())) {
                    waitingForSpeedKey = true;
                }
            }
            else {
                ImGui::Text(LOC("text.press_key_unbind").c_str());
            }

            HandleKeySetting(Configuration::cfg_SpeedKey, waitingForSpeedKey);

            ImGui::Text(LOC("text.noclip_key").c_str(), GetKeyName(Configuration::cfg_NoClipKey));
            if (!waitingForNoClipKey) {
                if (ImGui::Button(LOC("button.set_noclip_key").c_str())) {
                    waitingForNoClipKey = true;
                }
            }
            else {
                ImGui::Text(LOC("text.press_key_unbind").c_str());
            }

            HandleKeySetting(Configuration::cfg_NoClipKey, waitingForNoClipKey);
        }
    }
}
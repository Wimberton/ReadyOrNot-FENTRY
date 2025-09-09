#pragma once

// Embedded Chinese translations for Ready or Not Cheat
// Edit this file to update Chinese translations, then rebuild the DLL

namespace EmbeddedTranslations {
    // Visual Settings Tab Content
    static const char* ZH_VISUAL_SETTINGS_CONTENT = R"(# Ready or Not 作弊器中文语言文件
# 格式: 键=值

# 主应用程序
window.main_title=RONFentry - Ready or Not 作弊器

# 选项卡名称
tab.visuals=视觉
tab.player_mods=玩家模组
tab.weapon_mods=武器模组
tab.world_mods=世界模组
tab.settings_hotkeys=设置和热键

# 通用视觉设置
header.general_visual=通用视觉设置
checkbox.watermark=水印
tooltip.watermark=切换屏幕上自定义水印的显示
slider.esp_thickness=ESP粗细
tooltip.esp_thickness=修改所有ESP元素的线条粗细
combo.esp_box_style=ESP框样式
tooltip.esp_box_style=在各种ESP框布局之间切换
esp.general.unlit_mode=无光照模式
tooltip.esp.unlit_mode=启用无光照渲染模式以透视墙壁和光照效果

# 通用ESP设置（影响所有角色类型）
checkbox.esp_boxes=ESP框
tooltip.esp_boxes=切换所有角色类型的ESP框显示
checkbox.esp_names_distance=名称/距离
tooltip.esp_names_distance=显示角色名称和他们从你位置的距离
checkbox.esp_health=生命值条
tooltip.esp_health=显示角色生命值条 - 了解他们当前的生命值数量
checkbox.esp_lines=追踪线
tooltip.esp_lines=显示角色追踪线 - 有助于精确定位角色位置
checkbox.esp_lines_top=从顶部显示追踪线
tooltip.esp_lines_top=从屏幕顶部显示角色追踪线，而不是从底部

# 玩家视觉选项
header.player_visual=玩家视觉选项
checkbox.player_esp=玩家ESP
tooltip.player_esp=切换显示任何已启用的玩家ESP功能
checkbox.player_boxes=玩家框
tooltip.player_boxes=切换显示玩家ESP框
checkbox.player_skeleton=玩家骨架
tooltip.player_skeleton=显示玩家骨架 - 查看他们的蹲下/俯卧/面向方向
checkbox.player_names_distance=玩家名称/距离
tooltip.player_names_distance=显示玩家名称和他们从您玩家位置的距离
checkbox.player_health=玩家生命值
tooltip.player_health=显示玩家生命值 - 了解他们当前的生命值数量
checkbox.player_lines=玩家线条
tooltip.player_lines=显示玩家追踪线 - 有助于精确定位玩家位置
checkbox.player_lines_top=从顶部显示玩家线条
tooltip.player_lines_top=从屏幕顶部显示玩家追踪线，而不是从底部
slider.player_esp_distance=玩家ESP距离
tooltip.player_esp_distance=显示玩家ESP的最大距离（以米为单位）
color.visible_esp_color=可见ESP颜色
color.hidden_esp_color=隐藏ESP颜色
color.aim_target_esp_color=瞥准目标ESP颜色

# AI角色ESP设置
header.ai_visual=AI角色视觉选项
label.sert_teams=SERT小队
checkbox.sert_red_esp=SERT红队ESP
tooltip.sert_red_esp=为SERT红队成员显示ESP
checkbox.sert_red_boxes=SERT红队框
checkbox.sert_red_names=SERT红队名称
checkbox.sert_red_health=SERT红队生命值
checkbox.sert_red_lines=SERT红队线条
color.sert_red_esp_color=SERT红队ESP颜色

checkbox.sert_blue_esp=SERT蓝队ESP
tooltip.sert_blue_esp=为SERT蓝队成员显示ESP
checkbox.sert_blue_boxes=SERT蓝队框
checkbox.sert_blue_names=SERT蓝队名称
checkbox.sert_blue_health=SERT蓝队生命值
checkbox.sert_blue_lines=SERT蓝队线条
color.sert_blue_esp_color=SERT蓝队ESP颜色

checkbox.suspect_esp=嫌疑人ESP
tooltip.suspect_esp=为嫌疑人角色显示ESP
checkbox.suspect_boxes=嫌疑人框
checkbox.suspect_names=嫌疑人名称
checkbox.suspect_health=嫌疑人生命值
checkbox.suspect_lines=嫌疑人线条
color.suspect_esp_color=嫌疑人ESP颜色

checkbox.civilian_esp=平民ESP
tooltip.civilian_esp=为平民角色显示ESP
checkbox.civilian_boxes=平民框
checkbox.civilian_names=平民名称
checkbox.civilian_health=平民生命值
checkbox.civilian_lines=平民线条
color.civilian_esp_color=平民ESP颜色

checkbox.squad_esp=小队ESP
tooltip.squad_esp=为您的小队成员显示ESP
checkbox.squad_boxes=小队框
checkbox.squad_names=小队名称
checkbox.squad_health=小队生命值
checkbox.squad_lines=小队线条
color.squad_esp_color=小队ESP颜色

checkbox.wounded_esp=受伤ESP
tooltip.wounded_esp=为受伤/丧失行动能力的角色显示ESP
checkbox.wounded_boxes=受伤框
checkbox.wounded_names=受伤名称
checkbox.wounded_health=受伤生命值
checkbox.wounded_lines=受伤线条
color.wounded_esp_color=受伤ESP颜色

label.ai_distance_settings=AI距离设置
slider.ai_esp_distance=AI ESP距离
tooltip.ai_esp_distance=显示AI角色ESP的最大距离（以米为单位）

# 物体和交互ESP设置
header.object_visual=物体和交互ESP
label.evidence_investigation=证据和调查
checkbox.evidence_esp=证据ESP
tooltip.evidence_esp=为可以收集的证据物品显示ESP
color.evidence_esp_color=证据ESP颜色
checkbox.collected_evidence_esp=已收集证据ESP
tooltip.collected_evidence_esp=为已经收集的证据显示ESP
color.collected_evidence_esp_color=已收集证据ESP颜色

label.items_equipment=物品和装备
checkbox.items_esp=物品ESP
tooltip.items_esp=为地上的物品和装备显示ESP
color.items_esp_color=物品ESP颜色

label.interactive_objects=交互物体
checkbox.doors_esp=门ESP
tooltip.doors_esp=为门和入口点显示ESP
color.doors_esp_color=门ESP颜色
checkbox.traps_esp=陷阱ESP
tooltip.traps_esp=为陷阱和爆炸装置显示ESP
color.traps_esp_color=陷阱ESP颜色
checkbox.securables_esp=可保护物ESP
tooltip.securables_esp=为需要保护的目标显示ESP
color.securables_esp_color=可保护物ESP颜色

label.object_distance_settings=物体距离设置
slider.object_esp_distance=最大物体ESP距离
tooltip.object_esp_distance=显示物体ESP的最大距离（以米为单位）

# 调试ESP设置
header.debug_esp=调试ESP选项
checkbox.debug_class_names=显示类名
tooltip.debug_class_names=显示所有对象的实际类名以便调试
checkbox.debug_distance=显示调试距离
tooltip.debug_distance=在调试类名显示中显示距离
slider.debug_max_distance=调试最大距离
tooltip.debug_max_distance=显示调试类名的最大距离（以米为单位）
warning.debug_performance=警告：调试模式可能会影响性能！
text.debug_usage_help=使用调试模式来识别对象的类名，以便进行ESP开发和配置。

)";

    // Player Mods Tab Content
    static const char* ZH_PLAYER_MODS_CONTENT = R"(
# 玩家模组选项卡
header.player_settings=玩家设置
checkbox.no_flash_concussion=无闪光/震晃
tooltip.no_flash_concussion=禁用所有闪光弹和震晃效果
checkbox.godmode=上帝模式
tooltip.godmode=无限生命值 - 自动治疗所有肢体并在丧失行动能力时复活
checkbox.no_inventory_weight=无物品栏重量
tooltip.no_inventory_weight=移除玩家物品栏的所有重量限制
checkbox.unlock_all_items=解锁所有物品
tooltip.unlock_all_items=自动解锁所有武器和角色自定义物品

# 移动设置
header.movement_settings=移动设置
checkbox.no_player_stagger=无玩家摔倒
tooltip.no_player_stagger=武器和射击不再让您的玩家摔倒
checkbox.infinite_stamina=无限耐力
tooltip.infinite_stamina=移除任何耐力损失的限制。无限冲刺
checkbox.noclip=穿墙
tooltip.noclip=在地图中飞行。在多人游戏模式中要小心
checkbox.speed_hack=速度修改
tooltip.speed_hack=在地图中超快移动 - 对战术定位很有用
slider.speed_multiplier=速度倍数
tooltip.speed_multiplier=移动速度的倍数
esp.general.custom_fov=自定义FOV
tooltip.esp.custom_fov=启用自定义视野角度调整以获得更好的可见性
esp.general.custom_fov_value=FOV值
tooltip.esp.custom_fov_value=设置视野角度（60-130度）
checkbox.teleport_to_target=传送到目标
tooltip.teleport_to_target=启用热键传送到您瞥准的目标

# 名称修改器
header.name_changer=名称修改器
text.name_changer=名称修改器
input.player_name_hint=输入新的玩家名称...
tooltip.player_name_input=输入您想要更改为的名称
button.set_name=设置名称
tooltip.set_name_button=点击更改您的玩家名称

# 通知
notification.teleport_attempt=尝试传送...
notification.name_changed=名称已更改为
notification.name_change_failed=更改玩家名称失败
notification.empty_name=请在更改前输入名称
)";

    // Weapon Mods Tab Content
    static const char* ZH_WEAPON_MODS_CONTENT = R"(
# 武器模组选项卡
header.aimbot_settings=自动瞥准设置
checkbox.enable_aimbot=启用自动瞥准
tooltip.enable_aimbot=启用武器锁定所选玩家骨骼
checkbox.visibility_check=可见性检查
tooltip.visibility_check=使自动瞥准仅在玩家对您完全可见时启用
checkbox.show_fov_circle=显示FOV圆圈
tooltip.show_fov_circle=显示FOV圆圈 - 自动瞥准仅在玩家在圆圈内时才会触发
checkbox.magic_bullet=静默自动瞥准
tooltip.magic_bullet=使子弹命中目标而不显示移动您的瞥准 - 更不易被发现
combo.target_bone=目标骨骼
tooltip.target_bone=选择自动瞥准应该面对的骨骼
slider.aimbot_smoothing=自动瞥准平滑
tooltip.aimbot_smoothing=修改自动瞥准的平滑因子。较低的值 = 更快、狂暴的自动瞥准。较高 = 更合法。
slider.fov_radius=FOV半径
tooltip.fov_radius=修改自动瞥准锁定玩家的圆圈半径
slider.fov_opacity=FOV不透明度
tooltip.fov_opacity=自定义FOV圆圈的不透明度

# 武器设置
header.weapon_settings=武器设置
checkbox.no_recoil_spread=无后坐力/散布
tooltip.no_recoil_spread=移除武器的射击后坐力并使子弹超级精准
checkbox.infinite_ammo=无限弹药
tooltip.infinite_ammo=修改并设置任何弹药数量。无限弹药
checkbox.instant_reload=瞬间重新装弹
tooltip.instant_reload=瞬间重新装弹武器，无动画延迟
slider.ammo_amount=弹药数量
tooltip.ammo_amount=设置弹药数量
)";

    // Settings & Hotkeys Tab Content
    static const char* ZH_SETTINGS_HOTKEYS_CONTENT = R"(
# 设置和热键选项卡
header.ui_settings=UI设置
text.select_theme=选择主题
button.edit_custom_theme=编辑自定义主题
tooltip.edit_custom_theme_disabled=选择'自定义主题'开始编辑。
popup.custom_theme_editor=自定义主题编辑器
text.widgets=组件
button.save=保存
button.close_without_saving=不保存关闭
text.undo_changes=撤销更改。

# 热键设置
header.hotkey_settings=热键设置
text.aimkey=瞥准键: %s
button.set_aimkey=设置瞥准键
text.press_key_cancel=按下一个键...（ESC取消）
text.press_key_unbind=按下一个键...（ESC解绑）
tooltip.aimkey=按住以激活自动瞥准的键
text.speed_key=速度键: %s
button.set_speed_key=设置速度键
text.noclip_key=穿墙键: %s
button.set_noclip_key=设置穿墙键
text.teleport_key=传送键: %s
button.set_teleport_key=设置传送键
text.unified_teleport_key=统一传送键: %s
button.set_unified_teleport_key=设置统一传送键
tooltip.unified_teleport=传送到您当前瞥准目标，或如果没有目标则向前传送

# 传送设置标题和UI
header.teleport_settings=传送设置
checkbox.unified_teleport=启用传送
checkbox.smaller_tp_targeting=更小的TP定向
slider.tp_fov_radius=TP FOV半径
tooltip.smaller_tp_targeting=仅传送到更小 FOV 半径内的目标以获得精度
tooltip.tp_fov_radius=更小传送定向的FOV半径
slider.actor_teleport_offset=角色传送偏移
tooltip.actor_teleport_offset=从目标角色偏移的距离，以避免卡在里面
slider.tp_no_target_distance=向前传送距离
tooltip.tp_no_target_distance=当没有目标被选中时向前传送的距离

# 嫌疑人模组设置
header.suspect_mods=嫌疑人模组
checkbox.no_suspect_firefight=无嫌疑人枪战
tooltip.no_suspect_firefight=通过重置战斗状态防止嫌疑人和平民参与战斗
checkbox.disarm_all_suspects=解除所有嫌疑人武装
tooltip.disarm_all_suspects=防止嫌疑人和平民抽取、举起或使用武器
checkbox.force_suspect_surrender=强制嫌疑人投降
tooltip.force_suspect_surrender=强制所有嫌疑人立即投降并遵守命令
checkbox.auto_comply_suspects=自动遵守嫌疑人
tooltip.auto_comply_suspects=使嫌疑人以最大响应性自动遵守所有命令

# 陷阱模组设置
header.trap_mods=陷阱模组
checkbox.disable_all_traps=禁用所有陷阱
tooltip.disable_all_traps=禁用所有门陷阱和绊网以防止它们触发

# 语言选择
combo.language=语言
tooltip.language=选择您首选的语言
note.translation_feedback=发现翻译错误？请在Discord中告诉我们！

# 通知
notification.first_use=感谢您使用我们的RONFentry, Ready or Not作弊器。要开始使用，请按'INSERT'键打开菜单。

# 热键名称
key.no_key_set=未设置键
key.left_mouse=鼠标左键
key.right_mouse=鼠标右键
key.middle_mouse=鼠标中键
key.side_mouse_1=鼠标侧键1
key.side_mouse_2=鼠标侧键2
key.unknown_key=未知键

# 功能键
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

# 特殊键
key.caps_lock=大写锁定
key.scroll_lock=滚动锁定
key.num_lock=数字锁定
key.tab=Tab
key.space=空格键
key.enter=回车键
key.escape=Esc键
key.backspace=退格键
key.insert=Insert键
key.delete=Delete键
key.home=Home键
key.end=End键
key.page_up=Page Up
key.page_down=Page Down

# 箭头键
key.up_arrow=上箭头
key.down_arrow=下箭头
key.left_arrow=左箭头
key.right_arrow=右箭头

# 修饰键
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=左Shift
key.right_shift=右Shift
key.left_ctrl=左Ctrl
key.right_ctrl=右Ctrl
key.left_alt=左Alt
key.right_alt=右Alt

# 数字键盘键
key.numpad_0=数字键盘 0
key.numpad_1=数字键盘 1
key.numpad_2=数字键盘 2
key.numpad_3=数字键盘 3
key.numpad_4=数字键盘 4
key.numpad_5=数字键盘 5
key.numpad_6=数字键盘 6
key.numpad_7=数字键盘 7
key.numpad_8=数字键盘 8
key.numpad_9=数字键盘 9
key.numpad_multiply=数字键盘 *
key.numpad_add=数字键盘 +
key.numpad_subtract=数字键盘 -
key.numpad_decimal=数字键盘 .
key.numpad_divide=数字键盘 /
key.numpad_enter=数字键盘回车键
)";

    // Gamemode Mods Tab Content
    static const char* ZH_GAMEMODE_MODS_CONTENT = R"(
# 游戏模式模组选项卡
tab.gamemode_mods=游戏模式模组

# 游戏模式功能
header.gamemode_features=游戏模式功能
header.gamemode_info=游戏模式信息

# 使所有人丧失行动能力
text.incapacitate_all_key=使所有人丧失行动能力键: %s
button.set_incapacitate_key=设置使所有人丧失行动能力键
tooltip.incapacitate_all=立即使地图上所有嫌疑人和平民丧失行动能力

# 立即胜利
text.instant_win_key=立即胜利键: %s
button.set_instant_win_key=设置立即胜利键
tooltip.instant_win=立即成功完成任务

# 立即失败
text.instant_lose_key=立即失败键: %s
button.set_instant_lose_key=设置立即失败键
tooltip.instant_lose=立即任务失败

# 逮捕所有人
text.arrest_all_key=逮捕所有人键: %s
button.set_arrest_all_key=设置逮捕所有人键
tooltip.arrest_all=立即逮捕地图上所有嫌疑人和平民

# 报告所有人
text.report_all_key=报告所有人键: %s
button.set_report_all_key=设置报告所有人键
tooltip.report_all=立即报告地图上所有嫌疑人和平民

# 收集所有证据
text.collect_all_evidence_key=收集所有证据键: %s
button.set_collect_all_evidence_key=设置收集所有证据键
tooltip.collect_all_evidence=立即收集地图上所有证据物品

# 信息文本
info.gamemode_features=这些功能允许您操纵游戏状态和任务结果。谨慎使用，因为它们将影响您的任务评分。
info.incapacitate_desc=使所有人丧失行动能力：立即使所有敌对嫌疑人和平民丧失行动能力，使他们无法移动或战斗。
info.instant_win_desc=立即胜利：立即以成功完成结束任务。这将影响您的任务统计数据。
info.instant_lose_desc=立即失败：立即失败当前任务。如果您想快速重新开始或退出任务，请使用此选项。
info.arrest_all_desc=逮捕所有人：自动逮捕地图上所有嫌疑人和平民，可能有助于任务目标。
info.report_all_desc=报告所有人：自动向TOC（战术行动中心）报告地图上所有嫌疑人和平民。
)";

    // Combine all sections into the final content
    static const char* CHINESE_CONTENT = []() {
        static std::string combined = std::string(ZH_VISUAL_SETTINGS_CONTENT) + 
                                     std::string(ZH_PLAYER_MODS_CONTENT) + 
                                     std::string(ZH_WEAPON_MODS_CONTENT) + 
                                     std::string(ZH_GAMEMODE_MODS_CONTENT) + 
                                     std::string(ZH_SETTINGS_HOTKEYS_CONTENT);
        return combined.c_str();
    }();
}
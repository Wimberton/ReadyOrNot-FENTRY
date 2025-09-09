#pragma once

// Embedded Portuguese translations for Ready or Not Cheat
// Edit this file to update Portuguese translations, then rebuild the DLL

namespace EmbeddedTranslations {
    // Visual Settings Tab Content
    static const char* PT_VISUAL_SETTINGS_CONTENT = R"(# Arquivo de Idioma Português para Ready or Not Cheat
# Formato: chave=valor

# Aplicação Principal
window.main_title=RONFentry - Ready or Not Cheat

# Nomes das Abas
tab.visuals=Visuais
tab.player_mods=Mods do Jogador
tab.weapon_mods=Mods de Armas
tab.world_mods=Mods do Mundo
tab.settings_hotkeys=Configurações e Teclas

# Configurações Visuais Gerais
header.general_visual=Configurações Visuais Gerais
checkbox.watermark=Marca d'Água
tooltip.watermark=Alternar exibição da marca d'água personalizada na tela
slider.esp_thickness=Espessura do ESP
tooltip.esp_thickness=Modificar a espessura da linha de todos os elementos ESP
combo.esp_box_style=Estilo da Caixa ESP
tooltip.esp_box_style=Alternar entre vários layouts de Caixa ESP
esp.general.unlit_mode=Modo Sem Iluminação
tooltip.esp.unlit_mode=Habilitar modo de renderização sem iluminação para ver através de paredes e efeitos de luz

# Configurações ESP Gerais (afetam todos os tipos de personagens)
checkbox.esp_boxes=Caixas ESP
tooltip.esp_boxes=Alternar exibição de caixas ESP para todos os tipos de personagens
checkbox.esp_names_distance=Nomes/Distância
tooltip.esp_names_distance=Exibir nomes dos personagens e sua distância da sua posição
checkbox.esp_health=Barras de Saúde
tooltip.esp_health=Exibir barras de saúde dos personagens - conhecer suas quantidades de saúde atuais
checkbox.esp_lines=Linhas de Rastreamento
tooltip.esp_lines=Exibir linhas de rastreamento dos personagens - útil para localizar posições dos personagens
checkbox.esp_lines_top=Linhas de Rastreamento do Topo
tooltip.esp_lines_top=Exibir linhas de rastreamento dos personagens do topo da tela, não da parte inferior

# Opções Visuais do Jogador
header.player_visual=Opções Visuais do Jogador
checkbox.player_esp=ESP do Jogador
tooltip.player_esp=Alternar exibição de qualquer recurso ESP do jogador habilitado
checkbox.player_boxes=Caixas do Jogador
tooltip.player_boxes=Alternar exibição de caixas ESP do jogador
checkbox.player_skeleton=Esqueleto do Jogador
tooltip.player_skeleton=Exibir esqueletos do jogador - ver sua direção agachado/deitado/orientação
checkbox.player_names_distance=Nomes/Distância do Jogador
tooltip.player_names_distance=Exibir nomes dos jogadores e sua distância da sua posição
checkbox.player_health=Saúde do Jogador
tooltip.player_health=Exibir saúde do jogador - conhecer suas quantidades de saúde atuais
checkbox.player_lines=Linhas do Jogador
tooltip.player_lines=Exibir linhas de rastreamento do jogador - útil para localizar posições dos jogadores
checkbox.player_lines_top=Linhas do Jogador do Topo
tooltip.player_lines_top=Exibir linhas de rastreamento do jogador do topo da tela, não da parte inferior
slider.player_esp_distance=Distância ESP do Jogador
tooltip.player_esp_distance=Distância máxima para mostrar ESP do jogador (em metros)
color.visible_esp_color=Cor ESP Visível
color.hidden_esp_color=Cor ESP Oculta
color.aim_target_esp_color=Cor ESP Alvo da Mira

# Configurações ESP de Personagens IA
header.ai_visual=Opções Visuais de Personagens IA
label.sert_teams=Equipes SERT
checkbox.sert_red_esp=ESP SERT Vermelho
tooltip.sert_red_esp=Exibir ESP para membros da equipe SERT Vermelha
checkbox.sert_red_boxes=Caixas SERT Vermelho
checkbox.sert_red_names=Nomes SERT Vermelho
checkbox.sert_red_health=Saúde SERT Vermelho
checkbox.sert_red_lines=Linhas SERT Vermelho
color.sert_red_esp_color=Cor ESP SERT Vermelho

checkbox.sert_blue_esp=ESP SERT Azul
tooltip.sert_blue_esp=Exibir ESP para membros da equipe SERT Azul
checkbox.sert_blue_boxes=Caixas SERT Azul
checkbox.sert_blue_names=Nomes SERT Azul
checkbox.sert_blue_health=Saúde SERT Azul
checkbox.sert_blue_lines=Linhas SERT Azul
color.sert_blue_esp_color=Cor ESP SERT Azul

checkbox.suspect_esp=ESP de Suspeitos
tooltip.suspect_esp=Exibir ESP para personagens suspeitos
checkbox.suspect_boxes=Caixas de Suspeitos
checkbox.suspect_names=Nomes de Suspeitos
checkbox.suspect_health=Saúde de Suspeitos
checkbox.suspect_lines=Linhas de Suspeitos
color.suspect_esp_color=Cor ESP de Suspeitos

checkbox.civilian_esp=ESP de Civis
tooltip.civilian_esp=Exibir ESP para personagens civis
checkbox.civilian_boxes=Caixas de Civis
checkbox.civilian_names=Nomes de Civis
checkbox.civilian_health=Saúde de Civis
checkbox.civilian_lines=Linhas de Civis
color.civilian_esp_color=Cor ESP de Civis

checkbox.squad_esp=ESP do Esquadrão
tooltip.squad_esp=Exibir ESP para membros do seu esquadrão
checkbox.squad_boxes=Caixas do Esquadrão
checkbox.squad_names=Nomes do Esquadrão
checkbox.squad_health=Saúde do Esquadrão
checkbox.squad_lines=Linhas do Esquadrão
color.squad_esp_color=Cor ESP do Esquadrão

checkbox.wounded_esp=ESP de Feridos
tooltip.wounded_esp=Exibir ESP para personagens feridos/incapacitados
checkbox.wounded_boxes=Caixas de Feridos
checkbox.wounded_names=Nomes de Feridos
checkbox.wounded_health=Saúde de Feridos
checkbox.wounded_lines=Linhas de Feridos
color.wounded_esp_color=Cor ESP de Feridos

label.ai_distance_settings=Configurações de Distância IA
slider.ai_esp_distance=Distância ESP IA
tooltip.ai_esp_distance=Distância máxima para mostrar ESP de personagens IA (em metros)

# Configurações ESP de Objetos e Interativos
header.object_visual=ESP de Objetos e Interativos
label.evidence_investigation=Evidência e Investigação
checkbox.evidence_esp=ESP de Evidência
tooltip.evidence_esp=Exibir ESP para itens de evidência que podem ser coletados
color.evidence_esp_color=Cor ESP de Evidência
checkbox.collected_evidence_esp=ESP de Evidência Coletada
tooltip.collected_evidence_esp=Exibir ESP para evidência que já foi coletada
color.collected_evidence_esp_color=Cor ESP de Evidência Coletada

label.items_equipment=Itens e Equipamentos
checkbox.items_esp=ESP de Itens
tooltip.items_esp=Exibir ESP para itens e equipamentos no chão
color.items_esp_color=Cor ESP de Itens

label.interactive_objects=Objetos Interativos
checkbox.doors_esp=ESP de Portas
tooltip.doors_esp=Exibir ESP para portas e pontos de entrada
color.doors_esp_color=Cor ESP de Portas
checkbox.traps_esp=ESP de Armadilhas
tooltip.traps_esp=Exibir ESP para armadilhas e dispositivos explosivos
color.traps_esp_color=Cor ESP de Armadilhas
checkbox.securables_esp=ESP de Seguráveis
tooltip.securables_esp=Exibir ESP para objetivos que precisam ser protegidos
color.securables_esp_color=Cor ESP de Seguráveis

label.object_distance_settings=Configurações de Distância de Objetos
slider.object_esp_distance=Distância Máxima ESP de Objetos
tooltip.object_esp_distance=Distância máxima para mostrar ESP de objetos (em metros)

# Configurações ESP de Depuração
header.debug_esp=Opções ESP de Depuração
checkbox.debug_class_names=Mostrar Nomes de Classe
tooltip.debug_class_names=Exibir os nomes de classe reais de todos os objetos para depuração
checkbox.debug_distance=Mostrar Distância de Depuração
tooltip.debug_distance=Exibir distância na exibição de nomes de classe de depuração
slider.debug_max_distance=Distância Máxima de Depuração
tooltip.debug_max_distance=Distância máxima para mostrar nomes de classe de depuração (em metros)
warning.debug_performance=AVISO: O modo de depuração pode causar impacto na performance!
text.debug_usage_help=Use o modo de depuração para identificar nomes de classe de objetos para desenvolvimento e configuração ESP.

)";

    // Player Mods Tab Content
    static const char* PT_PLAYER_MODS_CONTENT = R"(
# Aba Mods do Jogador
header.player_settings=Configurações do Jogador
checkbox.no_flash_concussion=Sem Flash / Concussão
tooltip.no_flash_concussion=Desativar todos os efeitos de granadas de luz e concussão
checkbox.godmode=Modo Deus
tooltip.godmode=Saúde infinita - curar automaticamente todos os membros e reviver quando incapacitado
checkbox.no_inventory_weight=Sem Peso de Inventário
tooltip.no_inventory_weight=Remover todas as restrições de peso no seu inventário de jogador
checkbox.unlock_all_items=Desbloquear Todos os Itens
tooltip.unlock_all_items=Desbloquear automaticamente todos os itens de armas e personalização de personagem

# Configurações de Movimento
header.movement_settings=Configurações de Movimento
checkbox.no_player_stagger=Sem Vacilação do Jogador
tooltip.no_player_stagger=Armas e tiros não farão mais seu jogador vacilar
checkbox.infinite_stamina=Stamina Infinita
tooltip.infinite_stamina=Remover as limitações de qualquer perda de stamina. Corrida infinita
checkbox.noclip=NoClip
tooltip.noclip=Voar pelo mapa. Tenha cuidado em modos multijogador
checkbox.speed_hack=Hack de Velocidade
tooltip.speed_hack=Mover-se pelo mapa super rápido - útil para posicionamento tático
slider.speed_multiplier=Multiplicador de Velocidade
tooltip.speed_multiplier=Multiplicador para velocidade de movimento
esp.general.custom_fov=FOV Personalizado
tooltip.esp.custom_fov=Habilitar ajuste de campo de visão personalizado para melhor visibilidade
esp.general.custom_fov_value=Valor FOV
tooltip.esp.custom_fov_value=Definir o ângulo do campo de visão (60-130 graus)
checkbox.teleport_to_target=Teletransporte para Alvo
tooltip.teleport_to_target=Habilitar tecla para teletransportar para seu alvo mirado

# Alterador de Nome
header.name_changer=Alterador de Nome
text.name_changer=Alterador de Nome
input.player_name_hint=Digite novo nome do jogador...
tooltip.player_name_input=Digite o nome para o qual você quer mudar
button.set_name=Definir Nome
tooltip.set_name_button=Clique para mudar seu nome de jogador

# Notificações
notification.teleport_attempt=Tentando teletransporte...
notification.name_changed=Nome alterado para
notification.name_change_failed=Falha ao alterar nome do jogador
notification.empty_name=Por favor digite um nome antes de alterar
)";

    // Weapon Mods Tab Content
    static const char* PT_WEAPON_MODS_CONTENT = R"(
# Aba Mods de Armas
header.aimbot_settings=Configurações do Aimbot
checkbox.enable_aimbot=Habilitar Aimbot
tooltip.enable_aimbot=Habilitar travamento no osso do jogador selecionado com suas armas
checkbox.visibility_check=Verificação de Visibilidade
tooltip.visibility_check=Fazer o aimbot só funcionar quando o jogador estiver completamente visível para você
checkbox.show_fov_circle=Mostrar Círculo FOV
tooltip.show_fov_circle=Exibir o círculo FOV - O aimbot só será acionado se os jogadores estiverem dentro do círculo
checkbox.magic_bullet=Aimbot Silencioso
tooltip.magic_bullet=Faz balas acertarem o alvo sem mover visivelmente sua mira - mais indetectável
combo.target_bone=Osso Alvo
tooltip.target_bone=Selecionar qual osso o aimbot deve mirar
slider.aimbot_smoothing=Suavização do Aimbot
tooltip.aimbot_smoothing=Modificar o fator de suavização do aimbot. Valores menores = mais rápido, aimbot agressivo. Maior = mais legítimo.
slider.fov_radius=Raio FOV
tooltip.fov_radius=Modificar o raio do círculo no qual o aimbot travará nos jogadores
slider.fov_opacity=Opacidade FOV
tooltip.fov_opacity=Personalizar a opacidade do círculo FOV

# Configurações de Armas
header.weapon_settings=Configurações de Armas
checkbox.no_recoil_spread=Sem Recuo / Dispersão
tooltip.no_recoil_spread=Remover recuo de tiro de suas armas e tornar balas super precisas
checkbox.infinite_ammo=Munição Infinita
tooltip.infinite_ammo=Modificar e definir qualquer quantidade de munição. Munição infinita
checkbox.instant_reload=Recarga Instantânea
tooltip.instant_reload=Recarregar armas instantaneamente sem atrasos de animação
slider.ammo_amount=Quantidade de Munição
tooltip.ammo_amount=Definir a quantidade de munição
)";

    // Settings & Hotkeys Tab Content
    static const char* PT_SETTINGS_HOTKEYS_CONTENT = R"(
# Aba Configurações e Teclas
header.ui_settings=Configurações da UI
text.select_theme=Selecionar Tema
button.edit_custom_theme=Editar Tema Personalizado
tooltip.edit_custom_theme_disabled=Selecione 'Tema Personalizado' para começar a editar.
popup.custom_theme_editor=Editor de Tema Personalizado
text.widgets=Widgets
button.save=Salvar
button.close_without_saving=Fechar Sem Salvar
text.undo_changes=Desfazer Alterações.

# Configurações de Teclas
header.hotkey_settings=Configurações de Teclas
text.aimkey=Tecla de Mira: %s
button.set_aimkey=Definir Tecla de Mira
text.press_key_cancel=Pressione uma tecla... (ESC para cancelar)
text.press_key_unbind=Pressione uma tecla... (ESC para desvincular)
tooltip.aimkey=Tecla para segurar para ativação do aimbot
text.speed_key=Tecla de Velocidade: %s
button.set_speed_key=Definir Tecla de Velocidade
text.noclip_key=Tecla NoClip: %s
button.set_noclip_key=Definir Tecla NoClip
text.teleport_key=Tecla de Teletransporte: %s
button.set_teleport_key=Definir Tecla de Teletransporte
text.unified_teleport_key=Tecla de Teletransporte Unificado: %s
button.set_unified_teleport_key=Definir Tecla de Teletransporte Unificado
tooltip.unified_teleport=Teletransportar para seu alvo de mira atual, ou para frente se não houver alvo

# Cabeçalhos e UI de Configurações de Teletransporte
header.teleport_settings=Configurações de Teletransporte
checkbox.unified_teleport=Habilitar Teletransporte
checkbox.smaller_tp_targeting=Mira TP Menor
slider.tp_fov_radius=Raio FOV TP
tooltip.smaller_tp_targeting=Só teletransportar para alvos dentro de um raio FOV menor para precisão
tooltip.tp_fov_radius=O raio FOV para mira de teletransporte menor
slider.actor_teleport_offset=Deslocamento de Teletransporte do Ator
tooltip.actor_teleport_offset=Distância para deslocar do ator alvo para evitar entrar dentro
slider.tp_no_target_distance=Distância de Teletransporte para Frente
tooltip.tp_no_target_distance=Distância para teletransportar para frente quando nenhum alvo está selecionado

# Configurações de Mods de Suspeitos
header.suspect_mods=Mods de Suspeitos
checkbox.no_suspect_firefight=Sem Tiroteio de Suspeitos
tooltip.no_suspect_firefight=Impede suspeitos e civis de se envolver em combate reiniciando seu estado de combate
checkbox.disarm_all_suspects=Desarmar Todos os Suspeitos
tooltip.disarm_all_suspects=Impede suspeitos e civis de sacar, levantar ou usar armas
checkbox.force_suspect_surrender=Forçar Rendição de Suspeitos
tooltip.force_suspect_surrender=Força todos os suspeitos a se renderem imediatamente e obedecer comandos
checkbox.auto_comply_suspects=Auto-Obediência de Suspeitos
tooltip.auto_comply_suspects=Faz suspeitos obedecerem automaticamente a todos os comandos com máxima responsividade

# Configurações de Mods de Armadilhas
header.trap_mods=Mods de Armadilhas
checkbox.disable_all_traps=Desativar Todas as Armadilhas
tooltip.disable_all_traps=Desativa todas as armadilhas de porta e fios-armadilha para impedir que sejam acionadas

# Seleção de Idioma
combo.language=Idioma
tooltip.language=Selecione seu idioma preferido
note.translation_feedback=Encontrou um erro de tradução? Nos avise no Discord!

# Notificações
notification.first_use=Obrigado por usar nosso RONFentry, Ready or Not Cheat. Para começar, abra o menu com a tecla 'INSERT'.

# Nomes das Teclas
key.no_key_set=Nenhuma tecla definida
key.left_mouse=Botão Esquerdo do Mouse
key.right_mouse=Botão Direito do Mouse
key.middle_mouse=Botão do Meio do Mouse
key.side_mouse_1=Botão Lateral do Mouse 1
key.side_mouse_2=Botão Lateral do Mouse 2
key.unknown_key=Tecla Desconhecida

# Teclas de Função
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

# Teclas Especiais
key.caps_lock=Caps Lock
key.scroll_lock=Scroll Lock
key.num_lock=Num Lock
key.tab=Tab
key.space=Espaço
key.enter=Enter
key.escape=Escape
key.backspace=Backspace
key.insert=Insert
key.delete=Delete
key.home=Home
key.end=End
key.page_up=Page Up
key.page_down=Page Down

# Teclas de Seta
key.up_arrow=Seta Cima
key.down_arrow=Seta Baixo
key.left_arrow=Seta Esquerda
key.right_arrow=Seta Direita

# Teclas Modificadoras
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Shift Esquerdo
key.right_shift=Shift Direito
key.left_ctrl=Ctrl Esquerdo
key.right_ctrl=Ctrl Direito
key.left_alt=Alt Esquerdo
key.right_alt=Alt Direito

# Teclas do Teclado Numérico
key.numpad_0=Teclado Numérico 0
key.numpad_1=Teclado Numérico 1
key.numpad_2=Teclado Numérico 2
key.numpad_3=Teclado Numérico 3
key.numpad_4=Teclado Numérico 4
key.numpad_5=Teclado Numérico 5
key.numpad_6=Teclado Numérico 6
key.numpad_7=Teclado Numérico 7
key.numpad_8=Teclado Numérico 8
key.numpad_9=Teclado Numérico 9
key.numpad_multiply=Teclado Numérico *
key.numpad_add=Teclado Numérico +
key.numpad_subtract=Teclado Numérico -
key.numpad_decimal=Teclado Numérico .
key.numpad_divide=Teclado Numérico /
key.numpad_enter=Enter do Teclado Numérico
)";

    // Gamemode Mods Tab Content
    static const char* PT_GAMEMODE_MODS_CONTENT = R"(
# Aba Mods de Modo de Jogo
tab.gamemode_mods=Mods de Modo de Jogo

# Recursos do Modo de Jogo
header.gamemode_features=Recursos do Modo de Jogo
header.gamemode_info=Informações do Modo de Jogo

# Incapacitar Todos
text.incapacitate_all_key=Tecla Incapacitar Todos: %s
button.set_incapacitate_key=Definir Tecla Incapacitar Todos
tooltip.incapacitate_all=Incapacitar instantaneamente todos os suspeitos e civis no mapa

# Vitória Instantânea
text.instant_win_key=Tecla Vitória Instantânea: %s
button.set_instant_win_key=Definir Tecla Vitória Instantânea
tooltip.instant_win=Completar instantaneamente a missão com sucesso

# Derrota Instantânea
text.instant_lose_key=Tecla Derrota Instantânea: %s
button.set_instant_lose_key=Definir Tecla Derrota Instantânea
tooltip.instant_lose=Falhar instantaneamente a missão

# Prender Todos
text.arrest_all_key=Tecla Prender Todos: %s
button.set_arrest_all_key=Definir Tecla Prender Todos
tooltip.arrest_all=Prender instantaneamente todos os suspeitos e civis no mapa

# Reportar Todos
text.report_all_key=Tecla Reportar Todos: %s
button.set_report_all_key=Definir Tecla Reportar Todos
tooltip.report_all=Reportar instantaneamente todos os suspeitos e civis no mapa

# Coletar Todas as Evidências
text.collect_all_evidence_key=Tecla Coletar Todas as Evidências: %s
button.set_collect_all_evidence_key=Definir Tecla Coletar Todas as Evidências
tooltip.collect_all_evidence=Coletar instantaneamente todos os itens de evidência no mapa

# Texto Informativo
info.gamemode_features=Esses recursos permitem manipular o estado do jogo e o resultado da missão. Use com cuidado, pois afetarão sua pontuação da missão.
info.incapacitate_desc=Incapacitar Todos: Incapacita instantaneamente todos os suspeitos hostis e civis, tornando-os incapazes de se mover ou lutar.
info.instant_win_desc=Vitória Instantânea: Termina imediatamente a missão com uma conclusão bem-sucedida. Isso afetará suas estatísticas da missão.
info.instant_lose_desc=Derrota Instantânea: Falha imediatamente a missão atual. Use isso se quiser reiniciar rapidamente ou sair de uma missão.
info.arrest_all_desc=Prender Todos: Prende automaticamente todos os suspeitos e civis no mapa, potencialmente contribuindo para os objetivos da missão.
info.report_all_desc=Reportar Todos: Reporta automaticamente todos os suspeitos e civis no mapa para o TOC (Centro de Operações Táticas).
)";

    // Combine all sections into the final content
    static const char* PORTUGUESE_CONTENT = []() {
        static std::string combined = std::string(PT_VISUAL_SETTINGS_CONTENT) + 
                                     std::string(PT_PLAYER_MODS_CONTENT) + 
                                     std::string(PT_WEAPON_MODS_CONTENT) + 
                                     std::string(PT_GAMEMODE_MODS_CONTENT) + 
                                     std::string(PT_SETTINGS_HOTKEYS_CONTENT);
        return combined.c_str();
    }();
}
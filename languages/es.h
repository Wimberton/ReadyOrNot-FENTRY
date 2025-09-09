#pragma once

// Embedded Spanish translations for Ready or Not Cheat
// Edit this file to update Spanish translations, then rebuild the DLL

namespace EmbeddedTranslations {
    // Visual Settings Tab Content
    static const char* ES_VISUAL_SETTINGS_CONTENT = R"(# Archivo de Idioma Español para Ready or Not Cheat
# Formato: clave=valor

# Aplicación Principal
window.main_title=RONFentry - Ready or Not Cheat

# Nombres de Pestañas
tab.visuals=Visuales
tab.player_mods=Mods de Jugador
tab.weapon_mods=Mods de Armas
tab.world_mods=Mods de Mundo
tab.settings_hotkeys=Configuración y Teclas

# Configuración Visual General
header.general_visual=Configuración Visual General
checkbox.watermark=Marca de Agua
tooltip.watermark=Alternar la visualización de la marca de agua personalizada en pantalla
slider.esp_thickness=Grosor del ESP
tooltip.esp_thickness=Modificar el grosor de línea de todos los elementos ESP
combo.esp_box_style=Estilo de Caja ESP
tooltip.esp_box_style=Cambiar entre varios diseños de Caja ESP
esp.general.unlit_mode=Modo Sin Iluminación
tooltip.esp.unlit_mode=Habilitar modo de renderizado sin iluminación para ver a través de paredes y efectos de luz

# Configuración ESP General (afecta a todos los tipos de personajes)
checkbox.esp_boxes=Cajas ESP
tooltip.esp_boxes=Alternar la visualización de cajas ESP para todos los tipos de personajes
checkbox.esp_names_distance=Nombres/Distancia
tooltip.esp_names_distance=Mostrar nombres de personajes y su distancia desde tu posición
checkbox.esp_health=Barras de Salud
tooltip.esp_health=Mostrar barras de salud de personajes - conocer sus cantidades de salud actuales
checkbox.esp_lines=Líneas de Seguimiento
tooltip.esp_lines=Mostrar líneas de seguimiento de personajes - útil para localizar posiciones de personajes
checkbox.esp_lines_top=Líneas de Seguimiento Desde Arriba
tooltip.esp_lines_top=Mostrar líneas de seguimiento de personajes desde la parte superior de la pantalla, no desde abajo

# Opciones Visuales del Jugador
header.player_visual=Opciones Visuales del Jugador
checkbox.player_esp=ESP del Jugador
tooltip.player_esp=Alternar la visualización de cualquier característica ESP del jugador habilitada
checkbox.player_boxes=Cajas del Jugador
tooltip.player_boxes=Alternar la visualización de cajas ESP del jugador
checkbox.player_skeleton=Esqueleto del Jugador
tooltip.player_skeleton=Mostrar esqueletos del jugador - ver su dirección de agacharse/prono/orientación
checkbox.player_names_distance=Nombres/Distancia del Jugador
tooltip.player_names_distance=Mostrar nombres de jugadores y su distancia desde tu posición
checkbox.player_health=Salud del Jugador
tooltip.player_health=Mostrar salud del jugador - conocer sus cantidades de salud actuales
checkbox.player_lines=Líneas del Jugador
tooltip.player_lines=Mostrar líneas de seguimiento del jugador - útil para localizar posiciones de jugadores
checkbox.player_lines_top=Líneas del Jugador Desde Arriba
tooltip.player_lines_top=Mostrar líneas de seguimiento del jugador desde la parte superior de la pantalla, no desde abajo
slider.player_esp_distance=Distancia ESP del Jugador
tooltip.player_esp_distance=Distancia máxima para mostrar ESP del jugador (en metros)
color.visible_esp_color=Color ESP Visible
color.hidden_esp_color=Color ESP Oculto
color.aim_target_esp_color=Color ESP Objetivo de Puntería

# Configuración ESP de Personajes IA
header.ai_visual=Opciones Visuales de Personajes IA
label.sert_teams=Equipos SERT
checkbox.sert_red_esp=ESP SERT Rojo
tooltip.sert_red_esp=Mostrar ESP para miembros del equipo SERT Rojo
checkbox.sert_red_boxes=Cajas SERT Rojo
checkbox.sert_red_names=Nombres SERT Rojo
checkbox.sert_red_health=Salud SERT Rojo
checkbox.sert_red_lines=Líneas SERT Rojo
color.sert_red_esp_color=Color ESP SERT Rojo

checkbox.sert_blue_esp=ESP SERT Azul
tooltip.sert_blue_esp=Mostrar ESP para miembros del equipo SERT Azul
checkbox.sert_blue_boxes=Cajas SERT Azul
checkbox.sert_blue_names=Nombres SERT Azul
checkbox.sert_blue_health=Salud SERT Azul
checkbox.sert_blue_lines=Líneas SERT Azul
color.sert_blue_esp_color=Color ESP SERT Azul

checkbox.suspect_esp=ESP de Sospechosos
tooltip.suspect_esp=Mostrar ESP para personajes sospechosos
checkbox.suspect_boxes=Cajas de Sospechosos
checkbox.suspect_names=Nombres de Sospechosos
checkbox.suspect_health=Salud de Sospechosos
checkbox.suspect_lines=Líneas de Sospechosos
color.suspect_esp_color=Color ESP de Sospechosos

checkbox.civilian_esp=ESP de Civiles
tooltip.civilian_esp=Mostrar ESP para personajes civiles
checkbox.civilian_boxes=Cajas de Civiles
checkbox.civilian_names=Nombres de Civiles
checkbox.civilian_health=Salud de Civiles
checkbox.civilian_lines=Líneas de Civiles
color.civilian_esp_color=Color ESP de Civiles

checkbox.squad_esp=ESP del Escuadrón
tooltip.squad_esp=Mostrar ESP para miembros de tu escuadrón
checkbox.squad_boxes=Cajas del Escuadrón
checkbox.squad_names=Nombres del Escuadrón
checkbox.squad_health=Salud del Escuadrón
checkbox.squad_lines=Líneas del Escuadrón
color.squad_esp_color=Color ESP del Escuadrón

checkbox.wounded_esp=ESP de Heridos
tooltip.wounded_esp=Mostrar ESP para personajes heridos/incapacitados
checkbox.wounded_boxes=Cajas de Heridos
checkbox.wounded_names=Nombres de Heridos
checkbox.wounded_health=Salud de Heridos
checkbox.wounded_lines=Líneas de Heridos
color.wounded_esp_color=Color ESP de Heridos

label.ai_distance_settings=Configuración de Distancia IA
slider.ai_esp_distance=Distancia ESP IA
tooltip.ai_esp_distance=Distancia máxima para mostrar ESP de personajes IA (en metros)

# Configuración ESP de Objetos e Interactivos
header.object_visual=ESP de Objetos e Interactivos
label.evidence_investigation=Evidencia e Investigación
checkbox.evidence_esp=ESP de Evidencia
tooltip.evidence_esp=Mostrar ESP para elementos de evidencia que se pueden recoger
color.evidence_esp_color=Color ESP de Evidencia
checkbox.collected_evidence_esp=ESP de Evidencia Recolectada
tooltip.collected_evidence_esp=Mostrar ESP para evidencia que ya ha sido recolectada
color.collected_evidence_esp_color=Color ESP de Evidencia Recolectada

label.items_equipment=Objetos y Equipamiento
checkbox.items_esp=ESP de Objetos
tooltip.items_esp=Mostrar ESP para objetos y equipamiento en el suelo
color.items_esp_color=Color ESP de Objetos

label.interactive_objects=Objetos Interactivos
checkbox.doors_esp=ESP de Puertas
tooltip.doors_esp=Mostrar ESP para puertas y puntos de entrada
color.doors_esp_color=Color ESP de Puertas
checkbox.traps_esp=ESP de Trampas
tooltip.traps_esp=Mostrar ESP para trampas y dispositivos explosivos
color.traps_esp_color=Color ESP de Trampas
checkbox.securables_esp=ESP de Asegurables
tooltip.securables_esp=Mostrar ESP para objetivos que necesitan ser asegurados
color.securables_esp_color=Color ESP de Asegurables

label.object_distance_settings=Configuración de Distancia de Objetos
slider.object_esp_distance=Distancia Máxima ESP de Objetos
tooltip.object_esp_distance=Distancia máxima para mostrar ESP de objetos (en metros)

# Configuración ESP de Depuración
header.debug_esp=Opciones ESP de Depuración
checkbox.debug_class_names=Mostrar Nombres de Clase
tooltip.debug_class_names=Mostrar los nombres de clase reales de todos los objetos para depuración
checkbox.debug_distance=Mostrar Distancia de Depuración
tooltip.debug_distance=Mostrar distancia en la visualización de nombres de clase de depuración
slider.debug_max_distance=Distancia Máxima de Depuración
tooltip.debug_max_distance=Distancia máxima para mostrar nombres de clase de depuración (en metros)
warning.debug_performance=¡ADVERTENCIA: El modo de depuración puede causar impacto en el rendimiento!
text.debug_usage_help=Usar modo de depuración para identificar nombres de clase de objetos para desarrollo y configuración ESP.

)";

    // Player Mods Tab Content
    static const char* ES_PLAYER_MODS_CONTENT = R"(
# Pestaña Mods de Jugador
header.player_settings=Configuración del Jugador
checkbox.no_flash_concussion=Sin Flash / Conmoción
tooltip.no_flash_concussion=Desactivar todos los efectos de granadas cegadoras y conmoción
checkbox.godmode=Modo Dios
tooltip.godmode=Salud infinita - sanar automáticamente todas las extremidades y revivir cuando esté incapacitado
checkbox.no_inventory_weight=Sin Peso de Inventario
tooltip.no_inventory_weight=Eliminar todas las restricciones de peso en tu inventario de jugador
checkbox.unlock_all_items=Desbloquear Todos los Objetos
tooltip.unlock_all_items=Desbloquear automáticamente todos los objetos de armas y personalización de personajes

# Configuración de Movimiento
header.movement_settings=Configuración de Movimiento
checkbox.no_player_stagger=Sin Tambaleo del Jugador
tooltip.no_player_stagger=Las armas y disparos ya no harán tambalear a tu jugador
checkbox.infinite_stamina=Resistencia Infinita
tooltip.infinite_stamina=Eliminar las limitaciones de cualquier pérdida de resistencia. Sprint infinito
checkbox.noclip=NoClip
tooltip.noclip=Volar por el mapa. Ten cuidado en modos multijugador
checkbox.speed_hack=Hack de Velocidad
tooltip.speed_hack=Moverse por el mapa súper rápido - útil para posicionamiento táctico
slider.speed_multiplier=Multiplicador de Velocidad
tooltip.speed_multiplier=Multiplicador para la velocidad de movimiento
esp.general.custom_fov=FOV Personalizado
tooltip.esp.custom_fov=Habilitar ajuste de campo de visión personalizado para mejor visibilidad
esp.general.custom_fov_value=Valor FOV
tooltip.esp.custom_fov_value=Establecer el ángulo del campo de visión (60-130 grados)
checkbox.teleport_to_target=Teletransporte al Objetivo
tooltip.teleport_to_target=Habilitar tecla para teletransportarse al objetivo apuntado

# Cambiador de Nombre
header.name_changer=Cambiador de Nombre
text.name_changer=Cambiador de Nombre
input.player_name_hint=Ingresa nuevo nombre de jugador...
tooltip.player_name_input=Ingresa el nombre al que quieres cambiar
button.set_name=Establecer Nombre
tooltip.set_name_button=Haz clic para cambiar tu nombre de jugador

# Notificaciones
notification.teleport_attempt=Intentando teletransporte...
notification.name_changed=Nombre cambiado a
notification.name_change_failed=Error al cambiar nombre de jugador
notification.empty_name=Por favor ingresa un nombre antes de cambiar
)";

    // Weapon Mods Tab Content
    static const char* ES_WEAPON_MODS_CONTENT = R"(
# Pestaña Mods de Armas
header.aimbot_settings=Configuración de Aimbot
checkbox.enable_aimbot=Habilitar Aimbot
tooltip.enable_aimbot=Habilitar el bloqueo en el hueso de jugador seleccionado con tus armas
checkbox.visibility_check=Verificación de Visibilidad
tooltip.visibility_check=Hacer que el aimbot solo se habilite cuando el jugador sea completamente visible para ti
checkbox.show_fov_circle=Mostrar Círculo FOV
tooltip.show_fov_circle=Mostrar el círculo FOV - El aimbot solo se activará si los jugadores están dentro del círculo
checkbox.magic_bullet=Aimbot Silencioso
tooltip.magic_bullet=Hace que las balas golpeen el objetivo sin mover visiblemente tu puntería - más indetectable
combo.target_bone=Hueso Objetivo
tooltip.target_bone=Seleccionar qué hueso debe apuntar el aimbot
slider.aimbot_smoothing=Suavizado de Aimbot
tooltip.aimbot_smoothing=Modificar el factor de suavizado del aimbot. Valores bajos = más rápido, aimbot agresivo. Más alto = más legítimo.
slider.fov_radius=Radio FOV
tooltip.fov_radius=Modificar el radio del círculo en el que el aimbot se bloqueará a los jugadores
slider.fov_opacity=Opacidad FOV
tooltip.fov_opacity=Personalizar la opacidad del círculo FOV

# Configuración de Armas
header.weapon_settings=Configuración de Armas
checkbox.no_recoil_spread=Sin Retroceso / Dispersión
tooltip.no_recoil_spread=Eliminar el retroceso de disparo de tus armas y hacer las balas súper precisas
checkbox.infinite_ammo=Munición Infinita
tooltip.infinite_ammo=Modificar y establecer cualquier cantidad de munición. Munición infinita
checkbox.instant_reload=Recarga Instantánea
tooltip.instant_reload=Recargar armas instantáneamente sin retrasos de animación
slider.ammo_amount=Cantidad de Munición
tooltip.ammo_amount=Establecer la cantidad de munición
)";

    // Settings & Hotkeys Tab Content
    static const char* ES_SETTINGS_HOTKEYS_CONTENT = R"(
# Pestaña Configuración y Teclas
header.ui_settings=Configuración de UI
text.select_theme=Seleccionar Tema
button.edit_custom_theme=Editar Tema Personalizado
tooltip.edit_custom_theme_disabled=Selecciona 'Tema Personalizado' para comenzar a editar.
popup.custom_theme_editor=Editor de Tema Personalizado
text.widgets=Widgets
button.save=Guardar
button.close_without_saving=Cerrar Sin Guardar
text.undo_changes=Deshacer Cambios.

# Configuración de Teclas
header.hotkey_settings=Configuración de Teclas
text.aimkey=Tecla de Puntería: %s
button.set_aimkey=Establecer Tecla de Puntería
text.press_key_cancel=Presiona una tecla... (ESC para cancelar)
text.press_key_unbind=Presiona una tecla... (ESC para desvincular)
tooltip.aimkey=Tecla para mantener presionada para activación del aimbot
text.speed_key=Tecla de Velocidad: %s
button.set_speed_key=Establecer Tecla de Velocidad
text.noclip_key=Tecla NoClip: %s
button.set_noclip_key=Establecer Tecla NoClip
text.teleport_key=Tecla de Teletransporte: %s
button.set_teleport_key=Establecer Tecla de Teletransporte
text.unified_teleport_key=Tecla de Teletransporte Unificado: %s
button.set_unified_teleport_key=Establecer Tecla de Teletransporte Unificado
tooltip.unified_teleport=Teletransportarse a tu objetivo actual de puntería, o hacia adelante si no hay objetivo

# Encabezados y UI de Configuración de Teletransporte
header.teleport_settings=Configuración de Teletransporte
checkbox.unified_teleport=Habilitar Teletransporte
checkbox.smaller_tp_targeting=Apuntado TP Más Pequeño
slider.tp_fov_radius=Radio FOV TP
tooltip.smaller_tp_targeting=Solo teletransportarse a objetivos dentro de un radio FOV más pequeño para precisión
tooltip.tp_fov_radius=El radio FOV para apuntado de teletransporte más pequeño
slider.actor_teleport_offset=Desplazamiento de Teletransporte de Actor
tooltip.actor_teleport_offset=Distancia para desplazarse del actor objetivo para evitar entrar dentro
slider.tp_no_target_distance=Distancia de Teletransporte Hacia Adelante
tooltip.tp_no_target_distance=Distancia para teletransportarse hacia adelante cuando no hay objetivo seleccionado

# Configuración de Mods de Sospechosos
header.suspect_mods=Mods de Sospechosos
checkbox.no_suspect_firefight=Sin Tiroteo de Sospechosos
tooltip.no_suspect_firefight=Previene que sospechosos y civiles se involucren en combate reiniciando su estado de combate
checkbox.disarm_all_suspects=Desarmar Todos los Sospechosos
tooltip.disarm_all_suspects=Previene que sospechosos y civiles saquen, levanten o usen armas
checkbox.force_suspect_surrender=Forzar Rendición de Sospechosos
tooltip.force_suspect_surrender=Fuerza a todos los sospechosos a rendirse inmediatamente y cumplir con las órdenes
checkbox.auto_comply_suspects=Auto-Cumplimiento de Sospechosos
tooltip.auto_comply_suspects=Hace que los sospechosos cumplan automáticamente con todas las órdenes con máxima respuesta

# Configuración de Mods de Trampas
header.trap_mods=Mods de Trampas
checkbox.disable_all_traps=Desactivar Todas las Trampas
tooltip.disable_all_traps=Desactiva todas las trampas de puertas y cables trampa para prevenir que se activen

# Selección de Idioma
combo.language=Idioma
tooltip.language=Selecciona tu idioma preferido
note.translation_feedback=¿Encontraste un error de traducción? ¡Déjanos saber en Discord!

# Notificaciones
notification.first_use=Gracias por usar nuestro RONFentry, Ready or Not Cheat. Para comenzar, abre el menú con la tecla 'INSERT'.

# Nombres de Teclas
key.no_key_set=Sin tecla establecida
key.left_mouse=Botón Izquierdo del Ratón
key.right_mouse=Botón Derecho del Ratón
key.middle_mouse=Botón Central del Ratón
key.side_mouse_1=Botón Lateral del Ratón 1
key.side_mouse_2=Botón Lateral del Ratón 2
key.unknown_key=Tecla Desconocida

# Teclas de Función
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

# Teclas Especiales
key.caps_lock=Bloqueo de Mayúsculas
key.scroll_lock=Bloqueo de Desplazamiento
key.num_lock=Bloqueo Numérico
key.tab=Tab
key.space=Espacio
key.enter=Enter
key.escape=Escape
key.backspace=Retroceso
key.insert=Insert
key.delete=Suprimir
key.home=Inicio
key.end=Fin
key.page_up=Re Pág
key.page_down=Av Pág

# Teclas de Flechas
key.up_arrow=Flecha Arriba
key.down_arrow=Flecha Abajo
key.left_arrow=Flecha Izquierda
key.right_arrow=Flecha Derecha

# Teclas Modificadoras
key.shift=Shift
key.ctrl=Ctrl
key.alt=Alt
key.left_shift=Shift Izquierdo
key.right_shift=Shift Derecho
key.left_ctrl=Ctrl Izquierdo
key.right_ctrl=Ctrl Derecho
key.left_alt=Alt Izquierdo
key.right_alt=Alt Derecho

# Teclas del Teclado Numérico
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
key.numpad_enter=Enter del Teclado Numérico
)";

    // Gamemode Mods Tab Content
    static const char* ES_GAMEMODE_MODS_CONTENT = R"(
# Pestaña Mods de Modo de Juego
tab.gamemode_mods=Mods de Modo de Juego

# Características del Modo de Juego
header.gamemode_features=Características del Modo de Juego
header.gamemode_info=Información del Modo de Juego

# Incapacitar Todos
text.incapacitate_all_key=Tecla Incapacitar Todos: %s
button.set_incapacitate_key=Establecer Tecla Incapacitar Todos
tooltip.incapacitate_all=Incapacitar instantáneamente a todos los sospechosos y civiles en el mapa

# Victoria Instantánea
text.instant_win_key=Tecla Victoria Instantánea: %s
button.set_instant_win_key=Establecer Tecla Victoria Instantánea
tooltip.instant_win=Completar instantáneamente la misión con éxito

# Derrota Instantánea
text.instant_lose_key=Tecla Derrota Instantánea: %s
button.set_instant_lose_key=Establecer Tecla Derrota Instantánea
tooltip.instant_lose=Fallar instantáneamente la misión

# Arrestar Todos
text.arrest_all_key=Tecla Arrestar Todos: %s
button.set_arrest_all_key=Establecer Tecla Arrestar Todos
tooltip.arrest_all=Arrestar instantáneamente a todos los sospechosos y civiles en el mapa

# Reportar Todos
text.report_all_key=Tecla Reportar Todos: %s
button.set_report_all_key=Establecer Tecla Reportar Todos
tooltip.report_all=Reportar instantáneamente a todos los sospechosos y civiles en el mapa

# Recolectar Toda la Evidencia
text.collect_all_evidence_key=Tecla Recolectar Toda la Evidencia: %s
button.set_collect_all_evidence_key=Establecer Tecla Recolectar Toda la Evidencia
tooltip.collect_all_evidence=Recolectar instantáneamente todos los elementos de evidencia en el mapa

# Texto Informativo
info.gamemode_features=Estas características te permiten manipular el estado del juego y el resultado de la misión. Usa con precaución ya que afectarán tu puntuación de misión.
info.incapacitate_desc=Incapacitar Todos: Incapacita instantáneamente a todos los sospechosos hostiles y civiles, haciéndolos incapaces de moverse o luchar.
info.instant_win_desc=Victoria Instantánea: Termina inmediatamente la misión con una finalización exitosa. Esto afectará tus estadísticas de misión.
info.instant_lose_desc=Derrota Instantánea: Falla inmediatamente la misión actual. Usa esto si quieres reiniciar rápidamente o salir de una misión.
info.arrest_all_desc=Arrestar Todos: Arresta automáticamente a todos los sospechosos y civiles en el mapa, potencialmente contribuyendo a los objetivos de misión.
info.report_all_desc=Reportar Todos: Reporta automáticamente a todos los sospechosos y civiles en el mapa al TOC (Centro de Operaciones Tácticas).
)";

    // Combine all sections into the final content
    static const char* SPANISH_CONTENT = []() {
        static std::string combined = std::string(ES_VISUAL_SETTINGS_CONTENT) + 
                                     std::string(ES_PLAYER_MODS_CONTENT) + 
                                     std::string(ES_WEAPON_MODS_CONTENT) + 
                                     std::string(ES_GAMEMODE_MODS_CONTENT) + 
                                     std::string(ES_SETTINGS_HOTKEYS_CONTENT);
        return combined.c_str();
    }();
}
#define WLR_USE_UNSTABLE

#include <hyprland/src/Compositor.hpp>
#include <hyprland/src/desktop/DesktopTypes.hpp>
#include <hyprland/src/desktop/state/FocusState.hpp>
#include <hyprland/src/desktop/view/Window.hpp>
#include <hyprland/src/event/EventBus.hpp>
#include <hyprland/src/helpers/Monitor.hpp>
#include <hyprland/src/includes.hpp>
#include <hyprland/src/layout/LayoutManager.hpp>
#include <hyprland/src/managers/SeatManager.hpp>
#include <hyprland/src/managers/input/InputManager.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprland/src/protocols/LayerShell.hpp>
#include <hyprland/src/render/Renderer.hpp>

inline HANDLE              PHANDLE = nullptr;
static CHyprSignalListener g_moveListener;

static void onMouseMove(const Vector2D &pos, Event::SCallbackInfo &info) {
    // ignore if hold (fixes, resize dragging)
    if (!g_pInputManager->m_currentlyHeldButtons.empty())
        return;
    if (g_layoutManager->dragController->target())
        return;

    // check windows
    if (g_pCompositor->vectorToWindowUnified(
            pos, Desktop::View::WINDOW_ONLY | Desktop::View::ALLOW_FLOATING |
                     Desktop::View::INPUT_EXTENTS |
                     Desktop::View::FOLLOW_MOUSE_CHECK))
        return;

    // check layer surfaces (ignores, bars overlay ...)
    const auto mon = g_pCompositor->getMonitorFromVector(pos);
    if (mon) {
        Vector2D coords;
        PHLLS    ls;
        for (auto layer :
             {ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY, ZWLR_LAYER_SHELL_V1_LAYER_TOP,
              ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM,
              ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND})
            if (g_pCompositor->vectorToLayerSurface(
                    pos, &mon->m_layerSurfaceLayers[layer], &coords, &ls))
                return;
    }

    // truly empty - cancel and clear focus
    info.cancelled = true;

	// reset cursor
    g_pHyprRenderer->setCursorFromName("left_ptr");

    if (Desktop::focusState()->window())
        Desktop::focusState()->rawWindowFocus(nullptr,
                                              Desktop::FOCUS_REASON_FFM);

    if (g_pSeatManager->m_state.pointerFocus.lock())
        g_pSeatManager->setPointerFocus(nullptr, {});
}

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    // if (__hyprland_api_get_hash() != __hyprland_api_get_client_hash()) {
    //     HyprlandAPI::addNotification(PHANDLE, "[curleave] Version mismatch",
    //                                  CHyprColor{1.0, 0.2, 0.2, 1.0}, 5000);
    //     throw std::runtime_error("[curleave] Version mismatch");
    // }

    g_moveListener = Event::bus()->m_events.input.mouse.move.listen(
        [](const Vector2D &pos, Event::SCallbackInfo &info) {
            onMouseMove(pos, info);
        });

    return {"curleave", "blur on cursor leave window", "hxero", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() { g_moveListener.reset(); }

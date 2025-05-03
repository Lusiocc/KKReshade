#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "screenshot/screenshot.hpp"

static void on_reshade_finish_effects(reshade::api::effect_runtime* runtime, reshade::api::command_list* cmd_list, reshade::api::resource_view rtv, reshade::api::resource_view rtv_srgb)
{
    screenshot::on_reshade_finish_effects(runtime, cmd_list, rtv, rtv_srgb);
}

static void on_init_effect_runtime(reshade::api::effect_runtime* runtime)
{
    screenshot::on_init_effect_runtime(runtime);
}

static void on_destroy_effect_runtime(reshade::api::effect_runtime* runtime)
{
    screenshot::on_destroy_effect_runtime(runtime);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!reshade::register_addon(hModule))
            return FALSE;
        reshade::register_event<reshade::addon_event::init_effect_runtime>(&on_init_effect_runtime);
        reshade::register_event<reshade::addon_event::reshade_finish_effects>(&on_reshade_finish_effects);
        reshade::register_event<reshade::addon_event::destroy_effect_runtime>(&on_destroy_effect_runtime);

        screenshot::start();
        break;
    case DLL_PROCESS_DETACH:
        reshade::unregister_event<reshade::addon_event::init_effect_runtime>(&on_init_effect_runtime);
        reshade::unregister_event<reshade::addon_event::reshade_finish_effects>(&on_reshade_finish_effects);
        reshade::unregister_event<reshade::addon_event::destroy_effect_runtime>(&on_destroy_effect_runtime);
        reshade::unregister_addon(hModule);

        screenshot::stop();
        break;
    }
    return TRUE;
}

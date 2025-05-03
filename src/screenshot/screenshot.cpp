#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "screenshot.hpp"

#define SCREENSHOT_SHM_NAME "KKReshade_Screenshot_SHM"

static uint8_t buffer[MAX_IMAGE_SIZE];

static HANDLE hMapFile = nullptr;

namespace screenshot
{
    static ScreenshotMemory* shm = nullptr;
    
    void on_reshade_finish_effects(reshade::api::effect_runtime* runtime, reshade::api::command_list*, reshade::api::resource_view, reshade::api::resource_view)
    {
		runtime->capture_screenshot(buffer);
		memcpy(shm->imageBytes, buffer, shm->width * shm->height * shm->channels);
    }

    void on_init_effect_runtime(reshade::api::effect_runtime* runtime)
    {
        runtime->get_screenshot_width_and_height(&shm->width, &shm->height);
    }

    void on_destroy_effect_runtime(reshade::api::effect_runtime* runtime)
    {
        shm->width = 0;
        shm->height = 0;
    }

    void start()
    {
        hMapFile = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(ScreenshotMemory) + MAX_IMAGE_SIZE, SCREENSHOT_SHM_NAME);
        if (!hMapFile) return;

        shm = (ScreenshotMemory*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(ScreenshotMemory) + MAX_IMAGE_SIZE);
        if (!shm)
        {
            CloseHandle(hMapFile);
            return;
        }

        shm->channels = COLOR_CHANNELS;
    }

    void stop()
    {
        UnmapViewOfFile(shm);
        CloseHandle(hMapFile);
    }
}
/*
 * This library is released under the MIT License.
 *
 * Copyright (c) 2020 Michael Volk
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice, permission notice and disclaimer
 * shall be included in all copies or substantial portions of the
 * Software.
 */
#include "tft.h"
#include <esp_log.h>


static const char * TFT_TAG = "esp32-tft";


uint16_t tft16_color_rgb565(
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
    return
      ((green & 0x00FC) << 10) |
      (red & 0x00F8) |
      ((blue & 0x00F8) << 5) |
      (green >> 5);
}


esp_err_t tft_set_orientation(
    tft_handle_t tft,
    tft_orientation_t orientation)
{
    if (!tft->set_orientation) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    return tft->set_orientation(&tft->info, orientation);
}


esp_err_t tft16_render(
    tft_handle_t tft,
    uint16_t * buffer,
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1)
{
    if (!tft->render16) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    if (x0 > x1) {
        ESP_LOGE(
            TFT_TAG,
            "tft16_render(...) requires x0 <= x1"
        );
        return ESP_ERR_INVALID_ARG;
    }
    if (x0 > 127 || x1 > 127) {
        ESP_LOGE(
            TFT_TAG,
            "tft16_render(...) requires x0 and x1 < width"
        );
        return ESP_ERR_INVALID_ARG;
    }
    if (y0 > y1) {
        ESP_LOGE(
            TFT_TAG,
            "tft16_render(...) requires y0 <= y1"
        );
        return ESP_ERR_INVALID_ARG;
    }
    if (y0 > 127 || y1 > 127) {
        ESP_LOGE(
            TFT_TAG,
            "tft16_render(...) requires y0 and y1 < height"
        );
        return ESP_ERR_INVALID_ARG;
    }
    return tft->render16(&tft->info, buffer, x0, y0, x1, y1);
}


esp_err_t tft16_draw_point(
    tft_handle_t tft,
    uint16_t color,
    uint8_t x,
    uint8_t y)
{
    if (!tft->draw16_point) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    if (x > 127 || y > 127) {
        ESP_LOGE(
            TFT_TAG,
            "tft16_draw_point(...) requires x < width and y < height"
        );
        return ESP_ERR_INVALID_ARG;
    }
    return tft->draw16_point(&tft->info, color, x, y);
}

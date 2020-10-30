# TFT Prototyping Library for ESP32 & ESP-IDF

This library facilitates quick-start interfacing support
with small TFT LCD screens via SPI on Espressif ESP32
systems using the ESP-IDF development platform.

## For Prototyping

This library does not emphasize performance, memory
efficiency, testing or configurability.

This library is particularly useful for getting up
and running rapidly with widely available TFT
breakout modules using ESP-IDF.

This library is licensed under the permissive MIT
license. You are encouraged to fork it, modify it,
and mould it to fit your needs. It aspires only to
be your starting point.

## Part of an Ecosystem

This library alone is not very useful. It is designed
to work together with other libraries to provide a
a stable API atop potentially shifting hardware choices
during the prototyping phase.

For example, to use the Adafruit 1.44" color TFT LCD,
the
[`esp32-adafruit-144-tft` library](https://github.com/mvolk/esp32-adafruit-144-tft)
(backed by the
[`esp32-st7735r` library](https://github.com/mvolk/esp32-st7735r))
would be used to initialize the `tft_handle_t`. This library's
functions would take it from there, providing support for
creating color values and drawing to the screen.

## For ESP32 Only

This library aims to support only Espressif
[ESP32 modules](https://www.espressif.com/en/products/modules/esp32).

## For ESP-IDF Only

This library is designed to work only with Espressif's
[ESP-IDF v4.1+](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html),
the official freeRTOS-based platform for ESP32 development.

This library is not for Arduino-based development.

## Dependencies

This library does not depend on any other 3rd party libraries.

That said, per the "Part of an Ecosystem" section above, this
library is not very useful without a component(s) providing
support for specific TFT hardware.

## Boundaries

* **Color Depth:** this library presently provides support
  only for 16-bit color depth. Although direct support for
  RGB/565 is included, other 16-bit formats can be used
  provided you construct your own color values.
* **GFX:** this library does not provide features to draw
  geometries, text, images, etc.
* **Peripherals:** this library provides no support for the
  SD card readers commonly included with TFT breakout
  boards.

## Installation

Using the modern ESP-IDF with CMake, Git and the recommended
project structure (with a `components` folder), the easiest
way to install this library is to add it to the `components`
folder as a Git submodule:

```shell
cd ${YOUR_PROJECT_ROOT}/components
git submodule add https://github.com/mvolk/esp32-tft.git
git commit -m "Add esp32-tft component"
```

## API

There's not much to this high-level library. The
heavy lifting has been delegated to hardware-specific
libraries, leaving this "developer interface" quite
simple!

* `tft_set_orientation_(...)` sets the panel orientation
* `tft16_color_rgb565(...)` creates a 16-bit RGB/565 color
  corrected for the ESP32's little endian memory layout
* `tft16_render(...)` renders a 16-bit raster to a specified
  region of the display
* `tft16_draw_point(...)` sets the color of the specified
  pixel
* `tft_t` and `tft_info_t` are initialized by hardware-specific
  libraries and passed to this library's functions
* `tft_handle_t` is a convenient alias for `tft_t *`

See detailed durocumentation in [tft.h](./include/tft.h).

## Technical Notes

* This library adopts the convention that the origin (0, 0) is
  at the bottom left of the screen. Each hardware-specific
  library where specify in its README where the bottom left
  corner of the screen is in relation to physical landmarks
  on the hardware.

## Support

Technical support is not available.

## Contributing

### Bug Reports

Please feel free to report bugs by
[opening a new issue via Github](https://github.com/mvolk/esp32-tft/issues/new).

Please do not use Github issues to request technical support.

### Pull Requests

Pull requests that further the goals of this library are welcome.

The [issues list](https://github.com/mvolk/esp32-tft/issues)
is a good place to look for ideas if you would like to contribute but
don't have a specific contribution in mind.

If you would like to extend support to additional MCUs or
development platforms, please consider forking this library.

## Credits

This library draws inspiration from Adafruit's collection of
Arduino libraries, including
[Adafruit-ST7735-Library](https://github.com/adafruit/Adafruit-ST7735-Library),
[Adafruit-GFX-Library](https://github.com/adafruit/Adafruit-GFX-Library), and
[Adafruit-BusIO](https://github.com/adafruit/Adafruit_BusIO).

Additionally, Espressif's
[ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/index.html)
was invaluable.

## License & Copyright

See [LICENSE.txt](./LICENSE.txt) for license details.

## Liability Notice

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

# GlanceAt OLED

GlanceAt OLED is a **Home Assistant smart display** powered by an **ESP32-S3** and a **256×64 SSD1322 OLED panel**.

It is designed to sit on a desk or shelf and display useful information from Home Assistant such as:

- Weather
- Upcoming calendar events
- Clock and date
- Custom dashboards
- Notifications from Home Assistant automations

The device runs **ESPHome firmware** and integrates directly with Home Assistant using the ESPHome API.

---

# Features

- Native **Home Assistant integration** via ESPHome  
- **256×64 OLED display** driven by SSD1322  
- **Clock + Weather dashboard**  
- **Calendar display**  
- **Custom template support**  
- **Real-time notifications from Home Assistant**  
- **Template switching from Home Assistant UI**  
- **OTA firmware updates**

---

# Hardware

The GlanceAt display uses the following hardware:

- ESP32-S3 DevKitC
- SSD1322 OLED Display (256×64)
- SPI communication interface
- USB-C power

---

# Repository Structure

The repository contains two firmware configurations.

    glanceat-oled.yaml      Full firmware used on devices
    glanceat-base.yaml      Minimal ESPHome configuration for development

    templates/
      template_selector.h
      clock_weather.h
      calendar.h
      custom.h

### Full Firmware

`glanceat-oled.yaml` contains the complete firmware used by the device including:

- template selector
- weather integration
- calendar integration
- notification system
- Home Assistant sensors

### Base Configuration

`glanceat-base.yaml` provides a minimal configuration for developers who want to build their own firmware from scratch.

---

# Quick Start (Users)

Most users do **not need to compile firmware**.

The device ships pre-flashed and can be set up directly in Home Assistant.

1. Power the device  
2. Connect to the WiFi network:

    glanceat-oled Fallback  
    password: glanceat

3. Open the setup portal:

    http://192.168.4.1

4. Enter your WiFi credentials  
5. Add the device in Home Assistant

Full setup guide available at:

https://labs.smarthomeshopuk.com

---

# Home Assistant Requirements

The default firmware expects the following entities in Home Assistant.

### Weather entity

    weather.forecast_home

### Calendar entity

    calendar.glanceatcalendar

These values can be modified in the firmware using the substitutions section.

---

# Notifications

The display supports notifications triggered from Home Assistant using the ESPHome service:

    show_notification

Example service call:

    service: esphome.glanceat_oled_show_notification
    data:
      message: "Dinner is ready"
      duration_ms: 5000

Notifications temporarily override the display template and return to the previous screen once the duration expires.

---

# Development

Developers can modify the firmware using ESPHome.

Install ESPHome:

    pip install esphome

Compile and upload firmware:

    esphome run glanceat-oled.yaml

The first flash must be performed via USB. After this, firmware updates can be installed using **OTA updates**.

---

# Display Templates

The display rendering system is implemented in C++ header files located in the `templates` folder.

    templates/
      clock_weather.h
      calendar.h
      custom.h
      template_selector.h

Each template defines how information from Home Assistant is rendered on the OLED display.

Developers can modify existing templates or create new ones.

---

# Why API Encryption Is Disabled

The firmware intentionally disables API encryption so that the device can be **automatically discovered by Home Assistant** without requiring a pre-shared key.

Advanced users may enable encryption if desired.

---

# Documentation

Full setup guides are available at:

https://labs.smarthomeshopuk.com

---

# License

MIT License

---

# Credits

ESPHome  
https://esphome.io

Home Assistant  
https://www.home-assistant.io


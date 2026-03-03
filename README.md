# GlanceAt OLED Template
GlanceAt OLED provides a clean, always-on dashboard for your desk, wall, or workspace — powered by ESPHome and Home Assistant.

---

The template has a number of built in features that can be setup, however you can customise it via espHome. 

## Template Features
-  Clock with seconds and full date
-  Weather display (configurable weather entity)
-  Upcoming calendar event view
-  Notification overlay (triggered via Home Assistant service)
-  Template switching directly from Home Assistant
-   Custom Template for easy configuration

---

## Hardware

Designed for:
- ESP32-S3 (WROOM-1 recommended)
- SSD1322 256x64 OLED display (SPI)

---

## Quick Start

1. Flash the firmware using ESPHome.
2. Add the device to Home Assistant.
3. Update the `weather_entity` substitution if needed.
4. Setup a remote calendar in HA named, 'glanceatcalendar', connect the integration to the calendar you would like it to display. 
5. Select your preferred template from Home Assistant.

Full setup instructions are available at
https://labs.smarthomeshopuk.com/guides/glanceat-setup

---

## Weather Setup

By default, the firmware uses:

weather.forecast_home, if you have a custom weather integration in Home Assistant:
1. Go to HA -> Developer Tools -> States
2. Find your weater. entity
3. Update this line in 'glanceat-oled.yaml', in the substituitions section.

---

## Calendar Setup

The calendar view uses the Home Assistant **Remote Calendar** integration.

To configure:

1. Go to **Settings → Devices & Services → Add Integration**
2. Search for **Remote Calendar**
3. Add your calendar using its iCal / ICS URL
4. Name the calendar: 'glanceatcalendar'

---

## Notifications

You can trigger a notification overlay from home assistant using the service
esphome.glanceat_oled_show_notification. 



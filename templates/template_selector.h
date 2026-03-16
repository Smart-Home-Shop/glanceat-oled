#pragma once

#include "clock_weather.h"
#include "calendar.h"
#include "custom.h"


// ======================================================
// Global Notification Overlay
// ======================================================
static bool render_notification_overlay(display::Display &it) {

  if (!id(notification_active))
    return false;

  unsigned long elapsed = millis() - id(notification_started_ms);

  unsigned long duration = id(notification_duration_ms);

  if (elapsed > duration) {
    id(notification_active) = false;
    return false;
  }

  it.fill(COLOR_OFF);

  const std::string msg = id(notification_text);
  const size_t max_len = 38;

  std::string line1;
  std::string line2;

  if (msg.length() <= max_len) {
    line1 = msg;
  } else {
    size_t split = msg.rfind(' ', max_len);
    if (split == std::string::npos) split = max_len;

    line1 = msg.substr(0, split);
    line2 = msg.substr(split + 1);

    if (line2.length() > max_len - 3)
      line2 = line2.substr(0, max_len - 3) + "...";
  }

  it.printf(128, 4,
            &id(font_small),
            TextAlign::TOP_CENTER,
            "Notification");

  it.line(40, 18, 215, 18, COLOR_ON);

  it.printf(128, 26,
            &id(font_small),
            TextAlign::TOP_CENTER,
            "%s", line1.c_str());

  if (!line2.empty()) {
    it.printf(128, 40,
              &id(font_small),
              TextAlign::TOP_CENTER,
              "%s", line2.c_str());
  }

  return true;
}


// ======================================================
// Template Router
// ======================================================
void render_template(display::Display &it) {

  // First: global overlay check
  if (render_notification_overlay(it))
    return;

  // Then render selected template
  switch (id(active_template)) {

    case 2:
      render_custom(it);
      break;

    case 1:
      render_calendar(it);
      break;

    case 0:
    default:
      render_clock_weather(it);
      break;
  }
}
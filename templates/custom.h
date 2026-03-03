#pragma once

// =====================================================
//  CUSTOM TEMPLATE (USER SAFE FILE)
// -----------------------------------------------------
//  This file is safe to edit.
//  You can customise the display here.
//  It will not be overwritten during updates.
//
// =====================================================

void render_custom(display::Display &it) {

  it.fill(COLOR_OFF);

  // ==============================
  // Layout constants
  // ==============================
  constexpr int TITLE_Y   = 12;
  constexpr int LINE_Y    = 30;
  constexpr int MESSAGE_Y = 40;

  // ==============================
  // Title
  // ==============================
  it.printf(128, TITLE_Y,
            &id(font_medium),
            TextAlign::TOP_CENTER,
            "Custom Template");

  // Divider
  it.line(40, LINE_Y, 215, LINE_Y, COLOR_ON);

  // ==============================
  // Instruction
  // ==============================
  it.printf(128, MESSAGE_Y,
            &id(font_small),
            TextAlign::TOP_CENTER,
            "Edit custom.h");

}

// Example code: show temperature if available
/*
if (id(weather_temperature).has_state()) {
  it.printf(128, 52,
            &id(font_small),
            TextAlign::TOP_CENTER,
            "%.0f °C",
            id(weather_temperature).state);
}
*/
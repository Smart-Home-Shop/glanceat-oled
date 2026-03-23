#pragma once

// ===============================
// Weather Condition Formatter
// ===============================
static const char* format_weather_condition(const std::string &condition) {

  if (condition == "clear-night") return "Clear Night";
  if (condition == "cloudy") return "Cloudy";
  if (condition == "exceptional") return "Exceptional";
  if (condition == "fog") return "Fog";
  if (condition == "hail") return "Hail";
  if (condition == "lightning") return "Thunderstorm";
  if (condition == "lightning-rainy") return "Thunderstorm";
  if (condition == "partlycloudy") return "Partly Cloudy";
  if (condition == "pouring") return "Heavy Rain";
  if (condition == "rainy") return "Rain";
  if (condition == "snowy") return "Snow";
  if (condition == "snowy-rainy") return "Sleet";
  if (condition == "sunny") return "Sunny";
  if (condition == "windy") return "Windy";
  if (condition == "windy-variant") return "Windy";

  // fallback formatting
  if (!condition.empty()) {
    static std::string formatted;
    formatted = condition;
    formatted[0] = toupper(formatted[0]);
    return formatted.c_str();
  }

  return "";
}


// ===============================
// Clock + Weather Template
// ===============================
void render_clock_weather(display::Display &it) {

  it.fill(COLOR_OFF);

  auto now = id(sntp_time).now();

  // ---- Time ----
  it.strftime(
    128, 0,
    &id(font_large),
    TextAlign::TOP_CENTER,
    "%H:%M",
    now
  );

  // ---- Date ----
  it.strftime(
    128, 26,
    &id(font_small),
    TextAlign::TOP_CENTER,
    "%A, %d %B %Y",
    now
  );

  // Divider
  it.line(36, 42, 220, 42, COLOR_ON);

  // ===============================
  // Weather validation
  // ===============================
  if (!id(weather_state).has_state() ||
      !id(weather_temp).has_state() ||
      id(weather_state).state == "unknown" ||
      id(weather_state).state == "unavailable") {

    it.printf(
      128, 48,
      &id(font_small),
      TextAlign::TOP_CENTER,
      "Weather not configured"
    );

    return;
  }

  // ===============================
  // Format weather data
  // ===============================

  const std::string &state = id(weather_state).state;
  const char* condition = format_weather_condition(state);

  float temperature = id(weather_temp).state;

  // ===============================
  // Render weather row
  // ===============================

  // Temperature (left)
  it.printf(
    36, 48,
    &id(font_small),
    TextAlign::TOP_LEFT,
    "%.0f °C",
    temperature
  );

  // Condition (right)
  it.printf(
    220, 48,
    &id(font_small),
    TextAlign::TOP_RIGHT,
    "%s",
    condition
  );
}
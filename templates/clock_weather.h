#pragma once

// ===============================
// Weather Condition Formatter
// ===============================
static std::string format_weather_condition(const std::string &condition) {

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

  if (!condition.empty()) {
    std::string formatted = condition;
    formatted[0] = toupper(formatted[0]);
    return formatted;
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
  it.strftime(128, 0, &id(font_large),
              TextAlign::TOP_CENTER,
              "%H:%M:%S", now);

  // ---- Date ----
  it.strftime(128, 26, &id(font_small),
              TextAlign::TOP_CENTER,
              "%A, %d %B %Y", now);

  // Divider
  it.line(40, 42, 215, 42, COLOR_ON);

  // ---- Weather ----
  if (!id(weather_state).has_state() ||
      !id(weather_temp).has_state()) {

    it.printf(128, 48,
              &id(font_small),
              TextAlign::TOP_CENTER,
              "Weather not configured");
    return;
  }

  std::string condition =
      format_weather_condition(id(weather_state).state);

  it.printf(30, 48, &id(font_small),
            TextAlign::TOP_LEFT,
            "%.0f °C",
            id(weather_temp).state);

  it.printf(226, 48, &id(font_small),
            TextAlign::TOP_RIGHT,
            "%s",
            condition.c_str());
}
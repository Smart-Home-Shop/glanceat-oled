#pragma once

void render_calendar(display::Display &it) {

  it.fill(COLOR_OFF);

  const auto now = id(sntp_time).now();

  // ---- Clock (top left) ----
  it.strftime(
    1, 1,
    &id(font_small),
    TextAlign::TOP_LEFT,
    "%H:%M",
    now
  );

  // ======================================================
  // Validate calendar data
  // ======================================================

  if (!id(cal_next_title).has_state() ||
      !id(cal_next_start).has_state() ||
      !id(cal_next_end).has_state()) {

    it.printf(
      128, 32,
      &id(font_small),
      TextAlign::CENTER,
      "Calendar not configured"
    );

    return;
  }

  const std::string &start_str_full = id(cal_next_start).state;
  const std::string &end_str_full   = id(cal_next_end).state;

  if (start_str_full == "unknown" ||
      start_str_full == "unavailable" ||
      end_str_full == "unknown" ||
      end_str_full == "unavailable") {

    it.printf(
      128, 32,
      &id(font_small),
      TextAlign::CENTER,
      "No upcoming events"
    );

    return;
  }

  if (start_str_full.length() < 19 ||
      end_str_full.length() < 19)
    return;

  // ======================================================
  // Parse start time
  // ======================================================

  ESPTime start_time = now;

  start_time.year  = atoi(start_str_full.substr(0,4).c_str());
  start_time.month = atoi(start_str_full.substr(5,2).c_str());
  start_time.day_of_month = atoi(start_str_full.substr(8,2).c_str());
  start_time.hour  = atoi(start_str_full.substr(11,2).c_str());
  start_time.minute= atoi(start_str_full.substr(14,2).c_str());
  start_time.second= atoi(start_str_full.substr(17,2).c_str());

  start_time.recalc_timestamp_local();

  // ======================================================
  // Parse end time
  // ======================================================

  ESPTime end_time = start_time;

  end_time.hour   = atoi(end_str_full.substr(11,2).c_str());
  end_time.minute = atoi(end_str_full.substr(14,2).c_str());
  end_time.second = atoi(end_str_full.substr(17,2).c_str());

  end_time.recalc_timestamp_local();

  const time_t now_ts   = now.timestamp;
  const time_t start_ts = start_time.timestamp;
  const time_t end_ts   = end_time.timestamp;

  const bool event_active =
      (now_ts >= start_ts && now_ts < end_ts);

  // ======================================================
  // Calculate day difference
  // ======================================================

  ESPTime now_midnight = now;
  now_midnight.hour = 0;
  now_midnight.minute = 0;
  now_midnight.second = 0;
  now_midnight.recalc_timestamp_local();

  ESPTime start_midnight = start_time;
  start_midnight.hour = 0;
  start_midnight.minute = 0;
  start_midnight.second = 0;
  start_midnight.recalc_timestamp_local();

  int day_diff =
      (start_midnight.timestamp - now_midnight.timestamp) / 86400;

  // ======================================================
  // Determine day label
  // ======================================================

  char day_label[16];

  if (day_diff == 0) {
    strcpy(day_label, "Today");
  }
  else if (day_diff == 1) {
    strcpy(day_label, "Tomorrow");
  }
  else if (day_diff > 1) {

    static const char* months[] =
      {"Jan","Feb","Mar","Apr","May","Jun",
       "Jul","Aug","Sep","Oct","Nov","Dec"};

    snprintf(
      day_label,
      sizeof(day_label),
      "%02d %s",
      start_time.day_of_month,
      months[start_time.month - 1]
    );
  }
  else {

    it.printf(
      128, 32,
      &id(font_small),
      TextAlign::CENTER,
      "No upcoming events"
    );

    return;
  }

  // ======================================================
  // Title (truncate)
  // ======================================================

  const std::string &title_src = id(cal_next_title).state;

  char title[32];

  if (title_src.length() > 28) {
    snprintf(title, sizeof(title), "%.25s...", title_src.c_str());
  } else {
    snprintf(title, sizeof(title), "%s", title_src.c_str());
  }

  // ======================================================
  // Layout
  // ======================================================

  constexpr int TITLE_Y  = 14;
  constexpr int LINE_Y   = 34;
  constexpr int STATUS_Y = 36;
  constexpr int META_Y   = 50;

  it.printf(
    128, TITLE_Y,
    &id(font_medium),
    TextAlign::TOP_CENTER,
    "%s",
    title
  );

  it.line(12, LINE_Y, 242, LINE_Y, COLOR_ON);

  it.printf(
    128, STATUS_Y,
    &id(font_tiny),
    TextAlign::TOP_CENTER,
    event_active ? "NOW" : "UPCOMING"
  );

  it.printf(
    128, META_Y,
    &id(font_small),
    TextAlign::TOP_CENTER,
    "%s  •  %02d:%02d-%02d:%02d",
    day_label,
    start_time.hour,
    start_time.minute,
    end_time.hour,
    end_time.minute
  );
}
#pragma once

void render_calendar(display::Display &it) {

  it.fill(COLOR_OFF);

  const auto now = id(sntp_time).now();

  // ======================================================
  // Notification Overlay (shared behaviour)
  // ======================================================
  if (id(notification_active)) {

    unsigned long elapsed = millis() - id(notification_started_ms);

    unsigned long duration = id(notification_duration_ms);
    if (duration < 3000) duration = 3000;
    if (duration > 10000) duration = 10000;

    if (elapsed <= duration) {

      std::string msg = id(notification_text);

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

      it.printf(128, 4, &id(font_small),
                TextAlign::TOP_CENTER,
                "Notification");

      it.line(40, 18, 215, 18);

      it.printf(128, 26, &id(font_small),
                TextAlign::TOP_CENTER,
                "%s", line1.c_str());

      if (!line2.empty()) {
        it.printf(128, 40, &id(font_small),
                  TextAlign::TOP_CENTER,
                  "%s", line2.c_str());
      }

      return;
    }

    id(notification_active) = false;
  }

  // ======================================================
  // Top-left clock
  // ======================================================
  it.strftime(0, 0, &id(font_small),
              TextAlign::TOP_LEFT,
              "%H:%M", now);

  // ======================================================
  // Validate calendar data
  // ======================================================
  if (!id(cal_next_title).has_state() ||
      !id(cal_next_start).has_state() ||
      !id(cal_next_end).has_state()) {

    it.printf(128, 30, &id(font_medium),
              TextAlign::TOP_CENTER,
              "No upcoming events");
    return;
  }

  const std::string start_str_full = id(cal_next_start).state;
  const std::string end_str_full   = id(cal_next_end).state;

  if (start_str_full.length() < 19 ||
      end_str_full.length() < 19) {
    return;
  }

  const std::string start_str = start_str_full.substr(0, 19);
  const std::string end_str   = end_str_full.substr(0, 19);

  ESPTime start_time = now;
  start_time.year  = atoi(start_str.substr(0,4).c_str());
  start_time.month = atoi(start_str.substr(5,2).c_str());
  start_time.day_of_month = atoi(start_str.substr(8,2).c_str());
  start_time.hour  = atoi(start_str.substr(11,2).c_str());
  start_time.minute= atoi(start_str.substr(14,2).c_str());
  start_time.second= atoi(start_str.substr(17,2).c_str());
  start_time.recalc_timestamp_local();

  ESPTime end_time = start_time;
  end_time.hour   = atoi(end_str.substr(11,2).c_str());
  end_time.minute = atoi(end_str.substr(14,2).c_str());
  end_time.second = atoi(end_str.substr(17,2).c_str());
  end_time.recalc_timestamp_local();

  const time_t now_ts   = now.timestamp;
  const time_t start_ts = start_time.timestamp;
  const time_t end_ts   = end_time.timestamp;

  const bool event_active =
      (now_ts >= start_ts && now_ts < end_ts);

  // ======================================================
  // Day Label
  // ======================================================
  int day_diff = (start_ts - now_ts) / 86400;

  std::string day_label;

  if (day_diff == 0) {
    day_label = "Today";
  } else if (day_diff == 1) {
    day_label = "Tomorrow";
  } else if (day_diff > 1) {

    static const char* months[] =
      {"Jan","Feb","Mar","Apr","May","Jun",
       "Jul","Aug","Sep","Oct","Nov","Dec"};

    char buf[16];
    sprintf(buf, "%02d %s",
            start_time.day_of_month,
            months[start_time.month - 1]);
    day_label = buf;

  } else {
    it.printf(128, 30, &id(font_small),
              TextAlign::TOP_CENTER,
              "No upcoming events");
    return;
  }

  // ======================================================
  // Title (truncate)
  // ======================================================
  std::string title = id(cal_next_title).state;

  const size_t max_title_len = 28;
  if (title.length() > max_title_len)
    title = title.substr(0, max_title_len - 3) + "...";

  // ======================================================
  // Layout constants
  // ======================================================
  constexpr int TITLE_Y  = 14;
  constexpr int LINE_Y   = 34;
  constexpr int STATUS_Y = 36;
  constexpr int META_Y   = 50;

  // ======================================================
  // Render Layout
  // ======================================================
  it.printf(128, TITLE_Y,
            &id(font_medium),
            TextAlign::TOP_CENTER,
            "%s", title.c_str());

  it.line(12, LINE_Y, 242, LINE_Y, COLOR_ON);

  it.printf(128, STATUS_Y,
            &id(font_tiny),
            TextAlign::TOP_CENTER,
            event_active ? "NOW" : "UPCOMING");

  it.printf(128, META_Y,
            &id(font_small),
            TextAlign::TOP_CENTER,
            "%s  •  %02d:%02d-%02d:%02d",
            day_label.c_str(),
            start_time.hour,
            start_time.minute,
            end_time.hour,
            end_time.minute);
}
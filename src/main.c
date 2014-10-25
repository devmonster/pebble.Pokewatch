#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_player_text; // Player Text
static TextLayer *s_player_name; // My Name
static TextLayer *s_badge_text; // Badges
static TextLayer *s_badge_num; // 16
static TextLayer *s_pokedex_text;
static TextLayer *s_pokedex_num; //251
static TextLayer *s_time_text; // Time
static TextLayer *s_weekday_name; // shortname
static TextLayer *s_current_date; // current date

static GFont s_time_font;
static GFont s_player_font;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";
  static char weekday[] = "SUN";
  static char datenow[] = "JAN 01";
    
  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  strftime(weekday, sizeof("SUN"), "%a", tick_time); 
  strftime(datenow, sizeof("JAN 01"), "%b %e", tick_time);
 
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);
  text_layer_set_text(s_weekday_name, weekday);
  text_layer_set_text(s_current_date, datenow);
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
 update_time();
}

static void main_window_load(Window *window) {
  // Create time TextLayer  
  s_player_text = text_layer_create(GRect(5, 5, 137, 28)); // Player
  s_player_name = text_layer_create(GRect(5, 5, 137, 28)); // Ran Name
  s_badge_text = text_layer_create(GRect(5, 28, 137, 28)); // Badges
  s_badge_num = text_layer_create(GRect(5, 28, 137, 28)); // 16
  s_pokedex_text = text_layer_create(GRect(5, 51, 137, 28)); // Pokedex
  s_pokedex_num = text_layer_create(GRect(5, 51, 137, 28)); // 251
  s_time_text = text_layer_create(GRect(5, 83, 137, 28)); // Time
  s_time_layer = text_layer_create(GRect(5, 96, 139, 50)); // Actual Time
  s_weekday_name = text_layer_create(GRect(5, 83, 139, 50)); // Short weekday
  s_current_date = text_layer_create(GRect(5, 124, 139, 50)); // JAN 01
  
  text_layer_set_background_color(s_player_text, GColorClear);
  text_layer_set_text_color(s_player_text, GColorBlack);  
  
  text_layer_set_background_color(s_player_name, GColorClear);
  text_layer_set_text_color(s_player_name, GColorBlack);  
  
  text_layer_set_background_color(s_badge_text, GColorClear);
  text_layer_set_text_color(s_badge_text, GColorBlack);  
  
  text_layer_set_background_color(s_badge_num, GColorClear);
  text_layer_set_text_color(s_badge_num, GColorBlack);  
  
  text_layer_set_background_color(s_pokedex_text, GColorClear);
  text_layer_set_text_color(s_pokedex_text, GColorBlack);  
  
  text_layer_set_background_color(s_pokedex_num, GColorClear);
  text_layer_set_text_color(s_pokedex_num, GColorBlack);  
  
  text_layer_set_background_color(s_time_text, GColorClear);
  text_layer_set_text_color(s_time_text, GColorBlack);  
  
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  
  text_layer_set_background_color(s_weekday_name, GColorClear);
  text_layer_set_text_color(s_weekday_name, GColorBlack);
  
  text_layer_set_background_color(s_current_date, GColorClear);
  text_layer_set_text_color(s_current_date, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_text_alignment(s_player_text, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_player_name, GTextAlignmentRight);
  text_layer_set_text_alignment(s_badge_text, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_badge_num, GTextAlignmentRight);
  text_layer_set_text_alignment(s_pokedex_text, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_pokedex_num, GTextAlignmentRight);
  text_layer_set_text_alignment(s_time_text, GTextAlignmentLeft);  
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_weekday_name, GTextAlignmentRight);
  text_layer_set_text_alignment(s_current_date, GTextAlignmentCenter);
  
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_player_text));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_player_name));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_badge_text));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_badge_num));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_pokedex_text));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_pokedex_num));  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_text));  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weekday_name));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_current_date));
  
  // Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_POKEFONT_24));
  s_player_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_POKEFONT_12));

  // Apply to TextLayer  
  text_layer_set_font(s_player_text, s_player_font);
  text_layer_set_font(s_player_name, s_player_font);
  text_layer_set_font(s_badge_text, s_player_font);
  text_layer_set_font(s_badge_num, s_player_font);
  text_layer_set_font(s_pokedex_text, s_player_font);
  text_layer_set_font(s_pokedex_num, s_player_font);
  text_layer_set_font(s_time_text, s_player_font);
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_font(s_weekday_name, s_player_font);
  text_layer_set_font(s_current_date, s_player_font);
  
  text_layer_set_text(s_player_text, "PLAYER");
  text_layer_set_text(s_player_name, "Ran");
    
  text_layer_set_text(s_badge_text, "BADGES");
  text_layer_set_text(s_badge_num, "16");
  
  text_layer_set_text(s_pokedex_text, "POKeDEX");
  text_layer_set_text(s_pokedex_num, "251");
  
  text_layer_set_text(s_time_text, "TIME");
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_player_text);
    text_layer_destroy(s_player_name);
    text_layer_destroy(s_badge_text);
    text_layer_destroy(s_badge_num);
    text_layer_destroy(s_pokedex_text);
    text_layer_destroy(s_pokedex_num);
    text_layer_destroy(s_time_text);
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_weekday_name);
    text_layer_destroy(s_current_date);
  
    // Unload GFont
    fonts_unload_custom_font(s_time_font);
    fonts_unload_custom_font(s_player_font);
}


static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  update_time();
}

static void deinit() {
    tick_timer_service_unsubscribe();
  
    // Destroy Window
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
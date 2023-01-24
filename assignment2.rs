use esp_idf_sys::{gpio_set_direction, gpio_set_level, gpio_get_level};
use esp_idf_sys::gpio::{GPIO_NUM_17, GPIO_NUM_18, GPIO_MODE_OUTPUT};
use esp_idf_sys::gpio_pad_select_gpio;
use esp_idf_sys::esp_timer::esp_timer_get_time;
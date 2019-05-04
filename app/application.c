#include <application.h>
#include <vl53l0x.h>

bc_led_t led;
bool init_failed = true;

void application_init(void)
{
    bc_led_init(&led, BC_GPIO_LED, false, false);

    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);

    if (!vl53l0x_init(0x29, 500, false))
    {
        bc_log_error("vl53l0x init failed");
        bc_led_set_mode(&led, BC_LED_MODE_BLINK);
    }
    else
    {
        bc_log_info("vl53l0x init success");
        bc_led_pulse(&led, 200);
        init_failed = false;
        vl53l0x_start_continuous(0);
    }
}

void application_task(void)
{
    if (init_failed)
    {
        return;
    }

    uint16_t avg = 0;
    bool err = false;
    for (uint8_t i = 0; i < 5; i++)
    {
        uint16_t distance = vl53l0x_read_range_continuous_millimeters();
        if (vl53l0x_timeout_occurred() || distance > 8000 || distance < 50)
        {
            distance = 0;
            err = true;
        }
        avg += distance;
    }
    avg = avg / 5;

    if (err)
    {
        bc_log_warning("Measurement error");
    }
    else
    {
        bc_log_info("%u mm", avg);
    }

    bc_scheduler_plan_current_relative(10);
}

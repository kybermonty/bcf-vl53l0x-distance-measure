#include <application.h>
#include <vl53l0x.h>

bc_led_t led;
bool init_failed = true;

void application_init(void)
{
    bc_led_init(&led, BC_GPIO_LED, false, false);
    bc_led_pulse(&led, 500);

    bc_log_init(BC_LOG_LEVEL_DUMP, BC_LOG_TIMESTAMP_ABS);

    bc_system_pll_enable();

    if (!vl53l0x_init(41, 500, false))
    {
        bc_log_debug("vl53l0x init failed");
    }
    else
    {
        bc_log_debug("vl53l0x init success");
        init_failed = false;
    }
}

void application_task(void)
{
    if (init_failed)
    {
        return;
    }
    bc_log_debug("%d", vl53l0x_read_range_single_millimeters());
    if (vl53l0x_timeout_occurred()) {
        bc_log_debug("TIMEOUT");
    }

    bc_scheduler_plan_current_relative(200);
}

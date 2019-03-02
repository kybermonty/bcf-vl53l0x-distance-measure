#ifndef _VL53L0X_H
#define _VL53L0X_H

#include <bcl.h>

uint8_t address;
bool did_timeout;
bc_tick_t io_timeout;
bc_tick_t timeout_start_ms;

typedef enum
{
    VcselPeriodPreRange,
    VcselPeriodFinalRange
} vcselPeriodType;

bool vl53l0x_init(uint8_t addr, bc_tick_t timeout, bool io_2v8);
uint16_t vl53l0x_read_range_single_millimeters();
inline uint8_t vl53l0x_get_address() { return address; }
void vl53l0x_set_address(uint8_t new_addr);
inline bc_tick_t vl53l0x_get_timeout() { return io_timeout; }
inline void vl53l0x_set_timeout(bc_tick_t timeout) { io_timeout = timeout; }
bool vl53l0x_timeout_occurred();
void vl53l0x_write_reg(uint8_t reg, uint8_t value);
void vl53l0x_write_reg16_bit(uint8_t reg, uint16_t value);
void vl53l0x_write_reg32_bit(uint8_t reg, uint32_t value);
uint8_t vl53l0x_read_reg(uint8_t reg);
uint16_t vl53l0x_read_reg16_bit(uint8_t reg);
uint32_t vl53l0x_read_reg32_bit(uint8_t reg);
void vl53l0x_write_multi(uint8_t reg, uint8_t const * src, uint8_t count);
void vl53l0x_read_multi(uint8_t reg, uint8_t * dst, uint8_t count);
bool vl53l0x_set_signal_rate_limit(float limit_mcps);
float vl53l0x_get_signal_rate_limit();
bool vl53l0x_set_measurement_timing_budget(uint32_t budget_us);
uint32_t vl53l0x_get_measurement_timing_budget();
bool vl53l0x_set_vcsel_pulse_period(vcselPeriodType type, uint8_t period_pclks);
uint8_t vl53l0x_get_vcsel_pulse_period(vcselPeriodType type);
void vl53l0x_start_continuous(uint32_t period_ms);
void vl53l0x_stop_continuous();
uint16_t vl53l0x_read_range_continuous_millimeters();

#endif // _VL53L0X_H

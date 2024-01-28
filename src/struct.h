#pragma once

// current = res[4] << 16 | res[3] mA
// active_power = (res[6] << 16 | res[5]) / 10 W
struct dfun_meter_data
{
  uint16_t active_energy = 0;
  uint16_t voltage = 230;
  uint16_t current = 0;
  int16_t active_power = 0;
  uint16_t frequency = 50;
};

// http://192.168.33.1/rpc/EMData.GetStatus?id=0
struct shelly_phase_c_data
{
  uint16_t c_total_act_energy;
  uint16_t c_total_act_ret_energy;
};

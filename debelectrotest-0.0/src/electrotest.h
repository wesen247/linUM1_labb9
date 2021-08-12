#ifndef __ELECTROTEST_H__
#define __ELECTROTEST_H__

float calc_resistance(int count, char conn, float *array);
float calc_power_r(float volt, float resistance);
float calc_power_i(float volt, float current);
int e_resistance(float orig_resistance, float *res_array);

#endif

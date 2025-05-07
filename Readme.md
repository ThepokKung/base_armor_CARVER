# Coil Mapping Reference

This code is referenced from an older version. Remove references to `touchless_switch` and `Alcohol`.

## Sensor Readings 

| Coil Number | Function | Description |
|-------------|----------|-------------|
| 0 | emer | Emergency |
| 1 | limit_b_l | Back Left Limit |
| 2 | limit_b_r | Back Right Limit |
| 3 | limit_f_l | Front Left Limit |
| 4 | limit_f_r | Front Right Limit |


## Command Inputs

| Coil Number | Function     | Description                              |
|-------------|--------------|------------------------------------------|
| 10          | led_red      | Activate red LED                         |
| 11          | led_green    | Activate green LED                       |
| 12          | led_blue     | Activate blue LED                        |
| 13          | led_off      | Turn off all LEDs                        |
| 14          | led_white        | Activate all LEDs (white)                |
| 15          | led_purple       | Activate red and green LEDs (purple)     |
| 16          | led_yellow       | Activate red and blue LEDs (yellow)      |
| 17          | led_indigo       | Activate green and blue LEDs (indigo)    |
| 20          | start_motor  | Initiate the motor start sequence        |
| 21          | stop_motor   | Initiate the motor stop sequence         |

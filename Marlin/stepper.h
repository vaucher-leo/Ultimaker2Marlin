/*
  stepper.h - stepper motor driver: executes motion plans of planner.c using the stepper motors
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STEPPER_H
#define STEPPER_H

#include "planner.h"

#if EXTRUDERS > 2
  #define WRITE_E_STEP(v) { if(current_block->active_extruder == 2) { WRITE(E2_STEP_PIN, v); } else { if(current_block->active_extruder == 1) { WRITE(E1_STEP_PIN, v); } else { WRITE(E0_STEP_PIN, v); }}}
  #define NORM_E_DIR() { if(current_block->active_extruder == 2) { WRITE(E2_DIR_PIN, !INVERT_E2_DIR); } else { if(current_block->active_extruder == 1) { WRITE(E1_DIR_PIN, !INVERT_E1_DIR); } else { WRITE(E0_DIR_PIN, !INVERT_E0_DIR); }}}
  #define REV_E_DIR() { if(current_block->active_extruder == 2) { WRITE(E2_DIR_PIN, INVERT_E2_DIR); } else { if(current_block->active_extruder == 1) { WRITE(E1_DIR_PIN, INVERT_E1_DIR); } else { WRITE(E0_DIR_PIN, INVERT_E0_DIR); }}}
#elif EXTRUDERS > 1
  #define WRITE_E_STEP(v) { if(current_block->active_extruder == 1) { WRITE(E1_STEP_PIN, v); } else { WRITE(E0_STEP_PIN, v); }}
  #define NORM_E_DIR() { if(current_block->active_extruder == 1) { WRITE(E1_DIR_PIN, !INVERT_E1_DIR); } else { WRITE(E0_DIR_PIN, !INVERT_E0_DIR); }}
  #define REV_E_DIR() { if(current_block->active_extruder == 1) { WRITE(E1_DIR_PIN, INVERT_E1_DIR); } else { WRITE(E0_DIR_PIN, INVERT_E0_DIR); }}
#else
  #define WRITE_E_STEP(v) WRITE(E0_STEP_PIN, v)
  #define NORM_E_DIR() WRITE(E0_DIR_PIN, !INVERT_E0_DIR)
  #define REV_E_DIR() WRITE(E0_DIR_PIN, INVERT_E0_DIR)
#endif

#if MOTOR_CURRENT_PWM_XY_PIN > -1
extern int motor_current_setting[3];
#endif

#ifdef ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED
extern bool abort_on_endstop_hit;
#endif

// Initialize and start the stepper motor subsystem
void st_init();

// Block until all buffered steps are executed
void st_synchronize();

// Set current position in steps
void st_set_position(const long &x, const long &y, const long &z, const long &a, const long &c, const long &e);
void st_set_e_position(const long &e);

// Get current position in steps
long st_get_position(uint8_t axis);

// The stepper subsystem goes to sleep when it runs out of things to execute. Call this
// to notify the subsystem that it is time to go to work.
void st_wake_up();


void checkHitEndstops();        // Call from somewhere to create a serial error message with the locations where the endstops were hit, in case they were triggered
void endstops_hit_on_purpose(); // Avoid creation of the message, i.e. after homing and before a routine call of checkHitEndstops().

void enable_endstops(bool check); // Enable/disable endstop checking

void checkStepperErrors(); //Print errors detected by the stepper
bool isEndstopHit();

void finishAndDisableSteppers();

extern block_t *current_block;  // A pointer to the block currently being traced

void quickStop();

void digitalPotWrite(int address, int value);
void microstep_ms(uint8_t driver, int8_t ms1, int8_t ms2);
void microstep_mode(uint8_t driver, uint8_t stepping);
void digipot_init();
void digipot_current(uint8_t driver, int current);
void microstep_init();
void microstep_readings();

#endif  // STEPPER_H

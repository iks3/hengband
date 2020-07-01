﻿#pragma once

#include "system/angband.h"

void set_action(player_type *creature_ptr, ACTION_IDX typ);
void dispel_player(player_type *creature_ptr);
bool hp_player(player_type *creature_ptr, int num);
void do_poly_self(player_type *creature_ptr);
void do_poly_wounds(player_type *creature_ptr);
void change_race(player_type *creature_ptr, player_race_type new_race, concptr effect_msg);

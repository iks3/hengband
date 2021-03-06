﻿#pragma once

#include "system/angband.h"

struct MonsterSpellResult;

typedef struct player_type player_type;
MonsterSpellResult spell_RF5_CAUSE_1(player_type *target_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_2(player_type *target_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_3(player_type *target_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);
MonsterSpellResult spell_RF5_CAUSE_4(player_type *target_ptr, POSITION y, POSITION x, MONSTER_IDX m_idx, MONSTER_IDX t_idx, int TARGET_TYPE);

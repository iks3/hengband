#pragma once

/*! �I�[�g���[���̔N��A�g���A�̏d�A�Љ�I�n�ʂ̗v������ */
typedef struct {
    s16b agemin, agemax;
    s16b htmin, htmax;
    s16b wtmin, wtmax;
    s16b scmin, scmax;
} chara_limit_type;

extern s16b stat_limit[6];
bool get_stat_limits(player_type *creature_ptr);
void initialize_chara_limit(chara_limit_type *chara_limit_ptr);
bool get_chara_limits(player_type *creature_ptr, chara_limit_type *chara_limit_ptr);
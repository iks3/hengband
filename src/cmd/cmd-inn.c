﻿#include "angband.h"
#include "cmd/cmd-inn.h"
#include "cmd/cmd-magiceat.h"
#include "io/write-diary.h"
#include "world.h"
#include "player-effects.h"
#include "core.h" // 暫定、後で消す.
#include "rumor.h"

/*!
 * @brief 宿屋の利用サブルーチン
 * @details inn commands\n
 * Note that resting for the night was a perfect way to avoid player\n
 * ghosts in the town *if* you could only make it to the inn in time (-:\n
 * Now that the ghosts are temporarily disabled in 2.8.X, this function\n
 * will not be that useful.  I will keep it in the hopes the player\n
 * ghost code does become a reality again. Does help to avoid filthy urchins.\n
 * Resting at night is also a quick way to restock stores -KMW-\n
 * @param cmd 宿屋の利用施設ID
 * @return 施設の利用が実際に行われたか否か。
 */
bool inn_comm(player_type *customer_ptr, int cmd)
{
	switch (cmd)
	{
	case BACT_FOOD: /* Buy food & drink */
		if (customer_ptr->food >= PY_FOOD_FULL)
		{
			msg_print(_("今は満腹だ。", "You are full now."));
			return FALSE;
		}

		msg_print(_("バーテンはいくらかの食べ物とビールをくれた。", "The barkeep gives you some gruel and a beer."));
		(void)set_food(customer_ptr, PY_FOOD_MAX - 1);
		break;

	case BACT_REST: /* Rest for the night */
	{
		if ((customer_ptr->poisoned) || (customer_ptr->cut))
		{
			msg_print(_("あなたに必要なのは部屋ではなく、治療者です。", "You need a healer, not a room."));
			msg_print(NULL);
			msg_print(_("すみません、でもうちで誰かに死なれちゃ困りますんで。", "Sorry, but don't want anyone dying in here."));
			break;
		}

		s32b oldturn = current_world_ptr->game_turn;
		int prev_day, prev_hour, prev_min;

		extract_day_hour_min(customer_ptr, &prev_day, &prev_hour, &prev_min);
		bool is_player_undead = PRACE_IS_(customer_ptr, RACE_SKELETON) ||
			PRACE_IS_(customer_ptr, RACE_ZOMBIE) ||
			PRACE_IS_(customer_ptr, RACE_VAMPIRE) ||
			PRACE_IS_(customer_ptr, RACE_SPECTRE);
		if ((prev_hour >= 6) && (prev_hour < 18))
		{
			concptr stay_message_jp = is_player_undead ? "宿屋に泊まった" : "日が暮れるまで宿屋で過ごした";
			exe_write_diary(customer_ptr, DIARY_DESCRIPTION, 0, _(stay_message_jp, "stayed during the day at the inn."));
		}
		else
		{
			concptr stay_message_jp = is_player_undead ? "夜が明けるまで宿屋で過ごした" : "宿屋に泊まった";
			exe_write_diary(customer_ptr, DIARY_DESCRIPTION, 0, _(stay_message_jp, "stayed overnight at the inn."));
		}

		current_world_ptr->game_turn = (current_world_ptr->game_turn / (TURNS_PER_TICK * TOWN_DAWN / 2) + 1) * (TURNS_PER_TICK * TOWN_DAWN / 2);
		if (current_world_ptr->dungeon_turn < current_world_ptr->dungeon_turn_limit)
		{
			current_world_ptr->dungeon_turn += MIN((current_world_ptr->game_turn - oldturn), TURNS_PER_TICK * 250) * INN_DUNGEON_TURN_ADJ;
			if (current_world_ptr->dungeon_turn > current_world_ptr->dungeon_turn_limit) current_world_ptr->dungeon_turn = current_world_ptr->dungeon_turn_limit;
		}

		prevent_turn_overflow(customer_ptr);

		if ((prev_hour >= 18) && (prev_hour <= 23)) exe_write_diary(customer_ptr, DIARY_DIALY, 0, NULL);
		customer_ptr->chp = customer_ptr->mhp;

		if (ironman_nightmare)
		{
			msg_print(_("眠りに就くと恐ろしい光景が心をよぎった。", "Horrible visions flit through your mind as you sleep."));

			while (TRUE)
			{
				sanity_blast(customer_ptr, NULL, FALSE);
				if (!one_in_(3)) break;
			}

			msg_print(_("あなたは絶叫して目を覚ました。", "You awake screaming."));
			exe_write_diary(customer_ptr, DIARY_DESCRIPTION, 0, _("悪夢にうなされてよく眠れなかった。", "had a nightmare."));
			break;
		}

		set_blind(customer_ptr, 0);
		set_confused(customer_ptr, 0);
		customer_ptr->stun = 0;
		customer_ptr->chp = customer_ptr->mhp;
		customer_ptr->csp = customer_ptr->msp;
		if (customer_ptr->pclass == CLASS_MAGIC_EATER)
		{
			int i;
			for (i = 0; i < 72; i++)
			{
				customer_ptr->magic_num1[i] = customer_ptr->magic_num2[i] * EATER_CHARGE;
			}

			for (; i < 108; i++)
			{
				customer_ptr->magic_num1[i] = 0;
			}
		}

		if ((prev_hour >= 6) && (prev_hour <= 17))
		{
			msg_print(_("あなたはリフレッシュして目覚め、夕方を迎えた。", "You awake refreshed for the evening."));
			exe_write_diary(customer_ptr, DIARY_DESCRIPTION, 0, _("夕方を迎えた。", "awoke refreshed."));
			break;
		}

		msg_print(_("あなたはリフレッシュして目覚め、新たな日を迎えた。", "You awake refreshed for the new day."));
		exe_write_diary(customer_ptr, DIARY_DESCRIPTION, 0, _("すがすがしい朝を迎えた。", "awoke refreshed."));
		break;
	}
	case BACT_RUMORS: /* Listen for rumors */
	{
		display_rumor(customer_ptr, TRUE);
		break;
	}
	}

	return TRUE;
}

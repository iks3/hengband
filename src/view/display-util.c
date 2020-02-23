#include "display-util.h"
#include "term.h"

static struct
{
	int col;
	int row;
	int len;
	char header[20];
} disp_player_line[]
#ifdef JP
= {
	{ 1, 10, 25, "ÅC³(i¬)"},
	{ 1, 10, 25, "ÅC³(¼è)"},
	{ 1, 10, 25, "ÅC³(Eè)"},
	{ 1, 10, 25, "ÅC³(¶è)"},
	{ 1, 11, 25, "ÅC³(¶è)"},
	{ 1, 11, 25, "ÅC³(Eè)"},
	{ 1, 11, 25, ""},
	{ 1, 15, 25, "ËUC³"},
	{ 1, 16, 25, "Ëí{¦"},
	{ 1, 20, 25, "Á¬"},
	{ 1, 19, 25, "`b"},
	{29, 13, 21, "x"},
	{29, 14, 21, "o±l"},
	{29, 15, 21, "Ååo±"},
	{29, 16, 21, "x"},
	{29, 17, 21, "à"},
	{29, 19, 21, "út"},
	{29, 10, 21, "go"},
	{29, 11, 21, "lo"},
	{29, 20, 21, "vCÔ"},
	{53, 10, -1, "Å½  :"},
	{53, 11, -1, "Ë½  :"},
	{53, 12, -1, "@hä  :"},
	{53, 13, -1, "B§s®  :"},
	{53, 15, -1, "mo      :"},
	{53, 16, -1, "Tõ      :"},
	{53, 17, -1, "ð      :"},
	{53, 18, -1, "@¹ï  :"},
	{ 1, 12, 25, "Åñ"},
	{ 1, 17, 25, "Ëñ"},
	{ 1, 13, 25, "½Ï_[W"},
	{53, 20, -1, "ÔOüÍ:"},
	{26,  1, -1, "¼O  : "},
	{ 1,  3, -1, "«Ê     : "},
	{ 1,  4, -1, "í°     : "},
	{ 1,  5, -1, "EÆ     : "},
	{ 1,  6, -1, "@     : "},
	{ 1,  7, -1, "çì_ : "},
	{29,  3, 21, "Nî"},
	{29,  4, 21, "g·"},
	{29,  5, 21, "Ìd"},
	{29,  6, 21, "ÐïInÊ"},
	{29,  7, 21, "®«"},
	{29, 14, 21, "­»x"},
	{29, 16, 21, "x"},
	{53, 19, -1, "@í      :" },
};
#else
= {
	{ 1, 10, 25, "Bare hand"},
	{ 1, 10, 25, "Two hands"},
	{ 1, 10, 25, "Right hand"},
	{ 1, 10, 25, "Left hand"},
	{ 1, 11, 25, "Left hand"},
	{ 1, 11, 25, "Right hand"},
	{ 1, 11, 25, "Posture"},
	{ 1, 15, 25, "Shooting"},
	{ 1, 16, 25, "Multiplier"},
	{ 1, 20, 25, "Speed"},
	{ 1, 19, 25, "AC"},
	{29, 13, 21, "Level"},
	{29, 14, 21, "Experience"},
	{29, 15, 21, "Max Exp"},
	{29, 16, 21, "Exp to Adv"},
	{29, 17, 21, "Gold"},
	{29, 19, 21, "Time"},
	{29, 10, 21, "Hit point"},
	{29, 11, 21, "SP (Mana)"},
	{29, 20, 21, "Play time"},
	{53, 10, -1, "Fighting   : "},
	{53, 11, -1, "Bows/Throw : "},
	{53, 12, -1, "SavingThrow: "},
	{53, 13, -1, "Stealth    : "},
	{53, 15, -1, "Perception : "},
	{53, 16, -1, "Searching  : "},
	{53, 17, -1, "Disarming  : "},
	{53, 18, -1, "MagicDevice: "},
	{ 1, 12, 25, "Blows/Round"},
	{ 1, 17, 25, "Shots/Round"},
	{ 1, 13, 25, "AverageDmg/Rnd"},
	{53, 20, -1, "Infravision: "},
	{26,  1, -1, "Name  : "},
	{ 1,  3, -1, "Sex      : "},
	{ 1,  4, -1, "Race     : "},
	{ 1,  5, -1, "Class    : "},
	{ 1,  6, -1, "Magic    : "},
	{ 1,  7, -1, "Patron   : "},
	{29,  3, 21, "Age"},
	{29,  4, 21, "Height"},
	{29,  5, 21, "Weight"},
	{29,  6, 21, "Social Class"},
	{29,  7, 21, "Align"},
	{29, 14, 21, "Construction"},
	{29, 16, 21, "Const to Adv"},
	{53, 19, -1, "Digging    : " },
};
#endif


/*!
 * @brief vC[ÌXe[^X1íðoÍ·é
 * @param entry ÚID
 * @param val lðÛÇµ½¶ñ|C^
 * @param attr Ú\¦ÌF
 * @return Èµ
 */
void display_player_one_line(int entry, concptr val, TERM_COLOR attr)
{
	concptr head = disp_player_line[entry].header;
	int head_len = strlen(head);
	int row = disp_player_line[entry].row;
	int col = disp_player_line[entry].col;
	int len = disp_player_line[entry].len;
	Term_putstr(col, row, -1, TERM_WHITE, head);

	if (!val) return;

	if (len <= 0)
	{
		Term_putstr(col + head_len, row, -1, attr, val);
		return;
	}

	int val_len = len - head_len;
	char buf[40];
	sprintf(buf, "%*.*s", val_len, val_len, val);
	Term_putstr(col + head_len, row, -1, attr, buf);
}

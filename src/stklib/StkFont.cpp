#include <windows.h>
#include <tchar.h>
#include "StkFont.h"

#define STK_FONT_A 0
#define STK_FONT_B 1
#define STK_FONT_C 2
#define STK_FONT_D 3
#define STK_FONT_E 4
#define STK_FONT_F 5
#define STK_FONT_G 6
#define STK_FONT_H 7
#define STK_FONT_I 8
#define STK_FONT_J 9
#define STK_FONT_K 10
#define STK_FONT_L 11
#define STK_FONT_M 12
#define STK_FONT_N 13
#define STK_FONT_O 14
#define STK_FONT_P 15
#define STK_FONT_Q 16
#define STK_FONT_R 17
#define STK_FONT_S 18
#define STK_FONT_T 19
#define STK_FONT_U 20
#define STK_FONT_V 21
#define STK_FONT_W 22
#define STK_FONT_X 23
#define STK_FONT_Y 24
#define STK_FONT_Z 25
#define STK_FONT_0 30
#define STK_FONT_1 31
#define STK_FONT_2 32
#define STK_FONT_3 33
#define STK_FONT_4 34
#define STK_FONT_5 35
#define STK_FONT_6 36
#define STK_FONT_7 37
#define STK_FONT_8 38
#define STK_FONT_9 39
#define STK_FONT_COMMA 50
#define STK_FONT_DOT 51
#define STK_FONT_COLON 52
#define STK_FONT_SEMICOLON 53
#define STK_FONT_PLUS 54
#define STK_FONT_MINUS 55
#define STK_FONT_DIV 56
#define STK_FONT_MUL 57
#define STK_FONT_RBS 61
#define STK_FONT_RBE 62
#define STK_FONT_QES 63
#define STK_FONT_AT 64
#define STK_FONT_AND 65
#define STK_FONT_OC 66
#define STK_FONT_SPACE 70
#define STK_FONT_EMPTY 71
#define STK_FONT_NEKO 99

StkFont::StkFont()
{
	// STK_FONT_A
	chara[STK_FONT_A].width = 35;
	chara[STK_FONT_A].height = 50;
	chara[STK_FONT_A].length = 2;
	chara[STK_FONT_A].line[0].length = 3;
	chara[STK_FONT_A].line[0].point[0].p(5, 45);
	chara[STK_FONT_A].line[0].point[1].p(20, 5);
	chara[STK_FONT_A].line[0].point[2].p(35, 45);
	chara[STK_FONT_A].line[1].length = 2;
	chara[STK_FONT_A].line[1].point[0].p(10, 30);
	chara[STK_FONT_A].line[1].point[1].p(30, 30);

	// STK_FONT_B
	chara[STK_FONT_B].width = 25;
	chara[STK_FONT_B].height = 50;
	chara[STK_FONT_B].length = 2;
	chara[STK_FONT_B].line[0].length = 10;
	chara[STK_FONT_B].line[0].point[0].p(5, 5);
	chara[STK_FONT_B].line[0].point[1].p(20, 5);
	chara[STK_FONT_B].line[0].point[2].p(25, 10);
	chara[STK_FONT_B].line[0].point[3].p(25, 20);
	chara[STK_FONT_B].line[0].point[4].p(20, 25);
	chara[STK_FONT_B].line[0].point[5].p(25, 30);
	chara[STK_FONT_B].line[0].point[6].p(25, 40);
	chara[STK_FONT_B].line[0].point[7].p(20, 45);
	chara[STK_FONT_B].line[0].point[8].p(5, 45);
	chara[STK_FONT_B].line[0].point[9].p(5, 5);
	chara[STK_FONT_B].line[1].length = 2;
	chara[STK_FONT_B].line[1].point[0].p(5, 25);
	chara[STK_FONT_B].line[1].point[1].p(20, 25);

	// STK_FONT_C
	chara[STK_FONT_C].width = 25;
	chara[STK_FONT_C].height = 50;
	chara[STK_FONT_C].length = 1;
	chara[STK_FONT_C].line[0].length = 10;
	chara[STK_FONT_C].line[0].point[0].p(25, 15);
	chara[STK_FONT_C].line[0].point[1].p(25, 10);
	chara[STK_FONT_C].line[0].point[2].p(20, 5);
	chara[STK_FONT_C].line[0].point[3].p(10, 5);
	chara[STK_FONT_C].line[0].point[4].p(5, 10);
	chara[STK_FONT_C].line[0].point[5].p(5, 40);
	chara[STK_FONT_C].line[0].point[6].p(10, 45);
	chara[STK_FONT_C].line[0].point[7].p(20, 45);
	chara[STK_FONT_C].line[0].point[8].p(25, 40);
	chara[STK_FONT_C].line[0].point[9].p(25, 35);

	// STK_FONT_D
	chara[STK_FONT_D].width = 25;
	chara[STK_FONT_D].height = 50;
	chara[STK_FONT_D].length = 1;
	chara[STK_FONT_D].line[0].length = 7;
	chara[STK_FONT_D].line[0].point[0].p(5, 5);
	chara[STK_FONT_D].line[0].point[1].p(20, 5);
	chara[STK_FONT_D].line[0].point[2].p(25, 10);
	chara[STK_FONT_D].line[0].point[3].p(25, 40);
	chara[STK_FONT_D].line[0].point[4].p(20, 45);
	chara[STK_FONT_D].line[0].point[5].p(5, 45);
	chara[STK_FONT_D].line[0].point[6].p(5, 5);

	// STK_FONT_E
	chara[STK_FONT_E].width = 25;
	chara[STK_FONT_E].height = 50;
	chara[STK_FONT_E].length = 2;
	chara[STK_FONT_E].line[0].length = 4;
	chara[STK_FONT_E].line[0].point[0].p(25, 5);
	chara[STK_FONT_E].line[0].point[1].p(5, 5);
	chara[STK_FONT_E].line[0].point[2].p(5, 45);
	chara[STK_FONT_E].line[0].point[3].p(25, 45);
	chara[STK_FONT_E].line[1].length = 2;
	chara[STK_FONT_E].line[1].point[0].p(5, 25);
	chara[STK_FONT_E].line[1].point[1].p(25, 25);

	// STK_FONT_F
	chara[STK_FONT_F].width = 25;
	chara[STK_FONT_F].height = 50;
	chara[STK_FONT_F].length = 2;
	chara[STK_FONT_F].line[0].length = 3;
	chara[STK_FONT_F].line[0].point[0].p(25, 5);
	chara[STK_FONT_F].line[0].point[1].p(5, 5);
	chara[STK_FONT_F].line[0].point[2].p(5, 45);
	chara[STK_FONT_F].line[1].length = 2;
	chara[STK_FONT_F].line[1].point[0].p(5, 25);
	chara[STK_FONT_F].line[1].point[1].p(25, 25);

	// STK_FONT_G
	chara[STK_FONT_G].width = 35;
	chara[STK_FONT_G].height = 50;
	chara[STK_FONT_G].length = 2;
	chara[STK_FONT_G].line[0].length = 11;
	chara[STK_FONT_G].line[0].point[0].p(30, 15);
	chara[STK_FONT_G].line[0].point[1].p(30, 10);
	chara[STK_FONT_G].line[0].point[2].p(25, 5);
	chara[STK_FONT_G].line[0].point[3].p(10, 5);
	chara[STK_FONT_G].line[0].point[4].p(5, 10);
	chara[STK_FONT_G].line[0].point[5].p(5, 40);
	chara[STK_FONT_G].line[0].point[6].p(10, 45);
	chara[STK_FONT_G].line[0].point[7].p(25, 45);
	chara[STK_FONT_G].line[0].point[8].p(30, 40);
	chara[STK_FONT_G].line[0].point[9].p(30, 30);
	chara[STK_FONT_G].line[0].point[10].p(35, 30);
	chara[STK_FONT_G].line[1].length = 3;
	chara[STK_FONT_G].line[1].point[0].p(20, 30);
	chara[STK_FONT_G].line[1].point[1].p(30, 30);
	chara[STK_FONT_G].line[1].point[2].p(30, 45);

	// STK_FONT_H
	chara[STK_FONT_H].width = 35;
	chara[STK_FONT_H].height = 50;
	chara[STK_FONT_H].length = 3;
	chara[STK_FONT_H].line[0].length = 2;
	chara[STK_FONT_H].line[0].point[0].p(5, 5);
	chara[STK_FONT_H].line[0].point[1].p(5, 45);
	chara[STK_FONT_H].line[1].length = 2;
	chara[STK_FONT_H].line[1].point[0].p(5, 25);
	chara[STK_FONT_H].line[1].point[1].p(35, 25);
	chara[STK_FONT_H].line[2].length = 2;
	chara[STK_FONT_H].line[2].point[0].p(35, 5);
	chara[STK_FONT_H].line[2].point[1].p(35, 45);

	// STK_FONT_I
	chara[STK_FONT_I].width = 20;
	chara[STK_FONT_I].height = 50;
	chara[STK_FONT_I].length = 3;
	chara[STK_FONT_I].line[0].length = 2;
	chara[STK_FONT_I].line[0].point[0].p(5, 5);
	chara[STK_FONT_I].line[0].point[1].p(15, 5);
	chara[STK_FONT_I].line[1].length = 2;
	chara[STK_FONT_I].line[1].point[0].p(5, 45);
	chara[STK_FONT_I].line[1].point[1].p(15, 45);
	chara[STK_FONT_I].line[2].length = 2;
	chara[STK_FONT_I].line[2].point[0].p(10, 5);
	chara[STK_FONT_I].line[2].point[1].p(10, 45);

	// STK_FONT_J
	chara[STK_FONT_J].width = 30;
	chara[STK_FONT_J].height = 50;
	chara[STK_FONT_J].length = 2;
	chara[STK_FONT_J].line[0].length = 2;
	chara[STK_FONT_J].line[0].point[0].p(20, 5);
	chara[STK_FONT_J].line[0].point[1].p(30, 5);
	chara[STK_FONT_J].line[1].length = 6;
	chara[STK_FONT_J].line[1].point[0].p(25, 5);
	chara[STK_FONT_J].line[1].point[1].p(25, 40);
	chara[STK_FONT_J].line[1].point[2].p(20, 45);
	chara[STK_FONT_J].line[1].point[3].p(10, 45);
	chara[STK_FONT_J].line[1].point[4].p(5, 40);
	chara[STK_FONT_J].line[1].point[5].p(5, 30);

	// STK_FONT_K
	chara[STK_FONT_K].width = 30;
	chara[STK_FONT_K].height = 50;
	chara[STK_FONT_K].length = 3;
	chara[STK_FONT_K].line[0].length = 2;
	chara[STK_FONT_K].line[0].point[0].p(5, 5);
	chara[STK_FONT_K].line[0].point[1].p(5, 45);
	chara[STK_FONT_K].line[1].length = 2;
	chara[STK_FONT_K].line[1].point[0].p(5, 20);
	chara[STK_FONT_K].line[1].point[1].p(15, 20);
	chara[STK_FONT_K].line[2].length = 3;
	chara[STK_FONT_K].line[2].point[0].p(25, 5);
	chara[STK_FONT_K].line[2].point[1].p(15, 20);
	chara[STK_FONT_K].line[2].point[2].p(25, 45);

	// STK_FONT_L
	chara[STK_FONT_L].width = 25;
	chara[STK_FONT_L].height = 50;
	chara[STK_FONT_L].length = 1;
	chara[STK_FONT_L].line[0].length = 3;
	chara[STK_FONT_L].line[0].point[0].p(5, 5);
	chara[STK_FONT_L].line[0].point[1].p(5, 45);
	chara[STK_FONT_L].line[0].point[2].p(25, 45);

	// STK_FONT_M
	chara[STK_FONT_M].width = 35;
	chara[STK_FONT_M].height = 50;
	chara[STK_FONT_M].length = 1;
	chara[STK_FONT_M].line[0].length = 5;
	chara[STK_FONT_M].line[0].point[0].p(5, 45);
	chara[STK_FONT_M].line[0].point[1].p(5, 5);
	chara[STK_FONT_M].line[0].point[2].p(20, 25);
	chara[STK_FONT_M].line[0].point[3].p(35, 5);
	chara[STK_FONT_M].line[0].point[4].p(35, 45);

	// STK_FONT_N
	chara[STK_FONT_N].width = 25;
	chara[STK_FONT_N].height = 50;
	chara[STK_FONT_N].length = 1;
	chara[STK_FONT_N].line[0].length = 4;
	chara[STK_FONT_N].line[0].point[0].p(5, 45);
	chara[STK_FONT_N].line[0].point[1].p(5, 5);
	chara[STK_FONT_N].line[0].point[2].p(25, 45);
	chara[STK_FONT_N].line[0].point[3].p(25, 5);

	// STK_FONT_O
	chara[STK_FONT_O].width = 35;
	chara[STK_FONT_O].height = 50;
	chara[STK_FONT_O].length = 1;
	chara[STK_FONT_O].line[0].length = 9;
	chara[STK_FONT_O].line[0].point[0].p(10, 5);
	chara[STK_FONT_O].line[0].point[1].p(30, 5);
	chara[STK_FONT_O].line[0].point[2].p(35, 10);
	chara[STK_FONT_O].line[0].point[3].p(35, 40);
	chara[STK_FONT_O].line[0].point[4].p(30, 45);
	chara[STK_FONT_O].line[0].point[5].p(10, 45);
	chara[STK_FONT_O].line[0].point[6].p(5, 40);
	chara[STK_FONT_O].line[0].point[7].p(5, 10);
	chara[STK_FONT_O].line[0].point[8].p(10, 5);

	// STK_FONT_P
	chara[STK_FONT_P].width = 25;
	chara[STK_FONT_P].height = 50;
	chara[STK_FONT_P].length = 1;
	chara[STK_FONT_P].line[0].length = 7;
	chara[STK_FONT_P].line[0].point[0].p(5, 45);
	chara[STK_FONT_P].line[0].point[1].p(5, 5);
	chara[STK_FONT_P].line[0].point[2].p(20, 5);
	chara[STK_FONT_P].line[0].point[3].p(25, 10);
	chara[STK_FONT_P].line[0].point[4].p(25, 20);
	chara[STK_FONT_P].line[0].point[5].p(20, 25);
	chara[STK_FONT_P].line[0].point[6].p(5, 25);

	// STK_FONT_Q
	chara[STK_FONT_Q].width = 35;
	chara[STK_FONT_Q].height = 50;
	chara[STK_FONT_Q].length = 2;
	chara[STK_FONT_Q].line[0].length = 9;
	chara[STK_FONT_Q].line[0].point[0].p(10, 5);
	chara[STK_FONT_Q].line[0].point[1].p(25, 5);
	chara[STK_FONT_Q].line[0].point[2].p(30, 10);
	chara[STK_FONT_Q].line[0].point[3].p(30, 40);
	chara[STK_FONT_Q].line[0].point[4].p(25, 45);
	chara[STK_FONT_Q].line[0].point[5].p(10, 45);
	chara[STK_FONT_Q].line[0].point[6].p(5, 40);
	chara[STK_FONT_Q].line[0].point[7].p(5, 10);
	chara[STK_FONT_Q].line[0].point[8].p(10, 5);
	chara[STK_FONT_Q].line[1].length = 2;
	chara[STK_FONT_Q].line[1].point[0].p(25, 35);
	chara[STK_FONT_Q].line[1].point[1].p(35, 45);

	// STK_FONT_R
	chara[STK_FONT_R].width = 25;
	chara[STK_FONT_R].height = 50;
	chara[STK_FONT_R].length = 1;
	chara[STK_FONT_R].line[0].length = 9;
	chara[STK_FONT_R].line[0].point[0].p(5, 45);
	chara[STK_FONT_R].line[0].point[1].p(5, 5);
	chara[STK_FONT_R].line[0].point[2].p(20, 5);
	chara[STK_FONT_R].line[0].point[3].p(25, 10);
	chara[STK_FONT_R].line[0].point[4].p(25, 20);
	chara[STK_FONT_R].line[0].point[5].p(20, 25);
	chara[STK_FONT_R].line[0].point[6].p(5, 25);
	chara[STK_FONT_R].line[0].point[7].p(20, 25);
	chara[STK_FONT_R].line[0].point[8].p(25, 45);

	// STK_FONT_S
	chara[STK_FONT_S].width = 25;
	chara[STK_FONT_S].height = 50;
	chara[STK_FONT_S].length = 1;
	chara[STK_FONT_S].line[0].length = 12;
	chara[STK_FONT_S].line[0].point[0].p(25, 10);
	chara[STK_FONT_S].line[0].point[1].p(20, 5);
	chara[STK_FONT_S].line[0].point[2].p(10, 5);
	chara[STK_FONT_S].line[0].point[3].p(5, 10);
	chara[STK_FONT_S].line[0].point[4].p(5, 20);
	chara[STK_FONT_S].line[0].point[5].p(10, 25);
	chara[STK_FONT_S].line[0].point[6].p(20, 25);
	chara[STK_FONT_S].line[0].point[7].p(25, 30);
	chara[STK_FONT_S].line[0].point[8].p(25, 40);
	chara[STK_FONT_S].line[0].point[9].p(20, 45);
	chara[STK_FONT_S].line[0].point[10].p(10, 45);
	chara[STK_FONT_S].line[0].point[11].p(5, 40);

	// STK_FONT_T
	chara[STK_FONT_T].width = 25;
	chara[STK_FONT_T].height = 50;
	chara[STK_FONT_T].length = 2;
	chara[STK_FONT_T].line[0].length = 2;
	chara[STK_FONT_T].line[0].point[0].p(5, 5);
	chara[STK_FONT_T].line[0].point[1].p(25, 5);
	chara[STK_FONT_T].line[1].length = 2;
	chara[STK_FONT_T].line[1].point[0].p(15, 5);
	chara[STK_FONT_T].line[1].point[1].p(15, 45);

	// STK_FONT_U
	chara[STK_FONT_U].width = 25;
	chara[STK_FONT_U].height = 50;
	chara[STK_FONT_U].length = 1;
	chara[STK_FONT_U].line[0].length = 6;
	chara[STK_FONT_U].line[0].point[0].p(5, 5);
	chara[STK_FONT_U].line[0].point[1].p(5, 40);
	chara[STK_FONT_U].line[0].point[2].p(10, 45);
	chara[STK_FONT_U].line[0].point[3].p(20, 45);
	chara[STK_FONT_U].line[0].point[4].p(25, 40);
	chara[STK_FONT_U].line[0].point[5].p(25, 5);

	// STK_FONT_V
	chara[STK_FONT_V].width = 25;
	chara[STK_FONT_V].height = 50;
	chara[STK_FONT_V].length = 1;
	chara[STK_FONT_V].line[0].length = 3;
	chara[STK_FONT_V].line[0].point[0].p(5, 5);
	chara[STK_FONT_V].line[0].point[1].p(15, 45);
	chara[STK_FONT_V].line[0].point[2].p(25, 5);

	// STK_FONT_W
	chara[STK_FONT_W].width = 35;
	chara[STK_FONT_W].height = 50;
	chara[STK_FONT_W].length = 1;
	chara[STK_FONT_W].line[0].length = 5;
	chara[STK_FONT_W].line[0].point[0].p(5, 5);
	chara[STK_FONT_W].line[0].point[1].p(10, 45);
	chara[STK_FONT_W].line[0].point[2].p(20, 5);
	chara[STK_FONT_W].line[0].point[3].p(30, 45);
	chara[STK_FONT_W].line[0].point[4].p(35, 5);

	// STK_FONT_X
	chara[STK_FONT_X].width = 25;
	chara[STK_FONT_X].height = 50;
	chara[STK_FONT_X].length = 2;
	chara[STK_FONT_X].line[0].length = 2;
	chara[STK_FONT_X].line[0].point[0].p(5, 5);
	chara[STK_FONT_X].line[0].point[1].p(25, 45);
	chara[STK_FONT_X].line[1].length = 2;
	chara[STK_FONT_X].line[1].point[0].p(25, 5);
	chara[STK_FONT_X].line[1].point[1].p(5, 45);

	// STK_FONT_Y
	chara[STK_FONT_Y].width = 25;
	chara[STK_FONT_Y].height = 50;
	chara[STK_FONT_Y].length = 2;
	chara[STK_FONT_Y].line[0].length = 3;
	chara[STK_FONT_Y].line[0].point[0].p(5, 5);
	chara[STK_FONT_Y].line[0].point[1].p(15, 20);
	chara[STK_FONT_Y].line[0].point[2].p(25, 5);
	chara[STK_FONT_Y].line[1].length = 2;
	chara[STK_FONT_Y].line[1].point[0].p(15, 20);
	chara[STK_FONT_Y].line[1].point[1].p(15, 45);

	// STK_FONT_Z
	chara[STK_FONT_Z].width = 35;
	chara[STK_FONT_Z].height = 50;
	chara[STK_FONT_Z].length = 1;
	chara[STK_FONT_Z].line[0].length = 4;
	chara[STK_FONT_Z].line[0].point[0].p(5, 5);
	chara[STK_FONT_Z].line[0].point[1].p(35, 5);
	chara[STK_FONT_Z].line[0].point[2].p(5, 45);
	chara[STK_FONT_Z].line[0].point[3].p(35, 45);

	// STK_FONT_1
	chara[STK_FONT_1].width = 15;
	chara[STK_FONT_1].height = 50;
	chara[STK_FONT_1].length = 1;
	chara[STK_FONT_1].line[0].length = 2;
	chara[STK_FONT_1].line[0].point[0].p(10, 5);
	chara[STK_FONT_1].line[0].point[1].p(10, 45);

	// STK_FONT_2
	chara[STK_FONT_2].width = 25;
	chara[STK_FONT_2].height = 50;
	chara[STK_FONT_2].length = 1;
	chara[STK_FONT_2].line[0].length = 8;
	chara[STK_FONT_2].line[0].point[0].p(5, 15);
	chara[STK_FONT_2].line[0].point[1].p(5, 10);
	chara[STK_FONT_2].line[0].point[2].p(10, 5);
	chara[STK_FONT_2].line[0].point[3].p(20, 5);
	chara[STK_FONT_2].line[0].point[4].p(25, 10);
	chara[STK_FONT_2].line[0].point[5].p(25, 20);
	chara[STK_FONT_2].line[0].point[6].p(5, 45);
	chara[STK_FONT_2].line[0].point[7].p(25, 45);

	// STK_FONT_3
	chara[STK_FONT_3].width = 25;
	chara[STK_FONT_3].height = 50;
	chara[STK_FONT_3].length = 1;
	chara[STK_FONT_3].line[0].length = 15;
	chara[STK_FONT_3].line[0].point[0].p(5, 15);
	chara[STK_FONT_3].line[0].point[1].p(5, 10);
	chara[STK_FONT_3].line[0].point[2].p(10, 5);
	chara[STK_FONT_3].line[0].point[3].p(20, 5);
	chara[STK_FONT_3].line[0].point[4].p(25, 10);
	chara[STK_FONT_3].line[0].point[5].p(25, 20);
	chara[STK_FONT_3].line[0].point[6].p(20, 25);
	chara[STK_FONT_3].line[0].point[7].p(10, 25);
	chara[STK_FONT_3].line[0].point[8].p(20, 25);
	chara[STK_FONT_3].line[0].point[9].p(25, 30);
	chara[STK_FONT_3].line[0].point[10].p(25, 40);
	chara[STK_FONT_3].line[0].point[11].p(20, 45);
	chara[STK_FONT_3].line[0].point[12].p(10, 45);
	chara[STK_FONT_3].line[0].point[13].p(5, 40);
	chara[STK_FONT_3].line[0].point[14].p(5, 35);

	// STK_FONT_4
	chara[STK_FONT_4].width = 25;
	chara[STK_FONT_4].height = 50;
	chara[STK_FONT_4].length = 1;
	chara[STK_FONT_4].line[0].length = 4;
	chara[STK_FONT_4].line[0].point[0].p(25, 30);
	chara[STK_FONT_4].line[0].point[1].p(5, 30);
	chara[STK_FONT_4].line[0].point[2].p(20, 5);
	chara[STK_FONT_4].line[0].point[3].p(20, 45);

	// STK_FONT_5
	chara[STK_FONT_5].width = 25;
	chara[STK_FONT_5].height = 50;
	chara[STK_FONT_5].length = 1;
	chara[STK_FONT_5].line[0].length = 10;
	chara[STK_FONT_5].line[0].point[0].p(25, 5);
	chara[STK_FONT_5].line[0].point[1].p(5, 5);
	chara[STK_FONT_5].line[0].point[2].p(5, 25);
	chara[STK_FONT_5].line[0].point[3].p(20, 25);
	chara[STK_FONT_5].line[0].point[4].p(25, 30);
	chara[STK_FONT_5].line[0].point[5].p(25, 40);
	chara[STK_FONT_5].line[0].point[6].p(20, 45);
	chara[STK_FONT_5].line[0].point[7].p(10, 45);
	chara[STK_FONT_5].line[0].point[8].p(5, 40);
	chara[STK_FONT_5].line[0].point[9].p(5, 35);

	// STK_FONT_6
	chara[STK_FONT_6].width = 25;
	chara[STK_FONT_6].height = 50;
	chara[STK_FONT_6].length = 1;
	chara[STK_FONT_6].line[0].length = 12;
	chara[STK_FONT_6].line[0].point[0].p(25, 10);
	chara[STK_FONT_6].line[0].point[1].p(20, 5);
	chara[STK_FONT_6].line[0].point[2].p(10, 5);
	chara[STK_FONT_6].line[0].point[3].p(5, 10);
	chara[STK_FONT_6].line[0].point[4].p(5, 40);
	chara[STK_FONT_6].line[0].point[5].p(10, 45);
	chara[STK_FONT_6].line[0].point[6].p(20, 45);
	chara[STK_FONT_6].line[0].point[7].p(25, 40);
	chara[STK_FONT_6].line[0].point[8].p(25, 30);
	chara[STK_FONT_6].line[0].point[9].p(20, 25);
	chara[STK_FONT_6].line[0].point[10].p(10, 25);
	chara[STK_FONT_6].line[0].point[11].p(5, 30);

	// STK_FONT_7
	chara[STK_FONT_7].width = 25;
	chara[STK_FONT_7].height = 50;
	chara[STK_FONT_7].length = 1;
	chara[STK_FONT_7].line[0].length = 5;
	chara[STK_FONT_7].line[0].point[0].p(5, 15);
	chara[STK_FONT_7].line[0].point[1].p(5, 5);
	chara[STK_FONT_7].line[0].point[2].p(25, 5);
	chara[STK_FONT_7].line[0].point[3].p(25, 20);
	chara[STK_FONT_7].line[0].point[4].p(15, 45);

	// STK_FONT_8
	chara[STK_FONT_8].width = 25;
	chara[STK_FONT_8].height = 50;
	chara[STK_FONT_8].length = 1;
	chara[STK_FONT_8].line[0].length = 16;
	chara[STK_FONT_8].line[0].point[0].p(10, 25);
	chara[STK_FONT_8].line[0].point[1].p(5, 20);
	chara[STK_FONT_8].line[0].point[2].p(5, 10);
	chara[STK_FONT_8].line[0].point[3].p(10, 5);
	chara[STK_FONT_8].line[0].point[4].p(20, 5);
	chara[STK_FONT_8].line[0].point[5].p(25, 10);
	chara[STK_FONT_8].line[0].point[6].p(25, 20);
	chara[STK_FONT_8].line[0].point[7].p(20, 25);
	chara[STK_FONT_8].line[0].point[8].p(25, 30);
	chara[STK_FONT_8].line[0].point[9].p(25, 40);
	chara[STK_FONT_8].line[0].point[10].p(20, 45);
	chara[STK_FONT_8].line[0].point[11].p(10, 45);
	chara[STK_FONT_8].line[0].point[12].p(5, 40);
	chara[STK_FONT_8].line[0].point[13].p(5, 30);
	chara[STK_FONT_8].line[0].point[14].p(10, 25);
	chara[STK_FONT_8].line[0].point[15].p(20, 25);

	// STK_FONT_9
	chara[STK_FONT_9].width = 25;
	chara[STK_FONT_9].height = 50;
	chara[STK_FONT_9].length = 1;
	chara[STK_FONT_9].line[0].length = 12;
	chara[STK_FONT_9].line[0].point[0].p(5, 40);
	chara[STK_FONT_9].line[0].point[1].p(10, 45);
	chara[STK_FONT_9].line[0].point[2].p(20, 45);
	chara[STK_FONT_9].line[0].point[3].p(25, 40);
	chara[STK_FONT_9].line[0].point[4].p(25, 10);
	chara[STK_FONT_9].line[0].point[5].p(20, 5);
	chara[STK_FONT_9].line[0].point[6].p(10, 5);
	chara[STK_FONT_9].line[0].point[7].p(5, 10);
	chara[STK_FONT_9].line[0].point[8].p(5, 20);
	chara[STK_FONT_9].line[0].point[9].p(10, 25);
	chara[STK_FONT_9].line[0].point[10].p(20, 25);
	chara[STK_FONT_9].line[0].point[11].p(25, 20);

	// STK_FONT_0
	chara[STK_FONT_0].width = 25;
	chara[STK_FONT_0].height = 50;
	chara[STK_FONT_0].length = 1;
	chara[STK_FONT_0].line[0].length = 9;
	chara[STK_FONT_0].line[0].point[0].p(5, 10);
	chara[STK_FONT_0].line[0].point[1].p(10, 5);
	chara[STK_FONT_0].line[0].point[2].p(20, 5);
	chara[STK_FONT_0].line[0].point[3].p(25, 10);
	chara[STK_FONT_0].line[0].point[4].p(25, 40);
	chara[STK_FONT_0].line[0].point[5].p(20, 45);
	chara[STK_FONT_0].line[0].point[6].p(10, 45);
	chara[STK_FONT_0].line[0].point[7].p(5, 40);
	chara[STK_FONT_0].line[0].point[8].p(5, 10);

	// STK_FONT_COMMA
	chara[STK_FONT_COMMA].width = 15;
	chara[STK_FONT_COMMA].height = 50;
	chara[STK_FONT_COMMA].length = 1;
	chara[STK_FONT_COMMA].line[0].length = 3;
	chara[STK_FONT_COMMA].line[0].point[0].p(15, 35);
	chara[STK_FONT_COMMA].line[0].point[1].p(15, 40);
	chara[STK_FONT_COMMA].line[0].point[2].p(5, 45);

	// STK_FONT_DOT
	chara[STK_FONT_DOT].width = 10;
	chara[STK_FONT_DOT].height = 50;
	chara[STK_FONT_DOT].length = 1;
	chara[STK_FONT_DOT].line[0].length = 2;
	chara[STK_FONT_DOT].line[0].point[0].p(10, 40);
	chara[STK_FONT_DOT].line[0].point[1].p(10, 45);

	// STK_FONT_SEMICOLON
	chara[STK_FONT_SEMICOLON].width = 15;
	chara[STK_FONT_SEMICOLON].height = 50;
	chara[STK_FONT_SEMICOLON].length = 2;
	chara[STK_FONT_SEMICOLON].line[0].length = 3;
	chara[STK_FONT_SEMICOLON].line[0].point[0].p(15, 35);
	chara[STK_FONT_SEMICOLON].line[0].point[1].p(15, 40);
	chara[STK_FONT_SEMICOLON].line[0].point[2].p(5, 45);
	chara[STK_FONT_SEMICOLON].line[1].length = 2;
	chara[STK_FONT_SEMICOLON].line[1].point[0].p(15, 10);
	chara[STK_FONT_SEMICOLON].line[1].point[1].p(15, 15);

	// STK_FONT_COLON
	chara[STK_FONT_COLON].width = 10;
	chara[STK_FONT_COLON].height = 50;
	chara[STK_FONT_COLON].length = 2;
	chara[STK_FONT_COLON].line[0].length = 2;
	chara[STK_FONT_COLON].line[0].point[0].p(10, 10);
	chara[STK_FONT_COLON].line[0].point[1].p(10, 15);
	chara[STK_FONT_COLON].line[1].length = 2;
	chara[STK_FONT_COLON].line[1].point[0].p(10, 40);
	chara[STK_FONT_COLON].line[1].point[1].p(10, 45);

	// STK_FONT_PLUS
	chara[STK_FONT_PLUS].width = 25;
	chara[STK_FONT_PLUS].height = 50;
	chara[STK_FONT_PLUS].length = 2;
	chara[STK_FONT_PLUS].line[0].length = 2;
	chara[STK_FONT_PLUS].line[0].point[0].p(15, 15);
	chara[STK_FONT_PLUS].line[0].point[1].p(15, 35);
	chara[STK_FONT_PLUS].line[1].length = 2;
	chara[STK_FONT_PLUS].line[1].point[0].p(5, 25);
	chara[STK_FONT_PLUS].line[1].point[1].p(25, 25);

	// STK_FONT_MINUS
	chara[STK_FONT_MINUS].width = 25;
	chara[STK_FONT_MINUS].height = 50;
	chara[STK_FONT_MINUS].length = 1;
	chara[STK_FONT_MINUS].line[0].length = 2;
	chara[STK_FONT_MINUS].line[0].point[0].p(5, 25);
	chara[STK_FONT_MINUS].line[0].point[1].p(25, 25);

	// STK_FONT_MUL
	chara[STK_FONT_MUL].width = 25;
	chara[STK_FONT_MUL].height = 50;
	chara[STK_FONT_MUL].length = 2;
	chara[STK_FONT_MUL].line[0].length = 2;
	chara[STK_FONT_MUL].line[0].point[0].p(5, 15);
	chara[STK_FONT_MUL].line[0].point[1].p(25, 35);
	chara[STK_FONT_MUL].line[1].length = 2;
	chara[STK_FONT_MUL].line[1].point[0].p(25, 15);
	chara[STK_FONT_MUL].line[1].point[1].p(5, 35);

	// STK_FONT_DIV
	chara[STK_FONT_DIV].width = 25;
	chara[STK_FONT_DIV].height = 50;
	chara[STK_FONT_DIV].length = 1;
	chara[STK_FONT_DIV].line[0].length = 2;
	chara[STK_FONT_DIV].line[0].point[0].p(25, 15);
	chara[STK_FONT_DIV].line[0].point[1].p(5, 35);

	// STK_FONT_RBS
	chara[STK_FONT_RBS].width = 20;
	chara[STK_FONT_RBS].height = 50;
	chara[STK_FONT_RBS].length = 1;
	chara[STK_FONT_RBS].line[0].length = 5;
	chara[STK_FONT_RBS].line[0].point[0].p(20, 5);
	chara[STK_FONT_RBS].line[0].point[1].p(10, 10);
	chara[STK_FONT_RBS].line[0].point[2].p(5, 25);
	chara[STK_FONT_RBS].line[0].point[3].p(10, 40);
	chara[STK_FONT_RBS].line[0].point[4].p(20, 45);

	// STK_FONT_RBE
	chara[STK_FONT_RBE].width = 20;
	chara[STK_FONT_RBE].height = 50;
	chara[STK_FONT_RBE].length = 1;
	chara[STK_FONT_RBE].line[0].length = 5;
	chara[STK_FONT_RBE].line[0].point[0].p(5, 5);
	chara[STK_FONT_RBE].line[0].point[1].p(15, 10);
	chara[STK_FONT_RBE].line[0].point[2].p(20, 25);
	chara[STK_FONT_RBE].line[0].point[3].p(15, 40);
	chara[STK_FONT_RBE].line[0].point[4].p(5, 45);

	// STK_FONT_QES
	chara[STK_FONT_QES].width = 25;
	chara[STK_FONT_QES].height = 50;
	chara[STK_FONT_QES].length = 2;
	chara[STK_FONT_QES].line[0].length = 9;
	chara[STK_FONT_QES].line[0].point[0].p(5, 15);
	chara[STK_FONT_QES].line[0].point[1].p(5, 10);
	chara[STK_FONT_QES].line[0].point[2].p(10, 5);
	chara[STK_FONT_QES].line[0].point[3].p(20, 5);
	chara[STK_FONT_QES].line[0].point[4].p(25, 10);
	chara[STK_FONT_QES].line[0].point[5].p(25, 20);
	chara[STK_FONT_QES].line[0].point[6].p(20, 25);
	chara[STK_FONT_QES].line[0].point[7].p(15, 25);
	chara[STK_FONT_QES].line[0].point[8].p(15, 35);
	chara[STK_FONT_QES].line[1].length = 2;
	chara[STK_FONT_QES].line[1].point[0].p(15, 40);
	chara[STK_FONT_QES].line[1].point[1].p(15, 45);

	// STK_FONT_SPACE
	chara[STK_FONT_SPACE].width = 15;
	chara[STK_FONT_SPACE].height = 50;
	chara[STK_FONT_SPACE].length = 0;

	// STK_FONT_AT
	chara[STK_FONT_AT].width = 35;
	chara[STK_FONT_AT].height = 50;
	chara[STK_FONT_AT].length = 1;
	chara[STK_FONT_AT].line[0].length = 15;
	chara[STK_FONT_AT].line[0].point[0].p(30, 35);
	chara[STK_FONT_AT].line[0].point[1].p(20, 35);
	chara[STK_FONT_AT].line[0].point[2].p(15, 30);
	chara[STK_FONT_AT].line[0].point[3].p(15, 20);
	chara[STK_FONT_AT].line[0].point[4].p(20, 15);
	chara[STK_FONT_AT].line[0].point[5].p(30, 15);
	chara[STK_FONT_AT].line[0].point[6].p(30, 35);
	chara[STK_FONT_AT].line[0].point[7].p(35, 35);
	chara[STK_FONT_AT].line[0].point[8].p(35, 10);
	chara[STK_FONT_AT].line[0].point[9].p(30, 5);
	chara[STK_FONT_AT].line[0].point[10].p(15, 5);
	chara[STK_FONT_AT].line[0].point[11].p(5, 15);
	chara[STK_FONT_AT].line[0].point[12].p(5, 35);
	chara[STK_FONT_AT].line[0].point[13].p(15, 45);
	chara[STK_FONT_AT].line[0].point[14].p(35, 45);

	// STK_FONT_AND
	chara[STK_FONT_AND].width = 25;
	chara[STK_FONT_AND].height = 50;
	chara[STK_FONT_AND].length = 1;
	chara[STK_FONT_AND].line[0].length = 10;
	chara[STK_FONT_AND].line[0].point[0].p(25, 45);
	chara[STK_FONT_AND].line[0].point[1].p(5, 10);
	chara[STK_FONT_AND].line[0].point[2].p(10, 5);
	chara[STK_FONT_AND].line[0].point[3].p(15, 5);
	chara[STK_FONT_AND].line[0].point[4].p(20, 10);
	chara[STK_FONT_AND].line[0].point[5].p(20, 15);
	chara[STK_FONT_AND].line[0].point[6].p(5, 30);
	chara[STK_FONT_AND].line[0].point[7].p(5, 40);
	chara[STK_FONT_AND].line[0].point[8].p(10, 45);
	chara[STK_FONT_AND].line[0].point[9].p(25, 35);

	// STK_FONT_OC
	chara[STK_FONT_OC].width = 35;
	chara[STK_FONT_OC].height = 50;
	chara[STK_FONT_OC].length = 2;
	chara[STK_FONT_OC].line[0].length = 9;
	chara[STK_FONT_OC].line[0].point[0].p(10, 10);
	chara[STK_FONT_OC].line[0].point[1].p(30, 10);
	chara[STK_FONT_OC].line[0].point[2].p(35, 15);
	chara[STK_FONT_OC].line[0].point[3].p(35, 40);
	chara[STK_FONT_OC].line[0].point[4].p(30, 45);
	chara[STK_FONT_OC].line[0].point[5].p(10, 45);
	chara[STK_FONT_OC].line[0].point[6].p(5, 40);
	chara[STK_FONT_OC].line[0].point[7].p(5, 15);
	chara[STK_FONT_OC].line[0].point[8].p(10, 10);
	chara[STK_FONT_OC].line[1].length = 8;
	chara[STK_FONT_OC].line[1].point[0].p(30, 20);
	chara[STK_FONT_OC].line[1].point[1].p(25, 15);
	chara[STK_FONT_OC].line[1].point[2].p(15, 15);
	chara[STK_FONT_OC].line[1].point[3].p(10, 20);
	chara[STK_FONT_OC].line[1].point[4].p(10, 35);
	chara[STK_FONT_OC].line[1].point[5].p(15, 40);
	chara[STK_FONT_OC].line[1].point[6].p(25, 40);
	chara[STK_FONT_OC].line[1].point[7].p(30, 35);

	// STK_FONT_NEKO
	chara[STK_FONT_NEKO].width = 35;
	chara[STK_FONT_NEKO].height = 50;
	chara[STK_FONT_NEKO].length = 4;
	chara[STK_FONT_NEKO].line[0].length = 11;
	chara[STK_FONT_NEKO].line[0].point[0].p(5, 25);
	chara[STK_FONT_NEKO].line[0].point[1].p(10, 10);
	chara[STK_FONT_NEKO].line[0].point[2].p(15, 20);
	chara[STK_FONT_NEKO].line[0].point[3].p(25, 20);
	chara[STK_FONT_NEKO].line[0].point[4].p(30, 10);
	chara[STK_FONT_NEKO].line[0].point[5].p(35, 25);
	chara[STK_FONT_NEKO].line[0].point[6].p(35, 40);
	chara[STK_FONT_NEKO].line[0].point[7].p(30, 45);
	chara[STK_FONT_NEKO].line[0].point[8].p(10, 45);
	chara[STK_FONT_NEKO].line[0].point[9].p(5, 40);
	chara[STK_FONT_NEKO].line[0].point[10].p(5, 25);
	chara[STK_FONT_NEKO].line[1].length = 2;
	chara[STK_FONT_NEKO].line[1].point[0].p(10, 30);
	chara[STK_FONT_NEKO].line[1].point[1].p(10, 35);
	chara[STK_FONT_NEKO].line[2].length = 2;
	chara[STK_FONT_NEKO].line[2].point[0].p(30, 30);
	chara[STK_FONT_NEKO].line[2].point[1].p(30, 35);
	chara[STK_FONT_NEKO].line[3].length = 7;
	chara[STK_FONT_NEKO].line[3].point[0].p(10, 40);
	chara[STK_FONT_NEKO].line[3].point[1].p(15, 45);
	chara[STK_FONT_NEKO].line[3].point[2].p(20, 40);
	chara[STK_FONT_NEKO].line[3].point[3].p(20, 35);
	chara[STK_FONT_NEKO].line[3].point[4].p(20, 40);
	chara[STK_FONT_NEKO].line[3].point[5].p(25, 45);
	chara[STK_FONT_NEKO].line[3].point[6].p(30, 40);

	// STK_FONT_EMPTY
	chara[STK_FONT_EMPTY].width = 0;
	chara[STK_FONT_EMPTY].height = 50;
	chara[STK_FONT_EMPTY].length = 0;

	TinyArialFontHndl = CreateFont(10, 3, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	SmallArialFontHndl = CreateFont(17, 5, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	MediumArialFontHndl = CreateFont(33, 10, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
	LargeArialFontHndl = CreateFont(66, 20, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));

	disp_offset = 0;
	disp_end = 0;
	rgst_offset = 0;
	LastScrollTextOutTime = 0;
}

StkFont::~StkFont()
{

}

StkFont* StkFont::GetInstance()
{
	static int init = 1;
	static StkFont *f;
	if (init == 1) {
		f = new StkFont();
		init = 0;
	}
	return f;
}

void StkFont::DrawChara(HDC hdc, int index, int ox, int oy, float mx, float my)
{
	int i, j;
	POINT p[STK_FONT_MAX_POINT];

	for (i = 0; i < chara[index].length; i++) {
		for (j = 0; j < chara[index].line[i].length; j++) {
			p[j].x = ox + int(chara[index].line[i].point[j].x * mx);
			p[j].y = oy + int(chara[index].line[i].point[j].y * my);
		}
		p[j].x = ox + int(chara[index].line[i].point[j - 2].x * mx);
		p[j].y = oy + int(chara[index].line[i].point[j - 2].y * my);
		Polyline(hdc, p, j + 1);
	}
}

void StkFont::StkFontTinyTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c)
{
	StkFontTextOut(hdc, x, y, 0.12f, 0.12f, 12, str, c);
}

void StkFont::StkFontSmallTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c)
{
	StkFontTextOut(hdc, x, y, 0.2f, 0.2f, 8, str, c);
}

void StkFont::StkFontMediumTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c)
{
	StkFontTextOut(hdc, x, y, 0.4f, 0.4f, 3, str, c);
}

void StkFont::StkFontLargeTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c)
{
	StkFontTextOut(hdc, x, y, 1.0f, 1.0f, 0, str, c);
}

void StkFont::StkFontTextOut(HDC hdc, int x, int y, float mx, float my, int space, LPCTSTR ostr, COLORREF c)
{
	int index;

	TCHAR str[512];
	lstrcpy(str, ostr);
	CharUpper(str);
	int length = lstrlen(str);
	int ox = x;

	HPEN pen = CreatePen(PS_SOLID, 1, c);
	SelectObject(hdc, pen);
	for (int i = 0; i < length; i++) {
		TCHAR a = str[i];
		switch (a) {
		case 'A':
			index = STK_FONT_A;
			break;
		case 'B':
			index = STK_FONT_B;
			break;
		case 'C':
			index = STK_FONT_C;
			break;
		case 'D':
			index = STK_FONT_D;
			break;
		case 'E':
			index = STK_FONT_E;
			break;
		case 'F':
			index = STK_FONT_F;
			break;
		case 'G':
			index = STK_FONT_G;
			break;
		case 'H':
			index = STK_FONT_H;
			break;
		case 'I':
			index = STK_FONT_I;
			break;
		case 'J':
			index = STK_FONT_J;
			break;
		case 'K':
			index = STK_FONT_K;
			break;
		case 'L':
			index = STK_FONT_L;
			break;
		case 'M':
			index = STK_FONT_M;
			break;
		case 'N':
			index = STK_FONT_N;
			break;
		case 'O':
			index = STK_FONT_O;
			break;
		case 'P':
			index = STK_FONT_P;
			break;
		case 'Q':
			index = STK_FONT_Q;
			break;
		case 'R':
			index = STK_FONT_R;
			break;
		case 'S':
			index = STK_FONT_S;
			break;
		case 'T':
			index = STK_FONT_T;
			break;
		case 'U':
			index = STK_FONT_U;
			break;
		case 'V':
			index = STK_FONT_V;
			break;
		case 'W':
			index = STK_FONT_W;
			break;
		case 'X':
			index = STK_FONT_X;
			break;
		case 'Y':
			index = STK_FONT_Y;
			break;
		case 'Z':
			index = STK_FONT_Z;
			break;
		case '0':
			index = STK_FONT_0;
			break;
		case '1':
			index = STK_FONT_1;
			break;
		case '2':
			index = STK_FONT_2;
			break;
		case '3':
			index = STK_FONT_3;
			break;
		case '4':
			index = STK_FONT_4;
			break;
		case '5':
			index = STK_FONT_5;
			break;
		case '6':
			index = STK_FONT_6;
			break;
		case '7':
			index = STK_FONT_7;
			break;
		case '8':
			index = STK_FONT_8;
			break;
		case '9':
			index = STK_FONT_9;
			break;
		case ',':
			index = STK_FONT_COMMA;
			break;
		case '.':
			index = STK_FONT_DOT;
			break;
		case ':':
			index = STK_FONT_COLON;
			break;
		case ';':
			index = STK_FONT_SEMICOLON;
			break;
		case '+':
			index = STK_FONT_PLUS;
			break;
		case '-':
			index = STK_FONT_MINUS;
			break;
		case '*':
			index = STK_FONT_MUL;
			break;
		case '/':
			index = STK_FONT_DIV;
			break;
		case '(':
			index = STK_FONT_RBS;
			break;
		case ')':
			index = STK_FONT_RBE;
			break;
		case '?':
			index = STK_FONT_QES;
			break;
		case '@':
			index = STK_FONT_AT;
			break;
		case '&':
			index = STK_FONT_AND;
			break;
		case '!':
			index = STK_FONT_NEKO;
			break;
		case '^':
			index = STK_FONT_OC;
			break;
		case ' ':
			index = STK_FONT_SPACE;
			break;
		case '\n':
			x = ox;
			y += int(chara[STK_FONT_EMPTY].height * my);
			index = STK_FONT_EMPTY;
			break;
		default:
			index = STK_FONT_SPACE;
			break;
		}
		if (index != STK_FONT_EMPTY) {
			DrawChara(hdc, index, x, y, mx, my);
			x += int((chara[index].width + space) * mx);
		}
	}
	DeleteObject(pen);
}

void StkFont::ArialFontTinyTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c, BOOL Cen)
{
	HFONT PrevFontHndl = (HFONT)SelectObject(hdc, TinyArialFontHndl);
	if (Cen) {
		SIZE Sze;
		GetTextExtentPoint32(hdc, str, lstrlen(str), &Sze);
		x = x - Sze.cx / 2;
		y = y - Sze.cy / 2;
	}
	ArialFontTextOut(hdc, x, y, str, c);
	SelectObject(hdc, PrevFontHndl);
}

void StkFont::ArialFontSmallTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c, BOOL Cen)
{
	HFONT PrevFontHndl = (HFONT)SelectObject(hdc, SmallArialFontHndl);
	if (Cen) {
		SIZE Sze;
		GetTextExtentPoint32(hdc, str, lstrlen(str), &Sze);
		x = x - Sze.cx / 2;
		y = y - Sze.cy / 2;
	}
	ArialFontTextOut(hdc, x, y, str, c);
	SelectObject(hdc, PrevFontHndl);
}

void StkFont::ArialFontMediumTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c, BOOL Cen)
{
	HFONT PrevFontHndl = (HFONT)SelectObject(hdc, MediumArialFontHndl);
	if (Cen) {
		SIZE Sze;
		GetTextExtentPoint32(hdc, str, lstrlen(str), &Sze);
		x = x - Sze.cx / 2;
		y = y - Sze.cy / 2;
	}
	ArialFontTextOut(hdc, x, y, str, c);
	SelectObject(hdc, PrevFontHndl);
}

void StkFont::ArialFontLargeTextOut(HDC hdc, int x, int y, LPCTSTR str, COLORREF c, BOOL Cen)
{
	HFONT PrevFontHndl = (HFONT)SelectObject(hdc, LargeArialFontHndl);
	if (Cen) {
		SIZE Sze;
		GetTextExtentPoint32(hdc, str, lstrlen(str), &Sze);
		x = x - Sze.cx / 2;
		y = y - Sze.cy / 2;
	}
	ArialFontTextOut(hdc, x, y, str, c);
	SelectObject(hdc, PrevFontHndl);
}

void StkFont::ArialFontTextOut(HDC hdc, int x, int y, LPCTSTR ostr, COLORREF c)
{
	SetTextColor(hdc, c);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, x, y, (LPCTSTR)ostr, lstrlen((LPCTSTR)ostr));
}

void StkFont::StkFontClearScrollText()
{
	disp_offset = 0;
	disp_end = 0;
	rgst_offset = 0;
	LastScrollTextOutTime = 0;
}

void StkFont::StkFontAddScrollText(LPTSTR str)
{
	if (rgst_offset < 256 && str != NULL) {
		lstrcpy(ScrollText[rgst_offset], str);
		rgst_offset++;
	}
}

void StkFont::StkFontScrollTextOut(HDC hdc, int x, int y, int length, COLORREF c)
{
	if (hdc != NULL && length > 1) {
		if (disp_end == disp_offset + length) {
			disp_end = rgst_offset;
		}
		int l = 0;
		for (int i = disp_offset; i < disp_offset + length; i++) {
			if (i < disp_end) {
				StkFontSmallTextOut(hdc, x, y + l * 10, ScrollText[i], c);
				l++;
			}
		}

		DWORD CurrentTime = GetTickCount();
		if (CurrentTime - LastScrollTextOutTime > 50) {
			LastScrollTextOutTime = CurrentTime;
			if (disp_end < rgst_offset && disp_end < disp_offset + length) {
				disp_end++;
				return;
			}
			if (disp_offset < rgst_offset - length) {
				disp_offset++;
			}
		}
	}
}

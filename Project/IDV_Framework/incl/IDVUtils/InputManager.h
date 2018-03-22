#ifndef IDV_INPUT_MANAGER_H
#define IDV_INPUT_MANAGER_H

#include <SDL/SDL_keysym.h>


enum STDKEYS {
	T800K_UNKNOWN = 0,
	T800K_FIRST = 0,
	T800K_BACKSPACE = 8,
	T800K_TAB = 9,
	T800K_CLEAR = 12,
	T800K_RETURN = 13,
	T800K_PAUSE = 19,
	T800K_ESCAPE = 27,
	T800K_SPACE = 32,
	T800K_EXCLAIM = 33,
	T800K_QUOTEDBL = 34,
	T800K_HASH = 35,
	T800K_DOLLAR = 36,
	T800K_AMPERSAND = 38,
	T800K_QUOTE = 39,
	T800K_LEFTPAREN = 40,
	T800K_RIGHTPAREN = 41,
	T800K_ASTERISK = 42,
	T800K_PLUS = 43,
	T800K_COMMA = 44,
	T800K_MINUS = 45,
	T800K_PERIOD = 46,
	T800K_SLASH = 47,
	T800K_0 = 48,
	T800K_1 = 49,
	T800K_2 = 50,
	T800K_3 = 51,
	T800K_4 = 52,
	T800K_5 = 53,
	T800K_6 = 54,
	T800K_7 = 55,
	T800K_8 = 56,
	T800K_9 = 57,
	T800K_COLON = 58,
	T800K_SEMICOLON = 59,
	T800K_LESS = 60,
	T800K_EQUALS = 61,
	T800K_GREATER = 62,
	T800K_QUESTION = 63,
	T800K_AT = 64,
	T800K_LEFTBRACKET = 91,
	T800K_BACKSLASH = 92,
	T800K_RIGHTBRACKET = 93,
	T800K_CARET = 94,
	T800K_UNDERSCORE = 95,
	T800K_BACKQUOTE = 96,
	T800K_a = 97,
	T800K_b = 98,
	T800K_c = 99,
	T800K_d = 100,
	T800K_e = 101,
	T800K_f = 102,
	T800K_g = 103,
	T800K_h = 104,
	T800K_i = 105,
	T800K_j = 106,
	T800K_k = 107,
	T800K_l = 108,
	T800K_m = 109,
	T800K_n = 110,
	T800K_o = 111,
	T800K_p = 112,
	T800K_q = 113,
	T800K_r = 114,
	T800K_s = 115,
	T800K_t = 116,
	T800K_u = 117,
	T800K_v = 118,
	T800K_w = 119,
	T800K_x = 120,
	T800K_y = 121,
	T800K_z = 122,
	T800K_DELETE = 127,
	T800K_WORLD_0 = 160,
	T800K_WORLD_1 = 161,
	T800K_WORLD_2 = 162,
	T800K_WORLD_3 = 163,
	T800K_WORLD_4 = 164,
	T800K_WORLD_5 = 165,
	T800K_WORLD_6 = 166,
	T800K_WORLD_7 = 167,
	T800K_WORLD_8 = 168,
	T800K_WORLD_9 = 169,
	T800K_WORLD_10 = 170,
	T800K_WORLD_11 = 171,
	T800K_WORLD_12 = 172,
	T800K_WORLD_13 = 173,
	T800K_WORLD_14 = 174,
	T800K_WORLD_15 = 175,
	T800K_WORLD_16 = 176,
	T800K_WORLD_17 = 177,
	T800K_WORLD_18 = 178,
	T800K_WORLD_19 = 179,
	T800K_WORLD_20 = 180,
	T800K_WORLD_21 = 181,
	T800K_WORLD_22 = 182,
	T800K_WORLD_23 = 183,
	T800K_WORLD_24 = 184,
	T800K_WORLD_25 = 185,
	T800K_WORLD_26 = 186,
	T800K_WORLD_27 = 187,
	T800K_WORLD_28 = 188,
	T800K_WORLD_29 = 189,
	T800K_WORLD_30 = 190,
	T800K_WORLD_31 = 191,
	T800K_WORLD_32 = 192,
	T800K_WORLD_33 = 193,
	T800K_WORLD_34 = 194,
	T800K_WORLD_35 = 195,
	T800K_WORLD_36 = 196,
	T800K_WORLD_37 = 197,
	T800K_WORLD_38 = 198,
	T800K_WORLD_39 = 199,
	T800K_WORLD_40 = 200,
	T800K_WORLD_41 = 201,
	T800K_WORLD_42 = 202,
	T800K_WORLD_43 = 203,
	T800K_WORLD_44 = 204,
	T800K_WORLD_45 = 205,
	T800K_WORLD_46 = 206,
	T800K_WORLD_47 = 207,
	T800K_WORLD_48 = 208,
	T800K_WORLD_49 = 209,
	T800K_WORLD_50 = 210,
	T800K_WORLD_51 = 211,
	T800K_WORLD_52 = 212,
	T800K_WORLD_53 = 213,
	T800K_WORLD_54 = 214,
	T800K_WORLD_55 = 215,
	T800K_WORLD_56 = 216,
	T800K_WORLD_57 = 217,
	T800K_WORLD_58 = 218,
	T800K_WORLD_59 = 219,
	T800K_WORLD_60 = 220,
	T800K_WORLD_61 = 221,
	T800K_WORLD_62 = 222,
	T800K_WORLD_63 = 223,
	T800K_WORLD_64 = 224,
	T800K_WORLD_65 = 225,
	T800K_WORLD_66 = 226,
	T800K_WORLD_67 = 227,
	T800K_WORLD_68 = 228,
	T800K_WORLD_69 = 229,
	T800K_WORLD_70 = 230,
	T800K_WORLD_71 = 231,
	T800K_WORLD_72 = 232,
	T800K_WORLD_73 = 233,
	T800K_WORLD_74 = 234,
	T800K_WORLD_75 = 235,
	T800K_WORLD_76 = 236,
	T800K_WORLD_77 = 237,
	T800K_WORLD_78 = 238,
	T800K_WORLD_79 = 239,
	T800K_WORLD_80 = 240,
	T800K_WORLD_81 = 241,
	T800K_WORLD_82 = 242,
	T800K_WORLD_83 = 243,
	T800K_WORLD_84 = 244,
	T800K_WORLD_85 = 245,
	T800K_WORLD_86 = 246,
	T800K_WORLD_87 = 247,
	T800K_WORLD_88 = 248,
	T800K_WORLD_89 = 249,
	T800K_WORLD_90 = 250,
	T800K_WORLD_91 = 251,
	T800K_WORLD_92 = 252,
	T800K_WORLD_93 = 253,
	T800K_WORLD_94 = 254,
	T800K_WORLD_95 = 255,
	T800K_KP0 = 256,
	T800K_KP1 = 257,
	T800K_KP2 = 258,
	T800K_KP3 = 259,
	T800K_KP4 = 260,
	T800K_KP5 = 261,
	T800K_KP6 = 262,
	T800K_KP7 = 263,
	T800K_KP8 = 264,
	T800K_KP9 = 265,
	T800K_KP_PERIOD = 266,
	T800K_KP_DIVIDE = 267,
	T800K_KP_MULTIPLY = 268,
	T800K_KP_MINUS = 269,
	T800K_KP_PLUS = 270,
	T800K_KP_ENTER = 271,
	T800K_KP_EQUALS = 272,

	T800K_UP = 273,
	T800K_DOWN = 274,
	T800K_RIGHT = 275,
	T800K_LEFT = 276,
	T800K_INSERT = 277,
	T800K_HOME = 278,
	T800K_END = 279,
	T800K_PAGEUP = 280,
	T800K_PAGEDOWN = 281,

	T800K_F1 = 282,
	T800K_F2 = 283,
	T800K_F3 = 284,
	T800K_F4 = 285,
	T800K_F5 = 286,
	T800K_F6 = 287,
	T800K_F7 = 288,
	T800K_F8 = 289,
	T800K_F9 = 290,
	T800K_F10 = 291,
	T800K_F11 = 292,
	T800K_F12 = 293,
	T800K_F13 = 294,
	T800K_F14 = 295,
	T800K_F15 = 296,

	T800K_NUMLOCK = 300,
	T800K_CAPSLOCK = 301,
	T800K_SCROLLOCK = 302,
	T800K_RSHIFT = 303,
	T800K_LSHIFT = 304,
	T800K_RCTRL = 305,
	T800K_LCTRL = 306,
	T800K_RALT = 307,
	T800K_LALT = 308,
	T800K_RMETA = 309,
	T800K_LMETA = 310,
	T800K_LSUPER = 311,
	T800K_RSUPER = 312,
	T800K_MODE = 313,
	T800K_COMPOSE = 314,

	T800K_HELP = 315,
	T800K_PRINT = 316,
	T800K_SYSREQ = 317,
	T800K_BREAK = 318,
	T800K_MENU = 319,
	T800K_POWER = 320,
	T800K_EURO = 321,
	T800K_UNDO = 322,
	T800K_LAST
};

#define MAXKEYS 512
#define MAXMOUSEBUTTONS 5


class InputManager {
public:
	InputManager();
	bool	PressedOnceKey(int key);
	bool	PressedOnceMouseButton(int mb);

	bool	PressedKey(int key);
	bool	PressedMouseButton(int mb);

	bool	KeyStates[2][MAXKEYS];
	bool	MouseButtonStates[2][MAXMOUSEBUTTONS];

	int		xDelta;
	int 	yDelta;
};

#endif
#pragma once

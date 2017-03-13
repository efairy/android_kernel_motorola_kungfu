/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef _CUST_BATTERY_METER_TABLE_H
#define _CUST_BATTERY_METER_TABLE_H

#define BAT_NTC_10 1
#define BAT_NTC_47 0

#if (BAT_NTC_10 == 1)
#define RBAT_PULL_UP_R             16900
#endif

#if (BAT_NTC_47 == 1)
#define RBAT_PULL_UP_R             61900
#endif

#define RBAT_PULL_UP_VOLT          1800

typedef struct _BATTERY_PROFILE_STRUCT {
	signed int percentage;
	signed int voltage;
} BATTERY_PROFILE_STRUCT, *BATTERY_PROFILE_STRUCT_P;

typedef struct _R_PROFILE_STRUCT {
	signed int resistance;
	signed int voltage;
} R_PROFILE_STRUCT, *R_PROFILE_STRUCT_P;

typedef enum {
	T1_0C,
	T2_25C,
	T3_50C
} PROFILE_TEMPERATURE;

#if (BAT_NTC_10 == 1)
BATT_TEMPERATURE Batt_Temperature_Table[] = {
	{-20, 68237},
	{-15, 53650},
	{-10, 42506},
	{ -5, 33892},
	{  0, 27219},
	{  5, 22021},
	{ 10, 17926},
	{ 15, 14674},
	{ 20, 12081},
	{ 25, 10000},
	{ 30, 8315},
	{ 35, 6948},
	{ 40, 5834},
	{ 45, 4917},
	{ 50, 4161},
	{ 55, 3535},
	{ 60, 3014}
};
#endif

#if (BAT_NTC_47 == 1)
	BATT_TEMPERATURE Batt_Temperature_Table[] = {
	{-20, 483954},
	{-15, 360850},
	{-10, 271697},
	{ -5, 206463},
	{  0, 158214},
	{  5, 122259},
	{ 10, 95227},
	{ 15, 74730},
	{ 20, 59065},
	{ 25, 47000},
	{ 30, 37643},
	{ 35, 30334},
	{ 40, 24591},
	{ 45, 20048},
	{ 50, 16433},
	{ 55, 13539},
	{ 60, 11210}
	};
#endif

/* T0 -10C */
BATTERY_PROFILE_STRUCT battery_profile_t0[] = {
	{0,	4384},	
	{1,	4375},	
	{2,	4359},	
	{3,	4344},	
	{4,	4330},	
	{5,	4316},	
	{6,	4302},	
	{7,	4290},	
	{8,	4278},	
	{9,	4266},	
	{10,	4255},	
	{11,	4243},	
	{12,	4231},	
	{13,	4219},	
	{14,	4208},	
	{15,	4197},	
	{16,	4186},	
	{17,	4175},	
	{18,	4165},	
	{19,	4153},	
	{20,	4142},	
	{21,	4131},	
	{22,	4121},	
	{23,	4108},	
	{24,	4100},	
	{25,	4092},	
	{26,	4084},	
	{27,	4076},	
	{28,	4064},	
	{29,	4048},	
	{30,	4027},	
	{31,	4006},	
	{32,	3989},	
	{33,	3974},	
	{34,	3962},	
	{35,	3952},	
	{36,	3943},	
	{37,	3935},	
	{38,	3929},	
	{39,	3922},	
	{40,	3916},	
	{41,	3909},	
	{42,	3902},	
	{43,	3894},	
	{44,	3888},	
	{45,	3880},	
	{46,	3874},	
	{47,	3867},	
	{48,	3862},	
	{49,	3855},	
	{50,	3850},	
	{51,	3844},	
	{52,	3838},	
	{53,	3833},	
	{54,	3828},	
	{55,	3824},	
	{56,	3819},	
	{57,	3815},	
	{58,	3811},	
	{59,	3806},	
	{60,	3803},	
	{61,	3800},	
	{62,	3797},	
	{63,	3794},	
	{64,	3792},	
	{65,	3790},	
	{66,	3789},	
	{67,	3787},	
	{68,	3786},	
	{69,	3784},	
	{70,	3783},	
	{71,	3781},	
	{72,	3780},	
	{73,	3779},	
	{74,	3776},	
	{75,	3774},	
	{76,	3772},	
	{77,	3769},	
	{78,	3767},	
	{79,	3764},	
	{80,	3760},	
	{81,	3756},	
	{82,	3752},	
	{83,	3747},	
	{84,	3742},	
	{85,	3737},	
	{86,	3730},	
	{87,	3723},	
	{88,	3717},
	{89,	3711},
	{90,	3707},
	{91,	3702},
	{92,	3699},
	{93,	3696},
	{94,	3692},
	{95,	3687},
	{96,	3676},
	{97,	3651},
	{98,	3609},
	{99,	3549},
	{100,   3461},
	{101,	3333}
};





/* T1 0C */
BATTERY_PROFILE_STRUCT battery_profile_t1[] = {
{0,		4387},
{1,		4372},
{2,		4358},
{3,		4343},
{4,		4330},
{5,		4318},
{6,		4304},
{7,		4292},
{8,		4281},
{9,		4269},
{10,	4257},
{11,	4246},
{12,	4234},
{13,	4222},
{14,	4211},
{15,	4200},
{16,	4188},
{17,	4178},
{18,	4167},
{19,	4156},
{20,	4145},
{21,	4134},
{22,	4123},
{23,	4111},
{24,	4102},
{25,	4093},
{26,	4085},
{27,	4080},
{28,	4072},
{29,	4059},
{30,	4040},
{31,	4018},
{32,	4000},
{33,	3987},
{34,	3977},
{35,	3968},
{36,	3960},
{37,	3954},
{38,	3948},
{39,	3942},
{40,	3934},
{41,	3924},
{42,	3916},
{43,	3906},
{44,	3897},
{45,	3889},
{46,	3880},
{47,	3873},
{48,	3866},
{49,	3859},
{50,	3854},
{51,	3847},
{52,	3842},
{53,	3837},
{54,	3832},
{55,	3828},
{56,	3824},
{57,	3819},
{58,	3816},
{59,	3812},
{60,	3808},
{61,	3805},
{62,	3801},
{63,	3798},
{64,	3795},
{65,	3793},
{66,	3790},
{67,	3788},
{68,	3786},
{69,	3785},
{70,	3783},
{71,	3782},
{72,	3781},
{73,	3780},
{74,	3779},
{75,	3776},
{76,	3774},
{77,	3772},
{78,	3768},
{79,	3765},
{80,	3762},
{81,	3758},
{82,	3754},
{83,	3748},
{84,	3743},
{85,	3736},
{86,	3731},
{87,	3725},
{88,	3717},
{89,	3709},
{90,	3704},
{91,	3701},
{92,	3699},
{93,	3697},
{94,	3694},
{95,	3689},
{96,	3676},
{97,	3642},
{98,	3589},
{99,	3516},
{100,	3410},
{100,	3198}
};





/* T2 25C */
BATTERY_PROFILE_STRUCT battery_profile_t2[] = {
{0,		4386},
{1,		4370},
{2,		4357},
{3,		4346},
{4,		4333},
{5,		4320},
{6,		4307},
{7,		4295},
{8,		4283},
{9,		4270},
{10,	4258},
{11,	4246},
{12,	4234},
{13,	4223},
{14,	4211},
{15,	4200},
{16,	4188},
{17,	4177},
{18,	4165},
{19,	4154},
{20,	4143},
{21,	4133},
{22,	4121},
{23,	4110},
{24,	4099},
{25,	4088},
{26,	4078},
{27,	4071},
{28,	4066},
{29,	4056},
{30,	4040},
{31,	4023},
{32,	4009},
{33,	3997},
{34,	3990},
{35,	3984},
{36,	3980},
{37,	3973},
{38,	3965},
{39,	3957},
{40,	3949},
{41,	3940},
{42,	3930},
{43,	3920},
{44,	3907},
{45,	3894},
{46,	3884},
{47,	3875},
{48,	3868},
{49,	3862},
{50,	3855},
{51,	3849},
{52,	3844},
{53,	3839},
{54,	3835},
{55,	3831},
{56,	3826},
{57,	3822},
{58,	3818},
{59,	3814},
{60,	3810},
{61,	3806},
{62,	3805},
{63,	3801},
{64,	3798},
{65,	3795},
{66,	3793},
{67,	3790},
{68,	3787},
{69,	3785},
{70,	3782},
{71,	3781},
{72,	3777},
{73,	3773},
{74,	3770},
{75,	3767},
{76,	3764},
{77,	3759},
{78,	3754},
{79,	3751},
{80,	3748},
{81,	3745},
{82,	3741},
{83,	3737},
{84,	3731},
{85,	3725},
{86,	3721},
{87,	3715},
{88,	3707},
{89,	3698},
{90,	3694},
{91,	3692},
{92,	3692},
{93,	3690},
{94,	3689},
{95,	3685},
{96,	3675},
{97,	3640},
{98,	3591},
{99,	3525},
{100,	3433},
{100,	3271}
};





/* T3 50C */
BATTERY_PROFILE_STRUCT battery_profile_t3[] = {
{0,	    4386},
{1,	    4361},
{2,	    4347},
{3,	    4335},
{4,	    4323},
{5,	    4310},
{6,	    4298},
{7,	    4286},
{8,	    4275},
{9,	    4262},
{10,	4250},
{11,	4239},
{12,	4226},
{13,	4214},
{14,	4203},
{15,	4191},
{16,	4179},
{17,	4169},
{18,	4156},
{19,	4146},
{20,	4134},
{21,	4123},
{22,	4112},
{23,	4101},
{24,	4090},
{25,	4079},
{26,	4069},
{27,	4059},
{28,	4049},
{29,	4039},
{30,	4029},
{31,	4020},
{32,	4010},
{33,	4001},
{34,	3992},
{35,	3984},
{36,	3975},
{37,	3967},
{38,	3958},
{39,	3950},
{40,	3942},
{41,	3934},
{42,	3924},
{44,	3911},
{45,	3897},
{46,	3885},
{47,	3876},
{48,	3869},
{49,	3862},
{50,	3857},
{51,	3851},
{52,	3845},
{53,	3839},
{54,	3834},
{55,	3830},
{56,	3825},
{57,	3821},
{58,	3816},
{59,	3813},
{60,	3808},
{61,	3804},
{62,	3801},
{63,	3797},
{64,	3794},
{65,	3791},
{66,	3788},
{67,	3786},
{68,	3783},
{69,	3780},
{70,	3778},
{71,	3774},
{72,	3767},
{73,	3759},
{74,	3753},
{75,	3749},
{76,	3744},
{77,	3741},
{78,	3736},
{79,	3733},
{80,	3728},
{81,	3725},
{82,	3722},
{83,	3718},
{84,	3713},
{85,	3707},
{86,	3701},
{87,	3695},
{88,	3688},
{89,	3680},
{90,	3677},
{91,	3677},
{92,	3676},
{93,	3675},
{94,	3672},
{95,	3668},
{96,	3648},
{97,	3608},
{98,	3556},
{99,	3486},
{100,	3385},
{100,	3194},
{100,	3194}
};





/* battery profile for actual temperature. The size should be the same as T1, T2 and T3 */
BATTERY_PROFILE_STRUCT battery_profile_temperature[] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0}
};

/* T0 -10C */
R_PROFILE_STRUCT r_profile_t0[] = {
{685,	4384},	
{685,	4375},	
{683,	4359},	
{683,	4344},	
{678,	4330},	
{666,	4316},	
{665,	4302},	
{659,	4290},	
{656,	4278},	
{648,	4266},	
{646,	4255},	
{642,	4243},	
{634,	4231},	
{632,	4219},
{629,	4208},	
{628,	4197},	
{622,	4186},	
{623,	4175},	
{622,	4165},	
{617,	4153},	
{615,	4142},	
{609,	4131},	
{612,	4121},	
{606,	4108},	
{608,	4100},	
{617,	4092},	
{628,	4084},	
{634,	4076},	
{632,	4064},	
{623,	4048},	
{605,	4027},	
{588,	4006},	
{577,	3989},	
{566,	3974},	
{558,	3962},	
{557,	3952},	
{554,	3943},	
{553,	3935},	
{553,	3929},	
{550,	3922},	
{550,	3916},	
{549,	3909},	
{547,	3902},	
{543,	3894},	
{543,	3888},	
{538,	3880},	
{538,	3874},	
{535,	3867},	
{537,	3862},	
{538,	3855},	
{537,	3850},	
{538,	3844},	
{540,	3838},	
{541,	3833},	
{544,	3828},	
{547,	3824},	
{549,	3819},	
{552,	3815},	
{555,	3811},	
{555,	3806},	
{560,	3803},	
{563,	3800},	
{564,	3797},	
{566,	3794},	
{571,	3792},	
{572,	3790},	
{578,	3789},	
{583,	3787},	
{587,	3786},	
{597,	3784},	
{603,	3783},	
{614,	3781},	
{626,	3780},	
{639,	3779},	
{651,	3776},	
{667,	3774},	
{687,	3772},	
{698,	3769},	
{718,	3767},	
{738,	3764},	
{759,	3760},	
{785,	3756},	
{811,	3752},	
{837,	3747},	
{871,	3742},	
{905,	3737},	
{944,	3730},	
{986,	3723},	
{1036,	3717},
{1091,	3711},
{1158,	3707},
{1229,	3702},
{1318,	3699},
{1420,	3696},
{1524,	3692},
{1620,	3687},
{1691,	3676},
{1744,	3651},
{1784,	3609},
{1857,	3549},
{1963,	3461},
{1643,	3333}
};

/* T1 0C */
R_PROFILE_STRUCT r_profile_t1[] = {
{299,	4387},	
{299,	4372},	
{299,	4358},	
{296,	4343},	
{295,	4330},	
{293,	4318},	
{291,	4304},	
{288,	4292},	
{288,	4281},	
{290,	4269},	
{288,	4257},	
{287,	4246},	
{284,	4234},	
{284,	4222},	
{284,	4211},	
{285,	4200},	
{283,	4188},	
{285,	4178},	
{287,	4167},	
{289,	4156},	
{290,	4145},	
{290,	4134},	
{293,	4123},	
{291,	4111},	
{292,	4102},	
{295,	4093},	
{299,	4085},	
{316,	4080},	
{321,	4072},	
{321,	4059},	
{313,	4040},	
{302,	4018},	
{296,	4000},	
{294,	3987},	
{293,	3977},	
{292,	3968},	
{290,	3960},	
{291,	3954},	
{291,	3948},	
{290,	3942},	
{285,	3934},	
{277,	3924},	
{274,	3916},	
{268,	3906},	
{264,	3897},	
{260,	3889},	
{256,	3880},	
{252,	3873},	
{254,	3866},	
{253,	3859},	
{251,	3854},	
{251,	3847},	
{250,	3842},	
{251,	3837},	
{254,	3832},	
{256,	3828},	
{256,	3824},	
{256,	3819},	
{258,	3816},	
{259,	3812},	
{257,	3808},	
{259,	3805},	
{261,	3801},	
{264,	3798},	
{263,	3795},	
{265,	3793},	
{267,	3790},	
{267,	3788},	
{268,	3786},	
{268,	3785},	
{268,	3783},	
{270,	3782},	
{272,	3781},	
{274,	3780},	
{278,	3779},	
{279,	3776},	
{282,	3774},	
{285,	3772},	
{288,	3768},	
{291,	3765},	
{297,	3762},	
{304,	3758},	
{310,	3754},	
{316,	3748},	
{324,	3743},	
{332,	3736},	
{343,	3731},	
{353,	3725},	
{368,	3717},	
{381,	3709},	
{398,	3704},	
{417,	3701},	
{442,	3699},	
{470,	3697},	
{512,	3694},	
{557,	3689},	
{613,	3676},	
{665,	3642},	
{742,	3589},	
{869,	3516},	
{1073,	3410},
{1724,	3198}
};

/* T2 25C */
R_PROFILE_STRUCT r_profile_t2[] = {
{127,	4386},
{127,	4370},
{127,	4357},
{130,	4346},
{130,	4333},
{127,	4320},
{126,	4307},
{127,	4295},
{126,	4283},
{124,	4270},
{124,	4258},
{124,	4246},
{123,	4234},
{124,	4223},
{126,	4211},
{124,	4200},
{126,	4188},
{126,	4177},
{127,	4165},
{127,	4154},
{126,	4143},
{130,	4133},
{128,	4121},
{130,	4110},
{132,	4099},
{130,	4088},
{132,	4078},
{133,	4071},
{143,	4066},
{141,	4056},
{136,	4040},
{137,	4023},
{136,	4009},
{138,	3997},
{141,	3990},
{144,	3984},
{149,	3980},
{146,	3973},
{146,	3965},
{147,	3957},
{151,	3949},
{150,	3940},
{149,	3930},
{145,	3920},
{140,	3907},
{130,	3894},
{126,	3884},
{124,	3875},
{122,	3868},
{124,	3862},
{121,	3855},
{121,	3849},
{121,	3844},
{122,	3839},
{123,	3835},
{124,	3831},
{126,	3826},
{127,	3822},
{129,	3818},
{129,	3814},
{127,	3810},
{127,	3806},
{130,	3805},
{130,	3801},
{130,	3798},
{132,	3795},
{133,	3793},
{133,	3790},
{133,	3787},
{135,	3785},
{133,	3782},
{137,	3781},
{132,	3777},
{129,	3773},
{127,	3770},
{129,	3767},
{124,	3764},
{123,	3759},
{118,	3754},
{123,	3751},
{123,	3748},
{126,	3745},
{124,	3741},
{126,	3737},
{124,	3731},
{124,	3725},
{127,	3721},
{127,	3715},
{127,	3707},
{124,	3698},
{123,	3694},
{124,	3692},
{127,	3692},
{129,	3690},
{133,	3689},
{138,	3685},
{141,	3675},
{132,	3640},
{140,	3591},
{144,	3525},
{158,	3433},
{203,	3271}
};

/* T3 50C */
R_PROFILE_STRUCT r_profile_t3[] = {
{108,	4386},
{108,	4361},
{107,	4347},
{107,	4335},
{108,	4323},
{107,	4310},
{107,	4298},
{109,	4286},
{110,	4275},
{109,	4262},
{109,	4250},
{110,	4239},
{110,	4226},
{109,	4214},
{110,	4203},
{108,	4191},
{108,	4179},
{112,	4169},
{110,	4156},
{111,	4146},
{112,	4134},
{113,	4123},
{112,	4112},
{112,	4101},
{112,	4090},
{112,	4079},
{112,	4069},
{113,	4059},
{113,	4049},
{113,	4039},
{113,	4029},
{115,	4020},
{115,	4010},
{116,	4001},
{118,	3992},
{118,	3984},
{118,	3975},
{121,	3967},
{121,	3958},
{123,	3950},
{126,	3942},
{127,	3934},
{127,	3924},
{121,	3911},
{113,	3897},
{110,	3885},
{110,	3876},
{110,	3869},
{109,	3862},
{110,	3857},
{112,	3851},
{110,	3845},
{109,	3839},
{108,	3834},
{110,	3830},
{109,	3825},
{109,	3821},
{109,	3816},
{112,	3813},
{110,	3808},
{109,	3804},
{112,	3801},
{110,	3797},
{112,	3794},
{112,	3791},
{113,	3788},
{115,	3786},
{115,	3783},
{116,	3780},
{118,	3778},
{118,	3774},
{112,	3767},
{109,	3759},
{109,	3753},
{109,	3749},
{110,	3744},
{110,	3741},
{110,	3736},
{112,	3733},
{109,	3728},
{110,	3725},
{112,	3722},
{113,	3718},
{112,	3713},
{110,	3707},
{112,	3701},
{115,	3695},
{112,	3688},
{106,	3680},
{107,	3677},
{110,	3677},
{115,	3676},
{119,	3675},
{124,	3672},
{130,	3668},
{119,	3648},
{118,	3608},
{121,	3556},
{127,	3486},
{138,	3385},
{194,	3194},
{194,	3194}
};

/* r-table profile for actual temperature. The size should be the same as T1, T2 and T3 */
R_PROFILE_STRUCT r_profile_temperature[] = {
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0}
};

/* ============================================================
// function prototype
// ============================================================*/
int fgauge_get_saddles(void);
BATTERY_PROFILE_STRUCT_P fgauge_get_profile(unsigned int temperature);

int fgauge_get_saddles_r_table(void);
R_PROFILE_STRUCT_P fgauge_get_profile_r_table(unsigned int temperature);

#endif	/*#ifndef _CUST_BATTERY_METER_TABLE_H*/


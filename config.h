#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int cornerrad = 4;
static const unsigned int gappih    = 10;
static const unsigned int gappiv    = 10;
static const unsigned int gappoh    = 20;
static const unsigned int gappov    = 20;
static const int smartgaps          = 0;
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Mono:size=14" };
static const char dmenufont[]       = "Source Code Pro:size=14";
static const char col_gray1[]       = "#073642";
static const char col_gray2[]       = "#444444";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#383838", "#dcdddf", "#dcdddf" },
	[SchemeSel]  = { "#ffffff", "#000080",  "#000080" },
};

/* tagging */
static const char *tags[] = { "一", "に", "三", "四"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     iscentered   isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       1,           1,           -1 },
	{ "st-256color",NULL,     NULL,       1 << 8,       1,           1,           -1 },
	{ "thunar",     NULL,     NULL,       1 << 8,       1,           1,           -1 },
	{ "Thunar",     NULL,     NULL,       1 << 8,       1,           1,           -1 },
	{ "Leafpad",    NULL,     NULL,       1 << 8,       1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "タイル ",      tile },    /* first entry is default */
	{ "浮く  ",      NULL },    /* no layout function means floating behavior */
	{ "浮く  ",      monocle },
};

/* key definitions */
#define MODKEY    Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define BrtUp 	XF86XK_MonBrightnessUp
#define BrtDown XF86XK_MonBrightnessDown
#define VolUp	XF86XK_AudioRaiseVolume
#define VolDown	XF86XK_AudioLowerVolume
#define Airplane XF86XK_RFKill

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", "#cccccf", "-nf", "#141414", "-sb", "#000080", "-sf", "#dcdddf", NULL };
static const char *roficmd[] = { "rofi", "-i", "-show" ,"drun", "-modi","drun", "-show-icons" };
static const char *termcmd[]  = { "st", NULL };
static const char *screenshot[] = {"/.aur/dwm/scripts/screenshotRegion"};

static const char *brtUP[] = {"brightnessctl", "set", "2%+"};
static const char *brtDN[] = {"brightnessctl", "set", "2%-"};
static const char *volUP[] = {"/.aur/dwm/scripts/volumeUP.sh"};
static const char *volDN[] = {"/.aur/dwm/scripts/volumeDN.sh"};
static const char *dwmstatus[] = {"/.aur/dwm/scripts/status"};
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,	                XK_Return, spawn,          {.v = roficmd } },
	
	// keys that trigger updating status bar
	{ 0,	                        BrtUp,     spawn, 	   {.v = dwmstatus} },
	{ 0,	                        BrtDown,   spawn, 	   {.v = dwmstatus} },
	{ 0,	                        VolUp,     spawn, 	   {.v = dwmstatus} },
	{ 0,	                        VolDown,   spawn, 	   {.v = dwmstatus} },
	{ 0,	                        Airplane,  spawn, 	   {.v = dwmstatus} },
	
	// Brightness
	{ 0,			        XK_Print,  spawn, 	   {.v = screenshot} },
	{ 0,	                        BrtUp,     spawn, 	   {.v = brtUP} },
	{ 0,	                        BrtDown,   spawn, 	   {.v = brtDN} },
	// Volume
	{ 0,				VolUp,	   spawn,	   {.v = volUP} },
	{ 0,				VolDown,   spawn,	   {.v = volDN} },

	//{ MODKEY,                       XK_b,      togglebar,      {0} },

	// layout
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },

	// focus
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,			XK_Tab,	   focusstack,	   {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Tab,	   zoom,	   {0}},

	{ MODKEY|ShiftMask,             XK_Up,     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Down,   incnmaster,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_Right,  setmfact,       {.f = +0.05} },

	//{ MODKEY,                       XK_Tab,    zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
        { MODKEY,                       XK_space,  fullscreen,     {0} },
	//{ MODKEY|ShiftMask,             XK_i,  	   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	//{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	//{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
    // gaps
	{ MODKEY,		        XK_minus,  incrigaps,      {.i = -5 }},
	{ MODKEY,			XK_equal,  incrigaps,      {.i = +5 }},
	{ MODKEY|ShiftMask,		XK_minus,  incrogaps,      {.i = +5 }},
	{ MODKEY|ShiftMask,		XK_equal,  incrogaps,      {.i = -5 }},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};


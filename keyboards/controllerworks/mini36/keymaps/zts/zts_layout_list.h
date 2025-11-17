#pragma once

#if !defined (ZTS_LAYER_LIST)

#define ZTS_LAYER_LIST \
ZTS_X(BASE,   "Base") \
ZTS_X(EXTRA,  "Extra") \
ZTS_X(TAP,    "Tap") \
ZTS_X(BUTTON, "Button") \
ZTS_X(NAV,    "Nav") \
ZTS_X(MOUSE,  "Mouse") \
ZTS_X(MEDIA,  "Media") \
ZTS_X(NUM,    "Num") \
ZTS_X(SYM,    "Sym") \
ZTS_X(FUN,    "Fun")

#endif

const char * const layers_as_strings[] = {
    [BASE] = "BASE",
    [LOWER] = "__ LoWer __",
    [RAISE] = "^^ Raise ^^",
    [ADJUST] = "> ADJust <",
    [MOVE] = "=> MoVe <=",
    [WNDW] = ":> Window <:",
    [SYMB] = "%% Symbol %%",
    [NUMP] = "Num Pad",
};
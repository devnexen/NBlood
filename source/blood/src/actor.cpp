#include "build.h"
#include "pragmas.h"
#include "mmulti.h"
#include "common.h"
#include "common_game.h"

#include "actor.h"
#include "ai.h"
#include "aibat.h"
#include "aibeast.h"
#include "aiboneel.h"
#include "aiburn.h"
#include "aicaleb.h"
#include "aicerber.h"
#include "aicult.h"
#include "aigarg.h"
#include "aighost.h"
#include "aigilbst.h"
#include "aihand.h"
#include "aihound.h"
#include "aiinnoc.h"
#include "aipod.h"
#include "airat.h"
#include "aispid.h"
#include "aitchern.h"
#include "aizomba.h"
#include "aizombf.h"
#include "blood.h"
#include "callback.h"
#include "config.h"
#include "db.h"
#include "endgame.h"
#include "eventq.h"
#include "fx.h"
#include "gameutil.h"
#include "gib.h"
#include "globals.h"
#include "levels.h"
#include "loadsave.h"
#include "player.h"
#include "seq.h"
#include "sfx.h"
#include "sound.h"
#include "tile.h"
#include "trig.h"
#include "triggers.h"
#include "view.h"
#include "warp.h"
#include "weapon.h"

VECTORDATA gVectorData[] = {
    {
        DAMAGE_TYPE_2,
        17,
        174762,
        1152,
        10240,
        0,
        1,
        20480,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        FX_43, FX_6, (FX_ID)-1, 502,
        FX_43, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, FX_7, 502,
        FX_43, FX_6, FX_7, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 503,
        FX_43, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 503,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        4,
        65536,
        0,
        8192,
        0,
        1,
        12288,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        FX_43, FX_6, (FX_ID)-1, -1,
        FX_43, FX_0, (FX_ID)-1, -1,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        FX_43, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        7,
        21845,
        0,
        32768,
        0,
        1,
        12288,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, FX_7, 510,
        (FX_ID)-1, FX_5, FX_7, 511,
        FX_43, FX_6, (FX_ID)-1, 512,
        FX_43, FX_0, (FX_ID)-1, 513,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, FX_7, 512,
        FX_43, FX_6, FX_7, 512,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 513,
        FX_43, (FX_ID)-1, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        20,
        65536,
        0,
        16384,
        0,
        1,
        20480,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, FX_7, 510,
        (FX_ID)-1, FX_5, FX_7, 511,
        FX_43, FX_6, (FX_ID)-1, 512,
        FX_43, FX_0, (FX_ID)-1, 513,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, FX_7, 512,
        FX_43, FX_6, FX_7, 512,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 513,
        FX_43, (FX_ID)-1, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        6,
        87381,
        0,
        12288,
        0,
        1,
        6144,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        FX_43, FX_6, (FX_ID)-1, -1,
        FX_43, FX_0, (FX_ID)-1, -1,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        FX_43, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        12,
        65536,
        0,
        16384,
        0,
        1,
        12288,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        FX_43, FX_5, FX_7, 510,
        (FX_ID)-1, FX_5, FX_7, 511,
        FX_43, FX_6, (FX_ID)-1, 512,
        FX_43, FX_0, (FX_ID)-1, 513,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, FX_7, 512,
        FX_43, FX_6, FX_7, 512,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 513,
        FX_43, (FX_ID)-1, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, FX_6, (FX_ID)-1, 513,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        4,
        0,
        921,
        0,
        0,
        1,
        4096,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        12,
        0,
        1177,
        0,
        0,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        9,
        0,
        1177,
        0,
        0,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_3,
        50,
        43690,
        1024,
        8192,
        0,
        4,
        32768,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        18,
        436906,
        1024,
        16384,
        0,
        2,
        20480,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        9,
        218453,
        1024,
        0,
        0,
        1,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        20,
        436906,
        1024,
        16384,
        0,
        3,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        16,
        218453,
        1024,
        8192,
        0,
        4,
        20480,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        19,
        218453,
        614,
        8192,
        0,
        2,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        10,
        218453,
        614,
        8192,
        0,
        2,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        4,
        0,
        921,
        0,
        0,
        1,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        8,
        0,
        614,
        0,
        0,
        1,
        24576,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_2,
        9,
        0,
        512,
        0,
        0,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_5, (FX_ID)-1, 500,
        (FX_ID)-1, FX_5, (FX_ID)-1, 501,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_0, (FX_ID)-1, 503,
        (FX_ID)-1, FX_4, (FX_ID)-1, -1,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, FX_6, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, 502,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        (DAMAGE_TYPE)-1,
        0,
        0,
        2560,
        0,
        0,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, FX_34, FX_35, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_1,
        2,
        0,
        0,
        0,
        15,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    },
    {
        DAMAGE_TYPE_5,
        25,
        0,
        0,
        0,
        0,
        0,
        0,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
        (FX_ID)-1, (FX_ID)-1, (FX_ID)-1, -1,
    }
};

ITEMDATA gItemData[] = {
    {
        0,
        2552,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        2553,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        2554,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        2555,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        2556,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        2557,
        -8,
        0,
        32,
        32,
        -1,
    },
    {
        0,
        -1,
        -8,
        0,
        255,
        255,
        -1,
    },
    {
        0,
        519,
        -8,
        0,
        48,
        48,
        0,
    },
    {
        0,
        822,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        2169,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        2433,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        517,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        783,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        896,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        825,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        827,
        -8,
        0,
        40,
        40,
        4,
    },
    {
        0,
        828,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        829,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        830,
        -8,
        0,
        80,
        64,
        1,
    },
    {
        0,
        831,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        863,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        760,
        -8,
        0,
        40,
        40,
        2,
    },
    {
        0,
        836,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        851,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        2428,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        839,
        -8,
        0,
        40,
        40,
        3,
    },
    {
        0,
        768,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        840,
        -8,
        0,
        48,
        48,
        -1,
    },
    {
        0,
        841,
        -8,
        0,
        48,
        48,
        -1,
    },
    {
        0,
        842,
        -8,
        0,
        48,
        48,
        -1,
    },
    {
        0,
        843,
        -8,
        0,
        48,
        48,
        -1,
    },
    {
        0,
        683,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        521,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        604,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        520,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        803,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        518,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        522,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        523,
        -8,
        0,
        40,
        40,
        -1,
    },
    {
        0,
        837,
        -8,
        0,
        80,
        64,
        -1,
    },
    {
        0,
        2628,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        2586,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        2578,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        2602,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        2594,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        753,
        -8,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        753,
        -8,
        7,
        64,
        64,
        -1,
    },
    {
        0,
        3558,
        -128,
        0,
        64,
        64,
        -1,
    },
    {
        0,
        3558,
        -128,
        7,
        64,
        64,
        -1,
    }
};

AMMOITEMDATA gAmmoItemData[] = {
    {
        0,
        618,
        -8,
        0,
        40,
        40,
        480,
        6,
        7
    },
    {
        0,
        589,
        -8,
        0,
        48,
        48,
        1,
        5,
        6
    },
    {
        0,
        589,
        -8,
        0,
        48,
        48,
        1,
        5,
        6
    },
    {
        0,
        809,
        -8,
        0,
        48,
        48,
        5,
        5,
        6
    },
    {
        0,
        811,
        -8,
        0,
        48,
        48,
        1,
        10,
        11
    },
    {
        0,
        810,
        -8,
        0,
        48,
        48,
        1,
        11,
        12
    },
    {
        0,
        820,
        -8,
        0,
        24,
        24,
        10,
        8,
        0
    },
    {
        0,
        619,
        -8,
        0,
        48,
        48,
        4,
        2,
        0
    },
    {
        0,
        812,
        -8,
        0,
        48,
        48,
        15,
        2,
        0
    },
    {
        0,
        813,
        -8,
        0,
        48,
        48,
        15,
        3,
        0
    },
    {
        0,
        525,
        -8,
        0,
        48,
        48,
        100,
        9,
        10
    },
    {
        0,
        814,
        -8,
        0,
        48,
        48,
        15,
        255,
        0
    },
    {
        0,
        817,
        -8,
        0,
        48,
        48,
        100,
        3,
        0
    },
    {
        0,
        548,
        -8,
        0,
        24,
        24,
        32,
        7,
        0
    },
    {
        0,
        0,
        -8,
        0,
        48,
        48,
        6,
        255,
        0
    },
    {
        0,
        0,
        -8,
        0,
        48,
        48,
        6,
        255,
        0
    },
    {
        0,
        816,
        -8,
        0,
        48,
        48,
        8,
        1,
        0
    },
    {
        0,
        818,
        -8,
        0,
        48,
        48,
        8,
        255,
        0
    },
    {
        0,
        819,
        -8,
        0,
        48,
        48,
        8,
        255,
        0
    },
    {
        0,
        801,
        -8,
        0,
        48,
        48,
        6,
        4,
        0
    },
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    },
};

WEAPONITEMDATA gWeaponItemData[] = {
    {
        0,
        -1,
        0,
        0,
        0,
        0,
        0,
        -1,
        0
    },
    {
        0,
        559,
        -8,
        0,
        48,
        48,
        3,
        2,
        8
    },
    {
        0,
        558,
        -8,
        0,
        48,
        48,
        4,
        3,
        50
    },
    {
        0,
        524,
        -8,
        0,
        48,
        48,
        2,
        1,
        9
    },
    {
        0,
        525,
        -8,
        0,
        48,
        48,
        10,
        9,
        100
    },
    {
        0,
        539,
        -8,
        0,
        48,
        48,
        8,
        7,
        64
    },
    {
        0,
        526,
        -8,
        0,
        48,
        48,
        5,
        4,
        6
    },
    {
        0,
        -1,
        0,
        0,
        0,
        0,
        1,
        -1,
        0
    },
    {
        0,
        618,
        -8,
        0,
        48,
        48,
        7,
        6,
        480
    },
    {
        0,
        589,
        -8,
        0,
        48,
        48,
        6,
        5,
        1
    },
    {
        0,
        800,
        -8,
        0,
        48,
        48,
        9,
        8,
        35
    }
};

MissileType missileInfo[] = {
    {
        2138,
        978670,
        512,
        40,
        40,
        -16,
        16
    },
    {
        2424,
        3145728,
        0,
        32,
        32,
        -128,
        32
    },
    {
        3056,
        2796202,
        0,
        32,
        32,
        -128,
        32
    },
    {
        2424,
        2446677,
        0,
        32,
        32,
        -128,
        4
    },
    {
        0,
        1118481,
        0,
        24,
        24,
        -128,
        16
    },
    {
        0,
        1118481,
        0,
        32,
        32,
        -128,
        32
    },
    {
        2130,
        2796202,
        0,
        32,
        32,
        -128,
        16
    },
    {
        870,
        699050,
        0,
        32,
        32,
        -24,
        32
    },
    {
        0,
        1118481,
        0,
        24,
        24,
        -128,
        16
    },
    {
        0,
        838860,
        0,
        16,
        16,
        -16,
        16
    },
    {
        0,
        838860,
        0,
        8,
        8,
        0,
        16
    },
    {
        3056,
        2097152,
        0,
        32,
        32,
        -128,
        16
    },
    {
        0,
        2446677,
        0,
        30,
        30,
        -128,
        24
    },
    {
        0,
        2446677,
        0,
        30,
        30,
        -128,
        24
    },
    {
        0,
        1398101,
        0,
        24,
        24,
        -128,
        16
    },
    {
        2446,
        2796202,
        0,
        32,
        32,
        -128,
        16
    },
    {
        3056,
        2446677,
        0,
        16,
        16,
        -128,
        16
    },
    {
        3056,
        1747626,
        0,
        32,
        32,
        -128,
        16
    }
};

THINGINFO thingInfo[] = {
    {
        25,
        250,
        32,
        11,
        4096,
        80,
        384,
        907,
        0,
        0,
        0,
        0,
        256, 256, 128, 64, 0, 0, 128
    },
    {
        5,
        5,
        16,
        3,
        24576,
        1600,
        256,
        3444,
        -16,
        0,
        32,
        32,
        256, 256, 256, 64, 0, 0, 512
    },
    {
        5,
        5,
        16,
        3,
        24576,
        1600,
        256,
        3457,
        -16,
        0,
        32,
        32,
        256, 256, 256, 64, 0, 0, 512
    },
    {
        1,
        20,
        32,
        3,
        32768,
        80,
        0,
        739,
        0,
        0,
        0,
        0,
        256, 0, 256, 128, 0, 0, 0
    },
    {
        1,
        150,
        32,
        3,
        32768,
        80,
        0,
        642,
        0,
        0,
        0,
        0,
        256, 256, 256, 128, 0, 0, 0
    },
    {
        10,
        0,
        0,
        0,
        0,
        0,
        0,
        462,
        0,
        0,
        0,
        0,
        0, 0, 0, 256, 0, 0, 0
    },
    {
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        266,
        0,
        0,
        0,
        0,
        256, 0, 256, 256, 0, 0, 0
    },
    {
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        796,
        0,
        0,
        0,
        0,
        256, 0, 256, 256, 0, 0, 512
    },
    {
        50,
        0,
        0,
        0,
        0,
        0,
        0,
        1127,
        0,
        0,
        0,
        0,
        0, 0, 0, 256, 0, 0, 0
    },
    {
        8,
        0,
        0,
        0,
        0,
        0,
        0,
        1142,
        0,
        0,
        0,
        0,
        256, 0, 256, 128, 0, 0, 0
    },
    {
        4,
        0,
        0,
        0,
        0,
        0,
        0,
        1069,
        0,
        0,
        0,
        0,
        256, 256, 64, 256, 0, 0, 128
    },
    {
        40,
        0,
        0,
        0,
        0,
        0,
        0,
        483,
        0,
        0,
        0,
        0,
        64, 0, 128, 256, 0, 0, 0
    },
    {
        1,
        0,
        0,
        0,
        0,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        0, 256, 0, 256, 0, 0, 128
    },
    {
        1000,
        0,
        0,
        8,
        0,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        0, 0, 128, 256, 0, 0, 512
    },
    {
        0,
        15,
        8,
        3,
        32768,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        0,
        8,
        48,
        3,
        49152,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        10,
        2,
        0,
        0,
        32768,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        256, 0, 256, 256, 0, 0, 128
    },
    {
        20,
        2,
        0,
        0,
        32768,
        0,
        0,
        -1,
        0,
        0,
        0,
        0,
        0, 0, 0, 256, 0, 0, 128
    },
    {
        5,
        14,
        16,
        3,
        24576,
        1600,
        256,
        3422,
        -32,
        0,
        32,
        32,
        64, 256, 128, 64, 0, 0, 256
    },
    {
        5,
        14,
        16,
        3,
        24576,
        1600,
        256,
        3433,
        -32,
        0,
        32,
        32,
        64, 256, 128, 64, 0, 0, 256
    },
    {
        5,
        14,
        16,
        3,
        32768,
        1600,
        256,
        3467,
        -128,
        0,
        32,
        32,
        64, 256, 128, 64, 0, 0, 256
    },
    {
        5,
        6,
        16,
        3,
        32768,
        1600,
        256,
        1462,
        0,
        0,
        32,
        32,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        8,
        3,
        16,
        11,
        32768,
        1600,
        256,
        -1,
        0,
        0,
        0,
        0,
        256, 0, 256, 256, 0, 0, 0
    },
    {
        0,
        1,
        1,
        2,
        0,
        0,
        0,
        1147,
        0,
        10,
        0,
        0,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        0,
        1,
        1,
        2,
        0,
        0,
        0,
        1160,
        0,
        2,
        0,
        0,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        15,
        4,
        4,
        3,
        24576,
        0,
        257,
        -1,
        0,
        0,
        0,
        0,
        128, 64, 256, 256, 0, 0, 256
    },
    {
        30,
        30,
        8,
        3,
        8192,
        0,
        257,
        -1,
        0,
        0,
        0,
        0,
        128, 64, 256, 256, 0, 0, 64
    },
    {
        60,
        5,
        32,
        3,
        40960,
        1280,
        257,
        3405,
        0,
        0,
        40,
        40,
        128, 64, 256, 256, 0, 0, 64
    },
    {
        80,
        30,
        32,
        3,
        57344,
        1600,
        256,
        -1,
        -128,
        0,
        32,
        32,
        0, 0, 0, 0, 0, 0, 0
    },
    {
        80,
        30,
        32,
        3,
        57344,
        1600,
        256,
        -1,
        -128,
        0,
        32,
        32,
        256, 0, 256, 256, 0, 0, 0
    },
    {
        80,
        30,
        32,
        3,
        57344,
        1600,
        256,
        -1,
        -128,
        0,
        32,
        32,
        256, 0, 256, 256, 0, 0, 0
    },
    {
        150,
        30,
        48,
        3,
        32768,
        1600,
        257,
        800,
        -128,
        0,
        48,
        48,
        64, 64, 112, 64, 0, 96, 96
    },
    {
        1,
        30,
        48,
        3,
        32768,
        1600,
        0,
        2443,
        -128,
        0,
        16,
        16,
        0, 0, 0, 0, 0, 0, 0
    }
};

EXPLOSION explodeInfo[] = {
    {
        40,
        10,
        10,
        75,
        450,
        0,
        60,
        80,
        40
    },
    {
        80,
        20,
        10,
        150,
        900,
        0,
        60,
        160,
        60
    },
    {
        120,
        40,
        15,
        225,
        1350,
        0,
        60,
        240,
        80
    },
    {
        80,
        5,
        10,
        120,
        20,
        10,
        60,
        0,
        40
    },
    {
        120,
        10,
        10,
        180,
        40,
        10,
        60,
        0,
        80
    },
    {
        160,
        15,
        10,
        240,
        60,
        10,
        60,
        0,
        120
    },
    {
        40,
        20,
        10,
        120,
        0,
        10,
        30,
        60,
        40
    },
    {
        80,
        20,
        10,
        150,
        800,
        5,
        60,
        160,
        60
    },
};

int gDudeDrag = 0x2a00;

short gAffectedSectors[kMaxSectors];
short gAffectedXWalls[kMaxXWalls];
short gPlayerGibThingComments[] = {
    734, 735, 736, 737, 738, 739, 740, 741, 3038, 3049
};

void FireballSeqCallback(int, int);
void sub_38938(int, int);
void NapalmSeqCallback(int, int);
void sub_3888C(int, int);
void TreeToGibCallback(int, int);
void DudeToGibCallback1(int, int);
void DudeToGibCallback2(int, int);

SPRITEHIT gSpriteHit[kMaxXSprites];

int nFireballClient = seqRegisterClient(FireballSeqCallback);
int dword_2192D8 = seqRegisterClient(sub_38938);
int nNapalmClient = seqRegisterClient(NapalmSeqCallback);
int dword_2192E0 = seqRegisterClient(sub_3888C);
int nTreeToGibClient = seqRegisterClient(TreeToGibCallback);
int nDudeToGibClient1 = seqRegisterClient(DudeToGibCallback1);
int nDudeToGibClient2 = seqRegisterClient(DudeToGibCallback2);

int gPostCount = 0;

struct POSTPONE {
    short at0;
    short at2;
};

POSTPONE gPost[kMaxSprites];

static char buffer[120];

bool IsItemSprite(SPRITE *pSprite)
{
    return pSprite->type >= 100 && pSprite->type < 149;
}

bool IsWeaponSprite(SPRITE *pSprite)
{
    return pSprite->type >= 40 && pSprite->type < 51;
}

bool IsAmmoSprite(SPRITE *pSprite)
{
    return pSprite->type >= 60 && pSprite->type < 81;
}

bool IsUnderwaterSector(int nSector)
{
    int nXSector = sector[nSector].extra;
    if (nXSector > 0 && xsector[nXSector].at13_4)
        return 1;
    return 0;
}

int actSpriteOwnerToSpriteId(SPRITE *pSprite)
{
    dassert(pSprite != NULL);
    if (pSprite->owner == -1)
        return -1;
    int nSprite = pSprite->owner & 0xfff;
    if (pSprite->owner & 0x1000)
        nSprite = gPlayer[nSprite].pSprite->index;
    return nSprite;
}

void actPropagateSpriteOwner(SPRITE *pTarget, SPRITE *pSource)
{
    dassert(pTarget != NULL && pSource != NULL);
    if (IsPlayerSprite(pSource))
        pTarget->owner = (pSource->type-kDudePlayer1) | 0x1000;
    else
        pTarget->owner = pSource->index;
}

int actSpriteIdToOwnerId(int nSprite)
{
    if (nSprite == -1)
        return -1;
    dassert(nSprite >= 0 && nSprite < kMaxSprites);
    SPRITE *pSprite = &qsprite[nSprite];
    if (IsPlayerSprite(pSprite))
        nSprite = (pSprite->type-kDudePlayer1) | 0x1000;
    return nSprite;
}

int actOwnerIdToSpriteId(int nSprite)
{
    if (nSprite == -1)
        return -1;
    if (nSprite & 0x1000)
        nSprite = gPlayer[nSprite&0xfff].pSprite->index;
    return nSprite;
}

bool actTypeInSector(int nSector, int nType)
{
    for (int nSprite = headspritesect[nSector]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        if (qsprite[nSprite].index == nType)
            return 1;
    }
    return 0;
}

void actAllocateSpares(void)
{
}

int DudeDifficulty[5] = {
    512, 384, 256, 208, 160
};

void actInit(void)
{
    for (int nSprite = headspritestat[3]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->type == 44)
            pSprite->type = 70;
    }
    for (int nSprite = headspritestat[11]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        int nXSprite = pSprite->extra;
        XSPRITE *pXSprite = NULL;
        if (nXSprite > 0 && nXSprite < kMaxXSprites)
            pXSprite = &xsprite[nXSprite];
        if (pSprite->type == 459)
        {
            pXSprite->at1_6 = 0;
            pXSprite->at9_4 = ClipLow(pXSprite->at9_4, 1);
            pSprite->cstat &= ~1;
            pSprite->cstat |= 32768;
        }
    }
    for (int nSprite = headspritestat[4]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        int nXSprite = pSprite->extra;
        if (nXSprite <= 0 || nXSprite >= kMaxXSprites)
            ThrowError("WARNING: Sprite %d is on the wrong status list!\n", nSprite);
        XSPRITE *pXSprite = &xsprite[nXSprite];
        int nType = pSprite->type - 400;
        pSprite->clipdist = thingInfo[nType].at4;
        pSprite->hitag = thingInfo[nType].at5;
        if (pSprite->hitag&2)
            pSprite->hitag |= 4;
        xvel[nSprite] = yvel[nSprite] = zvel[nSprite] = 0;
        pXSprite->health = thingInfo[nType].at0<<4;
        switch (pSprite->type)
        {
        case 401:
        case 413:
            pXSprite->at1_6 = 0;
            break;
        case 426:
        {
            SEQINST *pInst = GetInstance(3, nXSprite);
            if (pInst && pInst->at13)
            {
                DICTNODE *hSeq = gSysRes.Lookup(pInst->at8, "SEQ");
                if (!hSeq)
                    break;
                seqSpawn(pInst->at8, 3, nXSprite);
            }
            break;
        }
        default:
            pXSprite->at1_6 = 1;
            break;
        }
    }
    if (gGameOptions.nMonsterSettings == 0)
    {
        gKillMgr.SetCount(0);
        while (headspritestat[6] >= 0)
        {
            SPRITE *pSprite = &qsprite[headspritestat[6]];
            int nXSprite = pSprite->extra;
            dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
            XSPRITE *pXSprite = &xsprite[nXSprite];
            // Drop Key
            if (pXSprite->atd_3 > 0)
                actDropObject(pSprite, 99 + pXSprite->atd_3);
            DeleteSprite(headspritestat[6]);
        }
    }
    else
    {
        char unk[kDudeMax-kDudeBase];
        memset(unk, 0, sizeof(unk));
        for (int nSprite = headspritestat[6]; nSprite >= 0; nSprite = nextspritestat[nSprite])
        {
            SPRITE *pSprite = &qsprite[nSprite];
            if (pSprite->type < kDudeBase || pSprite->type >= kDudeMax)
                ThrowError("Non-enemy sprite (%d) in the enemy sprite list.\n", nSprite);
            unk[pSprite->type-kDudeBase] = 1;
        }
        gKillMgr.sub_2641C();
        for (int i = 0; i < kDudeMax-kDudeBase; i++)
            for (int j = 0; j < 7; j++)
                dudeInfo[i].at70[j] = mulscale8(DudeDifficulty[gGameOptions.nDifficulty], dudeInfo[i].at54[j]);
        for (int nSprite = headspritestat[6]; nSprite >= 0; nSprite = nextspritestat[nSprite])
        {
            SPRITE *pSprite = &qsprite[nSprite];
            int nXSprite = pSprite->extra;
            dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
            XSPRITE *pXSprite = &xsprite[nXSprite];
            int nType = pSprite->type-kDudeBase;
            if (!IsPlayerSprite(pSprite))
            {
                pSprite->cstat |= 4096+256+1;
                pSprite->clipdist = dudeInfo[nType].ata;
                xvel[nSprite] = yvel[nSprite] = zvel[nSprite] = 0;
                pXSprite->health = dudeInfo[nType].at2<<4;
            }
            if (gSysRes.Lookup(dudeInfo[nType].seqStartID, "SEQ"))
                seqSpawn(dudeInfo[nType].seqStartID, 3, nXSprite);
        }
        aiInit();
    }
}

void ConcussSprite(int a1, SPRITE *pSprite, int x, int y, int z, int a6)
{
    dassert(pSprite != NULL);
    int dx = pSprite->x-x;
    int dy = pSprite->y-y;
    int dz = (pSprite->z-z)>>4;
    int dist2 = 0x40000+dx*dx+dy*dy+dz*dz;
    dassert(dist2 > 0);
    a6 = scale(0x40000, a6, dist2);
    if (pSprite->hitag & 1)
    {
        int mass = 0;
        if (pSprite->type >= kDudeBase && pSprite->type < kDudeMax)
            mass = dudeInfo[pSprite->type-kDudeBase].at4;
        else if (pSprite->type >= 400 && pSprite->type < 433)
            mass = thingInfo[pSprite->type-400].at2;
        else
            ThrowError("Unexpected type in ConcussSprite(): Sprite: %d  Type: %d  Stat: %d", pSprite->index, pSprite->type, pSprite->statnum);
        int size = (tilesiz[pSprite->picnum].x*pSprite->xrepeat*tilesiz[pSprite->picnum].y*pSprite->yrepeat)>>1;
        dassert(mass > 0);

        int t = scale(a6, size, mass);
        dx = mulscale16(t, dx);
        dy = mulscale16(t, dy);
        dz = mulscale16(t, dz);
        int nSprite = pSprite->index;
        dassert(nSprite >= 0 && nSprite < kMaxSprites);
        xvel[nSprite] += dx;
        yvel[nSprite] += dy;
        zvel[nSprite] += dz;
    }
    actDamageSprite(a1, pSprite, DAMAGE_TYPE_3, a6);
}

int actWallBounceVector(long *x, long *y, int nWall, int a4)
{
    int wx, wy;
    GetWallNormal(nWall, &wx, &wy);
    int t = dmulscale16(*x, wx, *y, wy);
    int t2 = mulscale16r(t, a4+0x10000);
    *x -= mulscale16(wx, t2);
    *y -= mulscale16(wy, t2);
    return mulscale16r(t, 0x10000-a4);
}

int actFloorBounceVector(long *x, long *y, long *z, int nSector, int a5)
{
    int t = 0x10000-a5;
    if (sector[nSector].floorheinum == 0)
    {
        int t2 = mulscale16(*z, t);
        *z = -(*z-t2);
        return t2;
    }
    WALL *pWall = &qwall[sector[nSector].wallptr];
    WALL *pWall2 = &qwall[pWall->point2];
    int angle = getangle(pWall2->x-pWall->x, pWall2->y-pWall->y)+512;
    int t2 = sector[nSector].floorheinum<<4;
    int t3 = approxDist(-0x10000, t2);
    int t4 = divscale16(-0x10000, t3);
    int t5 = divscale16(t2, t3);
    int t6 = mulscale30(t5, Cos(angle));
    int t7 = mulscale30(t5, Sin(angle));
    int t8 = tmulscale16(*x, t6, *y, t7, *z, t4);
    int t9 = mulscale16(t8, 0x10000+a5);
    *x -= mulscale16(t6, t9);
    *y -= mulscale16(t7, t9);
    *z -= mulscale16(t4, t9);
    return mulscale16r(t8, t);
}

void sub_2A620(int nSprite, int x, int y, int z, int nSector, int nDist, int a7, int a8, DAMAGE_TYPE a9, int a10, int a11, int a12, int a13)
{
    char va0[(kMaxSectors+7)>>3];
    int nOwner = actSpriteIdToOwnerId(nSprite);
    gAffectedSectors[0] = 0;
    gAffectedXWalls[0] = 0;
    GetClosestSpriteSectors(nSector, x, y, nDist, gAffectedSectors, va0, gAffectedXWalls);
    nDist <<= 4;
    if (a10 & 2)
    {
        for (int i = headspritestat[6]; i >= 0; i = nextspritestat[i])
        {
            if (i != nSprite || (a10 & 1))
            {
                SPRITE *pSprite2 = &qsprite[i];
                if (pSprite2->extra > 0 && pSprite2->extra < kMaxXSprites)
                {
                    if (pSprite2->hitag & 0x20)
                        continue;
                    if (!TestBitString(va0, pSprite2->sectnum))
                        continue;
                    if (!CheckProximity(pSprite2, x, y, z, nSector, nDist))
                        continue;
                    int dx = klabs(x-pSprite2->x);
                    int dy = klabs(y-pSprite2->y);
                    int dz = klabs(z-pSprite2->z)>>4;
                    int dist = ksqrt(dx*dx+dy*dy+dz*dz);
                    if (dist > nDist)
                        continue;
                    int vcx;
                    if (dist != 0)
                        vcx = a7+((nDist-dist)*a8)/nDist;
                    else
                        vcx = a7+a8;
                    actDamageSprite(nSprite, pSprite2, a9, vcx<<4);
                    if (a11)
                        actBurnSprite(nOwner, &xsprite[pSprite2->extra], a11);
                }
            }
        }
    }
    if (a10 & 4)
    {
        for (int i = headspritestat[6]; i >= 0; i = nextspritestat[i])
        {
            SPRITE *pSprite2 = &qsprite[i];
            if (pSprite2->hitag&0x20)
                continue;
            int nSector2 = pSprite2->sectnum;
            if (!TestBitString(va0, pSprite2->sectnum))
                continue;
            if (!CheckProximity(pSprite2, x, y, z, nSector, nDist))
                continue;
            XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
            if (pXSprite2->at17_5)
                continue;
            int dx = klabs(x-pSprite2->x);
            int dy = klabs(y-pSprite2->y);
            int dist = ksqrt(dx*dx+dy*dy);
            if (dist > nDist)
                continue;
            int vcx;
            if (dist != 0)
                vcx = a7+((nDist-dist)*a8)/nDist;
            else
                vcx = a7+a8;
            actDamageSprite(nSprite, pSprite2, a9, vcx<<4);
            if (a11)
                actBurnSprite(nOwner, pXSprite2, a11);
        }
    }
}

void sub_2AA94(SPRITE *pSprite, XSPRITE *pXSprite)
{
    int nSprite = actOwnerIdToSpriteId(pSprite->owner);
    actPostSprite(pSprite->index, 0);
    seqSpawn(9, 3, pSprite->extra);
    if (Chance(0x8000))
        pSprite->cstat |= 4;
    sfxPlay3DSound(pSprite, 303, 24+(pSprite->hitag&3), 1);
    sub_2A620(nSprite, pSprite->x, pSprite->y, pSprite->z, pSprite->sectnum, 128, 0, 60, DAMAGE_TYPE_3, 15, 120, 0, 0);
    if (pXSprite->at18_2 > 1)
    {
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        int v14[2];
        v14[0] = pXSprite->at18_2>>1;
        v14[1] = pXSprite->at18_2-v14[0];
        int v4 = pSprite->ang;
        xvel[pSprite->index] = 0;
        yvel[pSprite->index] = 0;
        zvel[pSprite->index] = 0;
        for (int i = 0; i < 2; i++)
        {
            int t1 = Random(0x33333)+0x33333;
            int t2 = Random2(0x71);
            pSprite->ang = (t2+v4+2048)&2047;
            SPRITE *pSprite2 = actFireThing(pSprite, 0, 0, -0x93d0, 428, t1);
            XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
            pSprite2->owner = pSprite->owner;
            seqSpawn(61, 3, pSprite2->extra, nNapalmClient);
            pXSprite2->at18_2 = v14[i];
        }
    }
}

SPRITE *actSpawnFloor(SPRITE *pSprite)
{
    short nSector = pSprite->sectnum;
    int x = pSprite->x;
    int y = pSprite->y;
    updatesector(x, y, &nSector);
    int zFloor = getflorzofslope(nSector, x, y);
    SPRITE *pSprite2 = actSpawnSprite(nSector, x, y, zFloor, 3, 0);
    if (pSprite2)
        pSprite2->cstat &= ~257;
    return pSprite2;
}

SPRITE *actDropAmmo(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (pSprite && pSprite->statnum < kMaxStatus && nType >= 60 && nType < 81)
    {
        pSprite2 = actSpawnFloor(pSprite);
        AMMOITEMDATA *pAmmo = &gAmmoItemData[nType-60];
        pSprite2->type = nType;
        pSprite2->picnum = pAmmo->picnum;
        pSprite2->shade = pAmmo->shade;
        pSprite2->xrepeat = pAmmo->xrepeat;
        pSprite2->yrepeat = pAmmo->yrepeat;
    }
    return pSprite2;
}

SPRITE *actDropWeapon(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (pSprite && pSprite->statnum < kMaxStatus && nType >= 40 && nType < 51)
    {
        pSprite2 = actSpawnFloor(pSprite);
        WEAPONITEMDATA *pWeapon = &gWeaponItemData[nType-40];
        pSprite2->type = nType;
        pSprite2->picnum = pWeapon->picnum;
        pSprite2->shade = pWeapon->shade;
        pSprite2->xrepeat = pWeapon->xrepeat;
        pSprite2->yrepeat = pWeapon->yrepeat;
    }
    return pSprite2;
}

SPRITE *actDropItem(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (pSprite && pSprite->statnum < kMaxStatus && nType >= 100 && nType < 149)
    {
        pSprite2 = actSpawnFloor(pSprite);
        ITEMDATA *pItem = &gItemData[nType-100];
        pSprite2->type = nType;
        pSprite2->picnum = pItem->picnum;
        pSprite2->shade = pItem->shade;
        pSprite2->xrepeat = pItem->xrepeat;
        pSprite2->yrepeat = pItem->yrepeat;
    }
    return pSprite2;
}

SPRITE *actDropKey(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (pSprite && pSprite->statnum < kMaxStatus && nType >= 100 && nType <= 106)
    {
        pSprite2 = actDropItem(pSprite, nType);
        if (pSprite2 && gGameOptions.nGameType == 1)
        {
            if (pSprite2->extra == -1)
                dbInsertXSprite(pSprite2->index);
            xsprite[pSprite2->extra].at18_0 = 3;
            gSpriteHit[pSprite2->extra].florhit = 0;
            gSpriteHit[pSprite2->extra].ceilhit = 0;
        }
    }
    return pSprite2;
}

SPRITE *actDropFlag(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (pSprite && pSprite->statnum < kMaxStatus && (nType == 147 || nType == 148))
    {
        pSprite2 = actDropItem(pSprite, nType);
        if (pSprite2 && gGameOptions.nGameType == 3)
        {
            evPost(pSprite2->index, 3, 1800, CALLBACK_ID_17);
        }
    }
    return pSprite2;
}

SPRITE *actDropObject(SPRITE *pSprite, int nType)
{
    SPRITE *pSprite2 = NULL;
    if (nType >= 100 && nType <= 106)
        pSprite2 = actDropKey(pSprite, nType);
    else if (nType == 147 || nType == 148)
        pSprite2 = actDropFlag(pSprite, nType);
    else if (nType >= 100 && nType < 149)
        pSprite2 = actDropItem(pSprite, nType);
    else if (nType >= 60 && nType < 81)
        pSprite2 = actDropAmmo(pSprite, nType);
    else if (nType >= 40 && nType < 51)
        pSprite2 = actDropAmmo(pSprite, nType);
    if (pSprite2)
    {
        int top, bottom;
        GetSpriteExtents(pSprite2, &top, &bottom);
        if (bottom >= pSprite2->z)
            pSprite2->z -= bottom - pSprite2->z;
    }
    return pSprite2;
}

bool actHealDude(XSPRITE *pXDude, int a2, int a3)
{
    dassert(pXDude != NULL);
    a2 <<= 4;
    a3 <<= 4;
    if (pXDude->health < a3)
    {
        SPRITE *pSprite = &qsprite[pXDude->reference];
        if (IsPlayerSprite(pSprite))
            sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, 780, pSprite->sectnum);
        pXDude->health = ClipHigh(pXDude->health+a2, a3);
        return 1;
    }
    return 0;
}

void actKillDude(int a1, SPRITE *pSprite, DAMAGE_TYPE a3, int a4)
{
    SPRITE *pSprite2 = &qsprite[a1];
    dassert(pSprite->type >= kDudeBase && pSprite->type < kDudeMax);
    int nType = pSprite->type-kDudeBase;
    int nXSprite = pSprite->extra;
    dassert(nXSprite > 0);
    XSPRITE *pXSprite = &xsprite[pSprite->extra];
    switch (pSprite->type)
    {
    case 227: // Cerberus
        seqSpawn(dudeInfo[nType].seqStartID+1, 3, nXSprite, -1);
        return;
    case 201:
    case 202:
    case 247:
    case 248:
        if (a3 == DAMAGE_TYPE_1 && pXSprite->at17_6 == 0)
        {
            pSprite->type = 240;
            aiNewState(pSprite, pXSprite, &cultistBurnGoto);
            actHealDude(pXSprite, dudeInfo[40].at2, dudeInfo[40].at2);
            return;
        }
        // no break
    case 251:
        if (a3 == DAMAGE_TYPE_1 && pXSprite->at17_6 == 0)
        {
            pSprite->type = 253;
            aiNewState(pSprite, pXSprite, &beastBurnGoto);
            actHealDude(pXSprite, dudeInfo[53].at2, dudeInfo[53].at2);
            return;
        }
        // no break
    case 245:
        if (a3 == DAMAGE_TYPE_1 && pXSprite->at17_6 == 0)
        {
            pSprite->type = 239;
            aiNewState(pSprite, pXSprite, &innocentBurnGoto);
            actHealDude(pXSprite, dudeInfo[39].at2, dudeInfo[39].at2);
            return;
        }
        break;
    }
    for (int p = connecthead; p >= 0; p = connectpoint2[p])
    {
        if (gPlayer[p].at2ee == pSprite->index && gPlayer[p].at1fe > 0)
            gPlayer[p].at2ee = -1;
    }
    if (pSprite->type != 249)
        trTriggerSprite(pSprite->index, pXSprite, 0);
    pSprite->hitag |= 7;
    if (IsPlayerSprite(pSprite2))
    {
        PLAYER *pPlayer = &gPlayer[pSprite2->index-kDudePlayer1];
        if (gGameOptions.nGameType == 1)
            pPlayer->at2c6++;
    }

    if (pXSprite->atd_3 > 0)
        actDropObject(pSprite, 100+pXSprite->atd_3-1);
    if (pXSprite->atc_0 > 0)
        actDropObject(pSprite, pXSprite->atc_0);
    if (pSprite->type == 201)
    {
        int nRand = Random(100);
        if (nRand < 10)
            actDropObject(pSprite, 42);
        else if (nRand < 50)
            actDropObject(pSprite, 69);
    }
    else if (pSprite->type == 202)
    {
        int nRand = Random(100);
        if (nRand < 10)
            actDropObject(pSprite, 41);
        else if (nRand < 50)
            actDropObject(pSprite, 67);
    }
    int nSeq;
    switch (a3)
    {
    case DAMAGE_TYPE_3:
        nSeq = 2;
        switch (pSprite->type)
        {
        case 201:
        case 202:
        case 230:
        case 239:
        case 240:
        case 245:
        case 246:
        case 247:
        case 248:
        case 249:
        case 250:
        case 252:
            sfxPlay3DSound(pSprite, 717,-1,0);
            break;
        }
        break;
    case DAMAGE_TYPE_1:
        nSeq = 3;
        sfxPlay3DSound(pSprite, 351, -1, 0);
        break;
    case DAMAGE_TYPE_5:
        switch (pSprite->type)
        {
        case 203:
        case 205:
            nSeq = 14;
            break;
        case 204:
            nSeq = 14;
            break;
        default:
            nSeq = 1;
            break;
        }
        break;
    case DAMAGE_TYPE_0:
        switch (pSprite->type)
        {
        case 201:
        case 202:
            nSeq = 1;
            break;
        default:
            nSeq = 1;
            break;
        }
        break;
    default:
        nSeq = 1;
        break;
    }

    if (!gSysRes.Lookup(dudeInfo[nType].seqStartID + nSeq, "SEQ"))
    {
        seqKill(3, nXSprite);
        gKillMgr.AddKill(pSprite);
        actPostSprite(pSprite->index, 1024);
        return;
    }

    switch (pSprite->type)
    {
    case 203:
        sfxPlay3DSound(pSprite, 1107+Random(2), -1, 0);
        if (nSeq == 2)
        {
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient1);
            int top, bottom;
            GetSpriteExtents(pSprite, &top, &bottom);
            CGibPosition gibPos(pSprite->x, pSprite->y, top);
            CGibVelocity gibVel(xvel[pSprite->index]>>1, yvel[pSprite->index]>>1, -0xccccc);
            GibSprite(pSprite, GIBTYPE_27, &gibPos, &gibVel);
        }
        else if (nSeq == 1 && Chance(0x4000))
        {
            seqSpawn(dudeInfo[nType].seqStartID+7, 3, nXSprite, nDudeToGibClient1);
            evPost(pSprite->index, 3, 0, CALLBACK_ID_5);
            sfxPlay3DSound(pSprite, 362, -1, 0);
            pXSprite->at10_0 = 35;
            pXSprite->at12_0 = 5;
            int top, bottom;
            GetSpriteExtents(pSprite, &top, &bottom);
            CGibPosition gibPos(pSprite->x, pSprite->y, top);
            CGibVelocity gibVel(xvel[pSprite->index] >> 1, yvel[pSprite->index] >> 1, -0x111111);
            GibSprite(pSprite, GIBTYPE_27, &gibPos, &gibVel);
        }
        else if (nSeq == 14)
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        else if (nSeq == 3)
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient2);
        else
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient1);
        break;
    case 201:
    case 202:
    case 247:
    case 248:
        sfxPlay3DSound(pSprite, 1018+Random(2), -1, 0);
        if (nSeq == 3)
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient2);
        else
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient1);
        break;
    case 240:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 718, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1018+Random(2), -1, 0);
        if (Chance(0x8000))
        {
            for (int i = 0; i < 3; i++)
                GibSprite(pSprite, GIBTYPE_7, NULL, NULL);
            seqSpawn(dudeInfo[nType].seqStartID+16-Random(1), 3, nXSprite, nDudeToGibClient1);
        }
        else
            seqSpawn(dudeInfo[nType].seqStartID+15, 3, nXSprite, nDudeToGibClient2);
        break;
    case 241:
        if (Chance(0x8000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1109, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1107+Random(2), -1, 0);
        if (Chance(0x8000))
        {
            seqSpawn(dudeInfo[nType].seqStartID+13, 3, nXSprite, nDudeToGibClient1);
            int top, bottom;
            GetSpriteExtents(pSprite, &top, &bottom);
            CGibPosition gibPos(pSprite->x, pSprite->y, top);
            CGibVelocity gibVel(xvel[pSprite->index]>>1, yvel[pSprite->index]>>1, -0xccccc);
            GibSprite(pSprite, GIBTYPE_27, &gibPos, &gibVel);
        }
        else
            seqSpawn(dudeInfo[nType].seqStartID+13, 3, nXSprite, nDudeToGibClient2);
        break;
    case 242:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1206, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1204+Random(2), -1, 0);
        seqSpawn(dudeInfo[4].seqStartID+10, 3, nXSprite, -1);
        break;
    case 239:
        a3 = DAMAGE_TYPE_3;
        seqSpawn(dudeInfo[nType].seqStartID+7, 3, nXSprite, nDudeToGibClient1);
        break;
    case 204:
        if (nSeq == 14)
        {
            sfxPlay3DSound(pSprite, 1206, -1, 0);
            seqSpawn(dudeInfo[nType].seqStartID+11, 3, nXSprite, -1);
            break;
        }
        sfxPlay3DSound(pSprite, 1204+Random(2), -1, 0);
        if (nSeq == 3)
            seqSpawn(dudeInfo[nType].seqStartID+10, 3, nXSprite, -1);
        else
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 206:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1405, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1403+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 207:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1455, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1453+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 210:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1605, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1603+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 211:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1305, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1303+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 212:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1905, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1903+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 213:
        if (pSprite->owner != -1)
        {
            SPRITE *pOwner = &qsprite[actSpriteOwnerToSpriteId(pSprite)];
            gDudeExtra[pOwner->extra].at6.u1.at4--;
        }
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1805, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1803+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 214:
        if (pSprite->owner != -1)
        {
            SPRITE *pOwner = &qsprite[actSpriteOwnerToSpriteId(pSprite)];
            gDudeExtra[pOwner->extra].at6.u1.at4--;
        }
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1805, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1803+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 215:
        if (pSprite->owner != -1)
        {
            SPRITE *pOwner = &qsprite[actSpriteOwnerToSpriteId(pSprite)];
            gDudeExtra[pOwner->extra].at6.u1.at4--;
        }
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1805, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1803+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 216:
        sfxPlay3DSound(pSprite, 1850, -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 217:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1705, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1703+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 218:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 1505, -1, 0);
        else
            sfxPlay3DSound(pSprite, 1503+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 219:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2005, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2003+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 220:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2105, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2103+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 221:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2205, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2203+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 222:
        if (a4 == 5)
            sfxPlay3DSound(pSprite, 2471, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2472, -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 223:
        if (a4 == 5)
            sfxPlay3DSound(pSprite, 2451, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2452, -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 224:
        sfxPlay3DSound(pSprite, 2501, -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 225:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2205, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2203+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 226:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2205, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2203+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 227:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2305, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2305+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 228:
        if (Chance(0x4000) && nSeq == 3)
            sfxPlay3DSound(pSprite, 2305, -1, 0);
        else
            sfxPlay3DSound(pSprite, 2305+Random(2), -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 229:
        sfxPlay3DSound(pSprite, 2380, -1, 0);
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    case 252:
        a3 = DAMAGE_TYPE_3;
        seqSpawn(dudeInfo[nType].seqStartID+11, 3, nXSprite, nDudeToGibClient1);
        break;
    case 251:
        sfxPlay3DSound(pSprite, 9000+Random(2), -1, 0);
        if (nSeq == 3)
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient2);
        else
            seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, nDudeToGibClient1);
        break;
    case 253:
        a3 = DAMAGE_TYPE_3;
        seqSpawn(dudeInfo[nType].seqStartID+12, 3, nXSprite, nDudeToGibClient1);
        break;
    default:
        seqSpawn(dudeInfo[nType].seqStartID+nSeq, 3, nXSprite, -1);
        break;
    }
    if (a3 == DAMAGE_TYPE_3)
    {
        DUDEINFO *pDudeInfo = &dudeInfo[pSprite->type-kDudeBase];
        for (int i = 0; i < 3; i++)
            if (pDudeInfo->at48[i] > -1)
                GibSprite(pSprite, (GIBTYPE)pDudeInfo->at48[i], NULL, NULL);
        for (int i = 0; i < 4; i++)
            fxSpawnBlood(pSprite, a4);
    }
    gKillMgr.AddKill(pSprite);
    actCheckRespawn(pSprite);
    pSprite->type = 426;
    actPostSprite(pSprite->index, 4);
}

int actDamageSprite(int nSource, SPRITE *pSprite, DAMAGE_TYPE a3, int a4)
{
    dassert(nSource < kMaxSprites);
    if (pSprite->hitag&32)
        return 0;
    int nXSprite = pSprite->extra;
    if (nXSprite <= 0)
        return 0;
    dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
    XSPRITE *pXSprite = &xsprite[nXSprite];
    dassert(pXSprite->reference == pSprite->index);
    if ((pXSprite->health == 0 && pSprite->statnum != 6) || pXSprite->at17_5)
        return 0;
    if (nSource == -1)
        nSource = pSprite->index;
    PLAYER *pSourcePlayer = NULL;
    if (IsPlayerSprite(&qsprite[nSource]))
        pSourcePlayer = &gPlayer[qsprite[nSource].type-kDudePlayer1];
    switch (pSprite->statnum)
    {
    case 6:
    {
        if (pSprite->type < kDudeBase || pSprite->type >= kDudeMax)
        {
            sprintf(buffer, "Bad Dude Failed: initial=%d type=%d %s\n", pSprite->zvel, pSprite->type, (pSprite->hitag&16) ? "RESPAWN" : "NORMAL");
            ThrowError(buffer);
        }
        dassert(pSprite->type >= kDudeBase && pSprite->type < kDudeMax);
        int nType = pSprite->type-kDudeBase;
        int nDamageFactor = dudeInfo[nType].at70[a3];
        if (!nDamageFactor)
            return 0;
        if (nDamageFactor != 256)
            a4 = mulscale8(a4, nDamageFactor);
        if (!IsPlayerSprite(pSprite))
        {
            if (!pXSprite->health)
                return 0;
            a4 = aiDamageSprite(pSprite, pXSprite, nSource, a3, a4);
            if (!pXSprite->health)
            {
                if (a3 == DAMAGE_TYPE_3 && a4 < 160)
                    a3 = DAMAGE_TYPE_0;
                actKillDude(nSource, pSprite, a3, a4);
            }
        }
        else
        {
            PLAYER *pPlayer = &gPlayer[pSprite->type-kDudePlayer1];
            if (pXSprite->health > 0 || playerSeqPlaying(pPlayer, 16))
                a4 = playerDamageSprite(nSource, pPlayer, a3, a4);
        }
        break;
    }
    case 4:
        dassert(pSprite->type >= kThingBase && pSprite->type < kThingMax);
        int nType = pSprite->type-kThingBase;
        int nDamageFactor = thingInfo[nType].at17[a3];
        if (!nDamageFactor)
            return 0;
        if (nDamageFactor != 256)
            a4 = mulscale8(a4, nDamageFactor);
        pXSprite->health = ClipLow(pXSprite->health-a4, 0);
        if (!pXSprite->health)
        {
            if (pSprite->type == 431)
            {
                GibSprite(pSprite, GIBTYPE_14, NULL, NULL);
                pXSprite->at10_0 = 0;
                pXSprite->at12_0 = 0;
                pXSprite->at14_0 = 0;
                pXSprite->at32_0 = 0;
                pXSprite->at18_2 = 0;
                pXSprite->atd_2 = 0;
                pXSprite->atf_7 = 0;
            }
            else if (!(pSprite->hitag&16))
                actPropagateSpriteOwner(pSprite, &qsprite[nSource]);
            trTriggerSprite(pSprite->index, pXSprite, 0);
            switch (pSprite->type)
            {
            case 416:
            case 417:
            case 425:
            case 426:
            case 427:
                if (a3 == 3 && pSourcePlayer && gFrameClock > pSourcePlayer->at312 && Chance(0x4000))
                {
                    sfxPlay3DSound(pSourcePlayer->pSprite, gPlayerGibThingComments[Random(10)], 0, 2);
                    pSourcePlayer->at312 = gFrameClock+3600;
                }
                break;
            case 413:
                seqSpawn(28, 3, pSprite->extra, -1);
                break;
            case 407:
                seqSpawn(12, 3, pSprite->extra, -1);
                GibSprite(pSprite, GIBTYPE_6, NULL, NULL);
                break;
            case 410:
                seqSpawn(15, 3, pSprite->extra, -1);
                break;
            case 411:
                seqSpawn(21, 3, pSprite->extra, -1);
                GibSprite(pSprite, GIBTYPE_4, NULL, NULL);
                break;
            case 412:
                switch (pXSprite->at10_0)
                {
                case -1:
                    GibSprite(pSprite, GIBTYPE_14, NULL, NULL);
                    sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, 312, pSprite->sectnum);
                    actPostSprite(pSprite->index, 1024);
                    break;
                case 0:
                    seqSpawn(25, 3, pSprite->extra, nTreeToGibClient);
                    sfxPlay3DSound(pSprite, 351, -1, 0);
                    break;
                case 1:
                    seqSpawn(26, 3, pSprite->extra, nTreeToGibClient);
                    sfxPlay3DSound(pSprite, 351, -1, 0);
                    break;
                }
                break;
            case 422:
                if (seqGetStatus(3, nXSprite) < 0)
                    seqSpawn(19, 3, pSprite->extra, -1);
                break;
            }
        }
        break;
    }
    return a4>>4;
}

void actHitcodeToData(int a1, HITINFO *pHitInfo, int *a3, SPRITE **a4, XSPRITE **a5, int *a6, WALL **a7, XWALL **a8, int *a9, SECTOR **a10, XSECTOR **a11)
{
    dassert(pHitInfo != NULL);
    int nSprite = -1;
    SPRITE *pSprite = NULL;
    XSPRITE *pXSprite = NULL;
    int nWall = -1;
    WALL *pWall = NULL;
    XWALL *pXWall = NULL;
    int nSector = -1;
    SECTOR *pSector = NULL;
    XSECTOR *pXSector = NULL;
    switch (a1)
    {
    case 3:
    case 5:
        nSprite = pHitInfo->hitsprite;
        dassert(nSprite >= 0 && nSprite < kMaxSprites);
        pSprite = &qsprite[nSprite];
        if (pSprite->extra > 0)
            pXSprite = &xsprite[pSprite->extra];
        break;
    case 0:
    case 4:
        nWall = pHitInfo->hitwall;
        dassert(nWall >= 0 && nWall < kMaxWalls);
        pWall = &qwall[nWall];
        if (pWall->extra > 0)
            pXWall = &xwall[pWall->extra];
        break;
    case 1:
    case 2:
    case 6:
        nSector = pHitInfo->hitsect;
        dassert(nSector >= 0 && nSector < kMaxSectors);
        pSector = &qsector[nSector];
        if (pSector->extra > 0)
            pXSector = &xsector[pSector->extra];
        break;
    }
    if (a3)
        *a3 = nSprite;
    if (a4)
        *a4 = pSprite;
    if (a5)
        *a5 = pXSprite;
    if (a6)
        *a6 = nWall;
    if (a7)
        *a7 = pWall;
    if (a8)
        *a8 = pXWall;
    if (a9)
        *a9 = nSector;
    if (a10)
        *a10 = pSector;
    if (a11)
        *a11 = pXSector;
}

void actImpactMissile(SPRITE *pMissile, int a2)
{
    int nXMissile = pMissile->extra;
    dassert(nXMissile > 0 && nXMissile < kMaxXSprites);
    XSPRITE *pXMissile = &xsprite[pMissile->extra];
    int nSpriteHit = -1;
    SPRITE *pSpriteHit = NULL;
    XSPRITE *pXSpriteHit = NULL;
    int nWallHit = -1;
    WALL *pWallHit = NULL;
    XWALL *pXWallHit = NULL;
    int nSectorHit = -1;
    SECTOR *pSectorHit = NULL;
    XSECTOR *pXSectorHit = NULL;
    actHitcodeToData(a2, &gHitInfo, &nSpriteHit, &pSpriteHit, &pXSpriteHit, &nWallHit, &pWallHit, &pXWallHit, &nSectorHit, &pSectorHit, &pXSectorHit);
    THINGINFO *pThingInfo = NULL;
    DUDEINFO *pDudeInfo = NULL;
    if (a2 == 3 && pSpriteHit)
    {
        if (pSpriteHit->statnum == 4)
        {
            dassert(pXSpriteHit != NULL);
            pThingInfo = &thingInfo[pSpriteHit->type-kThingBase];
        }
        else if (pSpriteHit->statnum == 6)
        {
            dassert(pXSpriteHit != NULL);
            pDudeInfo = &dudeInfo[pSpriteHit->type-kDudeBase];
        }
    }
    switch (pMissile->type)
    {
    case 315:
        if (a2 == 3 && pSpriteHit && (pThingInfo || pDudeInfo))
        {
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            DAMAGE_TYPE rand1 = (DAMAGE_TYPE)Random(7);
            int rand2 = (7+Random(7))<<4;
            actDamageSprite(nOwner, pSpriteHit, rand1, rand2);
            if ((pThingInfo && pThingInfo->at17[DAMAGE_TYPE_1] != 0) || (pDudeInfo && pDudeInfo->at70[DAMAGE_TYPE_1] != 0))
                actBurnSprite(pMissile->owner, pXSpriteHit, 360);
        }
        if (pMissile->extra > 0)
        {
            actPostSprite(pMissile->index, 0);
            if (pMissile->ang == 1024)
                sfxPlay3DSound(pMissile, 307, -1, 0);
            pMissile->type = 0;
            seqSpawn(9, 3, pMissile->extra, -1);
        }
        else
        {
            actPostSprite(pMissile->index, 1024);
        }
        break;
    case 302:
        sub_51340(pMissile, a2);
        if ((a2 == 0 || a2 == 4) && pWallHit)
        {
            SPRITE *pFX = gFX.fxSpawn(FX_52, pMissile->sectnum, pMissile->x, pMissile->y, pMissile->z, 0);
            if (pFX)
                pFX->ang = (GetWallAngle(nWallHit)+512)&2047;
        }
        GibSprite(pMissile, GIBTYPE_24, NULL, NULL);
        actPostSprite(pMissile->index, 1024);
        break;
    case 309:
        seqKill(3, nXMissile);
        if (a2 == 3 && pSpriteHit && (pThingInfo || pDudeInfo))
        {
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDamage = (15+Random(7))<<4;
            actDamageSprite(nOwner, pSpriteHit, DAMAGE_TYPE_2, nDamage);
        }
        actPostSprite(pMissile->index, 1024);
        break;
    case 311:
        sfxKill3DSound(pMissile, -1, -1);
        sfxPlay3DSound(pMissile->x, pMissile->y, pMissile->z, 306, pMissile->sectnum);
        GibSprite(pMissile, GIBTYPE_6, NULL, NULL);
        if (a2 == 3 && pSpriteHit && (pThingInfo || pDudeInfo))
        {
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDamage = (25+Random(20))<<4;
            actDamageSprite(nOwner, pSpriteHit, DAMAGE_TYPE_5, nDamage);
        }
        actPostSprite(pMissile->index, 1024);
        break;
    case 316:
    case 317:
        sfxKill3DSound(pMissile, -1, -1);
        sfxPlay3DSound(pMissile->x, pMissile->y, pMissile->z, 306, pMissile->sectnum);
        GibSprite(pMissile, GIBTYPE_6, NULL, NULL);
        if (a2 == 3 && pSpriteHit && (pThingInfo || pDudeInfo))
        {
            if (pDudeInfo)
            {
            }
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDmgMul = 3;
            if (pMissile->type == 317)
                nDmgMul = 6;
            int nDamage = (nDmgMul+Random(nDmgMul))<<4;
            actDamageSprite(nOwner, pSpriteHit, DAMAGE_TYPE_5, nDamage);
        }
        actPostSprite(pMissile->index, 1024);
        break;
    case 305:
    case 312:
        if (a2 == 3 && pSpriteHit && (pThingInfo || pDudeInfo))
        {
            if (pThingInfo && pSpriteHit->type == 400 && pXSpriteHit->at2c_0 == 0)
                evPost(nSpriteHit, 3, 0, CALLBACK_ID_0);
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDamage = (50+Random(50))<<4;
            actDamageSprite(nOwner, pSpriteHit, DAMAGE_TYPE_2, nDamage);
        }
        actExplodeSprite(pMissile);
        break;
    case 303:
        sfxKill3DSound(pMissile, -1, -1);
        actExplodeSprite(pMissile);
        break;
    case 301:
        sfxKill3DSound(pMissile, -1, -1);
        if (a2 == 3 && pSpriteHit)
        {
            if (pThingInfo || pDudeInfo)
            {
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                if ((pThingInfo && pThingInfo->at17[DAMAGE_TYPE_1] != 0) || (pDudeInfo && pDudeInfo->at70[DAMAGE_TYPE_1] != 0))
                {
                    if (pThingInfo && pSpriteHit->type == 400 && pXSpriteHit->at2c_0 == 0)
                        evPost(nSpriteHit, 3, 0, CALLBACK_ID_0);
                    actBurnSprite(pMissile->owner, pXSpriteHit, 480);
                    sub_2A620(nOwner, pMissile->x, pMissile->y, pMissile->z, pMissile->sectnum, 16, 20, 10, DAMAGE_TYPE_2, 6, 480, 0, 0);
                }
                else
                {
                    int nDamage = (20+Random(10))<<4;
                    actDamageSprite(nOwner, pSpriteHit, DAMAGE_TYPE_2, nDamage);
                }
                if (surfType[pSpriteHit->picnum] == 4)
                {
                    pMissile->picnum = 2123;
                    pXMissile->target = nSpriteHit;
                    pXMissile->at28_0 = pMissile->z-pSpriteHit->z;
                    pXMissile->at16_0 = getangle(pMissile->x-pSpriteHit->x, pMissile->y-pSpriteHit->y)-pSpriteHit->ang;
                    pXMissile->at1_6 = 1;
                    actPostSprite(pMissile->index, 14);
                    pMissile->cstat &= ~257;
                    break;
                }
            }
        }
        GibSprite(pMissile, GIBTYPE_17, NULL, NULL);
        actPostSprite(pMissile->index, 1024);
        break;
    case 304:
    case 308:
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            if (pObject->extra > 0)
            {
                XSPRITE *pXObject = &xsprite[pObject->extra];
                if ((pObject->statnum == 4 || pObject->statnum == 6) && pXObject->at2c_0 == 0)
                    evPost(nObject, 3, 0, CALLBACK_ID_0);
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                actBurnSprite(pMissile->owner, pXObject, (4+gGameOptions.nDifficulty)<<2);
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_1, 8);
            }
        }
        break;
    case 313:
        actExplodeSprite(pMissile);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            if (pObject->extra > 0)
            {
                XSPRITE *pXObject = &xsprite[pObject->extra];
                if ((pObject->statnum == 4 || pObject->statnum == 6) && pXObject->at2c_0 == 0)
                    evPost(nObject, 3, 0, CALLBACK_ID_0);
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                actBurnSprite(pMissile->owner, pXObject, (4+gGameOptions.nDifficulty)<<2);
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_1, 8);
                int nDamage = (25+Random(10))<<4;
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_2, nDamage);
            }
        }
        actExplodeSprite(pMissile);
        break;
    case 314:
        actExplodeSprite(pMissile);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            if (pObject->extra > 0)
            {
                XSPRITE *pXObject = &xsprite[pObject->extra];
                if ((pObject->statnum == 4 || pObject->statnum == 6) && pXObject->at2c_0 == 0)
                    evPost(nObject, 3, 0, CALLBACK_ID_0);
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                actBurnSprite(pMissile->owner, pXObject, 32);
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_5, 12);
                int nDamage = (25+Random(10))<<4;
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_2, nDamage);
            }
        }
        actExplodeSprite(pMissile);
        break;
    case 307:
        sfxKill3DSound(pMissile, -1, -1);
        sfxPlay3DSound(pMissile->x, pMissile->y, pMissile->z, 522, pMissile->sectnum);
        actPostSprite(pMissile->index, 15);
        seqSpawn(20, 3, pMissile->extra, -1);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            if (pObject->statnum == 6)
            {
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                int nDamage = (25+Random(10))<<4;
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_5, nDamage);
            }
        }
        break;
    case 300:
        actPostSprite(pMissile->index, 15);
        pMissile->cstat &= ~16;
        pMissile->type = 0;
        seqSpawn(20, 3, pMissile->extra, -1);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            if (pObject->statnum == 6)
            {
                int nOwner = actSpriteOwnerToSpriteId(pMissile);
                int nDamage = (10+Random(10))<<4;
                actDamageSprite(nOwner, pObject, DAMAGE_TYPE_5, nDamage);
                SPRITE *pOwner = &qsprite[nObject];
                XSPRITE *pXOwner = &xsprite[pOwner->extra];
                int nType = pOwner->type-kDudeBase;
                if (pXOwner->health > 0)
                    actHealDude(pXOwner, 10, dudeInfo[nType].at2);
            }
        }
        break;
    case 306:
        sfxKill3DSound(pMissile, -1, -1);
        sfxPlay3DSound(pMissile->x, pMissile->y, pMissile->z, 518, pMissile->sectnum);
        GibSprite(pMissile, (a2 == 2) ? GIBTYPE_23 : GIBTYPE_22, NULL, NULL);
        evKill(pMissile->index, 3);
        seqKill(3, nXMissile);
        actPostSprite(pMissile->index, 1024);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDamage = (15+Random(10))<<4;
            actDamageSprite(nOwner, pObject, DAMAGE_TYPE_6, nDamage);
        }
        break;
    case 310:
    default:
        seqKill(3, nXMissile);
        actPostSprite(pMissile->index, 1024);
        if (a2 == 3)
        {
            int nObject = gHitInfo.hitsprite;
            dassert(nObject >= 0 && nObject < kMaxSprites);
            SPRITE *pObject = &qsprite[nObject];
            int nOwner = actSpriteOwnerToSpriteId(pMissile);
            int nDamage = (10+Random(10))<<4;
            actDamageSprite(nOwner, pObject, DAMAGE_TYPE_0, nDamage);
        }
        break;
    }
    pMissile->cstat &= ~257;
}

void actKickObject(SPRITE *pSprite1, SPRITE *pSprite2)
{
    int nSprite1 = pSprite1->index;
    int nSprite2 = pSprite2->index;
    int nSpeed = ClipLow(approxDist(xvel[nSprite1], yvel[nSprite1])*2, 0xaaaaa);
    xvel[nSprite2] = mulscale30(nSpeed, Cos(pSprite1->ang+Random2(85)));
    yvel[nSprite2] = mulscale30(nSpeed, Sin(pSprite1->ang+Random2(85)));
    zvel[nSprite2] = mulscale(nSpeed, -0x2000, 14);
    pSprite2->hitag = 7;
}

void actTouchFloor(SPRITE *pSprite, int nSector)
{
    dassert(pSprite != NULL);
    dassert(nSector >= 0 && nSector < kMaxSectors);
    SECTOR *pSector = &qsector[nSector];
    XSECTOR *pXSector = NULL;
    if (pSector->extra > 0)
        pXSector = &xsector[pSector->extra];

    if (pXSector && (pSector->lotag == 618 || pXSector->at33_1 > 0))
    {
        DAMAGE_TYPE nDamageType;
        if (pSector->lotag == 618)
            nDamageType = (DAMAGE_TYPE)ClipRange(pXSector->at33_1, DAMAGE_TYPE_0, DAMAGE_TYPE_6);
        else
            nDamageType = (DAMAGE_TYPE)ClipRange(pXSector->at33_1-1, DAMAGE_TYPE_0, DAMAGE_TYPE_6);
        int nDamage;
        if (pXSector->at4_0)
            nDamage = ClipRange(pXSector->at4_0, 0, 1000);
        else
            nDamage = 1000;
        actDamageSprite(pSprite->index, pSprite, nDamageType, nDamage);
    }
    if (tileGetSurfType(nSector+0x4000) == 14)
    {
        actDamageSprite(pSprite->index, pSprite, DAMAGE_TYPE_1, 16);
        sfxPlay3DSound(pSprite, 352, 5, 2);
    }
}

void ProcessTouchObjects(SPRITE *pSprite, int nXSprite)
{
    int nSprite = pSprite->index;
    XSPRITE *pXSprite = &xsprite[nXSprite];
    SPRITEHIT *pSpriteHit = &gSpriteHit[nXSprite];
    PLAYER *pPlayer = NULL;
    if (IsPlayerSprite(pSprite))
        pPlayer = &gPlayer[pSprite->type-kDudePlayer1];
    int nHitSprite = pSpriteHit->ceilhit & 0x1fff;
    switch (pSpriteHit->ceilhit&0xe000)
    {
    case 0x8000:
        break;
    case 0xc000:
        if (sprite[nHitSprite].extra > 0)
        {
            SPRITE *pSprite2 = &qsprite[nHitSprite];
            XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
            if ((pSprite2->statnum == 4 || pSprite2->statnum == 6) && (xvel[nSprite] != 0 || yvel[nSprite] != 0 || zvel[nSprite] != 0))
            {
                if (pSprite2->statnum == 4)
                {
                    int nType = pSprite2->type-kThingBase;
                    THINGINFO *pThingInfo = &thingInfo[nType];
                    if (pThingInfo->at5&1)
                        pSprite2->hitag |= 1;
                    if (pThingInfo->at5&2)
                        pSprite2->hitag |= 4;
                    // Inlined ?
                    xvel[pSprite2->index] += mulscale(4, pSprite->x-sprite[nSprite].x, 2);
                    yvel[pSprite2->index] += mulscale(4, pSprite->y-sprite[nSprite].y, 2);
                }
                else
                {
                    pSprite2->hitag |= 5;
                    xvel[pSprite2->index] += mulscale(4, pSprite->x-sprite[nSprite].x, 2);
                    yvel[pSprite2->index] += mulscale(4, pSprite->y-sprite[nSprite].y, 2);
                    if (pSprite2->type == 229)
                        if (!IsPlayerSprite(pSprite) || gPlayer[pSprite->type-kDudePlayer1].at31a == 0)
                            actDamageSprite(pSprite2->index, pSprite, DAMAGE_TYPE_3, pXSprite->health<<2);
                }
            }
            if (pSprite2->type == 454)
            {
                if (pXSprite2->at1_6)
                {
                    pXSprite2->at10_0 = 1;
                    pXSprite2->at12_0 = ClipHigh(pXSprite2->at12_0+8, 600);
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_2, 16);
                }
                else
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_2, 1);
            }
        }
        break;
    }
    nHitSprite = pSpriteHit->hit & 0x1fff;
    switch (pSpriteHit->hit&0xe000)
    {
    case 0x8000:
        break;
    case 0xc000:
        if (sprite[nHitSprite].extra > 0)
        {
            SPRITE *pSprite2 = &qsprite[nHitSprite];
            //XSPRITE *pXSprite2 = &Xsprite[pSprite2->extra];
            switch (pSprite2->type)
            {
            case 415:
                actKickObject(pSprite, pSprite2);
                break;
            case 427:
                sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, 357, pSprite->sectnum);
                actKickObject(pSprite, pSprite2);
                actDamageSprite(-1, pSprite2, DAMAGE_TYPE_0, 80);
                break;
            case 239:
            case 240:
            case 241:
            case 242:
                // This does not make sense
                pXSprite->at2c_0 = ClipLow(pXSprite->at2c_0-4, 0);
                actDamageSprite(actOwnerIdToSpriteId(pXSprite->at2e_0), pSprite, DAMAGE_TYPE_1, 8);
                break;
            }
        }
        break;
    }
    nHitSprite = pSpriteHit->florhit & 0x1fff;
    switch (pSpriteHit->florhit&0xe000)
    {
    case 0x8000:
        break;
    case 0x4000:
        actTouchFloor(pSprite, nHitSprite);
        break;
    case 0xc000:
        if (sprite[nHitSprite].extra > 0)
        {
            SPRITE *pSprite2 = &qsprite[nHitSprite];
            XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
            switch (pSprite2->type)
            {
            case 415:
                if (pPlayer)
                {
                    if (pPlayer->at30e > gFrameClock)
                        return;
                    pPlayer->at30e = gFrameClock+60;
                }
                actKickObject(pSprite, pSprite2);
                sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, 357, pSprite->sectnum);
                sfxPlay3DSound(pSprite, 374, 0, 0);
                break;
            case 427:
                if (pPlayer)
                {
                    if (pPlayer->at30e > gFrameClock)
                        return;
                    pPlayer->at30e = gFrameClock+60;
                }
                actKickObject(pSprite, pSprite2);
                sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, 357, pSprite->sectnum);
                actDamageSprite(-1, pSprite2, DAMAGE_TYPE_0, 80);
                break;
            case 454:
                if (pXSprite2->at1_6)
                {
                    pXSprite2->at10_0 = 1;
                    pXSprite2->at12_0 = ClipHigh(pXSprite2->at12_0+8, 600);
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_2, 16);
                }
                else
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_2, 1);
                break;
            case 201:
            case 202:
            case 203:
            case 204:
            case 205:
            case 206:
            case 207:
            case 210:
            case 211:
            case 212:
            case 213:
            case 214:
            case 215:
            case 217:
            case 219:
            case 220:
            case 221:
            case 222:
            case 223:
            case 224:
            case 225:
            case 226:
            case 227:
            case 228:
            case 229:
            case 231:
            case 232:
            case 233:
            case 234:
            case 235:
            case 236:
            case 237:
            case 238:
                if (pPlayer)
                    actDamageSprite(nSprite, pSprite2,DAMAGE_TYPE_2, 8);
                break;
            }
        }
        break;
    }
}

void actAirDrag(SPRITE *pSprite, int a2)
{
    int vbp = 0;
    int v4 = 0;
    int nSector = pSprite->sectnum;
    dassert(nSector >= 0 && nSector < kMaxSectors);
    SECTOR *pSector = &qsector[nSector];
    int nXSector = pSector->extra;
    if (nXSector > 0)
    {
        dassert(nXSector < kMaxXSectors);
        XSECTOR *pXSector = &xsector[nXSector];
        if (pXSector->at31_1 && (pXSector->at37_6 || pXSector->at1_7))
        {
            int vcx = pXSector->at35_1<<12;
            if (!pXSector->at37_6 && pXSector->at1_7)
                vcx = mulscale16(vcx, pXSector->at1_7);
            vbp = mulscale30(vcx, Cos(pXSector->at36_3));
            v4 = mulscale30(vcx, Sin(pXSector->at36_3));
        }
    }
    xvel[pSprite->index] += mulscale16(vbp-xvel[pSprite->index], a2);
    yvel[pSprite->index] += mulscale16(v4-yvel[pSprite->index], a2);
    zvel[pSprite->index] -= mulscale16(zvel[pSprite->index], a2);
}

int MoveThing(SPRITE *pSprite)
{
    int nXSprite = pSprite->extra;
    dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pSprite->index;
    int v8 = 0;
    dassert(pSprite->type >= kThingBase && pSprite->type < kThingMax);
    THINGINFO *pThingInfo = &thingInfo[pSprite->type-kThingBase];
    int nSector = pSprite->sectnum;
    dassert(nSector >= 0 && nSector < kMaxSectors);
    int top, bottom;
    GetSpriteExtents(pSprite, &top, &bottom);
    if (xvel[nSprite] || yvel[nSprite])
    {
        short bakCstat = pSprite->cstat;
        pSprite->cstat &= ~257;
        v8 = gSpriteHit[nXSprite].hit = ClipMove(&pSprite->x, &pSprite->y, &pSprite->z, &nSector, xvel[nSprite]>>12, yvel[nSprite]>>12, pSprite->clipdist<<2, (pSprite->z-top)/4, (bottom-pSprite->z)/4, CLIPMASK0);
        pSprite->cstat = bakCstat;
        dassert(nSector >= 0);
        if (pSprite->sectnum != nSector)
        {
            dassert(nSector >= 0 && nSector < kMaxSectors);
            ChangeSpriteSect(nSprite, nSector);
        }
        if ((gSpriteHit[nXSprite].hit&0xe000) == 0x8000)
        {
            int nHitWall = gSpriteHit[nXSprite].hit&0x1fff;
            actWallBounceVector((long*)&xvel[nSprite], (long*)&yvel[nSprite], nHitWall, pThingInfo->at7);
            switch (pSprite->type)
            {
            case 427:
                sfxPlay3DSound(pSprite, 607, 0, 0);
                actDamageSprite(-1, pSprite, DAMAGE_TYPE_0, 80);
                break;
            case 415:
                sfxPlay3DSound(pSprite, 374, 0, 0);
                break;
            }
        }
    }
    else
    {
        dassert(nSector >= 0 && nSector < kMaxSectors);
        FindSector(pSprite->x, pSprite->y, pSprite->z, &nSector);
    }
    if (zvel[nSprite])
        pSprite->z += zvel[nSprite]>>8;
    long ceilZ, ceilHit, floorZ, floorHit;
    GetZRange(pSprite, &ceilZ, &ceilHit, &floorZ, &floorHit, pSprite->clipdist<<2, CLIPMASK0);
    GetSpriteExtents(pSprite, &top, &bottom);
    if ((pSprite->hitag & 2) && bottom < floorZ)
    {
        pSprite->z += 455;
        zvel[nSprite] += 58254;
        if (pSprite->type == 427)
        {
            SPRITE *pFX = gFX.fxSpawn(FX_27, pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0);
            if (pFX)
            {
                long v34 = (gFrameClock*3)&2047;
                long v30 = (gFrameClock*5)&2047;
                long vbx = (gFrameClock*11)&2047;
                long v2c = 0x44444;
                long v28 = 0;
                long v24 = 0;
                RotateVector(&v2c,&v28,vbx);
                RotateVector(&v2c,&v24,v30);
                RotateVector(&v28,&v24,v34);
                xvel[pFX->index] += v2c;
                yvel[pFX->index] += v28;
                zvel[pFX->index] += v24;
            }
        }
    }
    if (CheckLink(pSprite))
        GetZRange(pSprite, &ceilZ, &ceilHit, &floorZ, &floorHit, pSprite->clipdist<<2, CLIPMASK0);
    GetSpriteExtents(pSprite, &top, &bottom);
    if (bottom >= floorZ)
    {
        actTouchFloor(pSprite, pSprite->sectnum);
        gSpriteHit[nXSprite].florhit = floorHit;
        pSprite->z += floorZ-bottom;
        int v20 = zvel[nSprite]-velFloor[pSprite->sectnum];
        if (v20 > 0)
        {
            pSprite->hitag |= 4;
            int vax = actFloorBounceVector((long*)&xvel[nSprite], (long*)&yvel[nSprite], (long*)&v20, pSprite->sectnum, pThingInfo->at7);
            int nDamage = mulscale(vax, vax, 30)-pThingInfo->atb;
            if (nDamage > 0)
                actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_0, nDamage);
            zvel[nSprite] = v20;
            if (velFloor[pSprite->sectnum] == 0 && klabs(zvel[nSprite]) < 0x10000)
            {
                zvel[nSprite] = 0;
                pSprite->hitag &= ~4;
            }
            switch (pSprite->type)
            {
            case 428:
                if (zvel[nSprite] == 0 || Chance(0xA000))
                    sub_2AA94(pSprite, pXSprite);
                break;
            case 427:
                if (klabs(zvel[nSprite]) > 0x80000)
                {
                    sfxPlay3DSound(pSprite, 607, 0, 0);
                    actDamageSprite(-1, pSprite, DAMAGE_TYPE_0, 80);
                }
                break;
            case 415:
                if (klabs(zvel[nSprite]) > 0x80000)
                    sfxPlay3DSound(pSprite, 374, 0, 0);
                break;
            }
            v8 = 0x4000|nSector;
        }
        else if (zvel[nSprite] == 0)
            pSprite->hitag &= ~4;
    }
    else
    {
        gSpriteHit[nXSprite].florhit = 0;
        if (pSprite->hitag&2)
            pSprite->hitag |= 4;
    }
    if (top <= ceilZ)
    {
        gSpriteHit[nXSprite].ceilhit = ceilHit;
        pSprite->z += ClipLow(ceilZ-top, 0);
        if (zvel[nSprite] < 0)
        {
            xvel[nSprite] = mulscale16(xvel[nSprite], 0xc000);
            yvel[nSprite] = mulscale16(yvel[nSprite], 0xc000);
            zvel[nSprite] = mulscale16(-zvel[nSprite], 0x4000);
            switch (pSprite->type)
            {
            case 427:
                if (klabs(zvel[nSprite]) > 0x80000)
                {
                    sfxPlay3DSound(pSprite, 607, 0, 0);
                    actDamageSprite(-1, pSprite, DAMAGE_TYPE_0, 80);
                }
                break;
            case 415:
                if (klabs(zvel[nSprite]) > 0x80000)
                    sfxPlay3DSound(pSprite, 374, 0, 0);
                break;
            }
        }
    }
    else
        gSpriteHit[nXSprite].ceilhit = 0;
    if (bottom >= floorZ)
    {
        int nVel = approxDist(xvel[nSprite], yvel[nSprite]);
        int nVelClipped = ClipHigh(nVel, 0x11111);
        if ((floorHit & 0xe000) == 0xc000)
        {
            int nHitSprite = floorHit & 0x1fff;
            if ((sprite[nHitSprite].cstat & 0x30) == 0)
            {
                xvel[nSprite] += mulscale(4, pSprite->x - sprite[nHitSprite].x, 2);
                yvel[nSprite] += mulscale(4, pSprite->y - sprite[nHitSprite].y, 2);
                v8 = gSpriteHit[nXSprite].hit;
            }
        }
        if (nVel > 0)
        {
            int t = divscale16(nVelClipped, nVel);
            xvel[nSprite] -= mulscale16(t, xvel[nSprite]);
            yvel[nSprite] -= mulscale16(t, yvel[nSprite]);
        }
    }
    if (xvel[nSprite] || yvel[nSprite])
        pSprite->ang = getangle(xvel[nSprite], yvel[nSprite]);
    return v8;
}

void MoveDude(SPRITE *pSprite)
{
    int nXSprite = pSprite->extra;
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pSprite->index;
    PLAYER *pPlayer = NULL;
    if (IsPlayerSprite(pSprite))
        pPlayer = &gPlayer[pSprite->type-kDudePlayer1];
    dassert(pSprite->type >= kDudeBase && pSprite->type < kDudeMax);
    DUDEINFO *pDudeInfo = &dudeInfo[pSprite->type-kDudeBase];
    int top, bottom;
    GetSpriteExtents(pSprite, &top, &bottom);
    int bz = (bottom-pSprite->z)/4;
    int tz = (pSprite->z-top)/4;
    int wd = pSprite->clipdist<<2;
    int nSector = pSprite->sectnum;
    dassert(nSector >= 0 && nSector < kMaxSectors);
    if (xvel[nSprite] || yvel[nSprite])
    {
        if (pPlayer && gNoClip)
        {
            pSprite->x += xvel[nSprite]>>12;
            pSprite->y += yvel[nSprite]>>12;
            if (!FindSector(pSprite->x, pSprite->y, &nSector))
                nSector = pSprite->sectnum;
        }
        else
        {
            short bakCstat = pSprite->cstat;
            pSprite->cstat &= ~257;
            gSpriteHit[nXSprite].hit = ClipMove(&pSprite->x, &pSprite->y, &pSprite->z, &nSector, xvel[nSprite]>>12, yvel[nSprite]>>12, wd, tz, bz, 0x13001);
            if (nSector == -1)
            {
                nSector = pSprite->sectnum;
                if (pSprite->statnum == 6 || pSprite->statnum == 4)
                    actDamageSprite(pSprite->index, pSprite, DAMAGE_TYPE_0, 1000<<4);
            }
            if (sector[nSector].lotag >= 612 && sector[nSector].lotag <= 617)
            {
                short nSector2 = nSector;
                if (pushmove_old((int32_t*)&pSprite->x, (int32_t*)&pSprite->y, (int32_t*)&pSprite->z, &nSector2, wd, tz, bz, CLIPMASK0) == -1)
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_0, 1000 << 4);
                if (nSector2 != -1)
                    nSector = nSector2;
            }
            dassert(nSector >= 0);
            pSprite->cstat = bakCstat;
        }
        switch (gSpriteHit[nXSprite].hit&0xe000)
        {
        case 0xc000:
        {
            int nHitSprite = gSpriteHit[nXSprite].hit&0x1fff;
            SPRITE *pHitSprite = &qsprite[nHitSprite];
            XSPRITE *pHitXSprite = NULL;
            // Should be pHitSprite here
            if (pSprite->extra > 0)
                pHitXSprite = &xsprite[pHitSprite->extra];
            int nOwner = actSpriteOwnerToSpriteId(pHitSprite);
            if (pHitSprite->statnum == 5 && !(pHitSprite->hitag&32) && pSprite->index != nOwner)
            {
                HITINFO hitInfo = gHitInfo;
                gHitInfo.hitsprite = nSprite;
                actImpactMissile(pHitSprite, 3);
                gHitInfo = hitInfo;
            }
            if (pHitXSprite && pHitXSprite->ate_2 && !pHitXSprite->at1_6 && !pHitXSprite->atd_2)
                trTriggerSprite(nHitSprite, pHitXSprite, 33);
            if (pDudeInfo->at37 && pHitXSprite && pHitXSprite->atd_6 && !pHitXSprite->atd_3 && !pHitXSprite->atf_7 && !pHitXSprite->at1_6 && !pHitXSprite->at1_7 && !pPlayer)
                trTriggerSprite(nHitSprite, pHitXSprite, 30);
            break;
        }
        case 0x8000:
        {
            int nHitWall = gSpriteHit[nXSprite].hit&0x1fff;
            WALL *pHitWall = &qwall[nHitWall];
            XWALL *pHitXWall = NULL;
            if (pHitWall->extra > 0)
                pHitXWall = &xwall[pHitWall->extra];
            if (pDudeInfo->at37 && pHitXWall && pHitXWall->at10_5 && !pHitXWall->at10_2 && !pHitXWall->at13_3 && !pHitXWall->at1_6 && !pHitXWall->at1_7 && !pPlayer)
                trTriggerWall(nHitWall, pHitXWall, 50);
            if (pHitWall->nextsector != -1)
            {
                SECTOR *pHitSector = &qsector[pHitWall->nextsector];
                XSECTOR *pHitXSector = NULL;
                if (pHitSector->extra > 0)
                    pHitXSector = &xsector[pHitSector->extra];
                if (pDudeInfo->at37 && pHitXSector && pHitXSector->at17_7 && !pHitXSector->at16_7 && !pHitXSector->at37_7 && !pHitXSector->at1_6 && !pHitXSector->at1_7 && !pPlayer)
                    trTriggerSector(pHitWall->nextsector, pHitXSector, 40);
                if (top < pHitSector->ceilingz || bottom > pHitSector->floorz)
                {
                    // ???
                }
            }
            actWallBounceVector((long*)&xvel[nSprite], (long*)&yvel[nSprite], nHitWall, 0);
            break;
        }
        }
    }
    else
    {
        dassert(nSector >= 0 && nSector < kMaxSectors);
        FindSector(pSprite->x, pSprite->y, pSprite->z, &nSector);
    }
    if (pSprite->sectnum != nSector)
    {
        dassert(nSector >= 0 && nSector < kMaxSectors);
        XSECTOR *pXSector;
        int nXSector = sector[pSprite->sectnum].extra;
        if (nXSector > 0)
            pXSector = &xsector[nXSector];
        else
            pXSector = NULL;
        if (pXSector && pXSector->at17_6 && (pPlayer || !pXSector->at37_7))
            trTriggerSector(pSprite->sectnum, pXSector, 43);
        ChangeSpriteSect(nSprite, nSector);
        nXSector = sector[nSector].extra;
        if (nXSector > 0)
            pXSector = &xsector[nXSector];
        else
            pXSector = NULL;
        if (pXSector && pXSector->at17_5 && (pPlayer || !pXSector->at37_7))
        {
            if (sector[nSector].lotag == 604)
            {
                if (pPlayer)
                    pXSector->at4_0 = nSprite;
                else
                    pXSector->at4_0 = -1;
            }
            trTriggerSector(nSector, pXSector, 42);
        }
        nSector = pSprite->sectnum;
    }
    char bUnderwater = 0;
    char bDepth = 0;
    if (sector[nSector].extra > 0)
    {
        XSECTOR *pXSector = &xsector[sector[nSector].extra];
        if (pXSector->at13_4)
            bUnderwater = 1;
        if (pXSector->at13_5)
            bDepth = 1;
    }
    int nUpperLink = gUpperLink[nSector];
    int nLowerLink = gLowerLink[nSector];
    if (nUpperLink >= 0 && (qsprite[nUpperLink].type == 9 || qsprite[nUpperLink].type == 13))
        bDepth = 1;
    if (nLowerLink >= 0 && (qsprite[nLowerLink].type == 10 || qsprite[nLowerLink].type == 14))
        bDepth = 1;
    if (pPlayer)
        wd += 16;
    if (zvel[nSprite])
        pSprite->z += zvel[nSprite]>>8;
    long ceilZ, ceilHit, floorZ, floorHit;
    GetZRange(pSprite, &ceilZ, &ceilHit, &floorZ, &floorHit, wd, 0x13001);
    GetSpriteExtents(pSprite, &top, &bottom);
    if (pSprite->hitag & 2)
    {
        int vc = 58254;
        if (bDepth)
        {
            if (bUnderwater)
            {
                int cz = getceilzofslope(nSector, pSprite->x, pSprite->y);
                if (cz > top)
                    vc += ((bottom-cz)*-80099) / (bottom-top);
                else
                    vc = 0;
            }
            else
            {
                int fz = getflorzofslope(nSector, pSprite->x, pSprite->y);
                if (fz < bottom)
                    vc += ((bottom-fz)*-80099) / (bottom-top);
            }
        }
        else
        {
            if (bUnderwater)
                vc = 0;
            else if (bottom >= floorZ)
                vc =  0;
        }
        if (vc)
        {
            pSprite->z += ((vc*4)/2)>>8;
            zvel[nSprite] += vc;
        }
    }
    if (pPlayer && zvel[nSprite] > 0x155555 && !pPlayer->at31b && pXSprite->at30_0 > 0)
    {
        pPlayer->at31b = 1;
        sfxPlay3DSound(pSprite, 719, 0, 0);
    }
    int nLink = CheckLink(pSprite);
    if (nLink)
    {
        GetZRange(pSprite, &ceilZ, &ceilHit, &floorZ, &floorHit, wd, 0x13001);
        if (pPlayer)
            playerResetInertia(pPlayer);
        switch (nLink)
        {
        case 12:
            if (pPlayer == gView)
                SetBitString(gotpic, sector[pSprite->sectnum].floorpicnum);
            break;
        case 11:
            if (pPlayer == gView)
                SetBitString(gotpic, sector[pSprite->sectnum].ceilingpicnum);
            break;
        case 10:
        case 14:
            pXSprite->at17_6 = 0;
            if (pPlayer)
            {
                pPlayer->at2f = 0;
                pPlayer->at302 = 0;
                if (!pPlayer->at31c && pPlayer->atc.buttonFlags.jump)
                {
                    zvel[nSprite] = -0x6aaaa;
                    pPlayer->at31c = 1;
                }
                sfxPlay3DSound(pSprite, 721, -1, 0);
            }
            else
            {
                switch (pSprite->type)
                {
                case 201:
                case 202:
                    aiNewState(pSprite, pXSprite, &cultistGoto);
                    break;
                case 217:
                    aiNewState(pSprite, pXSprite, &gillBeastGoto);
                    pSprite->hitag |= 6;
                    break;
                case 218:
                    actKillDude(pSprite->index, pSprite, DAMAGE_TYPE_0, 1000<<4);
                    break;
                }
            }
            break;
        case 9:
            pXSprite->at17_6 = 1;
            if (pPlayer)
            {
                pPlayer->at2f = 1;
                pXSprite->at2c_0 = 0;
                pPlayer->at302 = klabs(zvel[nSprite])>>12;
                evPost(nSprite, 3, 0, CALLBACK_ID_10);
                sfxPlay3DSound(pSprite, 720, -1, 0);
            }
            else
            {
                switch (pSprite->type)
                {
                case 201:
                case 202:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    break;
                case 240:
                    if (Chance(0xa00))
                    {
                        pSprite->type = 201;
                        pXSprite->at2c_0 = 0;
                        evPost(nSprite, 3, 0, CALLBACK_ID_11);
                        sfxPlay3DSound(pSprite, 720, -1, 0);
                        aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    }
                    else
                    {
                        pSprite->type = 202;
                        pXSprite->at2c_0 = 0;
                        evPost(nSprite, 3, 0, CALLBACK_ID_11);
                        sfxPlay3DSound(pSprite, 720, -1, 0);
                        aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    }
                    break;
                case 203:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &zombieAGoto);
                    break;
                case 204:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &zombieFGoto);
                    break;
                case 217:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &gillBeastSwimGoto);
                    pSprite->hitag &= ~6;
                    break;
                case 206:
                case 211:
                case 213:
                case 214:
                case 215:
                case 219:
                case 220:
                case 239:
                    actKillDude(pSprite->index, pSprite, DAMAGE_TYPE_0, 1000<<4);
                    break;
                }
            }
            break;
        case 13:
            pXSprite->at17_6 = 2;
            if (pPlayer)
            {
                pPlayer->at2f = 1;
                pXSprite->at2c_0 = 0;
                pPlayer->at302 = klabs(zvel[nSprite])>>12;
                evPost(nSprite, 3, 0, CALLBACK_ID_10);
                sfxPlay3DSound(pSprite, 720, -1, 0);
            }
            else
            {
                switch (pSprite->type)
                {
                case 201:
                case 202:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    break;
                case 240:
                    if (Chance(0x400))
                    {
                        pSprite->type = 201;
                        pXSprite->at2c_0 = 0;
                        evPost(nSprite, 3, 0, CALLBACK_ID_11);
                        sfxPlay3DSound(pSprite, 720, -1, 0);
                        aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    }
                    else
                    {
                        pSprite->type = 202;
                        pXSprite->at2c_0 = 0;
                        evPost(nSprite, 3, 0, CALLBACK_ID_11);
                        sfxPlay3DSound(pSprite, 720, -1, 0);
                        aiNewState(pSprite, pXSprite, &cultistSwimGoto);
                    }
                    break;
                case 203:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &zombieAGoto);
                    break;
                case 204:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &zombieFGoto);
                    break;
                case 217:
                    pXSprite->at2c_0 = 0;
                    evPost(nSprite, 3, 0, CALLBACK_ID_11);
                    sfxPlay3DSound(pSprite, 720, -1, 0);
                    aiNewState(pSprite, pXSprite, &gillBeastSwimGoto);
                    pSprite->hitag &= ~6;
                    break;
                case 206:
                case 211:
                case 213:
                case 214:
                case 215:
                case 219:
                case 220:
                case 239:
                    actKillDude(pSprite->index, pSprite, DAMAGE_TYPE_0, 1000<<4);
                    break;
                }
            }
            break;
        }
    }
    GetSpriteExtents(pSprite, &top, &bottom);
    if (pPlayer && bottom >= floorZ)
    {
        int floorZ2 = floorZ;
        int floorHit2 = floorHit;
        GetZRange(pSprite, &ceilZ, &ceilHit, &floorZ, &floorHit, pSprite->clipdist<<2, 0x13001);
        if (bottom <= floorZ && pSprite->z - floorZ < bz)
        {
            floorZ = floorZ2;
            floorHit = floorHit2;
        }
    }
    if (floorZ <= bottom)
    {
        gSpriteHit[nXSprite].florhit = floorHit;
        pSprite->z += floorZ-bottom;
        int v30 = zvel[nSprite]-velFloor[pSprite->sectnum];
        if (v30 > 0)
        {
            int vax = actFloorBounceVector((long*)&xvel[nSprite], (long*)&yvel[nSprite], (long*)&v30, pSprite->sectnum, 0);
            int nDamage = mulscale(vax, vax, 30);
            if (pPlayer)
            {
                pPlayer->at31b = 0;
                if (nDamage > (15<<4) && (pSprite->hitag&4))
                    playerLandingSound(pPlayer);
                if (nDamage > (30<<4))
                    sfxPlay3DSound(pSprite, 701, 0, 0);
            }
            nDamage -= 100<<4;
            if (nDamage > 0)
                actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_0, nDamage);
            zvel[nSprite] = v30;
            if (klabs(zvel[nSprite]) < 0x10000)
            {
                zvel[nSprite] = velFloor[pSprite->sectnum];
                pSprite->hitag &= ~4;
            }
            else
                pSprite->hitag |= 4;
            switch (tileGetSurfType(floorHit))
            {
            case 5:
                gFX.fxSpawn(FX_9, pSprite->sectnum, pSprite->x, pSprite->y, floorZ, 0);
                break;
            case 14:
            {
                SPRITE *pFX = gFX.fxSpawn(FX_10, pSprite->sectnum, pSprite->x, pSprite->y, floorZ, 0);
                if (pFX)
                {
                    for (int i = 0; i < 7; i++)
                    {
                        SPRITE *pFX2 = gFX.fxSpawn(FX_14, pFX->sectnum, pFX->x, pFX->y, pFX->z, 0);
                        if (pFX2)
                        {
                            xvel[pFX2->index] = Random2(0x6aaaa);
                            yvel[pFX2->index] = Random2(0x6aaaa);
                            zvel[pFX2->index] = -Random(0xd5555);
                        }
                    }
                }
                break;
            }
            }
        }
        else if (zvel[nSprite] == 0)
            pSprite->hitag &= ~4;
    }
    else
    {
        gSpriteHit[nXSprite].florhit = 0;
        if (pSprite->hitag&2)
            pSprite->hitag |= 4;
    }
    if (top <= ceilZ)
    {
        gSpriteHit[nXSprite].ceilhit = ceilHit;
        pSprite->z += ClipLow(ceilZ-top, 0);
        if (zvel[nSector] <= 0 && (pSprite->hitag&4))
            zvel[nSprite] = mulscale16(-zvel[nSprite], 0x2000);
    }
    else
        gSpriteHit[nXSprite].ceilhit = 0;
    GetSpriteExtents(pSprite,&top,&bottom);

    pXSprite->at30_0 = ClipLow(floorZ-bottom, 0)>>8;
    if (xvel[nSprite] || yvel[nSprite])
    {
        if ((floorHit & 0xe000) == 0xc000)
        {
            int nHitSprite = floorHit & 0x1fff;
            if ((sprite[nHitSprite].cstat & 0x30) == 0)
            {
                xvel[nSprite] += mulscale(4, pSprite->x - sprite[nHitSprite].x, 2);
                yvel[nSprite] += mulscale(4, pSprite->y - sprite[nHitSprite].y, 2);
                return;
            }
        }
        int nXSector = sector[pSprite->sectnum].extra;
        if (nXSector > 0 && xsector[nXSector].at13_4)
            return;
        if (pXSprite->at30_0 >= 0x100)
            return;
        int nDrag = gDudeDrag;
        if (pXSprite->at30_0 > 0)
            nDrag -= scale(gDudeDrag, pXSprite->at30_0, 0x100);
        xvel[nSprite] -= mulscale16r(xvel[nSprite], nDrag);
        yvel[nSprite] -= mulscale16r(yvel[nSprite], nDrag);

        if (approxDist(xvel[nSprite], yvel[nSprite]) < 0x1000)
            xvel[nSprite] = yvel[nSprite] = 0;
    }
}

int MoveMissile(SPRITE *pSprite)
{
    int nXSprite = pSprite->extra;
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int vdi = -1;
    SPRITE *pOwner = NULL;
    int bakCstat = 0;
    if (pSprite->owner >= 0)
    {
        int nOwner = actSpriteOwnerToSpriteId(pSprite);
        pOwner = &qsprite[nOwner];
        if (IsDudeSprite(pOwner))
        {
            bakCstat = pOwner->cstat;
            pOwner->cstat &= ~257;
        }
        else
            pOwner = NULL;
    }
    gHitInfo.hitsect = -1;
    gHitInfo.hitwall = -1;
    gHitInfo.hitsprite = -1;
    if (pSprite->type == 304)
        actAirDrag(pSprite, 0x1000);
    int nSprite = pSprite->index;
    if (pXSprite->target != -1 && (xvel[nSprite] || yvel[nSprite] || zvel[nSprite]))
    {
        SPRITE *pTarget = &qsprite[pXSprite->target];
        XSPRITE *pXTarget;
        if (pTarget->extra > 0)
            pXTarget = &xsprite[pTarget->extra];
        else
            pXTarget = NULL;
        if (pTarget->statnum == 6 && pXTarget && pXTarget->health > 0)
        {
            int nTargetAngle = getangle(pTarget->x-pSprite->x, pTarget->y-pSprite->y);
            int nAngle = getangle(xvel[nSprite]>>12,yvel[nSprite]>>12);
            long vx = missileInfo[pSprite->type-300].at2;
            long vy = 0;
            RotatePoint(&vx, &vy, (nTargetAngle+1536)&2047, 0, 0);
            xvel[nSprite] = vx;
            yvel[nSprite] = vy;
            int dx = pTarget->x-pSprite->x;
            int dy = pTarget->y-pSprite->y;
            int dz = pTarget->z-pSprite->z;
            // Inlined
            int vax = dz/10;
            if (pTarget->z < pSprite->z)
                vax = -vax;
            zvel[nSprite] += vax;
            ksqrt(dx*dx+dy*dy+dz*dz);
        }
    }
    int vx = xvel[nSprite]>>12;
    int vy = yvel[nSprite]>>12;
    int vz = zvel[nSprite]>>8;
    int top, bottom;
    GetSpriteExtents(pSprite, &top, &bottom);
    int i = 1;
    while (1)
    {
        long x = pSprite->x;
        long y = pSprite->y;
        long z = pSprite->z;
        int nSector2 = pSprite->sectnum;
        clipmoveboxtracenum = 1;
        int vdx = ClipMove(&x, &y, &z, &nSector2, vx, vy, pSprite->clipdist<<2, (z-top)/4, (bottom-z)/4, CLIPMASK0);
        clipmoveboxtracenum = 3;
        short nSector = nSector2;
        if (nSector2 < 0)
        {
            vdi = -1;
            break;
        }
        if (vdx)
        {
            int nHitSprite = vdx & 0x1fff;
            if ((vdx&0xe000) == 0xc000)
            {
                gHitInfo.hitsprite = nHitSprite;
                vdi = 3;
            }
            else if ((vdx & 0xe000) == 0x8000)
            {
                gHitInfo.hitwall = nHitSprite;
                if (wall[nHitSprite].nextsector == -1)
                    vdi = 0;
                else
                {
                    int32_t fz, cz;
                    getzsofslope(wall[nHitSprite].nextsector, x, y, &cz, &fz);
                    if (z <= cz || z >= fz)
                        vdi = 0;
                    else
                        vdi = 4;
                }
            }
        }
        if (vdi == 4)
        {
            WALL *pWall = &qwall[gHitInfo.hitwall];
            if (pWall->extra)
            {
                XWALL *pXWall = &xwall[pWall->extra];
                if (pXWall->at10_6)
                {
                    trTriggerWall(gHitInfo.hitwall, pXWall, 51);
                    if (!(pWall->cstat&64))
                    {
                        vdi = -1;
                        if (i-- > 0)
                            continue;
                        vdi = 0;
                        break;
                    }
                }
            }
        }
        if (vdi >= 0 && vdi != 3)
        {
            int nAngle = getangle(xvel[nSprite], yvel[nSprite]);
            x -= mulscale30(Cos(nAngle), 16);
            y -= mulscale30(Sin(nAngle), 16);
            int nVel = approxDist(xvel[nSprite], yvel[nSprite]);
            vz -= scale(0x100, zvel[nSprite], nVel);
            updatesector(x, y, &nSector);
            nSector2 = nSector;
        }
        long ceilZ, ceilHit, floorZ, floorHit;
        GetZRangeAtXYZ(x, y, z, nSector2, &ceilZ, &ceilHit, &floorZ, &floorHit, pSprite->clipdist<<2, CLIPMASK0);
        GetSpriteExtents(pSprite, &top, &bottom);
        top += vz;
        bottom += vz;
        if (bottom >= floorZ)
        {
            gSpriteHit[nXSprite].florhit = floorHit;
            vz += floorZ-bottom;
            vdi = 2;
        }
        if (top <= ceilZ)
        {
            gSpriteHit[nXSprite].ceilhit = ceilHit;
            vz += ClipLow(ceilZ-top, 0);
            vdi = 1;
        }
        pSprite->x = x;
        pSprite->y = y;
        pSprite->z = z+vz;
        updatesector(x, y, &nSector);
        if (nSector >= 0 && nSector != pSprite->sectnum)
        {
            dassert(nSector >= 0 && nSector < kMaxSectors);
            ChangeSpriteSect(nSprite, nSector);
        }
        CheckLink(pSprite);
        gHitInfo.hitsect = pSprite->sectnum;
        gHitInfo.hitx = pSprite->x;
        gHitInfo.hity = pSprite->y;
        gHitInfo.hitz = pSprite->z;
        break;
    }
    if (pOwner)
        pOwner->cstat = bakCstat;
    return vdi;
}

void actExplodeSprite(SPRITE *pSprite)
{
    int nXSprite = pSprite->extra;
    if (nXSprite <= 0 || nXSprite >= kMaxXSprites)
        return;
    if (pSprite->statnum == 2)
        return;
    sfxKill3DSound(pSprite, -1, -1);
    evKill(pSprite->index, 3);
    int v4;
    switch (pSprite->type)
    {
    case 312:
        v4 = 7;
        seqSpawn(4, 3, nXSprite, -1);
        if (Chance(0x8000))
            pSprite->cstat |= 4;
        sfxPlay3DSound(pSprite, 303, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 303:
        v4 = 3;
        seqSpawn(9, 3, nXSprite, -1);
        if (Chance(0x8000))
            pSprite->cstat |= 4;
        sfxPlay3DSound(pSprite, 306, 24+(pSprite->index&3), 1);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 313:
    case 314:
        v4 = 3;
        seqSpawn(5, 3, nXSprite, -1);
        if (Chance(0x8000))
            pSprite->cstat |= 4;
        sfxPlay3DSound(pSprite, 304, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 418:
        v4 = 0;
        if (gSpriteHit[nXSprite].florhit == 0)
            seqSpawn(4,3,nXSprite,-1);
        else
            seqSpawn(3,3,nXSprite,-1);
        sfxPlay3DSound(pSprite, 303, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 401:
    case 402:
    case 419:
        v4 = 1;
        if (gSpriteHit[nXSprite].florhit == 0)
            seqSpawn(4,3,nXSprite,-1);
        else
            seqSpawn(3,3,nXSprite,-1);
        sfxPlay3DSound(pSprite, 304, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 420:
        v4 = 4;
        seqSpawn(5, 3, nXSprite, -1);
        sfxPlay3DSound(pSprite, 307, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    case 400:
    {
        SPRITE *pSprite2 = actSpawnSprite(pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0, 1);
        pSprite2->owner = pSprite->owner;
        if (actCheckRespawn(pSprite))
        {
            XSPRITE *pXSprite = &xsprite[nXSprite];
            pXSprite->at1_6 = 1;
            pXSprite->health = thingInfo[0].at0<<4;
        }
        else
            actPostSprite(pSprite->index, 1024);
        v4 = 2;
        nXSprite = pSprite2->extra;
        seqSpawn(4, 3, nXSprite, -1);
        sfxPlay3DSound(pSprite2, 305, -1, 0);
        GibSprite(pSprite2, GIBTYPE_14, NULL, NULL);
        pSprite = pSprite2;
        break;
    }
    case 459:
        v4 = 1;
        seqSpawn(4, 3, nXSprite, -1);
        sfxPlay3DSound(pSprite, 304, -1, 0);
        break;
    case 429:
        v4 = 3;
        seqSpawn(9, 3, nXSprite, -1);
        sfxPlay3DSound(pSprite, 307, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        sub_746D4(pSprite, 240);
        break;
    default:
        v4 = 1;
        seqSpawn(4, 3, nXSprite, -1);
        if (Chance(0x8000))
            pSprite->cstat |= 4;
        sfxPlay3DSound(pSprite, 303, -1, 0);
        GibSprite(pSprite, GIBTYPE_5, NULL, NULL);
        break;
    }
    int nSprite = pSprite->index;
    xvel[nSprite] = yvel[nSprite] = zvel[nSprite] = 0;
    actPostSprite(nSprite, 2);
    pSprite->xrepeat = pSprite->yrepeat = explodeInfo[v4].at0;
    pSprite->hitag &= ~3;
    pSprite->type = v4;
    EXPLOSION *pExplodeInfo = &explodeInfo[v4];
    xsprite[nXSprite].target = 0;
    xsprite[nXSprite].at10_0 = pExplodeInfo->atf;
    xsprite[nXSprite].at12_0 = pExplodeInfo->at13;
    xsprite[nXSprite].at14_0 = pExplodeInfo->at17;
}

void actActivateGibObject(SPRITE *pSprite, XSPRITE *pXSprite)
{
    int vdx = ClipRange(pXSprite->at10_0, 0, 31);
    int vc = ClipRange(pXSprite->at12_0, 0, 31);
    int v4 = ClipRange(pXSprite->at14_0, 0, 31);
    int vbp = pXSprite->at18_2;
    int v8 = pXSprite->atc_0;
    if (vdx > 0)
        GibSprite(pSprite, (GIBTYPE)(vdx-1), NULL, NULL);
    if (vc > 0)
        GibSprite(pSprite, (GIBTYPE)(vc-1), NULL, NULL);
    if (v4 > 0 && pXSprite->at2c_0 > 0)
        GibSprite(pSprite, (GIBTYPE)(v4-1), NULL, NULL);
    if (vbp > 0)
        sfxPlay3DSound(pSprite->x, pSprite->y, pSprite->z, vbp, pSprite->sectnum);
    if (v8 > 0)
        actDropObject(pSprite, v8);
    if (!(pSprite->cstat&32768) && !(pSprite->hitag&16))
        actPostSprite(pSprite->index, 1024);
}

bool IsUnderWater(SPRITE *pSprite)
{
    int nSector = pSprite->sectnum;
    int nXSector = sector[nSector].extra;
    if (nXSector > 0 && nXSector < kMaxXSectors)
        if (xsector[nXSector].at13_4)
            return 1;
    return 0;
}

void MakeSplash(SPRITE *pSprite, XSPRITE *pXSprite);

void actProcessSprites(void)
{
    int nSprite;
    int nNextSprite;
    for (nSprite = headspritestat[4]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag&32)
            continue;
        int nXSprite = pSprite->extra;
        if (nXSprite > 0)
        {
            XSPRITE *pXSprite = &xsprite[nXSprite];
            if (pSprite->type == 425 || pSprite->type == 426 || pSprite->type == 427)
                if (pXSprite->at17_5 && gFrameClock >= pXSprite->at20_0)
                    pXSprite->at17_5 = 0;
            if (pXSprite->at2c_0 > 0)
            {
                pXSprite->at2c_0 = ClipLow(pXSprite->at2c_0-4,0);
                actDamageSprite(actOwnerIdToSpriteId(pXSprite->at2e_0), pSprite, DAMAGE_TYPE_1, 8);
            }
            if (pXSprite->ate_4)
            {
                if (pSprite->type == 431)
                    pXSprite->target = -1;
                for (int nSprite2 = headspritestat[6]; nSprite2 >= 0; nSprite2 = nNextSprite)
                {
                    int v1b0 = 96;
                    nNextSprite = nextspritestat[nSprite2];
                    SPRITE *pSprite2 = &qsprite[nSprite2];
                    if (pSprite2->hitag&32)
                        continue;
                    XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
                    if ((unsigned int)pXSprite2->health > 0)
                    {
                        if (pSprite->type == 431 && pXSprite->target == -1)
                        {
                            int nOwner = actOwnerIdToSpriteId(pSprite->owner);
                            SPRITE *pOwner = &qsprite[nOwner];
                            PLAYER *pPlayer = &gPlayer[pOwner->type-kDudePlayer1];
                            PLAYER *pPlayer2 = NULL;
                            if (IsPlayerSprite(pSprite2))
                                pPlayer2 = &gPlayer[pSprite2->type-kDudePlayer1];
                            if (nSprite2 == nOwner || pSprite2->picnum == 205 || pSprite2->picnum == 220 || pSprite2->picnum == 219)
                                continue;
                            if (gGameOptions.nGameType == 3 && pPlayer2 && pPlayer->at2ea == pPlayer2->at2ea)
                                continue;
                            if (gGameOptions.nGameType == 1 && pPlayer2)
                                continue;
                            v1b0 = 512;
                        }
                        if (CheckProximity(pSprite2, pSprite->x, pSprite->y, pSprite->z, pSprite->sectnum, v1b0))
                        {
                            if (pSprite->type == 431)
                            {
                                if (Chance(0x4000) || nNextSprite < 0)
                                {
                                    if (pSprite2->cstat & 0x10001)
                                        pXSprite->target = pSprite2->index;
                                    else
                                        continue;
                                }
                                else
                                    continue;
                            }
                            if (pSprite->owner == -1)
                                actPropagateSpriteOwner(pSprite2, pSprite);
                            trTriggerSprite(nSprite, pXSprite, 35);
                        }
                    }
                }
            }
        }
    }
    for (nSprite = headspritestat[4]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nSector = pSprite->sectnum;
        int nXSprite = pSprite->extra;
        dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
        int nXSector = sector[nSector].extra;
        XSECTOR *pXSector = NULL;
        if (nXSector > 0)
        {
            dassert(nXSector > 0 && nXSector < kMaxXSectors);
            dassert(xsector[nXSector].reference == nSector);
            pXSector = &xsector[nXSector];
        }
        if (pXSector && pXSector->at14_0 && (pXSector->at13_0 || pXSector->at1_6 || pXSector->at1_7))
        {
            int nType = pSprite->type - kThingBase;
            THINGINFO *pThingInfo = &thingInfo[nType];
            if (pThingInfo->at5 & 1)
                pSprite->hitag |= 1;
            if (pThingInfo->at5 & 2)
                pSprite->hitag |= 4;
        }
        if (pSprite->hitag&3)
        {
            viewBackupSpriteLoc(nSprite, pSprite);
            if (pXSector && pXSector->at14_0)
            {
                int top, bottom;
                GetSpriteExtents(pSprite, &top, &bottom);
                if (getflorzofslope(nSector, pSprite->x, pSprite->y) <= bottom)
                {
                    int angle = pXSector->at15_0;
                    int speed = 0;
                    if (pXSector->at13_0 || pXSector->at1_6 || pXSector->at1_7)
                    {
                        speed = pXSector->at14_0 << 9;
                        if (!pXSector->at13_0 && pXSector->at1_7)
                            speed = mulscale16(speed, pXSector->at1_7);
                    }
                    if (sector[nSector].floorstat&64)
                        angle = (angle+GetWallAngle(sector[nSector].wallptr)+512)&2047;
                    int dx = mulscale30(speed, Cos(angle));
                    int dy = mulscale30(speed, Sin(angle));
                    xvel[nSprite] += dx;
                    yvel[nSprite] += dy;
                }
            }
            actAirDrag(pSprite, 128);
            if ((pSprite->index>>8) == (gFrame&15) && (pSprite->hitag&2))
                pSprite->hitag |= 4;
            if ((pSprite->hitag&4) || xvel[nSprite] || yvel[nSprite] || zvel[nSprite] ||
                velFloor[pSprite->sectnum] || velCeil[pSprite->sectnum])
            {
                int hit = MoveThing(pSprite);
                if (hit)
                {
                    int nXSprite = pSprite->extra;
                    if (nXSprite)
                    {
                        XSPRITE *pXSprite = &xsprite[nXSprite];
                        if (pXSprite->ate_0)
                            trTriggerSprite(nSprite, pXSprite, 0);
                        switch (pSprite->type)
                        {
                        case 423:
                        case 424:
                            MakeSplash(pSprite, pXSprite);
                            break;
                        case 421:
                            seqSpawn(24, 3, nXSprite, -1);
                            if ((hit&0xe000) == 0xc000)
                            {
                                int nObject = hit & 0x1fff;
                                dassert(nObject >= 0 && nObject < kMaxSprites);
                                SPRITE *pObject = &qsprite[nObject];
                                actDamageSprite(actSpriteOwnerToSpriteId(pSprite), pObject, DAMAGE_TYPE_0, 12);
                            }
                            break;
                        case 430:
                            if ((hit&0xe000) == 0x4000)
                            {
                                sub_2A620(actSpriteOwnerToSpriteId(pSprite), pSprite->x, pSprite->y, pSprite->z, pSprite->sectnum, 200, 1, 20, DAMAGE_TYPE_3, 6, 0, 0, 0);
                                evPost(pSprite->index, 3, 0, CALLBACK_ID_19);
                            }
                            else
                            {
                                int nObject = hit & 0x1fff;
                                dassert(nObject >= 0 && nObject < kMaxSprites);
                                SPRITE *pObject = &qsprite[nObject];
                                actDamageSprite(actSpriteOwnerToSpriteId(pSprite), pObject, DAMAGE_TYPE_0, 12);
                                evPost(pSprite->index, 3, 0, CALLBACK_ID_19);
                            }
                            break;
                        case 429:
                        {
                            int nObject = hit & 0x1fff;
                            dassert(nObject >= 0 && nObject < kMaxSprites);
                            int nOwner = actSpriteOwnerToSpriteId(pSprite);
                            actExplodeSprite(pSprite);
                            break;
                        }
                        }
                    }
                }
            }
        }
    }
    for (nSprite = headspritestat[5]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        viewBackupSpriteLoc(nSprite, pSprite);
        int hit = MoveMissile(pSprite);
        if (hit >= 0)
            actImpactMissile(pSprite, hit);
    }
    for (nSprite = headspritestat[2]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        char v24c[(kMaxSectors+7)>>3];
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nOwner = actSpriteOwnerToSpriteId(pSprite);
        int nType = pSprite->type;
        dassert(nType >= 0 && nType < kExplodeMax);
        EXPLOSION *pExplodeInfo = &explodeInfo[nType];
        int nXSprite = pSprite->extra;
        dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
        XSPRITE *pXSprite = &xsprite[nXSprite];
        int x = pSprite->x;
        int y = pSprite->y;
        int z = pSprite->z;
        int nSector = pSprite->sectnum;
        gAffectedSectors[0] = -1;
        gAffectedXWalls[0] = -1;
        GetClosestSpriteSectors(nSector, x, y, pExplodeInfo->at3, gAffectedSectors, v24c, gAffectedXWalls);
        for (int i = 0; i < kMaxXWalls; i++)
        {
            int nWall = gAffectedXWalls[i];
            if (nWall == -1)
                break;
            XWALL *pXWall = &xwall[wall[nWall].extra];
            trTriggerWall(nWall, pXWall, 51);
        }
        for (int nSprite2 = headspritestat[6]; nSprite2 >= 0; nSprite2 = nextspritestat[nSprite2])
        {
            SPRITE *pDude = &qsprite[nSprite2];
            if (pDude->hitag & 32)
                continue;
            if (TestBitString(v24c, pDude->sectnum))
            {
                if (pXSprite->at10_0 && CheckProximity(pDude, x, y, z, nSector, pExplodeInfo->at3))
                {
                    if (pExplodeInfo->at1 && pXSprite->target == 0)
                    {
                        pXSprite->target = 1;
                        actDamageSprite(nOwner, pDude, DAMAGE_TYPE_0, (pExplodeInfo->at1+Random(pExplodeInfo->at2))<<4);
                    }
                    if (pExplodeInfo->at7)
                        ConcussSprite(nOwner, pDude, x, y, z, pExplodeInfo->at7);
                    if (pExplodeInfo->atb)
                    {
                        dassert(pDude->extra > 0 && pDude->extra < kMaxXSprites);
                        XSPRITE *pXDude = &xsprite[pDude->extra];
                        if (!pXDude->at2c_0)
                            evPost(nSprite2, 3, 0, CALLBACK_ID_0);
                        actBurnSprite(pSprite->owner, pXDude, pExplodeInfo->atb<<2);
                    }
                }
            }
        }
        for (int nSprite2 = headspritestat[4]; nSprite2 >= 0; nSprite2 = nextspritestat[nSprite2])
        {
            SPRITE *pThing = &qsprite[nSprite2];
            if (pThing->hitag & 32)
                continue;
            if (TestBitString(v24c, pThing->sectnum))
            {
                if (pXSprite->at10_0 && CheckProximity(pThing, x, y, z, nSector, pExplodeInfo->at3))
                {
                    XSPRITE *pXSprite2 = &xsprite[pThing->extra];
                    if (!pXSprite2->at17_5)
                    {
                        if (pExplodeInfo->at7)
                            ConcussSprite(nOwner, pThing, x, y, z, pExplodeInfo->at7);
                        if (pExplodeInfo->atb)
                        {
                            dassert(pThing->extra > 0 && pThing->extra < kMaxXSprites);
                            XSPRITE *pXThing = &xsprite[pThing->extra];
                            if (pThing->type == 400 && !pXThing->at2c_0)
                                evPost(nSprite2, 3, 0, CALLBACK_ID_0);
                            actBurnSprite(pSprite->owner, pXThing, pExplodeInfo->atb<<2);
                        }
                    }
                }
            }
        }
        for (int p = connecthead; p >= 0; p = connectpoint2[p])
        {
            SPRITE *pSprite2 = gPlayer[p].pSprite;
            int dx = (x - pSprite->x)>>4;
            int dy = (y - pSprite->y)>>4;
            int dz = (z - pSprite->z)>>8;
            int nDist = dx*dx+dy*dy+dz*dz+0x40000;
            int t = divscale16(pXSprite->at12_0, nDist);
            gPlayer[p].at35a += t;
        }
        pXSprite->at10_0 = ClipLow(pXSprite->at10_0-4, 0);
        pXSprite->at12_0 = ClipLow(pXSprite->at12_0-4, 0);
        pXSprite->at14_0 = ClipLow(pXSprite->at14_0-4, 0);
        if (!pXSprite->at10_0 && !pXSprite->at12_0 && !pXSprite->at14_0 && seqGetStatus(3, nXSprite) < 0)
            actPostSprite(nSprite, 1024);
    }
    for (nSprite = headspritestat[11]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nXSprite = pSprite->extra;
        dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
        XSPRITE *pXSprite = &xsprite[nXSprite];
        switch (pSprite->type)
        {
        case 454:
            pXSprite->at12_0 = ClipLow(pXSprite->at12_0-4, 0);
            break;
        case 452:
            if (pXSprite->at1_6 && seqGetStatus(3, nXSprite) < 0)
            {
                int x = pSprite->x;
                int y = pSprite->y;
                int z = pSprite->z;
                int t = (pXSprite->at10_0<<23)/120;
                int dx = mulscale30(t, Cos(pSprite->ang));
                int dy = mulscale30(t, Sin(pSprite->ang));
                for (int i = 0; i < 2; i++)
                {
                    SPRITE *pFX = gFX.fxSpawn(FX_32, pSprite->sectnum, x, y, z, 0);
                    if (pFX)
                    {
                        xvel[pFX->index] = dx + Random2(0x8888);
                        yvel[pFX->index] = dy + Random2(0x8888);
                        zvel[pFX->index] = Random2(0x8888);
                    }
                    x += (dx/2)>>12;
                    y += (dy/2)>>12;
                }
                dy = Sin(pSprite->ang)>>16;
                dx = Cos(pSprite->ang)>>16;
                gVectorData[VECTOR_TYPE_20].at9 = pXSprite->at10_0<<9;
                actFireVector(pSprite, 0, 0, dx, dy, Random2(0x8888), VECTOR_TYPE_20);
            }
            break;
        }
    }
    for (nSprite = headspritestat[6]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nXSprite = pSprite->extra;
        if (nXSprite > 0)
        {
            XSPRITE *pXSprite = &xsprite[nXSprite];
            if (pXSprite->at2c_0 > 0)
            {
                switch (pSprite->type)
                {
                case 239:
                case 240:
                case 241:
                case 242:
                    actDamageSprite(actOwnerIdToSpriteId(pXSprite->at2e_0), pSprite, DAMAGE_TYPE_1, 8);
                    break;
                default:
                    pXSprite->at2c_0 = ClipLow(pXSprite->at2c_0-4, 0);
                    actDamageSprite(actOwnerIdToSpriteId(pXSprite->at2e_0), pSprite, DAMAGE_TYPE_1, 8);
                    break;
                }
            }
            if (pSprite->type == 227)
            {
                if (pXSprite->health <= 0 && seqGetStatus(3, nXSprite) < 0)
                {
                    pXSprite->health = dudeInfo[28].at2<<4;
                    pSprite->type = 228;
                    aiSetTarget(pXSprite, pXSprite->target);
                    aiActivateDude(pSprite, pXSprite);
                }
            }
            if (pXSprite->ate_4 && !pXSprite->atd_2)
            {
                for (int nSprite2 = headspritestat[6]; nSprite2 >= 0; nSprite2 = nNextSprite)
                {
                    nNextSprite = nextspritestat[nSprite2];
                    SPRITE *pSprite2 = &qsprite[nSprite2];
                    if (pSprite2->hitag&32)
                        continue;
                    XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
                    if ((unsigned int)pXSprite2->health > 0 && pSprite2->type >= kDudePlayer1 && pSprite2->type <= kDudePlayer8)
                    {
                        if (CheckProximity(pSprite2, pSprite->x, pSprite->y, pSprite->z, pSprite->sectnum, 128))
                        {
                            trTriggerSprite(nSprite, pXSprite, 35);
                        }
                    }
                }
            }
            if (IsPlayerSprite(pSprite))
            {
                PLAYER *pPlayer = &gPlayer[pSprite->type-kDudePlayer1];
                if (pPlayer->at34e)
                    sub_41250(pPlayer);
                if (pPlayer->at376 && Chance(0x8000))
                    actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_4, 12);
                if (pPlayer->at87)
                {
                    char bActive = packItemActive(pPlayer, 1);
                    if (bActive || pPlayer->at31a)
                        pPlayer->at2f2 = 1200;
                    else
                        pPlayer->at2f2 = ClipLow(pPlayer->at2f2-4, 0);
                    if (pPlayer->at2f2 < 1080 && packCheckItem(pPlayer, 1) && !bActive)
                        packUseItem(pPlayer, 1);
                    if (!pPlayer->at2f2)
                    {
                        pPlayer->at36e += 4;
                        if (Chance(pPlayer->at362))
                            actDamageSprite(nSprite, pSprite, DAMAGE_TYPE_4, 3<<4);
                    }
                    else
                        pPlayer->at36e = 0;
                    if (xvel[nSprite] || yvel[nSprite])
                        sfxPlay3DSound(pSprite, 709, 100, 2);
                    pPlayer->at302 = ClipLow(pPlayer->at302-4, 0);
                }
                else if (gGameOptions.nGameType == 0)
                {
                    if (pPlayer->pXSprite->health > 0 && pPlayer->at30a >= 1200 && Chance(0x200))
                    {
                        pPlayer->at30a = -1;
                        sfxPlay3DSound(pSprite, 3100+Random(11), 0, 2);
                    }
                }
            }
            ProcessTouchObjects(pSprite, nXSprite);
        }
    }
    for (nSprite = headspritestat[6]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nXSprite = pSprite->extra;
        dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
        int nSector = pSprite->sectnum;
        viewBackupSpriteLoc(nSprite, pSprite);
        int nXSector = sector[nSector].extra;
        XSECTOR *pXSector = NULL;
        if (nXSector > 0)
        {
            dassert(nXSector > 0 && nXSector < kMaxXSectors);
            dassert(xsector[nXSector].reference == nSector);
            pXSector = &xsector[nXSector];
        }
        if (pXSector)
        {
            int top, bottom;
            GetSpriteExtents(pSprite, &top, &bottom);
            if (getflorzofslope(nSector, pSprite->x, pSprite->y) <= bottom)
            {
                int angle = pXSector->at15_0;
                int speed = 0;
                if (pXSector->at13_0 || pXSector->at1_6 || pXSector->at1_7)
                {
                    speed = pXSector->at14_0 << 9;
                    if (!pXSector->at13_0 && pXSector->at1_7)
                        speed = mulscale16(speed, pXSector->at1_7);
                }
                if (sector[nSector].floorstat&64)
                    angle = (angle+GetWallAngle(sector[nSector].wallptr)+512)&2047;
                int dx = mulscale30(speed, Cos(angle));
                int dy = mulscale30(speed, Sin(angle));
                xvel[nSprite] += dx;
                yvel[nSprite] += dy;
            }
        }
        if (pXSector && pXSector->at13_4)
            actAirDrag(pSprite, 5376);
        else
            actAirDrag(pSprite, 128);
        if ((pSprite->hitag&4) || xvel[nSprite] || yvel[nSprite] || zvel[nSprite] ||
            velFloor[pSprite->sectnum] || velCeil[pSprite->sectnum])
            MoveDude(pSprite);
    }
    for (nSprite = headspritestat[14]; nSprite >= 0; nSprite = nextspritestat[nSprite])
    {
        SPRITE *pSprite = &qsprite[nSprite];
        if (pSprite->hitag & 32)
            continue;
        int nXSprite = pSprite->extra;
        dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
        XSPRITE *pXSprite = &xsprite[nXSprite];
        int nTarget = pXSprite->target;
        dassert(nTarget >= 0);
        viewBackupSpriteLoc(nSprite, pSprite);
        dassert(nTarget < kMaxSprites);
        SPRITE *pTarget = &qsprite[nTarget];
        if (pTarget->statnum == kMaxStatus)
        {
            GibSprite(pSprite, GIBTYPE_17, NULL, NULL);
            actPostSprite(pSprite->index, 1024);
        }
        if (pTarget->extra && xsprite[pTarget->extra].health > 0)
        {
            int x = pTarget->x+mulscale30r(Cos(pXSprite->at16_0+pTarget->ang), pTarget->clipdist*2);
            int y = pTarget->y+mulscale30r(Sin(pXSprite->at16_0+pTarget->ang), pTarget->clipdist*2);
            int z = pTarget->z+pXSprite->at28_0;
            vec3_t pos = { x, y, z };
            setsprite(nSprite,&pos);
            xvel[nSprite] = xvel[nTarget];
            yvel[nSprite] = yvel[nTarget];
            zvel[nSprite] = zvel[nTarget];
        }
        else
        {
            GibSprite(pSprite, GIBTYPE_17, NULL, NULL);
            actPostSprite(pSprite->index, 1024);
        }
    }
    aiProcessDudes();
    gFX.fxProcess();
}

SPRITE * actSpawnSprite(int nSector, int x, int y, int z, int nStat, char a6)
{
    int nSprite = InsertSprite(nSector, nStat);
    if (nSprite >= 0)
        sprite[nSprite].extra = -1;
    else
    {
        nSprite = headspritestat[9];
        dassert(nSprite >= 0);
        dassert(nSector >= 0 && nSector < kMaxSectors);
        ChangeSpriteSect(nSprite, nSector);
        actPostSprite(nSprite, nStat);
    }
    vec3_t pos = { x, y, z };
    setsprite(nSprite, &pos);
    SPRITE *pSprite = &qsprite[nSprite];
    pSprite->type = 0;
    if (a6 && pSprite->extra == -1)
    {
        int nXSprite = dbInsertXSprite(nSprite);
        gSpriteHit[nXSprite].florhit = 0;
        gSpriteHit[nXSprite].ceilhit = 0;
    }
    return pSprite;
}

SPRITE * actSpawnSprite(SPRITE *pSource, int nStat);

SPRITE *sub_36878(SPRITE *pSource, short nType, int a3, int a4)
{
    SPRITE *pSprite2 = actSpawnSprite(pSource, 6);
    if (!pSprite2)
        return NULL;
    XSPRITE *pXSprite2 = &xsprite[pSprite2->extra];
    int angle = pSource->ang;
    int nDude = nType-kDudeBase;
    int x, y, z;
    z = a4 + pSource->z;
    if (a3 < 0)
    {
        x = pSource->x;
        y = pSource->y;
    }
    else
    {
        x = pSource->x+mulscale30r(Cos(angle), a3);
        y = pSource->y+mulscale30r(Sin(angle), a3);
    }
    pSprite2->type = nType;
    pSprite2->ang = angle;
    vec3_t pos = { x, y, z };
    setsprite(pSprite2->index, &pos);
    pSprite2->cstat |= 0x1101;
    pSprite2->clipdist = dudeInfo[nDude].ata;
    pXSprite2->health = dudeInfo[nDude].at2<<4;
    if (gSysRes.Lookup(dudeInfo[nDude].seqStartID, "SEQ"))
        seqSpawn(dudeInfo[nDude].seqStartID, 3, pSprite2->extra, -1);
    aiInitSprite(pSprite2);
    return pSprite2;
}

SPRITE * actSpawnSprite(SPRITE *pSource, int nStat)
{
    int nSprite = InsertSprite(pSource->sectnum, nStat);
    if (nSprite < 0)
    {
        nSprite = headspritestat[9];
        dassert(nSprite >= 0);
        dassert(pSource->sectnum >= 0 && pSource->sectnum < kMaxSectors);
        ChangeSpriteSect(nSprite, pSource->sectnum);
        actPostSprite(nSprite, nStat);
    }
    SPRITE *pSprite = &qsprite[nSprite];
    pSprite->x = pSource->x;
    pSprite->y = pSource->y;
    pSprite->z = pSource->z;
    xvel[nSprite] = xvel[pSource->index];
    yvel[nSprite] = yvel[pSource->index];
    zvel[nSprite] = zvel[pSource->index];
    pSprite->hitag = 0;
    int nXSprite = dbInsertXSprite(nSprite);
    gSpriteHit[nXSprite].florhit = 0;
    gSpriteHit[nXSprite].ceilhit = 0;
    return pSprite;
}

SPRITE * actSpawnThing(int nSector, int x, int y, int z, int nThingType)
{
    dassert(nThingType >= kThingBase && nThingType < kThingMax);
    SPRITE *pSprite = actSpawnSprite(nSector, x, y, z, 4, 1);
    int nType = nThingType-kThingBase;
    int nThing = pSprite->index;
    int nXThing = pSprite->extra;
    pSprite->type = nThingType;
    dassert(nXThing > 0 && nXThing < kMaxXSprites);
    XSPRITE *pXThing = &xsprite[nXThing];
    THINGINFO *pThingInfo = &thingInfo[nType];
    pXThing->health = pThingInfo->at0<<4;
    pSprite->clipdist = pThingInfo->at4;
    pSprite->hitag = pThingInfo->at5;
    if (pSprite->hitag & 2)
        pSprite->hitag |= 4;
    pSprite->cstat |= pThingInfo->atf;
    pSprite->picnum = pThingInfo->at11;
    pSprite->shade = pThingInfo->at13;
    pSprite->pal = pThingInfo->at14;
    if (pThingInfo->at15)
        pSprite->xrepeat = pThingInfo->at15;
    if (pThingInfo->at16)
        pSprite->yrepeat = pThingInfo->at16;
    SetBitString(show2dsprite, pSprite->index);
    switch (nThingType)
    {
    case 432:
        pXThing->at10_0 = 0;
        pXThing->at12_0 = 0;
        pXThing->at14_0 = 0;
        pXThing->at18_2 = 0;
        pXThing->at1_6 = 1;
        pXThing->atd_1 = 1;
        pXThing->atd_2 = 0;
        break;
    case 431:
        pXThing->at10_0 = 0;
        pXThing->at12_0 = 0;
        pXThing->at14_0 = 0;
        pXThing->at18_2 = 0;
        pXThing->at1_6 = 1;
        pXThing->atd_1 = 0;
        pXThing->atd_2 = 0;
        break;
    case 427:
        pXThing->at10_0 = 8;
        pXThing->at12_0 = 0;
        pXThing->at14_0 = 0;
        pXThing->at18_2 = 318;
        pXThing->at20_0 = gFrame+180.0;
        pXThing->at17_5 = 1;
        pXThing->at1_6 = 1;
        pXThing->atd_1 = 0;
        pXThing->atd_2 = 0;
        break;
    case 425:
    case 426:
        if (nThingType == 425)
            pXThing->at10_0 = 19;
        else if (nThingType == 426)
            pXThing->at10_0 = 8;
        pXThing->at12_0 = 0;
        pXThing->at14_0 = 0;
        pXThing->at18_2 = 318;
        pXThing->at20_0 = gFrame+180.0;
        pXThing->at17_5 = 1;
        pXThing->at1_6 = 1;
        pXThing->atd_1 = 0;
        pXThing->atd_2 = 0;
        break;
    case 418:
        evPost(nThing, 3, 0, CALLBACK_ID_8);
        sfxPlay3DSound(pSprite, 450, 0, 0);
        break;
    case 419:
        sfxPlay3DSound(pSprite, 450, 0, 0);
        evPost(nThing, 3, 0, CALLBACK_ID_8);
        break;
    case 420:
        evPost(nThing, 3, 0, CALLBACK_ID_8);
        break;
    }
    return pSprite;
}

SPRITE * actFireThing(SPRITE *pSprite, int a2, int a3, int a4, int thingType, int a6)
{
    dassert(thingType >= kThingBase && thingType < kThingMax);
    int x = pSprite->x+mulscale30(a2, Cos(pSprite->ang+512));
    int y = pSprite->y+mulscale30(a2, Sin(pSprite->ang+512));
    int z = pSprite->z+a3;
    x += mulscale28(pSprite->clipdist, Cos(pSprite->ang));
    y += mulscale28(pSprite->clipdist, Sin(pSprite->ang));
    if (HitScan(pSprite, z, x-pSprite->x, y-pSprite->y, 0, CLIPMASK0, pSprite->clipdist) != -1)
    {
        x = gHitInfo.hitx-mulscale28(pSprite->clipdist<<1, Cos(pSprite->ang));
        y = gHitInfo.hity-mulscale28(pSprite->clipdist<<1, Sin(pSprite->ang));
    }
    SPRITE *pThing = actSpawnThing(pSprite->sectnum, x, y, z, thingType);
    actPropagateSpriteOwner(pThing, pSprite);
    pThing->ang = pSprite->ang;
    xvel[pThing->index] = mulscale30(a6, Cos(pThing->ang));
    yvel[pThing->index] = mulscale30(a6, Sin(pThing->ang));
    zvel[pThing->index] = mulscale(a6, a4, 14);
    xvel[pThing->index] += xvel[pSprite->index]/2;
    yvel[pThing->index] += yvel[pSprite->index]/2;
    zvel[pThing->index] += zvel[pSprite->index]/2;
    return pThing;
}

SPRITE* actFireMissile(SPRITE *pSprite, int a2, int a3, int a4, int a5, int a6, int nType)
{
    dassert(nType >= kMissileBase && nType < kMissileMax);
    char v4 = 0;
    int nSprite = pSprite->index;
    MissileType *pMissileInfo = &missileInfo[nType-kMissileBase];
    int x = pSprite->x+mulscale30(a2, Cos(pSprite->ang+512));
    int y = pSprite->y+mulscale30(a2, Sin(pSprite->ang+512));
    int z = pSprite->z+a3;
    int clipdist = pMissileInfo->atd+pSprite->clipdist;
    x += mulscale28(clipdist, Cos(pSprite->ang));
    y += mulscale28(clipdist, Sin(pSprite->ang));
    int hit = HitScan(pSprite, z, x-pSprite->x, y-pSprite->y, 0, CLIPMASK0, clipdist);
    if (hit != -1)
    {
        if (hit == 3 || hit == 0)
        {
            v4 = 1;
            x = gHitInfo.hitx-mulscale28(Cos(pSprite->ang), 16);
            y = gHitInfo.hity-mulscale28(Sin(pSprite->ang), 16);
        }
        else
        {
            x = gHitInfo.hitx-mulscale28(pMissileInfo->atd<<1, Cos(pSprite->ang));
            y = gHitInfo.hity-mulscale28(pMissileInfo->atd<<1, Sin(pSprite->ang));
        }
    }
    SPRITE *pMissile = actSpawnSprite(pSprite->sectnum, x, y, z, 5, 1);
    int nMissile = pMissile->index;
    SetBitString(show2dsprite, nMissile);
    pMissile->type = nType;
    pMissile->shade = pMissileInfo->atc;
    pMissile->pal = 0;
    pMissile->clipdist = pMissileInfo->atd;
    pMissile->hitag = 1;
    pMissile->xrepeat = pMissileInfo->ata;
    pMissile->yrepeat = pMissileInfo->atb;
    pMissile->picnum = pMissileInfo->picnum;
    pMissile->ang = (pSprite->ang+pMissileInfo->at6)&2047;
    xvel[nMissile] = mulscale(pMissileInfo->at2, a4, 14);
    yvel[nMissile] = mulscale(pMissileInfo->at2, a5, 14);
    zvel[nMissile] = mulscale(pMissileInfo->at2, a6, 14);
    actPropagateSpriteOwner(pMissile, pSprite);
    pMissile->cstat |= 1;
    int nXSprite = pMissile->extra;
    dassert(nXSprite > 0 && nXSprite < kMaxXSprites);
    xsprite[nXSprite].target = -1;
    evPost(nMissile, 3, 600, CALLBACK_ID_1);
    switch (nType)
    {
    case 315:
        evPost(nMissile, 3, 0, CALLBACK_ID_0);
        break;
    case 302:
        evPost(nMissile, 3, 0, CALLBACK_ID_15);
        break;
    case 309:
        seqSpawn(29, 3, nXSprite, -1);
        break;
    case 300:
        pMissile->cstat |= 16;
        break;
    case 306:
        sfxPlay3DSound(pMissile, 251, 0, 0);
        break;
    case 307:
        seqSpawn(2, 3, nXSprite, -1);
        sfxPlay3DSound(pMissile, 493, 0, 0);
        break;
    case 312:
        seqSpawn(61, 3, nXSprite, nNapalmClient);
        sfxPlay3DSound(pMissile, 441, 0, 0);
        break;
    case 305:
        seqSpawn(22, 3, nXSprite, nFireballClient);
        sfxPlay3DSound(pMissile, 441, 0, 0);
        break;
    case 308:
        seqSpawn(27, 3, nXSprite, -1);
        xvel[nMissile] += xvel[nSprite]/2+Random2(0x11111);
        yvel[nMissile] += yvel[nSprite]/2+Random2(0x11111);
        zvel[nMissile] += zvel[nSprite]/2+Random2(0x11111);
        break;
    case 313:
        seqSpawn(61, 3, nXSprite, dword_2192E0);
        sfxPlay3DSound(pMissile, 441, 0, 0);
        break;
    case 314:
        seqSpawn(23, 3, nXSprite, dword_2192D8);
        xvel[nMissile] += xvel[nSprite]/2+Random2(0x11111);
        yvel[nMissile] += yvel[nSprite]/2+Random2(0x11111);
        zvel[nMissile] += zvel[nSprite]/2+Random2(0x11111);
        break;
    case 304:
        if (Chance(0x8000))
            seqSpawn(0, 3, nXSprite, -1);
        else
            seqSpawn(1, 3, nXSprite, -1);
        xvel[nMissile] += xvel[nSprite]/2+Random2(0x11111);
        yvel[nMissile] += yvel[nSprite]/2+Random2(0x11111);
        zvel[nMissile] += zvel[nSprite]/2+Random2(0x11111);
        break;
    case 303:
        evPost(nMissile, 3, 30, CALLBACK_ID_2);
        evPost(nMissile, 3, 0, CALLBACK_ID_3);
        sfxPlay3DSound(pMissile, 422, 0, 0);
        break;
    case 301:
        evPost(nMissile, 3, 0, CALLBACK_ID_3);
        sfxPlay3DSound(pMissile, 422, 0, 0);
        break;
    case 317:
        evPost(nMissile, 3, 0, CALLBACK_ID_7);
        break;
    case 311:
        sfxPlay3DSound(pMissile, 252, 0, 0);
        break;
    }
    if (v4)
    {
        actImpactMissile(pMissile, hit);
        pMissile = NULL;
    }
    return pMissile;
}

int actGetRespawnTime(SPRITE *pSprite)
{
    int nXSprite = pSprite->extra;
    if (nXSprite <= 0)
        return -1;
    XSPRITE *pXSprite = &xsprite[nXSprite];
    if (IsDudeSprite(pSprite) && !IsPlayerSprite(pSprite))
    {
        if (pXSprite->at18_0 == 2 || (pXSprite->at18_0 != 1 && gGameOptions.nMonsterSettings == 2))
            return gGameOptions.nMonsterRespawnTime;
        return -1;
    }
    if (IsWeaponSprite(pSprite))
    {
        if (pXSprite->at18_0 == 3 || gGameOptions.nWeaponSettings == 1)
            return 0;
        if (pXSprite->at18_0 != 1 && gGameOptions.nWeaponSettings != 0)
            return gGameOptions.nWeaponRespawnTime;
        return -1;
    }
    if (IsAmmoSprite(pSprite))
    {
        if (pXSprite->at18_0 == 2 || (pXSprite->at18_0 != 1 && gGameOptions.nWeaponSettings != 0))
            return gGameOptions.nWeaponRespawnTime;
        return -1;
    }
    if (IsItemSprite(pSprite))
    {
        if (pXSprite->at18_0 == 3 && gGameOptions.nGameType == 1)
            return 0;
        if (pXSprite->at18_0 == 2 || (pXSprite->at18_0 != 1 && gGameOptions.nItemSettings != 0))
        {
            switch (pSprite->type)
            {
            case 113:
            case 117:
            case 124:
                return gGameOptions.nSpecialRespawnTime;
            case 114:
                return gGameOptions.nSpecialRespawnTime<<1;
            default:
                return gGameOptions.nItemRespawnTime;
            }
        }
        return -1;
    }
    return -1;
}

bool actCheckRespawn(SPRITE *pSprite)
{
    int nSprite = pSprite->index;
    int nXSprite = pSprite->extra;
    if (nXSprite > 0)
    {
        XSPRITE *pXSprite = &xsprite[nXSprite];
        int nRespawnTime = actGetRespawnTime(pSprite);
        if (nRespawnTime < 0)
            return 0;
        pXSprite->atb_4 = 1;
        if (pSprite->type >= kThingBase && pSprite->type < kThingMax)
        {
            pXSprite->atb_4 = 3;
            if (pSprite->type == 400)
                pSprite->cstat |= 32768;
        }
        if (nRespawnTime > 0)
        {
            if (pXSprite->atb_4 == 1)
                nRespawnTime = mulscale16(nRespawnTime, 0xa000);
            pSprite->owner = pSprite->statnum;
            actPostSprite(pSprite->index, 8);
            pSprite->hitag |= 16;
            if (pSprite->type >= kDudeBase && pSprite->type < kDudeMax)
            {
                pSprite->cstat &= ~257;
                pSprite->x = baseSprite[nSprite].x;
                pSprite->y = baseSprite[nSprite].y;
                pSprite->z = baseSprite[nSprite].z;
            }
            evPost(nSprite, 3, nRespawnTime, CALLBACK_ID_9);
        }
        return 1;
    }
    return  0;
}

bool actCanSplatWall(int nWall)
{
    dassert(nWall >= 0 && nWall < kMaxWalls);
    WALL *pWall = &qwall[nWall];
    if (pWall->cstat & 16384)
        return 0;
    if (pWall->cstat & 32768)
        return 0;
    if (pWall->lotag >= 500 && pWall->lotag < 512)
        return 0;
    if (pWall->nextsector != -1)
    {
        SECTOR *pSector = &qsector[pWall->nextsector];
        if (pSector->lotag >= 600 && pSector->lotag < 620)
            return 0;
    }
    return 1;
}

void actFireVector(SPRITE *pShooter, int a2, int a3, int a4, int a5, int a6, VECTOR_TYPE vectorType)
{
    int nShooter = pShooter->index;
    dassert(vectorType >= 0 && vectorType < kVectorMax);
    VECTORDATA *pVectorData = &gVectorData[vectorType];
    int nRange = pVectorData->at9;
    int hit = VectorScan(pShooter, a2, a3, a4, a5, a6, nRange, 1);
    if (hit == 3)
    {
        int nSprite = gHitInfo.hitsprite;
        dassert(nSprite >= 0 && nSprite < kMaxSprites);
        SPRITE *pSprite = &qsprite[nSprite];
        if (IsPlayerSprite(pSprite))
        {
            PLAYER *pPlayer = &gPlayer[pSprite->type-kDudePlayer1];
            if (powerupCheck(pPlayer, 24))
            {
                gHitInfo.hitsprite = nShooter;
                gHitInfo.hitx = pShooter->x;
                gHitInfo.hity = pShooter->y;
                gHitInfo.hitz = pShooter->z;
            }
        }
    }
    int x = gHitInfo.hitx-mulscale(a4, 16, 14);
    int y = gHitInfo.hity-mulscale(a5, 16, 14);
    int z = gHitInfo.hitz-mulscale(a6, 256, 14);
    short nSector = gHitInfo.hitsect;
    char nSurf = 0;
    if (nRange == 0 || approxDist(gHitInfo.hitx-pShooter->x, gHitInfo.hity-pShooter->y) < nRange)
    {
        switch (hit)
        {
        case 1:
        {
            int nSector = gHitInfo.hitsect;
            if (sector[nSector].ceilingstat&1)
                nSurf = 0;
            else
                nSurf = surfType[sector[nSector].ceilingpicnum];
            break;
        }
        case 2:
        {
            int nSector = gHitInfo.hitsect;
            if (sector[nSector].floorstat&1)
                nSurf = 0;
            else
                nSurf = surfType[sector[nSector].floorpicnum];
            break;
        }
        case 0:
        {
            int nWall = gHitInfo.hitwall;
            dassert(nWall >= 0 && nWall < kMaxWalls);
            nSurf = surfType[wall[nWall].picnum];
            if (actCanSplatWall(nWall))
            {
                int x = gHitInfo.hitx-mulscale(a4, 16, 14);
                int y = gHitInfo.hity-mulscale(a5, 16, 14);
                int z = gHitInfo.hitz-mulscale(a6, 256, 14);
                int nSurf = surfType[wall[nWall].picnum];
                dassert(nSurf < kSurfMax);
                if (pVectorData->at1d[nSurf].at0 >= 0)
                {
                    SPRITE *pFX = gFX.fxSpawn(pVectorData->at1d[nSurf].at0, nSector, x, y, z, 0);
                    if (pFX)
                    {
                        pFX->ang = (GetWallAngle(nWall)+512)&2047;
                        pFX->cstat |= 16;
                    }
                }
            }
            break;
        }
        case 4:
        {
            int nWall = gHitInfo.hitwall;
            dassert(nWall >= 0 && nWall < kMaxWalls);
            nSurf = surfType[wall[nWall].picnum];
            int nXWall = wall[nWall].extra;
            if (nXWall > 0)
            {
                XWALL *pXWall = &xwall[nXWall];
                if (pXWall->at10_6)
                    trTriggerWall(nWall, pXWall, 51);
            }
            break;
        }
        case 3:
        {
            int nSprite = gHitInfo.hitsprite;
            nSurf = surfType[sprite[nSprite].picnum];
            dassert(nSprite >= 0 && nSprite < kMaxSprites);
            SPRITE *pSprite = &qsprite[nSprite];
            x -= mulscale(a4, 112, 14);
            y -= mulscale(a5, 112, 14);
            z -= mulscale(a6, 112<<4, 14);
            int shift = 4;
            if (vectorType == VECTOR_TYPE_0 && !IsPlayerSprite(pSprite))
                shift = 3;
            actDamageSprite(nShooter, pSprite, pVectorData->at0, pVectorData->at1<<shift);
            int nXSprite = pSprite->extra;
            if (nXSprite > 0)
            {
                XSPRITE *pXSprite = &xsprite[nXSprite];
                if (pXSprite->atd_7)
                    trTriggerSprite(nSprite, pXSprite, 31);
            }
            if (pSprite->statnum == 4)
            {
                int t = thingInfo[pSprite->type-kThingBase].at2;
                if (t > 0 && pVectorData->at5)
                {
                    int t2 = divscale(pVectorData->at5, t, 8);
                    xvel[nSprite] += mulscale16(a4, t2);
                    yvel[nSprite] += mulscale16(a5, t2);
                    zvel[nSprite] += mulscale16(a6, t2);
                }
                if (pVectorData->at11)
                {
                    XSPRITE *pXSprite = &xsprite[nXSprite];
                    if (!pXSprite->at2c_0)
                        evPost(nSprite, 3, 0, CALLBACK_ID_0);
                    actBurnSprite(actSpriteIdToOwnerId(nShooter), pXSprite, pVectorData->at11);
                }
            }
            if (pSprite->statnum == 6)
            {
                int t = dudeInfo[pSprite->type-kDudeBase].at4;
                if (t > 0 && pVectorData->at5)
                {
                    int t2 = divscale(pVectorData->at5, t, 8);
                    xvel[nSprite] += mulscale16(a4, t2);
                    yvel[nSprite] += mulscale16(a5, t2);
                    zvel[nSprite] += mulscale16(a6, t2);
                }
                if (pVectorData->at11)
                {
                    XSPRITE *pXSprite = &xsprite[nXSprite];
                    if (!pXSprite->at2c_0)
                        evPost(nSprite, 3, 0, CALLBACK_ID_0);
                    actBurnSprite(actSpriteIdToOwnerId(nShooter), pXSprite, pVectorData->at11);
                }
                if (Chance(pVectorData->atd))
                {
                    int t = gVectorData[19].at9;
                    a4 += Random3(4000);
                    a5 += Random3(4000);
                    a6 += Random3(4000);
                    if (HitScan(pSprite, gHitInfo.hitz, a4, a5, a6, CLIPMASK1, t) == 0)
                    {
                        if (approxDist(gHitInfo.hitx-pSprite->x, gHitInfo.hity-pSprite->y) <= t)
                        {
                            int nWall = gHitInfo.hitwall;
                            int nSector = gHitInfo.hitsect;
                            if (actCanSplatWall(nWall))
                            {
                                int x = gHitInfo.hitx - mulscale(a4, 16, 14);
                                int y = gHitInfo.hity - mulscale(a5, 16, 14);
                                int z = gHitInfo.hitz - mulscale(a6, 16<<4, 14);
                                int nSurf = surfType[wall[nWall].picnum];
                                VECTORDATA *pVectorData = &gVectorData[19];
                                FX_ID t2 = pVectorData->at1d[nSurf].at1;
                                FX_ID t3 = pVectorData->at1d[nSurf].at2;
                                SPRITE *pFX = NULL;
                                if (t2 > -1 && (t3 == -1 || Chance(0x4000)))
                                    pFX = gFX.fxSpawn(t2, nSector, x, y, z, 0);
                                else if(t3 > -1)
                                    pFX = gFX.fxSpawn(t3, nSector, x, y, z, 0);
                                if (pFX)
                                {
                                    zvel[pFX->index] = 0x2222;
                                    pFX->ang = (GetWallAngle(nWall)+512)&2047;
                                    pFX->cstat |= 16;
                                }
                            }
                        }
                    }
                }
                for (int i = 0; i < pVectorData->at15; i++)
                    if (Chance(pVectorData->at19))
                        fxSpawnBlood(pSprite, pVectorData->at1<<4);
            }
            break;
        }
        }
    }
    dassert(nSurf < kSurfMax);
    if (pVectorData->at1d[nSurf].at1 >= 0)
        gFX.fxSpawn(pVectorData->at1d[nSurf].at1, nSector, x, y, z, 0);
    if (pVectorData->at1d[nSurf].at2 >= 0)
        gFX.fxSpawn(pVectorData->at1d[nSurf].at2, nSector, x, y, z, 0);
    if (pVectorData->at1d[nSurf].at3 >= 0)
        sfxPlay3DSound(x, y, z, pVectorData->at1d[nSurf].at3, nSector);
}

void FireballSeqCallback(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    SPRITE *pFX = gFX.fxSpawn(FX_11, pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0);
    if (pFX)
    {
        int nFX = pFX->index;
        xvel[nFX] = xvel[nSprite];
        yvel[nFX] = yvel[nSprite];
        zvel[nFX] = zvel[nSprite];
    }
}

void NapalmSeqCallback(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    SPRITE *pFX = gFX.fxSpawn(FX_12, pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0);
    if (pFX)
    {
        int nFX = pFX->index;
        xvel[nFX] = xvel[nSprite];
        yvel[nFX] = yvel[nSprite];
        zvel[nFX] = zvel[nSprite];
    }
}

void sub_3888C(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    SPRITE *pFX = gFX.fxSpawn(FX_32, pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0);
    if (pFX)
    {
        int nFX = pFX->index;
        xvel[nFX] = xvel[nSprite];
        yvel[nFX] = yvel[nSprite];
        zvel[nFX] = zvel[nSprite];
    }
}

void sub_38938(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    SPRITE *pFX = gFX.fxSpawn(FX_33, pSprite->sectnum, pSprite->x, pSprite->y, pSprite->z, 0);
    if (pFX)
    {
        int nFX = pFX->index;
        xvel[nFX] = xvel[nSprite];
        yvel[nFX] = yvel[nSprite];
        zvel[nFX] = zvel[nSprite];
    }
}

void TreeToGibCallback(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    pSprite->type = 417;
    pXSprite->at1_6 = 1;
    pXSprite->at10_0 = 15;
    pXSprite->at12_0 = 0;
    pXSprite->at14_0 = 0;
    pXSprite->health = thingInfo[17].at0;
    pXSprite->at18_2 = 312;
    pSprite->cstat |= 257;
}

void DudeToGibCallback1(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    pSprite->type = 426;
    pXSprite->at10_0 = 8;
    pXSprite->at12_0 = 0;
    pXSprite->at14_0 = 0;
    pXSprite->health = thingInfo[26].at0;
    pXSprite->at18_2 = 319;
    pXSprite->atd_1 = 0;
    pXSprite->atd_2 = 0;
    pXSprite->at17_5 = 0;
    pXSprite->at20_0 = gFrameClock;
    pXSprite->at1_6 = 1;
}

void DudeToGibCallback2(int, int nXSprite)
{
    XSPRITE *pXSprite = &xsprite[nXSprite];
    int nSprite = pXSprite->reference;
    SPRITE *pSprite = &qsprite[nSprite];
    pSprite->type = 426;
    pXSprite->at10_0 = 3;
    pXSprite->at12_0 = 0;
    pXSprite->at14_0 = 0;
    pXSprite->health = thingInfo[26].at0;
    pXSprite->at18_2 = 319;
    pXSprite->atd_1 = 0;
    pXSprite->atd_2 = 0;
    pXSprite->at17_5 = 0;
    pXSprite->at20_0 = gFrameClock;
    pXSprite->at1_6 = 1;
}

void actPostSprite(int nSprite, int nStatus)
{
    int n;
    dassert(gPostCount < kMaxSprites);
    dassert(nSprite < kMaxSprites && sprite[nSprite].statnum < kMaxStatus);
    dassert(nStatus >= 0 && nStatus <= kStatFree);
    if (sprite[nSprite].hitag&32)
    {
        for (n = 0; n < gPostCount; n++)
            if (gPost[n].at0 == nSprite)
                break;
        dassert(n < gPostCount);
    }
    else
    {
        n = gPostCount;
        sprite[nSprite].hitag |= 32;
        gPostCount++;
    }
    gPost[n].at0 = nSprite;
    gPost[n].at2 = nStatus;
}

void actPostProcess(void)
{
    for (int i = 0; i < gPostCount; i++)
    {
        POSTPONE *pPost = &gPost[i];
        int nSprite = pPost->at0;
        SPRITE *pSprite = &qsprite[nSprite];
        pSprite->hitag &= ~32;
        int nStatus = pPost->at2;
        if (nStatus == kStatFree)
        {
            evKill(nSprite, 3);
            if (sprite[nSprite].extra > 0)
                seqKill(3, sprite[nSprite].extra);
            DeleteSprite(nSprite);
        }
        else
            ChangeSpriteStat(nSprite, nStatus);
    }
    gPostCount = 0;
}

void MakeSplash(SPRITE *pSprite, XSPRITE *pXSprite)
{
    pSprite->hitag &= ~2;
    int nXSprite = pSprite->extra;
    pSprite->z -= 4<<8;
    int nSurface = tileGetSurfType(gSpriteHit[nXSprite].florhit);
    switch (pSprite->type)
    {
    case 423:
        if (nSurface == 5)
        {
            seqSpawn(6, 3, nXSprite, -1);
            sfxPlay3DSound(pSprite, 356, -1, 0);
        }
        else
        {
            seqSpawn(7, 3, nXSprite, -1);
            sfxPlay3DSound(pSprite, 354, -1, 0);
        }
        break;
    case 424:
        seqSpawn(8, 3, nXSprite, -1);
        sfxPlay3DSound(pSprite, 354, -1, 0);
        break;
    }
}

class ActorLoadSave : public LoadSave
{
    virtual void Load(void);
    virtual void Save(void);
};

void ActorLoadSave::Load(void)
{
    Read(gSpriteHit, sizeof(gSpriteHit));
    Read(gAffectedSectors, sizeof(gAffectedSectors));
    Read(gAffectedXWalls, sizeof(gAffectedXWalls));
    Read(&gPostCount, sizeof(gPostCount));
    Read(gPost, sizeof(gPost));
    actInit();
}

void ActorLoadSave::Save(void)
{
    Write(gSpriteHit, sizeof(gSpriteHit));
    Write(gAffectedSectors, sizeof(gAffectedSectors));
    Write(gAffectedXWalls, sizeof(gAffectedXWalls));
    Write(&gPostCount, sizeof(gPostCount));
    Write(gPost, sizeof(gPost));
}

static ActorLoadSave myLoadSave;
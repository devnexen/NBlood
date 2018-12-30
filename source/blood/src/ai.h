#pragma once

#include "compat.h"
#include "common_game.h"
#include "actor.h"
#include "db.h"

struct AISTATE {
    int at0; // seq
    int at4; // seq callback
    int at8;
    void(*atc)(SPRITE *, XSPRITE *);
    void(*at10)(SPRITE *, XSPRITE *);
    void(*at14)(SPRITE *, XSPRITE *);
    AISTATE *at18; // next state ?
};

enum AI_SFX_PRIORITY {
    AI_SFX_PRIORITY_0 = 0,
    AI_SFX_PRIORITY_1,
    AI_SFX_PRIORITY_2,
};


struct DUDEEXTRA_at6_u1
{
    int at0;
    int at4;
    char at8;
};

struct DUDEEXTRA_at6_u2
{
    int at0;
    char at4;
};

struct DUDEEXTRA
{
    int at0;
    char at4;
    AI_SFX_PRIORITY at5;
    union
    {
        DUDEEXTRA_at6_u1 u1;
        DUDEEXTRA_at6_u2 u2;
    } at6;
    //DUDEEXTRA_at6 at6;
};

struct TARGETTRACK {
    int at0;
    int at4;
    int at8; // view angle
    int atc;
    int at10; // Move predict
};

extern int dword_138BB0[5];
extern DUDEEXTRA gDudeExtra[];
int gDudeSlope[];

bool sub_5BDA8(SPRITE *pSprite, int nSeq);
void aiPlay3DSound(SPRITE *pSprite, int a2, AI_SFX_PRIORITY a3, int a4);
void aiNewState(SPRITE *pSprite, XSPRITE *pXSprite, AISTATE *pAIState);
void aiChooseDirection(SPRITE *pSprite, XSPRITE *pXSprite, int a3);
void aiMoveForward(SPRITE *pSprite, XSPRITE *pXSprite);
void aiMoveTurn(SPRITE *pSprite, XSPRITE *pXSprite);
void aiMoveDodge(SPRITE *pSprite, XSPRITE *pXSprite);
void aiActivateDude(SPRITE *pSprite, XSPRITE *pXSprite);
void aiSetTarget(XSPRITE *pXSprite, int x, int y, int z);
void aiSetTarget(XSPRITE *pXSprite, int nTarget);
int aiDamageSprite(SPRITE *pSprite, XSPRITE *pXSprite, int nSource, DAMAGE_TYPE nDmgType, int nDamage);
void aiThinkTarget(SPRITE *pSprite, XSPRITE *pXSprite);
void sub_5F15C(SPRITE *pSprite, XSPRITE *pXSprite);
void aiProcessDudes(void);
void aiInit(void);
void aiInitSprite(SPRITE *pSprite);
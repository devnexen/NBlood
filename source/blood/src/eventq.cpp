#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "build.h"
#include "common_game.h"

#include "callback.h"
#include "db.h"
#include "eventq.h"
#include "globals.h"
#include "loadsave.h"
#include "pqueue.h"
#include "triggers.h"

class EventQueue : public PriorityQueue
{
public:
    char IsNotEmpty(int nTime)
    {
        return fNodeCount > 0 && nTime >= queueItems[1].at0;
    }
    EVENT ERemove(void)
    {
        unsigned long node = Remove();
        return *(EVENT*)&node;
    }
    void Kill(int, int);
    void Kill(int, int, CALLBACK_ID);
};

EventQueue eventQ;

void EventQueue::Kill(int a1, int a2)
{
    EVENT evn = { a1, a2, 0, 0 };
    //evn.at0_0 = a1;
    //evn.at1_5 = a2;

    short vs = *(short*)&evn;
    for (int i = 1; i <= fNodeCount;)
    {
        if ((short)queueItems[i].at4 == vs)
            Delete(i);
        else
            i++;
    }
}

void EventQueue::Kill(int a1, int a2, CALLBACK_ID a3)
{
    EVENT evn = { a1, a2, kCommandCallback, a3 };
    int vc = *(int*)&evn;
    for (int i = 1; i <= fNodeCount;)
    {
        if (queueItems[i].at4 == vc)
            Delete(i);
        else
            i++;
    }
}

struct RXBUCKET
{
    unsigned int at0_0 : 13;
    unsigned int at1_5 : 3;
};

RXBUCKET rxBucket[1024+1];

int GetBucketChannel(RXBUCKET *pRX)
{
    switch (pRX->at1_5)
    {
    case 6:
    {
        int nIndex = pRX->at0_0;
        int nXIndex = sector[nIndex].extra;
        dassert(nXIndex > 0);
        return xsector[nXIndex].at8_0;
    }
    case 0:
    {
        int nIndex = pRX->at0_0;
        int nXIndex = wall[nIndex].extra;
        dassert(nXIndex > 0);
        return xwall[nXIndex].at8_0;
    }
    case 3:
    {
        int nIndex = pRX->at0_0;
        int nXIndex = sprite[nIndex].extra;
        dassert(nXIndex > 0);
        return xsprite[nXIndex].at5_2;
    }
    default:
        ThrowError("Unexpected rxBucket type %d, index %d", pRX->at1_5, pRX->at0_0);
        break;
    }
    return 0;
}

int CompareChannels(const void *a, const void *b)
{
    return GetBucketChannel((RXBUCKET*)a)-GetBucketChannel((RXBUCKET*)b);
}

unsigned short bucketHead[kMaxChannels+1];

void evInit(void)
{
    eventQ.fNodeCount = 0;
    int nCount = 0;
    for (int i = 0; i < numsectors; i++)
    {
        int nXSector = sector[i].extra;
        if (nXSector >= kMaxXSectors)
            ThrowError("Invalid xsector reference in sector %d", i);
        if (nXSector > 0 && xsector[nXSector].at8_0 > 0)
        {
            dassert(nCount < kMaxChannels);
            rxBucket[nCount].at1_5 = 6;
            rxBucket[nCount].at0_0 = i;
            nCount++;
        }
    }
    for (int i = 0; i < numwalls; i++)
    {
        int nXWall = wall[i].extra;
        if (nXWall >= kMaxXWalls)
            ThrowError("Invalid xwall reference in wall %d", i);
        if (nXWall > 0 && xwall[nXWall].at8_0 > 0)
        {
            dassert(nCount < kMaxChannels);
            rxBucket[nCount].at1_5 = 0;
            rxBucket[nCount].at0_0 = i;
            nCount++;
        }
    }
    for (int i = 0; i < kMaxSprites; i++)
    {
        if (sprite[i].statnum < kMaxStatus)
        {
            int nXSprite = sprite[i].extra;
            if (nXSprite >= kMaxXSprites)
                ThrowError("Invalid xsprite reference in sprite %d", i);
            if (nXSprite > 0 && xsprite[nXSprite].at5_2 > 0)
            {
                dassert(nCount < kMaxChannels);
                rxBucket[nCount].at1_5 = 3;
                rxBucket[nCount].at0_0 = i;
                nCount++;
            }
        }
    }
    // TODO: Use Watcom's qsort algorithm
    qsort(rxBucket, nCount, sizeof(RXBUCKET), CompareChannels);
    int i, j = 0;
    for (i = 0; i < 1024; i++)
    {
        bucketHead[i] = j;
        while(j < nCount && GetBucketChannel(&rxBucket[j]) == i)
            j++;
    }
    bucketHead[i] = j;
}

char evGetSourceState(int nType, int nIndex)
{
    switch (nType)
    {
    case 6:
    {
        int nXIndex = sector[nIndex].extra;
        dassert(nXIndex > 0 && nXIndex < kMaxXSectors);
        return xsector[nXIndex].at1_6;
    }
    case 0:
    {
        int nXIndex = wall[nIndex].extra;
        dassert(nXIndex > 0 && nXIndex < kMaxXWalls);
        return xwall[nXIndex].at1_6;
    }
    case 3:
    {
        int nXIndex = sprite[nIndex].extra;
        dassert(nXIndex > 0 && nXIndex < kMaxXSprites);
        return xsprite[nXIndex].at1_6;
    }
    }
    return 0;
}

void evSend(int nIndex, int nType, int rxId, COMMAND_ID command)
{
    if (command == COMMAND_ID_2)
        command = evGetSourceState(nType, nIndex) ? COMMAND_ID_1 : COMMAND_ID_0;
    else if (command == COMMAND_ID_4)
        command = evGetSourceState(nType, nIndex) ? COMMAND_ID_0 : COMMAND_ID_1;
    EVENT evn;
    evn.at0_0 = nIndex;
    evn.at1_5 = nType;
    evn.at2_0 = command;
    if (rxId > 0)
    {
        switch (rxId)
        {
        case 7:
        case 10:
            break;
        case 3:
            if (command < COMMAND_ID_64)
                ThrowError("Invalid TextOver command by xobject %d(type %d)", nIndex, nType);
            trTextOver(command-COMMAND_ID_64);
            return;
        case 4:
            levelEndLevel(0);
            return;
        case 5:
            levelEndLevel(1);
            return;
        case 1:
            if (command < COMMAND_ID_64)
                ThrowError("Invalid SetupSecret command by xobject %d(type %d)", nIndex, nType);
            levelSetupSecret(command - COMMAND_ID_64);
            break;
        case 2:
            if (command < COMMAND_ID_64)
                ThrowError("Invalid Secret command by xobject %d(type %d)", nIndex, nType);
            levelTriggerSecret(command - COMMAND_ID_64);
            break;
        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
        case 95:
        case 96:
        case 97:
            for (int nSprite = headspritestat[4]; nSprite >= 0; nSprite = nextspritestat[nSprite])
            {
                SPRITE *pSprite = &qsprite[nSprite];
                if (pSprite->hitag&32)
                    continue;
                int nXSprite = pSprite->extra;
                if (nXSprite > 0)
                {
                    XSPRITE *pXSprite = &xsprite[nXSprite];
                    if (pXSprite->at5_2 == rxId)
                        trMessageSprite(nSprite, evn);
                }
            }
            return;
        case 80:
        case 81:
            for (int nSprite = headspritestat[3]; nSprite >= 0; nSprite = nextspritestat[nSprite])
            {
                SPRITE *pSprite = &qsprite[nSprite];
                if (pSprite->hitag&32)
                    continue;
                int nXSprite = pSprite->extra;
                if (nXSprite > 0)
                {
                    XSPRITE *pXSprite = &xsprite[nXSprite];
                    if (pXSprite->at5_2 == rxId)
                        trMessageSprite(nSprite, evn);
                }
            }
            return;
        }
    }
    for (int i = bucketHead[rxId]; i < bucketHead[rxId+1]; i++)
    {
        if (evn.at1_5 != rxBucket[i].at1_5 || evn.at0_0 != rxBucket[i].at0_0)
        {
            switch (rxBucket[i].at1_5)
            {
            case 6:
                trMessageSector(rxBucket[i].at0_0, evn);
                break;
            case 0:
                trMessageWall(rxBucket[i].at0_0, evn);
                break;
            case 3:
            {
                int nSprite = rxBucket[i].at0_0;
                SPRITE *pSprite = &qsprite[nSprite];
                if (pSprite->hitag&32)
                    continue;
                int nXSprite = pSprite->extra;
                if (nXSprite > 0)
                {
                    XSPRITE *pXSprite = &xsprite[nXSprite];
                    if (pXSprite->at5_2 > 0)
                        trMessageSprite(nSprite, evn);
                }
                break;
            }
            }
        }
    }
}

void evPost(int nIndex, int nType, unsigned long nDelta, COMMAND_ID command)
{
    dassert(command != kCommandCallback);
    if (command == COMMAND_ID_2)
        command = evGetSourceState(nType, nIndex) ? COMMAND_ID_1 : COMMAND_ID_0;
    else if (command == COMMAND_ID_4)
        command = evGetSourceState(nType, nIndex) ? COMMAND_ID_0 : COMMAND_ID_1;
    EVENT evn;
    evn.at0_0 = nIndex;
    evn.at1_5 = nType;
    evn.at2_0 = command;
    // Inlined?
    eventQ.Insert(gFrameClock+nDelta, *(unsigned long*)&evn);
}

void evPost(int nIndex, int nType, unsigned long nDelta, CALLBACK_ID a4)
{
    EVENT evn;
    evn.at0_0 = nIndex;
    evn.at1_5 = nType;
    evn.at2_0 = kCommandCallback;
    evn.funcID = a4;
    eventQ.Insert(gFrameClock+nDelta, *(unsigned long*)&evn);
}

void evProcess(unsigned long nTime)
{
#if 0
    while (1)
    {
        // Inlined?
        char bDone;
        if (eventQ.fNodeCount > 0 && nTime >= eventQ.queueItems[1])
            bDone = 1;
        else
            bDone = 0;
        if (!bDone)
            break;
#endif
    while(eventQ.IsNotEmpty(nTime))
    {
        EVENT event = eventQ.ERemove();
        if (event.at2_0 == kCommandCallback)
        {
            dassert(event.funcID < kCallbackMax);
            dassert(gCallback[event.funcID] != NULL);
            gCallback[event.funcID](event.at0_0);
        }
        else
        {
            switch (event.at1_5)
            {
            case 6:
                trMessageSector(event.at0_0, event);
                break;
            case 0:
                trMessageWall(event.at0_0, event);
                break;
            case 3:
                trMessageSprite(event.at0_0, event);
                break;
            }
        }
    }
}

void evKill(int a1, int a2)
{
    eventQ.Kill(a1, a2);
}

void evKill(int a1, int a2, CALLBACK_ID a3)
{
    eventQ.Kill(a1, a2, a3);
}

class EventQLoadSave : public LoadSave
{
public:
    virtual void Load();
    virtual void Save();
};

void EventQLoadSave::Load()
{
    Read(&eventQ, sizeof(eventQ));
    Read(rxBucket, sizeof(rxBucket));
    Read(bucketHead, sizeof(bucketHead));
}

void EventQLoadSave::Save()
{
    Write(&eventQ, sizeof(eventQ));
    Write(rxBucket, sizeof(rxBucket));
    Write(bucketHead, sizeof(bucketHead));
}

static EventQLoadSave myLoadSave;
#pragma once
#include "controls.h"
#include "common_game.h"

enum PACKETMODE {
    PACKETMODE_0 = 0,
    PACKETMODE_1,
    PACKETMODE_2,
    PACKETMODE_3,
};

enum NETWORKMODE {
    NETWORK_NONE = 0,
    NETWORK_SERVER,
    NETWORK_CLIENT
};

extern char packet[576];
extern bool gStartNewGame;
extern PACKETMODE gPacketMode;
extern int gNetFifoClock;
extern int gNetFifoTail;
extern int gNetFifoHead[8];
extern int gPredictTail;
extern int gNetFifoMasterTail;
extern GINPUT gFifoInput[256][8];
extern int myMinLag[8];
extern int otherMinLag;
extern int myMaxLag;
extern unsigned long gChecksum[4];
extern unsigned long gCheckFifo[256][8][4];
extern int gCheckHead[8];
extern int gSendCheckTail;
extern int gCheckTail;
extern int gInitialNetPlayers;
extern int gBufferJitter;
extern int gPlayerReady[8];
extern int gSyncRate;
extern bool bNoResend;
extern bool gRobust;
extern bool bOutOfSync;
extern bool ready2send;
extern NETWORKMODE gNetMode;
extern char gNetAddress[32];



struct PKT_STARTGAME {
    short version;
    char gameType, difficulty, monsterSettings, weaponSettings, itemSettings, respawnSettings;
    char episodeId, levelId;
    int unk;
    char userMap, userMapName[13];
};

extern PKT_STARTGAME gPacketStartGame;


inline void PutPacketByte(char *&p, int a2)
{
    //dassert(p - packet + 1 < sizeof(packet));
    *p++ = a2;
}

inline void PutPacketWord(char *&p, int a2)
{
    //dassert(p - packet + 2 < sizeof(packet));
    *(short*)p = a2;
    p += 2;
}

inline void PutPacketDWord(char *&p, int a2)
{
    //dassert(p - packet + 4 < sizeof(packet));
    *(int*)p = a2;
    p += 4;
}

inline void PutPacketBuffer(char *&p, const void *pBuffer, int size)
{
    //dassert(p + size < packet + sizeof(packet));
    memcpy(p, pBuffer, size);
    p += size;
}

inline char GetPacketByte(char *&p)
{
    return *p++;
}

inline short GetPacketWord(char *&p)
{
    short t = *(short*)p;
    p += 2;
    return t;
}

inline int GetPacketDWord(char *&p)
{
    int t = *(int*)p;
    p += 4;
    return t;
}

inline void GetPacketBuffer(char *&p, void *pBuffer, int size)
{
    //dassert(p + size < packet + sizeof(packet));
    memcpy(pBuffer, p, size);
    p += size;
}

void sub_79760(void);
void netBroadcastMessage(int nPlayer, const char *pzMessage);
void netWaitForEveryone(char a1);
void sub_7AC28(const char *pzString);
void netGetPackets(void);
void netBroadcastTaunt(int nPlayer, int nTaunt);
void CalcGameChecksum(void);
void netBroadcastMyLogoff(void);
void netInitialize(void);
void netBroadcastPlayerInfo(int nPlayer);
void netCheckSync(void);
void netGetInput(void);
void netPlayerQuit(int nPlayer);
void netUpdate(void);
void netDeinitialize(void);
void netBroadcastNewGame(void);
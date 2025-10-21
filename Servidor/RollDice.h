#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>

#include "smLib3d/smd3d.h"
#include "sinbaram/sinItem.h"

namespace IO
{
    class PacketReader;
}

#ifdef _W_SERVER
class smCHAR;
class rsPLAYINFO;

namespace Server
{
    struct RollDicePlayerInfo
    {
        rsPLAYINFO* Player;
        int Number;
        int ChooseOrder;
    };

    struct RollDiceDrops
    {
        bool BeginDice;
        int CurrentOrder;

        unsigned int ExpirationTime;
        unsigned int SkipTime;

        std::queue<sITEMINFO> ItemQueue;
        std::vector<RollDicePlayerInfo> Players;
    };

    class RollDice
    {
    public:
        RollDice(const RollDice&) = delete;
        RollDice& operator=(const RollDice&) = delete;
        ~RollDice() = default;
        static RollDice& GetInstance();

    private:
        RollDice();

    public:
        void PushMonsterKilled(const smCHAR* Monster);
        void Update();
        void HandlePacket(IO::PacketReader& Packet, rsPLAYINFO* Player, unsigned int PacketCode);
        void RewardPlayer(rsPLAYINFO* Player, const sITEMINFO& Item, int Number);
        void OnPlayerQuitGame(rsPLAYINFO* Player);

    private:
        std::unordered_map<int, RollDiceDrops> m_DropMap;
        int m_CurrentKey;
    };
}
#else

namespace Game
{
    class RollDice
    {
        using Ranking = std::tuple<int, int, std::string>;

    public:
        RollDice(const RollDice&) = delete;
        RollDice& operator=(const RollDice&) = delete;
        ~RollDice() = default;
        static RollDice& GetInstance();

    private:
        RollDice();

    public:
        void Initialize();
        void Open();
        void Close();
        bool IsOpen() const;
        bool IsHover() const;
        void Update();
        void Render();

        void HandlePacket(IO::PacketReader& Packet, unsigned int PacketCode);
        bool LButtonDown();

    private:
        void Roll();
        void Pass();

    private:
        bool m_Open;
        bool m_WaitDice;

        int m_ServerKey;

        unsigned int m_ExpirationTime;
        unsigned int m_CloseTime;

        sITEM m_ShowItem;

        std::vector<Ranking> m_Users;

        IDirect3DTexture9* m_BackgroundTexture;
        IDirect3DTexture9* m_CloseTexture;
        IDirect3DTexture9* m_RollTexture;
        IDirect3DTexture9* m_PassTexture;
        IDirect3DTexture9* m_RankingTexture;
    };
}
#endif
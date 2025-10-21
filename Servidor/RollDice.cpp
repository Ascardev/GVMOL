#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <process.h>

#include "RollDice.h"

#include "sinbaram/sinLinkHeader.h"

#include "IO/PacketReader.h"
#include "IO/PacketWriter.h"

#ifdef _W_SERVER
#include "field.h"
#include "SrcServer/onserver.h"

constexpr unsigned int MaximumDropDistance = 16 * 64 * 16 * 64;
constexpr unsigned int MaxRollDiceTime = 15 * 1000;
constexpr unsigned int DelayForSkippingTime = 3 * 1000;

//
extern std::unordered_map<DWORD, std::unordered_map<rsPLAYINFO*, DWORD>> DamageList;
extern int rsSendServerChatMessageToAllUser(int Color, char* msg, ...);

namespace Server
{
	RollDice& RollDice::GetInstance()
	{
		static RollDice Instance;
		return Instance;
	}

	RollDice::RollDice()
	{
		m_CurrentKey = GetRandomPos(INT32_MIN, INT32_MAX);
	}

	void RollDice::PushMonsterKilled(const smCHAR* Monster)
	{
		LOGEx("KitaDevs", "RollDice() -> PushMonsterKilled( %d )", 0);

		// Create drop infos.
		if (Monster->smMonsterInfo.FallItemPerMax == 0 || Monster->smMonsterInfo.FallItemCount == 0)
			return;

		RollDiceDrops Drops = { 0 };
		auto lpMonInfo = &Monster->smMonsterInfo;

		for (int i = 0; i < lpMonInfo->FallItemMax; i++)
		{
			auto Chance = static_cast<int>(((rand() << 7) | ((GetCurrentTime() >> 2) & 0x7F)) % lpMonInfo->FallItemPerMax);
			auto Rating = 0;

			for (int j = 0; j < lpMonInfo->FallItemCount; j++)
			{
				if (Chance >= Rating && Chance < (Rating + lpMonInfo->FallItems[j].Percentage))
				{
					if (lpMonInfo->FallItems[j].dwItemCode && lpMonInfo->FallItems[j].dwItemCode != (sinGG1 | sin01))
					{
						DWORD dwCode = lpMonInfo->FallItems[j].dwItemCode;

						for (int c = 0; c < DefaultItemCount; c++)
						{
							if (DefaultItems[c].Item.CODE == dwCode && !DefaultItems[c].Item.UniqueItem)
							{
								if (DefaultItems[c].sGenDay[0] > 0)
								{
									if (DefaultItems[c].sGenDay[0] <= DefaultItems[c].sGenDay[1])
									{
										break;
									}
									else
									{
										DefaultItems[c].sGenDay[1]++;
									}
								}

								sITEMINFO ItemInfo = { 0 };
								CreateDefItem(&ItemInfo, &DefaultItems[c]);
								ZeroMemory(&ItemInfo.ItemHeader, sizeof(ItemInfo.ItemHeader));

								if (rsServerConfig.Event_Potion)
								{
									if ((ItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
									{
										ItemInfo.PotionCount = (rand() % rsServerConfig.Event_Potion) + 1;
									}
								}

								Drops.ItemQueue.push(ItemInfo);
							}
						}
					}

					break;
				}

				Rating += lpMonInfo->FallItems[j].Percentage;
			}
		}

		LOGEx("KitaDevs", "RollDice() -> PushMonsterKilled( %d )( %d )", 1, Drops.ItemQueue.size());

		if (Drops.ItemQueue.empty())
			return;

		if (DamageList[Monster->dwObjectSerial].empty())
			return;

		LOGEx("KitaDevs", "RollDice() -> PushMonsterKilled( %d )", 3);

		auto Players = std::vector<std::pair<rsPLAYINFO*, DWORD>>{ DamageList[Monster->dwObjectSerial].begin(), DamageList[Monster->dwObjectSerial].end() };
		for (auto it = Players.begin(); it != Players.end();)
		{
			bool ErasePlayer = true;

			if (it->first && it->first->lpsmSock && it->first->smCharInfo.Life[0] > 0)
			{
				const int x = (it->first->Position.x - Monster->pX) >> FLOATNS;
				const int z = (it->first->Position.z - Monster->pZ) >> FLOATNS;
				const int dist = x * x + z * z;

				if (dist <= MaximumDropDistance)
				{
					ErasePlayer = false;
				};
			}

			if (ErasePlayer)
			{
				it = Players.erase(it);
				continue;
			}

			++it;
		}

		LOGEx("KitaDevs", "RollDice() -> PushMonsterKilled( %d )", 4);

		if (Players.empty())
			return;

		std::sort(Players.begin(), Players.end(), [](const std::pair<rsPLAYINFO*, DWORD>& a, const std::pair<rsPLAYINFO*, DWORD>& b)
		{
			return a.second < b.second;
		});

		for (auto it = Players.begin(); it != Players.end();)
		{
			bool ErasePlayer = false;

			if (it->first && it->first->lpsmSock)
			{
				for (size_t i = 0; i < Players.size(); i++)
				{
					if (Players[i].first && Players[i].first->lpsmSock && Players[i].first != it->first)
					{
						if (it->first->lpsmSock->acc_sin.sin_addr.S_un.S_addr == Players[i].first->lpsmSock->acc_sin.sin_addr.S_un.S_addr)
						{
							ErasePlayer = true;
							break;
						}
					}
				}
			}

			if (ErasePlayer)
			{
				it = Players.erase(it);
				continue;
			}

			++it;
		}

		std::sort(Players.begin(), Players.end(), [](const std::pair<rsPLAYINFO*, DWORD>& a, const std::pair<rsPLAYINFO*, DWORD>& b)
		{
			return a.second > b.second;
		});

		// Max players allowed is defined only here.
		unsigned int MaxAllowedPlayers = 20;

		if (Players.size() > MaxAllowedPlayers)
			Players.resize(MaxAllowedPlayers);

		std::vector<RollDicePlayerInfo> RollDicePlayers(Players.size());

		for (size_t i = 0; i < Players.size(); i++)
		{
			RollDicePlayers[i].Number = -1;
			RollDicePlayers[i].ChooseOrder = -1;
			RollDicePlayers[i].Player = Players[Players.size() - (i + 1)].first;
		}

		Drops.BeginDice = true;
		Drops.Players = RollDicePlayers;

		// Add drop to queue.
		m_DropMap[m_CurrentKey++] = Drops;

		LOGEx("KitaDevs", "RollDice() -> PushMonsterKilled( %d )( %d )", 5, Players.size());
	}

	void RollDice::Update()
	{
		for (auto it = m_DropMap.begin(); it != m_DropMap.end();)
		{
			if (it->second.ExpirationTime == 0)
			{
				// First phase.
				IO::PacketWriter Packet(smTRANSCODE_ROLLDICE_START);

				Packet << it->first;
				Packet << it->second.BeginDice;
				Packet << MaxRollDiceTime;

				// Get item from queue.
				const auto& Item = it->second.ItemQueue.front();

				// Encapsulate it.
				Packet << std::make_pair(&Item, sizeof(Item));

				// Finalize.
				Packet.Finalize();

				for (auto& p : it->second.Players)
				{
					p.Player->lpsmSock->Send(Packet, Packet.GetSize());
				}

				// Begins countdown.
				it->second.BeginDice = false;
				it->second.CurrentOrder = 0;
				it->second.ExpirationTime = GetCurrentTime() + MaxRollDiceTime;
				it->second.SkipTime = 0;

				LOGEx("KitaDevs", "RollDice() -> Update( %d )", 0);
			}
			else if (GetCurrentTime() > it->second.ExpirationTime || (it->second.SkipTime && GetCurrentTime() > it->second.SkipTime))
			{
				// Second phase.
				int LastNumber = -1;
				rsPLAYINFO* Winner = nullptr;

				for (auto& p : it->second.Players)
				{
					if (p.Number > LastNumber && p.Number > 0 && p.Player->lpsmSock)
					{
						LastNumber = p.Number;
						Winner = p.Player;
					}

					p.Number = -1;
				}

				if (Winner)
				{
					RewardPlayer(Winner, it->second.ItemQueue.front(), LastNumber);
					LOGEx(Winner, "RollDice", "UID( %d ) - ID( %s ) - Name( %s ) - Won the item ( %s ) with the number( %d  - Map( %d )).",
						it->first, Winner->szID, Winner->szName, it->second.ItemQueue.front().ItemName, LastNumber, Winner->Position.Area);
				}

				LOGEx("KitaDevs", "RollDice() -> Update( %d )", 1);

				it->second.ItemQueue.pop();
				it->second.CurrentOrder = 0;
				it->second.ExpirationTime = 0;
				it->second.SkipTime = 0;

				{
					IO::PacketWriter Msg(smTRANSCODE_ROLLDICE_END);
					Msg << it->second.ItemQueue.size();

					if (Winner)
					{
						Msg << true;
						Msg << Winner->szName;
					}
					else
					{
						Msg << false;
					}

					Msg.Finalize();

					for (auto& p : it->second.Players)
					{
						if (p.Player && p.Player->lpsmSock)
						{
							p.Player->lpsmSock->Send(Msg, Msg.GetSize());
						}
					}
				}

				if (it->second.ItemQueue.empty())
				{
					it = m_DropMap.erase(it);
					continue;
				}
			}

			++it;
		}
	}

	void RollDice::HandlePacket(IO::PacketReader& Packet, rsPLAYINFO* Player, unsigned int PacketCode)
	{
		if (!Player || !Player->lpsmSock)
			return;

		switch (PacketCode)
		{
		case smTRANSCODE_ROLLDICE_UPDATE:
		{
			int Key = 0;
			Packet >> Key;
			bool Roll = false;
			Packet >> Roll;

			if (m_DropMap.find(Key) != m_DropMap.end())
			{
				if (m_DropMap[Key].ExpirationTime > GetCurrentTime())
				{
					IO::PacketWriter Msg(smTRANSCODE_ROLLDICE_UPDATE);
					bool UpdateGame = false;
					bool SkipTiming = true;

					for (auto& p : m_DropMap[Key].Players)
					{
						if (p.Player == Player)
						{
							if (p.Number == -1)
							{
								// Game will sort based on Number and then the ordering.
								p.ChooseOrder = m_DropMap[Key].CurrentOrder++;

								if (Roll)
								{
									// Choose random number.
									p.Number = GetRandomPos(1, 1000);
								}
								else
								{
									p.Number = 0;
								}

								// Flag to update game.
								UpdateGame = true;
							}
						}
						else if (p.Number == -1)
						{
							SkipTiming = false;
						}

						Msg << p.Number;
						Msg << p.ChooseOrder;
						Msg << p.Player->szName;
					}

					if (UpdateGame)
					{
						Msg.Finalize();

						for (auto& p : m_DropMap[Key].Players)
						{
							p.Player->lpsmSock->Send(Msg, Msg.GetSize());
						}
					}

					if (SkipTiming && m_DropMap[Key].SkipTime == 0)
					{
						m_DropMap[Key].SkipTime = GetCurrentTime() + DelayForSkippingTime;
					}
				}
			}
		} break;
		}
	}

	void RollDice::RewardPlayer(rsPLAYINFO* Player, const sITEMINFO& Item, int Number)
	{
		if (Player)
		{
			bool Success = false;

			for (int i = 0; i < MAX_ITEM; i++)
			{
				if (sItem[i].CODE == Item.CODE)
				{
					AwardItem::GetInstance()->SaveItem(Player, const_cast<char*>(Item.ItemName), sItem[i].LastCategory);
					Success = true;
					break;
				}
			}

			if (Success)
			{
				char Msg[256] = { 0 };
				sprintf_s(Msg, "Roleta do Chefe> %s conquistou o item %s.", Player->szName, Item.ItemName);
				rsSendServerChatMessageToAllUser(3, Msg);
			}
		}
	}

	void RollDice::OnPlayerQuitGame(rsPLAYINFO* Player)
	{
		for (auto& Map : m_DropMap)
		{
			for (auto it = Map.second.Players.begin(); it != Map.second.Players.end();)
			{
				if (it->Player == Player)
				{
					it = Map.second.Players.erase(it);
				}
				else
				{
					it++;
				}
			}
		}
	}
}
#else
#include "UI/UIRect2D.h"

constexpr unsigned int RollDiceTimeout = 10 * 1000;
constexpr const char* RollDiceOpenMessage = "Roleta do Chefe> Parabéns, você está participando do sorteio !";
constexpr const char* RollDiceWonItem = "Roleta do Chefe> Parabéns %s, você ganhou o item sorteado.";
constexpr const char* RollDiceItemWinner = "Roleta do Chefe> %s foi o vencedor da vez.";

namespace Game
{
	RollDice& RollDice::GetInstance()
	{
		static RollDice Instance;
		return Instance;
	}

	RollDice::RollDice()
	{
		m_Open = false;
		m_WaitDice = false;

		m_ServerKey = 0;

		m_ExpirationTime = 0;
		m_CloseTime = 0;

		ZeroMemory(&m_ShowItem, sizeof(m_ShowItem));

		m_BackgroundTexture = nullptr;
		m_CloseTexture = nullptr;
		m_RollTexture = nullptr;
		m_PassTexture = nullptr;
		m_RankingTexture = nullptr;
	}

	void RollDice::Initialize()
	{
		m_BackgroundTexture = LoadDibSurfaceOffscreen("Game\\images\\RollDice\\ItemBg.png");
		m_CloseTexture = LoadDibSurfaceOffscreen("Game\\images\\RollDice\\RankClose_.png");
		m_RollTexture = LoadDibSurfaceOffscreen("Game\\images\\RollDice\\Roll_.png");
		m_PassTexture = LoadDibSurfaceOffscreen("Game\\images\\RollDice\\Pass_.png");
		m_RankingTexture = LoadDibSurfaceOffscreen("Game\\images\\RollDice\\RankBg.png");
	}

	void RollDice::Open()
	{
		m_Open = true;
	}

	void RollDice::Close()
	{
		m_Open = false;
	}

	bool RollDice::IsOpen() const
	{
		return m_Open;
	}

	bool RollDice::IsHover() const
	{
		if (!m_Open)
			return false;

		auto X = (WinSizeX - 262) / 2;
		auto Y = (WinSizeY - 540) / 2;

		if (pRealCursorPos.x > X && pRealCursorPos.x <= X + 262 &&
			pRealCursorPos.y > Y && pRealCursorPos.y <= Y + 240)
			return true;

		X = (WinSizeX - 500) / 2;
		Y = (WinSizeY - 60) / 2;

		if (pRealCursorPos.x > X && pRealCursorPos.x <= X + 500 &&
			pRealCursorPos.y > Y && pRealCursorPos.y <= Y + 312)
			return true;

		return false;
	}

	void RollDice::Update()
	{
		if (!m_Open)
			return;

		auto BackgroundX = (WinSizeX - 262) / 2;
		auto BackgroundY = (WinSizeY - 540) / 2;

		if (pRealCursorPos.x > BackgroundX + 99 && pRealCursorPos.x <= BackgroundX + 99 + 64 &&
			pRealCursorPos.y > BackgroundY + 72 && pRealCursorPos.y <= BackgroundY + 72 + 86)
		{
			m_ShowItem.x = BackgroundX + 99;
			m_ShowItem.y = BackgroundY + 72;

			sinShowItemInfoFlag = 1;
			cItem.ShowItemInfo(&m_ShowItem, 2);
		}

		if (m_ExpirationTime && m_ExpirationTime < dwPlayTime)
		{
			if (!m_WaitDice)
				Pass();

			// Reset timer.
			m_ExpirationTime = 0;
		}

		if (m_CloseTime && m_CloseTime < dwPlayTime)
		{
			// Self close window.
			Close();

			// Reset timer.
			m_CloseTime = 0;

			// Reset wait dice.
			m_WaitDice = false;
		}
	}

	void RollDice::Render()
	{
		if (!m_Open)
			return;

		auto r = RECT{ 0 };

		auto BackgroundX = (WinSizeX - 262) / 2;
		auto BackgroundY = (WinSizeY - 540) / 2;
		DrawSprite(BackgroundX, BackgroundY, m_BackgroundTexture, 0, 0, 262, 240);

		auto RankBgX = (WinSizeX - 500) / 2;
		auto RankBgY = (WinSizeY - 60) / 2;
		DrawSprite(RankBgX, RankBgY, m_RankingTexture, 0, 0, 500, 312);

		if (m_ShowItem.Flag)
		{
			auto BackgroundX = (WinSizeX - 262) / 2;
			auto BackgroundY = (WinSizeY - 540) / 2;

			auto Rect = RECT{ BackgroundX + 99, BackgroundY + 72, BackgroundX + 99 + 64, BackgroundY + 72 + 86 };

			if (pRealCursorPos.x > Rect.left && pRealCursorPos.x <= Rect.right &&
				pRealCursorPos.y > Rect.top && pRealCursorPos.y <= Rect.bottom)
			{
				dsDrawColorBox(sinInvenColor[4], Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top);
			}

			auto Rect2D = UI::AdjustTextureToOrigin(UI::Rect2D(Rect), m_ShowItem.lpItem, true);
			DrawSprite(Rect2D.GetX(), Rect2D.GetY(), m_ShowItem.lpItem, 0, 0, m_ShowItem.w, m_ShowItem.h, -1, Rect2D.GetWidth(), Rect2D.GetHeight());

			r.left = BackgroundX + 20; r.top = BackgroundY + 162;
			r.right = r.left + 222; r.bottom = r.top + 20;
			DrawFontTextNewFormat(r, m_ShowItem.sItemInfo.ItemName, RGB(255, 255, 255), 0, DT_CENTER);
		}

		if ((m_ShowItem.CODE & sinITEM_MASK2) == sinFO1)
			cInvenTory.DrawForceOrbEffect(m_ShowItem.x, m_ShowItem.y);

		for (size_t i = 0; i < m_Users.size(); i++)
		{
			auto FixX = RankBgX + (238 * ((i / 10) % 2));
			auto FixY = RankBgY + ((20 * ((i % 10))) + (200 * (i / 20)));

			r.left = 13 + FixX; r.top = 104 + FixY;
			r.right = r.left + 20; r.bottom = r.top + 19;
			DrawFontTextNewFormat(r, std::to_string(i + 1).c_str(), RGB(255, 255, 255), 0, DT_CENTER | DT_BOTTOM);

			r.left = 34 + FixX; r.top = 104 + FixY;
			r.right = r.left + 137; r.bottom = r.top + 19;
			DrawFontTextNewFormat(r, std::get<2>(m_Users[i]).c_str(), RGB(255, 255, 255), 0, DT_CENTER | DT_BOTTOM);

			r.left = 172 + FixX; r.top = 104 + FixY;
			r.right = r.left + 78; r.bottom = r.top + 19;
			DrawFontTextNewFormat(r, std::to_string(std::get<0>(m_Users[i])).c_str(), RGB(255, 255, 255), 0, DT_CENTER | DT_BOTTOM);
		}

		{
			auto TimeLeft = (m_ExpirationTime >= dwPlayTime ? ((m_ExpirationTime + 500) - dwPlayTime) / 1000 : 0);
			r.left = BackgroundX + 40; r.top = BackgroundY + 180;
			r.right = r.left + 181; r.bottom = r.top + 19;
			DrawFontTextNewFormat(r, (std::to_string(TimeLeft) + "s").c_str(), sinInvenColor[4], 0, DT_CENTER);
		}

		// Roll
		if (pRealCursorPos.x > BackgroundX + 36 && pRealCursorPos.x <= BackgroundX + 36 + 88 &&
			pRealCursorPos.y > BackgroundY + 199 && pRealCursorPos.y <= BackgroundY + 199 + 25)
		{
			DrawSprite(BackgroundX + 36, BackgroundY + 199, m_RollTexture, 0, 0, 88, 25);
		}

		// Pass
		if (pRealCursorPos.x > BackgroundX + 136 && pRealCursorPos.x <= BackgroundX + 136 + 88 &&
			pRealCursorPos.y > BackgroundY + 199 && pRealCursorPos.y <= BackgroundY + 199 + 25)
		{
			DrawSprite(BackgroundX + 136, BackgroundY + 199, m_PassTexture, 0, 0, 88, 25);
		}

		// Close
		if (pRealCursorPos.x > BackgroundX + 244 && pRealCursorPos.x <= BackgroundX + 244 + 16 &&
			pRealCursorPos.y > BackgroundY + 5 && pRealCursorPos.y <= BackgroundY + 5 + 15)
		{
			DrawSprite(BackgroundX + 238, BackgroundY + 8, m_CloseTexture, 0, 0, 16, 15);
		}
	}

	void RollDice::HandlePacket(IO::PacketReader& Packet, unsigned int PacketCode)
	{
		LOGEx("KitaDevs", "RollDice() - PacketCode( 0x%d ).", PacketCode);

		switch (PacketCode)
		{
		case smTRANSCODE_ROLLDICE_START:
		{
			bool ShowMessage = false;

			Packet >> m_ServerKey;
			Packet >> ShowMessage;
			Packet >> m_CloseTime;

			m_ExpirationTime = dwPlayTime + RollDiceTimeout;
			m_CloseTime += dwPlayTime;

			sITEMINFO ItemData = { 0 };
			Packet >> std::make_pair(&ItemData, sizeof(ItemData));

			// Try loading item image.
			LoadItemImage(&ItemData, &m_ShowItem);

			// Reset wait dice.
			m_WaitDice = false;

			// Prepare for new users.
			m_Users.clear();

			// Self open this window.
			Open();

			// Show message if required.
			if (ShowMessage)
				cMessageBox.ShowMessageEvent(const_cast<char*>(RollDiceOpenMessage));
		} break;

		case smTRANSCODE_ROLLDICE_UPDATE:
		{
			// Declare users.
			std::vector<Ranking> Users;

			// Read any ammount of players available.
			while (!Packet.EndOfFile())
			{
				int NumberRolled = 0;
				int ChooseOrder = 0;
				std::string UserName;

				Packet >> NumberRolled;
				Packet >> ChooseOrder;
				Packet >> UserName;

				// Insert into temporary vector.
				Users.emplace_back(std::make_tuple(NumberRolled, ChooseOrder, UserName));
			}

			// Sort order.
			std::sort(Users.begin(), Users.end(), [](const Ranking& a, const Ranking& b)
			{
				// Number is greater (order first).
				if (std::get<0>(a) > std::get<0>(b))
				return true;

			// Number is lesser (order later).
			if (std::get<0>(a) < std::get<0>(b))
				return false;

			// Number is equal, order by the choosing time.
			return std::get<1>(a) < std::get<1>(b);
			});

			m_Users = Users;
		} break;

		case smTRANSCODE_ROLLDICE_END:
		{
			// Get number of items left.
			size_t ItemsLeft = 0;
			Packet >> ItemsLeft;

			// Check if we have a winner.
			bool Winner = false;
			Packet >> Winner;

			if (Winner)
			{
				// Get winner name.
				std::string Name;
				Packet >> Name;

				// Check if it is me.
				if (_strcmpi(lpCurPlayer->smCharInfo.szName, Name.c_str()) == 0)
				{
					char Msg[256] = { 0 };
					sprintf_s(Msg, RollDiceWonItem, Name.c_str());
					cMessageBox.ShowMessageEvent(Msg);
				}
				else
				{
					char Msg[256] = { 0 };
					sprintf_s(Msg, RollDiceItemWinner, Name.c_str());
					cMessageBox.ShowMessageEvent(Msg);
				}
			}

			if (ItemsLeft == 0)
				m_CloseTime = dwPlayTime + 1500;
		} break;
		}
	}

	bool RollDice::LButtonDown()
	{
		auto BackgroundX = (WinSizeX - 262) / 2;
		auto BackgroundY = (WinSizeY - 540) / 2;

		// Roll
		if (pRealCursorPos.x > BackgroundX + 36 && pRealCursorPos.x <= BackgroundX + 36 + 88 &&
			pRealCursorPos.y > BackgroundY + 199 && pRealCursorPos.y <= BackgroundY + 199 + 25)
		{
			if (!m_WaitDice)
				Roll();

			return true;
		}

		// Pass
		if (pRealCursorPos.x > BackgroundX + 136 && pRealCursorPos.x <= BackgroundX + 136 + 88 &&
			pRealCursorPos.y > BackgroundY + 199 && pRealCursorPos.y <= BackgroundY + 199 + 25)
		{
			if (!m_WaitDice)
				Pass();

			return true;
		}

		// Close
		if (pRealCursorPos.x > BackgroundX + 244 && pRealCursorPos.x <= BackgroundX + 244 + 16 &&
			pRealCursorPos.y > BackgroundY + 5 && pRealCursorPos.y <= BackgroundY + 5 + 15)
		{
			m_CloseTime = dwPlayTime;

			if (!m_WaitDice)
				Pass();

			return true;
		}

		return false;
	}

	void RollDice::Roll()
	{
		IO::PacketWriter Packet(smTRANSCODE_ROLLDICE_UPDATE);
		Packet << m_ServerKey;
		Packet << true;
		Packet.Finalize();

		// Send.
		smWsockServer->Send(Packet, Packet.GetSize());

		// Now waiting for server to roll the dice.
		m_WaitDice = true;
	}

	void RollDice::Pass()
	{
		IO::PacketWriter Packet(smTRANSCODE_ROLLDICE_UPDATE);
		Packet << m_ServerKey;
		Packet << false;
		Packet.Finalize();

		// Send.
		smWsockServer->Send(Packet, Packet.GetSize());

		// Now waiting for server to roll the dice.
		m_WaitDice = true;
	}
}
#endif
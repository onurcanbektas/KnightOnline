// GameProcMain.h: interface for the CGameProcMain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEPROCMAIN_H__E1C4F2CC_5AF3_4417_8917_A52CD5523DB3__INCLUDED_)
#define AFX_GAMEPROCMAIN_H__E1C4F2CC_5AF3_4417_8917_A52CD5523DB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameProcedure.h"
#include <set>

typedef std::set<int>::iterator it_ID;
typedef std::pair<it_ID, bool> pair_ID;

class CGameProcMain : public CGameProcedure  
{
	friend class CGameProcedure;
protected:
	std::set<int> m_SetNPCID;
	std::set<int> m_SetUPCID;

public:
#ifdef _N3_64GRID_
	CServerMesh		*m_pSMesh;									// �������� �ʿ��� �޽� Ŭ����..
#endif
	class CUIInventory*			m_pUIInventory;			// �κ��丮
	class CUIVarious*			m_pUIVar;				// ĳ���� ����â, ���� ���� ���� �������� �� �ٿ뵵 UI
	class CUIChat*				m_pUIChatDlg;			// ä�� ����� ��ȭ����..
	class CUIMessageWnd*		m_pUIMsgDlg;			// ���� �޽��� ��� ����.
	
	// Folded UI
	class CUIChat2*			m_pUIChatDlg2;
	class CUIMessageWnd2*	m_pUIMsgDlg2;

	class CUIStateBar*			m_pUIStateBarAndMiniMap;	// mp,hp,exp, minimap....
	class CUICmd*				m_pUICmd;				// ���� �ϴ��� ��ɹ�ư â..
	class CUITargetBar*			m_pUITargetBar;			// Ÿ�� ����â..
	class CUICmdList*			m_pUICmdListDlg;	    
	class CUICmdEdit*			m_pUICmdEditDlg;
	class CUITransactionDlg*	m_pUITransactionDlg;
	class CUIDroppedItemDlg*	m_pUIDroppedItemDlg;
	class CSubProcPerTrade*		m_pSubProcPerTrade;
	class CUIHelp*				m_pUIHelp;
	class CUIPartyOrForce*		m_pUIPartyOrForce;
	class CUISkillTreeDlg*		m_pUISkillTreeDlg;
	class CUIHotKeyDlg*			m_pUIHotKeyDlg;
	class CUINotice*			m_pUINotice;
	class CUIClassChange*		m_pUIClassChange;
	class CUINPCEvent*			m_pUINpcEvent;
	class CUIItemExchange*		m_pUIItemREDlg;
	class CUIRepairTooltipDlg*	m_pUIRepairTooltip;
	class CUIWareHouseDlg*		m_pUIWareHouseDlg;
	class CUIInn*				m_pUIInn;
	class CUICreateClanName*	m_pUICreateClanName;
	


	class CUIKnightsOperation*	m_pUIKnightsOp;					// ���� ����Ʈ ����, ����, ��...
	class CUIPartyBBS*			m_pUIPartyBBS;					// ��Ƽ ���� �Խ���.
	class CUITradeSellBBS*		m_pUITradeBBS;					// ��ŷ� �Խ���
	class CUIQuestMenu*			m_pUIQuestMenu;					// Quest Menu
	class CUIQuestTalk*			m_pUIQuestTalk;					// Quest Talk
	class CUIDead*				m_pUIDead;						// Dead UI
	class CUITradeBBSSelector*	m_pUITradeBBSSelector;			// ��ŷ� �Խ��� ���� ����
	class CUITradeBBSEditDlg*	m_pUITradeBBSEdit;				// ��ŷ� �Խù� ����

	class CN3Shape*				m_pTargetSymbol;				// �÷��̾ Ÿ������ ���� ĳ������ ��ġ���� �׸��� �ȴ�..

	class CN3SndObjStream*		m_pSnd_Town, *m_pSnd_Battle;	//��������, �������� ������..
	class CMagicSkillMng*		m_pMagicSkillMng;

	class CUINpcTalk*			m_pUINpcTalk;	
	class CUINPCChangeEvent*	m_pUINpcChange;
	class CUIWarp*				m_pUIWarp;
	class CWarMessage*			m_pWarMessage;					// ������� �޽���
	class CLightMgr*			m_pLightMgr;

	   
	//..
	BOOL		m_bLoadComplete;							// �ε��� �Ϸ�Ǿ���??
	
	float		m_fMsgSendTimeMove;							// �ֱ� �̵� �޽��� ���� �ð�..
	float		m_fMsgSendTimeRot;							// �ֱ� ȸ�� �޽��� ���� �ð�..
	float		m_fPlayerYawSended; // �ֱٿ� �޽����� ���� ������ �÷��̾� y �� ȸ����.
	float		m_fRequestGameSave;	// �ֱٿ� ���� ������ ������ ��û�� �ð�
	__Vector3	m_vPlayerPosSended; // �ֱٿ� �޽����� ���� ������ �÷��̾� ��ġ.

	__Vector3	m_vMouseLBClickedPos;
	__Vector3	m_vMouseSkillPos;

	float		m_fLBClickTime;

	int			m_iJoinReqClan;
	int			m_iJoinReqClanRequierID;

	int			KM_COUNT;

protected:
	virtual bool ProcessPacket(Packet& pkt);

	bool	MsgRecv_CharacterSelect(Packet& pkt); // virtual
	int		MsgRecv_VersionCheck(Packet& pkt); // virtual

	bool	MsgRecv_MyInfo_All(Packet& pkt);
	void	MsgRecv_MyInfo_HP(Packet& pkt);
	void	MsgRecv_MyInfo_MSP(Packet& pkt);
	void	MsgRecv_MyInfo_EXP(Packet& pkt);
	bool	MsgRecv_MyInfo_LevelChange(Packet& pkt);
	void	MsgRecv_MyInfo_RealmPoint(Packet& pkt);
	void	MsgRecv_MyInfo_PointChange(Packet& pkt);

	bool	MsgRecv_Chat(Packet& pkt);
	bool	MsgRecv_UserMove(Packet& pkt);
	bool	MsgRecv_Rotation(Packet& pkt);
//	bool	MsgRecv_Dead(Packet& pkt);
	bool	MsgRecv_Regen(Packet& pkt);
	void	MsgRecv_Corpse(Packet& pkt);
	bool	MsgRecv_Time(Packet& pkt);
	bool	MsgRecv_Weather(Packet& pkt);
	
	bool	MsgRecv_UserInAndRequest(Packet& pkt);		// ���� ������ ��� User ���̵� ī��Ʈ��ŭ �޴´�... �۱�.. ������Ʈ�� �ʿ��� �͸� �������� ��û..
	bool	MsgRecv_UserInRequested(Packet& pkt);					// �������� ��û�� ������ ���̵���� �޾Ƽ� User ó��..
	bool	MsgRecv_UserInOut(Packet& pkt);
	bool	MsgRecv_UserIn(Packet& pkt, bool bWithFX=false);
	bool	MsgRecv_UserOut(Packet& pkt);
	void	MsgRecv_UserState(Packet& pkt);

	bool	MsgRecv_NPCInAndRequest(Packet& pkt);		// ���� ������ ��� NPC ���̵� ī��Ʈ��ŭ �޴´�... �۱�.. ������Ʈ�� �ʿ��� �͸� �������� ��û..
	bool	MsgRecv_NPCInRequested(Packet& pkt);				// �������� ��û�� NPC ���̵���� �޾Ƽ� User ó��..
	bool	MsgRecv_NPCInOut(Packet& pkt);
	bool	MsgRecv_NPCIn(Packet& pkt);
	bool	MsgRecv_NPCOut(Packet& pkt);
	bool	MsgRecv_NPCMove(Packet& pkt);

	bool	MsgRecv_Attack(Packet& pkt);
	bool	MsgRecv_Dead(Packet& pkt);

	bool	MsgRecv_ItemMove(Packet& pkt);					// Item Move�� ���� ����..
	bool	MsgRecv_ItemBundleDrop(Packet& pkt);			// Item �� �ʵ忡 ��Ÿ���µ��� ���� ����
	bool	MsgRecv_ItemBundleOpen(Packet& pkt);			// ������ ���ڸ� ���ų� ��ü�� ������..
	bool	MsgRecv_ItemTradeStart(Packet& pkt);			// ������ ��ŷ�..
	bool	MsgRecv_ItemTradeResult(Packet& pkt);			// ������ ��ŷ� ���..
	bool	MsgRecv_ItemDroppedGetResult(Packet& pkt);	// ���� ������ ������ �Ա� ���..
	bool	MsgRecv_ItemWeightChange(Packet& pkt);		// ������ ���� ��ȭ..

	bool	MsgRecv_UserLookChange(Packet& pkt);			// �Ѹ���� �ٲ��.. ������ �����

	void	MsgRecv_TargetHP(Packet& pkt);

	void	MsgRecv_ZoneChange(Packet& pkt);			// �� �ܼ��� �� ü����.

	void	MsgRecv_Notice(Packet& pkt);
	void	MsgRecv_PartyOrForce(Packet& pkt);
	void	MsgRecv_PerTrade(Packet& pkt);

	void	MsgRecv_SkillChange(Packet& pkt);			// ��ų ��ȭ..
	void	MsgRecv_MagicProcess(Packet& pkt);			// ��ų ��ȭ..
	void	MsgRecv_ClassChange(Packet& pkt);			// ���� ��ȭ..
	void	MsgRecv_ClassPromotion(Packet& pkt);

	void	MsgRecv_ObjectEvent(Packet& pkt);			// ������Ʈ �̺�Ʈ ��û�� ���� ����

	void	MsgRecv_DurabilityChange(Packet& pkt);		// ������ ����..
	void	MsgRecv_NpcEvent(Packet& pkt);				// Npc Event(Exchange, Repair both).. 

	void	MsgRecv_Knights(Packet& pkt);				// ���� ���� ���� ��Ŷ..
	void	MsgRecv_KnightsListBasic(Packet& pkt);		// ���� �⺻ ������..
	
	void	MsgRecv_CompressedPacket(Packet& pkt);		// ����� ��Ŷ�̴�... ���� Ǯ�� ������ ���鼭 �ѹ��� �Ľ��ؾ� �Ѵ�!!!
	void	MsgRecv_ContinousPacket(Packet& pkt);		// �پ ���� ��Ŷ�̴�.. ������ ���鼭 �ѹ��� �Ľ��ؾ� �Ѵ�!!!

	void	MsgRecv_ItemRepair(Packet& pkt);			// Item Repair Result.. 
	void	MsgRecv_ItemCountChange(Packet& pkt);		// Item Count Change..
	void	MsgRecv_ItemDestroy(Packet& pkt);			// Item Count Change..

	void	MsgRecv_WareHouse(Packet& pkt);			// ������ ���� ��Ŷ..
	void	MsgRecv_WareHouseOpen(Packet& pkt);		// ������ ����..

	void	MsgRecv_NpcChangeOpen(Packet& pkt);		// Class Change�� �ʱ�ȭ..
	void	MsgRecv_AllPointInit(Packet& pkt);			// All Point �ʱ�ȭ..
	void	MsgRecv_SkillPointInit(Packet& pkt);		// Skill Point �ʱ�ȭ..
	void	MsgRecv_PointChangePriceQueryRequest(Packet& pkt);		// ���ݿ� ���� ���� ��Ŷ..

	void	MsgRecv_NoahChange(Packet& pkt);			// ��� ����..
	void	MsgRecv_WarpList(Packet& pkt);				// ���� ����Ʈ..
//	void	MsgRecv_ServerCheckAndRequestConcurrentUserCount(Packet& pkt);			// ���� IP �� ��Ʈ�� �޾� �����ڸ� üũ�� ����..
//	void	MsgRecv_ConcurrentUserCountAndSendServerCheck(Packet& pkt);
	
	//knights...
	void	MsgRecv_Knights_Create(Packet& pkt);
	void	MsgRecv_Knights_Withdraw(Packet& pkt);
	void	MsgRecv_Knights_Join(Packet& pkt);
	void	MsgRecv_Knights_Leave(Packet& pkt);
	void	MsgRecv_Knights_AppointViceChief(Packet& pkt);
	void	MsgRecv_Knights_MemberInfoAll(Packet& pkt);
	void	MsgRecv_Knights_GradeChangeAll(Packet& pkt);
	void	MsgRecv_Knights_Duty_Change(Packet& pkt);
	void	MsgRecv_Knigts_Join_Req(Packet& pkt);

public:
	void	ProcessUIKeyInput(bool bEnable = true);
	bool	OnMouseMove(POINT ptCur, POINT ptPrev);
	bool	OnMouseLbtnDown(POINT ptCur, POINT ptPrev);
	bool	OnMouseLBtnPressd(POINT ptCur, POINT ptPrev);
	bool	OnMouseLBtnPress(POINT ptCur, POINT ptPrev);
	bool	OnMouseLDBtnPress(POINT ptCur, POINT ptPrev);
	bool	OnMouseRbtnDown(POINT ptCur, POINT ptPrev);
	bool	OnMouseRBtnPressd(POINT ptCur, POINT ptPrev);
	bool	OnMouseRBtnPress(POINT ptCur, POINT ptPrev);
	bool	OnMouseRDBtnPress(POINT ptCur, POINT ptPrev);
	
	// added by d5dl2
	bool	OnMouseMBtnPress(POINT ptCur, POINT ptPrev);
	
	void	ControlViewVDegree(int16_t sValue);
	void	PlayBGM_Town();
	void	PlayBGM_Battle();

	void	DoCommercialTransaction(int iTradeID);								// ��ŷ�..

	const __InfoPartyOrForce*	PartyOrForceConditionGet(bool& bIAmLeader, bool& bIAmMember, int& iMemberIndex, class CPlayerBase*& pTarget);
	void						TargetSelect(int iID, bool bMustAlive);
	void						TargetSelect(class CPlayerNPC* pTarget);

	void	CommandToggleUIChat();
	void	CommandToggleUIMsgWnd();

	bool	CommandToggleUIInventory();
	bool	CommandToggleUIState();
	bool	CommandToggleAttackContinous();
	bool	CommandToggleMoveContinous();
	bool	CommandToggleWalkRun();
	bool	CommandToggleUISkillTree();
	bool	CommandToggleUIMiniMap();
	bool	CommandToggleCmdList();
	bool	OpenCmdEdit(std::string msg);

	void	CommandMove(e_MoveDirection eMD, bool bStartOrEnd); // �����̴� ����(������, ����), �����̱� �����ϴ°�?
	void	CommandEnableAttackContinous(bool bEnable, CPlayerBase* pTarget);
	void	CommandCameraChange(); // ī�޶� ���� �ٲٱ�..
	void	CommandSitDown(bool bLimitInterval, bool bSitDown, bool bImmediately = false);

	void	CommandTargetSelect_NearstEnemy(); // ���� ����� �� Ÿ�� ���..
	void	CommandTargetSelect_NearstOurForce(); // ���� ����� ��Ƽ Ÿ�����..

	void	CloseUIs(); // ���� ��ŷ�, �������... UI �ݱ�..

	void	NoahTrade(uint8_t bType, uint32_t dwGoldOffset, uint32_t dwGold);

	void	MsgOutput(const std::string& szMsg, D3DCOLOR crMsg);

	void	InitZone(int iZone, const __Vector3& vPosPlayer);
	void	InitUI();
	void	InitPlayerPosition(const __Vector3& vPos); // �÷��̾� ��ġ �ʱ�ȭ.. ������ �����, �⺻������ ���ϰ� �Ѵ�.

	void	MsgSend_Continous();												// Ư�� ����(?)�Ͽ��� �������� ���������� �޽����� ����..
	void	MsgSend_Attack(int iTargetID, float fInterval, float fDistance);	// ���� ��Ŷ ������ - ���̺��� ���� �ֱ⸦ ���� �༭ ��ŷ�� ���´�.
	void	MsgSend_Move(bool bMove, bool bContinous);							// �������� ������ ��Ŷ�� ������.. // �����̴°� ? �ֱ������� �����̴� �ǰ�?
	void	MsgSend_Rotation();													// �������� ȸ�� ��Ŷ�� ������..
	void	MsgSend_Chat(enum e_ChatMode eMode, const std::string& szChat);		// �������� ä�� �޽����� ������..
	void	MsgSend_ChatSelectTarget(const std::string& szTargetID); // �ϴ��� ä�� ��� ���ϱ�.
	void	MsgSend_Regen();
	bool	MsgSend_RequestItemBundleOpen(CPlayerNPC* pCorpse); // ������ ���ڸ� ���ų� ��ü�� ������..
	void	MsgSend_RequestTargetHP(int16_t siIDTarget, uint8_t byUpdateImmediately); // 0x00 - ���� �þ�Բ�.. 0x01 - ��� ������Ʈ..
	void	MsgSend_GameStart();
	bool	MsgSend_NPCEvent(int16_t siIDTarget);
	void	MsgSend_NPCInRequest(int iID); // NPC ������ ���� ��� ��û�Ѵ�..
	void	MsgSend_UserInRequest(int iID); // User ������ ���� ��� ��û�Ѵ�..
	void	MsgSend_Warp(); // ����?? - ��ü������ �ɼ��� �ִ�..
	void	MsgSend_StateChange(enum e_SubPacket_State eSP, int iState);
	void	MsgSend_PerTradeReq(int iDestID, bool bNear = true);
	void	MsgSend_SpeedCheck(bool bInit = false);

	void	MsgSend_PartyOrForcePermit(int iPartyOrForce, bool bYesNo); // iPartyOrForce 1 : Party, 2:Force
	void	MsgSend_PartyOrForceLeave(int iPartyOrForce); // iPartyOrForce 1 : Party, 2:Force
	bool	MsgSend_PartyOrForceCreate(int iPartyOrForce, const std::string& szID); // iPartyOrForce 1 : Party, 2:Force

	void	MsgSend_ObjectEvent(int iEventID, int iNPCID);		// ������Ʈ�� �����Ǿ� �ִ� �̺�Ʈ ��û..
	void	MsgSend_Weather(int iWeather, int iPercent);
	void	MsgSend_Time(int iHour, int iMin);
	void	MsgSend_Administrator(enum e_SubPacket_Administrator eSP, const std::string& szID);
	
	void	MsgSend_KnightsJoin(int iTargetID);
	void	MsgSend_KnightsLeave(std::string& szName);
	void	MsgSend_KnightsWithdraw();
	void	MsgSend_KnightsAppointViceChief(std::string& szName);
	void	MsgSend_KnightsJoinReq(bool bJoin);	
	void	MsgSend_PerTradeBBSReq(std::string szName, int iDestID);
	void	MsgSend_CharacterSelect(); // virtual


	void	ProcessPlayerInclination();				// ��� ó��..(������ �־ ��簡 ���ϸ� �̲�����..).
	void	ProcessLocalInput(uint32_t dwMouseFlags);	// Ű���� �������� ó���Ѵ�..
	void	ParseChattingCommand(const std::string& szCmd);
	

	void	UpdateUI_PartyOrForceButtons(); // Ŀ�ǵ� �ٿ� �ִ� ��Ƽ ��ư�� ��Ȳ�� ���� ������Ʈ ���ش�.
	void	UpdateUI_MiniMap();
	void	UpdateUI_TargetBar();
	void	UpdateBGM();
	void	UpdateCameraAndLight();

	void	RenderTarget();
	
	void	Init();									// UI �� UI ���ҽ����� �д´�.
	void	Release();								// Release..	
	void	ReleaseUIs();
	void	ReleaseSound();
	
	void	Tick();								// ����� ���..
	void	Render();							// ������..

	CGameProcMain();									// ������.
	virtual ~CGameProcMain();							// �Ҹ���.
};

#endif // !defined(AFX_GAMEPROCMAIN_H__E1C4F2CC_5AF3_4417_8917_A52CD5523DB3__INCLUDED_)

// GameProcedure.cpp: implementation of the CGameProcedure class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "resource.h"

#include "GameDef.h"
#include "GameEng.h"
#include "packetdef.h"
#include "LocalInput.h"
#include "APISocket.h"
#include "UIMessageBox.h"
#include "UIMessageBoxManager.h"
#include "UIManager.h"

#include "N3FXMgr.h"
#include "PlayerMyself.h"
#include "GameProcedure.h"
#include "GameProcLogIn.h"
//#include "GameProcStart.h"
#include "GameProcNationSelect.h"
#include "GameProcCharacterCreate.h"
#include "GameProcCharacterSelect.h"
#include "GameProcMain.h"
#include "GameProcOption.h"

#include "UILoading.h"
#include "UINotice.h"
#include "UIHelp.h"
#include "UIHotKeyDlg.h"
#include "UIChat.h"
#include "UIVarious.h"
#include "UIPartyOrForce.h"
#include "UIMessageWnd.h"
#include "UIEndingDisplay.h"

#include "N3UIEdit.h"
#include "N3SndObjStream.h"
#include "N3FXBundle.h"

#include "BitmapFile.h"
#include "Jpeg.h"
#include "JpegFile.h"

#include "MagicSkillMng.h"
#include "GameCursor.h"

#include "shared/Compression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CN3SndObjStream*	CGameProcedure::s_pSnd_BGM = NULL;			// ���� ������� ������..
CLocalInput*		CGameProcedure::s_pLocalInput = NULL;		// ���콺�� Ű���� �Է� ��ü .. Direct Input �� ���.
CAPISocket*			CGameProcedure::s_pSocket = NULL;			// ���� ���� ��ü
CAPISocket*			CGameProcedure::s_pSocketSub = NULL;		// ���� ���� ��ü
CGameEng*			CGameProcedure::s_pEng = NULL;				// 3D Wrapper Engine
CN3FXMgr*			CGameProcedure::s_pFX = NULL;

CUIManager*			CGameProcedure::s_pUIMgr = NULL;			// UI Manager
CUILoading*			CGameProcedure::s_pUILoading = NULL;		// �ε���..
CUIMessageBoxManager*	CGameProcedure::s_pMsgBoxMgr = NULL;		// MessageBox Manager
//bool				CGameProcedure::s_bUseSpeedHack = false;

CGameProcedure*				CGameProcedure::s_pProcPrev = NULL;
CGameProcedure*				CGameProcedure::s_pProcActive = NULL;

CGameProcLogIn*				CGameProcedure::s_pProcLogIn = NULL;
CGameProcNationSelect*		CGameProcedure::s_pProcNationSelect = NULL;
CGameProcCharacterCreate*	CGameProcedure::s_pProcCharacterCreate = NULL;
CGameProcCharacterSelect*	CGameProcedure::s_pProcCharacterSelect = NULL;
CGameProcMain*				CGameProcedure::s_pProcMain = NULL;
CGameProcOption*			CGameProcedure::s_pProcOption = NULL;
CGameCursor*				CGameProcedure::s_pGameCursor = NULL;

SDL_Cursor*	CGameProcedure::s_hCursorNormal    = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorNormal1   = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorClick     = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorClick1    = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorAttack    = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorPreRepair = NULL;
SDL_Cursor*	CGameProcedure::s_hCursorNowRepair = NULL;

e_LogInClassification CGameProcedure::s_eLogInClassification; // ������ ����.. MGame, Daum, KnightOnLine ....
std::string	CGameProcedure::s_szAccount = ""; // ���� ���ڿ�..
std::string	CGameProcedure::s_szPassWord = ""; // ���� ���..
std::string	CGameProcedure::s_szServer = ""; // ���� ���ڿ�..
bool CGameProcedure::m_bCursorLocked = false;
SDL_Cursor*	CGameProcedure::m_hPrevGameCursor = NULL;
HWND CGameProcedure::s_hWndSubSocket = NULL; // ���� ���Ͽ� ������ �ڵ�..
int	CGameProcedure::s_iChrSelectIndex = 0;
bool CGameProcedure::s_bNeedReportConnectionClosed = false; // ���������� �������� �����ؾ� �ϴ���..
bool CGameProcedure::s_bWindowed = false; // â��� ����??
bool CGameProcedure::s_bKeyPress = false;	//Ű�� ���������� ui���� �ش��ϴ� ���۵����� �ִٸ�
bool CGameProcedure::s_bKeyPressed = false;	//Ű�� �ö����� ui���� �ش��ϴ� ���۵����� �ִٸ�

// NOTE: adding boolean to check if window has focus or not
bool CGameProcedure::s_bIsWindowInFocus = true;

// NOTE: added a bool for whether window has mouse focus or not
bool CGameProcedure::s_bWindowHasMouseFocus = true;

CGameProcedure::CGameProcedure()
{
	m_bCursorLocked = false;
}

CGameProcedure::~CGameProcedure()
{
	m_bCursorLocked = false;
}

void CGameProcedure::Release()
{
	s_pUIMgr->SetFocusedUI(NULL);
}

void CGameProcedure::Init()
{
	s_pUIMgr->SetFocusedUI(NULL);
}

void CGameProcedure::StaticMemberInit(SDL_Window* pWindow)
{
	//////////////////////////////////////////////////////////////////////////////////////////
	// ���� �⺻ 3D ���� �����..
#if _DEBUG 
	s_bWindowed = true;
#endif // #if _DEBUG 

/*
#ifndef _DEBUG
	// �븸 ������ ��� IME ������ ���� ��¥ Ǯ��带 ����..
	int iLangID = ::GetUserDefaultLangID();
	if(0x0404 == iLangID) 
	{
		s_bWindowed = true;
		
		DEVMODE dm;
		dm.dmSize = sizeof(DEVMODE);
		dm.dmPelsWidth = CN3Base::s_Options.iViewWidth;
		dm.dmPelsHeight = CN3Base::s_Options.iViewHeight;
		dm.dmBitsPerPel = CN3Base::s_Options.iViewColorDepth;
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		::ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
	}
#endif // #ifndef _DEBUG
*/


	s_pEng = new CGameEng();
	if(false == s_pEng->Init(s_bWindowed, pWindow, CN3Base::s_Options.iViewWidth, CN3Base::s_Options.iViewHeight, CN3Base::s_Options.iViewColorDepth, TRUE)) exit(-1);
	// ���� �⺻ 3D ���� �����..
	
	
	RECT rc;
	::GetClientRect(s_hWndBase, &rc);
	RECT rcTmp = rc; rcTmp.left = (rc.right - rc.left) / 2; rcTmp.bottom = rcTmp.top + 30;
	CN3UIEdit::CreateEditWindow(s_hWndBase, rcTmp);
	//////////////////////////////////////////////////////////////////////////////////////////

	//s_hWndSubSocket = hWndSub; // ���� ���Ͽ� ������ �ڵ�..

	CGameBase::StaticMemberInit(); // Table �� ����, ������Ʈ, ĳ���� �ʱ�ȭ...

	//////////////////////////////////////////////////////////////////////////////////////////
	// Game Procedure ���ϰ� ���� ��ǲ, 3D����, Resource Table �ε� �� �ʱ�ȭ...
	s_pSocket = new CAPISocket();
	s_pSocketSub = new CAPISocket();


	SDL_Surface* pSurf0 = IMG_Load("cursor_normal.cur");
	SDL_Surface* pSurf1 = IMG_Load("cursor_normal1.cur");
	SDL_Surface* pSurf2 = IMG_Load("cursor_click.cur");
	SDL_Surface* pSurf3 = IMG_Load("cursor_click1.cur");
	SDL_Surface* pSurf4 = IMG_Load("cursor_attack.cur");
	SDL_Surface* pSurf5 = IMG_Load("repair0.cur");
	SDL_Surface* pSurf6 = IMG_Load("repair1.cur");
	SDL_Surface* pSurf7 = IMG_Load("WarFare.ico");

	if(pSurf0==NULL||pSurf1==NULL||pSurf2==NULL||pSurf3==NULL||pSurf4==NULL||pSurf5==NULL||pSurf6==NULL||pSurf7==NULL) {
		printf("ERROR: Unable to load image. %s\n", IMG_GetError());
		system("pause");
		//Sleep(1000 * 5);
		exit(-1);
	}

	s_hCursorNormal    = SDL_CreateColorCursor(pSurf0, 0, 0);
	s_hCursorNormal1   = SDL_CreateColorCursor(pSurf1, 0, 0);
	s_hCursorClick     = SDL_CreateColorCursor(pSurf2, 0, 0);
	s_hCursorClick1    = SDL_CreateColorCursor(pSurf3, 0, 0);
	s_hCursorAttack    = SDL_CreateColorCursor(pSurf4, 0, 0);
	s_hCursorPreRepair = SDL_CreateColorCursor(pSurf5, 0, 0);
	s_hCursorNowRepair = SDL_CreateColorCursor(pSurf6, 0, 0);

	SDL_SetCursor(s_hCursorNormal);
	SDL_SetWindowIcon(pWindow, pSurf7);

	SDL_FreeSurface(pSurf0);
	SDL_FreeSurface(pSurf1);
	SDL_FreeSurface(pSurf2);
	SDL_FreeSurface(pSurf3);
	SDL_FreeSurface(pSurf4);
	SDL_FreeSurface(pSurf5);
	SDL_FreeSurface(pSurf6);
	SDL_FreeSurface(pSurf7);


	/*
	if(!CN3Base::s_Options.bWindowCursor)
	{
		s_pGameCursor = new CGameCursor();
		s_pGameCursor->LoadFromFile("ui\\cursor.uif");
	}
	SetGameCursor(s_hCursorNormal);
	*/

	s_pLocalInput = new CLocalInput();
	s_pLocalInput->Init(pWindow, FALSE); // Input �� �ʱ�ȭ.

	//////////////////////////////////////////////////////////////////////////////////////////
	// Sound �ʱ�ȭ..
	if(CN3Base::s_Options.bSndEnable)
	{
		CN3Base::s_SndMgr.Init(s_hWndBase);//pWindow);
		CN3Base::s_SndMgr.SetDuplicated(CN3Base::s_Options.bSndDuplicated);
	}
	CN3FXBundle::SetEffectSndDistance(float(CN3Base::s_Options.iEffectSndDist));

	s_pFX = new CN3FXMgr();

	__TABLE_UI_RESRC* pTblUI = s_pTbl_UI.Find(NATION_ELMORAD); // �⺻�� ������ UI �� �Ѵ�..
	if(pTblUI == NULL) {
		printf("ERROR: UI table is NULL.\n");
		system("pause");
		//Sleep(1000 * 5);
		exit(-1);
	}

	s_pUIMgr = new CUIManager(); // �⺻ UIManager
	s_pMsgBoxMgr = new CUIMessageBoxManager(); //MessageBox Manager

	// ����..
	CN3UIBase::EnableTooltip(pTblUI->szToolTip);

	//////////////////////////////////////////////////////////////////////////////////////////
	// �� ���ν����� ����
	s_pProcLogIn			= new CGameProcLogIn();				// �α��� ���ν���
	s_pProcNationSelect		= new CGameProcNationSelect();		// ���� ����
	s_pProcCharacterSelect	= new CGameProcCharacterSelect();	// ĳ���� ����
	s_pProcCharacterCreate	= new CGameProcCharacterCreate();	// ĳ���� �����
	s_pProcMain				= new CGameProcMain();				// ���� ���� ���ν���
	s_pProcOption			= new CGameProcOption();			// ���� �ɼ� ���ν���
}

void CGameProcedure::StaticMemberRelease()
{
#ifndef _DEBUG
	// �븸 ������ ��� IME ������ ���� ��¥ Ǯ��带 ����..
	int iLangID = ::GetUserDefaultLangID();
	if(0x0404 == iLangID) 
	{
		DEVMODE dm;
		::EnumDisplaySettings(NULL, ENUM_REGISTRY_SETTINGS, &dm);

		// ������Ʈ���� ���÷��� ���� ���� ������ ���÷��� ��尡 �ٸ��� ���� �����ش�.
		if(	dm.dmPelsWidth != CN3Base::s_Options.iViewWidth || 
			dm.dmPelsHeight != CN3Base::s_Options.iViewHeight || 
			dm.dmBitsPerPel != CN3Base::s_Options.iViewColorDepth)
		{
			dm.dmSize = sizeof(DEVMODE);
			dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			::ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		}
	}
#endif // #ifndef _DEBUG


	delete s_pSocket; s_pSocket = NULL; // ��� ����..
	delete s_pSocketSub; s_pSocketSub = NULL; // ���� ���� ���ֱ�..
	delete s_pFX; s_pFX = NULL;

	////////////////////////////////////////////////////////////
	// �⺻�� ����..
	if(s_pPlayer)
	{
		int iRun = s_pPlayer->IsRunning(); // �̵� ��尡 �ٴ� ���¿����� 
		CGameProcedure::RegPutSetting("UserRun", &iRun, 4); // �ȱ�, �ٱ� ���� ���..
	}
	
	if(s_pEng)
	{
		e_ViewPoint eVP = s_pEng->ViewPoint();
		CGameProcedure::RegPutSetting("CameraMode", &eVP, 4); // ī�޶� ���� ���
	}
	// �⺻�� ����..
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	// ����ȭ�� ���̱�..
	if(s_pPlayer)
	{
		e_Nation eNation = s_pPlayer->m_InfoBase.eNation;
		__TABLE_UI_RESRC* pTbl = s_pTbl_UI.Find(eNation);
		if(pTbl)
		{
			CUIEndingDisplay Credit; // ���� ǥ���ϱ�..
			Credit.LoadFromFile(pTbl->szEndingDisplay);
			Credit.Render();
		}
	}
	// ����ȭ�� ���̱�..
	////////////////////////////////////////////////////////////////////////

//	if ( (s_pProcMain) && (s_pProcMain->m_pUIHotKeyDlg) )
//			s_pProcMain->m_pUIHotKeyDlg->CloseIconRegistry();

	// UI ��ġ�� ���̱� ���� ���� ����..
	if(s_pProcMain)
	{
		UIPostData_Write(UI_POST_WND_CHAT, s_pProcMain->m_pUIChatDlg);
		UIPostData_Write(UI_POST_WND_HOTKEY, s_pProcMain->m_pUIHotKeyDlg);
		UIPostData_Write(UI_POST_WND_HELP, s_pProcMain->m_pUIHelp);
		UIPostData_Write(UI_POST_WND_PARTY, s_pProcMain->m_pUIPartyOrForce);
		UIPostData_Write(UI_POST_WND_INFO, s_pProcMain->m_pUIMsgDlg);
	}

	// �� ���ν�����
	delete s_pProcLogIn; s_pProcLogIn = NULL; 						// �α��� ���ν���
	delete s_pProcNationSelect; s_pProcNationSelect = NULL; 		// ���� ����
	delete s_pProcCharacterSelect; s_pProcCharacterSelect = NULL; 	// ĳ���� ����
	delete s_pProcCharacterCreate; s_pProcCharacterCreate = NULL; 	// ĳ���� �����
	delete s_pProcMain; s_pProcMain = NULL; 						// ���� ���� ���ν���
	delete s_pProcOption; s_pProcOption = NULL; 					// ���� �ɼ� ���ν���

	// UI �� ������..
	if(s_pUILoading) delete s_pUILoading; s_pUILoading = NULL;		// Loading Bar
	delete s_pMsgBoxMgr;
	delete s_pUIMgr; s_pUIMgr = NULL;				// UI Manager

//	delete s_pIME; s_pIME = NULL;
	delete s_pLocalInput; s_pLocalInput = NULL;
	delete s_pEng; s_pEng = NULL; // �� �������� ���� ������.!!!!!

	if(s_pGameCursor) delete s_pGameCursor; s_pGameCursor = NULL;

	CGameBase::StaticMemberRelease();
}

void CGameProcedure::Tick()
{
	s_pLocalInput->Tick(); // Ű����� ���콺�κ��� �Է��� �޴´�.
	if(s_pGameCursor) s_pGameCursor->Tick();

	ProcessUIKeyInput();

	uint32_t dwMouseFlags = s_pLocalInput->MouseGetFlag();
	POINT ptPrev = s_pLocalInput->MouseGetPosOld();
	POINT ptCur = s_pLocalInput->MouseGetPos();

	e_Nation eNation = s_pPlayer->m_InfoBase.eNation;
	if(dwMouseFlags & MOUSE_LBCLICK) SDL_SetCursor(((NATION_ELMORAD == eNation) ? s_hCursorClick1 : s_hCursorClick));
	else if(dwMouseFlags & MOUSE_LBCLICKED) SDL_SetCursor(((NATION_ELMORAD == eNation) ? s_hCursorNormal1 : s_hCursorNormal));
	if(dwMouseFlags & MOUSE_RBCLICKED)
	{
		if(s_pPlayer->m_bAttackContinous && s_pProcActive == s_pProcMain) // ���� ���ν��� �̸�..
			SDL_SetCursor(s_hCursorAttack);
		else
			SDL_SetCursor(((NATION_ELMORAD == eNation) ? s_hCursorNormal1 : s_hCursorNormal));
	}

	uint32_t dwRet = 0;
	dwRet = s_pMsgBoxMgr->MouseProcAndTick(dwMouseFlags, s_pLocalInput->MouseGetPos(), s_pLocalInput->MouseGetPosOld());

	if(0 == dwRet)
	{
		dwRet = s_pUIMgr->MouseProc(dwMouseFlags, ptCur, ptPrev);
		s_pUIMgr->Tick();
	}

	// �� �ϸ�... 
//	if((dwRet & UI_MOUSEPROC_CHILDDONESOMETHING) || (dwRet & UI_MOUSEPROC_DONESOMETHING))
//		s_pLocalInput->MouseRemoveFlag(0xffMOUSE_LBCLICK | MOUSE_LBCLICKED | MOUSE_LBDBLCLK);
	s_pUIMgr->m_bDoneSomething = false;		// UI ���� ������ �ߴ�...
	if(dwRet != UI_MOUSEPROC_NONE)
		s_pUIMgr->m_bDoneSomething = true;		// UI ���� ������ �ߴ�...

	CN3Base::s_SndMgr.Tick(); // Sound Engine...

	// ��ũ�� ĸ�� Ű..
	if(s_pLocalInput->IsKeyPress(SDL_SCANCODE_KP_MINUS)) // Ű�е��� ���̳ʽ� Ű�� ������..
	{
		SYSTEMTIME st;
		::GetLocalTime(&st);
		char szFN[128] = "";
//		sprintf(szFN, "%d_%d_%d_%d.%d.%d.jpg", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		sprintf(szFN, "%d_%d_%d_%d.%d.%d.ksc", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		this->CaptureScreenAndSaveToFile(szFN);
	}

	//////////////////////////////////
	// Network Msg ó���ϱ�
	while (!s_pSocket->m_qRecvPkt.empty())
	{
		auto pkt = s_pSocket->m_qRecvPkt.front();
		if (!ProcessPacket(*pkt))
			CLogWriter::Write("Invalid Packet... (%d)", pkt->GetOpcode());

		delete pkt;
		s_pSocket->m_qRecvPkt.pop();
	}

	while (!s_pSocketSub->m_qRecvPkt.empty())
	{
		auto pkt = s_pSocketSub->m_qRecvPkt.front();
		if (!ProcessPacket(*pkt))
			break;

		delete pkt;
		s_pSocketSub->m_qRecvPkt.pop();
	}
	// Network Msg ó���ϱ�
	//////////////////////////////////
}

void CGameProcedure::Render()
{
	if(s_pUIMgr) s_pUIMgr->Render(); // UI �� ������..

	s_pMsgBoxMgr->Render();
	if(s_pGameCursor) s_pGameCursor->Render();
}

void CGameProcedure::TickActive()
{
	if(s_pProcActive != s_pProcPrev) // ���ν����� �ٲ��..
	{
		if(s_pProcPrev) s_pProcPrev->Release();
		if(s_pProcActive) s_pProcActive->Init();

		s_pProcPrev = s_pProcActive;
	}

	if(s_pProcActive)	s_pProcActive->Tick();		// ���� ���ν��� Tick ................................
}

void CGameProcedure::RenderActive()
{
//	if(s_pProcActive != s_pProcPrev) // ���ν����� �ٲ��..
//	{
//		if(s_pProcPrev) s_pProcPrev->Release();
//		if(s_pProcActive) s_pProcActive->Init();
//
//		s_pProcPrev = s_pProcActive;
//	}
//	else 
//	{
		if(s_pProcActive == s_pProcPrev) s_pProcActive->Render();
//	}
}

bool CGameProcedure::CaptureScreenAndSaveToFile(const std::string& szFN)
{
	/*
	if(szFN.empty()) return false;
	CJpegFile file;

	RECT wndRect;
	GetWindowRect(CN3Base::s_hWndBase, &wndRect);
	
	HANDLE hDIB = file.CopyScreenToDIB(&wndRect);
	if(hDIB)
	{
		int nQuality = 90;
		char szBuf[256] = "";

		//��ڴ� ������ ��ũ�� ĸ�ĸ� �Ҽ� �ְ�...
		if(s_pPlayer->m_InfoBase.iAuthority == AUTHORITY_MANAGER)
			nQuality = 100;

		if(file.EncryptJPEG(hDIB, nQuality, szFN, szBuf) == TRUE)
		{
			TRACE("Screen Captue %s\n", szFN.c_str());
		}
		GlobalFree(hDIB);
	}
	*/
	return true;
/*
	int iW = CN3Base::s_CameraData.vp.Width;
	int iH = CN3Base::s_CameraData.vp.Height;

	bool bResult = false;
	LPDIRECT3DSURFACE8 lpDDSTmp = NULL;
	LPDIRECT3DSURFACE8 lpDDSBack = NULL;
	CN3Base::s_lpD3DDev->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &lpDDSBack);
	if(lpDDSBack)
	{
		CN3Base::s_lpD3DDev->CreateImageSurface(iW, iH, D3DFMT_X8R8G8B8, &lpDDSTmp);
		if(lpDDSTmp)
		{
			HRESULT rval = D3DXLoadSurfaceFromSurface(lpDDSTmp, NULL, NULL, lpDDSBack, NULL, NULL, D3DX_FILTER_NONE, 0);
//			HRESULT rval = s_lpD3DDev->CopyRects(lpDDSBack, NULL, 0, lpDDSTmp, NULL);
//			char szErr[256];
//			::D3DXGetErrorString(rval, szErr, 256);

			if(D3D_OK == rval)
			{
				D3DLOCKED_RECT LR;
				if(D3D_OK == lpDDSTmp->LockRect(&LR, NULL, 0))
				{
//					std::vector<uint8_t> buff(iW * iH * 3, 0);
					CBitMapFile bmf;
					bmf.Create(iW, iH);

					for(int y = 0; y < iH; y++)
					{
						uint8_t* pPS = ((uint8_t*)LR.pBits) + LR.Pitch * y;
//						uint8_t* pPD = (uint8_t*)(&(buff[y * (iW * 3)]));
						uint8_t* pPD = (uint8_t*)(bmf.Pixels(0, y));

						for(int x = 0; x < iW; x++, pPS += 4, pPD +=3 )
						{
							pPD[0] = pPS[0];
							pPD[1] = pPS[1];
							pPD[2] = pPS[2];
						}
					}
					lpDDSTmp->UnlockRect();

//					CJpeg jpg;
//					jpg.SaveJPG(szFN.c_str(), iW, iH, &(buff[0]));
					bmf.SaveToFile(szFN.c_str());
				}
			}
			
			lpDDSTmp->Release();
			lpDDSTmp = NULL;
		}


		lpDDSBack->Release();
		lpDDSBack = NULL;
	}

	return bResult;
*/
}

void CGameProcedure::ProcActiveSet(CGameProcedure *pProc)
{
	if(NULL == pProc || s_pProcActive == pProc) return;

	if(s_pUIMgr) s_pUIMgr->EnableOperationSet(true); // UI�� �����Ҽ� �ְ� �Ѵ�..
	CGameProcedure::MessageBoxClose(-1); // MessageBox �� �� ������ �����.

	s_pProcPrev = s_pProcActive; // ���� �� ������ ���..
	s_pProcActive = pProc;
}

void CGameProcedure::ReConnect()
{
	s_bNeedReportConnectionClosed = false; // ���������� �������� �����ؾ� �ϴ���..
	CGameProcedure::s_pSocket->ReConnect();
	s_bNeedReportConnectionClosed = true; // ���������� �������� �����ؾ� �ϴ���..
}

std::string CGameProcedure::MessageBoxPost(const std::string& szMsg, const std::string& szTitle, int iStyle, e_Behavior eBehavior)
{
	return s_pMsgBoxMgr->MessageBoxPost(szMsg, szTitle, iStyle, eBehavior);
}

void CGameProcedure::MessageBoxClose(const std::string& szMsg)
{
	s_pMsgBoxMgr->MessageBoxClose(szMsg);
}

void CGameProcedure::MessageBoxClose(int iMsgBoxIndex)
{
	if( iMsgBoxIndex == -1 )
		s_pMsgBoxMgr->MessageBoxCloseAll();
}


bool CGameProcedure::RegPutSetting( const char *ValueName, void *pValueData, long length )
{
	HKEY	hKey;

	if ( RegOpenKey( HKEY_CURRENT_USER, GetStrRegKeySetting().c_str(), &hKey ) != ERROR_SUCCESS ) 
	{
		if ( RegCreateKey( HKEY_CURRENT_USER, GetStrRegKeySetting().c_str(), &hKey ) != ERROR_SUCCESS )
		{
			__ASSERT(0, "Registry Create Failed!!!");
			return false;
		}
		if(RegOpenKey( HKEY_CURRENT_USER, GetStrRegKeySetting().c_str(), &hKey ) != ERROR_SUCCESS ) 
		{
			__ASSERT(0, "Registry Open Failed!!!");
			return false;
		}
	}

	// set the value
	if ( RegSetValueEx( hKey, ValueName, 0, REG_BINARY, (const uint8_t *)pValueData, length ) != ERROR_SUCCESS )
	{
		__ASSERT(0, "Registry Write Failed!!!");
		RegCloseKey( hKey );
		return false;
	}

	if ( RegCloseKey( hKey ) != ERROR_SUCCESS ) 
	{
		__ASSERT(0, "Registry Close Failed!!!");
		return false;
	}

	return true;
}

bool CGameProcedure::RegGetSetting( const char *ValueName, void *pValueData, long length)
{
	HKEY	hKey;
	DWORD	Type;
	DWORD	len;

	len = length;

	if ( RegOpenKey( HKEY_CURRENT_USER, GetStrRegKeySetting().c_str(), &hKey ) != ERROR_SUCCESS ) 
	{
//		__ASSERT(0, "Registry Open Failed!!!");
		return false;
	}

	// get the value
	if ( RegQueryValueEx( hKey, ValueName, NULL, &Type, (uint8_t *)pValueData, &len ) != ERROR_SUCCESS )
	{
//		__ASSERT(0, "Registry Query Failed!!!");
		RegCloseKey( hKey );
		return false;
	}

	if ( RegCloseKey( hKey ) != ERROR_SUCCESS ) 
	{
//		__ASSERT(0, "Registry Close Failed!!!");
		return false;
	}

	return true;
}

void CGameProcedure::UIPostData_Write(const std::string& szKey, CN3UIBase* pUI)
{
	if(szKey.empty() || NULL == pUI) return;

	__WndInfo WI;
	lstrcpyn(WI.szName, szKey.c_str(), 16);
	WI.bVisible = pUI->IsVisible();
	WI.ptPosition = pUI->GetPos();

	RegPutSetting(WI.szName, &WI, sizeof(__WndInfo) );
}

void CGameProcedure::UIPostData_Read(const std::string& szKey, CN3UIBase* pUI, int iDefaultX, int	 iDefaultY)
{
	if(szKey.empty() || NULL == pUI) return;

	// 1. ����Ʈ �����͸� �����..
	// 2. �����͸� �о�´�..
	// 3. ������ ��ȿ������ �Ǵ��Ѵ�..

	__WndInfo WI;
	WI.ptPosition.x = iDefaultX;
	WI.ptPosition.y = iDefaultY;
	if(false == RegGetSetting(szKey.c_str(), &WI, sizeof(__WndInfo))) WI.bVisible = true; // �⺻ �����Ͱ� ������ ������ ���̰� �Ѵ�..

	RECT rc = pUI->GetRegion();

	if (WI.ptPosition.x < 0) WI.ptPosition.x = 0;
	if (WI.ptPosition.x + (rc.right - rc.left) > (int)s_CameraData.vp.Width)
		WI.ptPosition.x = s_CameraData.vp.Width - (rc.right - rc.left);
	if (WI.ptPosition.y < 0) WI.ptPosition.y = 0;
	if (WI.ptPosition.y + (rc.bottom - rc.top) >(int)s_CameraData.vp.Height)
		WI.ptPosition.y = s_CameraData.vp.Height - (rc.bottom - rc.top);

	pUI->SetVisible(WI.bVisible);
	if(0 == WI.ptPosition.x && 0 == WI.ptPosition.y)
		pUI->SetPos(iDefaultX, iDefaultY);
	else pUI->SetPos(WI.ptPosition.x, WI.ptPosition.y);
}

void CGameProcedure::SetGameCursor(SDL_Cursor* hCursor, bool bLocked)
{
	if(s_pGameCursor)
	{
		e_Cursor eCursor = CURSOR_KA_NORMAL;

		if(hCursor == s_hCursorNormal)
			eCursor = CURSOR_KA_NORMAL;
		else if(hCursor == s_hCursorNormal1)
			eCursor = CURSOR_EL_NORMAL;
		else if(hCursor == s_hCursorClick)
			eCursor = CURSOR_KA_CLICK;
		else if(hCursor == s_hCursorClick1)
			eCursor = CURSOR_EL_CLICK;
		else if(hCursor == s_hCursorAttack)
			eCursor = CURSOR_ATTACK;
		else if(hCursor == s_hCursorPreRepair)
			eCursor = CURSOR_PRE_REPAIR;
		else if(hCursor == s_hCursorNowRepair)
			eCursor = CURSOR_NOW_REPAIR;
		else if(hCursor == NULL)
			eCursor = CURSOR_UNKNOWN;

		SetGameCursor(eCursor, bLocked);

		if ((!m_bCursorLocked) && bLocked)
		{
			m_bCursorLocked = true;
		}

	}
	else
	{
		if ((m_bCursorLocked) && (!bLocked) ) return;
		else if ( ((m_bCursorLocked) && bLocked) || ((!m_bCursorLocked) && !bLocked) )
		{
			SDL_SetCursor(hCursor);
			return;
		}
		else if ((!m_bCursorLocked) && bLocked)
		{
			m_hPrevGameCursor = SDL_GetCursor();
			m_bCursorLocked = true;
			SDL_SetCursor(hCursor);
		}
	}
}

void CGameProcedure::SetGameCursor(e_Cursor eCursor, bool bLocked)
{
	if(s_pGameCursor == NULL) return;
	s_pGameCursor->SetGameCursor(eCursor, bLocked);
}

void CGameProcedure::RestoreGameCursor()
{
	if(s_pGameCursor)
	{
		if (m_bCursorLocked) 
			m_bCursorLocked = false;

		if(s_pGameCursor) s_pGameCursor->RestoreGameCursor();
	}
	else
	{
		if (m_bCursorLocked) 
			m_bCursorLocked = false;

		SDL_SetCursor(m_hPrevGameCursor);	
	}
}

std::string CGameProcedure::GetStrRegKeySetting()
{
	char szBuff[256];
	sprintf(szBuff, "Software\\KnightOnline\\%s_%s_%d", s_szAccount.c_str(), s_szServer.c_str(), s_iChrSelectIndex);
	return szBuff;
}

bool CGameProcedure::ProcessPacket(Packet& pkt)
{
	int iCmd = pkt.read<uint8_t>();	// Ŀ��� �Ľ�..
	switch ( iCmd )										// Ŀ��忡 �ٶ� �б�..
	{
		case WIZ_COMPRESS_PACKET:
			this->MsgRecv_CompressedPacket(pkt);
			return true;

		case WIZ_VERSION_CHECK: // ��ȣȭ�� ���� �޴´�..
			this->MsgRecv_VersionCheck(pkt); // virtual
			return true;

		case WIZ_LOGIN:
			this->MsgRecv_GameServerLogIn(pkt);
			return true;

		case WIZ_SERVER_CHANGE:				// ���� �ٲٱ� �޽���..
		{
			// �ٸ� �� ������ �ٽ� �����Ѵ�.
			int iLen = 0;
			std::string szName, szIP;
//			iLen = pkt.read<int16_t>(); // ���� �̸�
//			pkt.readString(szName, iLen);
			iLen = pkt.read<int16_t>(); // ���� IP
			pkt.readString(szIP, iLen);
			uint32_t dwPort = pkt.read<int16_t>();
			s_pPlayer->m_InfoExt.iZoneInit = pkt.read<uint8_t>();
			s_pPlayer->m_InfoExt.iZoneCur = pkt.read<uint8_t>();
			int iVictoryNation = pkt.read<uint8_t>();
			CGameProcedure::LoadingUIChange(iVictoryNation);

			s_bNeedReportConnectionClosed = false; // ���������� �������� �����ؾ� �ϴ���..
			s_pSocket->Disconnect(); // ����...
			Sleep(2000); // 2�� ������.. ������ ó���� �ð��� �ش�.
			int iErr = s_pSocket->Connect(s_hWndBase, szIP.c_str(), dwPort);
			s_bNeedReportConnectionClosed = true; // ���������� �������� �����ؾ� �ϴ���..

			if(iErr) this->ReportServerConnectionFailed("Current Zone", iErr, true); // ���� ���� ����.. Exit.
			else
			{
				// ����üũ�� ������.. �������� ������ ��ȣȭ Ű�� �´�.
				// ���� ���ν����� ��� Character_Select �� ������ �α����ϰ�� GameServer_LogIn �� ������.
				this->MsgSend_VersionCheck(); 
			}
		}
		return true;

		case WIZ_SEL_CHAR:
		{
			this->MsgRecv_CharacterSelect(pkt); // virtual
		}
		return true;
	}

	return false;
}

void CGameProcedure::ReportServerConnectionFailed(const std::string& szServerName, int iErrCode, bool bNeedQuitGame)
{
	char szErr[256];
	std::string szFmt;
	::_LoadStringFromResource(IDS_FMT_CONNECT_ERROR, szFmt);
	sprintf(szErr, szFmt.c_str(), szServerName.c_str(), iErrCode);
	
	e_Behavior eBehavior = ((bNeedQuitGame) ? BEHAVIOR_EXIT : BEHAVIOR_NOTHING);
	CGameProcedure::MessageBoxPost(szErr, "", MB_OK, eBehavior);
	return;
}

void CGameProcedure::ReportServerConnectionClosed(bool bNeedQuitGame)
{
	if(!s_bNeedReportConnectionClosed) return;

	std::string szMsg;
	::_LoadStringFromResource(IDS_CONNECTION_CLOSED, szMsg);
	e_Behavior eBehavior = ((bNeedQuitGame) ? BEHAVIOR_EXIT : BEHAVIOR_NOTHING);
	CGameProcedure::MessageBoxPost(szMsg, "", MB_OK, eBehavior);

	if(s_pPlayer)
	{
		__Vector3 vPos = s_pPlayer->Position();
		CLogWriter::Write("Socket Closed... Zone(%d) Pos(%.1f, %.1f, %.1f) Exp(%d)",
			s_pPlayer->m_InfoExt.iZoneCur, vPos.x, vPos.y, vPos.z, s_pPlayer->m_InfoExt.iExp);
	}
	else
	{
		CLogWriter::Write("Socket Closed...");
	}

	if(s_pSocket) s_pSocket->Release();
}

void CGameProcedure::ReportDebugStringAndSendToServer(const std::string& szDebug)
{
	if(szDebug.empty()) return;

	CLogWriter::Write(szDebug.c_str());

	if(s_pSocket && s_pSocket->IsConnected())
	{
		int iLen = szDebug.size();
		std::vector<uint8_t> buffer;	// ����.. 
		buffer.assign(iLen + 4, 0x00);
		int iOffset=0;												// �ɼ�..
		s_pSocket->MP_AddByte(&(buffer[0]), iOffset, WIZ_DEBUG_STRING_PACKET);
		s_pSocket->MP_AddShort(&(buffer[0]), iOffset, iLen);
		s_pSocket->MP_AddString(&(buffer[0]), iOffset, szDebug);
		s_pSocket->Send(&(buffer[0]), iOffset);				// ����..
	}
}

void CGameProcedure::MsgSend_GameServerLogIn()
{
	uint8_t byBuff[128];										// ��Ŷ ����..
	int iOffset = 0;										// ������ ������..

	CAPISocket::MP_AddByte(byBuff, iOffset, WIZ_LOGIN);	// Ŀ���.
	CAPISocket::MP_AddShort(byBuff, iOffset, (int16_t)s_szAccount.size());	// ���̵� ����..
	CAPISocket::MP_AddString(byBuff, iOffset, s_szAccount);			// ���� ���̵�..
	CAPISocket::MP_AddShort(byBuff, iOffset, (int16_t)s_szPassWord.size());	// �н����� ����
	CAPISocket::MP_AddString(byBuff, iOffset, s_szPassWord);		// ���� �н�����
		
	s_pSocket->Send(byBuff, iOffset);								// ������
}

void CGameProcedure::MsgSend_VersionCheck() // virtual
{
	// Version Check
	int iOffset = 0;
	uint8_t byBuffs[4];
	CAPISocket::MP_AddByte(byBuffs, iOffset, WIZ_VERSION_CHECK);				// Ŀ���.
	s_pSocket->Send(byBuffs, iOffset);	// ������

#ifdef _CRYPTION
	s_pSocket->m_bEnableSend = FALSE; // ������ ����..?
#endif // #ifdef _CRYPTION
}

void CGameProcedure::MsgSend_CharacterSelect() // virtual
{
	uint8_t byBuff[64];
	int iOffset = 0;
	CAPISocket::MP_AddByte(byBuff, iOffset, WIZ_SEL_CHAR);				// Ŀ���.
	CAPISocket::MP_AddShort(byBuff, iOffset, (int16_t)s_szAccount.size());				// ���� ����..
	CAPISocket::MP_AddString(byBuff, iOffset, s_szAccount);						// ���� ���ڿ�..
	CAPISocket::MP_AddShort(byBuff, iOffset, (int16_t)s_pPlayer->IDString().size());		// ĳ�� ���̵� ����..
	CAPISocket::MP_AddString(byBuff, iOffset, s_pPlayer->IDString());			// ĳ�� ���̵� ���ڿ�..
	CAPISocket::MP_AddByte(byBuff, iOffset, s_pPlayer->m_InfoExt.iZoneInit);	// ó�� �������� �ƴ��� 0x01:ó�� ����
	CAPISocket::MP_AddByte(byBuff, iOffset, s_pPlayer->m_InfoExt.iZoneCur);		// ĳ���� ����â������ ĳ���� �� ��ȣ
	s_pSocket->Send(byBuff, iOffset);	// ������

	CLogWriter::Write("MsgSend_CharacterSelect - name(%s) zone(%d)",
		s_pPlayer->IDString().c_str(), s_pPlayer->m_InfoExt.iZoneCur); // ����� �α�..
}

void CGameProcedure::MsgRecv_CompressedPacket(Packet& pkt) // ����� ������ �̴�... �ѹ� �� �Ľ��ؾ� �Ѵ�!!!
{
	uint16_t compressedLength = pkt.read<uint16_t>();
	uint16_t originalLength = pkt.read<uint16_t>();
	uint32_t crc = pkt.read<uint32_t>();

	uint8_t * decompressedBuffer = Compression::DecompressWithCRC32(pkt.contents() + pkt.rpos(), compressedLength, originalLength, crc);
	if (decompressedBuffer == NULL)
		return;

	Packet decompressedPkt;
	decompressedPkt.append(decompressedBuffer, originalLength);
	delete[] decompressedBuffer;

	ProcessPacket(decompressedPkt);
}

int CGameProcedure::MsgRecv_VersionCheck(Packet& pkt) // virtual
{
	int iVersion = pkt.read<int16_t>();	// ����
#ifdef _CRYPTION
	uint64_t iPublicKey = pkt.read<uint64_t>(); // ��ȣȭ ����Ű
	CAPISocket::InitCrypt(iPublicKey);
	s_pSocket->m_bEnableSend = TRUE; // ������ ����..?
#endif // #ifdef _CRYPTION

	if(iVersion != CURRENT_VERSION)
	{
		char szErr[256];

		int iLangID = ::GetUserDefaultLangID();
		if(0x0404 == iLangID)// Taiwan Language
		{
			std::string szFmt;
			::_LoadStringFromResource(IDS_VERSION_CONFIRM_TW, szFmt);
			CGameProcedure::MessageBoxPost(szFmt, "", MB_OK, BEHAVIOR_EXIT);
		}
		else
		{
			std::string szFmt;
			::_LoadStringFromResource(IDS_VERSION_CONFIRM, szFmt);
			sprintf(szErr, szFmt.c_str(), CURRENT_VERSION / 1000.0f, iVersion / 1000.0f);
			CGameProcedure::MessageBoxPost(szErr, "", MB_OK, BEHAVIOR_EXIT);
		}

	}

	return iVersion;
}

int CGameProcedure::MsgRecv_GameServerLogIn(Packet& pkt) // virtual
{
	int iNation = pkt.read<uint8_t>(); // ���� - 0 ���� 0xff - ����..
	return iNation;
}

bool CGameProcedure::MsgRecv_CharacterSelect(Packet& pkt) // virtual
{
	int iResult = pkt.read<uint8_t>(); // 0x00 ����
	if(1 == iResult) // ����..
	{
		int iZoneCur = pkt.read<uint8_t>();
		float fX = (pkt.read<uint16_t>())/10.0f;
		float fZ = (pkt.read<uint16_t>())/10.0f;
		float fY = (pkt.read<int16_t>())/10.0f;

		int iVictoryNation = pkt.read<uint8_t>();
		CGameProcedure::LoadingUIChange(iVictoryNation);

		int iZonePrev;
		if(N3FORMAT_VER_DEFAULT & N3FORMAT_VER_1264) {
			iZonePrev = s_pPlayer->m_InfoExt.iZoneCur = 10*iZoneCur;
		} else {
			iZonePrev = s_pPlayer->m_InfoExt.iZoneCur = iZoneCur;
		}
		s_pPlayer->PositionSet(__Vector3(fX, fY, fZ), true);

		CLogWriter::Write("MsgRecv_CharacterSelect - name(%s) zone(%d -> %d)", s_pPlayer->m_InfoBase.szID.c_str(), iZonePrev, iZoneCur);
		return true;
	}
	else // ����
	{
		CLogWriter::Write("MsgRecv_CharacterSelect - failed(%d)", iResult);
		return false;
	}

	if(iResult) return true;
	else return false;
}

void CGameProcedure::ProcessUIKeyInput(bool bEnable)
{
	s_bKeyPressed	= false;	//Ű�� �ö����� ui���� �ش��ϴ� ���۵����� �ִٸ�

	if(!bEnable)
	{
		if(s_bKeyPress)
		{
			for(int i = 0; i < NUMDIKEYS; i++)
			{
				if(s_pLocalInput->IsKeyPressed(i))
				{
					if(!s_bKeyPressed) s_bKeyPress = false;
					break;
				}
			}
		}
		return;
	}


	CN3UIBase* pMsgBox = s_pMsgBoxMgr->GetFocusMsgBox();
	CN3UIBase* pUIFocus = s_pUIMgr->GetFocusedUI();

	if(pMsgBox && pMsgBox->IsVisible())//this_ui
	{
		for(int i = 0; i < NUMDIKEYS; i++)
		{
			if(s_pLocalInput->IsKeyPress(i))
				s_bKeyPress |= pMsgBox->OnKeyPress(i);
			if(s_pLocalInput->IsKeyPressed(i))
				s_bKeyPressed |= pMsgBox->OnKeyPressed(i);
		}
	}
	else if(pUIFocus && pUIFocus->IsVisible()) // ��Ŀ�� �� UI �� ������...
	{
		for(int i = 0; i < NUMDIKEYS; i++)
		{
			if(s_pLocalInput->IsKeyPress(i))
			{
				if(pUIFocus->m_pChildUI && pUIFocus->m_pChildUI->IsVisible())
					s_bKeyPress |= pUIFocus->m_pChildUI->OnKeyPress(i);
				else
					s_bKeyPress |= pUIFocus->OnKeyPress(i);
			}
			if(s_pLocalInput->IsKeyPressed(i))
			{
				if(pUIFocus->m_pChildUI && pUIFocus->m_pChildUI->IsVisible())
					s_bKeyPressed |= pUIFocus->m_pChildUI->OnKeyPressed(i);
				else
					s_bKeyPressed |= pUIFocus->OnKeyPressed(i);
			}
		}
	}

	if(s_bKeyPress)
	{
		for(int i = 0; i < NUMDIKEYS; i++)
		{
			if(s_pLocalInput->IsKeyPressed(i))
			{
				if(!s_bKeyPressed) s_bKeyPress = false;
				break;
			}
		}
	}
}

bool CGameProcedure::IsUIKeyOperated()
{
	if (!s_bKeyPress && !s_bKeyPressed)
		return false;

	return true;
}

void CGameProcedure::LoadingUIChange(int iVictoryNation)
{
	if(s_pPlayer->m_InfoExt.iVictoryNation == iVictoryNation)
		return;

	s_pPlayer->m_InfoExt.iVictoryNation = iVictoryNation;

	std::string szLoading;
	if(s_pUILoading) delete s_pUILoading; s_pUILoading = NULL;		// Loading Bar

	s_pUILoading = new CUILoading();
	__ASSERT(s_pUILoading, "�ε�ȭ�� ���� ����");
	if(s_pUILoading == NULL) return;

	__TABLE_UI_RESRC* pTblUI = s_pTbl_UI.Find(NATION_ELMORAD); // �⺻�� ������ UI �� �Ѵ�..
	__ASSERT(pTblUI, "�⺻ UI �� �����ϴ�.");
	if(pTblUI == NULL) return;

	switch(iVictoryNation)
	{
	case VICTORY_ABSENCE:
		szLoading = pTblUI->szLoading;
		break;
	case VICTORY_ELMORAD:
		szLoading = pTblUI->szElLoading;
		break;
	case VICTORY_KARUS:
		szLoading = pTblUI->szKaLoading;
		break;
	default:
		szLoading = pTblUI->szLoading;
		break;
	}

	//TRACE("Loading UIF : %s\n", szLoading.c_str());
	s_pUILoading->LoadFromFile(szLoading); // �⺻���� �ε� �� �����..
}

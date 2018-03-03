#ifndef __PACKET_DEF_H_
#define __PACKET_DEF_H_

const int SOCKET_PORT_GAME = 15001;
const int SOCKET_PORT_LOGIN = 15100;

#include "shared/types.h"
#include "shared/packets.h"

#define N3_ACCOUNT_LOGIN			0xf3
#define N3_ACCOUNT_LOGIN_MGAME		0xf4	// !!! LOGIN_REQ !!! �� ����
#define N3_GAMESERVER_GROUP_LIST	0xf5	// Recv - b1(ServerCount) loop(	s1(IP����), str1(IP���ڿ�), s1(�����̸�����), str1(�����̸����ڿ�), s1(���������ο�) )

	enum e_ChatMode {	N3_CHAT_NORMAL = 1,
						N3_CHAT_PRIVATE,
						N3_CHAT_PARTY,
						N3_CHAT_FORCE,
						N3_CHAT_SHOUT,
						N3_CHAT_CLAN,
						N3_CHAT_PUBLIC,
						N3_CHAT_WAR,
						N3_CHAT_TITLE,						//�����ٿ� �� ����
						N3_CHAT_TITLE_DELETE,				//�����ٿ� �ִ� ���� ����
						N3_CHAT_CONTINUE,					//���� ����
						N3_CHAT_CONTINUE_DELETE,			//���� ���� ����
						N3_CHAT_UNKNOWN = 0xffffffff };

	enum e_SubPacket_Trade		{	N3_SP_TRADE_BUY  = 0x01,
									N3_SP_TRADE_SELL = 0x02,
									N3_SP_TRADE_MOVE = 0x03	};

	enum e_SubPacket_State {	N3_SP_STATE_CHANGE_SITDOWN = 0x01,
								N3_SP_STATE_CHANGE_RECRUIT_PARTY = 0x02,
								N3_SP_STATE_CHANGE_SIZE = 0x03,
								N3_SP_STATE_CHANGE_ACTION = 0x04,			// 1 - �λ�, 11 - ����
								N3_SP_STATE_CHANGE_VISIBLE = 0x05 };		// ���� 0 ~ 255

	// Sub Packet
	enum e_SubPacket_Party {	N3_SP_PARTY_OR_FORCE_CREATE			= 0x01,	// Send - s1(ID)	| Recv b1(YesNoErr)
							N3_SP_PARTY_OR_FORCE_PERMIT			= 0x02,	// Send - b1(YesNo) | Recv - s1(ID)
							N3_SP_PARTY_OR_FORCE_INSERT			= 0x03,	// Send - s1(ID) | Recv - s3(ID, HPMax, HP) b2(Level, Class) - ���ڿ��� ID �� �˾Ƴ���.. ID �� -1 �̸�.. ��Ƽ�� �����°��� ������ �����ѰŴ�..
							N3_SP_PARTY_OR_FORCE_REMOVE			= 0x04,	// Send - s1(ID) | Recv - s1(ID) - �ڱ� �ڽ��̸� ��Ƽ�� ���� �Ѵ�..
							N3_SP_PARTY_OR_FORCE_DESTROY			= 0x05,	// Send
							N3_SP_PARTY_OR_FORCE_HP_CHANGE		= 0x06,	// Recv - s3(ID, HPMax, HP)
							N3_SP_PARTY_OR_FORCE_LEVEL_CHANGE	= 0x07,	// Recv - s1(ID), b1(Level)
							N3_SP_PARTY_OR_FORCE_CLASS_CHANGE	= 0x08,	// Recv - s1(ID), b1(Class)�幰���� �����Ҷ�...
							N3_SP_PARTY_OR_FORCE_STATUS_CHANGE	= 0x09 };	// Recv - s1(ID), b1(Status)��, ����, ���Ӽ�����, �ູ

	// Sub Packet
	enum e_SubPacket_PerTrade {	N3_SP_PER_TRADE_REQ =			0x01, 
								N3_SP_PER_TRADE_AGREE =			0x02,
								N3_SP_PER_TRADE_ADD =			0x03,
								N3_SP_PER_TRADE_OTHER_ADD =		0x04,
								N3_SP_PER_TRADE_DECIDE	=		0x05,
								N3_SP_PER_TRADE_OTHER_DECIDE =	0x06,
								N3_SP_PER_TRADE_DONE =			0x07,
								N3_SP_PER_TRADE_CANCEL =		0x08 };	

	// Sub Packet
	enum e_SubPacket_Magic {	N3_SP_MAGIC_CASTING =	0x01,
								N3_SP_MAGIC_FLYING =	0x02,
								N3_SP_MAGIC_EFFECTING =	0x03,
								N3_SP_MAGIC_FAIL = 		0x04,
								N3_SP_MAGIC_TYPE4BUFFTYPE = 0x05,
								N3_SP_MAGIC_CANCEL = 0x06								
	};

	// Sub Packet..
	enum e_SubPacket_ClassChange_Main {
		N3_SP_CLASS_CHANGE_PURE = 0x01,		// Class Change Real..
		N3_SP_CLASS_CHANGE_REQ  = 0x02,		// Class Change Req..
		N3_SP_CLASS_ALL_POINT   = 0x03,		// Class Change All Point..
		N3_SP_CLASS_SKILL_POINT = 0x04,
		N3_SP_CLASS_POINT_CHANGE_PRICE_QUERY = 0x05,
		N3_SP_CLASS_PROMOTION = 0x06	};

	enum e_SubPacket_ClassChange {	N3_SP_CLASS_CHANGE_SUCCESS	= 0x01,		// Success..
									N3_SP_CLASS_CHANGE_NOT_YET	= 0x02,		// Not yet..
									N3_SP_CLASS_CHANGE_ALREADY = 0x03,		// Already..
									N3_SP_CLASS_CHANGE_ITEM_IN_SLOT = 0x04,		// Item in Slot..
									N3_SP_CLASS_CHANGE_FAILURE	= 0x00 };	// Failure..

	enum e_SubPacket_Knights {	N3_SP_KNIGHTS_CREATE =				0x01, // ���� Send - s1(Name Length) str1 | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_JOIN =				0x02, // ���� Send - s1(Knights ID) | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_WITHDRAW =			0x03, // Ż�� Send - | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_MEMBER_REMOVE =		0x04, // ��� ���� - 
								N3_SP_KNIGHTS_DESTROY	=			0x05, // �ǰ��� Send - | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_MEMBER_JOIN_ADMIT =	0x06, // ��� ���� �㰡 Send - s1(Knights ID) | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_MEMBER_JOIN_REJECT =	0x07, // ��� ���� ���� Send - s1(Knights ID) | Recv - b1(1:���� 0:����)
								N3_SP_KNIGHTS_MEMBER_PUNISH =		0x08, // ��� ¡�� - ���԰� ����
								N3_SP_KNIGHTS_APPOINT_CHIEF =		0x09, // ���� �Ӹ� - ���԰� ����
								N3_SP_KNIGHTS_APPOINT_VICECHIEF =	0x0A, // �δ��� �Ӹ� - ���԰� ����
								N3_SP_KNIGHTS_APPOINT_OFFICER =		0x0B, // �屳�Ӹ� - ���԰� ����
								N3_SP_KNIGHTS_GRADE_CHANGE_ALL =	0x0C, // �� ������ ��� �� ���� ���� Recv - s1(count) Loop { s1(Knights ID) b2(Grade Rank) }
								N3_SP_KNIGHTS_MEMBER_INFO_ALL =		0x0D, // ��� ��� ��û Send - s1(page) | s1(Member Count) Loop { s1(Name Length) str1 (Name) }
								N3_SP_KNIGHTS_MEMBER_INFO_ONLINE =	0x0E, // ���� ���� ����Ʈ Send - s1(page) | s1(Member Count) Loop { s1(Name Length) str1 (Name) }
								N3_SP_KNIGHTS_STASH =				0x0F, // ���� â��
								N3_SP_KNIGHTS_DUTY_CHANGE =			0x10, // ����� ���� ����.. �ش� ������� ����.. Recv - s1(Knights ID) b1(����);
								N3_SP_KNIGHTS_JOIN_REQ =			0x11, // ���� �ε���
								N3_SP_KNIGHTS_UNKNOWN };

	enum e_SubPacket_KNights_Create {	N3_SP_KNIGHTS_CREATE_FAIL_DBFAIL =			0x00,
										N3_SP_KNIGHTS_CREATE_SUCCESS =				0x01,
										N3_SP_KNIGHTS_CREATE_FAIL_LOWLEVEL =		0x02,
										N3_SP_KNIGHTS_CREATE_FAIL_DUPLICATEDNAME =	0x03,
										N3_SP_KNIGHTS_CREATE_FAIL_LOWMONEY =		0x04,
										N3_SP_KNIGHTS_CREATE_FAIL_ALREADYJOINED =	0x05,
										N3_SP_KNIGHTS_CREATE_FAIL_UNKNOWN =			0x06,
										N3_SP_KNIGHTS_CREATE_FAIL_INVALIDDAY =		0x07,
										N3_SP_KNIGHTS_CREATE_FAIL_INVALIDSERVER =	0x08 };

	enum e_SubPacket_KNights_Common {	N3_SP_KNIGHTS_COMMON_DBFAIL =				0x00,	//DB�˻� ����..
										N3_SP_KNIGHTS_COMMON_SUCCESS =				0x01,	//����
										N3_SP_KNIGHTS_COMMON_FAIL_NONE_USER =		0x02,	//���� ����..
										N3_SP_KNIGHTS_COMMON_FAIL_DEAD_USER =		0x03,	//��������� �׾� ����..
										N3_SP_KNIGHTS_COMMON_FAIL_ENEMY_USER =		0x04,	//��������� ������ �ٸ�..
										N3_SP_KNIGHTS_COMMON_FAIL_OTHER_CLAN_USER =	0x05,	//��������� �̹� �ٸ� Ŭ���̳� ���ܿ� ���ԵǾ� ����..
										N3_SP_KNIGHTS_COMMON_FAIL_INVALIDRIGHT =	0x06,	//������ ����..
										N3_SP_KNIGHTS_COMMON_FAIL_NONE_CLAN =		0x07,	//�������� �ʴ� ����..									
										N3_SP_KNIGHTS_COMMON_FAIL_FULL =			0x08,	//�ο��� Ǯ..
										N3_SP_KNIGHTS_COMMON_FAIL_ME =				0x09,	//�ڱ��ڽ��� ������ ���..
										N3_SP_KNIGHTS_COMMON_FAIL_NOT_JOINED =		0x0A,	//�����̳� Ŭ���� ���ԵǾ� ���� ����...
										N3_SP_KNIGHTS_COMMON_FAIL_REJECT =			0x0B,	//������� ����...
										N3_SP_KNIGHTS_COMMON_FAIL_BATTLEZONE =		0x0C	// ������������ �ź�..
								};	// join, appoint, leave, withdraw ��� ����.....
	
	enum e_SubPacket_KnightsList {	N3_SP_KNIGHTS_LIST_BASIC_ALL = 0x01,  // Receive - s1(knights Count) { s21(id, �̸�����), str1(�̸�) }
									N3_SP_KNIGHTS_LIST_BASIC_INSERT = 0x02, // Receive - s2(id, �̸�����), str1(�̸�)
									N3_SP_KNIGHTS_LIST_BASIC_REMOVE = 0x03 }; // Receive - s1(id)

	enum e_SubPacket_Administrator { N3_SP_ADMINISTRATOR_ARREST = 0x01, // �� ���� �ִ� ������ ��ü����.. Send b1(Type) s1(�����̸�����), str1(�����̸�)
									N3_SP_ADMINISTRATOR_FORBID_CONNECT = 0x02, // ���ӱ��� �� �ѾƳ���.. Send b1(Type) s1(�����̸�����), str1(�����̸�)
									N3_SP_ADMINISTRATOR_CHAT_FORBID = 0x03, // ä�ñ��� Send b1(Type) s1(�����̸�����), str1(�����̸�)
									N3_SP_ADMINISTRATOR_CHAT_PERMIT = 0x04 }; // ä���㰡 Send b1(Type) s1(�����̸�����), str1(�����̸�)
									
	enum e_SubPacket_WareHouse {	N3_SP_WARE_OPEN = 				0x01,	// Open..
									N3_SP_WARE_GET_IN =				0x02,	// �̱�..
									N3_SP_WARE_GET_OUT =			0X03,	// ����..
									N3_SP_WARE_WARE_MOVE =			0x04,	// �̵�..
									N3_SP_WARE_INV_MOVE =			0x05,	// �̵�..
									N3_SP_WARE_INN =				0x10,	// ��ó��..������������ ����..
									N3_SP_WARE_UNKNOWN };

	enum e_SubPacket_NoahChange {	N3_SP_NOAH_GET = 0x01,	// ��� ����,
									N3_SP_NOAH_LOST	= 0x02,	// ��� �н�..
									N3_SP_NOAH_SPEND = 0x03	// ��� �Һ�..
								};		

	enum e_Party_BBS {	N3_SP_PARTY_REGISTER						= 0x01,		// ��Ƽ �Խ��ǿ� ���
						N3_SP_PARTY_REGISTER_CANCEL					= 0x02,		// ��Ƽ �Խ��ǿ��� ��� ���
						N3_SP_PARTY_BBS_DATA						= 0x03};	// ��Ƽ �Խ� ���� �䱸

	enum e_Trade_BBS_Kind { N3_SP_TRADE_BBS_BUY						= 0x01,		// ��� ���� ���
							N3_SP_TRADE_BBS_SELL					= 0x02};		// �Ĵ� ���� ���

	enum e_Trade_BBS_Sub  { N3_SP_TYPE_REGISTER						= 0x01,		// ���� ����ϱ�
							N3_SP_TYPE_REGISTER_CANCEL				= 0x02,		// ��� �����ϱ�
							N3_SP_TYPE_BBS_DATA						= 0x03,		// �Խ��� ���� �䱸
							N3_SP_TYPE_BBS_OPEN						= 0x04,		// ��ŷ� �Խ��� ����
							N3_SP_TYPE_BBS_TRADE					= 0x05};	// �Խ��ǿ��� �ŷ� ��û�ϱ�

#endif // end of #ifndef __PACKET_DEF_H_

#pragma once
// �⺻ ����
#define		WINCX			800
#define		WINCY			600
#define		PURE			= 0
#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1	// ���
#define		OBJ_EQUIP		2	// ����
#define		OBJ_BUY			3	// ����
#define		OBJ_SELL		4	// �Ǹ�
#define		PI				3.1415926535f
#define		VK_MAX			0xff

// ��ų ����
#define		MANA_DBR		200
#define		MANA_ZACKS		100
#define		MANA_GUNGUARD	100
#define		MANA_WINDMILL	150
#define		MANA_MAHA		250
#define		MANA_HEADSHOT	250
#define		MANA_MOVINGSHOT	400
#define		MANA_SPREE		500

#define		MANA_SATELITE	1000
#define		MANA_AWAKENING	1500

// ��ų ��Ÿ��
#define		COOL_DBR		20
#define		COOL_ZACKS		2
#define		COOL_GUNGUARD	8
#define		COOL_WINDMILL	4
#define		COOL_MAHA		4
#define		COOL_HEADSHOT	4
#define		COOL_MOVINGSHOT	10
#define		COOL_SPREE		12

#define		COOL_SATELITE	30
#define		COOL_AWAKENING	90

// Ÿ�� ����
#define		TILECX		64
#define		TILECY		64

	// == �����ƹ� ==
#define		SERIAROOM_SIZEX 1080
#define		SERIAROOM_SIZEY 720

#define		SERIA_TILEX		21
#define		SERIA_TILEY		12

	// == ����̾� ==
#define		HENDON_SIZEX	3472
#define		HENDON_SIZEY	680

#define		HENDON_TILEX	55
#define		HENDON_TILEY	12

	// == �̽ý��� ����(������) ==
#define		NEST_SIZEX		1792
#define		NEST_SIZEY		840

#define		NEST_TILEX		28
#define		NEST_TILEY		13

#define		LIGHT_STONE		1
#define		DARK_STONE		2

	// == �������̶� ==
#define		ALFHLYRA_SIZEX		1600
#define		ALFHLYRA_SIZEY		600

#define		ALFHLYRA_TILEX		25
#define		ALFHLYRA_TILEY		10

	// == ������1 ==
#define		RESHIPON1_SIZEX		1200
#define		RESHIPON1_SIZEY		600
			
#define		RESHIPON1_TILEX		19
#define		RESHIPON1_TILEY		10

	// == ������2 ==
#define		RESHIPON2_SIZEX		1200
#define		RESHIPON2_SIZEY		600

#define		RESHIPON2_TILEX		19
#define		RESHIPON2_TILEY		10

	// == �����н�(��ī���� ���� ����) ==
#define		STOMPATH_SIZEX		1600
#define		STOMPATH_SIZEY		600

#define		STOMPATH_TILEX		25
#define		STOMPATH_TILEY		10

	// == ��ī���� ����(������) ==
#define		SKASARAIR_SIZEX		1600
#define		SKASARAIR_SIZEY		600

#define		SKASARAIR_TILEX		25
#define		SKASARAIR_TILEY		10

#pragma region �̱��� ��ũ��
#define SINGLE(type) public:\
						static type* Get_Instance()\
						{\
							if (!m_pInstance)\
							{\
								m_pInstance = new type;\
							}\
							return m_pInstance;\
						}\
						\
						static void Destroy_Instance()\
						{\
							if (m_pInstance)\
							{\
								delete m_pInstance;\
								m_pInstance = nullptr;\
							}\
						}\
						private:\
							type();\
							~type();\
						private:\
							static type* m_pInstance;
#pragma endregion �̱��� ��ũ��

enum ATT_TYPE;

// ���� ������ �������� ID
enum RENDERID 
{	
	BACKGROUND,
	BACKGROUNDEFFECT,
	GAMEOBJECT,
	EFFECT,
	UI,
	OVERDUI,		// UI ���� ��µǴ� ������, ü�¹� ���� UI
	TWOOVERDUI,		// OVERDUI ���� ��µǴ� ü����, ���������� ���� UI
	TRIPLEOVERDUI,
	QUADOVERDUI,
	OCTAOVERDUI,
	HEXAOVERDUI,
	MOUSEPOINTER,
	RENDER_END
};

// ��Ʈ�ڽ��� �ǰ� ����
typedef struct tagHitInfo
{
	ATT_TYPE	eAttType;
	bool		bIsHit;
	float		fAttPoint;
	float		fAttRatio;
	float		fThrustPower;
	float		fThrustAccel;
	float		fLevitatePower;
	float		fLevitateAngle;
	float		fKnockbackAngle;
	float		fKnockbackTime;
}HIT_INFO;

// Obj �⺻ ����
typedef struct tagInfo
{
	// ũ��, ��ġ
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	// �������ͽ�
	float		fHp;		// HP
	float		fMaxHp;
	float		fMp;		// Mp
	float		fMaxMp;

	float		fAtk;		// ���� ���ݷ�
	float		fDef;		// ���� ����

	float		fMAtk;		// ���� ���ݷ�
	float		fMDef;		// ���� ����

	float		fStrength;	// ��
	float		fAtkSpeed;	// ���ݼӵ�

	float		fHealth;	// ü��
	float		fMoveSpeed;	// �̵��ӵ�

	float		fFire;		// ȭ
	float		fWater;		// ��
	float		fLightness;	// ��
	float		fDarkness;	// ��

	float		fExorcism;	// �׸���
}INFO;

// ��������Ʈ ������ ���� Frame ����ü
typedef struct tagFrame
{
	int			iFrameStart;	// bmp���Ͽ��� iMotion�࿡���� ���� �ε���
	int			iFrameEnd;		// bmp���Ͽ��� iMotion�࿡���� �� �ε���
	int			iMotion;		// bmp���Ͽ��� ��������Ʈ�� ���� �ε���
	double		dwSpeed;		// ��ȯ �ӵ� ������, ũ�Ⱑ Ŀ������ ��ȯ �ӵ��� ������
	double		dwTime;			// ??

}FRAME;

// ���� ����ü
typedef struct tagColor
{
	int R;
	int G;
	int B;
}RGB;

// ���� Ÿ��
enum DIRECTION	
{ 
	DIR_LEFT,
	DIR_UP, 
	DIR_RIGHT, 
	DIR_DOWN, 
	DIR_LU, 
	DIR_RU, 
	DIR_END 
};

// ������Ʈ Ÿ��
enum OBJ_ID		
{ 
	OBJ_PLAYER,				// �÷��̾�
	OBJ_PLAYER_ATTACK,		// �÷��̾� ����
	OBJ_PLAYER_WIDEATTACK,	// �÷��̾� ��������
	OBJ_EFFECT,				// ����Ʈ
	OBJ_MONSTER,			// ����
	OBJ_MONSTER_ATTACK,		// ���� ����
	OBJ_MONSTER_WIDEATTACK,	// ���� ��������
	OBJ_NPC,				// NPC
	OBJ_DECORATION,			// ���ǰ
	OBJ_DAMAGEFONT,			// ������ ��Ʈ
	OBJ_COMBOFONT,			// �޺� ��Ʈ
	OBJ_CRITICALFONT,		// ũ��Ƽ�� ��Ʈ
	OBJ_AIRIALFONT,			// ����� ��Ʈ
	OBJ_BOSSHP,				// ���� Hp ��Ȳ
	OBJ_BOSSHPBAR,			// ���� Hp ��
	OBJ_BOSSHPNUM,			// ���� Hp �� ��
	OBJ_RUNESTONE1,			// �̽ý��� ��ȯ�� �齺��(��)
	OBJ_RUNESTONE2,			// �̽ý��� ��ȯ�� �齺��(��)
	OBJ_MONHP,				// ���� Hp ��Ȳ
	OBJ_MONHPBAR,			// ���� Hp ��
	OBJ_MONHPNUM,			// ���� Hp �� ��
	OBJ_MONPORTRAIT,		// ���� �ʻ�ȭ
	OBJ_MONSTERTYPE,		// ���� Ÿ��
	OBJ_INVEN,				// �κ��丮 UI
	OBJ_STORE,				// ���� UI
	OBJ_MYINFO,				// ������ UI
	OBJ_SKILLICON,			// ��ų ������
	OBJ_ITEM,				// ������
	OBJ_INVENITEM,			// �κ��丮 ������
	OBJ_EQUIPMENT,			// �������� ������(������â)
	OBJ_STOREITEM,			// ���� ������
	OBJ_MOUSE,				// ���콺
	OBJ_MOUSEPOINT,			// ���콺 ������ ������
	OBJ_MAINUI,				// ����UI
	OBJ_UI,					// UI
	OBJ_END					// END
};

// �� Ÿ��
enum SCENEID	
{
	SC_LOGO,
	SC_MENU,
	SC_EDIT_SERIAROOM,
	SC_SERIAROOM,
	SC_EDIT_HENDON,
	SC_HENDON,
	SC_EDIT_NEST,
	SC_NEST,
	SC_EDIT_ALFHLYRA,
	SC_ALFHLYRA,
	SC_EDIT_RESHIPON1,
	SC_RESHIPON1,
	SC_EDIT_RESHIPON2,
	SC_RESHIPON2,
	SC_EDIT_STOMPATH,
	SC_STOMPATH,
	SC_EDIT_SKASARAIR,
	SC_SKASARAIR,
	SC_END 
};

// ���� Ÿ��
enum MON_TYPE
{
	PLAYER,
	BOSS,
	NORMAL,
	MON_TYPE_END
};

// ���� ����(FSM)
enum MON_STATE
{
	MON_IDLE,
	MON_APPEAR,
	MON_TRACE,
	MON_ATTACK1,
	MON_ATTACK2,
	MON_NORMAL_ATTACKED,
	MON_THRUST_ATTACKED,
	MON_LEVITATE_ATTACKED,
	MON_DEAD,

	BOSS_IDLE,
	BOSS_APPEAR,	// ���� �����

	BOSS_TRACE,
	BOSS_ATTACK1,
	BOSS_ATTACK2,
	BOSS_ATTACK3,
	BOSS_ATTACK4,

	BOSS_BACKSTEP,
	BOSS_NORMAL_ATTACKED,
	BOSS_THRUST_ATTACKED,
	BOSS_LEVITATE_ATTACKED,

	BOSS_PREPATTERN,	// ���� ����� ��� �鸮�� ����
	BOSS_PATTERN1,		// ��������1
	BOSS_PATTERN2,		// ��������2
	BOSS_PATTERN3,		// ��������3
	BOSS_PATTERN3_FAIL,	// ��������3 ����������
	BOSS_PATTERN4,		// ��������4

	BOSS_FLYINGREADY,
	BOSS_FLYING,
	BOSS_ONEHANDUP,
	BOSS_TWOHANDUP,
	
	BOSS_GROGY,
	BOSS_DEAD,

	MON_END,
};

// ���� ä��
enum CHANNELID 
{ 
	SOUND_EFFECT,
	SOUND_EFFECT2,
	SOUND_EFFECT3,
	SOUND_BGM,
	MAXCHANNEL
};

// ���� Ÿ��(�Ϲ�, ����, ��ġ��)
enum ATT_TYPE
{
	ATT_NORMAL,
	ATT_LEVITATE,
	ATT_THRUST,
	ATT_WIDE,
	ATT_JUSTEFFECT,
	ATT_END,
};

// ������ Ÿ��(���, ����, ����, �㸮, �Ź�, ����, Īȣ, ����, �����, ����, �������, ������, �Ҹ�ǰ)
enum ITEM_TYPE
{
	ITEM_WEAPON,	// ����
	ITEM_TITLE,		// Īȣ
	ITEM_SHOULDER,	// ���
	ITEM_TOP,		// ����
	ITEM_PANTS,		// ����
	ITEM_WAIST,		// �㸮
	ITEM_SHOES,		// �Ź�
	ITEM_BRACELET,	// ����
	ITEM_NECKLACE,	// �����
	ITEM_RING,		// ����
	ITEM_ASSIST,	// �������
	ITEM_STONE,		// ������
	ITEM_EXPEND,	// �Ҹ�ǰ
};







template<typename T>
void	Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct	DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if(Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

struct	CTagFinder
{
public:
	CTagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& rObj)
	{
		return !lstrcmp(m_pString, rObj.first);
	}

private:
	const TCHAR* m_pString;
};

extern	HWND	g_hWnd;
#pragma once
// 기본 셋팅
#define		WINCX			800
#define		WINCY			600
#define		PURE			= 0
#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1	// 사망
#define		OBJ_EQUIP		2	// 장착
#define		OBJ_BUY			3	// 구매
#define		OBJ_SELL		4	// 판매
#define		PI				3.1415926535f
#define		VK_MAX			0xff

// 스킬 마나
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

// 스킬 쿨타임
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

// 타일 관련
#define		TILECX		64
#define		TILECY		64

	// == 세리아방 ==
#define		SERIAROOM_SIZEX 1080
#define		SERIAROOM_SIZEY 720

#define		SERIA_TILEX		21
#define		SERIA_TILEY		12

	// == 헨돈마이어 ==
#define		HENDON_SIZEX	3472
#define		HENDON_SIZEY	680

#define		HENDON_TILEX	55
#define		HENDON_TILEY	12

	// == 이시스의 둥지(보스방) ==
#define		NEST_SIZEX		1792
#define		NEST_SIZEY		840

#define		NEST_TILEX		28
#define		NEST_TILEY		13

#define		LIGHT_STONE		1
#define		DARK_STONE		2

	// == 알프라이라 ==
#define		ALFHLYRA_SIZEX		1600
#define		ALFHLYRA_SIZEY		600

#define		ALFHLYRA_TILEX		25
#define		ALFHLYRA_TILEY		10

	// == 레쉬폰1 ==
#define		RESHIPON1_SIZEX		1200
#define		RESHIPON1_SIZEY		600
			
#define		RESHIPON1_TILEX		19
#define		RESHIPON1_TILEY		10

	// == 레쉬폰2 ==
#define		RESHIPON2_SIZEX		1200
#define		RESHIPON2_SIZEY		600

#define		RESHIPON2_TILEX		19
#define		RESHIPON2_TILEY		10

	// == 스톰패스(스카사의 레어 전방) ==
#define		STOMPATH_SIZEX		1600
#define		STOMPATH_SIZEY		600

#define		STOMPATH_TILEX		25
#define		STOMPATH_TILEY		10

	// == 스카사의 레어(보스방) ==
#define		SKASARAIR_SIZEX		1600
#define		SKASARAIR_SIZEY		600

#define		SKASARAIR_TILEX		25
#define		SKASARAIR_TILEY		10

#pragma region 싱글톤 매크로
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
#pragma endregion 싱글톤 매크로

enum ATT_TYPE;

// 렌더 순서를 결정짓는 ID
enum RENDERID 
{	
	BACKGROUND,
	BACKGROUNDEFFECT,
	GAMEOBJECT,
	EFFECT,
	UI,
	OVERDUI,		// UI 위에 출력되는 아이콘, 체력바 등의 UI
	TWOOVERDUI,		// OVERDUI 위에 출력되는 체력줄, 아이템정보 등의 UI
	TRIPLEOVERDUI,
	QUADOVERDUI,
	OCTAOVERDUI,
	HEXAOVERDUI,
	MOUSEPOINTER,
	RENDER_END
};

// 히트박스의 피격 정보
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

// Obj 기본 정보
typedef struct tagInfo
{
	// 크기, 위치
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

	// 스테이터스
	float		fHp;		// HP
	float		fMaxHp;
	float		fMp;		// Mp
	float		fMaxMp;

	float		fAtk;		// 물리 공격력
	float		fDef;		// 물리 방어력

	float		fMAtk;		// 마법 공격력
	float		fMDef;		// 마법 방어력

	float		fStrength;	// 힘
	float		fAtkSpeed;	// 공격속도

	float		fHealth;	// 체력
	float		fMoveSpeed;	// 이동속도

	float		fFire;		// 화
	float		fWater;		// 수
	float		fLightness;	// 명
	float		fDarkness;	// 암

	float		fExorcism;	// 항마력
}INFO;

// 스프라이트 구현을 위한 Frame 구조체
typedef struct tagFrame
{
	int			iFrameStart;	// bmp파일에서 iMotion행에서의 현재 인덱스
	int			iFrameEnd;		// bmp파일에서 iMotion행에서의 열 인덱스
	int			iMotion;		// bmp파일에서 스프라이트의 세로 인덱스
	double		dwSpeed;		// 전환 속도 조절용, 크기가 커질수록 전환 속도가 느려짐
	double		dwTime;			// ??

}FRAME;

// 색상 구조체
typedef struct tagColor
{
	int R;
	int G;
	int B;
}RGB;

// 방향 타입
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

// 오브젝트 타입
enum OBJ_ID		
{ 
	OBJ_PLAYER,				// 플레이어
	OBJ_PLAYER_ATTACK,		// 플레이어 공격
	OBJ_PLAYER_WIDEATTACK,	// 플레이어 광역공격
	OBJ_EFFECT,				// 이펙트
	OBJ_MONSTER,			// 몬스터
	OBJ_MONSTER_ATTACK,		// 몬스터 공격
	OBJ_MONSTER_WIDEATTACK,	// 몬스터 광역공격
	OBJ_NPC,				// NPC
	OBJ_DECORATION,			// 장식품
	OBJ_DAMAGEFONT,			// 데미지 폰트
	OBJ_COMBOFONT,			// 콤보 폰트
	OBJ_CRITICALFONT,		// 크리티컬 폰트
	OBJ_AIRIALFONT,			// 에어리얼 폰트
	OBJ_BOSSHP,				// 보스 Hp 현황
	OBJ_BOSSHPBAR,			// 보스 Hp 바
	OBJ_BOSSHPNUM,			// 보스 Hp 줄 수
	OBJ_RUNESTONE1,			// 이시스가 소환한 룬스톤(낮)
	OBJ_RUNESTONE2,			// 이시스가 소환한 룬스톤(밤)
	OBJ_MONHP,				// 몬스터 Hp 현황
	OBJ_MONHPBAR,			// 몬스터 Hp 바
	OBJ_MONHPNUM,			// 몬스터 Hp 줄 수
	OBJ_MONPORTRAIT,		// 몬스터 초상화
	OBJ_MONSTERTYPE,		// 몬스터 타입
	OBJ_INVEN,				// 인벤토리 UI
	OBJ_STORE,				// 상점 UI
	OBJ_MYINFO,				// 내정보 UI
	OBJ_SKILLICON,			// 스킬 아이콘
	OBJ_ITEM,				// 아이템
	OBJ_INVENITEM,			// 인벤토리 아이템
	OBJ_EQUIPMENT,			// 장착중인 아이템(내정보창)
	OBJ_STOREITEM,			// 상점 아이템
	OBJ_MOUSE,				// 마우스
	OBJ_MOUSEPOINT,			// 마우스 포인터 꼭짓점
	OBJ_MAINUI,				// 메인UI
	OBJ_UI,					// UI
	OBJ_END					// END
};

// 씬 타입
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

// 몬스터 타입
enum MON_TYPE
{
	PLAYER,
	BOSS,
	NORMAL,
	MON_TYPE_END
};

// 보스 상태(FSM)
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
	BOSS_APPEAR,	// 보스 등장용

	BOSS_TRACE,
	BOSS_ATTACK1,
	BOSS_ATTACK2,
	BOSS_ATTACK3,
	BOSS_ATTACK4,

	BOSS_BACKSTEP,
	BOSS_NORMAL_ATTACKED,
	BOSS_THRUST_ATTACKED,
	BOSS_LEVITATE_ATTACKED,

	BOSS_PREPATTERN,	// 패턴 사용전 잠깐 들리는 상태
	BOSS_PATTERN1,		// 보스패턴1
	BOSS_PATTERN2,		// 보스패턴2
	BOSS_PATTERN3,		// 보스패턴3
	BOSS_PATTERN3_FAIL,	// 보스패턴3 실패했을시
	BOSS_PATTERN4,		// 보스패턴4

	BOSS_FLYINGREADY,
	BOSS_FLYING,
	BOSS_ONEHANDUP,
	BOSS_TWOHANDUP,
	
	BOSS_GROGY,
	BOSS_DEAD,

	MON_END,
};

// 사운드 채널
enum CHANNELID 
{ 
	SOUND_EFFECT,
	SOUND_EFFECT2,
	SOUND_EFFECT3,
	SOUND_BGM,
	MAXCHANNEL
};

// 공격 타입(일반, 띄우기, 밀치기)
enum ATT_TYPE
{
	ATT_NORMAL,
	ATT_LEVITATE,
	ATT_THRUST,
	ATT_WIDE,
	ATT_JUSTEFFECT,
	ATT_END,
};

// 아이템 타입(어깨, 상의, 하의, 허리, 신발, 무기, 칭호, 팔찌, 목걸이, 반지, 보조장비, 마법석, 소모품)
enum ITEM_TYPE
{
	ITEM_WEAPON,	// 무기
	ITEM_TITLE,		// 칭호
	ITEM_SHOULDER,	// 어깨
	ITEM_TOP,		// 상의
	ITEM_PANTS,		// 하의
	ITEM_WAIST,		// 허리
	ITEM_SHOES,		// 신발
	ITEM_BRACELET,	// 팔찌
	ITEM_NECKLACE,	// 목걸이
	ITEM_RING,		// 반지
	ITEM_ASSIST,	// 보조장비
	ITEM_STONE,		// 마법석
	ITEM_EXPEND,	// 소모품
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
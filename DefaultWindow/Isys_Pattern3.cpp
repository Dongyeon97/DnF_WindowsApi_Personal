#include "stdafx.h"
#include "Isys_Pattern3.h"

#include "ObjMgr.h"

#include "Player.h"
#include "AI.h"
#include "Monster.h"
#include "MonsterAttack.h"
#include "MonsterAttack2.h"
#include "Effect.h"
#include "SoundMgr.h"
#include "NonAlpha.h"
#include "RuneStone.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "UI_Alpha.h"
#include "TownCutsin.h"

CIsys_Pattern3::CIsys_Pattern3()
	: CState(BOSS_PATTERN3)
	, m_iSuccessCount(0)
	, m_IsSuccess(false)
{

}

CIsys_Pattern3::~CIsys_Pattern3()
{
}

void CIsys_Pattern3::Update()
{
	// Player�� ��ġ üũ
	CObj* pPlayer = CObjMgr::Get_Instance()->GetObjList(OBJ_PLAYER).front();
	float fPlayerX = pPlayer->Get_Info().fX;
	float fPlayerY = pPlayer->Get_Info().fY;

	// ���� �ڽ��� ��ġ üũ
	CMonster* pMonster = GetMonster();
	float fMonsterX = pMonster->Get_Info().fX;
	float fMonsterY = pMonster->Get_Info().fY;

	if (pPlayer)
	{
		// 2�� ����ȭ ���� ���Ը�� - ó�� �����Ҷ��� �ߵ�
		if (0 < pMonster->Get_dwTime() && 0 == m_iAttackCount && 0 == m_iPatternCount)
		{
			++m_iAttackCount;
			// �̽ý��� �������°� ��
			pMonster->Set_IsImmune(true);

			pMonster->Set_ScaleX(160.f);
			pMonster->Set_ScaleY(304.f);
			pMonster->Set_FrameKey(L"Isys_FlyingReady");
			pMonster->Set_State(BOSS_FLYINGREADY);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_skill_04.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);
		}
		else if (1.2 < pMonster->Get_dwTime() && 1 == m_iAttackCount && 0 == m_iPatternCount)
		{
			++m_iAttackCount;

			// ���� ����
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 45.f, fMonsterY - 115.f, 702.f, 524.f, 0.f, 180.f, 0.f, 0.f, 0.9f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpWing", { 255, 0, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 6, 0, 0.125, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_RenderID(BACKGROUNDEFFECT);

			// ȸ���� �߻�
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CTownCutsin>::
				Create_Obj(ATT_JUSTEFFECT, false, 400.f, 300.f, 800.f, 600.f, 0.f, 0.f, 0.f, 0.f, 1.5f, 800.f, 600.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_Wind", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 18, 0, 0.08, 0. });
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_AlphaValue(200);

			pMonster->Set_ScaleX(371.f);
			pMonster->Set_ScaleY(373.f);
			pMonster->Set_FrameKey(L"Isys_FlyingReady2");
			pMonster->Set_State(BOSS_APPEAR);
		}
		else if (2.1 < pMonster->Get_dwTime() && 2 == m_iAttackCount && 0 == m_iPatternCount)
		{
			++m_iAttackCount;
			// ���� ���
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX - 80.f, fMonsterY - 200.f, 415.f, 636.f, 0.f, 180.f, 0.f, 0.f, 0.6f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Isys_JumpBeam", { 255, 255, 255 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 5, 0, 0.1, 0. });

			// �Ȱ�
			CObjMgr::Get_Instance()->Add_Object(OBJ_EFFECT, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_JUSTEFFECT, true, fMonsterX + 50.f, fMonsterY + 50.f, 871.f, 419.f, 0.f, 180.f, 0.f, 0.f, 1.0f, 700, 350.f, pMonster->Get_Rect().bottom,
					pMonster->Get_Info().fAtk, 10.f, 5.f, 1.f, 3.5f, 90.f, 180.f, 1.f, L"Smoke_Jump_FloorTest", { 0, 0, 0 }));
			CObjMgr::Get_Instance()->GetObjList(OBJ_EFFECT).back()->Set_Frame(tagFrame{ 0, 9, 0, 0.1, 0. });
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_wing_01.ogg", SOUND_EFFECT, g_fVolume + 0.2f);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_wing_disappear.ogg", SOUND_EFFECT2, g_fVolume + 0.2f);
			CSoundMgr::Get_Instance()->PlaySoundW(L"isys_meet_whirlwind.ogg", SOUND_EFFECT3, g_fVolume + 0.2f);

			// ����� �̵��� ���Ͻ���
			pMonster->Set_Pos(NEST_SIZEX * 0.5f, 300.f);

			pMonster->Set_ScaleX(500.f);
			pMonster->Set_ScaleY(500.f);
			pMonster->Set_FrameKey(L"Isys_Flying");
			pMonster->Set_State(BOSS_FLYING);
		}

		// 1�� ��/�� �齺�� ����
		if (3 < pMonster->Get_dwTime() && 3 == m_iAttackCount && 0 == m_iPatternCount)
		{
			++m_iAttackCount;
			// �μž� �� ���� ��� - �ε��� 1��
			CObjMgr::Get_Instance()->Add_Object(OBJ_DECORATION, CAbstractFactory<CRuneStone>::
				Create_Obj(NEST_SIZEX * 0.5f + 200.f, 300.f, L"BlueRune"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_SpriteIndex(1);
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_DrawOption(1);

			// �� �齺�� - 1
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
							 1, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
							 2, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
							 3, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
							 4, 1, OBJ_RUNESTONE1, L"BlueRune");

			// �� �齺�� - 2
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
							 1, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
							 2, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
							 3, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
							 float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
							 4, 1, OBJ_RUNESTONE2, L"RedRune");
		}

		// 2�� ��/�� �齺�� ����
		else if (3 < pMonster->Get_dwTime() && 0 == m_iAttackCount && 1 == m_iPatternCount)
		{
			++m_iAttackCount;
			// �μž� �� ���� ��� - �ε��� 2��
			CObjMgr::Get_Instance()->Add_Object(OBJ_DECORATION, CAbstractFactory<CRuneStone>::
				Create_Obj(NEST_SIZEX * 0.5f + 200.f, 300.f, L"RedRune"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_SpriteIndex(2);
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_DrawOption(1);

			// �� �齺�� - 1
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				1, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				2, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				3, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				4, 1, OBJ_RUNESTONE1, L"BlueRune");

			// �� �齺�� - 2
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				1, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				2, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				3, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				4, 1, OBJ_RUNESTONE2, L"RedRune");
		}

		// 3�� ��/�� �齺�� ����
		else if (3 < pMonster->Get_dwTime() && 0 == m_iAttackCount && 2 == m_iPatternCount)
		{
			++m_iAttackCount;
			// �μž� �� ���� ��� - �ε��� 3��
			CObjMgr::Get_Instance()->Add_Object(OBJ_DECORATION, CAbstractFactory<CRuneStone>::
				Create_Obj(NEST_SIZEX * 0.5f + 200.f, 300.f, L"RedRune"));
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_SpriteIndex(3);
			CObjMgr::Get_Instance()->GetObjList(OBJ_DECORATION).back()->Set_DrawOption(1);

			// �� �齺�� - 1
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				1, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				2, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				3, 1, OBJ_RUNESTONE1, L"BlueRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				4, 1, OBJ_RUNESTONE1, L"BlueRune");

			// �� �齺�� - 2
			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				1, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f - rand() % 100),
				2, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f - rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				3, 1, OBJ_RUNESTONE2, L"RedRune");

			Making_RuneStone(float(NEST_SIZEX * 0.5f + rand() % 600),
				float(NEST_SIZEY * 0.5f + 200.f + rand() % 100),
				4, 1, OBJ_RUNESTONE2, L"RedRune");
		}

		list<CObj*> lstLight = CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE1);
		list<CObj*> lstDark = CObjMgr::Get_Instance()->GetObjList(OBJ_RUNESTONE2);

		list<CObj*>::iterator iterLight = lstLight.begin();
		list<CObj*>::iterator iterDark = lstDark.begin();

		// ��������
		if ((12 < pMonster->Get_dwTime() && 4 == m_iAttackCount && 0 == m_iPatternCount)
			|| (12 < pMonster->Get_dwTime() && 1 == m_iAttackCount && 0 < m_iPatternCount))
		{
			++m_iAttackCount;
			switch (m_iPatternCount)
			{
				// ù��° ���� - 1�� �ε��� �� �μ���
			case 0:
				iterLight = find_if(lstLight.begin(), lstLight.end(), [](auto& iter) {
					if (1 == iter->Get_SpriteIndex())
						return true;
					return false; });
				iterDark = find_if(lstDark.begin(), lstDark.end(), [](auto& iter) {
					if (1 == iter->Get_SpriteIndex())
						return true;
					return false; });

				// ���� �Ѵ� end���ͷ����͸� ���� 1ȸ ����
				if (iterLight == lstLight.end() && iterDark == lstDark.end() &&
					(3 == lstLight.size() && 3 == lstDark.size()))
					m_IsSuccess = true;
				break;

				// �ι�° ����
			case 1:
				iterLight = find_if(lstLight.begin(), lstLight.end(), [](auto& iter) {
					if (2 == iter->Get_SpriteIndex())
						return true;
					return false; });
				iterDark = find_if(lstDark.begin(), lstDark.end(), [](auto& iter) {
					if (2 == iter->Get_SpriteIndex())
						return true;
					return false; });

				// ���� �Ѵ� end���ͷ����͸� ���� 1ȸ ����
				if (iterLight == lstLight.end() && iterDark == lstDark.end() &&
					(3 == lstLight.size() && 3 == lstDark.size()))
					m_IsSuccess = true;
				break;

				// ����° ����
			case 2:
				iterLight = find_if(lstLight.begin(), lstLight.end(), [](auto& iter) {
					if (3 == iter->Get_SpriteIndex())
						return true;
					return false; });
				iterDark = find_if(lstDark.begin(), lstDark.end(), [](auto& iter) {
					if (3 == iter->Get_SpriteIndex())
						return true;
					return false; });

				// ���� �Ѵ� end���ͷ������̰�, �ش� �齺�游 �ı������� ���� 1ȸ ����
				if (iterLight == lstLight.end() && iterDark == lstDark.end() &&
					(3 == lstLight.size() && 3 == lstDark.size()))
					m_IsSuccess = true;
				break;
			}

			if (m_IsSuccess)
				++m_iSuccessCount;
		}
		
		// ���� ����Ŭ ���� ���� - 15���̳��� ���� ����� �齺���� �ı����� ���� �� ����

		// 1. �̽ý��� ���� 3ȸ�� ��� �����߰�, �� �� 2ȸ ���� ���������� ���� �׷α�
		if (15 < pMonster->Get_dwTime() && 2 == m_iPatternCount && 2 <= m_iSuccessCount)
		{
			++m_iPatternCount;

			Exit();
			pMonster->Set_ScaleX(371.f);
			pMonster->Set_ScaleY(373.f);
			pMonster->Set_IsImmune(false);
			pMonster->Set_State(MON_STATE::BOSS_GROGY);
			m_pAI->SetCurState(MON_STATE::BOSS_GROGY);
			m_pAI->GetCurState()->Enter();
		}
		// 2. �̽ý��� ���� 3ȸ�� ��� �����߰�, �� �� 2ȸ ���� ���������� ������ �������鼭 ���ִ� ����� ����(���ۿ���)
		// �Ŀ� �ٽ� ����3 ����
		else if (15 < pMonster->Get_dwTime() && 2 == m_iPatternCount && 2 > m_iSuccessCount)
		{
			Exit();
			++m_iPatternCount;
			pMonster->Set_State(MON_STATE::BOSS_PATTERN3_FAIL);
			m_pAI->SetCurState(MON_STATE::BOSS_PATTERN3_FAIL);
			m_pAI->GetCurState()->Enter();
		}
		// 3. ���� ���Ƚ���� 3ȸ �̸��̰�, �̹� ������ ���� ���������� ������ ����� �ߵ� -> ���� ���ϻ���Ŭ ����
		else if (15 < pMonster->Get_dwTime() && 2 > m_iPatternCount && !m_IsSuccess)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_ATTACK, CAbstractFactory<CMonsterAttack>::
				Create_Obj(ATT_LEVITATE, true, fPlayerX, pPlayer->Get_TileCollision().bottom - 32, NEST_SIZEX, NEST_SIZEY, 0.f, 0.f, 0.f, 0.f, 1.f, NEST_SIZEX, NEST_SIZEY, pPlayer->Get_TileCollision().bottom - 32,
					pMonster->Get_Info().fAtk, 10000.f, 0.f, 0.f, 10.f, 90.f, 0.f, 0.2f, L"Isys_Awaken", { 0, 0, 0 }));

			for (int i = 0; i < 12; ++i)
			{
				Making_Thunder(float(rand() % NEST_SIZEX), float(200 + rand() % 600), 1.f);
			}

			Exit();
			++m_iPatternCount;
			pMonster->Set_State(MON_STATE::BOSS_PATTERN3);
			m_pAI->SetCurState(MON_STATE::BOSS_PATTERN3);
			m_pAI->GetCurState()->Enter();
		}
		// 4. ���� ���Ƚ���� 3ȸ �̸��̰�, �̹� ������ ���� ���������� -> ���� ���ϻ���Ŭ ����
		else if (15 < pMonster->Get_dwTime() && 2 > m_iPatternCount && m_IsSuccess)
		{
			Exit();
			++m_iPatternCount;
			pMonster->Set_State(MON_STATE::BOSS_PATTERN3);
			m_pAI->SetCurState(MON_STATE::BOSS_PATTERN3);
			m_pAI->GetCurState()->Enter();
		}
	}
}

void CIsys_Pattern3::LateUpdate()
{
}

void CIsys_Pattern3::Enter()
{
	CMonster* pMonster = GetMonster();
	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;
	m_IsSuccess = false;	// ���� ���� ����Ŭ�� ���� �������θ� false�� ������
}

void CIsys_Pattern3::Exit()
{
	CMonster* pMonster = GetMonster();

	pMonster->Set_dwTime(0);
	m_iAttackCount = 0;		// ���� ���� ����Ŭ�� ���� ����Ƚ�� �ʱ�ȭ
	m_IsSuccess = false;	// ���� ���� ����Ŭ�� ���� �������θ� false�� ������

	// �ѹ� ���� ����Ŭ �������� �齺�� ���� �ı�
	CObjMgr::Get_Instance()->Delete_ID(OBJ_RUNESTONE1);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_RUNESTONE2);
	CObjMgr::Get_Instance()->Delete_ID(OBJ_DECORATION);
}

void CIsys_Pattern3::Making_RuneStone(float _fX, float _fY, int _iSpriteIndex, int _iOption, OBJ_ID _eType, TCHAR* _pKey)
{
	CObjMgr::Get_Instance()->Add_Object(_eType, CAbstractFactory<CRuneStone>::
		Create_Obj(_fX, _fY, _pKey));
	CObjMgr::Get_Instance()->GetObjList(_eType).back()->Set_SpriteIndex(_iSpriteIndex);
	CObjMgr::Get_Instance()->GetObjList(_eType).back()->Set_DrawOption(_iOption);
}

void CIsys_Pattern3::Making_Thunder(float _fX, float _fY, float _fLifeTime)
{
	// ���� ����Ʈ
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER_WIDEATTACK, CAbstractFactory<CMonsterAttack>::
		Create_Obj(ATT_JUSTEFFECT, false, _fX, _fY, 672.f, 693.f, 0.f, 0.f, 0.f, 0.f, _fLifeTime, 150.f, 300.f, 0.f,
			0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, L"Isys_MeetLightning", { 0, 0, 0 }));
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_Frame(tagFrame{ 0, 11, 0, 0.085, 0. });
	CObjMgr::Get_Instance()->GetObjList(OBJ_MONSTER_WIDEATTACK).back()->Set_RenderID(GAMEOBJECT);
}

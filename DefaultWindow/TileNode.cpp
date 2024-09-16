#include "stdafx.h"
#include "TileNode.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"


CTileNode::CTileNode()
{
}

CTileNode::~CTileNode()
{
	Release();
}

void CTileNode::Initialize()
{
	// 타일 크기 설정
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Edit/tile_1.bmp", L"XTile");
	m_pFrameKey = L"XTile";
}

int CTileNode::Update()
{
	__super::Update_Rect();

	return 0;
}

void CTileNode::Late_Update()
{

}

void CTileNode::Render(HDC hDC)
{
	// float	fScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	// float	fScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
}

void CTileNode::Release()
{
}

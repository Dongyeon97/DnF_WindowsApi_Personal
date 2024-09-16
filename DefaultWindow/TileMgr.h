#pragma once

#include "TileNode.h"

class CTileMgr
{
public:
	CTileMgr();
	~CTileMgr();
public:
	static CTileMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	static CTileMgr* m_pInstance;

public:
	void	Initialize();
	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();

	void	Picking(POINT pt, int _iDrawID, int _iOption);
	vector<CObj*>&	GetTileSeria()	{ return m_vecTileSeria; }
	vector<CObj*>&	GetTileHendon() { return m_vecTileHendon; }
	vector<CObj*>&	GetTileNest()	{ return m_vecTileNest; }
	vector<CObj*>&	GetTileAlfhlyra() { return m_vecTileAlfhlyra; }
	vector<CObj*>&	GetTileReshipon1() { return m_vecTileReshipon1; }
	vector<CObj*>&	GetTileReshipon2() { return m_vecTileReshipon2; }
	vector<CObj*>&	GetTileSkasaRair() { return m_vecTileSkasaRair; }

	void	Save_Tile(const WCHAR* _filepath);
	void	Load_Tile(const WCHAR* _filepath);

private:
	vector<CObj*>		m_vecTileSeria;		// 세리아방 타일이 저장될 벡터
	vector<CObj*>		m_vecTileHendon;	// 헨돈마이어 타일이 저장될 벡터
	vector<CObj*>		m_vecTileNest;		// 천공의 둥지 타일이 저장될 벡터
	vector<CObj*>		m_vecTileAlfhlyra;	// 알프라이라 타일이 저장될 벡터
	vector<CObj*>		m_vecTileReshipon1;	// 레쉬폰1 타일이 저장될 벡터
	vector<CObj*>		m_vecTileReshipon2;	// 레쉬폰2 타일이 저장될 벡터
	vector<CObj*>		m_vecTileSkasaRair;	// 스카사의 레어 타일이 저장될 벡터

	DWORD				m_lPickedTime;
};


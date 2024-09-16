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
	vector<CObj*>		m_vecTileSeria;		// �����ƹ� Ÿ���� ����� ����
	vector<CObj*>		m_vecTileHendon;	// ����̾� Ÿ���� ����� ����
	vector<CObj*>		m_vecTileNest;		// õ���� ���� Ÿ���� ����� ����
	vector<CObj*>		m_vecTileAlfhlyra;	// �������̶� Ÿ���� ����� ����
	vector<CObj*>		m_vecTileReshipon1;	// ������1 Ÿ���� ����� ����
	vector<CObj*>		m_vecTileReshipon2;	// ������2 Ÿ���� ����� ����
	vector<CObj*>		m_vecTileSkasaRair;	// ��ī���� ���� Ÿ���� ����� ����

	DWORD				m_lPickedTime;
};


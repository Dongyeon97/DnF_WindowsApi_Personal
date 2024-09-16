#include "UI.h"
class CUI_Base :
    public CUI
{
public:
	CUI_Base();
	virtual ~CUI_Base();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

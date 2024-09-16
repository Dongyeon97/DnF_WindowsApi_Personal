// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

#include <vfw.h>
#pragma comment(lib, "vfw32.lib")

// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일

// - 코드 재사용을 위한 초창기 방법 중 하나, 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자에 의해 제공
// - 라이브러리의 대다수 함수들은 함수의 정의 및 선언들을 필요로 하기 때문에 링크되기 전 전처리기에 의해 해당 헤더파일을 원시 프로그램(현재 사용자가 작성한 프로그램)에 포함시켜야 한다.
// - 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 된다.

#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

#include <io.h>
#include <iostream>

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif


using namespace std;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

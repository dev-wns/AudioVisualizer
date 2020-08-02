#pragma once

// 자주 사용되지만 변경은 잘 안될만한 
// 헤더파일과 라이브러리 또는 매크로 정의를 포함 합니다.
#define WIN32_LEAN_AND_MEAN // 자주 쓰지 않는 API를 막아 빌드 속도를 높인다. ( MFC 사용하지 않을 때 이용 )

// 윈도우 관련 헤더
#include <WinSock2.h> 
#include <windows.h>
#include <windowsx.h>


// 표준 템플릿 라이브러리
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <algorithm>
#include <memory>
#include <set>
#include <list>
#include <assert.h>


// External Include
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\D3DX10math.h"


// 링크
#pragma comment(lib,"winmm.lib") // use timeGetTime
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\dxgi.lib")
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\d3dx11.lib")

// Utility
#include "BaseUtility.hpp"
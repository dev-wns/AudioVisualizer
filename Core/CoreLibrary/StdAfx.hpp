#pragma once
// 컴파일 에러수준4 이상
// 사용하지 않는 전역 함수를 제거합니다. 무시.
#pragma warning( disable : 4505 )

// 자주 쓰지 않는 API를 막아 빌드 속도를 높인다. ( MFC 사용하지 않을 때 이용 )
#define WIN32_LEAN_AND_MEAN 

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

#include "Exception.h"

// 메모리 누수 확인
//#include <stdlib.h>
//#include <crtdbg.h>

// External Include
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\D3DX10math.h"

#pragma comment(lib,"winmm.lib") // use timeGetTime
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\dxgi.lib")
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\d3dx11.lib")
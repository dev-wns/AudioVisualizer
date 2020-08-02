#pragma once

// ���� �������� ������ �� �ȵɸ��� 
// ������ϰ� ���̺귯�� �Ǵ� ��ũ�� ���Ǹ� ���� �մϴ�.
#define WIN32_LEAN_AND_MEAN // ���� ���� �ʴ� API�� ���� ���� �ӵ��� ���δ�. ( MFC ������� ���� �� �̿� )

// ������ ���� ���
#include <WinSock2.h> 
#include <windows.h>
#include <windowsx.h>


// ǥ�� ���ø� ���̺귯��
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


// ��ũ
#pragma comment(lib,"winmm.lib") // use timeGetTime
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\dxgi.lib")
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\d3dx11.lib")

// Utility
#include "BaseUtility.hpp"
#pragma once
// ������ ��������4 �̻�
// ������� �ʴ� ���� �Լ��� �����մϴ�. ����.
#pragma warning( disable : 4505 )

// ���� ���� �ʴ� API�� ���� ���� �ӵ��� ���δ�. ( MFC ������� ���� �� �̿� )
#define WIN32_LEAN_AND_MEAN 

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

#include "Exception.h"

// �޸� ���� Ȯ��
//#include <stdlib.h>
//#include <crtdbg.h>

// External Include
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\d3dx11.h"
#include "..\\..\\ExternalLibraries\\DirectX11\\Include\\D3DX10math.h"

#pragma comment(lib,"winmm.lib") // use timeGetTime
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\dxgi.lib")
//#pragma comment(lib,"..\\ExternalLibraries\\DirectX11\\d3dx11.lib")
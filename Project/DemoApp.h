#pragma once
#include "App.h"

struct Vertex
{
	VECTOR3 position;
	VECTOR4 color;
}; //�����ڵ忡�� float x,y,z  / float r, g,b, a �� �Ǿ�����. �� �Ǵ��� Ȯ���ʿ� 

class DemoApp : public App
{
public:
	DemoApp();
	~DemoApp();
	virtual void Init(HWND hWnd);
	virtual void Update();
	virtual void Render();
	virtual void Release();

private:
	virtual void	DataLoading();
	virtual void	DataRelease();

private:
	bool  ObjLoad();
	void ObjRelease();
	void ObjUpdate(float dTime = 0);
	void ObjDraw(float dTime = 0);

	ID3D12Resource* mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW* mVertexBufferView = nullptr;
};


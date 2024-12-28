#pragma once
#include "App.h"

struct Vertex
{
	VECTOR3 position;
	VECTOR4 color;
};




class DemoApp : public App
{
public:
	DemoApp();
	~DemoApp();
	virtual void Init(HWND hWnd);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Release();

private:
	virtual void DataLoading() override;
	virtual void DataRelease() override;
	virtual void CreateCBs() override;

private:
	bool ObjLoad();
	void ObjRelease();
	void ObjUpdate(float dTime = 0);
	void ObjDraw(float dTime = 0);

	ID3D12Resource* mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW* mVertexBufferView = nullptr;
	COLOR mColor = { 1, 0, 0, 1 };
	float mColorTime = 0.f;
	float mColorSpeed = 0.6f;
};


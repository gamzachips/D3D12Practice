/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3/YENA : 2D/3D 렌더링 엔진.						                       // 
//                                                                         //
//  제 작 : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Tech,Inc http://www.zero-g.kr						   //	
//  초기개발 : 2003.12 - 2004.03.                                          //
//  개발환경 : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008       //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0c(2007, November)                           //
//                  OpenGL 1.x / 2.x                                       //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  테스트 환경 : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                      Core2 w/Quad                                       //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6 Series                       //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9xxx Series.                //
//                             GeForce 2/4xx GTS Series.                   //
//                             GeForce 7xx GTX Series.                     //
//                             GeForce 2Way-SLI / 3Way-SLI		   	       //
//                OS - Windows 98 / 2K / XP / VISTA / Win7 x32:x64         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
// __class__.h: __작업__ 헤더.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04. Update.
// 2017.01. Update. __class__ / DX11.1 (Windows SDK 8.1)
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma warning(disable:4996)
 


/////////////////////////////////////////////////////////////////////////////
//
// class __class__ : __작업__ 운용 클래스.
//
class __class__
{
protected:

public:
	__class__();
	virtual ~__class__();

	virtual int  Create(LPDEVICE pDev);
	virtual void Release();
	virtual void Update(float dTime);
	virtual void Draw(float dTime);
	virtual void Apply(LPDXDC pDXDC);
	virtual void Clear();

};

//typedef __class__ YnShader;




//////////////////////////////////////////////////////////////////////////////// 
//
// __클래스__ 전역 함수들
//
//////////////////////////////////////////////////////////////////////////////// 

int  __class__Create(LPDEVICE pDev);
void __class__Release();
void __class__(float dTime);
void __class__Draw(float dTime);




/////////////////////////////////////////////////////////////////////////////
//
//  __클래스__ 전역 데이터들.
//  
namespace YENA
{
	//....
}
using namespace YENA;




/****************** end of file "__class__.h" *******************************/
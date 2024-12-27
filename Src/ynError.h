// 
//! \file   ynError.h
//! \brief  예나 / 엔진 / 예외처리 프레임워크
//! 
//! \author 김 기홍 Kihong Kim / onlysonim@gmail.com
//! \date   2003.11.4. 
//! \date   2010.08.20. Updated. Yena 1.01 통합 / VS08, VS10 
//! \date   2012.12.10. Updated. C++11 / GCC5 / VS12 
//! \date   2015.10.20. Updated. C++11/14 / GCC6.1 / VS15 
//! \date   2018.03.05. Updated. C++17  / GCC11 / VS17
//! \date   2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//
#pragma once
#pragma warning(disable:4996)
#include "windows.h"
#include "tchar.h"

#include "locale"
#include "codecvt"
//#using namespace std;
using namespace std;

namespace YENA {

#ifndef _DEPRECATED 
#define _DEPRECATED(a) [[deprecated(a)]]
#define _SAMPLE_TEST  _DEPRECATED("샘플코드/테스트용") 
#else
#define _SAMPLE_TEST
#endif

#ifndef _YNGLOBAL
#define _YNGLOBAL		__declspec(selectany)
#define _YNGLOBALCONST  extern const __declspec(selectany)
#define GLOBALCONST  _YNGLOBALCONST
#endif

#ifndef YN_OK
#define YN_OK    0						//작업 종료. 문제 없음
#define YN_FAIL -1						//작업 오류. 기타 오류 있음..
//#define YN_FAIL_xxx                   //필요한 에러코드를 추가할 것. 
#define YN_FAILED(v)  ((v) != YN_OK)	//오류 검사.
#endif

//#include "wstring"
//#undef in
//#undef out



/////////////////////////////////////////////////////////////////////////////
//
// 문자열 운용 함수들
//
/////////////////////////////////////////////////////////////////////////////

inline string ynVaStringA (const char* fmt, ...)
{
	char buff[1024] = "";
	va_list vl;
	va_start(vl, fmt);
	vsprintf(buff, fmt, vl);
	va_end(vl);
    return string(buff);
} 

inline wstring ynVaStringW (const WCHAR* fmt, ...)
{
	WCHAR buff[1024] = L"";
	va_list vl;
	va_start(vl, fmt);
	vswprintf(buff, fmt, vl);
	va_end(vl);
    return wstring(buff);
}

/*#ifdef _UNICODE
#define yn_va_size(fmt,...)  vswprintf(nullptr, 0, fmt, __VA_ARGS__)
#define yn_va_printf(buff, size, fmt,...)  vswprintf(buff, size, fmt, __VA_ARGS__)
#else
#define yn_va_size(fmt,...)  _snprintf(nullptr, 0, fmt, __VA_ARGS__)
#define yn_va_printf(buff, size, fmt,...)  _sprintf(buff, size, fmt, __VA_ARGS__)
#endif

inline wstring ynVaStringW (const WCHAR* fmt, ...)
{
	size_t size = va_size(fmt);
	if (size <= 0) return _T("...");
	unique_ptr<WCHAR[]> buff(new WCHAR[size + 1]);
	//_swprintf(buff.c_str(), size, fmn)
	va_printf(buff.get(), size, fmt); 

    return wstring(buff.get());
}*/

/*
inline wstring ynVaStringWL (const WCHAR* fmt, va_list& vl)
{
	WCHAR buff[1024] = L"";
	//va_list vl;
	//va_start(vl, fmt);
	vswprintf(buff, fmt, vl);
	va_end(vl);
    return wstring(buff);
}
*/

inline string ynVaStringAL (const char* fmt, va_list& vl)
{
	size_t size = _vsnprintf(nullptr, 0, fmt, vl);			//형식화 문자열 길이 얻기 (널문자 제외)
	if (size<=0) return string("---");
	unique_ptr<CHAR[]> buff(new CHAR[size + 1]);			//'널문자' 포함, 공간확보.
	vsprintf(buff.get(), fmt, vl);
	va_end(vl);
	return string(buff.get());
}

inline wstring ynVaStringWL (const WCHAR* fmt, va_list& vl)
{
	size_t size = _vsnwprintf(nullptr, 0, fmt, vl);
	if (size<=0) return wstring(_T("---"));
	unique_ptr<WCHAR[]> buff(new WCHAR[size + 1]);
	vswprintf(buff.get(), fmt, vl);
	va_end(vl);
	return wstring(buff.get());
}


template<typename ... Args>
inline string ynVaStringA2 (const char* fmt, Args ... args)
{
	size_t size = _snprintf(nullptr, 0, fmt, args...);			//형식화 문자열 길이 얻기 (널문자 제외)
	if (size<=0) return string("---");
	unique_ptr<CHAR[]> buff(new CHAR[size + 1]);				//'널문자' 포함, 공간확보.
	sprintf(buff.get(), fmt, args...);
	return string(buff.get());
}

template<typename ... Args>
inline wstring ynVaStringW2 (const WCHAR* fmt, Args ... args)
{
	size_t size = _snwprintf(nullptr, 0, fmt, args...);
	if (size<=0) return wstring(_T("---"));
	unique_ptr<WCHAR[]> buff(new WCHAR[size + 1]);
	_swprintf(buff.get(), fmt, args...);
	return wstring(buff.get());
}


inline string ynStrHRA (HRESULT hr)
{
	char err[20] = "";
    sprintf_s(err, "\nHR=0x%08X", static_cast<UINT>(hr));
    return string(err);
} 

inline wstring ynStrHRW (HRESULT hr)
{
	WCHAR err[20] = L"";
    _swprintf(err,  L"\nHR=0x%08X", static_cast<UINT>(hr));
    return wstring(err);
}

/*inline string ynDbgA(const char* file, UINT line, CHAR* fn)
{
	return ynToStrA("%s(%d) : %s", file, line, fn);
}

inline wstring ynDbgW(WCHAR* file, UINT line, WCHAR* fn)
{
	return ynToStrW(L"%s(%d) : %s", file, line, fn);
}*/

#define ynToStrA		ynVaStringA
#define ynToStrW		ynVaStringW

#define _ynStrFmtX(dst, src, fn, ...)   { (dst)=fn((src), __VA_ARGS__); } 
//#define _ynStrFmt2X(dst, src, fn, ...)  { (dst)=fn((src), __VA_ARGS__); } 
#define ynStrFmtA(dst, src, ...)		_ynStrFmtX(dst, src, ynVaStringA, __VA_ARGS__) 
#define ynStrFmtW(dst, src, ...)		_ynStrFmtX(dst, src, ynVaStringW, __VA_ARGS__) 
#define ynStrFmt2A(dst, src, ...)		_ynStrFmtX(dst, src, ynVaStringA2, __VA_ARGS__)
#define ynStrFmt2W(dst, src, ...)		_ynStrFmtX(dst, src, ynVaStringW2, __VA_ARGS__)

#define _ynStrFmtVX(dst, src, fn)		{ va_list v1,v2; va_start(v1, src); va_copy(v2, v1); va_end(v1); (dst)=fn((src), v2); }
//#define ynStrFmtVW(dst, src)			{ va_list v1,v2; va_start(v1, src); va_copy(v2, v1); va_end(v1); (dst)=ynVaStringWL((src), v2); }
//#define ynStrFmtVA(dst, src)			{ va_list v1,v2; va_start(v1, src); va_copy(v2, v1); va_end(v1); (dst)=ynVaStringAL((src), v2); }
#define ynStrFmtVA(dst, src)			_ynStrFmtVX(dst, src, ynVaStringAL) 
#define ynStrFmtVW(dst, src)			_ynStrFmtVX(dst, src, ynVaStringWL)

#ifdef _UNICODE 
	#define ynStrFmt(dst, src, ...)		ynStrFmtW(dst, src, __VA_ARGS__) 
	#define ynStrFmt2(dst, src, ...)	ynStrFmt2W(dst, src, __VA_ARGS__) 
	#define ynStrFmtV(dst, src)			ynStrFmtVW(dst, src)
	//#define ynStrFmt(dst, src, ...)   { (dst)=ynVaStringW((src), __VA_ARGS__); } 
	//#define ynStrFmt2(dst, src, ...)  { (dst)=ynVaStringW2((src), __VA_ARGS__); } 
	//#define ynStrFmtV(dst, src)		{ va_list v1,v2; va_start(v1, src); va_copy(v2, v1); va_end(v1); (dst)=ynVaStringWL((src), v2); }
	
	#define ynToStr(fmt, ...)			ynVaStringW(fmt, __VA_ARGS__)
	//#define ynToStr(fmt, ...)			ynToStrW( __VA_ARGS__ + fmt )
	#define ynToStrVCE(fmt, ...)		ynVaStringW(fmt, ##__VA_ARGS__)		

	#define ynStrHR  ynStrHRW
	//#define ynDbg  ynDbgW(__FILEW__, __LINE__, __FUNCTIONW__)
	#define ynStrConv(src)				ynError::conv.from_bytes(src)
	#define ynStrConvwp(src)			ynStrconv(src).c_str()
#else
	#define ynStrFmt(dst, src, ...)		ynStrFmtA(dst, src, __VA_ARGS__) 
	#define ynStrFmt2(dst, src, ...)	ynStrFmt2A(dst, src, __VA_ARGS__) 
	#define ynStrFmtV(dst, src)			ynStrFmtVA(dst, src)
	//#define ynStrFmt(dst, src, ...)   { (dst)=ynVaStringA((src), __VA_ARGS__); } 
	//#define ynStrFmt2(dst, src, ...)  { (dst)=ynVaStringA2((src), __VA_ARGS__); } 
	//#define ynStrFmtV(dst, src)		{ va_list v1,v2; va_start(v1, src); va_copy(v2, v1); va_end(v1); (dst)=ynVaStringAL((src), v2); }

	#define ynToStr(fmt, ...)			ynVaStringA(fmt, __VA_ARGS__)
	//#define ynToStr(fmt, ...)			ynToStrA( __VA_ARGS__ + fmt )
	#define ynToStrVCE(fmt, ...)		ynVaStringA(fmt, ##__VA_ARGS__)

	#define strHR  ynStrHRA
	//#define dbg  dbgA(__FILE__, __LINE__, __FUNCTION__)
#endif



/////////////////////////////////////////////////////////////////////////////
//
// 디버깅 메세지 출력 매크로
//
/////////////////////////////////////////////////////////////////////////////
#define ynMessageBoxA(show, msg) \
	if(show) MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONERROR); 

#define ynMessageBoxW(show, msg) \
	if(show) MessageBoxW(NULL, msg, _T("Error"), MB_OK | MB_ICONERROR); 

#define ynOutputLogs(msg)	 	//로그파일 남기기...(생략)
//#define ynOutputMessage(show, mt, msg) \
//{	OutputDebugString(_T("\n--<< "mt" >>------------------------------------------------------------------------- \n")); 
// ex) ynOutputMessage(show, "Exception", errmsg.c_str());

#define _line_head_  "\n--<< Error >>------------------------------------------------------------------------- \n"
#define _line_tail_  "\n-------------------------------------------------------------------------------------- \n\n"

#define ynOutputMessageA(show, msg) \
{	\
	OutputDebugStringA(_line_head_); \
	OutputDebugStringA(msg);\
	OutputDebugStringA(_line_tail_); \
	ynOutputLogs(msg); \
	ynMessageBoxA(show, msg); \
}

#define ynOutputMessageW(show, msg) \
{	\
	OutputDebugStringW(_T(_line_head_)); \
	OutputDebugStringW(msg);\
	OutputDebugStringW(_T(_line_tail_)); \
	ynOutputLogs(msg); \
	ynMessageBoxW(show, msg); \
}

#define ynGetHRMessageA(hr, str) \
{	\
	CHAR buff[1024] = ""; \
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,\
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buff, 1024, NULL); \
	str = buff; \
}

#define ynGetHRMessageW(hr, str) \
{	\
	WCHAR buff[1024] = _T(""); \
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,\
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buff, 1024, NULL); \
	str = buff; \
}


#ifdef _UNICODE
#define ynMessageBox		ynMessageBoxW
#define ynOutputMessage		ynOutputMessageW
#define	ynGetHRMessage		ynGetHRMessageW
#else
#define ynMessageBox		ynMessageBoxA 
#define ynOutputMessage		ynOutputMessageA
#define ynGetHRMessage		ynGetHRMessageA
#endif

//#define ynGetHRMessage(hr, buff) \
//	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,\
//				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buff, 1024, NULL); 

/*template<typename T, typename U>
void ynGetHRMessage(UINT hr, T& str) \
{	
	U buff[1024] = _T(""); 
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, hr,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buff, 1024, NULL); 
	str = buff; 
}*/




/////////////////////////////////////////////////////////////////////////////
//
//! \class Except
//! \brief 예나 / 엔진 / 예외 처리 클래스
//!
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
////////////////////////////////////////////////////////////////////////////////

class ynExcept
{
protected:
	//HRESULT m_hr; 
	wstring m_Msg  = _T("---");
	wstring m_File = _T("---");
	wstring m_Func = _T("---");
	UINT	m_Line = 0;

/*protected:
	virtual wstring _genMessage(wstring& what, TCHAR* msg, ...)
	{
		wstring mva; ynStrFmtV(mva, msg);
		wstring ffl = what;
		m_Msg = mva + _T("\n") + ffl;
		return m_Msg;
	}*/

public:
	ynExcept() = default;
	virtual ~ynExcept() = default;

	ynExcept(TCHAR* file, UINT line, TCHAR* func) : m_File(file), m_Func(func), m_Line(line)
	{
		m_Msg = ynVaStringW( _T("\n%s(%d) : %s\n"), file, line, func);
	}

	virtual wstring msg  () noexcept { return m_Msg;  }
	virtual wstring file () noexcept { return m_File; }
	virtual wstring func () noexcept { return m_Func; }
	virtual UINT    line () noexcept { return m_Line; }

	_NODISCARD virtual wstring what () noexcept { return msg();  }
	
	virtual int logw(BOOL show, const TCHAR* msg, ...)
	{
		wstring msgva; ynStrFmtV(msgva, msg);
		wstring errmsg = msgva + L"\n" + m_Msg;
		ynOutputMessage(show, errmsg.c_str());
		return YN_OK;
	}

	virtual int logw(BOOL show, Except& e)
	{
		return logw(show, e.what().c_str());
	}

	virtual int logw(BOOL show = TRUE)
	{
		ynOutputMessage(show, what().c_str());
		return YN_OK;
	}

};



/////////////////////////////////////////////////////////////////////////////
//
//! \class  ynDebugInfo
//! \brief  예나 / 엔진 / 디버깅 정보 클래스
//!
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
// 
/////////////////////////////////////////////////////////////////////////////

template<typename ... Args>
class ynDebugInfo : public ynExcept
{
protected:
	//추가 데이터는 여기에...

protected:
	wstring _genMessage(wstring& what, TCHAR* msg, Args... args)
	{
		wstring& mva = ynVaStringW(msg, args...);
		wstring& ffl = what;
		m_Msg = mva + _T("\n") + ffl;
		return m_Msg;
	}

public:
	ynDebugInfo() = delete;
	virtual ~ynDebugInfo() = default;
		
	ynDebugInfo(TCHAR* file, UINT line, TCHAR* func) : ynExcept(file, line, func) { }

	ynDebugInfo(ynExcept& e, TCHAR* msg, Args ... args) : ynExcept(e) 
	{ 
		_genMessage(e.what(), msg, args...); 
	}

	ynDebugInfo(TCHAR* file, UINT line, TCHAR* func, TCHAR* msg, Args ... args) : ynExcept(file, line, func) 
	{	
		_genMessage(what(), msg, args...); 
	}

	ynDebugInfo(TCHAR* msg, Args ... args) {	m_Msg = ynVaStringW(msg, args...); }
	 
	static ynDebugInfo trace(TCHAR* file, UINT line, TCHAR* func)
	{
		return ynDebugInfo<>(file, line, func);
 	}

};

#define ynDbg_file()          ynDebugInfo<>(__FILEW__, __LINE__, __FUNCTIONW__)
#define ynDbg_file2()         ynDebugInfo<>::trace(__FILEW__, __LINE__, __FUNCTIONW__)
#define ynDbg_trace(msg, ...) ynDebugInfo( ynDbg_file(), msg, __VA_ARGS__)
#define ynDbgTrace(msg, ...)  ynDebugInfo( ynDbg_file(), msg, __VA_ARGS__)
//#define ynDbg_va(msg, ...)  DebugInfo(__FILEW__, __LINE__, __FUNCTIONW__, msg, __VA_ARGS__)
 




/////////////////////////////////////////////////////////////////////////////
//
//! \class  ynError
//! \brief	예나 / 엔진 / 에러 처리 클래스.	
//!
//! \author 김기홍 / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//! \ingroup Yena
//
////////////////////////////////////////////////////////////////////////////////

class ynError : public ynExcept, public runtime_error
{
protected:
	HRESULT m_hr = S_YN_OK; 
	//wstring m_Msg;
	//wstring m_Fns;
public:
	static string  _tempa_;
	static wstring _tempw_;
	static wstring_convert<codecvt_utf8<wchar_t>> conv;
	//wstring_convert< codecvt_utf8<char32_t>, char32_t > conv;
	//wstring_convert< codecvt_utf16<wchar_t>, wchar_t  > conv;
public:
	ynError() = delete;
	//Error() = default;
	virtual ~ynError() = default;
	
	ynError(HRESULT hr, const WCHAR* msg) : runtime_error("--"), m_hr(hr) 
	{
		m_Func = msg;		
		m_Msg = ynStrHRW(hr) + L" : " + m_Func + L"\n";
	} 
	
	ynError(HRESULT hr, const char* msg) : runtime_error(ynStrHRA(hr)), m_hr(hr) 
	{
		wstring s0 = conv.from_bytes(runtime_ynError::what());
		m_Func = conv.from_bytes(msg);
		m_Msg  = s0 + L" : " + m_Func + L"\n";
	} 	 
	
	ynError(HRESULT hr, ynExcept& e) : runtime_error("--"), m_hr(hr)
	{
		m_Func = e.func();
		m_Msg  = ynStrHRW(hr) + L" : " + m_Func + L"\n" + e.what();
	}

	/*Error(HRESULT hr, Error& e) : runtime_ynError("--"), m_hr(hr)
	{
		m_Func = e.func();
		m_Msg  = ynStrHRW(hr) + L" : " + m_Func + L"\n" + e.what();
	}

	Error(Error& e) : runtime_ynError("--"), m_hr(e.hr())
	{
		//m_hr   = e.hr();
		m_File = e.file();
		m_Func = e.func();
		m_Line = e.line();
		m_Msg  = ynStrHRW(m_hr) + L" : " + m_Func + L"\n" + e.what();
	}*/

	ynError(HRESULT hr, TCHAR* file, UINT line, TCHAR* func, const TCHAR* msg, ...)
			: runtime_error("--"), ynExcept(file, line, func), m_hr(hr) 
	{
		m_Msg = strHR(hr) + _T(" : ") + m_Func + _T("\n");
		wstring mva; ynStrFmtV(mva, msg);
		wstring ffl; ynStrFmt(ffl, _T("\n%s(%d) : %s\n"), file, line, func);
		m_Msg += mva + _T("\n") + ffl;
	}

				virtual HRESULT	hr   () noexcept { return m_hr;  }
	_NODISCARD	virtual wstring	what () noexcept { return m_Msg; }
	//_NODISCARD virtual const WCHAR* what () noexcept { return m_Msg.c_str(); }

	//예외처리 테스트용.
	_SAMPLE_TEST static HRESULT test(int a, int b, TCHAR* msg)
	{
		return E_OUTOFMEMORY;
	}
	
	_NODISCARD	static inline const char* to_bytes(const wstring& ws)
	{
		_tempa_ = conv.to_bytes(ws.c_str());
		return _tempa_.c_str();
		//return conv.to_bytes(ws.c_str()).c_str();
	}

	virtual int logw(BOOL show, const WCHAR* msg, ...)
	{
		wstring msgva;  ynStrFmtVW(msgva, msg);
		wstring herr;   ynGetHRMessageW(hr(), herr);
		wstring errmsg; 
		ynStrFmt2W(errmsg, _T("%s : %s \n에러코드(0x%08X) : %s"), 
				 msgva.c_str(), what().c_str(), static_cast<UINT>(hr()), herr.c_str());
		ynOutputMessageW(show, errmsg.c_str());
		return YN_OK;
	}

	virtual int loga(BOOL show, const char* msg, ...)
	{
		string msgva;  ynStrFmtVA(msgva, msg);
		string herr;   ynGetHRMessageA(hr(), herr);
		string errmsg; 
		ynStrFmt2A(errmsg, "%s : %s \n에러코드(0x%08X) : %s", 
				 msgva.c_str(), to_bytes(what()), static_cast<UINT>(hr()), herr.c_str());
		//std::snprintf(errmsg.c_str()
		ynOutputMessageA(show, errmsg.c_str());
		return YN_OK;
	}

	virtual int logw(BOOL show, ynExcept& e)
	{
		return logw(show, e.what().c_str());
	}

	virtual int logw(BOOL show = TRUE)
	{
		ynOutputMessage(show, what().c_str());
		return YN_OK;
	}

public:
	//======================================================================
	// 에러 출력용 정적 인터페이스 : 구형 호환성 유지.
	//======================================================================
	//int ynError(BOOL bBox, TCHAR* msg, ...);

	static int logw(BOOL bMBox, HRESULT hr, const TCHAR* msg, ...)
	{
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring herr;   ynGetHRMessage(hr, herr);
		wstring errmsg; 
		ynStrFmt2(errmsg, _T("%s : \n에러코드(0x%08X) : %s"), 
				msgva.c_str(), static_cast<UINT>(hr), herr.c_str());
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}


	static int logw(BOOL bMBox, ynError& e, const TCHAR* msg, ...)
	{
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring herr;   ynGetHRMessage(e.hr(), herr);
		wstring errmsg; 
		ynStrFmt2(errmsg, _T("%s : %s \n에러코드(0x%08X) : %s"), 
				 msgva.c_str(), e.what().c_str(), static_cast<UINT>(e.hr()), herr.c_str());
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}


	/*static int logw(BOOL bMBox, exception& e, const TCHAR* msg, ...)
	{
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring& herr = conv.from_bytes(e.what());  //ynGetHRMessage(e.hr(), herr);
		wstring errmsg; 
		ynStrFmt2(errmsg, _T("%s : %s \n에러코드(0x%08X) : %s"), 
		  		msgva.c_str(), herr.c_str(), static_cast<UINT>(0), herr.c_str());
		ynOutputMessage(bMBox, errmsg.c_str());
		//ynOutputMessage(bMBox, "Error", errmsg.c_str());
		return YN_OK;
	}*/


	static int logw(TCHAR* file, UINT line, TCHAR* func, BOOL bMBox, 
					HRESULT hr, const TCHAR* msg, ...)
	{
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring herr;   ynGetHRMessage(hr, herr);
		wstring errmsg; 
		ynStrFmt2(errmsg,  _T("%s \n에러코드(0x%X) : %s \nFile=%s (%d)\nFunc=%s\n\n"), 
				msgva.c_str(), static_cast<UINT>(hr), herr.c_str(), file, line, func);
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}


	static int logw(BOOL bMBox, const TCHAR* msg, HRESULT hr,  //ID3DBlob* pErr, 
						const CHAR* err, UINT size, TCHAR* file, CHAR* entry, CHAR* sm)
	{
		wstring& entw = conv.from_bytes(entry);
		wstring& smw  = conv.from_bytes(sm);
		wstring& errw = conv.from_bytes(err);
		wstring herr = _T("아래의 오류를 확인하십시오.");
		wstring errmsg; 
		ynStrFmt2(errmsg,  _T("%s \nFile=%s  Entry=%s  Target=%s  \n에러코드(0x%08X) : %s \n\n%s"),
				msg, file, entw.c_str(), smw.c_str(), static_cast<UINT>(hr), herr.c_str(), errw.c_str());
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}


	static int logw(BOOL bMBox, TCHAR* file, UINT line, TCHAR* func, HRESULT hr,  //ID3DBlob* pErr, 
						const CHAR* err, UINT size, const TCHAR* msg, ...)
	{
		wstring& errw = conv.from_bytes(err);
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring herr;   ynGetHRMessage(hr, herr);
		wstring errmsg; 
		ynStrFmt2(errmsg,  _T("%s \n에러코드(0x%X) : %s \nError=%s \nFile=%s (%d)\nFunc=%s\n\n"),
				 msgva.c_str(), static_cast<UINT>(hr), herr.c_str(), errw.c_str(), file, line, func);
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}
	 

	static int logw2(BOOL bMBox, TCHAR* file, UINT line, TCHAR* func, HRESULT hr,  //ID3DBlob* pErr, 
						const CHAR* err, UINT size, const TCHAR* msg, ...)
	{
		wstring& errw = conv.from_bytes(err);
		wstring msgva;  ynStrFmtV(msgva, msg);
		wstring herr;   ynGetHRMessage(hr, herr);
		wstring errmsg; 
		ynStrFmt2(errmsg,  _T("%s \n에러코드(0x%X) : %s \nError=%s \nFile=%s (%d)\nFunc=%s\n\n"),
				 msgva.c_str(), static_cast<UINT>(hr), herr.c_str(), errw.c_str(), file, line, func);
		ynOutputMessage(bMBox, errmsg.c_str());
		return YN_OK;
	}


}; // end of class Error


_YNGLOBAL  std::string   ynError::_tempa_;
_YNGLOBAL  std::wstring  ynError::_tempw_;
_YNGLOBAL  std::wstring_convert<codecvt_utf8<wchar_t>>  ynError::conv;




/////////////////////////////////////////////////////////////////////////////
//
//! 에러 메세지 출력 매크로
//
// ex) ynError(e, _T("D3D 구성 실패"));
// ex) ynError(e, _T("D3D 구성 실패 : %d %s %s"), 100, _T("DebugeConsole 테스트!"), _T("4.5.2@3-1"));
// ex) ynErrorste(e, _T("폰트 생성 실패 : \nFile=%s"), filename);	
//
/////////////////////////////////////////////////////////////////////////////

//! \def ynError(e, msg, ...)
//! \brief 에러 메세지 \a msg 와 함께 예외객체 및 디버깅 정보를 출력한다.
//! \param e   예외처리 객체
//! \param msg 에러 메세지, 가변인자 처리 가능.
// 
#define ynError(e, msg, ...) 		ynError::logw( TRUE, e, msg, __VA_ARGS__ )
#define ynErrorste(e, msg, ...)		ynError::logw( TRUE, ynError(YN_FAIL, dbgTrace( _T("Err=%s"), strconvwp(e.what()))), msg, __VA_ARGS__ )
//#define ynErrork(e, msg, ...)		ynDebugInfo& di = dbgTrace( _T("%s"), strconv(e.what()) ) ; Error::logw( TRUE, di, msg, __VA_ARGS__ ) 
#define ynError0(hr, msg, ...)		ynError::logw( TRUE, hr, msg, __VA_ARGS__ )
#define ynError1(hr, msg, ...)		ynError::logw( __FILEW__, __LINE__, __FUNCTIONW__, TRUE, hr, msg, __VA_ARGS__ ) 
#define ynError2(hr, err, msg, ...) \
	ynError::logw2( TRUE, __FILEW__, __LINE__, __FUNCTIONW__, hr, (CHAR*)err->GetBufferPointer(), (UINT)err->GetBufferSize(), msg, __VA_ARGS__ )
	//Error::logw( TRUE, __FILEW__, __LINE__, __FUNCTIONW__, hr, (CHAR*)err->GetBufferPointer(), (UINT)err->GetBufferSize(), msg, __VA_ARGS__ )
#define ynErrorW(mb, msg, hr, err, file, entry, sm) \
	ynError::logw( mb, msg, hr, (CHAR*)err->GetBufferPointer(), (UINT)err->GetBufferSize(), file, entry, sm)
//#define ynError(hr, msg, pBlob)  ynErrorW( TRUE, hr, msg, pBlob)

#define ynToString(v)  _T(#v)
#define ynToStringW(v)  L""#v
#define ynToStringA(v)  #v

//! 코드 테스트 및 예외처리  출력 매크로. 
// ex) ynChkFailed( creteDevice( .... ) );
// ex) ynChkFailed( Error::test(10, 20, _T("테스트!")) ); 
//
#define ynChkFailed(fn)		{ HRESULT hr = fn; if(YN_FAILED(hr)){ throw ynError(hr, ynDbgTrace(ynToString(fn))); }}
#define ynChkFailed1(fn)	{ HRESULT hr = fn; if(YN_FAILED(hr)){ throw ynError(hr, ynToString(fn)); }}		
#define ynChkFailed2(fn)	{ if((fn) == NULL){ throw ynError(GetLastError(), ynDbgTrace(ynToString(fn))); }}
//#define ynChkFailed2(fn)	{ { throw Error(hr, dbgTrace(ynToString(fn))); }}
#define ynCheckFail			ynChkFailed
#define ynCheckNull			ynChkFailed2
//#define ynThrowFail		ynChkFailed
//#define ynThrowNull		ynChkFailed2

//#define ynThrowFailed(fn)			{ HRESULT hr = fn; if(YN_FAILED(hr)){ throw Error(hr, ynToString(fn)); }}
//#define ynThrowErr(hr, msg)		{ throw ynError(hr, msg); }
//#define ynThrowErr(hr, msg, ...)	{ throw ynError(hr, msg, __VA_ARGS__); }
//#define ynChkFailed(fn)			{ hr = fn; if(YN_FAILED(hr)){ throw ynError(hr, ynToStringA(fn)); }}


} //end of namespace YENA



/*************** end of file : "ynError.h" *****************************************/
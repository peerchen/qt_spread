#pragma once

struct TipsOrderInfo;

class CGlobalMgr
{
public:
	CGlobalMgr(void);
public:
	~CGlobalMgr(void);

	// ���һ����ʾ
	bool AddTips( const TipsOrderInfo &stTips ); 
};

extern CGlobalMgr g_GlobalMgr;

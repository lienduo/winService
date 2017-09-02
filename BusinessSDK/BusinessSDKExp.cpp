/////////////////////////////////////////////////////////////////////////////
// Name:        BusinessSDK.cpp
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#define BusinessSDK_OP_API extern "C" _declspec(dllexport)
#include "BusinessSDKExp.h"

BusinessSDK_OP_API int BusSdk_Start()
{
	return -1;
}
BusinessSDK_OP_API int BusSdk_Stop()
{
	return 0;
}
BusinessSDK_OP_API int BusSdk_Pause()
{
	return 0;
}
BusinessSDK_OP_API int BusSdk_Continue()
{
	return 0;
}
BusinessSDK_OP_API int BusSdk_Status()
{
	return 0;
}
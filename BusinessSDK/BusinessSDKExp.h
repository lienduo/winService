/////////////////////////////////////////////////////////////////////////////
// Name:        BusinessSDK.h
// Purpose:     
// Author:      Center
// Modified by: 
// Created:     
// RCS-ID:      
// Copyright:   CodeCenter
// Licence:     
/////////////////////////////////////////////////////////////////////////////
#pragma once
#ifdef BusinessSDK_OP_API
#else
#pragma comment(lib,"BusinessSDK.lib")
#define BusinessSDK_OP_API extern "C" _declspec(dllimport)
#endif

BusinessSDK_OP_API int BusSdk_Start();
BusinessSDK_OP_API int BusSdk_Stop();
BusinessSDK_OP_API int BusSdk_Pause();
BusinessSDK_OP_API int BusSdk_Continue();
BusinessSDK_OP_API int BusSdk_Status();
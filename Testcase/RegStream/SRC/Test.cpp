/***************************************************************************
//
// TEST.CPP
//
// TAPI Service provider for TSP++ version 3.00
// Main TAPI Service Provider shell
//
// Copyright (C) 1999 Test
// All rights reserved
//
// Generated by the TSPWizard (C) JulMar Technology, Inc.
// 
/***************************************************************************/

/*-------------------------------------------------------------------------------*/
// INCLUDE FILES
/*-------------------------------------------------------------------------------*/
#include "stdafx.h"
#include "Test.h"

/*-------------------------------------------------------------------------------*/
// CONSTANTS AND GLOBALS
/*-------------------------------------------------------------------------------*/
CTestServiceProvider theSP;

/*-------------------------------------------------------------------------------*/
// RTTI overrides of TSP++ objects
/*-------------------------------------------------------------------------------*/
DECLARE_TSPI_OVERRIDE(CTestDevice);
DECLARE_TSPI_OVERRIDE(CTestLine);
DECLARE_TSPI_OVERRIDE(CTestAddress);

/*****************************************************************************
** Procedure:  CTestServiceProvider::CTestServiceProvider
**
** Arguments:  void
**
** Returns:    void
**
** Description:  This is the constructor for the provider object.  It
**               is responsible for initializing the UI.DLL name and the
**               provider manufacturer names.  In additional, any overrides
**               of class objects should be performed here.
**
*****************************************************************************/
CTestServiceProvider::CTestServiceProvider() : 
	CServiceProvider(_T("TestUI.DLL"),		// Name of UI DLL
					 _T("Provider"),
					 TAPIVER_20)
{   
	// Setup our line device and phone device object override.
	SetRuntimeObjects (
		"CTestDevice",	// Device override 
		"CTestLine",		// Line override
		"CTestAddress",		// Address override
		NULL,						// Call override
		NULL,						// Conference call override
		NULL);						// Phone override

#ifdef _DEBUG
	// Turn on tracing level for debug builds -- see SPLIB.H for
	// additional tracing flags.
	SetTraceLevel(TRC_API |			// TSPI_xxx entrypoints (requires JTTSPTRC.dll)
				  TRC_DUMP |		// TSPI buffers (requires JTTSPTRC.dll)
				  TRC_MIN |			// Basic tracing inside library
				  TRC_WARNINGS |	// Warnings from TSP++
				  TRC_STATS |		// Statistics on calls/addresses/lines
				  TRC_OBJECTS |		// Object creation/destruction
				  TRC_THREADS);		// Thread creation/destruction
#endif

}// CTestServiceProvider::CTestServiceProvider

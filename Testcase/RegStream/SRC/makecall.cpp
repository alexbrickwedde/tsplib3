/***************************************************************************
//
// MAKECALL.CPP
//
// TAPI Service provider for TSP++ version 3.00
// lineMakeCall and lineDial management
//
// Copyright (C) 1999 Test
// All rights reserved
//
// Generated by the TSPWizard (C) JulMar Technology, Inc.
// 
/***************************************************************************/

/*----------------------------------------------------------------------------
	INCLUDE FILES
-----------------------------------------------------------------------------*/
#include "stdafx.h"
#include "Test.h"

/*****************************************************************************
** Procedure:  CTestLine::OnMakeCall
**
** Arguments: 'pReq' - Request object representing this MAKECALL event 
**            'lpBuff' - The event block pointer
**
** Returns:    void
**
** Description:  This function manages the TSPI_lineMakeCall processing
**               for this service provider. 
**
*****************************************************************************/
bool CTestLine::OnMakeCall(RTMakeCall* pRequest, LPCVOID lpBuff)
{
	// Cast the input opaque pointer back to an event block
	const TEvent* pEvent = static_cast<const TEvent*>(lpBuff);
	CTSPICallAppearance* pCall = pRequest->GetCallInfo();
	DIALINFO* pAddress = (pRequest->GetCount() > 0) ? pRequest->GetDialableNumber(0) : NULL;

	// If we are in the initial state (i.e. this request has not been processed
	// before by any other thread). Then move the packet to the waiting state so 
	// other threads will not interfere with other events or timers.  This is 
	// guaranteed to be thread-safe and atomic.
	if (pRequest->EnterState(STATE_INITIAL, STATE_IGNORE))
	{
		// TODO: Examine the dialing string and convert TAPI special indicator
		// characters to the appropriate information to send to the device. The
		// supported characters are:
		//
		// ! - Indicates that a hookflash (one-half second onhook, followed by one-half 
		// second offhook before continuing) is to be inserted in the dial string.
		//
		// t/T - Indicates that tone (DTMF) dialing is to be used for the digits 
		// following it
		//
		// p/P - Indicates that pulse dialing is to be used for the digits following it.
		// , - Indicates that dialing is to be paused. The duration of a pause is 
		// specified by GetLineDevCaps()->DefaultDialParams.dwDialPause. 
		// Multiple commas can be used to provide longer pauses
		// TODO: Send a command to place a call on this line

		// Transition the waiting state - waiting for a hardware response
		pRequest->SetState(STATE_WAITING);
	}

	// If we are in the waiting stage (2) then see if we received an event from the
	// switch (vs. an interval timer) and if that event was an ACK/NAK in response
	// to the command we issued.
	else if (pRequest->GetState() == STATE_WAITING && lpBuff != NULL)
	{
		// TODO: Check the return code from the PBX and fail the request or
		// complete it with a zero return code

		bool fError = false;
		if (fError == false)
		{
			// Complete this request so that TAPI will forward on callstate information
			// to applications. Make sure to tell TSP++ to not delete the request yet
			// by using the last parameter
			CompleteRequest(pRequest, 0, true, false);

			// Because the request is "complete" in TAPI's eyes, we can adjust the
			// call state and change call information (assigned trunk, caller-id, etc.)
			// Change the call state to dialtone.
			pCall->SetCallState(LINECALLSTATE_DIALTONE, 
						LINEDIALTONEMODE_NORMAL, LINEMEDIAMODE_INTERACTIVEVOICE);

			// TODO: Associate the call-id from the hadrware with the call object so we
			// can find it later.
			// pCall->SetCallID(dwCallID);

			// TODO: Add any additional information to the call which was received from
			// the hardware. Another option is to do this in the unsolicitied handler
			// found in UNSOLICITED.CPP - this is especially helpful if the event can
			// be recieved independant of a call being placed by the TSP (i.e. external
			// stimulus
			//
			// pCall->SetTrunk (...) etc.

			// Transition to the dialing stage and the the proceeding (waiting for ringback) state
			pCall->SetCallState(LINECALLSTATE_DIALING);
			pCall->SetCallState(LINECALLSTATE_PROCEEDING);

			// Finally, destroy the request from our list now that we have
			// setup the call appearance. This releases the address information.
			CompleteRequest(pRequest, 0);
		}
		return true;
	}

	// Check to see if our request has exceeded the limit for processing.  If 
	// so, tell TAPI that the request failed and delete the request.
	if (pRequest->GetState() == STATE_WAITING &&
		(pRequest->GetStateTime()+REQUEST_TIMEOUT) < GetTickCount())
		CompleteRequest(pRequest, LINEERR_OPERATIONFAILED);

	// Let the request fall through to the unsolicited handler
	return false;

}// CTestLine::OnMakeCall

/*****************************************************************************
** Procedure:  CTestLine::OnDial
**
** Arguments: 'pReq' - Request object representing this DIAL event 
**            'lpBuff' - Our CEventBlock* pointer
**
** Returns:    void
**
** Description:  This function manages the TSPI_lineDial processing
**               for this service provider.
**
*****************************************************************************/
bool CTestLine::OnDial(RTDial* pRequest, LPCVOID lpBuff)
{
	// Cast the input opaque pointer back to an event block
	const TEvent* pEvent = static_cast<const TEvent*>(lpBuff);
	CTSPICallAppearance* pCall = pRequest->GetCallInfo();
	DIALINFO* pAddress = (pRequest->GetCount() > 0) ? pRequest->GetDialableNumber(0) : NULL;
	
	// If we are in the initial state (i.e. this request has not been processed
	// before by any other thread). Then move the packet to the waiting state so 
	// other threads will not interfere with other events or timers.  This is 
	// guaranteed to be thread-safe and atomic.
	if (pRequest->EnterState(STATE_INITIAL, STATE_IGNORE))
	{
		// TODO: Examine the dialing string and convert TAPI special indicator
		// characters to the appropriate information to send to the device. The
		// supported characters are:
		//
		// ! - Indicates that a hookflash (one-half second onhook, followed by one-half 
		// second offhook before continuing) is to be inserted in the dial string.
		//
		// t/T - Indicates that tone (DTMF) dialing is to be used for the digits 
		// following it
		//
		// p/P - Indicates that pulse dialing is to be used for the digits following it.
		// , - Indicates that dialing is to be paused. The duration of a pause is 
		// specified by GetLineDevCaps()->DefaultDialParams.dwDialPause. 
		// Multiple commas can be used to provide longer pauses
		// TODO: Send a command to place a call on this line

		// Transition the waiting state - waiting for a hardware response
		pRequest->SetState(STATE_WAITING);
	}

	// If we are in the waiting stage (2) then see if we received an event from the
	// switch (vs. an interval timer) and if that event was an ACK/NAK in response
	// to the command we issued.
	else if (pRequest->GetState() == STATE_WAITING && lpBuff != NULL)
	{
		// TODO: Check the return code from the PBX and fail the request or
		// complete it with a zero return code

		bool fError = false;
		if (fError == false)
		{
			// Complete this request so that TAPI will forward on callstate information
			// to applications. Make sure to tell TSP++ to not delete the request yet
			// by using the last parameter
			CompleteRequest(pRequest, 0, true, false);

			// Because the request is "complete" in TAPI's eyes, we can adjust the
			// call state and change call information (assigned trunk, caller-id, etc.)
			// Change the call state to dialtone.
			pCall->SetCallState(LINECALLSTATE_DIALTONE, 
						LINEDIALTONEMODE_NORMAL, LINEMEDIAMODE_INTERACTIVEVOICE);

			// TODO: Associate the call-id from the hadrware with the call object so we
			// can find it later.
			// pCall->SetCallID(dwCallID);

			// TODO: Add any additional information to the call which was received from
			// the hardware. Another option is to do this in the unsolicitied handler
			// found in UNSOLICITED.CPP - this is especially helpful if the event can
			// be recieved independant of a call being placed by the TSP (i.e. external
			// stimulus
			//
			// pCall->SetTrunk (...) etc.

			// Transition to the dialing stage and the the proceeding (waiting for ringback) state
			pCall->SetCallState(LINECALLSTATE_DIALING);
			pCall->SetCallState(LINECALLSTATE_PROCEEDING);

			// Finally, destroy the request from our list now that we have
			// setup the call appearance. This releases the address information.
			CompleteRequest(pRequest, 0);
		}
		return true;
	}

	// Check to see if our request has exceeded the limit for processing.  If 
	// so, tell TAPI that the request failed and delete the request.
	if (pRequest->GetState() == STATE_WAITING && 
		(pRequest->GetStateTime()+REQUEST_TIMEOUT) < GetTickCount())
		CompleteRequest(pRequest, LINEERR_OPERATIONFAILED);

	// Let the request fall through to the unsolicited handler
	return false;

}// CTestLine::OnDial

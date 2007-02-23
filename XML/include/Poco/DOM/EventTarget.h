//
// EventTarget.h
//
// $Id: //poco/Main/XML/include/Poco/DOM/EventTarget.h#2 $
//
// Library: XML
// Package: DOM
// Module:  DOMEvents
//
// Definition of the DOM EventTarget interface.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef DOM_EventTarget_INCLUDED
#define DOM_EventTarget_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/DOM/DOMObject.h"
#include "Poco/XML/XMLString.h"


namespace Poco {
namespace XML {


class EventListener;
class Event;


class XML_API EventTarget: public DOMObject
	/// The EventTarget interface is implemented by all Nodes in an implementation
	/// which supports the DOM Event Model. Therefore, this interface can be obtained
	/// by using binding-specific casting methods on an instance of the Node interface.
	/// The interface allows registration and removal of EventListeners on an EventTarget
	/// and dispatch of events to that EventTarget.
{
public:
	virtual void addEventListener(const XMLString& type, EventListener* listener, bool useCapture) = 0;
		/// This method allows the registration of event listeners on 
		/// the event target. If an EventListener is added to an
		/// EventTarget while it is processing an event, it will not 
		/// be triggered by the current actions but may be triggered
		/// during a later stage of event flow, such as the bubbling phase.
		/// If multiple identical EventListeners are registered on the same 
		/// EventTarget with the same parameters the duplicate instances are 
		/// discarded. They do not cause the EventListener to be called twice and since they are
		/// discarded they do not need to be removed with the removeEventListener method. 	
	
	virtual void removeEventListener(const XMLString& type, EventListener* listener, bool useCapture) = 0;
		/// This method allows the removal of event listeners from the event 
		/// target. If an EventListener is removed from an EventTarget while it is 
		/// processing an event, it will not be triggered by the current actions. 
		/// EventListeners can never be invoked after being removed.
		/// Calling removeEventListener with arguments which do not identify 
		/// any currently registered EventListener on the EventTarget has no effect. 

	virtual bool dispatchEvent(Event* evt) = 0;
		/// This method allows the dispatch of events into the implementations 
		/// event model. Events dispatched in this manner will have the same capturing and 
		/// bubbling behavior as events dispatched directly by the
		/// implementation. The target of the event is the EventTarget on 
		/// which dispatchEvent is called. 

protected:
	virtual ~EventTarget();
};


} } // namespace Poco::XML


#endif // DOM_EventTarget_INCLUDED

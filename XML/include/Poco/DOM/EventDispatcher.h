//
// EventDispatcher.h
//
// $Id: //poco/Main/XML/include/Poco/DOM/EventDispatcher.h#2 $
//
// Library: XML
// Package: DOM
// Module:  DOMEvents
//
// Definition of the EventDispatcher class.
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


#ifndef DOM_EventDispatcher_INCLUDED
#define DOM_EventDispatcher_INCLUDED


#include "Poco/XML/XML.h"
#include "Poco/XML/XMLString.h"
#include <list>


namespace Poco {
namespace XML {


class Event;
class EventListener;


class XML_API EventDispatcher
	/// This helper class manages event listener subscriptions
	/// and event dispatching for AbstractNode.
	///
	/// The EventListener list is managed in such a way that
	/// event listeners can be added and removed even
	/// from within an EventListener, while events are being
	/// dispatched.
{
public:
	EventDispatcher();
		/// Creates the EventDispatcher.
		
	~EventDispatcher();
		/// Destroys the EventDispatcher.
		
	void addEventListener(const XMLString& type, EventListener* listener, bool useCapture);
		/// Adds an EventListener to the internal list.
		
	void removeEventListener(const XMLString& type, EventListener* listener, bool useCapture);
		/// Removes an EventListener from the internal list.
		///
		/// If a dispatch is currently in progress, the list
		/// entry is only marked for deletion.
		/// If no dispatch is currently in progress, all EventListeners
		/// marked for deletion are removed from the list.

	void dispatchEvent(Event* evt);
		/// Dispatches the event.
		///
		/// Also removes all EventListeners marked for deletion from the 
		/// event dispatcher list.
		
	void captureEvent(Event* evt);
		/// Dispatches the event in its capturing phase.
		///
		/// Also removes all EventListeners marked for deletion from the 
		/// event dispatcher list.
		
	void bubbleEvent(Event* evt);
		/// Dispatches the event in its bubbling phase.
		///
		/// Also removes all EventListeners marked for deletion from the 
		/// event dispatcher list.

private:
	struct EventListenerItem
	{
		XMLString      type;
		EventListener* pListener;
		bool           useCapture;
	};

	typedef std::list<EventListenerItem> EventListenerList;
	
	int               _inDispatch;
	EventListenerList _listeners;
};


} } // namespace Poco::XML


#endif // DOM_EventDispatcher_INCLUDED

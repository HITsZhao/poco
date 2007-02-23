//
// ElementsByTagNameList.cpp
//
// $Id: //poco/Main/XML/src/ElementsByTagNameList.cpp#10 $
//
// Library: XML
// Package: DOM
// Module:  DOM
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


#include "Poco/DOM/ElementsByTagNameList.h"
#include "Poco/DOM/Node.h"
#include "Poco/DOM/Document.h"


namespace Poco {
namespace XML {


ElementsByTagNameList::ElementsByTagNameList(const Node* pParent, const XMLString& name):
	_pParent(pParent),
	_name(name),
	_count(0)
{
	poco_check_ptr (pParent);
	
	_pParent->duplicate();
}


ElementsByTagNameList::~ElementsByTagNameList()
{
	_pParent->release();
}


Node* ElementsByTagNameList::item(unsigned long index) const
{
	_count = 0;
	return find(_pParent, index);
}


unsigned long ElementsByTagNameList::length() const
{
	_count = 0;
	find(_pParent, ULONG_MAX);
	return _count;
}


Node* ElementsByTagNameList::find(const Node* pParent, unsigned long index) const
{
	static const XMLString asterisk = toXMLString("*");

	if (!pParent) return 0;

	// preorder search
	Node* pCur = pParent->firstChild();
	while (pCur)
	{
		if (pCur->nodeType() == Node::ELEMENT_NODE && (_name == asterisk || pCur->nodeName() == _name))
		{
			if (_count == index) return pCur;
			_count++;
		}
		Node* pNode = find(pCur, index);
		if (pNode) return pNode;
		pCur = pCur->nextSibling();
	}
	return pCur;
}


void ElementsByTagNameList::autoRelease()
{
	_pParent->ownerDocument()->autoReleasePool().add(this);
}


ElementsByTagNameListNS::ElementsByTagNameListNS(const Node* pParent, const XMLString& namespaceURI, const XMLString& localName):
	_pParent(pParent),
	_localName(localName),
	_namespaceURI(namespaceURI),
	_count(0)
{
	poco_check_ptr (pParent);
	
	_pParent->duplicate();
}



ElementsByTagNameListNS::~ElementsByTagNameListNS()
{
	_pParent->release();
}


Node* ElementsByTagNameListNS::item(unsigned long index) const
{
	_count = 0;
	return find(_pParent, index);
}


unsigned long ElementsByTagNameListNS::length() const
{
	_count = 0;
	find(_pParent, ULONG_MAX);
	return _count;
}


Node* ElementsByTagNameListNS::find(const Node* pParent, unsigned long index) const
{
	static const XMLString asterisk = toXMLString("*");

	if (!pParent) return 0;

	// preorder search
	Node* pCur = pParent->firstChild();
	while (pCur)
	{
		if (pCur->nodeType() == Node::ELEMENT_NODE && (_localName == asterisk || pCur->localName() == _localName) && (_namespaceURI == asterisk || pCur->namespaceURI() == _namespaceURI))
		{
			if (_count == index) return pCur;
			_count++;
		}
		Node* pNode = find(pCur, index);
		if (pNode) return pNode;
		pCur = pCur->nextSibling();
	}
	return pCur;
}


void ElementsByTagNameListNS::autoRelease()
{
	_pParent->ownerDocument()->autoReleasePool().add(this);
}


} } // namespace Poco::XML

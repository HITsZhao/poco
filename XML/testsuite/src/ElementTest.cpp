//
// ElementTest.cpp
//
// $Id: //poco/Main/XML/testsuite/src/ElementTest.cpp#9 $
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


#include "ElementTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Attr.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/AutoPtr.h"


using Poco::XML::Element;
using Poco::XML::Document;
using Poco::XML::Attr;
using Poco::XML::Text;
using Poco::XML::Node;
using Poco::XML::NamedNodeMap;
using Poco::XML::NodeList;
using Poco::XML::AutoPtr;
using Poco::XML::XMLString;


ElementTest::ElementTest(const std::string& name): CppUnit::TestCase(name)
{
}


ElementTest::~ElementTest()
{
}


void ElementTest::testAttributes()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pElem = pDoc->createElement("elem");
	
	assert (!pElem->hasAttributes());

	pElem->setAttribute("a1", "v1");
	assert (pElem->hasAttributes());
	
	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "v1");
	
	Attr* pAttr1 = pElem->getAttributeNode("a1");
	assert (pAttr1 != 0);
	assert (pAttr1->name() == "a1");
	assert (pAttr1->nodeName() == "a1");
	assert (pAttr1->value() == "v1");
	assert (pAttr1->nodeValue() == "v1");
	assert (pAttr1->ownerElement() == pElem);
	assert (pAttr1->ownerDocument() == pDoc);
	assert (pAttr1->innerText() == "v1");
	
	assert (pAttr1->previousSibling() == 0);
	assert (pAttr1->nextSibling() == 0);
	
	pAttr1->setValue("V1");
	assert (pElem->getAttribute("a1") == "V1");
	
	pElem->setAttribute("a2", "v2");
	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "V1");
	assert (pElem->hasAttribute("a2"));
	assert (pElem->getAttribute("a2") == "v2");
	
	Attr* pAttr2 = pElem->getAttributeNode("a2");
	assert (pAttr2 != 0);
	assert (pAttr2->name() == "a2");
	assert (pAttr2->value() == "v2");
	assert (pAttr2->ownerElement() == pElem);

	assert (pAttr1->previousSibling() == 0);
	assert (pAttr1->nextSibling() == pAttr2);
	assert (pAttr2->previousSibling() == pAttr1);
	assert (pAttr2->nextSibling() == 0);

	Attr* pAttr3 = pElem->getAttributeNode("a3");
	assert (pAttr3 == 0);

	pAttr3 = pDoc->createAttribute("a3");
	pAttr3->setValue("v3");
	pElem->setAttributeNode(pAttr3);
	pAttr3->release();
	
	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "V1");
	assert (pElem->hasAttribute("a2"));
	assert (pElem->getAttribute("a2") == "v2");
	assert (pElem->hasAttribute("a3"));
	assert (pElem->getAttribute("a3") == "v3");

	assert (pAttr1->previousSibling() == 0);
	assert (pAttr1->nextSibling() == pAttr2);
	assert (pAttr2->previousSibling() == pAttr1);
	assert (pAttr2->nextSibling() == pAttr3);
	assert (pAttr3->previousSibling() == pAttr2);
	assert (pAttr3->nextSibling() == 0);
	
	pAttr2 = pDoc->createAttribute("a2");
	pAttr2->setValue("V2");
	pElem->setAttributeNode(pAttr2);
	pAttr2->release();

	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "V1");
	assert (pElem->hasAttribute("a2"));
	assert (pElem->getAttribute("a2") == "V2");
	assert (pElem->hasAttribute("a3"));
	assert (pElem->getAttribute("a3") == "v3");
	
	pAttr1 = pDoc->createAttribute("a1");
	pAttr1->setValue("v1");
	pElem->setAttributeNode(pAttr1);
	pAttr1->release();
	
	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "v1");
	assert (pElem->hasAttribute("a2"));
	assert (pElem->getAttribute("a2") == "V2");
	assert (pElem->hasAttribute("a3"));
	assert (pElem->getAttribute("a3") == "v3");

	pAttr3 = pDoc->createAttribute("a3");
	pAttr3->setValue("V3");
	pElem->setAttributeNode(pAttr3);
	pAttr3->release();

	assert (pElem->hasAttribute("a1"));
	assert (pElem->getAttribute("a1") == "v1");
	assert (pElem->hasAttribute("a2"));
	assert (pElem->getAttribute("a2") == "V2");
	assert (pElem->hasAttribute("a3"));
	assert (pElem->getAttribute("a3") == "V3");
	
	pElem->removeAttributeNode(pAttr3);
	assert (!pElem->hasAttribute("a3"));
	
	pElem->removeAttribute("a1");
	assert (!pElem->hasAttribute("a1"));
	
	pElem->removeAttribute("a2");
	assert (!pElem->hasAttribute("a2"));
	
	assert (!pElem->hasAttributes());
}


void ElementTest::testAttributesNS()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pElem = pDoc->createElementNS("urn:ns1", "p:elem");
	
	assert (pElem->namespaceURI() == "urn:ns1");
	assert (pElem->prefix() == "p");
	assert (pElem->tagName() == "p:elem");
	assert (pElem->localName() == "elem");
	
	assert (!pElem->hasAttributes());

	pElem->setAttributeNS("urn:ns1", "a1", "v1");
	assert (pElem->hasAttributes());
	
	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "v1");
	
	Attr* pAttr1 = pElem->getAttributeNodeNS("urn:ns1", "a1");
	assert (pAttr1 != 0);
	assert (pAttr1->name() == "a1");
	assert (pAttr1->namespaceURI() == "urn:ns1");
	assert (pAttr1->prefix().empty());
	assert (pAttr1->localName() == "a1");
	assert (pAttr1->nodeName() == "a1");
	assert (pAttr1->value() == "v1");
	assert (pAttr1->nodeValue() == "v1");
	assert (pAttr1->ownerElement() == pElem);
	
	pAttr1->setValue("V1");
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "V1");
	
	pElem->setAttributeNS("urn:ns1", "a2", "v2");
	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "V1");
	assert (pElem->hasAttributeNS("urn:ns1", "a2"));
	assert (pElem->getAttributeNS("urn:ns1", "a2") == "v2");
	
	Attr* pAttr2 = pElem->getAttributeNodeNS("urn:ns1", "a2");
	assert (pAttr2 != 0);
	assert (pAttr2->name() == "a2");
	assert (pAttr2->namespaceURI() == "urn:ns1");
	assert (pAttr2->prefix().empty());
	assert (pAttr2->localName() == "a2");
	assert (pAttr2->value() == "v2");
	assert (pAttr2->ownerElement() == pElem);

	Attr* pAttr3 = pElem->getAttributeNodeNS("urn:ns2", "p:a3");
	assert (pAttr3 == 0);

	pAttr3 = pDoc->createAttributeNS("urn:ns2", "p:a3");
	pAttr3->setValue("v3");
	pElem->setAttributeNodeNS(pAttr3);
	pAttr3->release();
	
	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "V1");
	assert (pElem->hasAttributeNS("urn:ns1", "a2"));
	assert (pElem->getAttributeNS("urn:ns1", "a2") == "v2");
	assert (pElem->hasAttributeNS("urn:ns2", "a3"));
	assert (pElem->getAttributeNS("urn:ns2", "a3") == "v3");
	
	pAttr2 = pDoc->createAttributeNS("urn:ns1", "a2");
	pAttr2->setValue("V2");
	pElem->setAttributeNodeNS(pAttr2);
	pAttr2->release();

	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "V1");
	assert (pElem->hasAttributeNS("urn:ns1", "a2"));
	assert (pElem->getAttributeNS("urn:ns1", "a2") == "V2");
	assert (pElem->hasAttributeNS("urn:ns2", "a3"));
	assert (pElem->getAttributeNS("urn:ns2", "a3") == "v3");
	
	pAttr1 = pDoc->createAttributeNS("urn:ns1", "a1");
	pAttr1->setValue("v1");
	pElem->setAttributeNodeNS(pAttr1);
	pAttr1->release();
	
	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "v1");
	assert (pElem->hasAttributeNS("urn:ns1", "a2"));
	assert (pElem->getAttributeNS("urn:ns1", "a2") == "V2");
	assert (pElem->hasAttributeNS("urn:ns2", "a3"));
	assert (pElem->getAttributeNS("urn:ns2", "a3") == "v3");

	pAttr3 = pDoc->createAttributeNS("urn:ns2", "q:a3");
	pAttr3->setValue("V3");
	pElem->setAttributeNodeNS(pAttr3);
	pAttr3->release();

	assert (pElem->hasAttributeNS("urn:ns1", "a1"));
	assert (pElem->getAttributeNS("urn:ns1", "a1") == "v1");
	assert (pElem->hasAttributeNS("urn:ns1", "a2"));
	assert (pElem->getAttributeNS("urn:ns1", "a2") == "V2");
	assert (pElem->hasAttributeNS("urn:ns2", "a3"));
	assert (pElem->getAttributeNS("urn:ns2", "a3") == "V3");

	pElem->removeAttributeNode(pAttr3);
	assert (!pElem->hasAttributeNS("urn:ns2", "a3"));
	
	pElem->removeAttributeNS("urn:ns1", "a1");
	assert (!pElem->hasAttributeNS("urn:ns1", "a1"));
	
	pElem->removeAttributeNS("urn:ns1", "a2");
	assert (!pElem->hasAttributeNS("urn:ns1", "a2"));
	
	assert (!pElem->hasAttributes());
}


void ElementTest::testAttrMap()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pElem = pDoc->createElement("elem");

	AutoPtr<NamedNodeMap> pNNM = pElem->attributes();
	assert (pNNM->length() == 0);
	
	pElem->setAttribute("a1", "v1");
	assert (pNNM->length() == 1);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItem("a1")->nodeName() == "a1");

	pElem->setAttribute("a2", "v2");
	assert (pNNM->length() == 2);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItem("a1")->nodeName() == "a1");
	assert (pNNM->item(1)->nodeName() == "a2");
	assert (pNNM->getNamedItem("a2")->nodeName() == "a2");
	
	Attr* pAttr = pDoc->createAttribute("a3");
	pNNM->setNamedItem(pAttr);
	pAttr->release();
	
	assert (pNNM->length() == 3);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItem("a1")->nodeName() == "a1");
	assert (pNNM->item(1)->nodeName() == "a2");
	assert (pNNM->getNamedItem("a2")->nodeName() == "a2");
	assert (pNNM->item(2)->nodeName() == "a3");
	assert (pNNM->getNamedItem("a3")->nodeName() == "a3");

	pNNM->removeNamedItem("a2");
	assert (pNNM->length() == 2);
	assert (!pElem->hasAttribute("a2"));
	
	pNNM->removeNamedItem("a3");
	assert (pNNM->length() == 1);
	assert (!pElem->hasAttribute("a3"));
	
	pElem->removeAttribute("a1");
	assert (pNNM->length() == 0);
}


void ElementTest::testAttrMapNS()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pElem = pDoc->createElementNS("urn:ns1", "elem");

	AutoPtr<NamedNodeMap> pNNM = pElem->attributes();
	assert (pNNM->length() == 0);
	
	pElem->setAttributeNS("urn:ns1", "a1", "v1");
	assert (pNNM->length() == 1);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItemNS("urn:ns1", "a1")->nodeName() == "a1");

	pElem->setAttributeNS("urn:ns1", "a2", "v2");
	assert (pNNM->length() == 2);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItem("a1")->nodeName() == "a1");
	assert (pNNM->item(1)->nodeName() == "a2");
	assert (pNNM->getNamedItem("a2")->nodeName() == "a2");
	
	Attr* pAttr = pDoc->createAttributeNS("urn:ns2", "a3");
	pNNM->setNamedItem(pAttr);
	pAttr->release();
	
	assert (pNNM->length() == 3);
	assert (pNNM->item(0)->nodeName() == "a1");
	assert (pNNM->getNamedItemNS("urn:ns1", "a1")->nodeName() == "a1");
	assert (pNNM->item(1)->nodeName() == "a2");
	assert (pNNM->getNamedItemNS("urn:ns1", "a2")->nodeName() == "a2");
	assert (pNNM->item(2)->nodeName() == "a3");
	assert (pNNM->getNamedItemNS("urn:ns2", "a3")->nodeName() == "a3");

	pNNM->removeNamedItemNS("urn:ns1", "a2");
	assert (pNNM->length() == 2);
	assert (!pElem->hasAttributeNS("urn:ns1", "a2"));
	
	pNNM->removeNamedItemNS("urn:ns2", "a3");
	assert (pNNM->length() == 1);
	assert (!pElem->hasAttributeNS("urn:ns2", "a3"));
	
	pElem->removeAttributeNS("urn:ns1", "a1");
	assert (pNNM->length() == 0);
}


void ElementTest::testElementsByTagName()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pRoot = pDoc->createElement("root");
	AutoPtr<NodeList> pNL1 = pRoot->getElementsByTagName("*");
	AutoPtr<NodeList> pNL2 = pRoot->getElementsByTagName("elem");
	
	assert (pNL1->length() == 0);
	assert (pNL2->length() == 0);
	
	AutoPtr<Element> pElem1 = pDoc->createElement("elem");
	pRoot->appendChild(pElem1);
	
	assert (pNL1->length() == 1);
	assert (pNL2->length() == 1);
	assert (pNL1->item(0) == pElem1);
	assert (pNL2->item(0) == pElem1);

	AutoPtr<Element> pElem2 = pDoc->createElement("Elem");
	pRoot->appendChild(pElem2);

	assert (pNL1->length() == 2);
	assert (pNL2->length() == 1);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem2);
	assert (pNL2->item(0) == pElem1);

	AutoPtr<Element> pElem3 = pDoc->createElement("elem");
	pRoot->appendChild(pElem3);

	assert (pNL1->length() == 3);
	assert (pNL2->length() == 2);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem2);
	assert (pNL1->item(2) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem3);
	
	AutoPtr<Element> pElem11 = pDoc->createElement("elem");
	pElem1->appendChild(pElem11);

	assert (pNL1->length() == 4);
	assert (pNL2->length() == 3);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem2);
	assert (pNL1->item(3) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem3);

	AutoPtr<Element> pElem12 = pDoc->createElement("Elem");
	pElem1->appendChild(pElem12);

	assert (pNL1->length() == 5);
	assert (pNL2->length() == 3);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem12);
	assert (pNL1->item(3) == pElem2);
	assert (pNL1->item(4) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem3);

	AutoPtr<Element> pElem21 = pDoc->createElement("elem");
	pElem2->appendChild(pElem21);

	assert (pNL1->length() == 6);
	assert (pNL2->length() == 4);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem12);
	assert (pNL1->item(3) == pElem2);
	assert (pNL1->item(4) == pElem21);
	assert (pNL1->item(5) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem21);
	assert (pNL2->item(3) == pElem3);
}


void ElementTest::testElementsByTagNameNS()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pRoot = pDoc->createElementNS("urn:ns1", "root");
	AutoPtr<NodeList> pNL1 = pRoot->getElementsByTagNameNS("*", "*");
	AutoPtr<NodeList> pNL2 = pRoot->getElementsByTagNameNS("*", "elem");
	AutoPtr<NodeList> pNL3 = pRoot->getElementsByTagNameNS("urn:ns1", "elem");
	
	assert (pNL1->length() == 0);
	assert (pNL2->length() == 0);
	
	AutoPtr<Element> pElem1 = pDoc->createElementNS("urn:ns1", "elem");
	pRoot->appendChild(pElem1);
	
	assert (pNL1->length() == 1);
	assert (pNL2->length() == 1);
	assert (pNL3->length() == 1);
	assert (pNL1->item(0) == pElem1);
	assert (pNL2->item(0) == pElem1);
	assert (pNL3->item(0) == pElem1);

	AutoPtr<Element> pElem2 = pDoc->createElementNS("urn:ns1", "Elem");
	pRoot->appendChild(pElem2);

	assert (pNL1->length() == 2);
	assert (pNL2->length() == 1);
	assert (pNL3->length() == 1);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem2);
	assert (pNL2->item(0) == pElem1);
	assert (pNL3->item(0) == pElem1);

	AutoPtr<Element> pElem3 = pDoc->createElementNS("urn:ns2", "elem");
	pRoot->appendChild(pElem3);

	assert (pNL1->length() == 3);
	assert (pNL2->length() == 2);
	assert (pNL3->length() == 1);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem2);
	assert (pNL1->item(2) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem3);
	assert (pNL3->item(0) == pElem1);
	
	AutoPtr<Element> pElem11 = pDoc->createElementNS("urn:ns1", "elem");
	pElem1->appendChild(pElem11);

	assert (pNL1->length() == 4);
	assert (pNL2->length() == 3);
	assert (pNL3->length() == 2);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem2);
	assert (pNL1->item(3) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem3);
	assert (pNL3->item(0) == pElem1);
	assert (pNL3->item(1) == pElem11);

	AutoPtr<Element> pElem12 = pDoc->createElementNS("urn:ns1", "Elem");
	pElem1->appendChild(pElem12);

	assert (pNL1->length() == 5);
	assert (pNL2->length() == 3);
	assert (pNL3->length() == 2);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem12);
	assert (pNL1->item(3) == pElem2);
	assert (pNL1->item(4) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem3);
	assert (pNL3->item(0) == pElem1);
	assert (pNL3->item(1) == pElem11);

	AutoPtr<Element> pElem21 = pDoc->createElementNS("urn:ns1", "elem");
	pElem2->appendChild(pElem21);

	assert (pNL1->length() == 6);
	assert (pNL2->length() == 4);
	assert (pNL3->length() == 3);
	assert (pNL1->item(0) == pElem1);
	assert (pNL1->item(1) == pElem11);
	assert (pNL1->item(2) == pElem12);
	assert (pNL1->item(3) == pElem2);
	assert (pNL1->item(4) == pElem21);
	assert (pNL1->item(5) == pElem3);
	assert (pNL2->item(0) == pElem1);
	assert (pNL2->item(1) == pElem11);
	assert (pNL2->item(2) == pElem21);
	assert (pNL2->item(3) == pElem3);
	assert (pNL3->item(0) == pElem1);
	assert (pNL3->item(1) == pElem11);
	assert (pNL3->item(2) == pElem21);
}


void ElementTest::testInnerText()
{
	AutoPtr<Document> pDoc = new Document;
	AutoPtr<Element> pRoot = pDoc->createElement("root");
	AutoPtr<Text> pText1 = pDoc->createTextNode("text1");
	AutoPtr<Element> pElem1 = pDoc->createElement("elem1");
	AutoPtr<Text> pText2 = pDoc->createTextNode("text2");
	AutoPtr<Text> pText3 = pDoc->createTextNode("text3");
	
	pElem1->appendChild(pText2);
	pRoot->appendChild(pText1);
	pRoot->appendChild(pElem1);
	pRoot->appendChild(pText3);
	
	XMLString innerText = pRoot->innerText();
	assert (innerText == "text1text2text3");
}


void ElementTest::testChildElement()
{
	AutoPtr<Document> pDoc  = new Document;
	AutoPtr<Element> pRoot  = pDoc->createElement("root");
	AutoPtr<Element> pElem1 = pDoc->createElement("elem1");
	AutoPtr<Element> pElem2 = pDoc->createElement("elem2");
	AutoPtr<Element> pElem3 = pDoc->createElement("elem3");
	AutoPtr<Element> pElem4 = pDoc->createElement("elem3");
	
	pRoot->appendChild(pElem1);
	pRoot->appendChild(pElem2);
	pRoot->appendChild(pElem3);
	pRoot->appendChild(pElem4);
	
	assert (pRoot->getChildElement("elem1") == pElem1);
	assert (pRoot->getChildElement("elem2") == pElem2);
	assert (pRoot->getChildElement("elem3") == pElem3);
	assert (pRoot->getChildElement("elem4") == 0);
	
	assert (pElem1->getChildElement("elem11") == 0);
}


void ElementTest::testChildElementNS()
{
	AutoPtr<Document> pDoc  = new Document;
	AutoPtr<Element> pRoot  = pDoc->createElementNS("urn:ns", "root");
	AutoPtr<Element> pElem1 = pDoc->createElementNS("urn:ns", "elem1");
	AutoPtr<Element> pElem2 = pDoc->createElementNS("urn:ns", "elem2");
	AutoPtr<Element> pElem3 = pDoc->createElementNS("urn:ns", "elem3");
	AutoPtr<Element> pElem4 = pDoc->createElementNS("urn:ns", "elem3");
	
	pRoot->appendChild(pElem1);
	pRoot->appendChild(pElem2);
	pRoot->appendChild(pElem3);
	pRoot->appendChild(pElem4);
	
	assert (pRoot->getChildElementNS("urn:ns", "elem1") == pElem1);
	assert (pRoot->getChildElementNS("urn:ns", "elem2") == pElem2);
	assert (pRoot->getChildElementNS("urn:ns", "elem3") == pElem3);
	assert (pRoot->getChildElementNS("urn:ns", "elem4") == 0);
	assert (pRoot->getChildElementNS("urn:NS", "elem1") == 0);
	
	assert (pElem1->getChildElementNS("urn:ns", "elem11") == 0);
}


void ElementTest::setUp()
{
}


void ElementTest::tearDown()
{
}


CppUnit::Test* ElementTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("ElementTest");

	CppUnit_addTest(pSuite, ElementTest, testAttributes);
	CppUnit_addTest(pSuite, ElementTest, testAttributesNS);
	CppUnit_addTest(pSuite, ElementTest, testAttrMap);
	CppUnit_addTest(pSuite, ElementTest, testAttrMapNS);
	CppUnit_addTest(pSuite, ElementTest, testElementsByTagName);
	CppUnit_addTest(pSuite, ElementTest, testElementsByTagNameNS);
	CppUnit_addTest(pSuite, ElementTest, testInnerText);
	CppUnit_addTest(pSuite, ElementTest, testChildElement);
	CppUnit_addTest(pSuite, ElementTest, testChildElementNS);

	return pSuite;
}

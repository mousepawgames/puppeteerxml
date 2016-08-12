#include"puppeteerxml.hpp"
#include <iochannel.hpp>

using namespace std;
using namespace pawlib::ioformat;
using namespace pawlib;
using namespace xercesc;

namespace puppeteerxml
{
    int init()
    {
         try //initializes xerces platform and throws and error message if it fails.
        {
            XMLPlatformUtils::Initialize();
        }
        catch (const XMLException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.getMessage());
            ioc << "Error during initialization! :\n"
                 << message << "\n" << io_end;
            XMLString::release(&message);
            return 1;
        }
        return 0;
    }

    void terminate()
    {
        XMLPlatformUtils::Terminate();
    }

    int Puppeteer::Parsing(const char* docName)
    {


        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
        DOMLSParser* parser = ((DOMImplementationLS*)impl)->createLSParser(DOMImplementationLS::MODE_SYNCHRONOUS, 0);

        // options that can be set on parser: currently researching what each does
        if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMValidate, true))
            parser->getDomConfig()->setParameter(XMLUni::fgDOMValidate, true);
        if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMNamespaces, true))
            parser->getDomConfig()->setParameter(XMLUni::fgDOMNamespaces, true);
       // if (parser->getDomConfig()->canSetParameter(XMLUni::fgDOMDatatypeNormalization, true))
        //    parser->getDomConfig()->setParameter(XMLUni::fgDOMDatatypeNormalization, true);


        //tries to parse document
        try
        {
            doc = parser->parseURI(docName);
        }
        //if fails then generates a Xerces based message indicating why it failed
        catch (const XMLException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.getMessage());
            ioc << "Exception message is: \n"
                 << message << io_end;
            XMLString::release(&message);
            return PARSE_ERROR1;
        }
        catch (const DOMException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.msg);
            ioc << "Exception message is: \n" << message  << io_end;
            XMLString::release(&message);
            return PARSE_ERROR2;
        }
        catch (...)
        {
            ioc << "Unexpected Exception " << io_end;
            return UNKNOWN_PARSE_ERROR;
        }

    //    root = doc->getDocumentElement();
        rootEl = doc->getDocumentElement();

        parser->release();
        return 0;

    }

    void Puppeteer::CreateDoc()
    {
        XMLCh tempStr[100];

        XMLString::transcode("Range", tempStr, 99);
        DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(tempStr);

        XMLString::transcode("root", tempStr, 99);
        doc = impl->createDocument(0, tempStr, 0);
        rootEl = doc->getDocumentElement();
    //    root = doc->getDocumentElement();
    }

    void Puppeteer::Release()
    {
        doc->release();
    }

    int Puppeteer::serializeDOM(const char* fileName)
    {

        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
        DOMLSSerializer* theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();

        //creates the standard output format for ease of reading by user
        if (theSerializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
            theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);


        // LocalFileFormatTarget prints the resultant XML stream
        // to a the specified file. Default file is
        XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(fileName);
        DOMLSOutput* theOutput = ((DOMImplementationLS*)impl)->createLSOutput();
        theOutput->setByteStream(myFormTarget);

    // StdOutFormatTarget prints the resultant XML stream
        // to stdout once it receives any thing from the serializer.

        try
        {
            // do the serialization through DOMLSSerializer::write();
            theSerializer->write(doc, theOutput);
        }
        catch (const XMLException& toCatch)
        {
            char* message = XMLString::transcode(toCatch.getMessage());
            ioc << "Exception message is: \n"
                << message << io_end;
            XMLString::release(&message);
            return SERIALIZE_ERROR1;
        }
        catch (const DOMException& toCatch)
            {
            char* message = XMLString::transcode(toCatch.msg);
            ioc << "Exception message is: \n"
                << message << "\n" << io_end;
            XMLString::release(&message);
            return SERIALIZE_ERROR2;
            }
        catch (...)
        {
            ioc << "Unexpected Exception \n" << io_end ;
            return UNKNOWN_SERIALIZE_ERROR;
        }

        theOutput->release();
        theSerializer->release();
        delete myFormTarget;
        return 0;
    }


    /*creates a list of the children nodes of the objects selected.
        The default for this is root.
    */
    void Puppeteer::getChildList(char select)
    {
        DOMNode* grab;
        switch(select)
        {
            case 'r': grab = rootEl; break;
            case 'c': grab = currEl; break;
            default: grab = rootEl;
        }
        ChildList = grab->getChildNodes();
    }



    int Puppeteer::getChildFromList(unsigned int index)
    {
        if(index < ChildList->getLength())
            currEl = (DOMElement*) ChildList->item(index);
        else
        {
            /* will also be output to the error channel of ioc
            Used to make looping easy if one needed to loop through
            the list of Nodes the loop would just have to end on a return
            of OUT_OF_BOUNDS */
            return OUT_OF_BOUNDS;
        }
        //check to see if there is a child element here
        if(currEl == NULL)
            return NO_NODE;
        return 0;
    }

    void Puppeteer::getAttrByName(const char* attrName)
    {
        getAttrList();
        Attr = AttrList->getNamedItem(XMLString::transcode(attrName));
    }


    //gets the attribute node to an attribute on the list
    void Puppeteer::getAttrFromList(int index)
    {
        Attr = AttrList->item(index);
        // Add error checking to confirm if attribute actually existed  `
    }

    int Puppeteer::getAttrList()
    {
        if(currEl->hasAttributes())
            AttrList = currEl->getAttributes();
        else
        {
            return NO_ATTRIBUTE;
        }
        return NO_ERROR;
    }



    int Puppeteer::getNumberOfAttributes()
    {
       if(currEl->hasAttributes())
        //checks for attributes to not waste time creating the AttrList
       {
           AttrList = currEl->getAttributes();
           return AttrList->getLength();
       }
       else
        return NO_ATTRIBUTE;

    }

    /* These addAttr functions take a higher Ram approach then ones used below
        These may be reimplemented because of multi attribute usage
        or originally DOMNode didn't handle attributes well
    If attribute doesn't exist on the current node then it adds
     the attribute with the specified value
     If the attribute does exist it changes the value of the attribute
    void Puppeteer::addAttr(const char* name, const char* value)
    {
        XMLCh tempStr[100];
        XMLString::transcode(name, tempStr, 99); // changes input value name into a XMLChar
        DOMAttr* att1 = doc->createAttribute(tempStr); //Creates a attribute node with the name, name
        XMLString::transcode(value, tempStr, 99); // same as above
        att1->setValue(tempStr); // sets the value of the attribute node to value
        getAttrList();
        AttrList->setNamedItem(att1); // attaches the attribute node created to the currently selected node.

    }
    // This function acts as a default to set an attribute with no value
    void Puppeteer::addAttr(const char* name)
    {
        XMLCh tempStr[100];
        XMLString::transcode(name, tempStr, 99); // changes input value name into a XMLChar
        DOMAttr* att1 = doc->createAttribute(tempStr); //Creates a attribute node with the name, name
        getAttrList();
        AttrList->setNamedItem(att1); // attaches the attribute node created to the currently selected node.

    }

    */

    void Puppeteer::remove_attribute(const char* name)
    {
        getAttrList(); //make sure attribute list is generated
        AttrList->removeNamedItem(XMLString::transcode(name)); //removes the node from the list
    }

    //Note: program will fail if the element value is a simple numerical value
    //Note: program will fail if value starts with an element
    /* The following functions adds a child of the tag name element to the either root or curr
    */

    void Puppeteer::addChild_to_Root(const char* element)
    {
        XMLCh tempStr[100]; // must be in Xerces special char for use

        XMLString::transcode(element, tempStr, 99);
        DOMElement*   e1 = doc->createElement(tempStr);
        rootEl->appendChild(e1);
    }

    void Puppeteer::addChild_to_Root(DOMNode* element)
    {
        rootEl->appendChild(element);
    }

    void Puppeteer::addChild_to_Curr(const char* element)
    {
        XMLCh tempStr[100];
        XMLString::transcode(element, tempStr, 99);
        DOMNode*   e2 = doc->createElement(tempStr);
        currEl->appendChild(e2);
    }

    void Puppeteer::addChild_to_Curr(DOMNode* element)
    {
        currEl->appendChild(element);
    }

    void Puppeteer::addChild_before_Curr(const char* element)
    {

        XMLCh tempStr[100]; // must be in Xerces special char for use
        DOMNode* Parent = currEl->getParentNode();
        XMLString::transcode(element, tempStr, 99);
        DOMElement* e1 = doc->createElement(tempStr);
        Parent->insertBefore(e1, currEl); //uses the child list of the parent for placing the node before the specified one.

    }

    void Puppeteer::addChild_before_Curr(DOMNode* element)
    {
        DOMNode* Parent = currEl->getParentNode();
        Parent->insertBefore(element, currEl);
    }

    /*Copies the current node and returns it. If true is passed into the function the node and everything under it
    will be copied. if false will only copy the base node. Default is false */

    /*NOTE: need to test if attributes are copied when only copying the base node by passing false*/
    DOMNode* Puppeteer::copy_Curr(bool Everything)
    {
        return currEl->cloneNode(Everything);
    }


    void Puppeteer::addTextNode(const char* element)
    {
        XMLCh tempStr[100];
        XMLString::transcode(element,tempStr, 99);
        currEl->setTextContent(tempStr);
    }

    /* imports a node from a different document and returns the node
    in case the user doesn't want to give it a parent node yet. */
    DOMNode* Puppeteer::importNode(DOMNode* node, bool deep)
    {
        return doc->importNode(node, deep);
    }
    /*imports node directly to the curr node's child list appended at the end */
    void Puppeteer::import_to_Curr(DOMNode* node, bool deep)
    {
        addChild_to_Curr(importNode(node, deep));
    }
    /*For added funtionality also adds child before curr from another document */
    void Puppeteer::import_before_Curr(DOMNode* node, bool deep)
    {
        addChild_before_Curr(importNode(node, deep));
    }
    /*imports node directly to Root node's child list appended at the end */
    void Puppeteer::import_to_Root(DOMNode* node, bool deep)
    {
        addChild_to_Root(importNode(node, deep));
    }



    //Functionality needs to be added so that it returns the node removed.
    void Puppeteer::remove_Curr_Node()
    {
        DOMNode* temp = currEl;
        DOMNode* parent = currEl->getParentNode();
        if(previous_Element() < 0)
            nextSibling();
        parent->removeChild(temp);
    }



    /*NOTE: The list is not an active element any changes to
    what was already there will not change the values in this list
    yet if you change a piece in this list it will appear in final
    Document when serialized */
    // creates an attribute list from the attributes on the current node


    int Puppeteer::getChild(char node)
    {
        DOMElement* temp = currEl; //used to hold the current element in case there is no child
        switch(node) //allows quick selection of the child elements either from the root node or the current node
        {
           // case 'a': attr = curr->
            case 'c': currEl = currEl->getFirstElementChild(); break;
            case 'r': currEl = rootEl->getFirstElementChild(); break;
            default: currEl = rootEl->getFirstElementChild(); // default for now probably will be used as error later
        }
        if(currEl == NULL)
        {
            currEl = temp;
            return NO_NODE; // case that there is no child element

        }
        else
            return NO_ERROR; // represents that no error has occurred
    }
    //Function added to allow for clearer code

    /* These functions don't do base elements instead they simply just do nodes
    // gets the next child element of the curr node
    int Puppeteer::nextSibling()
    {
        curr = curr->getNextSibling();
        //check to see if curr is still valid
        if(curr == NULL)
            return NO_NODE; // case that there is no child element
        else
            return 0; // represents that no error has occurred
    }

    int Puppeteer::previousSibling()
    {
        DOMNode* tmp = curr;
        curr = curr->getPreviousSibling();
        //check to see if curr is still valid
        if(curr == NULL)
        {
            curr = tmp;
            return NO_NODE; // case that there is no child element
        }
        else
            return 0; // represents that no error has occurred

    }

    */
    /*Currently only will do the current elements Tag Name. Later wish to expand to
    convert current attribute, current attribute's value, and the current elements text node */
    char* Puppeteer::to_String(char option)
    {

         switch(option)
        {
             case 'r': if(rootEl != NULL)
                            return XMLString::transcode(rootEl->getNodeName());
                        else
                            ioc << "No root node set";
                        break;
             case 'n': return XMLString::transcode(currEl->getNodeName()); break; //gets the current nodes name
             case 'a': return XMLString::transcode(Attr->getNodeName()); break; // Attribute name
             case 'v': return XMLString::transcode(Attr->getNodeValue()); break; // Value of the attribute
             case 't': getTextContent(); break; // text node of curr
             default: return '\0';
        }

        return '\0';

    }


    /* This is a test to see if parsing is more effective with elements rather than nodes */

    int Puppeteer::getElementChild(char node)
    {
        switch(node) //allows quick selection of the child elements either from the root node or the current node
        {
            case 'c': currEl = currEl->getFirstElementChild(); break;
            case 'r': currEl = rootEl->getFirstElementChild(); break;
            default: currEl = rootEl->getFirstElementChild(); // default for now probably will be used as error later
        }

        //curr = currEl; used for testing purposes
        if(currEl == NULL)
            return NO_NODE; // case that there is no child element
        else
            return 0; // represents that no error has occurred

    }


    char* Puppeteer::Element_String(char option)
    {
         switch(option)
        {
             case 'r': if(rootEl != NULL)
                            return XMLString::transcode(rootEl->getTagName());
                        else
                            ioc << "No root node set" << io_end;
                break;
             case 'n': return XMLString::transcode(currEl->getTagName()); break; //gets the current nodes name
                //The attribute to string part of this code requires more error checking essentially to check if Attr is a valid attribute node

             case 'a': if(Attr != NULL)
                            return XMLString::transcode(Attr->getNodeName());
                        else
                            ioc << "No Attribute set" << io_end;
                break; // Attribute name
             case 'v': if(Attr != NULL)
                            return XMLString::transcode(Attr->getNodeValue());
                        else
                            ioc << "No Attribute set" << io_end;
                break; // Attribute name


             case 't':
                            return  getTextContent();
                        break; // text node of curr
             default: return '\0';
        }

        return '\0';

    }



    // gets the next child element of the curr node
    int Puppeteer::next_Element()
    {
        DOMElement* temp = currEl;
        currEl = currEl->getNextElementSibling();
        //check to see if curr is still valid
        if(currEl == NULL)
        {
            currEl = temp; // because there was no child set back to original curr
            return NO_NODE; // case that there is no child element
        }
        else
            return 0; // represents that no error has occurred
    }

    int Puppeteer::previous_Element()
    {
         DOMElement* tmp = currEl;
        currEl = currEl->getPreviousElementSibling();
        //check to see if curr is still valid
        if(currEl == NULL)
        {
            currEl = tmp;
            return NO_NODE; // case that there is no child element
        }
        else
            return 0; // represents that no error has occurred


    }


    void Puppeteer::getRootFirstChild()
    {
        currEl = rootEl->getFirstElementChild();
    }

    void Puppeteer::getCurrFirstChild()
    {
        currEl = currEl->getFirstElementChild();
    }



    void Puppeteer::add_attribute(const char* name, const char* value)
    {
        XMLCh nameStr[100];
        XMLCh valueStr[100];

        XMLString::transcode(name, nameStr, 99); // changes input value name into a XMLChar
        XMLString::transcode(value, valueStr, 99);

        currEl->setAttribute(nameStr, valueStr);
    }

    void Puppeteer::add_attribute(const char* name)
    {
        XMLCh nameStr[100];

        XMLString::transcode(name, nameStr, 99);
        currEl->setAttribute(nameStr, NULL);
    }

    void Puppeteer::add_text(const char* text)
    {
         XMLCh textStr[100]; // must be in Xerces special char for use

        XMLString::transcode(text, textStr, 99);
    //    DOMText*   textNode = doc->createTextNode(textStr);
        currEl->setTextContent(textStr);

    }



    char* Puppeteer::getTextContent()
    {


        DOMNode* temp = currEl->getFirstChild();
        if(temp != 0)
        {


            switch(temp->getNodeType())
            {
            case TEXT_NODE:
            case CDATA_SECTION_NODE:
                return XMLString::transcode(temp->getNodeValue());
                break;
            default: return "-2";
            }
        }
        else
           return "-1";

        return "0";
    }
}

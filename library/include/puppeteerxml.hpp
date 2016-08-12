#ifndef PUPPETEERXML_HPP_INCLUDED
#define PUPPETEERXML_HPP_INCLUDED

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>


#define DEFAULT_FILE "XMLtest.xml"
#define TEXT_NODE 3
#define CDATA_SECTION_NODE 4

using namespace xercesc;

namespace puppeteerxml
{

    int init();
    void terminate();



    class Puppeteer
    {
    private:
        DOMNamedNodeMap* AttrList;
        DOMNodeList* ChildList;

        //DOMNode* curr;
        DOMElement* currEl; //The EL represents element
        DOMElement* rootEl;
        DOMDocument* doc;
        //DOMNode* root;
        DOMNode* transition;
        DOMNode* Attr;


    public:
        //error code system for now still considering changing to hexadecimal
        enum PuppetError
        {
            NO_TEXTNODE             = -10,
            NO_ATTRIBUTE            = -9,
            UNKNOWN_SERIALIZE_ERROR = -8,
            SERIALIZE_ERROR2        = -7,
            SERIALIZE_ERROR1        = -6,
            UNKNOWN_PARSE_ERROR     = -5,
            PARSE_ERROR1            = -4,
            PARSE_ERROR2            = -3,
            OUT_OF_BOUNDS           = -2,
            NO_NODE                 = -1,
            NO_ERROR                =  0

        };


        Puppeteer()
        {
            currEl = NULL;
            rootEl = NULL;

//            curr = NULL;
//            root = NULL;
            doc = NULL;
            transition = NULL;
            Attr = NULL;
            AttrList = NULL;
            ChildList = NULL;
        }
        ~Puppeteer() {}


        int Parsing(const char* docName);
        void CreateDoc();
        //Used to remove all excess resources called when done with the document
        void Release();
        int serializeDOM(const char* fileName = DEFAULT_FILE);


        void getChildList(char select = 'r');
        int getChildFromList(unsigned int index);

        void getAttrByName(const char* attrName);
        void getAttrFromList(int index = 0);
        /*
        Gets a list of attributes from the current node
        returns a negative value if none exist and zero if
        there are attributes
        */
        int getAttrList();
        /*
        Gets the number of attributes on the given curr node.
        Return value is the same as above in the case there are no nodes
        */
        int getNumberOfAttributes();
        /*multiple attributes with the same name can not exist on an element
        So if the named element is called the value is changed. Name of an
        attribute can't begin or be just a number. However the value can be.*/

        void remove_attribute(const char* name);


        void addChild_to_Root(const char*);
        void addChild_to_Root(DOMNode* element);
        void addChild_to_Curr(const char*);
        void addChild_to_Curr(DOMNode* element);
        void addChild_before_Curr(const char*);
        void addChild_before_Curr(DOMNode* element);
        DOMNode* copy_Curr(bool Everything = false);
        void addTextNode(const char*);

        /*import functions: allows addition of node from other xml documents
        node is the node that is to be added,
        deep is to determine if all children of the node should also be added
       */
        DOMNode* importNode(DOMNode* node, bool deep);
        void import_to_Curr(DOMNode* node, bool deep);
        void import_before_Curr(DOMNode* node, bool deep);
        void import_to_Root(DOMNode* node, bool deep);
        /*
        Removes the previous node and all of its children.
        Then sets curr to its sibling on the left of the tree.
        If there is no sibling on the left then it sets it to the
        parent node instead.
        */
        void remove_Curr_Node();

        /*
        Removes the node specified by user. However only works within
        a specific scope. This will only examine the list on nodes underneath
        the parent and not under any of the children. In addition will either remove
        the first node encountered or all nodes that have that name.
        */ //NOTE: Note yet implemented
        //void remove_Named_Node(const char*);



        int getChild(char node = 'r'); //default to get child element of root.
        int setRoot(); // used to clarify code but just calls default getChild
        int nextSibling();
        int previousSibling();
        //returns the name, value or text of root, curr, or attribute nodes
        char* to_String(char option = 'n');

        int getElementChild(char node = 'r');
        char* Element_String(char option = 'n');
        int next_Element();
        int previous_Element();

        void add_attribute(const char* name, const char* value);
        void add_attribute(const char* name);
        void add_text(const char* text);
        void getCurrFirstChild();
        void getRootFirstChild();
        char* getTextContent();



    };

}
#endif // PUPPETTEERXML_HPP_INCLUDED

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <iochannel.hpp>
#include <puppeteerxml.hpp>

int main()
{
    /*initializes xerces utilities for remainder of program, program must call terminate
    when done using XML parsing to free resources */
    puppeteerxml::init();

	//Puppeteer begins
    puppeteerxml::Puppeteer trial;

	/*
    trial.CreateDoc();
    trial.add_to_Root("Evolving");
    trial.add_to_Root("Code");
    trial.add_to_Root("Writter");
    trial.getRootFirstChild();
    trial.add_text("But not to quickly");
    trial.getCurrFirstChild();

    trial.serializeDOM();
	*/
    trial.Parsing("XMLtest.xml");
    pawlib::ioc << trial.Element_String('r') << pawlib::io_end;
    trial.getRootFirstChild();
    pawlib::ioc << trial.Element_String() << pawlib::io_end;

    //trial.serializeDOM();
    //trial.Release();
    // done with the document, must call release() to release the entire document resources
    //trial.Release();
    puppeteerxml::terminate(); // ends usage of Xerces XML platform

	//Puppeteer ends
	/*
    signed char c = -123;
    signed short int si = -12345;
    signed int i = -123456789;
    signed long int li = -123456789123456789;
	*/

    return 0;
}

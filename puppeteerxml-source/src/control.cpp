#include "puppeteerxml/control.hpp"

namespace puppeteerxml
{
    void control::test()
    {
        pawlib::ioc << pawlib::ioformat::fg_blue << pawlib::ioformat::ta_bold
                    << "PuppeteerXML is alive!" << pawlib::io_end;
    }
}

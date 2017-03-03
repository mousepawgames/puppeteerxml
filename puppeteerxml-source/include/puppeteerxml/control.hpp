/** Control [PuppeteerXML]
  * Version: 1.0
  *
  * Opens and works with a single XML file.
  *
  * Last Updated: 2 March 2017
  * Author: Nate Groggett
  */

/* LICENSE
 * Copyright (c) 2017 MousePaw Games.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See http://www.mousepawgames.com/participate/opensource for information
 * on how to contribute to our projects.
 */

#ifndef PUPPETEERXML_HPP_INCLUDED
#define PUPPETEERXML_HPP_INCLUDED

#include "pawlib/iochannel.hpp"
#include "pugixml/pugiconfig.hpp"
#include "pugixml/pugixml.hpp"

namespace puppeteerxml
{
    /* Yes, I borrowed the name from the "control" of a marionette puppet.
     * I needed something more descriptive for the class name, rather than
     * repeating the folder and namespace AGAIN.
     * -Jason C. McDonald */

    class control
    {
    public:
        control(){}

        // Feel free to take this out when you no longer need it.
        static void test();

        ~control(){}

    };
}
#endif // PUPPETTEERXML_HPP_INCLUDED

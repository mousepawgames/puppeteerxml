none:
	@echo "=== PuppeteerXML 1.0 ==="
	@echo "Select a build target:"
	@echo "   make ready                Build PuppeteerXML and bundle it for distribution."
	@echo
	@echo "   make clean                Clean up PuppeteerXML and Tester."
	@echo "   make cleandebug           Clean up PuppeteerXML and Tester Debug."
	@echo "   make cleanrelease         Clean up PuppeteerXML and Tester Release."
	@echo "   make docs                 Generate HTML docs."
	@echo "   make puppeteerxml         Build PuppeteerXML as release."
	@echo "   make puppeteerxml_debug   Build PuppeteerXML as debug."
	@echo "   make tester               Build PuppeteerXML Tester (+ PuppeteerXML) as release."
	@echo "   make tester_debug         Build PuppeteerXML Tester (+ PuppeteerXML) as debug."
	@echo "   make all                  Build everything."
	@echo "   make allfresh             Clean and rebuild everything."
	@echo
	@echo "Clang Sanitizers (requires Debug build and Clang.)"
	@echo "  SAN=address     Use AddressSanitizer"
	@echo "  SAN=leak        Use LeakSanitizer w/o AddressSanitizer (Linux only)"
	@echo "  SAN=memory      Use MemorySanitizer"
	@echo "  SAN=thread      Use ThreadSanitizer"
	@echo "  SAN=undefined   Use UndefiniedBehaviorSanitizer"
	@echo
	@echo "Optional Architecture (only when building PuppeteerXML or Tester)"
	@echo "  ARCH=32	Make x86 build (-m32)"
	@echo "  ARCH=64	Make x64 build (-m64)"
	@echo
	@echo "Use Configuration File"
	@echo "  CONFIG=foo      Uses the configuration file 'foo.config'"
	@echo "                  in the root of this repository."
	@echo "  When unspecified, default.config will be used."
	@echo
	@echo "For other build options, see the 'make' command in 'docs/', 'puppeteerxml-source/', and 'puppeteerxml-tester/'."

clean:
	$(MAKE) clean -C puppeteerxml-source
	$(MAKE) clean -C puppeteerxml-tester

cleanall: clean
	$(MAKE) clean -C docs

cleandebug:
	$(MAKE) cleandebug -C puppeteerxml-source
	$(MAKE) cleandebug -C puppeteerxml-tester

cleanrelease:
	$(MAKE) cleanrelease -C puppeteerxml-source
	$(MAKE) cleanrelease -C puppeteerxml-tester

docs:
	$(MAKE) html -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/html/index.html'."
	@echo "-------------"

docs_pdf:
	$(MAKE) latexpdf -C docs
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "View docs at 'docs/build/latex/PawLIB.pdf'."
	@echo "-------------"

puppeteerxml:
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C puppeteerxml-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML is in 'puppeteerxml-library/lib/Release'."
	@echo "-------------"

puppeteerxml_debug:
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C puppeteerxml-source
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML is in 'puppeteerxml-library/lib/Debug'."
	@echo "-------------"

ready: library
	@rm -rf puppeteerxml
	@echo "Creating file structure..."
	@mkdir -p puppeteerxml/lib
	@echo "Copying PuppeteerXML..."
	@cp -r puppeteerxml-source/include puppeteerxml/
	@cp puppeteerxml-source/lib/Release/libpuppeteerxml.a puppeteerxml/lib/libpuppeteerxml.a
	@echo "Copying README and LICENSE..."
	@cp README.md puppeteerxml/README.md
	@cp LICENSE.md puppeteerxml/LICENCE.md
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "The library is in 'puppeteerxml'."
	@echo "-------------"

tester: puppeteerxml
	$(MAKE) release ARCH=$(ARCH) CONFIG=$(CONFIG) -C tester
	@rm -f tester
	@ln -s puppeteerxml-tester/bin/Release/puppeteerxml-tester puppeteerxml-tester
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML Tester is in 'puppeteerxml-tester/bin/Release'."
	@echo "The link './tester' has been created for convenience."
	@echo "-------------"

tester_debug: puppeteerxml_debug
	$(MAKE) debug ARCH=$(ARCH) CONFIG=$(CONFIG) SAN=$(SAN) -C puppeteerxml-tester
	@rm -f tester_debug
	@ln -s puppeteerxml-tester/bin/Debug/puppeteerxml-tester tester_debug
	@echo "-------------"
	@echo "<<<<<<< FINISHED >>>>>>>"
	@echo "PuppeteerXML Tester is in 'puppeteerxml-tester/bin/Debug'."
	@echo "The link './tester_debug' has been created for convenience."
	@echo "-------------"

all: docs tester

allfresh: cleanall all

.PHONY: all allfresh clean cleandebug cleanrelease docs docs_pdf puppeteerxml puppeteerxml_debug ready tester tester_debug

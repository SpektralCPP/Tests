all:

install: includes/Spektral/Tests/TestGroup.hpp includes/Spektral/Tests/TestSuite.hpp includes/Spektral/Tests/TestCase.hpp
	@echo "Installing header at /usr/include/Spektral/Tests/"
	@sudo mkdir -p /usr/include/Spektral/Tests/
	@sudo cp $^ /usr/include/Spektral/Tests/

docs: doxygenfile
	@echo "Generating docs"
	@mkdir -p docs/html
	@doxygen $^

all: install

install: /usr/include/Spektral/Tests/tests.hpp

/usr/include/Spektral/Tests/colors.hpp\
/usr/include/Spektral/Tests/test_group.hpp\
/usr/include/Spektral/Tests/test_suite.hpp\
/usr/include/Spektral/Tests/tests.hpp /usr/include/Spektral/Tests/utils.hpp:\
	includes/Spektral/Tests/colors.hpp\
	includes/Spektral/Tests/test_group.hpp\
	includes/Spektral/Tests/test_suite.hpp includes/Spektral/Tests/tests.hpp\
	includes/Spektral/Tests/utils.hpp
	@echo "Installing header at /usr/include/Spektral/Tests/"
	@sudo mkdir -p /usr/include/Spektral/Tests/
	@sudo cp $^ /usr/include/Spektral/Tests/

docs: doxygenfile
	@echo "Generating docs"
	@mkdir -p docs/html
	@doxygen $^

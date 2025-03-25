all: install

install: /usr/include/Spektral/Tests/tests.hpp

/usr/include/Spektral/Tests/tests.hpp: includes/Spektral/Tests/tests.hpp
	@echo "Installing header at /usr/include/Spektral/Tests/tests.hpp"
	@sudo mkdir -p /usr/include/Spektral/Tests/
	@sudo cp $^ /usr/include/Spektral/Tests/tests.hpp

docs: doxygenfile
	@echo "Generating docs"
	@mkdir -p docs/html
	@doxygen $^

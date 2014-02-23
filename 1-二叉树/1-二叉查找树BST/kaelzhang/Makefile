REPORTER = spec

test:
		@npm install
		@./node_modules/.bin/mocha \
			--reporter $(REPORTER) \
			./test.js

.PHONY: test
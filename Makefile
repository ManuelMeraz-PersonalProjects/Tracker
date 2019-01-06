help:
	@echo "    clean"
	@echo "        Remove python artifacts."
	@echo "    lint"
	@echo "        Check style with flake8."
	@echo "    test"
	@echo "        Run py.test"
	@echo '    run'
	@echo '        Run main'

.PHONY: clean
clean:
	@find . -name '*.pyc' -exec rm --force {} +
	@find . -name '*.pyo' -exec rm --force {} +
	@find . -name '*~' -exec rm --force  {} +
	@find . -name '__pyache__' -type d -exec rm -rf {} +

lint:
	@flake8 

test: 
	@py.test --verbose --color=yes ./tests

run:
	@python ./src/main.py

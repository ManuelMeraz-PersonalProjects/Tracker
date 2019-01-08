help:
	@echo "    clean"
	@echo "        Remove python artifacts."
	@echo "    lint"
	@echo "        Check style with flake8."
	@echo "    test"
	@echo "        Run py.test"
	@echo '    run'
	@echo '        Run main'
	@echo '    docs'
	@echo '        Create html documentations in docs/'

.PHONY: clean
clean:
	@find . -name '*.pyc' -exec rm --force {} +
	@find . -name '*.pyo' -exec rm --force {} +
	@find . -name '*~' -exec rm --force  {} +
	@find . -name '*.db' -exec rm --force  {} +
	@find . -name '__pycache__' -type d -exec rm -rf {} +

lint:
	@flake8 

test: 
	@pytest --verbose --color=yes 

run:
	@python3 tracker/main.py

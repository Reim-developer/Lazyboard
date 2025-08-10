.PHONY: target build

SHELL = /usr/bin/bash

debug:
	@$(MAKE) -C scripts debug

clean-cache:
	@$(MAKE) -C scripts clean-cache

gdb:
	@$(MAKE) -C scripts gdb
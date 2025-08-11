.PHONY: build

debug:
	@$(MAKE) -C scripts debug-build
	@echo "[INFO]: Exit with status: $$?"

debug-gdb:
	@$(MAKE) -C scripts debug-gdb

check:
	@$(MAKE) -C scripts linter-check

dev-push:
	@$(MAKE) -C scripts dev-push

master-push:
	@$(MAKE) -C scripts master-push

stable-push:
	@$(MAKE) -C scripts stable-push
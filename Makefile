.PHONY: build

debug:
	@$(MAKE) -C scripts debug-build
	@echo "[INFO]: Exit with status: $$?"

debug-gdb:
	@$(MAKE) -C scripts debug-gdb

backend-test:
	@$(MAKE) -C scripts backend-test

check-backend:
	@$(MAKE) -C scripts check-backend

check-frontend:
	@$(MAKE) -C scripts check-frontend

dev-push:
	@$(MAKE) -C scripts dev-push

master-push:
	@$(MAKE) -C scripts master-push

stable-push:
	@$(MAKE) -C scripts stable-push
.PHONY: build

scripts_folder = scripts

debug:
	@$(MAKE) -C $(scripts_folder) debug-build
	@echo "[INFO]: Exit with status: $$?"

debug-non-gui:
	@$(MAKE) -C $(scripts_folder) debug-non-gui

debug-gdb:
	@$(MAKE) -C $(scripts_folder) debug-gdb

backend-test:
	@$(MAKE) -C $(scripts_folder) backend-test

check-backend:
	@$(MAKE) -C $(scripts_folder) check-backend

check-frontend:
	@$(MAKE) -C $(scripts_folder) check-frontend

dev-push:
	@$(MAKE) -C $(scripts_folder) dev-push

master-push:
	@$(MAKE) -C $(scripts_folder) master-push

stable-push:
	@$(MAKE) -C $(scripts_folder) stable-push

build_options ?= none
deploy-linux:
	@$(MAKE) -C $(scripts_folder) deploy-linux build_options="$(build_options)"
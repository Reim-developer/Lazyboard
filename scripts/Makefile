build_options ?= none
valid_options := backend-build frontend-build backend-check frontend-check backend-test

ifeq ($(filter $(build_options),$(valid_options)),)
$(error "Invalid build option: $(build_options), all valid options is: | $(valid_options) |")
endif

.PHONY: build target

debug-build:
	@./debug.sh debug-build

debug-non-gui:
	@./debug.sh debug-build-noshow

debug-gdb:
	@./debug.sh debug-gdb

check-frontend:
	@./debug.sh check-frontend

check-backend:
	@./debug.sh check-backend

dev-push:
	@./debug.sh push-dev

master-push:
	@./debug.sh push-master

stable-push:
	@./debug.sh push-stable

backend-test:
	@./debug.sh backend-test

deploy-linux:
	$(if $(filter $(build_options),frontend-build), \
		@$(MAKE) __linux_front_end_build,)
		
	$(if $(filter $(build_options),backend-build), \
		@$(MAKE) __linux_back_end_build,)

	$(if $(filter $(build_options),frontend-check), \
		@$(MAKE) __linux_front_end_check,)

	$(if $(filter $(build_options),backend-check), \
		@$(MAKE) __linux_back_end_check,)

	$(if $(filter $(build_options),backend-test), \
		@$(MAKE) __linux_back_end_test,)

__linux_back_end_check:
	@./linux_deploy.sh backend-check

__linux_front_end_check:
	@./linux_deploy.sh frontend-check

__linux_back_end_build:
	@./linux_deploy.sh backend-build

__linux_front_end_build:
	@./linux_deploy.sh frontend-build

__linux_back_end_test:
	@./linux_deploy.sh backend-test
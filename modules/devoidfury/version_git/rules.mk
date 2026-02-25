

GENERATED_VERSIONS_FILE = $(INTERMEDIATE_OUTPUT)/src/version_git.h

LOCAL_BRANCH = $(shell git -C "$(TOP_DIR)" name-rev --name-only HEAD)
QMK_REMOTE = $(shell git -C "$(TOP_DIR)" config branch.$(LOCAL_BRANCH).remote)

USERSPACE_BRANCH = $(shell git -C "$(QMK_USERSPACE)" name-rev --name-only HEAD)
USERSPACE_REMOTE = $(shell git -C "$(QMK_USERSPACE)" config branch.$(USERSPACE_BRANCH).remote)

$(GENERATED_VERSIONS_FILE):
	echo "#pragma once" > $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_COMMIT \"$$(git -C "$(TOP_DIR)" rev-parse --short HEAD)$$(git -C "$(TOP_DIR)" diff --quiet || echo "*" )\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_BRANCH \"$$(git -C "$(TOP_DIR)" config branch.$(LOCAL_BRANCH).merge)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_REMOTE \"$(QMK_REMOTE)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_REMOTE_URL \"$$(git -C "$(TOP_DIR)" config remote.$(QMK_REMOTE).url)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define USERSPACE_COMMIT \"$$(git -C "$(QMK_USERSPACE)" rev-parse --short HEAD)$$(git -C "$(QMK_USERSPACE)" diff --quiet || echo "*" )\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define USERSPACE_BRANCH \"$$(git -C "$(QMK_USERSPACE)" config branch.$(USERSPACE_BRANCH).merge)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define USERSPACE_REMOTE \"$(USERSPACE_REMOTE)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define USERSPACE_REMOTE_URL \"$$(git -C "$(QMK_USERSPACE)" config remote.$(USERSPACE_REMOTE).url)\"" >> $(GENERATED_VERSIONS_FILE)

generated-files: $(GENERATED_VERSIONS_FILE)

POST_CONFIG_H += $(GENERATED_VERSIONS_FILE)



GENERATED_VERSIONS_FILE = $(MODULE_PATH_VERSION)/qmk_version.h

clean_qmk_version_h:
	rm -f $(GENERATED_VERSIONS_FILE)


LOCAL_BRANCH = $(shell git -C "$(TOP_DIR)" name-rev --name-only HEAD)
QMK_REMOTE = $(shell git -C "$(TOP_DIR)" config branch.$(LOCAL_BRANCH).remote)

$(GENERATED_VERSIONS_FILE): clean_qmk_version_h
	echo "#pragma once" > $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_COMMIT \"$$(git -C "$(TOP_DIR)" rev-parse HEAD)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_BRANCH \"$$(git -C "$(TOP_DIR)" config branch.$(LOCAL_BRANCH).merge)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_REMOTE \"$(QMK_REMOTE)\"" >> $(GENERATED_VERSIONS_FILE)
	echo "#define QMK_REMOTE_URL \"$$(git -C "$(TOP_DIR)" config remote.$(QMK_REMOTE).url)\"" >> $(GENERATED_VERSIONS_FILE)

generated-files: $(GENERATED_VERSIONS_FILE)

POST_CONFIG_H += $(GENERATED_VERSIONS_FILE)

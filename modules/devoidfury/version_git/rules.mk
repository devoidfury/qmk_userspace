

GIT_VERSIONS_FILE = $(INTERMEDIATE_OUTPUT)/src/version_git.h

define git-qmk =
git -C "$(TOP_DIR)"
endef

define git-user =
git -C "$(QMK_USERSPACE)"
endef

define clean-url
sed -e 's%git@\|https\?://%%' -e 's/.git$$//' -e 's%:%/%'
endef

LOCAL_BRANCH = $(shell $(git-qmk) name-rev --name-only HEAD)
QMK_REMOTE = $(shell $(git-qmk) config branch.$(LOCAL_BRANCH).remote)

USERSPACE_BRANCH = $(shell $(git-user) name-rev --name-only HEAD)
USERSPACE_REMOTE = $(shell $(git-user) config branch.$(USERSPACE_BRANCH).remote)

$(GIT_VERSIONS_FILE):
	echo "#pragma once" > $(GIT_VERSIONS_FILE)
	echo "#define QMK_COMMIT \"$$($(git-qmk) rev-parse --short HEAD)$$($(git-qmk) diff --quiet || echo "*" )\"" >> $(GIT_VERSIONS_FILE)
	echo "#define QMK_BRANCH \"$$($(git-qmk) config branch.$(LOCAL_BRANCH).merge | sed 's%refs/heads/%%' )\"" >> $(GIT_VERSIONS_FILE)
	echo "#define QMK_REMOTE_URL \"$$($(git-qmk) config remote.$(QMK_REMOTE).url | $(clean-url) )\"" >> $(GIT_VERSIONS_FILE)
	echo "#define USERSPACE_COMMIT \"$$($(git-user) rev-parse --short HEAD)$$($(git-user) diff --quiet || echo "*" )\"" >> $(GIT_VERSIONS_FILE)
	echo "#define USERSPACE_BRANCH \"$$($(git-user) config branch.$(USERSPACE_BRANCH).merge | sed 's%refs/heads/%%' )\"" >> $(GIT_VERSIONS_FILE)
	echo "#define USERSPACE_REMOTE_URL \"$$($(git-user) config remote.$(USERSPACE_REMOTE).url | $(clean-url) )\"" >> $(GIT_VERSIONS_FILE)

generated-files: $(GIT_VERSIONS_FILE)

POST_CONFIG_H += $(GIT_VERSIONS_FILE)

file(READ "${GIT_VERSION}" git_version)

# remove line breaks at the end of file
string(STRIP "${git_version}" git_version)

file(WRITE "${MY_VERSION_HEADER}"
	"#pragma once\n"
	"#define MY_VERSION \"${git_version}\"\n"
)

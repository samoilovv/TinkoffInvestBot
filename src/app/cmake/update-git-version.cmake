# extract version from annotated tag in format vX.Y.Z
execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --match "v[0-9]*.[0-9]*.[0-9]*"
	WORKING_DIRECTORY "${GIT_DIR}"
	RESULT_VARIABLE result
        OUTPUT_VARIABLE tag
	ERROR_VARIABLE error
)

if ((NOT DEFINED tag) OR (tag STREQUAL ""))
        set(tag "v0.0.0")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} tag -a "${tag}" -m "auto-generated tag ${tag}"
                WORKING_DIRECTORY "${GIT_DIR}"
        )
endif()

string(REGEX MATCH "v[0-9]*.[0-9]*.[0-9]*-([0-9]*)" _ ${tag})
set(ver_build ${CMAKE_MATCH_1})
if(NOT DEFINED ver_build)
    set(ver_build 0)
endif()
string(REGEX MATCH "v[0-9]*.[0-9]*.([0-9]*)" _ ${tag})
set(ver_patch ${CMAKE_MATCH_1})

string(REGEX MATCH "v[0-9]*.([0-9]*).[0-9]*" _ ${tag})
set(ver_minor ${CMAKE_MATCH_1})

string(REGEX MATCH "v([0-9]*).[0-9]*.[0-9]*" _ ${tag})
set(ver_major ${CMAKE_MATCH_1})

execute_process(
        COMMAND ${GIT_EXECUTABLE} log --pretty=format:"%s" -1
        WORKING_DIRECTORY "${GIT_DIR}"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE commit_comment
        ERROR_VARIABLE error
)

set(needNewTag False)
if (${result} EQUAL 0)
    if ((commit_comment MATCHES "new patch|update patch/i") AND (NOT ${ver_build} EQUAL 0))
        set(needNewTag True)
        MATH(EXPR ver_patch "${ver_patch}+1")
        set(ver_build 0)
    endif()
    if ((commit_comment MATCHES "new minor|update minor/i") AND (NOT ${ver_patch} EQUAL 0))
        set(needNewTag True)
        MATH(EXPR ver_minor "${ver_minor}+1")
        set(ver_build 0)
        set(ver_patch 0)
    endif()
    if ((commit_comment MATCHES "new major|update major/i") AND (NOT ${ver_minor} EQUAL 0))
        set(needNewTag True)
        MATH(EXPR ver_major "${ver_major}+1")
        set(ver_build 0)
        set(ver_patch 0)
        set(ver_minor 0)
    endif()
    if(needNewTag)
        set(tag "v${ver_major}.${ver_minor}.${ver_patch}")
        execute_process(
                COMMAND ${GIT_EXECUTABLE} tag -a "${tag}" -m "${commit_comment}"
                WORKING_DIRECTORY "${GIT_DIR}"
        )
    endif()
endif()

set(version ${ver_major}.${ver_minor}.${ver_patch}-build${ver_build})

if (EXISTS "${VERSION_FILE}")
	file(READ "${VERSION_FILE}" old_version)
	if (old_version STREQUAL version)
		return()
	endif()
endif()

file(WRITE "${VERSION_FILE}" "${version}")

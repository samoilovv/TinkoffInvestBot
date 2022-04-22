find_package(Git REQUIRED)

set(update_git_version_script "${CMAKE_CURRENT_LIST_DIR}/update-git-version.cmake")

function(generate_git_version TARGET GIT_DIR VERSION_FILE)

	# add target to update Git version file at build time if neccessary
	# the BYPRODUCTS might be updated or not, depending whether Git tag was changed
	# this is required to avoid recompiling your project if nothing changed
	add_custom_target(${TARGET}
		COMMAND ${CMAKE_COMMAND}
			-D "GIT_EXECUTABLE=${GIT_EXECUTABLE}"
			-D "GIT_DIR=${GIT_DIR}"
			-D "VERSION_FILE=${VERSION_FILE}"
                        -P "${update_git_version_script}"
		BYPRODUCTS
			"${VERSION_FILE}"
		DEPENDS
                        "${update_git_version_script}"
	)
endfunction()

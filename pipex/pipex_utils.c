#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int is_directory(const char *path) {
	struct stat statbuf;

	if (stat(path, &statbuf) != 0) {
		perror("stat");
		return 0;
	}
	return S_ISDIR(statbuf.st_mode);
}

int is_executable(const char *path) {
	struct stat statbuf;

	if (stat(path, &statbuf) != 0) {
		perror("stat");
		return 0;
	}
	if ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP) || (statbuf.st_mode & S_IXOTH)) {
		return 1;
	} else {
		return 0;
	}
}

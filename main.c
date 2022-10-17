#include <stdio.h>
#include <string.h>
#include <dirent.h>

int isEmpty(const char *path)
{
	struct dirent *ent;
	int ret = 1;

	DIR *d = opendir(path);
	if (!d) {
		fprintf(stderr, "%s: ", path);
		perror("");
		return -1;
	}

	while ((ent = readdir(d))) {
		if (!strcmp(ent->d_name, ".") || !(strcmp(ent->d_name, "..")))
			continue;
		ret = 0;
		break;
	}

	closedir(d);
	return ret;
}

void findfiles(const char* dirname) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }
    struct dirent* ynt;
    ynt = readdir(dir);
    if (isEmpty(dirname))
    {
      printf("%s/\n", dirname);
    }
    while (ynt != NULL) {
      if(ynt->d_type == DT_REG)
      {
        printf("%s/%s\n",dirname, ynt->d_name);
      }
        if (ynt->d_type == DT_DIR && strcmp(ynt->d_name, ".") != 0 && strcmp(ynt->d_name, "..") != 0) {
            
            char path[1000] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, ynt->d_name);
            findfiles(path);
        }
        
        ynt = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    findfiles(argv[1]);
    return 0;
}
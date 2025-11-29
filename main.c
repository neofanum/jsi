#include <stdio.h>

#include "jsi.h"

int main(int argc, char* argv[]) {
    struct app jsi = {0};

    if (argc == 1) {
        print_usage();
        return 1;
    }

    snprintf(jsi.name, sizeof(jsi.name), "jsi %s", argv[1]);
    create_window(&jsi);
    load_image(&jsi, argv[1]);
    run(&jsi);
    cleanup(&jsi);
    return 0;
}

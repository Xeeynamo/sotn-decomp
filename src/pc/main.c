#include <common.h>

bool InitGame(void);
void MainGame(void);
void ResetGame(void);
int OpenCd(const char* filename);

int main(int argc, char* argv[]) {
    const char* filename;

    if (argc < 2) {
        filename = "disks/sotn.us.bin";
    } else {
        filename = argv[1];
    }
    OpenCd(filename);

    if (InitGame()) {
        MainGame();
    }
    ResetGame();
}

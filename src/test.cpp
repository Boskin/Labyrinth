#include <string>

int main() {
    std::string testFile;
	
	return 0;
}

void wait(int timeMillis) {
    /*int start = clock();
    while(((clock() - start) / CLOCKS_PER_SEC / 1000) < timeMillis);*/
}

void coolDownThread(void* coolDown) {
    /*int* coolDownTimer = reinterpret_cast<int*>(coolDown);
    wait(*coolDownTimer);
    *coolDownTimer = 0;
    _endthread();*/
}

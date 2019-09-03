#define PIPE_DATA_SIZE 56

struct pipe {
	int tileStart;
	int x;
	int y;
	unsigned char pipeData[PIPE_DATA_SIZE];
};

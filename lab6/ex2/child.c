#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FUNC(x) (4.0 / (x * x + 1.0))
#define FIFO_PATH "myfifo"

double calculate_integral(double start, double end, double width) {
    double sum = 0.0;
    double x;
    for (x = start; x < end; x += width) {
        sum += FUNC(x) * width;
    }
    return sum;
}

int main() {
    int fd = open(FIFO_PATH, O_RDONLY);

    char buffer[100];
    read(fd, buffer, sizeof(buffer));
    close(fd);

    double start, end;
    sscanf(buffer, "%lf %lf", &start, &end);

    double width = 0.00001;
    double result = calculate_integral(start, end, width);

    fd = open(FIFO_PATH, O_WRONLY);

    write(fd, &result, sizeof(result));
    close(fd);

    return 0;
}

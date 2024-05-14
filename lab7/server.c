#include <fcntl.h> /* For O_* constants */
#include <mqueue.h>
#include <sys/stat.h> /* For mode constants */

int main() {

  mqd_t mq_open(const char *name, int oflag);
  mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
}
